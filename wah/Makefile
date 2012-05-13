CC=g++
CXX=g++

CXXFLAGS=-Wall -Werror -O3 -g -march=native

CXX_SRC = \
  make_random_list.cc \
  decode_wah.cc \
  encode_wah.cc \
  print_wah.cc \
  $(NULL)

OBJS=$(patsubst %.cc,%.o,$(CXX_SRC))
DEPENDS=$(patsubst %.cc,%.d,$(CXX_SRC))

TARGETS=$(patsubst %.cc,%,$(CXX_SRC))

# rules

.PHONY : all clean distclean depend

all: $(TARGETS)

clean:
	rm -f $(OBJS) $(DEPENDS)
distclean: clean
	rm -f $(TARGETS)

%.d: %.cc
	@set -e; $(CXX) -MM $(CXXPFLAGS) $< \
	  | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	  [ -s $@ ] || rm -f $@

-include $(DEPENDS)
