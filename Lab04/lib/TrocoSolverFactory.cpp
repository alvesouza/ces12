#include <TrocoSolverFactory.h>

       
TrocoSolverAbstract* TrocoSolverFactory::make(std::string name) {
    if (!name.compare("PD"))
        return new TrocoSolverPD();
    else if (!name.compare("GR"))
        return new TrocoSolverGreedy();
    else if (!name.compare("DC"))
        return new TrocoSolverDivConquer();
    else return nullptr;
}
