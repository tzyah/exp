#ifndef WAH_HPP__
#define WAH_HPP__

#include <vector>

namespace tzyah { namespace wah {

  template <typename Word>
    struct word_traits {
        typedef Word type;

        static const Word LITERAL_BITS  = sizeof(Word) * 8 - 1;
        static const Word
          RUNLEN_MAX = static_cast<Word>(1) << (LITERAL_BITS - 1);

        static const Word RUNLEN_MASK = RUNLEN_MAX - 1;
        static const Word FILL_MASK = ~RUNLEN_MASK;

        static const Word
          LITERAL_FLAG  = static_cast<Word>(1) << LITERAL_BITS;
        static const Word
          ONE_FILL_FLAG = static_cast<Word>(1) << (LITERAL_BITS - 1);
    };

  template <
    typename Value, typename Word, typename Container = std::vector<Word>
  >
    class bitset {

      public: // typedefs
        typedef Value value_type;
        typedef Word word_type;
        typedef Container container_type;

      public: // iterators
        typedef typename container_type::iterator iterator;
        typedef typename container_type::const_iterator const_iterator;

        iterator begin() { return container_.begin(); }
        const_iterator begin() const { return container_.begin(); }
        iterator end() { return container_.end(); }
        const_iterator end() const { return container_.end(); }

      private:
        container_type container_;

      private: // utility
        static value_type at_word(const value_type& v)
        {
          return v / word_traits<word_type>::LITERAL_BITS;
        }

      public: // constructor
        bitset() {}

      public:
        void set(const value_type& v)
        {
          typedef word_traits<word_type> tr;

          const value_type word_index = at_word(v);
          const word_type literal
            = static_cast<word_type>(1) << (v - tr::LITERAL_BITS * word_index)
            | tr::LITERAL_FLAG;

          value_type i = 0;

          for (
            iterator it = container_.begin();
            it != container_.end();
            ++it
          ) {
            // for literal word
            if (*it & tr::LITERAL_FLAG) {
              if (i == word_index) {
                *it |= literal;
                return;
              }
              ++i;
              continue;
            }

            // for [01]-fill word
            const word_type runlen = (*it & tr::RUNLEN_MASK) + 1;

            // skip until approaching word_index
            if (i + runlen <= word_index) {
              i += runlen;
              continue;
            }

            // set() don't have to do nothing on 1-fill word
            if ((*it & tr::FILL_MASK) == tr::ONE_FILL_FLAG) {
              return;
            }

            // first bit of word
            if (runlen == 0) {
              *it = literal;
              return;
            }

            // when word index of value is the head of zero sequence,
            // insert target value literal in front of the 0-fill
            // word and decrement the runlength of the 0-fill word.
            if (i == word_index) {
              it = container_.insert(it, literal);
              --*++it;
              return;
            }

            // opposite situation above
            if (i + runlen == word_index) {
              --*it;
              it = container_.insert(++it, literal);
              return;
            }

            // when word index is middle of runs,
            // shorten the beginning length, insert target literal
            // and create (and also insert) trailing 0-fill word.
            //
            // TODO: There is a concern about fragmentation of fill words,
            // but no concatination is implemented now.
            *it = word_index - i - 1;
            it = container_.insert(++it, literal);
            const word_type trail_len = runlen - (word_index + 1 - i) - 1;
            it = container_.insert(++it, trail_len);
            return;
          }

          // if no word to be set literal in container,
          // push skip words and literal.
          for (value_type rest; (rest = word_index - i) != 0; ) {
            word_type w
              = std::min(rest, static_cast<value_type>(tr::RUNLEN_MAX)) - 1;
            container_.push_back(w);
            i += w + 1;
          }
          container_.push_back(literal);
        }
      
    };

}} // tzyah::wah

#endif
