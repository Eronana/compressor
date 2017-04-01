CXX=g++
RM=rm -f
CPPFLAGS=-O2 -Wall -std=c++11


SRCS=main.cpp utils.cpp config.cpp compressor.cpp uncompressor.cpp lzhash.cpp bitstream.cpp lz77.cpp huffman.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(CPPFLAGS) -o main $(OBJS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend