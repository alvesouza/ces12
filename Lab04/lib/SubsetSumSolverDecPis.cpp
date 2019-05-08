
#include <SubsetSumSolverDecPis.h>



 bool SSPSolverDecPis::solve(const std::vector< long> &input,
                            long value, std::vector< char> &output) {
    
    output.resize(input.size(),0);
    std::vector<int> int_output;
    int_output.resize(input.size(),0);
    std::vector<long> input_copy;
    input_copy.resize(input.size(),0);
    for (int i = 0 ; i < input.size() ; i++)
        input_copy[i] = input[i];
    
    
    long z = decompL(input.size(), input_copy.data(), int_output.data(), value);
    
    
    for (int i = 0 ; i < input.size() ; i++) {
        output[i] = int_output[i];
        
    }//for
    
    
    //std::cerr << "\n******** val " << value <<  " z " << z << " =? " << (z == value);
    
    return (z == value);
    
}
