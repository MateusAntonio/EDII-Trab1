#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileReader.h"


struct tsp{
    char* name;
    char* comment;
    char* type;
    int dimension;
    char* edge_weight_type;
    City** node_coord_section; //array of cities with size of dimension
};

TSP* init_tsp(char* name, char* comment, char* type, int dimension, char* edge_weight_type){
    TSP* new_tsp = malloc(sizeof(*new_tsp)); //mallocs the size of the struct

    new_tsp->name = malloc(strlen(name)+1); //mallocs the name string
    strcpy(new_tsp->name, name);

    new_tsp->comment = malloc(strlen(comment)+1); //mallocs the comment string
    strcpy(new_tsp->comment, comment);

    new_tsp->type = malloc(strlen(type)+1); //mallocs the type string
    strcpy(new_tsp->type, type);

    new_tsp->dimension = dimension;

    new_tsp->edge_weight_type = malloc(strlen(edge_weight_type)+1); //mallocs the edge weight type string
    strcpy(new_tsp->edge_weight_type, edge_weight_type);

    return new_tsp;
}

void print_tsp(TSP* tsp){
    printf("NAME: %s\n", tsp->name);
    printf("COMMENT: %s\n", tsp->comment);
    printf("TYPE: %s\n", tsp->type);
    printf("DIMENSION: %d\n", tsp->dimension);
    printf("EDGE_WEIGHT_TYPE: %s\n", tsp->edge_weight_type);
}


void free_tsp_cities(TSP* tsp){ //TODO TESTE DESSA FUNCAO 
    for(int i = 1; i < (tsp->dimension+1); i++){ //starts at 1, cuz array index equals to city id
        free_city(tsp->node_coord_section[i]);
    }
}

void free_tsp(TSP* tsp){
    free(tsp->name);
    free(tsp->comment);
    free(tsp->type);
    free(tsp->edge_weight_type);
    free_tsp_cities(tsp);
    free(tsp);
}

TSP* read_tsp_file(char* filename){
    FILE* file = fopen(filename, "r");
    if(!file){
        printf("File %s does not exist! Aborting!\n", filename);
        return NULL;
    }  
    printf("file %s aberto com sucesso!\n", filename);

    //reads the name of the problem
    char name[32] = "";
    fscanf(file, "%s ", name); //ignore the "NAME: " string
    fscanf(file, "%s", name);

    //reads the comment of the problem
    char comment[100] = "";
    fscanf(file, "%s ", comment); //ignore the "COMMENT: " string
    fgets(comment, 100, file);
    comment[strcspn(comment, "\n")] = '\0'; //change the '\n' of the end of the line to a '\0'

    //reads the type of the problem
    char type[10] = "";
    fscanf(file, "%s ", type); //ignore the "TYPE: " string
    fgets(type, 10, file);
    type[strcspn(type,"\n")] = '\0'; //change the '\n' of the end of the line to a '\0'
    
    //reads the dimension of the problem
    char dimension[10] = "";
    fscanf(file, "%s ", dimension); //ignore the "DIMENSION: " string
    fgets(dimension, 10, file);
    dimension[strcspn(dimension,"\n")] = '\0'; //change the '\n' of the end of the line to a '\0'


    //reads the edge_weight_type of the problem
    char edge_weight_type[32] = "";
    fscanf(file, "%s ", edge_weight_type); //ignore the "EDGE_WEIGHT_TYPE: " string
    fgets(edge_weight_type, 32, file);
    edge_weight_type[strcspn(edge_weight_type, "\n")] = '0'; //change the '\n' of the end of the line to a '\0'


    //ignore the NODE_COORD_SECTION line 
    char buffer[32] = "";
    fgets(buffer, 32, file);







    printf("nome do problema: %s\n", name);
    printf("comentario do problema: %s\n", comment);
    printf("tipo do problema: %s\n", type);
    printf("tamanho do problema: %s\n", dimension);
    printf("edge do problema: %s\n", edge_weight_type);    
    //TODO leitura do arquivo de entrada e inicializaçao da struct

    fclose(file);

    return NULL;
}








/*
******** exemplo de entrada ********
NAME: berlin52
COMMENT: 52 locations in Berlin (Groetschel)
TYPE: TSP
DIMENSION: 52
EDGE_WEIGHT_TYPE: EUC_2D
NODE_COORD_SECTION
1 565.0 575.0
2 25.0 185.0
3 345.0 750.0
4 945.0 685.0
...
52 1740.0 245.0
EOF

*/