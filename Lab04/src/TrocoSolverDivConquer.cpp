#include <TrocoSolver.h>

void TrocoSolverDivConquer::solve(const std::vector<unsigned int> &denom,unsigned int value, std::vector<unsigned int> &coins) {
    //std::cout<<"Começa DIV"<<std::endl;
    //std::cout<<"value = "<< value <<std::endl;

    int quant;//quantidade que vai receber o menor numero de moedas necessarias
    coins.resize(denom.size(),0);//a coins recebe o valor zero pelo vetor inteiro e tem o tamanho alterado 
    recursivecalls = -1;//recebe -1 pois ainda não é recurssão
    
    //std::cout<<"\ndenom.size() = " << denom.size() <<"\nvalue = "<< value <<std::endl;
    quant = recursiveTroco(denom,denom.size()-1,value, coins);

    if(quant >=0) return;//se quant for menor que zero significa que não tem solução 

    // fills a dummy answer with 1 coin of each denomination    
    coins.resize(denom.size(),1);//coins recebe 1 em todos caso não tenha solução 
    //std::cout<<"Termina DIV"<<std::endl;
    
    
}//solve

int TrocoSolverDivConquer::recursiveTroco(const std::vector<unsigned int> &denom,int ultima,
    unsigned int value, std::vector<unsigned int> &coinsProv)
{
    // coinsProv1e2 são vetores que serão parametros para as variaveis de entrada, e são copias de coinsProv 
    std::vector<unsigned int> coinsProv1(coinsProv), coinsProv2(coinsProv);//vai aumentar bastante a quantidade de memora necessaria

    int aux1 = -1,aux2 = -1;//aux irão receber o numero de moedas necessarias para resolver
    
    recursivecalls++;//na primeira chamada começa com -1 pois na primeira vez que chama ainda não foi recursão
    
    if (ultima < 0) return -1;//ultima é a maior ordem da moeda a ser utilizada 

    if(value<=0)//se valor for menor ou igual a zero quer dizer que tem que acabou
    {
        if(value<0) return -1;//se value for menor que zero que dizer que não é solução
        return 0;//se retornar 0 quer dizer que é uma solução possivel talvez não é otima
    }
    
    coinsProv1[ultima]++;//adciona um na coinsProv,para a aux1
    //std::cout<<"ultima = "<< ultima <<"\nvalue = "<< value <<"\ndenom[ultima] = "<< denom[ultima] <<std::endl;
    if(value >= denom[ultima]) aux1 = TrocoSolverDivConquer::recursiveTroco(denom, ultima,value - denom[ultima], coinsProv1);
    aux2 = TrocoSolverDivConquer::recursiveTroco(denom, ultima-1,value, coinsProv2);

    //vai verificar qual é solução e vai retornar a menor das soluções
    if((aux1<aux2 && aux1 !=-1)||(aux2==-1 &&aux1!=-1))
    {
        coinsProv = coinsProv1;
        return aux1+1;
    }
    else
    {
        coinsProv = coinsProv2;
        return aux2;
    }

}