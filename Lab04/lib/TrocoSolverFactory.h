#ifndef TROCO_SOLVER_FACTORY
#define TROCO_SOLVER_FACTORY

#include <TrocoSolver.h>
#include <string>

class TrocoSolverFactory {
public:
    static TrocoSolverAbstract* make(std::string name); 
           
};//factory


#endif
