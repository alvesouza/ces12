#ifndef SSP_SOLVER_BALSUB
#define SSP_SOLVER_BALSUB


#include <vector>
#include <string>
#include <SubsetSumSolverAbstract.h>


class SSPSolverBalsub : public SubsetSumSolverAbstract {

    
public:
    
    virtual bool solve(const std::vector< long> &input,
                        long value, std::vector< char> &output);
        
    virtual std::string getName() { return "BS"; }
    
}; 




#endif
