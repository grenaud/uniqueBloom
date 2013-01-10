/*
 * uniqueseq
 * Date: Dec-16-2012 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com
 *
 */

#include <iostream>
#include <fstream>

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

    if(argc ==1 ){
	cerr<<"Usage uniqueseqBloom [fastq file] [temp file]"<<endl;
	cerr<<"the [temp file] can be whatever you wish, just pick a file you can write to"<<endl;
	return 1;
    }

    counting_bloom_t *bloom;

    // PrefixTree<int>  trieSeq;
    FastQParser fqp (argv[1]);

    if (!(bloom = new_counting_bloom(CAPACITY, ERROR_RATE, argv[2]))) {
        cerr<<"ERROR: Could not create bloom filter\n"<<endl;
        return EXIT_FAILURE;
    }else{
	cerr<<"Created bloom filter "<<argv[1]<<endl;
    }

    while(fqp.hasData()){

	// cout<<"l1"<<endl;
    	FastQObj * test	=fqp.getData();
    

	if( counting_bloom_check(bloom, test->getSeq()->c_str(), test->getSeq()->size()  )== 0 ){ //not found
	    cout<<*test<<endl;
	    counting_bloom_add(bloom,  test->getSeq()->c_str(), test->getSeq()->size() );
	}else{
	    //do nothing
	}


	// cout<<"l2"<<endl;	
	//trieSeq.searchMismatch( (test->getSeq())->c_str(),&matches,0);
	// cout<<matches.size()<<endl;
	// if(matches.empty()){//not found
	//     trieSeq.insertIntoTree( test->getSeq()->c_str()  , 0);
	//     cout<<*test<<endl;
	// }else{
	//     //skip
	//     //cout<<"skip "<<*test<<endl;

	// }
	    
    }
    free_counting_bloom(bloom);

    return 0;
}

