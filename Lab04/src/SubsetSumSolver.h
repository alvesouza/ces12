#ifndef SSP_SOLVER
#define SSP_SOLVER


#include <vector>
#include <string>
#include <SubsetSumSolverAbstract.h>


class SSPSolverBranchBound : public SubsetSumSolverAbstract {

    
public:
    
    virtual bool solve(const std::vector< long> &input,
                        long value, std::vector< char> &output);

    bool recursiveBranchBound(const std::vector< long> &input,long i,
                            long value, std::vector< char> &output);
        
    virtual std::string getName() { return "BB"; }
    
}; 

class SSPSolverPD : public SubsetSumSolverAbstract {

public:
    
    virtual bool solve(const std::vector< long> &input,
                        long value, std::vector< char> &output);
    
    virtual std::string getName() { return "PD"; }
    
}; 

#endif
