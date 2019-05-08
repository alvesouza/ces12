
#include <SSPSolverFactory.h>


SubsetSumSolverAbstract* SSPSolverFactory::makeSSP(std::string name) {
    if (name == "BS" )
        return new SSPSolverBalsub();
    else if (name == "PD" )
        return new SSPSolverPD();
    else if (name == "BB" )
        return new SSPSolverBranchBound();
    else if (name == "DD" )
        return new SSPSolverDecPis();
    else return nullptr;
    }
