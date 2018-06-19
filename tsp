//ultima linha 40(solve)
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string>

struct arestaListaNode{
    int destino;
    int distancia;
    struct arestaListaNode* prox;

};

struct CelVert {
    struct arestaListaNode* head;
};
struct Cidade{
    //int indice;//indice respectivo a cada cidade
    //caminho(struct) ponteiro pronto para receber um vetor
    bool passou;
    float x,y;
    CelVert list;
};


struct grafo {
    int nvert;
    Cidade *array;
};

struct noArvore{
    int vert;
    noArvore *esq,*dir;
};

float distancia(float x1,float y1,float x2,float y2)
{
    return sqrtf((x1 - x2)*(x1 - x2) +
        (y1 - y2)*(y1 - y2));
}

int nint(float x)
{
    return (int)(x + 0.5);
}

struct arestaListaNode* novaAresta(int destino, int dist)
{
    struct arestaListaNode* no = (arestaListaNode*)malloc(sizeof(arestaListaNode));
    no->destino = destino;
    no->distancia = dist;
    no->prox = NULL;
    return no;
}

struct grafo* criarGrafo(int n)
{
    grafo *gr = (grafo*)malloc(sizeof(grafo));
    gr->nvert = n;

    gr->array = (Cidade*)malloc(n*sizeof(Cidade));

    for(int i = 0; i<n; i++)
    {
        gr->array[i].list.head = NULL;
        gr->array[i].passou = false;
    }

    return gr;
}

void adcionarArestaGrafo(grafo* gr, int i, int dest)
{
    i--;
    dest--;
    arestaListaNode* no = novaAresta(dest, nint(distancia(gr->array[i].x,gr->array[i].y,gr->array[dest].x,gr->array[dest].y)));
    no->prox = gr->array[i].list.head;
    gr->array[i].list.head = no;
}

struct HeapNo{
    int i;
    int key;
};

struct Heap{
    int n;
    int max;
    int *pos;
    HeapNo **vetor;
};

void decreaseKey(struct Heap* heap, int v, int key)
{
    int i = heap->pos[v],j;

    HeapNo* t;
    heap->vetor[i]->key = key;
 
    j = ((i - 1) >>1);
    while (i>0 && heap->vetor[i]->key < heap->vetor[j]->key)
    {
        
        heap->pos[heap->vetor[i]->i] = j;
        heap->pos[heap->vetor[j]->i] = i;
        t = heap->vetor[i];
        heap->vetor[i] = heap->vetor[j];
        heap->vetor[j] = t;
        
        i = j;
        j = ((j - 1) >>1);
    }
}

HeapNo* novoHeapNo(int i,int key)
{
    HeapNo* no = (HeapNo*)malloc(sizeof(HeapNo));
    no->i = i;
    no->key = key;
    return no;
}

Heap* novoHeap(int maximo)
{
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->n = 0;
    h->pos = (int*)malloc(sizeof(int));
    h->max = maximo;
    h->vetor = (HeapNo**)malloc(maximo*sizeof(HeapNo*));
    return h;
}
void freeArestas(arestaListaNode* no)
{
    if(no->prox != NULL)
        freeArestas(no);
    free(no);
}
void freeGrafo(grafo *gr)
{
    int n = gr->nvert;
    for(int i = 0;i<n;i++)
        freeArestas(gr->array[i].list.head);
}

noArvore* gerarArvore(grafo *gr,int *pai, int n)
{
    int dis1,dis2,j,trocaindex;
    noArvore *posicaoNo[n],*t;
    for(int i = 0;i<n;i++)
    {
        posicaoNo[i] = NULL;
    }
    posicaoNo[0] = (noArvore*)malloc(sizeof(noArvore));
    posicaoNo[0]->esq = NULL;
    posicaoNo[0]->dir = NULL;
    posicaoNo[0]->vert = 1;
    for(int i = 1;i<n;i++)
    {
        if(posicaoNo[i]== NULL)
            posicaoNo[i] = (noArvore*)malloc(sizeof(noArvore));
            posicaoNo[i]->esq = NULL;
            posicaoNo[i]->dir = NULL;
            posicaoNo[i]->vert = i+1;
        if(posicaoNo[pai[i]]== NULL)
            posicaoNo[pai[i]] = (noArvore*)malloc(sizeof(noArvore));
            posicaoNo[pai[i]]->esq = NULL;
            posicaoNo[pai[i]]->dir = NULL;
            posicaoNo[pai[i]]->vert = pai[i]+1;
        if(posicaoNo[pai[i]]->esq == NULL)
            posicaoNo[pai[i]]->esq = posicaoNo[i];
        else{
            j = posicaoNo[pai[i]]->esq->vert-1;
            dis1 = nint(distancia(gr->array[i].x,gr->array[i].y,gr->array[pai[i]].x,gr->array[pai[i]].y));
            dis2 = nint(distancia(gr->array[j].x,gr->array[j].y,gr->array[pai[i]].x,gr->array[pai[i]].y));
            t = posicaoNo[i];
            if(dis2>dis1||(dis1==dis2&&i < j))
            {
                t = posicaoNo[pai[i]]->esq;
                posicaoNo[pai[i]]->esq = posicaoNo[i];
            }
            posicaoNo[pai[i]]->dir = t;

        }
    }
    return posicaoNo[0];
}

void percorreArvore(grafo *gr,noArvore *raiz,int *ultimo,int *custo)
{
    int i,j;
    i = raiz->vert;
    *ultimo = i;
    if(raiz->esq != NULL)
    {
        j = raiz->esq->vert-1;
        *custo += nint(distancia(gr->array[i].x,gr->array[i].y,gr->array[j].x,gr->array[j].y));
        percorreArvore(gr,raiz->esq,ultimo,custo);
    }
    if(raiz->dir != NULL)
    {
        j = raiz->dir->vert-1;
        *custo += nint(distancia(gr->array[*ultimo].x,gr->array[*ultimo].y,gr->array[j].x,gr->array[j].y));
        percorreArvore(gr,raiz->dir,ultimo,custo);
    }


}
void freeArvore(noArvore* raiz)
{
    if(raiz->esq !=NULL)
    {
        freeArvore(raiz->esq);
        raiz->esq = NULL;
    }
    if(raiz->dir !=NULL)
    {
        freeArvore(raiz->dir);
        raiz->dir = NULL;
    }
    free(raiz);
}
void gerarHeap(Heap* h, int i)
{
    int esq,dir;
    int menor = i;

    dir = (i<<1) + 2;
    esq = (i<<1)|1;

    if(esq < h->n && h->vetor[esq]->key < h->vetor[menor]->key)
        menor = esq;
    if(dir < h->n && h->vetor[dir]->key < h->vetor[menor]->key)
        menor = dir;
    
    if(i!= menor)
    {
        HeapNo* menorNo = h->vetor[menor];
        HeapNo* iNo = h->vetor[i];
        HeapNo *t;

        h->pos[menorNo->i] = i;
        h->pos[iNo->i] = menor;

        t = h->vetor[menor];
        h->vetor[menor] = h->vetor[i];
        h->vetor[i] = t;

        gerarHeap(h, menor);
    }

}

bool estaVazio(Heap* h){
    return h->max == 0;
}

HeapNo* extrairMenor(Heap* h)
{
    if(estaVazio(h))
        return NULL;

    HeapNo *raiz,*ultimo;
    raiz = h->vetor[0];
    ultimo = h->vetor[h->n-1];
    h->vetor[0] = ultimo;

    h->pos[raiz->i] = h->n - 1;
    h->pos[ultimo->i] = 0;

    h->n--;
    gerarHeap(h, 0);

    return raiz;
}
//prim não esta completo
noArvore* Prim(grafo *gr)
{
    int i,dest,j,primeiro,NV = gr->nvert;
    int pai[NV],key[NV];
    bool sairLoop = false;
    noArvore *raiz;

    HeapNo* extraiHeapNo;
    arestaListaNode* arestaAtual;

    Heap* heap = novoHeap(NV);
    for(i=0;i<NV;i++)
    {
        key[i] = INT64_MAX;
        pai[i] = -1;//sem pai
        heap->vetor[i] = novoHeapNo(i,key[i]);
        heap->pos[i] = i;
    }

    key[0] = 0;
    heap->vetor[0] = novoHeapNo(0,key[0]);
    heap->pos[0] = 0;

    heap->n = i;

    while(!estaVazio(heap))
    {
        extraiHeapNo = extrairMenor(heap);

        arestaAtual = gr->array[extraiHeapNo->i].list.head;

        while(arestaAtual != NULL)
        {
            dest = arestaAtual->destino;
            if((heap->pos[dest]<heap->n)&&arestaAtual->distancia < key[dest])
            {
                key[dest] = arestaAtual->distancia;
                pai[dest] = extraiHeapNo->i;
                decreaseKey(heap, dest, key[dest]);
            }
            arestaAtual = arestaAtual->prox;
        }
        
    }
    raiz = gerarArvore(gr,pai,NV);

    return raiz;
}



int solve(std::string ent)
{
    FILE *fp;
    int m,n;//numero de vertices
    grafo *grafoCidades;
    Cidade *cidadeArray;
    noArvore *raiz;
    int custo,ultimoAPassar;
    fp = fopen(ent.c_str(),"r");
    fscanf(fp,"%d",&m);

    grafoCidades = criarGrafo(m);
    
    n = m;
    for(int i = 0;n>0;n--)
    {
        
        fscanf(fp,"%d",&i);
        i--;
        fscanf(fp,"%f %f",&grafoCidades->array[i].x,&grafoCidades->array[i].y); 
        grafoCidades->array[i].passou = false;   
    }

    for(int X = 1; X<=m;X++)
        for(int Y = m; Y> 0; Y--)
        {
            if(X!=Y)
                adcionarArestaGrafo(grafoCidades, X, Y);
        }
    
    fclose(fp);

    raiz = Prim(grafoCidades);
    custo = 0;
    percorreArvore(grafoCidades,raiz,&ultimoAPassar,&custo);
    custo += nint(distancia(grafoCidades->array[ultimoAPassar].x,grafoCidades->array[ultimoAPassar].y,
        grafoCidades->array[0].x,grafoCidades->array[0].y));
    freeGrafo(grafoCidades);
    freeArvore(raiz);
    return custo;
}
void responder(int *respostas,int n)
{
    FILE *file;
    std::string saida;
    int i = 0;
    file = fopen("saida.txt","w");
    n--;
    while(i<n)
    {  
        saida = std::to_string(respostas[i]) + "\n";
        fprintf(file,saida.c_str);
        i++;
    }
    
    saida = std::to_string(respostas[i]);
    fprintf(file,saida.c_str);

    fclose(file);

}
void TSP(int n)
{
    int i = 1;
    std::string ent = "ent";
    int *respostas;
    respostas = new int[n];
    while(i <= n)
    {
        if(i < 10)
        {
            ent = "ent0" + std::to_string(i) + ".txt";
        }
        else{
            ent = "ent" + std::to_string(i) + ".txt";
        }
        respostas[i] = solve(ent);
        i++;
        
    }
    responder(respostas,n);
}


int main()
{
    int n;
    float x;

    std::cin >> n;
    TSP(n);

    return 0;
}
