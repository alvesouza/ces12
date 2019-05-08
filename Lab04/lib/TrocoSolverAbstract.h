#ifndef TROCO_SOLVER_ABSTRACT
#define TROCO_SOLVER_ABSTRACT


class TrocoSolverAbstract {
public:
    
    virtual void solve(const std::vector<unsigned int> &denom,
                       unsigned int value, std::vector<unsigned int> &coins)=0; 
                       
    virtual std::string getName() { return "ABSTRACT"; }
    
    virtual long countRecursiveCalls() { return 0; }
    
}; 


#endif
