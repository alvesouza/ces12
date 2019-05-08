
#include <SubsetSumSolverBalsub.h>
#include <balsub.h>


 bool SSPSolverBalsub::solve(const std::vector< long> &input,
                            long value, std::vector< char> &output) {
    
    long z;
    balsub(input,value,z,output);
    
    long sumSSP = 0;
    for (int i = 0 ; i < input.size() ; i++) {
        if (output[i]) sumSSP+= input[i];
    }
    
    return (sumSSP == value);
    
    
}
