#include <SubsetSumSolver.h>
#include<iostream>
#include <string>


 bool SSPSolverPD::solve(const std::vector< long> &input,
                            long value, std::vector< char> &output) {
    
    long w=0,i = 0;
    bool encontrouSol = false;
    std::vector<std::vector<long>> tabela;
    output.resize(input.size());
    tabela.resize(input.size());
    //std::cout<<"Começa PD"<<std::endl;
    //std::cout<<"value = "<< value <<std::endl;
    //std::cout<<"n = "<< input.size() <<std::endl;
    long index = 0,n = input.size();
    //std::cout<<"input = [" << input[index++];
    //while(index<n) std::cout<<" " << input[index++];
    //std::cout<<"]" << std::endl;
    index = 0;
    while(index<n)output[index++] = false;

    for(int i=input.size()-1;i>=0;i--)
    {
        tabela[i].resize(value+1,0);
        //for(long tamanho = value;tamanho >= 0;tamanho--)tabela[i][tamanho] = 0;
        //std::cout<<" flag01" << std::endl;
    } 
    i =0;
    //std::cout<<" flag02" << std::endl;
    for(long n = input.size();i<n&&(!encontrouSol);i++)
    {
        //std::cout<<" flag02:01" << std::endl;
        w = 0;
        for(;w<=value&&(!encontrouSol);w++)
        {
            //std::cout<<" flag02:02" << std::endl;
            //std::cout<<" i = " << i << "\nw="<<w<< std::endl;
            
            if(input[i]<=w)
            {
                //std::cout<<" flag02:03" << std::endl;
                if(i==0)
                {
                    //std::cout<<" flag02:04" << std::endl;
                    tabela[i][w] = input[i];
                }
                else if(input[i]+tabela[i-1][w-input[i]]>=tabela[i-1][w])
                {
                    //std::cout<<" flag02:05" << std::endl;
                    tabela[i][w] = input[i]+tabela[i-1][w-input[i]];

                }
                else
                {
                    //std::cout<<" flag02:06" << std::endl;
                    tabela[i][w] = tabela[i-1][w];
                }
                
            }
            else
            {
                //std::cout<<" flag02:07" << std::endl;
                tabela[i][w] = (i!=0?tabela[i-1][w]:0);

            }
            if(tabela[i][w]==value)
            {
                //std::cout<<" flag02:08" << std::endl;
                encontrouSol = true;

            }
        }
        
    }
    /*if(value<50&&!encontrouSol)
    {
        std::cout<<" Tabela:\n";
        for(int i=0;i<(input.size());i++)
        {
            for(long tamanho = value,j = 0;j <=tamanho;j++)std::cout<<" "<<(tabela[i][j]>9?std::to_string(tabela[i][j]):("0"+std::to_string(tabela[i][j]))) ;
            std::cout<<std::endl;
            //std::cout<<" flag01" << std::endl;
        } 

    }*/
    //std::cout<<" flag03" << std::endl;
    i--;
    w--;
    //std::cout<<" i = " <<i<<" w = " <<w<< std::endl;
    if(encontrouSol)
        while(i>=0&&w>0)
        {
            //std::cout<<" flag10" << std::endl;
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

    //std::cout<<" flag04" << std::endl;
    /*
    std::cout<<"\nencontrouSol = " << (encontrouSol?"true":"false") <<"\nterminou PD" <<std::endl;
    if(encontrouSol)
    {

        std::cout<<" flag05" << std::endl;
        index = 0;
        std::cout<<"input = [" << input[index++];
        while(index<n) std::cout<<" " << input[index++];
        std::cout<<"]" << std::endl;
        index = 0;
        std::cout<<"output = [" << (output[index++]?"true":"false");
        while(index<n) std::cout<<" " << (output[index++]?"true":"false");
        std::cout<<"]" << std::endl;
    }
    std::cout<<"\nterminou PD" <<std::endl;
    
    //if(encontrouSol&&value<60)std::cin>>value;
    //std::cout<<" flag06" << std::endl;*/
    return encontrouSol;
    
}
