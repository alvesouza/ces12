#include <SubsetSumSolver.h>
#include<iostream>

bool SSPSolverBranchBound::solve(const std::vector< long> &input,long value, std::vector< char> &output)
{
    std::cout<<"Começa BranchBound"<<std::endl;
    std::cout<<"value = "<< value <<std::endl;
    output.resize(input.size(),false);
    
    long i = -1;
    bool encontrouSol = false;
    //coins.resize(denom.size(),0);//a coins recebe o valor zero pelo vetor inteiro e tem o tamanho alterado 
    //recursivecalls = -1;//recebe -1 pois ainda não é recurssão
    long index = 0,n = input.size();
    std::cout<<"input = [" << input[index++];
    while(index<n) std::cout<<" " << input[index++];
    std::cout<<"]" << std::endl;
    //std::cout<<"\ndenom.size() = " << denom.size() <<"\nvalue = "<< value <<std::endl;
    encontrouSol = SSPSolverBranchBound::recursiveBranchBound(input,i,value, output);
    std::cout<<"\nencontrouSol = " << (encontrouSol?"true":"false") <<"\nterminou branchbound" <<std::endl;
    if(encontrouSol)
    {
        index = 0;
        std::cout<<"input = [" << input[index++];
        while(index<n) std::cout<<" " << input[index++];
        std::cout<<"]" << std::endl;
        index = 0;
        std::cout<<"output = [" << (output[index++]?"true":"false");
        while(index<n) std::cout<<" " << (output[index++]?"true":"false");
        std::cout<<"]" << std::endl;
    }
    return encontrouSol;//se quant for menor que zero significa que não tem solução 

    // fills a dummy answer with 1 coin of each denomination    
    //coins.resize(denom.size(),1);//coins recebe 1 em todos caso não tenha solução 
    //std::cout<<"Termina DIV"<<std::endl;
    
    
}//solve

 bool SSPSolverBranchBound::recursiveBranchBound(const std::vector< long> &input,long i,
                            long value, std::vector< char> &output) {
    i++;
    bool encontrouSol1 = false,encontrouSol2 = false;
    if(i==input.size())return (value==0);
    else if(value==0)return true;

    encontrouSol1 = SSPSolverBranchBound::recursiveBranchBound(input,i,value-input[i], output);
    if(!encontrouSol1)encontrouSol2 = SSPSolverBranchBound::recursiveBranchBound(input,i,value, output);

    if(encontrouSol1)output[i] == true;

    return (encontrouSol1||encontrouSol2);
    
}
