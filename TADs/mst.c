#include <stdio.h>
#include <stdlib.h>
#include "mst.h"
#include "City.h"

typedef struct arc{
    int weight;
    City* umaCidade;
    City* otaCidade;
}Arc;


struct mst{//TODO
    /*lista de arcos ordenados tamanho (dimension-1)+..+1 */
};


int calc_arc_array_size(int dimension){
    int sum = 0;
    for(int cont = dimension-1; cont > 0; cont--){
      sum += cont;
    }
	return sum;
}

MST* generate_mst(TSP* tsp){ //TODO
	int array_size = calc_arc_array_size(tsp->dimension);

	return NULL; //trocar pra retornar a mst
}


/*TODO
	*alocar vetorzao para todos os arcos da mst
	*calcular a distancia entre todas as cidades e inicializar a struct ARC
	*inserir todos os arcos criados no vetorzao
	*ordenar por ordem nao-decrescente
	*union-find
*/

// [c1,c2,c3,c4]

// [c1->c2, c1->c3, c1->c4, c2->c3, c2->c4, c3->c4]

