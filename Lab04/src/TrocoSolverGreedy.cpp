#include <TrocoSolver.h>

void TrocoSolverGreedy::solve(const std::vector<unsigned int> &denom,unsigned int value, std::vector<unsigned int> &coins) {

    // fills a dummy answer with 3 coins of each denomination    
    coins.resize(denom.size(),3); 
    
    
}//solve

// dica: iterar um vetor de tras pra frente
//https://stackoverflow.com/questions/3610933/iterating-c-vector-from-the-end-to-the-begin
//http://www.cplusplus.com/reference/vector/vector/rbegin/
