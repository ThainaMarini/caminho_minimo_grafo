#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<limits.h>
#include"estruturas.h"

void exibeGrafo(int **mat,long int n){
//    int i,j;
//    for(i=0;i<n;i++){
//        for(j=0;j<n;j++){
//          printf("%4d ",mat[i][j]);
//       }
//        printf("\n");
//
//   }
}

int min(int x,int y){
	if(x < y){
		return x;
	}else{
		return y;
	}
}
void BFS(int **mat, long int n, int vertice, int op){
	// Crescente = 0
	// Decrescente = 1
	int i,j,*alcancado;
	alcancado = malloc(n*sizeof(int));	// Vetor auxiliar para marcar os vertices alcancados
	TipoFila fila;
	FFVazia(&fila);
	TipoItem item;
	// Zera vetor
	for(i=0;i<n;i++){
		alcancado[i] = 0;	// Marca todos os vertices como 'nao alcancados'
	}
	// Marca o vertice de origem como alcancado
	alcancado[vertice] = 1;
	item.numero = vertice;
	// Enfileira vertice de origem
	Enfileira(item,&fila);
	printf("\nOrdem de visitacao BFS: \n%d, ",vertice+1);
	while(!Vazia(fila)){	
		i = fila.Frente->Prox->Item.numero; // vertice da frente da fila
		item.numero = i;
		Desenfileira(&fila,&item);
		if(op==1){	// Ordem crescente
			for(j=0;j<n;j++){	
				if(mat[i][j] != 0 && alcancado[j] != 1){	
					alcancado[j] = 1;
					item.numero = j;
					Enfileira(item,&fila); 
					printf("%d, ",j+1);
				}
			}	
		}else{	// Decrescente
			for(j=n-1;j>=0;j--){	
				if(mat[i][j] != 0 && alcancado[j] != 1){
					alcancado[j] = 1;
					item.numero = j;
					Enfileira(item,&fila); 
					printf("%d, ",j+1);
				}
			}	
		}
	}	
	free(alcancado);
}

void DFS(int **mat, long int n, int vG ,int op){ 
	// Crescente = 0
	// Decrescente = 1
	int i,j,*alcancado;
	alcancado = malloc(n*sizeof(int));	// Vetor auxiliar para marcar os vertices alcancados
	TipoPilha pilha;
	FPVazia(&pilha);
	TipoItem item;

	// Zera vetor
	for(i=0;i<n;i++){
		alcancado[i] = 0;	// Marca todos como 'nao alcancados'
	}
	// Marca o vertice de origem como alcancado
	alcancado[vG] = 1;
	item.numero = vG;
	// Enfileira vertice de origem
	Empilha(item,&pilha);
	printf("\nOrdem de visitacao DFS: \n%d, ",vG+1);
	while(!PVazia(pilha)){
		i = pilha.Topo->Prox->Item.numero;	// Vertice do topo da pilha
		printf("i=%d\n",i);
		if(op==1){	// Ordem crescente
			// encontrar o prox vertice de menor id que tem ligacao					
			for(j=0; j<n; j++){
				if(alcancado[j] == 0 && mat[i][j] != 0){ // se não alcançou e existe aresta entre i e j
					alcancado[j] = 1;
					item.numero = j;
					Empilha(item,&pilha);
					printf("%d, ",j+1);
					break;
				}
			}
			if(j == n){	// descobrindo se o loop anterior parou por i ser isolado ou não ter alguem mais pra visitar
				item.numero=j;
				Desempilha(&pilha, &item);
			}									
		}else{ // Decrescente
			// encontrar o prox vertice de maior id que tem ligacao
			for(j=n-1; j>=0; j--){
				if(alcancado[j] == 0 && mat[i][j] != 0){ // se não alcançou e existe aresta entre i e j
					alcancado[j] = 1;
					item.numero = j;
					Empilha(item,&pilha);
					printf("%d, ",j+1);
					break;
				}
			}
			if(j == -1){	// descobrindo se o loop anterior parou por i ser isolado ou não ter alguem mais pra visitar
				item.numero=j;
				Desempilha(&pilha, &item);
			}	
		}
	}	
	free(alcancado);
}

int minimiza(int *C, int *D, long int n){
	int i,menor=D[0],p=C[0];
	for(i=1;i<n;i++){
		if(D[i] < menor && C[i] < 1001){	// Procura o menor elemento de D existente em C
			menor = D[i];
			p = C[i];
		}
	}
	return C[p];
}

void Dijkstra(int **mat,long int n,int vG){
	int i,j,v,w,k,*D,*C;
	D = malloc(n*sizeof(int));	// Caminho minimo
	C = malloc(n*sizeof(int)); // Conjunto de controle
	
	for(i=0;i<n;i++){  // C = V 
		C[i] = i;  // Define os valores de controle de C	
	}
	// C = C - {vG}
	C[vG] = 1001;	// Exclui o vertice de origem do conjunto de controle
	
	for(j=0;j<n;j++){
		if(mat[vG][j] == 0){
			D[j] = 1001;		// Atribui infinito nas ligacoes diretas nao existentes
		}else{
			D[j] = mat[vG][j]; // Ligacoes diretas de vG para todos os vertices
		}
	}
	
	D[vG] = 1001; // Caminho minimo de vG de para vG = infinito

	for(k=0;k<n-2;k++){ // Repita n-2 vezes
		v = minimiza(C,D,n); // Elemento de C que minimiza D[v]
		if(v >= n){
			break;
		}
		C[v] = 1001;			// C = C - {v} 
		for(w=0;w<n;w++){		// Para cada elemento W 
			if(C[w] < 1001 && mat[v][w] != 0){   // Pertencente a C
				D[w]  = min(D[w],D[v]+mat[v][w]);	
			}
		}	
	}	
//	for(i=0;i<n;i++){
//		if(D[i] >= 1001){
//			printf("INF  ");
//		}else{
//			printf("%d  ",D[i]);
//		}	
//	}
//	printf("\n");
	free(D);
	free(C);	
}

void BellmanFord(int **mat,long int N, int vG){
	int *D, *C, i,k,a,j,w, v, cont = 0;
	D = malloc(N*sizeof(int));	// Caminho minimo
	C = malloc(N*sizeof(int)); // Conjunto de controle
	for (i = 0; i < N; i++){
		C[i] = 0;
	}	
	for (k = 0; k < N; k++) 
		for (j = 0; j < N; j++)
			if (mat[k][j] != 0){
				i = v = k;
				C[v] = 1;
				k = N;
				j = N;
			}

	for (j = 0; j < N; j++)
		D[j] = 1001;
	D[vG] = 0;
	for (j = 0; j < N - 1 ; j++){
		for (w = 0; w < N; w++){
			for(v = 0; v < N; v++)
				if (mat[v][w] != 0){
					D[w] = min(D[w],D[v] + mat[v][w]);	
				}
		}
		for (i = 0; i < N; i++)
			if (C[i] != 1)
				for (j = 0; j < N; j++)
					if (mat[i][j] != 0){
						v = i;
						C[v] = 1;
						i = N;
						j = N;
					}
		}
	}


void FloydWarshall(int **mat,long int n){
	int i,j,k;
	int **D;
    D = (int**)malloc(sizeof(int*)*n);	// Matriz resultante
    for (i=0;i<n;i++){
        D[i] = (int*)malloc(sizeof(int)*n);  
	}
	for (i = 0; i < n; i++)
    	for (j = 0; j < n; j++)
      		D[i][j] = mat[i][j];
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(mat[k][j] != 0){
					D[i][j] = min(D[i][j], D[i][k]+D[k][j]);
				}	
			}
		}	
	}
//	for(i=0;i<n;i++){
//		for(j=0;j<n;j++){
//			if(D[i][j]>9999999)
//				printf("%s","INF");
//			else
//				printf("%4d  ",D[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
	free(D);
}

// Verifica se uma nova aresta ja existe, se nao existir salva a posicao
bool verifAresta(int x,int y, int **grafo){
	// Nao pode sortear loops nem arestas paralelas
	// Nao pode sortear 1 2 e depois 2 1
	// Elimina loops
	if(x == y || grafo[x][y] != 0 || grafo[y][x] != 0){
		return true;
	}else{
		return false;
	}	
}

void geraGrafo(int **mat, float d, long int qtdV, int qtdA, int sn){
    int i,j,x,y,peso,cont=0;
	bool igual;

    // Inserção das arestas
    for(i=0;i<qtdA;i++){
    	igual = true;
        // Sorteia os vertices que receberao uma aresta
        while(igual == true){
        	x = rand() % qtdV;
        	y = rand() % qtdV;
        	igual = verifAresta(x,y,mat);	
		}
		
        // Sorteia o peso da aresta
        peso = rand() % 999 + 1;
        //printf("%d %d = %d \n",x,y,peso);
        mat[x][y] = peso;
        // Se o grafo for nao direcionado, insere a aresta inversa
        if(sn == 2){
            mat[y][x] = mat[x][y];
        }    
    }
}
void zeraGrafo(int **mat,long int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            mat[i][j] = 0;
        }
    }
}

void liberaMatriz(int **mat, long int n){
    int i;
    for(i=0;i<n;i++){
        free(mat[i]);
    }
    free(mat);
}

void escreveGrafo(int **mat,long int n,int c){
	int i=0,j;
	FILE *arq;	
	// w = cria arquivo vazio para escrita
	arq = fopen("graph.dat", "w");
	if(arq == NULL){
		printf("Erro ao abrir o arquivo!\n");
	}else{
		fprintf(arq,"%d %d\n",n,c);
		for(i=0;i<n;i++){
        	for(j=0;j<n;j++){
        		if(mat[i][j] != 0){
        			fprintf(arq,"%d %d %d\n",i+1,j+1,mat[i][j]);		
				}			
        	}
   		}
	}
	fclose(arq);
}

int main(){
	FILE *arq;
	int op,op2,op3,op5,sn,c,vertice=0,x,y,p,k,cont=0;
	double temp[3];
	int **mat,i,j;
	long int n;
	float d;
	srand(time(NULL));
    double time_spent = 0.0;
    clock_t begin=0.0,end=0.0;
    
    while(true){
    	if(cont<1)
    		printf("[1] - Gerar grafo\n");
    	else{
    		printf("[1] - Gerar novo grafo\n");
		} 
    	printf("[2] - Ler arquivo\n");
    	scanf("%d", &op);
    	system("cls");
    	if(op==1){
    		// Entrada: vertices, densidade e se será grafo direcionado ou nao
	    	printf("Digite a quantidade de vertices: ");
	    	scanf("%li",&n);
	    	while(n < 3 || n > 10000000){
	        	printf("Tamanho invalido!\nTamanho precisa ser > 3 e < 10000000\n");
	        	printf("Digite a quantidade de vertices: ");
	        	scanf("%li",&n);
	   		}system("cls");
	   		printf("Digite a densidade: ");
	    	scanf("%f",&d);
	    	while(d < 0.2 || d > 1){
	        	printf("Tamanho invalido!\nA densidade precisa ser > 0.2 e < 1\n");
	        	scanf("%f",&d);
	    	}
	    	system("cls");
	    	printf("[1] - Grafo direcionado\n[2] - Grafo nao direcionado\n");
	 	   	scanf("%d",&sn);
	 	   	system("cls");
	    	c = (((n*n) - n) / 2) * d; // Calculo da quantidade de aresta ((n2 - n) / 2) * d   
			mat = (int**)malloc(sizeof(int*)*n) ;
	    	for (i=0;i<n;i++){
	        	mat[i] = (int*)malloc(sizeof(int)*n);  // Alocacao da matriz dinamica
	    	}
	    	zeraGrafo(mat,n);			// Limpa lixo de memoria
			geraGrafo(mat,d,n,c,sn); 	// Gera o grafo de acordo com os valores lidos	
	   		exibeGrafo(mat,n);
	   		escreveGrafo(mat,n,c);
	   		printf("\nGrafo gerado e salvo em .dat:\n\n");
	   		system("pause");
	   		system("cls");
		}else if(op==2){	// Ler arq
			arq = fopen("graph.dat","r");
			if(arq == NULL){
				printf("Ocorreu um erro ao ler o arquivo!\n");
				return 0;
			}	
			fscanf(arq,"%li%d",&n,&k);			// Leitura da quantidade de vertices e arestas	
			mat = (int**)malloc(sizeof(int*)*n) ;
			for(i=0;i<n;i++){
			  	mat[i] = (int*)malloc(sizeof(int)*n);  // Alocacao da matriz dinamica
			}
			zeraGrafo(mat,n);	
			while(!feof(arq)){
				fscanf(arq,"%d%d%d",&x,&y,&p);
				mat[x-1][y-1] = p;
			} 	
			fclose(arq);
			printf("Grafo lido: \n\n ");
			exibeGrafo(mat,n);
			system("pause");
			system("cls");	
		}
		printf("[1] - Algoritmos de busca\n");
		printf("[2] - Algoritmos de caminho minimo\n");
		printf("[3] - Encerrar programa\n");
    	scanf("%d", &op);
    	system("cls");
    	switch(op){
			case 1:
				printf("[1] - BFS\n");
				printf("[2] - DFS\n");
				scanf("%d", &op2);
				system("cls");
				printf("\n[1] - Visitacao crescente\n[2] - Visitacao decrescente\n");
				scanf("%d",&op5);
				system("cls");
				switch(op2){
					case 1:
						printf("Digite o vertice inicial\n");
						scanf("%d",&vertice);
						while(vertice>n || vertice<1){
							printf("Vertice precisa ser < N & > 1\n");
							printf("Digite o vertice inicial novamente\n");
							scanf("%d",&vertice);
						}
						system("cls");
						vertice--;
						printf("\nGrafo:\n\n");
						exibeGrafo(mat,n);
						printf("\n#Configuracao do grafo:\n\n");;
					   	printf("\nQuantidade de vertices: %d\n",n);
					   	printf("\nDensidade do grafo: %f\n",d);
					   	printf("\nGrafo Direcionado? Y(1) - N(2): %d\n",sn);
					   	printf("\nVertice inicial: %d\n",vertice+1);
					   	printf("\nVisitacao crescente? Y(1) - N(2): %d\n",op5);
						BFS(mat,n,vertice,op5);	
						printf("\n");
						system("pause");
	   					system("cls");
						break;
					case 2:
						printf("Digite o vertice inicial\n");
						scanf("%d",&vertice);
						while(vertice>n || vertice<1){
							printf("Vertice precisa ser < N & > 1\n");
							printf("Digite o vertice inicial novamente\n");
							scanf("%d",&vertice);
						}
						vertice--;
						printf("\nGrafo:\n\n");
						exibeGrafo(mat,n);
						printf("\n#Configuracao do grafo:\n\n");;
					   	printf("\nQuantidade de vertices: %d\n",n);
					   	printf("\nDensidade do grafo: %f\n",d);
					   	printf("\nGrafo Direcionado? Y(1) - N(2): %d\n",sn);
					   	printf("\nGrafo Direcionado? Y(1) - N(2): %d\n",sn);
					   	printf("\nVertice inicial: %d\n",vertice+1);
					   	printf("\nVisitacao crescente? Y(1) - N(2): %d\n",op5);
						DFS(mat,n,vertice,op5);	
						printf("\n");
						system("pause");
	   					system("cls");
						break;
				}
				break;
			case 2:
				printf("[1] - Tempo de execucao do Dijkstra\n");
				printf("[2] - Tempo de execucao do Bellman-Ford\n");
				printf("[3] - Tempo de execucao do Floy-Marshall\n");
				printf("[4] - Comparar o tempo dos 3 algoritmos\n");
				scanf("%d", &op3);
				system("cls");
				printf("Grafo gerado: \n\n");
				exibeGrafo(mat,n);
				printf("\n");
				begin = end = 0;
				switch(op3){
					case 1:
						time_spent = 0;
						begin=end=0;
						begin = clock();
   						for(i=0;i<n;i++){
   							Dijkstra(mat,n,i);
						}
	   					end = clock();
	   					time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
					   	printf("\n#Configuracao do grafo:\n\n");;
					   	printf("\nQuantidade de vertices: %d\n",n);
					   	printf("\nDensidade do grafo: %f\n",d);
					   	printf("\nGrafo Direcionado? Y(1) - N(2): %d\n",sn);
						printf("\nTempo do Dijkstra: %lf segundos\n",time_spent);
						begin=end=0;
						break;
					case 2:
						time_spent = 0;
						begin=end=0;
						begin = clock();
						for(i=0;i<n;i++)
							BellmanFord(mat,n,i); 
						end = clock();
					   	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
					   	printf("\n#Configuracao do grafo: \n\n");;
					   	printf("\nQuantidade de vertices: %d\n",n);
					   	printf("\nDensidade do grafo: %f\n",d);
					   	printf("\nGrafo Direcionado? Y(1) - N(2): %d\n",sn);
						printf("\nTempo do Bellman-Ford: %lf segundos\n",time_spent);
						begin=end=0;
						break;
					case 3:
						time_spent = 0;
						begin=end=0;
						begin = clock();
   						FloydWarshall(mat,n);
   						end = clock();
   						time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
					   	printf("\n#Configuracao do grafo: \n\n");;
					   	printf("\nQuantidade de vertices: %d\n",n);
					   	printf("\nDensidade do grafo: %f\n",d);
					   	printf("\nGrafo Direcionado? Y(1) - N(2): %d\n",sn);
						printf("\nTempo do Floyd-Warshall: %lf segundos\n",time_spent);
						break;
					case 4:
						time_spent = 0;
						begin=end=0;
						printf("\n#Configuracao do grafo: \n\n");;
					   	printf("\nQuantidade de vertices: %d\n",n);
					   	printf("\nDensidade do grafo: %f\n",d);
					   	printf("\nGrafo Direcionado? Y(1) - N(2): %d\n",sn);   	
					   	begin = clock();
   						for(i=0;i<n;i++){
   							Dijkstra(mat,n,i);
						}
	   					end = clock();
	   					time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	   					temp[0] = time_spent;
					   	printf("\nTempo do Dijkstra: %lf segundos\n",time_spent);
					   	time_spent = 0;
						begin=end=0;
						begin = clock();
					   	for(i=0;i<n;i++)
						   BellmanFord(mat,n,i); 
						end = clock();
					   	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
					   	temp[1] = time_spent;
					   	printf("\nTempo do Bellman-Ford: %lf segundos\n",time_spent);
					   	begin=end=0;
					   	time_spent = 0;
					   	begin = clock();
   						FloydWarshall(mat,n);
   						end = clock();
   						time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   						temp[2] = time_spent;
   						printf("Tempo do Floyd-Warshall: %lf segundos\n",time_spent);
   						begin=end=0;
						break;
				}
				system("pause");
				system("cls");	
				break;			
			case 3:	
				printf("Encerrando programa...\n");
				liberaMatriz(mat,n);
				return 0;	
		}
		cont++;
	}
}
