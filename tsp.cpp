// LabExame.cpp: Define o ponto de entrada para a aplicação de console.
//
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS


#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string>
#include<chrono>

struct arestaListaNode {
	int destino;
	int distancia;
	struct arestaListaNode* prox;

};

struct CelVert {
	struct arestaListaNode* head;
};
struct Cidade {
	//int indice;//indice respectivo a cada cidade
	//caminho(struct) ponteiro pronto para receber um vetor
	bool passou;
	float x, y;
	CelVert list;
};


struct grafo {
	int nvert;
	Cidade *array;
};

struct noArvore {
	int vert,numFilhos;
	noArvore **filho;
};

float distancia(float x1, float y1, float x2, float y2)
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

	//std::cout << "Flag2:1 " << std::endl;
	struct arestaListaNode* no = (arestaListaNode*)malloc(sizeof(arestaListaNode));

	//std::cout << "Flag2:2 " << std::endl;
	no->destino = destino;
	no->distancia = dist;
	no->prox = NULL;
	return no;
}

struct grafo* criarGrafo(int n)
{

	std::cout << "Flag3:1 "  << std::endl;
	grafo *gr = (grafo*)malloc(sizeof(grafo));
	gr->nvert = n;

	gr->array = (Cidade*)malloc(n * sizeof(Cidade));

	std::cout << "Flag3:2 " << std::endl;
	for (int i = 0; i<n; i++)
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
	arestaListaNode* no = novaAresta(dest, nint(distancia(gr->array[i].x, gr->array[i].y, gr->array[dest].x, gr->array[dest].y)));
	no->prox = gr->array[i].list.head;
	gr->array[i].list.head = no;
}

struct HeapNo {
	int i;
	int key;
};

struct Heap {
	int n;
	int max;
	int *pos;
	HeapNo **vetor;
};

void decreaseKey(struct Heap* heap, int v, int key,int *pai)
{
	int i = heap->pos[v], j;
	bool continuaLoop = true;
	HeapNo* t;
	heap->vetor[i]->key = key;

	j = ((i - 1) >> 1);
	while (i>0 && continuaLoop)
	{
		continuaLoop = false;
		if (heap->vetor[i]->key < heap->vetor[j]->key)
			continuaLoop = true;
		else if (heap->vetor[i]->key == heap->vetor[j]->key)
			if (pai[heap->vetor[i]->i] < pai[heap->vetor[j]->i])
				continuaLoop = true;
			else if(pai[heap->vetor[i]->i] == pai[heap->vetor[j]->i])
				if(heap->vetor[i]->i < heap->vetor[j]->i)
					continuaLoop = true;
		if (continuaLoop == true)
		{
			/*std::cout << "i: " << i << " j : " << j << std::endl;
			for (int I = 0; I<heap->n; I++)
				std::cout << (heap->vetor[I]->i+1) << "["<< heap->vetor[I]->key<<","<< (pai[heap->vetor[I]->i]+1)<<","<< I<<"]";
			std::cout << std::endl;
			std::cout << "heap->vetor[i]: " << (1+heap->vetor[i]->i) << " heap->vetor[j] : " << (heap->vetor[j]->i+1) << std::endl;*/
			heap->pos[heap->vetor[i]->i] = j;
			heap->pos[heap->vetor[j]->i] = i;
			t = heap->vetor[i];
			heap->vetor[i] = heap->vetor[j];
			heap->vetor[j] = t;
			/*std::cout << "Apos Mudanca"<< std::endl;
			std::cout << "heap->vetor[i]: " << (heap->vetor[i]->i+1) << " heap->vetor[j] : " << (heap->vetor[j]->i+1) << std::endl;
			for (int I = 0; I<heap->n; I++)
				std::cout << (heap->vetor[I]->i + 1) << "[" << heap->vetor[I]->key << "," << (pai[heap->vetor[I]->i] + 1) << "," << I << "] - ";
			std::cout << std::endl;*/

			i = j;
			j = ((j - 1) >> 1);

		}
	}
}

HeapNo* novoHeapNo(int i, int key)
{

	std::cout << "Flag4:1 " << i << std::endl;
	HeapNo* no = (HeapNo*)malloc(sizeof(HeapNo));

	std::cout << "Flag4:2 " << i << std::endl;
	no->i = i;
	no->key = key;
	return no;
}

Heap* novoHeap(int maximo)
{

	std::cout << "Flag5:1 " << std::endl;
	Heap* h = (Heap*)malloc(sizeof(Heap));
	std::cout << "Flag5:2 " << std::endl;
	h->n = 0;
	h->pos = (int*)malloc(sizeof(int));
	std::cout << "Flag5:3 " << std::endl;
	h->max = maximo;
	h->vetor = (HeapNo**)malloc(maximo * sizeof(HeapNo*));
	std::cout << "Flag5:4 " << std::endl;
	return h;
}
void freeArestas(arestaListaNode* no)
{
	if (no == NULL)
		return;
	if (no->prox != NULL)
		freeArestas(no->prox);
	free(no);
}
void freeGrafo(grafo *gr)
{
	int n = gr->nvert;
	for (int i = 0; i<n; i++)
		freeArestas(gr->array[i].list.head);
}
void mergeArvore(grafo *gr,noArvore **filhos, int pai ,int i, int m, int f)
{
	int i1, i2, i3,dis1,dis2,I,J;
	noArvore **t;
	std::cout << "Flag6:1 " << std::endl;
	t = (noArvore**)malloc(f* sizeof(noArvore));
	std::cout << "Flag6:2 " << std::endl;
	i1 = i;
	i2 = i;
	i3 = m + 1;
	while (i2 <= m && i3 < f)
	{
		I = pai;
		J = filhos[i2]->vert-1;
		dis1 = nint(distancia(gr->array[I].x, gr->array[I].y, gr->array[J].x, gr->array[J].y));
		J = filhos[i3]->vert - 1;
		dis2 = nint(distancia(gr->array[I].x, gr->array[I].y, gr->array[J].x, gr->array[J].y));
		if ((dis2 > dis1) || (dis2 == dis1 && filhos[i2]->vert > filhos[i3]->vert))
			t[i1++] = filhos[i3++];
		else
			t[i1++] = filhos[i2++];
		while (i2 <= m)
			t[i1++] = filhos[i2++];
		while (i3 <= f)
			t[i1++] = filhos[i3++];
		for (int X = i; X <= f; X++)
			filhos[X] = t[X];
	}
	free(t);
}
noArvore* gerarArvore(grafo *gr, int *pai, int n)
{
	int dis1, dis2, trocaindex,*numFilhos,*cFilhos,b,p,r,m,f;
	noArvore **posicaoNo;
	std::cout << "Flag7:1 " << std::endl;
	posicaoNo = (noArvore**)malloc(n*sizeof(noArvore));
	std::cout << "Flag7:2 " << std::endl;
	numFilhos = (int*)malloc(n * sizeof(int));
	cFilhos = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		std::cout << "Flag7:3 " << std::endl;
		posicaoNo[i] = (noArvore*)malloc(sizeof(noArvore));
		std::cout << "Flag7:4 " << std::endl;
		posicaoNo[i]->filho = NULL;
		posicaoNo[i]->numFilhos = 0;
		posicaoNo[i]->vert = i + 1;
		numFilhos[i] = 0;
	}
	for (int i = 1; i < n; i++)
		numFilhos[pai[i]]++;
	for (int i = n-1; i >0; i--) {
		cFilhos[pai[i]] --;
		if (posicaoNo[pai[i]]->filho == NULL)
		{
			std::cout << "Flag7:5 " << std::endl;
			posicaoNo[pai[i]]->filho = (noArvore**)malloc(numFilhos[pai[i]]*sizeof(noArvore));
			std::cout << "Flag7:6 " << std::endl;
			cFilhos[pai[i]] = numFilhos[pai[i]] - 1;
			posicaoNo[pai[i]]->numFilhos = numFilhos[pai[i]];
		}
		posicaoNo[pai[i]]->filho[cFilhos[pai[i]]] = posicaoNo[i];
	}
	for (int j = 0, i = 0; j < n; j++)
	{
		if (numFilhos[j] > 1)
		{
			b = 1;
			f = numFilhos[j];
			while (b < f) {
				p = 0;
				while (p + b <= f) {
					r = p - 1 + 2 * b;
					if (f < r)
						r = f;
					m = p + b - 1;
					mergeArvore(gr,posicaoNo[j]->filho,j,p,m,r);
					
					p += 2 * b;
				}
				b *= 2;

			}
		}
	}
	return posicaoNo[0];
}

void percorreArvore(grafo *gr, noArvore *raiz, int *ultimo, int *custo)
{
	int i, j,n;
	i = raiz->vert-1;
	*ultimo = i;
	n = raiz->numFilhos;
	for (int J = 0; J < n; J++)
	{
		j = raiz->filho[J]->vert - 1;
		*custo += nint(distancia(gr->array[i].x, gr->array[i].y, gr->array[j].x, gr->array[j].y));
		//std::cout << (*ultimo + 1) << "-" << (j + 1) << " : " << *custo << std::endl;
		percorreArvore(gr, raiz->filho[J], ultimo, custo);
	}
}
void freeArvore(noArvore* raiz)
{
	int i, j, n;
	i = raiz->vert - 1;
	n = raiz->numFilhos;
	for (int J = 0; J < n; J++)
	{
		j = raiz->filho[J]->vert - 1;
		freeArvore(raiz->filho[J]);
	}
	free(raiz->filho);
	free(raiz);
}
void gerarHeap(Heap* h, int i,int *pai)
{
	int esq, dir;
	int menor = i;

	dir = (i << 1) + 2;
	esq = (i << 1) | 1;

	if (esq < h->n)
		if (h->vetor[esq]->key < h->vetor[menor]->key)
			menor = esq;
		else if (h->vetor[esq]->key == h->vetor[menor]->key)
			if (pai[h->vetor[esq]->i] < pai[h->vetor[menor]->i])
				menor = esq;
			else if (pai[h->vetor[esq]->i] == pai[h->vetor[menor]->i])
				if (h->vetor[esq]->i < h->vetor[menor]->i)
					menor = esq;
	if (dir < h->n)
		if (h->vetor[dir]->key < h->vetor[menor]->key)
			menor = dir;
		else if (h->vetor[dir]->key == h->vetor[menor]->key)
			if (pai[h->vetor[dir]->i] < pai[h->vetor[menor]->i])
				menor = dir;
			else if (pai[h->vetor[dir]->i] == pai[h->vetor[menor]->i])
				if (h->vetor[dir]->i < h->vetor[menor]->i)
					menor = dir;

	if (i != menor)
	{
		HeapNo* menorNo = h->vetor[menor];
		HeapNo* iNo = h->vetor[i];
		HeapNo *t;

		h->pos[menorNo->i] = i;
		h->pos[iNo->i] = menor;

		t = h->vetor[menor];
		h->vetor[menor] = h->vetor[i];
		h->vetor[i] = t;

		gerarHeap(h, menor,pai);
	}

}

bool estaVazio(Heap* h) {
	return h->n == 0;
}

HeapNo* extrairMenor(Heap* h,int *pai)
{
	if (estaVazio(h))
		return NULL;

	HeapNo *raiz, *ultimo;
	raiz = h->vetor[0];
	ultimo = h->vetor[h->n - 1];
	h->vetor[0] = ultimo;

	h->pos[raiz->i] = h->n - 1;
	h->pos[ultimo->i] = 0;
	//std::cout << "Extraiu: " << (raiz->i+1) << std::endl;
	h->n--;
	/*for (int I = 0; I<h->n; I++)
		std::cout << (h->vetor[I]->i+1) << "[" << h->vetor[I]->key << "," << (pai[h->vetor[I]->i]+1) << "," << I << "] - ";
	std::cout << std::endl;*/
	gerarHeap(h, 0,pai);
	/*for (int I = 0; I<h->n; I++)
		std::cout << (h->vetor[I]->i + 1) << "[" << h->vetor[I]->key << "," << (pai[h->vetor[I]->i] + 1) << "," << I << "] - ";
	std::cout << std::endl;*/
	return raiz;
}
void mergeFilhos(grafo* gr, int pai, int *filhos, int i,int m, int f)
{
	int i1 = i, i2 = 0, i3 = m+1, *aux,dis1,dis3;
	bool entraI3;
	aux = (int*)malloc((f - i + 1) * sizeof(int));
	while (i1 <= m && i3 <= f)
	{
		entraI3 = false;
		dis1 = nint(distancia(gr->array[pai].x, gr->array[pai].y, gr->array[filhos[i1]].x, gr->array[filhos[i1]].y));
		dis3 = nint(distancia(gr->array[pai].x, gr->array[pai].y, gr->array[filhos[i3]].x, gr->array[filhos[i3]].y));
		if (dis1 > dis3)
			entraI3 = true;
		else if (dis1 == dis3)
			if (filhos[i1] > filhos[i3])
				entraI3 = true;
		if (entraI3)
		{
			aux[i2++] = filhos[i3++];
		}
		else
			aux[i2++] = filhos[i1++];
	}
	while(i1 <= m)
		aux[i2++] = filhos[i1++];
	while(i3 <= f)
		aux[i2++] = filhos[i3++];
	while(i2>0)
		filhos[--i3] = aux[--i2];
	free(aux);
}
void mergeSortFilhos(grafo* gr, int pai, int *filhos, int i, int f)
{
	int m;
	if (i < f)
	{
		m = ((i + f) >> 1);
		mergeSortFilhos(gr, pai, filhos, i, m);
		mergeSortFilhos(gr, pai, filhos, m+1, f);
		mergeFilhos(gr, pai, filhos, i, m, f);
	}
}
void passarPorArvorePai(grafo* gr, int *pai, int atual,int n ,int *ultimo, int *custo)
{
	int *filhos, j = 0,*aux,dis1,dis2,index,index2,dist,numFilhos;
	for (int i = 1; i < n; i++)
		if (pai[i] == atual)
			j++;
	numFilhos = j;
	std::cout << "Flag8:1 " << std::endl;
	filhos = (int*)malloc(j * sizeof(int));
	std::cout << "Flag8:2 " << std::endl;
	

	for (int i = 1,j = 0; j < numFilhos; i++)
		if (pai[i] == atual)
			filhos[j++] = i;
	/*std::cout << "Filhos de '" << (atual + 1) << "'" << std::endl;
	std::cout << "Antes do merge " << std::endl;
	for (int i = 0; i < numFilhos; i++)
		std::cout << (filhos[i] + 1)<<":" << nint(distancia(gr->array[atual].x, gr->array[atual].y, gr->array[filhos[i]].x, gr->array[filhos[i]].y))<< " - ";*/

	mergeSortFilhos(gr,atual,filhos,0,numFilhos-1);
	/*std::cout << "depois do merge " << std::endl;
	for (int i = 0; i < numFilhos; i++)
		std::cout << (filhos[i] + 1) << ":" << nint(distancia(gr->array[atual].x, gr->array[atual].y, gr->array[filhos[i]].x, gr->array[filhos[i]].y)) << " - ";
	
	for (int i = 0; i < numFilhos; i++)
		std::cout << (filhos[i]+1) << " - ";
	std::cout << std::endl;*/
	*ultimo = atual;
	for (int i = 0; i < numFilhos; i++)
	{
		index = filhos[i];
		dist = nint(distancia(gr->array[*ultimo].x, gr->array[*ultimo].y, gr->array[index].x, gr->array[index].y));
		*custo += dist;
		//std::cout << (*ultimo + 1) << "-" << (index+1) << " Distancia: " << dist << " Custo: " << *custo << std::endl;
		passarPorArvorePai(gr, pai, index, n, ultimo, custo);
	}
	free(filhos);

}
//prim não esta completo
//noArvore* 
int Prim(grafo *gr)
{
	int i, dest, j, primeiro, NV = gr->nvert,dist;
	int *pai, *key;
	bool sairLoop = false;
	int ultimo,custo;
	noArvore *raiz;
	pai = new int[NV];
	key = new int[NV];

	HeapNo* extraiHeapNo;
	arestaListaNode* arestaAtual;
	Heap* heap = novoHeap(NV);
	for (i = 0; i<NV; i++)
	{
		key[i] = 2147483645;
		pai[i] = -1;//sem pai
		heap->vetor[i] = novoHeapNo(i, key[i]);
		heap->pos[i] = i;
	}
	key[0] = 0;
	heap->vetor[0] = novoHeapNo(0, key[0]);
	heap->pos[0] = 0;

	heap->n = i;

	while (!estaVazio(heap))
	{
		extraiHeapNo = extrairMenor(heap,pai);
		arestaAtual = gr->array[extraiHeapNo->i].list.head;
		ultimo = -1;
		while (arestaAtual != NULL)
		{
			dest = arestaAtual->destino;
			//std::cout << "destino: " << (dest+1) << std::endl;
			if ((heap->pos[dest]<heap->n) && (arestaAtual->distancia < key[dest]||(arestaAtual->distancia == key[dest]&&
				pai[dest] > extraiHeapNo->i)))
			if(heap->pos[dest]<heap->n)
				if (arestaAtual->distancia < key[dest])
				{
					key[dest] = arestaAtual->distancia;
					/*std::cout << "Aresta: " << (extraiHeapNo->i + 1) << "-" << (dest + 1) << " Distancia: " << key[dest] << std::endl;*/
					pai[dest] = extraiHeapNo->i;
					decreaseKey(heap, dest, key[dest],pai);
					ultimo = dest;
				}
				else if(arestaAtual->distancia == key[dest])
					if (pai[dest] > extraiHeapNo->i)
					{
						/*std::cout << "Aresta: " << (extraiHeapNo->i + 1) << "-" << (dest + 1) << " Distancia: " << key[dest] << std::endl;*/
						pai[dest] = extraiHeapNo->i;
						decreaseKey(heap, dest, key[dest],pai);
						ultimo = dest;
					}
			arestaAtual = arestaAtual->prox;
		}

	}
	ultimo = 0;
	custo = 0;
	passarPorArvorePai(gr, pai, 0, NV, &ultimo, &custo);
	dist = nint(distancia(gr->array[ultimo].x, gr->array[ultimo].y,
		gr->array[0].x, gr->array[0].y));
	custo += dist;
	free(pai);
	for (int i = 0; i < NV; i++)
		free(heap->vetor[i]);
	free(heap->pos);
	free(heap);
	//std::cout << (ultimo + 1) << "-" << (1) << " Distancia: " << dist  <<" Custo: " << custo << std::endl;
	return custo;
}



int solve(std::string ent)
{
	FILE *fp;
	int m, n,custo;//numero de vertices
	grafo *grafoCidades;
	noArvore *raiz;
	int ultimoAPassar;
	fp = fopen(ent.c_str(), "r");
	fscanf(fp, "%d", &m);
	if (m == 0)
	{
		return 0;
	}
	grafoCidades = criarGrafo(m);

	n = m;
	for (int i = 0,j; n>0; n--)
	{

		fscanf(fp, "%d", &j);
		j--;
		fscanf(fp, "%f %f", &grafoCidades->array[j].x, &grafoCidades->array[j].y);
		grafoCidades->array[j].passou = false;
	}
	std::cout << "Flag10:1 " << std::endl;
	for (int X = 1; X <= m; X++)
		for (int Y = m; Y> 0; Y--)
		{
			if (X != Y)
				adcionarArestaGrafo(grafoCidades, X, Y);
		}
	std::cout << "Flag10:2 " << std::endl;
	fclose(fp);
	custo = Prim(grafoCidades);
	freeGrafo(grafoCidades);
	return custo;
}
void responder(int *respostas, int n)
{
	FILE *file;
	std::string saida;
	int i = 0;
	file = fopen("saida.txt", "w");
	n--;
	while (i<n)
	{
		fprintf(file, "%d\n", respostas[i]);
		i++;
	}

	fprintf(file, "%d", respostas[i]);

	fclose(file);

}
void TSP(int n)
{
	int i = 1;
	std::string ent = "ent";
	int *respostas;
	respostas = new int[n];
	while (i <= n)
	{
		std::cout << "Caso: " << i << std::endl;
		std::cout << "Flag1: " << i << std::endl;
		if (i < 10)
		{
			ent = "ent0" + std::to_string(i) + ".txt";
		}
		else {
			ent = "ent" + std::to_string(i) + ".txt";
		}
		respostas[i-1] = solve(ent);
		i++;

	}
	responder(respostas, n);
}


int main()
{	
	int n;
	float x;
	std::cin >> n;
	auto start = std::chrono::high_resolution_clock::now();
	TSP(n);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	std::cin >> n;
	return 0;
}
