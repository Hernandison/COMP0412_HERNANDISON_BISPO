#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   

/*
========================================================================
 1. INSERTION SORT
========================================================================
*/
void insertion(int *A, int n) {
    int i, j, chave;
    for (i = 1; i < n; i++) {
        chave = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > chave) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = chave;
    }
}

/*
========================================================================
 2. MERGE SORT (mergesort2)
========================================================================
*/


void intercala(int *A, int *B, int p, int q, int r) {
    int i = p;
    int j = q + 1;
    int k = p;

    while (i <= q && j <= r) {
        if (B[i] <= B[j]) {
            A[k++] = B[i++];
        } else {
            A[k++] = B[j++];
        }
    }

  
    while (i <= q) {
        A[k++] = B[i++];
    }
   
    while (j <= r) {
        A[k++] = B[j++];
    }
}


void mergesort_recursivo(int *A, int *B, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;

        for (int i = p; i <= r; i++) {
            B[i] = A[i];
        }
        
        mergesort_recursivo(A, B, p, q);
        mergesort_recursivo(A, B, q + 1, r);
        
        for(int i = p; i <= r; i++) {
            B[i] = A[i];
        }
        
        intercala(A, B, p, q, r);
    }
}


void mergesort2(int *A, int n) {
    if (n <= 0) return;

    
    int *B = (int *)malloc(n * sizeof(int));
    if (B == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para mergesort\n");
        return;
    }
    
   
    mergesort_recursivo(A, B, 0, n - 1);
    
    free(B);
}


/*
========================================================================
 3. QUICK SORT (quicksort)
========================================================================
*/


void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int particiona(int *A, int p, int r) {
    int pivo = A[r]; 
    int i = (p - 1); 

    for (int j = p; j <= r - 1; j++) {
      
        if (A[j] <= pivo) {
            i++; 
            troca(&A[i], &A[j]);
        }
    }
    troca(&A[i + 1], &A[r]);
    return (i + 1);
}


void quicksort_recursivo(int *A, int p, int r) {
    if (p < r) {
      
        int q = particiona(A, p, r);

        
        quicksort_recursivo(A, p, q - 1);
        quicksort_recursivo(A, q + 1, r);
    }
}


void quicksort(int *A, int n) {
    if (n <= 0) return;
    quicksort_recursivo(A, 0, n - 1);
}


/*
========================================================================
 FUNÇÕES AUXILIARES PARA GERAR VETORES
========================================================================
*/


void gerar_vetor_aleatorio(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand();
    }
}

void gerar_vetor_crescente(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

void gerar_vetor_decrescente(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - 1 - i;
    }
}

void copiar_vetor(int *origem, int *destino, int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

/*
========================================================================
 FUNÇÃO PRINCIPAL (MAIN)
========================================================================
*/
int main() {
  
    int tamanhos[] = {1000, 5000, 10000, 20000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    
    printf("Tamanho;Tipo;Algoritmo;Tempo (s)\n");

    for (int i = 0; i < num_tamanhos; i++) {
        int N = tamanhos[i];

        
        int *vetor_original = (int *)malloc(N * sizeof(int));
        int *vetor_copia = (int *)malloc(N * sizeof(int));

        if (vetor_original == NULL || vetor_copia == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria\n");
            return 1;
        }

  
        gerar_vetor_aleatorio(vetor_original, N);
        
        copiar_vetor(vetor_original, vetor_copia, N);
        start = clock();
        insertion(vetor_copia, N);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%d;Aleatorio;Insertion;%f\n", N, cpu_time_used);

        copiar_vetor(vetor_original, vetor_copia, N);
        start = clock();
        mergesort2(vetor_copia, N);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%d;Aleatorio;MergeSort;%f\n", N, cpu_time_used);

        copiar_vetor(vetor_original, vetor_copia, N);
        start = clock();
        quicksort(vetor_copia, N);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%d;Aleatorio;QuickSort;%f\n", N, cpu_time_used);


     
        gerar_vetor_crescente(vetor_original, N);
        
        copiar_vetor(vetor_original, vetor_copia, N);
        start = clock();
        insertion(vetor_copia, N);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%d;Crescente;Insertion;%f\n", N, cpu_time_used);

        copiar_vetor(vetor_original, vetor_copia, N);
        start = clock();
        mergesort2(vetor_copia, N);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%d;Crescente;MergeSort;%f\n", N, cpu_time_used);

        copiar_vetor(vetor_original, vetor_copia, N);
        start = clock();
        quicksort(vetor_copia, N);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%d;Crescente;QuickSort;%f\n", N, cpu_time_used);

      
        gerar_vetor_decrescente(vetor_original, N);
        
        copiar_vetor(vetor_original, vetor_copia, N);
        start = clock();
        insertion(vetor_copia, N);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%d;Decrescente;Insertion;%f\n", N, cpu_time_used);

        copiar_vetor(vetor_original, vetor_copia, N);
        start = clock();
        mergesort2(vetor_copia, N);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%d;Decrescente;MergeSort;%f\n", N, cpu_time_used);

        copiar_vetor(vetor_original, vetor_copia, N);
        start = clock();
        quicksort(vetor_copia, N);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%d;Decrescente;QuickSort;%f\n", N, cpu_time_used);

      
        free(vetor_original);
        free(vetor_copia);
    }

    return 0;
}