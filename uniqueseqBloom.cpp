/*
 * uniqueseq
 * Date: Dec-16-2012 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com
 *
 */

#include <iostream>
#include <fstream>
#include <gzstream.h>

#include "FastQParser.h"
#include "FastQObj.h"
// #include "PrefixTree.h"

#include "utils.h"

extern "C" {
#include "dablooms.h"
}
#define CAPACITY 10000000000
#define ERROR_RATE .0005

using namespace std;

int main (int argc, char *argv[]) {
    bool isFasta   =false;
    bool hasReverse=false;
    //    bool outputSpecified=false;

    string revReads;
    string outRevReads;
    string outputStr="/dev/stdout";

    ogzstream myFileo;
    ogzstream myFileo2;

    // streambuf  * buf;    

    if(argc ==1 ){
	cerr<<"Usage uniqueseqBloom [fastq file] [temp file] "<<endl;
	cerr<<"the [temp file] can be whatever you wish, just pick a file you can write to"<<endl;
	cerr<<"Options:"<<endl;
	cerr<<"\t-f\tInput is fasta"<<endl;
	cerr<<"\t-o\tOutput (default: stdout)"<<endl;
	cerr<<"\t-r\tInput Reverse reads"<<endl;
	cerr<<"\t-p\tOutput Reverse reads"<<endl;

	return 1;
    }

    for(int i=1;i<(argc-2);i++){ 

	if(string(argv[i]) == "-f"){
            isFasta=true;
            continue;
        }

	if(string(argv[i]) == "-r"){
            hasReverse=true;
	    revReads=string(argv[i+1]);
	    i++;
            continue;
        }

	if(string(argv[i]) == "-p"){
	    outRevReads=string(argv[i+1]);
	    i++;
            continue;
        }

	if(string(argv[i]) == "-o"){
	    outputStr=string(argv[i+1]);
	    // buf =  new     streambuf (outputStr);
	    //	    outputSpecified=true;
	    i++;
            continue;
        }

    }



    

    if(outRevReads.empty()){

	if(hasReverse){
	    cerr<<"You must specify the output for the reverse reads"<<endl;
	    return 1;
	}

    }

    // if(!outputSpecified){
    // 	buf  =  cout.rdbuf();
    // }

    //    myFileo(buf);
    myFileo.open(outputStr.c_str(), ios::out);
    myFileo2.open(outRevReads.c_str(), ios::out);

    counting_bloom_t *bloom;

    // PrefixTree<int>  trieSeq;
    FastQParser fqp (argv[argc-2],isFasta);
    FastQParser * fqp2=0;

    if(hasReverse){
	fqp2  = new FastQParser(revReads,isFasta);
    }
    
    if (!(bloom = new_counting_bloom(CAPACITY, ERROR_RATE, argv[argc-1]))) {
        cerr<<"ERROR: Could not create bloom filter\n"<<endl;
        return EXIT_FAILURE;
    }else{
	cerr<<"Created bloom filter "<<argv[argc-1]<<endl;
    }

    while(fqp.hasData()){

	// cout<<"l1"<<endl;
    	FastQObj * test	=fqp.getData();
    	FastQObj * test2=0;
	    //=fqp.getData();
	
	string * strtocheck=test->getSeq();

	if(hasReverse){
	    fqp2->hasData();	    
	    test2=fqp2->getData();
	    //strtocheck=strtocheck+"#"+test->getSeq();
	    strtocheck->append(string("#")+*(test2->getSeq()) );
	    //	    cout<<*strtocheck<<endl;
	}

	if( counting_bloom_check(bloom, strtocheck->c_str(), strtocheck->size()  )== 0 ){ //not found
	    myFileo <<*test<<endl;
	    if(hasReverse){ 	    myFileo2<<*test2<<endl; }
	    counting_bloom_add(bloom,  strtocheck->c_str(), strtocheck->size() );
	}else{//not unique
	    //do nothing
	}


	    
    }
    free_counting_bloom(bloom);

    myFileo.close();
    myFileo2.close();

    return 0;
}

