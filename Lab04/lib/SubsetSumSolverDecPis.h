#ifndef SSP_SOLVER_SUBSUMPISINGER
#define SSP_SOLVER_SUBSUMPISINGER


#include <vector>
#include <string>
#include <SubsetSumSolverAbstract.h>
#include <iostream>
#include <subsum.h>

class SSPSolverDecPis : public SubsetSumSolverAbstract {

    
public:
    
    virtual bool solve(const std::vector< long> &input,
                        long value, std::vector< char> &output);
        
    virtual std::string getName() { return "DD"; }
    
}; 




#endif
