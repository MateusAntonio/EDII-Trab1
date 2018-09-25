#include <stdlib.h>
#include "UF.h"

/*
* "Weighted QU + path compression" adapted from source code presented on class
*/

int* id;
int* sz;
int N;


void UF_init(int size){
    N = size;
    id = malloc(N * sizeof(*id));   //mallocs the arrays dinamically because the size of the input is unknown
    sz = malloc(N * sizeof(*sz));
    for(int i = 0; i < N; i++){
        id[i] = i;
        sz[i] = 1;
    }
}


int UF_find(int i){
    while(i != id[i])
        i = id[i];
    return i;
}


void UF_union(int p, int q){
    int i = UF_find(p);
    int j = UF_find(q);

    if(i == j)
        return;
    if(sz[i] < sz[j]){
        id[i] = j;
        sz[j] += sz[i];
    }else{
        id[j] = i;
        sz[i] += sz[j];
    }
}


bool UF_connected(int p, int q){
    return UF_find(p) == UF_find(q);
}


void UF_free(){
    free(id);   //frees both arrays dinamically allocated
    free(sz);
}