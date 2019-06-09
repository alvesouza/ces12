//Aluno:Pedro Alves de Souza Neto
//Entregue com 1 dia de atraso
//testato compilando no ubuntu,comando: g++ -std=c++11
/*o codeblocks nÃ£o estava funcionando era algum problema relacionado a maquina 64-bits(uma das razÃµes 
do atraso,nÃ£o a unica),nÃ£o descobri qual Ã© o compilador padrÃ£o do codeblocks entÃ£o usei o g++ para c++11*/
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string>
//Caso queira testar o tempo,informaÃ§Ãµes do tempo estÃ£o comentadas na 'int main()'
//#include<chrono>

/*Tive problemas com alocaÃ§Ã£o de memoria entÃ£o tentei usar o minimo possivel,esse Ã© o motivo da estrutura do grafo nÃ£o ter 
arestas,pois jÃ¡ sabemos que todo mundo vai para todo mundo*/
//A estrutura de cidades recebe apenas sua posiÃ§Ã£o e nÃ£o suas arestas o que daria um espaÃ§o na orden nÂ²
struct Cidade {
	float x, y;
};

//estrutura do grafo
struct grafo {
	int nvert;//numero de vertices
	Cidade *array;//armazena as cidades em seus respectivos 'indices-1'
};

//funÃ§Ã£o da distancia em float
float distancia(float x1, float y1, float x2, float y2)
{
	return sqrtf((x1 - x2)*(x1 - x2) +
		(y1 - y2)*(y1 - y2));
}
//conversor de float para inteiro com aproximaÃ§Ã£o
int nint(float x)
{
	return (int)(x + 0.5);
}

//cria o grafo
struct grafo* criarGrafo(int n)//'n' Ã© o numero de cidade
{

	grafo *gr = (grafo*)malloc(sizeof(grafo));
	gr->nvert = n;

	gr->array = (Cidade*)malloc(n * sizeof(Cidade));

	return gr;
}


//Ã‰ a estrutura do no do heap,onde 
struct HeapNo {
	int i;//i Ã© o indice da sua respectiva cidade
	int key;//Key Ã© o 'peso' das arestas
};

struct Heap {
	int n;
	int max;
	int *pos;
	HeapNo **vetor;
};

//Reduz 'Key' do heap escolhido,serÃ¡ chamado se achou uma menor distancia entre a cidade e 'T'
void decreaseKey(struct Heap* heap, int v, int key,int *pai)
{
	int i = heap->pos[v], j;
	bool continuaLoop = true;
	HeapNo* t;
	heap->vetor[i]->key = key;

	j = ((i - 1) >> 1);
	while (i>0 && continuaLoop)
	{
        //faz a condicional com os criterios para se determinar se sai do loop
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
            //Logo abaixo serve para saber como esta o heap

			//std::cout << "i: " << i << " j : " << j << std::endl;
			//for (int I = 0; I<heap->n; I++)
				//std::cout << (heap->vetor[I]->i+1) << "["<< heap->vetor[I]->key<<","<< (pai[heap->vetor[I]->i]+1)<<","<< I<<"]";
			//std::cout << std::endl;
			//std::cout << "heap->vetor[i]: " << (1+heap->vetor[i]->i) << " heap->vetor[j] : " << (heap->vetor[j]->i+1) << std::endl;

            //troca os nos do heap para ser ordenado
			heap->pos[heap->vetor[i]->i] = j;
			heap->pos[heap->vetor[j]->i] = i;
			t = heap->vetor[i];
			heap->vetor[i] = heap->vetor[j];
			heap->vetor[j] = t;

            //Logo abaixo serve para saber como ele ficou logo apos a troca de ordenaÃ§Ã£o

			/*std::cout << "Apos Mudanca"<< std::endl;
			std::cout << "heap->vetor[i]: " << (heap->vetor[i]->i+1) << " heap->vetor[j] : " << (heap->vetor[j]->i+1) << std::endl;
			for (int I = 0; I<heap->n; I++)
				std::cout << (heap->vetor[I]->i + 1) << "[" << heap->vetor[I]->key << 
				"," << (pai[heap->vetor[I]->i] + 1) << "," << I << "] - ";
			std::cout << std::endl;*/

			i = j;
			j = ((j - 1) >> 1);

		}
	}
}
//libera a memoria do grafo
void freeGrafo(grafo *gr)
{
	free(gr->array);
	gr->array = NULL;
	free(gr);
	gr = NULL;
}

//ordena o heap e gera o heap
void gerarHeap(Heap* h, int i,int *pai)
{
	int esq, dir;
	int menor = i;

	dir = (i << 1) + 2;//(2*i+2) em bitwise o que Ã© mais rapido
	esq = (i << 1) | 1;//(2*i+1) em bitwise o que Ã© mais rapido

    //condicionais para ver se troca com o heap filho da esquerda
	if (esq < h->n)
		if (h->vetor[esq]->key < h->vetor[menor]->key)
			menor = esq;
		else if (h->vetor[esq]->key == h->vetor[menor]->key)
			if (pai[h->vetor[esq]->i] < pai[h->vetor[menor]->i])
				menor = esq;
			else if (pai[h->vetor[esq]->i] == pai[h->vetor[menor]->i])
				if (h->vetor[esq]->i < h->vetor[menor]->i)
					menor = esq;
	//condicionais para ver se troca com o heap filho da direita
    if (dir < h->n)
		if (h->vetor[dir]->key < h->vetor[menor]->key)
			menor = dir;
		else if (h->vetor[dir]->key == h->vetor[menor]->key)
			if (pai[h->vetor[dir]->i] < pai[h->vetor[menor]->i])
				menor = dir;
			else if (pai[h->vetor[dir]->i] == pai[h->vetor[menor]->i])
				if (h->vetor[dir]->i < h->vetor[menor]->i)
					menor = dir;
    //se ocorreu a troca, os heapsNodes sÃ£o alterados
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
//verifica se heaps sÃ£o vazios
bool estaVazio(Heap* h) {
	return h->n == 0;
}

//extrai o menor do heap
HeapNo* extrairMenor(Heap* h,int *pai)
{
    //se estiver vazio nÃ£o retorna nada
	if (estaVazio(h))
	{
		return NULL;
	}
	HeapNo *raiz, *ultimo;
	raiz = h->vetor[0];
	ultimo = h->vetor[h->n - 1];
	h->vetor[0] = ultimo;
	h->pos[raiz->i] = h->n - 1;
	h->pos[ultimo->i] = 0;
	//std::cout << "Extraiu: " << (raiz->i+1) << std::endl;
	h->n--;
	//tire os comentarios para verificar como fica o heap logo apos a extraÃ§Ã£o
    /*for (int I = 0; I<h->n; I++)
		std::cout << (h->vetor[I]->i+1) << "[" << h->vetor[I]->key << "," << (pai[h->vetor[I]->i]+1) << "," << I << "] - ";*/
	//std::cout << std::endl;
	gerarHeap(h, 0,pai);
    //heap apos re-ordenar o heap
	/*for (int I = 0; I<h->n; I++)
		std::cout << (h->vetor[I]->i + 1) << "[" << h->vetor[I]->key << "," << (pai[h->vetor[I]->i] + 1) << "," << I << "] - ";
	std::cout << std::endl;*/
	
    return raiz;//raiz Ã© o node do menor
}
//serve para ordenar os filhos para ter o caminho desejado,que esta sendo feito em , 'passarPorArvorePai'
void mergeFilhos(grafo* gr, int pai, int *filhos, int i,int m, int f)
{
	int i1 = i, i2 = 0, i3 = m+1, *aux,dis1,dis3;
	bool entraI3;
	if (f == i)
		return;
	aux = (int*)malloc((f - i + 1) * sizeof(int));
	while (i1 <= m && i3 <= f)
	{
		entraI3 = false;
		dis1 = nint(distancia(gr->array[pai].x, gr->array[pai].y, gr->array[filhos[i1]].x, gr->array[filhos[i1]].y));
		dis3 = nint(distancia(gr->array[pai].x, gr->array[pai].y, gr->array[filhos[i3]].x, gr->array[filhos[i3]].y));
        //condicionais para ordenar o vetor dos filhos
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
    //pÃµe no vetor filhos
	while(i2>0)
		filhos[--i3] = aux[--i2];
	free(aux);
	aux = NULL;
}

//mergeSort do vetor dos filhos,visto na funÃ§Ã£o ' passarPorArvorePai'
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
//FunÃ§Ã£o que faz o percursso desejado
void passarPorArvorePai(grafo* gr, int *pai, int atual,int n ,int *ultimo, int *custo)
{
	int *filhos,index,dist,numFilhos,j = 0;
    //conta quantos filhos,o 'atual' possui
	for (int i = 1; i < n; i++)
		if (pai[i] == atual)
			j++;
	*ultimo = atual;//armazena o atual com o ultimo a passar
	numFilhos = j;
	if (j == 0)
		return;
	if(j == 1)
		filhos = (int*)malloc(2 * sizeof(int));
	else
		filhos = (int*)malloc(j * sizeof(int));
	for (int i = 1,j = 0; j < numFilhos; i++)
		if (pai[i] == atual)
			filhos[j++] = i;
    
    //Comentario Abaixo serve para saber os filhos de 'atual' antes da ordenaÃ§Ã£o

	//std::cout << "Filhos de '" << (atual + 1) << "'" << std::endl;
	//std::cout << "Antes do merge " << std::endl;
	/*for (int i = 0; i < numFilhos; i++)
		std::cout << (filhos[i] + 1)<<":" << nint(distancia(gr->array[atual].x, gr->array[atual].y, gr->array[filhos[i]].x, gr->array[filhos[i]].y))<< " - ";*/

	mergeSortFilhos(gr,atual,filhos,0,numFilhos-1);
	
    //Comentario Abaixo serve para saber os filhos de 'atual' antes da ordenaÃ§Ã£o

    //std::cout << "depois do merge " << std::endl;
	/*for (int i = 0; i < numFilhos; i++)
		std::cout << (filhos[i] + 1) << ":" << nint(distancia(gr->array[atual].x, gr->array[atual].y, gr->array[filhos[i]].x, gr->array[filhos[i]].y)) << " - ";*/
	
	/*for (int i = 0; i < numFilhos; i++)
		std::cout << (filhos[i]+1) << " - ";
	std::cout << std::endl;*/

    //passa para os filhos
	for (int i = 0; i < numFilhos; i++)
	{
		index = filhos[i];
		dist = nint(distancia(gr->array[*ultimo].x, gr->array[*ultimo].y, gr->array[index].x, gr->array[index].y));
		*custo += dist;//soma a distancia
		//std::cout << (*ultimo + 1) << "-" << (index+1) << " Distancia: " << dist << " Custo: " << *custo << std::endl;
		passarPorArvorePai(gr, pai, index, n, ultimo, custo);
		//std::cout << "Atual: " << atual << std::endl;
	}
	free(filhos);
	filhos = NULL;
}
//noArvore* 
int Prim(grafo *gr)
{
	int i, dest, j, NV = gr->nvert,dist;
	int *pai, *key;
	bool continuarLoop = true,fazerTroca = false;
	int ultimo,custo,arestaAtual,verticeAtual;
	if (NV == 1)
		return 0;
	pai = (int*)malloc(NV*sizeof(int));
	key = (int*)malloc(NV * sizeof(int));
	
	HeapNo* extraiHeapNo;
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	heap->n = 0;
	heap->pos = (int*)malloc(NV*sizeof(int));
	heap->max = NV;
	heap->vetor = (HeapNo**)malloc(NV* sizeof(HeapNo*));
	key[0] = 0;
	heap->vetor[0] = (HeapNo*)malloc(sizeof(HeapNo));
	//std::cout << "heap->vetor[0] = "<<heap->vetor[0]<<std::endl;
	heap->vetor[0]->i = 0;
	heap->vetor[0]->key = 0;
	heap->pos[0] = 0;
	pai[0] = -1;
	
	for (i = 1; i<NV; i++)
	{
		key[i] = 2147483645;
		pai[i] = -1;//sem pai/
		heap->vetor[i] = (HeapNo*)malloc(sizeof(HeapNo));
		heap->vetor[i]->i = i;
		heap->vetor[i]->key = key[i];
		heap->pos[i] = i;
	}
	
	heap->n = i;
	while (!estaVazio(heap))
	{
		extraiHeapNo = extrairMenor(heap,pai);
		
		arestaAtual = 0;
		verticeAtual = extraiHeapNo->i;
		dest = 0;
		continuarLoop = true;
		dest = 0;
		while (continuarLoop)
		{
			fazerTroca = false;
			dist = nint(distancia(gr->array[verticeAtual].x, gr->array[verticeAtual].y, gr->array[dest].x, gr->array[dest].y));
			//std::cout << "destino: " << (dest+1) << std::endl;

            //condicionais para saber se muda o valor do heap
			if ((heap->pos[dest] < heap->n) && (dist < key[dest] || (dist == key[dest] &&
				pai[dest] > verticeAtual)))
				if (heap->pos[dest] < heap->n)
					if (dist < key[dest])
						fazerTroca = true;
					else if (dist == key[dest])
						if (pai[dest] > verticeAtual)
							fazerTroca = true;
			if (fazerTroca) {
				key[dest] = dist;
                
                //Comentario abaixo serve para saber a aresta que foi alterada onde '(extraiHeapNo->i + 1)' Ã© o inicio e '(dest+1)' Ã© o vertice de destino

				/*std::cout << "Aresta: " << (extraiHeapNo->i + 1) << "-" << (dest + 1) << " Distancia: " << key[dest] << std::endl;*/
				pai[dest] = extraiHeapNo->i;
				decreaseKey(heap, dest, key[dest], pai);
				ultimo = dest;
			}
			dest++;
			if (verticeAtual == dest)
				dest++;
			if (dest >= NV)
				continuarLoop = false;
		}

	}
	ultimo = 0;
	custo = 0;
	passarPorArvorePai(gr, pai, 0, NV, &ultimo, &custo);//passa pela arvore de custo minimo
	dist = nint(distancia(gr->array[ultimo].x, gr->array[ultimo].y,
		gr->array[0].x, gr->array[0].y));//adciona o custo final que Ã© a distancia entre o ultimo vertice a passar e o vertice 1
	custo += dist;
	free(pai);
	pai = NULL;
	free(key);
	key = NULL;
	
	free(heap->vetor);
	heap->vetor = NULL;
	free(heap);
	heap = NULL;
	//std::cout << (ultimo + 1) << "-" << (1) << " Distancia: " << dist  <<" Custo: " << custo << std::endl;
	return custo;
}


//funÃ§Ã£o para se comeÃ§ar a resolver o problema
int solve(std::string ent)
{
	FILE *fp;
	int m, n,custo;//numero de vertices
	grafo *grafoCidades;
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
		grafoCidades->array[j];
	}

	fclose(fp);
	custo = Prim(grafoCidades);
	freeGrafo(grafoCidades);
	grafoCidades = NULL;
	return custo;
}
//feito para responder o na 'saida.txt'
void responder(int *respostas, int n)//n Ã© o numero de de ent's
{
	FILE *file;
	std::string saida;
	int i = 0;
	file = fopen("saida.txt", "w");
	while (i<n)
	{
		fprintf(file, "%d\n", respostas[i]);
		i++;
	}
	
	fclose(file);
	
}
//TSP gerencia as entradas 'txt' e saida
void TSP(int n)
{
	int i = 1;
	std::string ent = "ent";
	int *respostas;
	if(n==1)
		respostas = (int*)malloc(2 * sizeof(int));
	else
		respostas = (int*)malloc(n*sizeof(int));
	while (i <= n)
	{
		//std::cout << "Caso: " << i << std::endl;
		
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
	responder(respostas,n);
}


int main()
{	
	int n;
	std::cin >> n;
    //codigo serve para saber o tempo do codigo
	//auto start = std::chrono::high_resolution_clock::now();
	TSP(n);
	//auto end = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double> elapsed = end - start;
	//std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	//std::cin >> n;
	return 0;
}