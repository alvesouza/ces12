#ifndef CES12_SSPSOLVERFACTORY_H
#define CES12_SSPSOLVERFACTORY_H

#include <SubsetSumSolverAbstract.h>
#include <SubsetSumSolverBalsub.h>
#include <SubsetSumSolverDecPis.h>
#include <SubsetSumSolver.h>


class SSPSolverFactory {
    
public:
    static  SubsetSumSolverAbstract* makeSSP(std::string name);
    
    
};//factory



#endif
