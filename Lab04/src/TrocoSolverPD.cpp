#include <TrocoSolver.h>

void TrocoSolverPD::solve(const std::vector<unsigned int> &denom,unsigned int value, std::vector<unsigned int> &coins) {
    unsigned int quantProv;
    unsigned int ultProv;
    std::vector<int> quant;
    quant.resize(value+1,-1);//inicializa o vetor quant
    quant[0] = 0;
    coins.resize(denom.size(),0);//inicializa o vetor coins 
    std::vector<unsigned int> ultima;
    ultima.resize(value+1,0);//inicializa o vetor ultima que representa o valor da ultima moeda da solução
    // moedas: vetor de moedas disponíveis (menor é de 1 centavo)
    //quant[0] = 0; // solução ótima para troco de valor 0
    //ultima[0] = 0; // última moeda dessa solução
    for (unsigned int cents = 1; cents <= value; cents++) {
        quantProv = -1; // solução provisória: todas de 1 centavo
        ultProv = 0; // última moeda dessa solução
        for (int j = 0; j < denom.size(); j++) {
            if (denom[j] > cents) continue; // essa moeda não serve
            if (quant[cents - denom[j]] + 1 < quantProv || quantProv == -1) {
                if(quant[cents - denom[j]]==-1)continue;//siginifica que não tem solução
                quantProv = quant[cents - denom[j]] + 1;
                ultProv = j;//j não é a moeda mas é o index de denom,para podermos saber o valor
            }
        }
        quant[cents] = quantProv; // solução para troco == cents
        ultima[cents] = ultProv; // última moeda dessa solução
    }

    //loop para se determinar as moedas do troco
    while(value > 0)
    {
        if (quant[value] == -1)//se negativo não é solução
            break;
        coins[ultima[value]] ++;//"ultima[value]" é o index do denom da ultima moeda usada
        value -= denom[ultima[value]];//subtrai o valor da ultima moeda usada
    }
    if (value == 0)
        return;
    // fills a dummy answer with 2 coins of each denomination    
    coins.resize(denom.size(),2); 
    
    
}//solve
