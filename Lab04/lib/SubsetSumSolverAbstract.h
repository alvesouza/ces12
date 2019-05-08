#ifndef SSP_SOLVER_ABSTRACT
#define SSP_SOLVER_ABSTRACT

#include <vector>
#include <string>

class SubsetSumSolverAbstract {
public:
    
    virtual bool solve(const std::vector< long> &input,
                        long value, std::vector< char> &output)=0; 
                       
    virtual std::string getName() { return "ABSTRACT"; }

}; 


#endif
