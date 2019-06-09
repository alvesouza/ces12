#include <TspSolver.h>

struct noLista
{
    no *atual;
    noLista *prox;
};

struct no
{
    int indiceCity;
    noLista *listaFilhos;
};

void heapMinAresta::Sift(int i)
{
    int esq = 2*i;
    int dir = 2*i+1;
    int menor = i;
    aresta aux;
    if (esq <= size && vetorAresta[esq].distancia <= vetorAresta[i].distancia)
        {
            if(vetorAresta[esq].distancia < vetorAresta[i].distancia||(vetorAresta[esq].city[1]<vetorAresta[i].city[1])||(vetorAresta[esq].city[2]<vetorAresta[i].city[2]))
                menor = esq;
        }
    if (dir <= size && vetorAresta[dir].distancia <= vetorAresta[menor].distancia)
        {
            if(vetorAresta[dir].distancia < vetorAresta[i].distancia||(vetorAresta[dir].city[1]<vetorAresta[i].city[1])||(vetorAresta[dir].city[2]<vetorAresta[i].city[2]))
                menor = dir;

        }
    if (menor != i) {
        aux = vetorAresta[i];
        vetorAresta[i] = vetorAresta[menor];
        vetorAresta[menor] = aux;
        Sift(menor);
    }
}

void heapMinAresta::Modify(int i,aresta x)
{
    aresta aux;
    vetorAresta[i].city[1] = x.city[1];
    vetorAresta[i].city[2] = x.city[2];
    vetorAresta[i].distancia = x.distancia;
    while (i > 1 && vetorAresta[i/2].distancia > vetorAresta[i].distancia) { //conserta para cima
        aux = vetorAresta[i];
        vetorAresta[i] = vetorAresta[i/2];
        vetorAresta[i/2] = aux;
        i=i/2;
    }
    Sift(i); // ou conserta para baixo

}

void heapMinAresta::insertAresta(aresta x)
{
    Modify(++size,x);
}

void heapMinAresta::insertVetorAresta(std::vector<std::vector<int>> &matriz,int indice,std::vector<bool> &naArvore)
{
    int n = matriz.size();
    aresta adcionada;
    for(int i =0;i<n;i++)
    {
        if(!naArvore[i])
        {
            adcionada.city[1] = indice;
            adcionada.city[2] = i;
            adcionada.distancia = matriz[indice][i];
            insertAresta(adcionada);
        }
        
    }

}

aresta heapMinAresta::extractMin()
{
    aresta min;
    min.distancia = vetorAresta[1].distancia;
    min.city[1] = vetorAresta[1].city[1];   
    min.city[2] = vetorAresta[1].city[2];
    //troca do ultimo com o primeiro
    Modify(1,vetorAresta[size]);
    size--;
    return min;
}

void TspSolver::makeMatrix(std::vector<std::vector<int>> &matriz,std::vector<int> &index,TspReader &tr)
{
    std::vector<City> vc;
    int n = tr.getNumCities();
    tr.copyCitiesVector(vc);
    index.resize(n);
    matriz.resize(n);
    for(int i = 0;i<n;i++)
    {
        matriz[vc[i].getId()-1].resize(n);
        index[vc[i].getId()-1] = vc[i].getId();
        for(int j = 0;j<n;j++)
            matriz[vc[i].getId()-1][vc[j].getId()-1] = vc[i].disti(vc[j]);
    }
}

void percorreArvore(std::vector<int> &caminho,no *noArvore,int *indexCaminho)
{
    noLista *aux;
    caminho[*indexCaminho] = noArvore->indiceCity;
    aux = noArvore->listaFilhos;
    (*indexCaminho)++;
    //percorre a lista de filhos por recursão
    while(aux != NULL)
    {
        percorreArvore(caminho,aux->atual,indexCaminho);
        aux = aux->prox;
    }
    //ao fim da recursão desaloca a memoria da arvore
    free(noArvore->listaFilhos);
    free(noArvore);
}

void TspSolver::prim(std::vector<std::vector<int>> &matriz,std::vector<int> &index,std::vector<int> &caminho)
{
    no *raiz,*noAux;
    noLista *noAuxLista;
    std::vector<bool> naArvore;
    std::vector<no*> posPointer;
    aresta aux;
    int n = matriz.size(),j,indice,indexCaminho = 0;
    naArvore.resize(n,false);
    heapMinAresta heap;
    //inicializa heap
    heap.setHeapMaxSize(n*n);
    naArvore[0] = true;
    heap.insertVetorAresta(matriz,0,naArvore);
    //seta raiz
    raiz = (no*)malloc(sizeof(no));
    raiz->indiceCity = 0;
    raiz->listaFilhos = NULL;
    //inicializa vetor que aponta para os nos das arvores 
    posPointer.resize(n,NULL);
    posPointer[0] = raiz;
    
    //criar arvore de custo minimo
    for(int i = 1;i<n;i++)
    {
        j = 0;
        //procura vertice a adcionar,caso esteja na arvore, sera ignorado
        while(naArvore[j])
        {
            aux = heap.extractMin();
            j = aux.city[2];
        }
        naArvore[j] = true;
        indice = aux.city[1];//de onde a aresta sai

        //procura a posição a se adcionar
        noAuxLista = posPointer[indice]->listaFilhos;
        if(posPointer[indice]->listaFilhos == NULL)
        {
            posPointer[indice]->listaFilhos = (noLista*)malloc(sizeof(noLista));
            noAuxLista = posPointer[indice]->listaFilhos;

            //adciona na arvore
            posPointer[indice]->listaFilhos->prox = NULL;
            posPointer[indice]->listaFilhos->atual = (no*)malloc(sizeof(no));
            posPointer[indice]->listaFilhos->atual->listaFilhos = NULL;
            posPointer[indice]->listaFilhos->atual->indiceCity = j;
            posPointer[j] = posPointer[indice]->listaFilhos->atual;
        }
        else
        {
            while(noAuxLista->prox!=NULL)
                noAuxLista = noAuxLista->prox;

            //adciona o no na arvore
            noAuxLista->prox = (noLista*)malloc(sizeof(noLista));
            noAuxLista = noAuxLista->prox;
            posPointer[j] = noAuxLista->atual;
            noAuxLista->atual = (no*)malloc(sizeof(no));
            noAuxLista->atual->listaFilhos = NULL;
            noAuxLista->atual->indiceCity = j;

        }

        //adciona arestas do vertice j no heap de minimo
        heap.insertVetorAresta(matriz,j,naArvore);        
    }

    //percorre caminho e adciona na variavel caminho
    percorreArvore(caminho,raiz,&indexCaminho);//desaloca a arvore no final
}

void TspSolver::solve(TspReader &tr,std::vector<int> &percourse) {

    //por matriz
    int n = tr.getNumCities();
    std::vector<int> caminho;
    caminho.resize(n);
    std::vector<std::vector<int>> matriz;
    std::vector<int> index;
    makeMatrix(matriz,index,tr);

    prim(matriz,index,caminho);

    // here it is filling the vector with  1,2,3,...n
    // you should fill it with a permutation that represents the TSP solution
    for (int i = 0; i < tr.getNumCities() ; i++)
        percourse.push_back(index[caminho[i]]);
        
        //percourse[3] = 100;
}//solve
