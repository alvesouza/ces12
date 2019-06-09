#ifndef TSP_SOLVER
#define TSP_SOLVER

#include <TspSolver.h>
#include <TspReader.h>
#include <vector>
#include<iostrea>

class aresta
{
public:
    int city[2];
    int distancia;
};


class heapMinAresta{
public:
    std::vector<aresta> vetorAresta;
    int size;
    heapMinAresta()
    {
        size = 0;
        vetorAresta.resize(1);
    }
    void setHeapMaxSize(int n)
    {
        vetorAresta.resize(n+1);
    }
    aresta Min();
    aresta extractMin();
    void insertAresta(aresta x);
    void insertVetorAresta(std::vector<std::vector<int>> &matriz,int indice,std::vector<bool> &naArvore);
    void Modify(int i,aresta x);
    void Build();
private:
    void Sift(int i);
    
    
};
class TspSolver {
public:
    // you should fill percourse with a permutation that represents the TSP solution
    void solve(TspReader &tr,std::vector<int> &percourse); 
    void makeMatrix(std::vector<std::vector<int>> &matriz,std::vector<int> &index,TspReader &tr);
    void prim(std::vector<std::vector<int>> &matriz,std::vector<int> &index,std::vector<int> &caminho);
        


}; 



#endif
