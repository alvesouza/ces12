#include <TrocoSolver.h>

void TrocoSolverGreedy::solve(const std::vector<unsigned int> &denom,unsigned int value, std::vector<unsigned int> &coins) {
    
    coins.resize(denom.size(),0);//altera o tamanho do vetor e zera suas posições 
    
    for(int i = denom.size()-1;i>0 && value>0;i--)
    {
        if(value>=denom[i])//se for aceita quer dizer que no greedy,vai fazer parte da solução
        {
            coins[i] = int(value/denom[i]);
            value = value%denom[i];//retorna o resto da divisão acima
        }
        i--;
    }
    if(value == 0)//se value for zero, ele possui solução
        return;
    // fills a dummy answer with 3 coins of each denomination    
    coins.resize(denom.size(),3); 
    
    
}//solve

// dica: iterar um vetor de tras pra frente
//https://stackoverflow.com/questions/3610933/iterating-c-vector-from-the-end-to-the-begin
//http://www.cplusplus.com/reference/vector/vector/rbegin/
