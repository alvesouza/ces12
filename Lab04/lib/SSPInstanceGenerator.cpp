#include <SSPInstanceGenerator.h>



void SSPInstanceGenerator::generate(long size, std::vector< long> &input,  long &value) {
    input.resize(size,0);
    if (_alg == "RAND")
            fillRAND(size,input,value);
    else if (_alg[0] == 'P') {
            assert(isdigit(_alg[1]) && "the instance generator name must have the format P<digit> example: P3");
            fillP((_alg[1]-'0'),size,input,value); }
    else if (_alg == "EVOD") 
            fillEvenOdd(size,input,value);
    else if (_alg == "TODD") 
            fillTodd(size,input,value);
    else if (_alg == "AVIS") 
            fillAvis(size,input,value);
    else
            assert(false && "SSP called with invalid algorithm name");
    
    cutXAboveCapacity(input,value);
}// generate



void SSPInstanceGenerator::fillRAND(long size, std::vector< long> &input,  long &value) {
    unsigned long int i, k, st = 0, ed = 5, inc;
    for (i = 0; i < input.size() ; i++) {
        input[i] = (random() % (ed + 1 - st) + st) + 1;
        st += 6;
        ed = st + 5;
    }
    value = (input[input.size()-1] + input[input.size()-1]/3 )  ; // value is third above of the largest value in input
}//fillrand


void SSPInstanceGenerator::fillP(int order, long size, std::vector< long> &input,  long &value) {
     long i, k, st = 0, ed = 5, inc;
     long tenpower = std::pow(10,order);
    inc = (tenpower + input.size() - 1) / ( long)input.size();
    //std::cerr << " \n inc " << inc << "  tp: " << tenpower;
    st = 1, ed = inc;
    for (i = 0; i < input.size(); i++) {
        input[i] = (random() % (ed + 1 - st) + st);
        st += inc + 1;
        ed = st + inc;
    }//for
    
    value = input.size() * (tenpower / 4);
}//fillP

void SSPInstanceGenerator::fillEvenOdd(long size, std::vector< long> &input,  long &value) {
    long i, k, st = 0, ed = 5, inc;
    int arrSize = input.size();
    inc = (1e3 + arrSize - 1) / arrSize;
	st = 1, ed = inc;
	for (i = 0; i < arrSize; i++) {
        input[i] = ((st / 2) + random() % ((ed - st + 2) / 2)) * 2;
		st += inc + 1;
		ed = st + inc;
    }//for
    value = (input.size() * (1000 / 4)) + 1;
}//fillEvenOdd

void SSPInstanceGenerator::fillTodd(long size, std::vector< long> &input,  long &value) {
    long i, k, st = 0, ed = 5, inc;
    int arrSize = input.size();
    k = floor(log2(arrSize));
	for (i = 0; i < arrSize; i++) {
		input[i] = std::pow(2, k + arrSize + 1) + std::pow(2, k + i) + 1;
	}//for
	
    value = (input.size() + 1) * std::pow(2, k + input.size()) - std::pow(2, k) + floor(input.size() / 2);
}//fillTodd

void SSPInstanceGenerator::fillAvis(long size, std::vector< long> &input,  long &value) {
    long i, k, st = 0, ed = 5, inc;
    int arrSize = input.size();

    for (i = 0; i < arrSize; i++) {
			input[i] = arrSize * (arrSize + 1) + i;
	}
	value =  floor((input.size() - 1) / 2) * input.size() * (input.size() + 1)
				+ (fatorial(input.size()) / (fatorial(2) * fatorial(input.size() - 2)));
}

		
/////////// AUXILIARY FUNCTIONS ///////////

void cutXAboveCapacity(std::vector< long> &input, const  long &value) {
    std::sort(input.begin(), input.end());
    bool cut = false;
     long i;
    for ( i = 0 ; i < input.size() ; i++)
        if (input[i] > value) { cut = true; break; }
    if (cut) {
        input.resize(i-1);
    }
}//cutXAboveCapacity

void streamSSP(std::ostream &os, const std::vector< long> &input, const  long &value) {
    os << std::endl << "INP("<< input.size() << ") [ " ;
    for (int i : input) 
        os << i << " " ;
    os << "] "<< std::endl <<  "val: " << value << std::endl ;
}//streamSSP


// version that includes solution
void streamSSP(std::ostream &os, const std::vector< long> &input,const  long &value,      
               const std::vector<char> &x) {
    streamSSP(os,input,value);
    os << "ans: [ " ;
    long sumsol = 0;
    for (int i=0; i < x.size(); i++) {
        if (x[i]) os << i; else os << '.'; 
        os << " " ;
        if (x[i]) sumsol+=input[i];
    }//for
    os << "] "<< std::endl <<  "sum: " << sumsol << std::endl ;
}//streamSSP

double fatorial(int n) {
    //https://en.cppreference.com/w/cpp/numeric/math/tgamma
    return std::tgamma((double)n+1); // this is factorial
}


