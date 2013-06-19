
CXX      = g++   
LIBGAB   = /home/gabriel_renaud/lib/

CXXFLAGS = -Wall -lm -O3 -lz -I${LIBGAB} -I${LIBGAB}/VCFparser/ -I${LIBGAB}/VCFparser/gzstream/  -c
LDFLAGS  = -lz


all:   uniqueseqBloom #uniqueseq

# uniqueseq.o:	uniqueseq.cpp
# 	${CXX} ${CXXFLAGS} uniqueseq.cpp

# uniqueseq:	uniqueseq.o ${LIBGAB}utils.o   ${LIBGAB}/VCFparser/FastQParser.o ${LIBGAB}/VCFparser/FastQObj.o  ${LIBGAB}/VCFparser/gzstream/libgzstream.a PrefixTree.o
# 	${CXX}  -o $@ $^ $(LDLIBS) $(LDFLAGS)

uniqueseqBloom.o:	uniqueseqBloom.cpp
	${CXX} ${CXXFLAGS} -I/home/gabriel_renaud/scripts/uniqueSeqs/dablooms/dablooms/src/ uniqueseqBloom.cpp

uniqueseqBloom:	uniqueseqBloom.o ${LIBGAB}utils.o  ${LIBGAB}/VCFparser/FastQParser.o ${LIBGAB}/VCFparser/FastQObj.o /home/gabriel_renaud/scripts/uniqueSeqs/dablooms/dablooms/build/libdablooms.a  ${LIBGAB}/VCFparser/gzstream/libgzstream.a 
	${CXX}  -o $@ $^ $(LDLIBS) $(LDFLAGS)

# PrefixTree.o:	PrefixTree.cpp
# 	g++ -g $(CXXFLAGS) -c  $^

clean :
	rm -f uniqueseq.o uniqueseq PrefixTree.o uniqueseqBloom

