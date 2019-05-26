#include <TrocoSolver.h>
#include<iostream>

void TrocoSolverGreedy::solve(const std::vector<unsigned int> &denom,unsigned int value, std::vector<unsigned int> &coins) {
    
    //std::cout<<"\n\nComeça Greedy"<<std::endl;
    //std::cout<<"value =  " << value <<std::endl;
    //std::cout<<"value = "<< value <<std::endl;
    coins.resize(denom.size(),0);//altera o tamanho do vetor e zera suas posições 
    
    for(int i = denom.size()-1;i>=0 && value>0;i--)
    {
        //std::cout<<"\nEntra loop\n"<<std::endl;
        //std::cout<<"value =  " << value <<std::endl;
        //std::cout<<"denom["<<i<<"] = " << denom[i] <<std::endl;
        if(value>=denom[i])//se for aceita quer dizer que no greedy,vai fazer parte da solução
        {
            //std::cout<<"coins["<<i<<"] = " <<int(value/denom[i])<<std::endl;
            coins[i] = int(value/denom[i]);
            value = value%denom[i];//retorna o resto da divisão acima
        }
    }
    if(value == 0)//se value for zero, ele possui solução
        return;
    // fills a dummy answer with 3 coins of each denomination    
    coins.resize(denom.size(),3); 
    //std::cout<<"Termina Greedy\n\n"<<std::endl;
    
}//solve

// dica: iterar um vetor de tras pra frente
//https://stackoverflow.com/questions/3610933/iterating-c-vector-from-the-end-to-the-begin
//http://www.cplusplus.com/reference/vector/vector/rbegin/
