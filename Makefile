
CXX      = g++   
LIBGAB   = /home/gabriel_renaud/lib/

CXXFLAGS = -Wall -lm -O3 -lz -I${LIBGAB} -I${LIBGAB}/VCFparser/  -c
LDFLAGS  = -lz


all: uniqueseq  uniqueseqBloom

uniqueseq.o:	uniqueseq.cpp
	${CXX} ${CXXFLAGS} uniqueseq.cpp

uniqueseq:	uniqueseq.o ${LIBGAB}utils.o   ${LIBGAB}/VCFparser/FastQParser.o ${LIBGAB}/VCFparser/FastQObj.o  PrefixTree.o
	${CXX} $(LDFLAGS) -o $@ $^ $(LDLIBS)

uniqueseqBloom.o:	uniqueseqBloom.cpp
	${CXX} ${CXXFLAGS} -I/home/gabriel_renaud/scripts/uniqueSeqs/dablooms/dablooms/src/ uniqueseqBloom.cpp

uniqueseqBloom:	uniqueseqBloom.o ${LIBGAB}utils.o   ${LIBGAB}/VCFparser/FastQParser.o ${LIBGAB}/VCFparser/FastQObj.o /home/gabriel_renaud/scripts/uniqueSeqs/dablooms/dablooms/build/libdablooms.a
	${CXX} $(LDFLAGS) -o $@ $^ $(LDLIBS)

PrefixTree.o:	PrefixTree.cpp
	g++ -g $(CXXFLAGS) -c  $^

clean :
	rm -f uniqueseq.o uniqueseq PrefixTree.o uniqueseqBloom

