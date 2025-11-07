#include <stdio.h>

void maxheapify (int *A, int m, int i) {
    int e, d, maior, aux;
    e = 2 * i + 1;
    d = 2 * i + 2;
    if ((e <= m) && A[e] > A[i])
        maior = e;
    else 
        maior = i;
    if  ((d<m) && (A[d] > A[maior]))
        maior = d;
    
    if (maior != i) {
        aux = A[i];
        A[i] = A[maior];
        A[maior] = aux;
        maxheapify(A, m, maior);
    }                
}



void build_max_heap (int *A int n) {
    for(int i = n/2; i >= 0; i --)
        maxheapify(A, n, i);

}


void heapsort2 (int *A, int n) {
    int m, aux;
    build_maxheap (A, n);
    m = n-1
    for (int i = n-1; i>=1; i--) {
        aux = A[0];
        A[0] = A[i];
        A[i] = aux;
        m--;
        maxheapify(A, m, 0);
    }

}