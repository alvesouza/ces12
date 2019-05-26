#include <SubsetSumSolver.h>
#include<iostream>


 bool SSPSolverPD::solve(const std::vector< long> &input,
                            long value, std::vector< char> &output) {
    
    long w=0,i = 0;
    bool encontrouSol = false;
    std::vector<std::vector<long>> tabela;
    output.resize(input.size(),false);
    tabela.resize(input.size());
    std::cout<<"Começa PD"<<std::endl;
    std::cout<<"value = "<< value <<std::endl;

    long index = 0,n = input.size();
    std::cout<<"input = [" << input[index++];
    while(index<n) std::cout<<" " << input[index++];
    std::cout<<"]" << std::endl;

    for(int i=input.size()-1;i>=0;i--)
    {
        tabela[i].resize(value+1,0);
    }

    for(long n = input.size();i<=n&&(!encontrouSol);i++)
    {
        for(w = 1;w<=value&&(!encontrouSol);w++)
        {
            if(input[i]<=w)
            {
                if(i==0)
                {
                    tabela[i][w] = input[i];
                }
                else if(input[i]+tabela[i-1][w-input[i]]>=tabela[i-1][w-input[i]])
                    tabela[i][w] = input[i]+tabela[i-1][w-input[i]];
                else
                    tabela[i][w] = tabela[i-1][w];
                
            }
            else
                tabela[i][w] = tabela[i-1][w];
            if(tabela[i][w]==value)
                encontrouSol = true;
        }
    }
    i--;
    w--;
    if(encontrouSol)
        while(i>=0&&w>0)
        {
            if(i>0)
            {
                if(tabela[i][w] != tabela[i-1][w])
                {
                    output[i] = true;
                    w -= input[i];
                }
                i--;
            }
            else
            {
               if(tabela[i][w] == input[i])
                {
                    output[i] = true;
                    w -= input[i];
                }
                i--; 
            }
            

        }

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
    return encontrouSol;
    
}
