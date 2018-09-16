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

    char name[32] = "";
    char comment[100] = "";
    char type[10] = "";
    char dimension_[10] = "";
    char edge_weight_type[32] = "";
    char buffer[52] = "";


    //reads the name of the problem
    fscanf(file, "%s ", name); //ignore the "NAME: " string
    fscanf(file, "%s", name);

    //reads the comment of the problem
    fscanf(file, "%s ", comment); //ignore the "COMMENT: " string
    fgets(comment, 100, file);
    comment[strcspn(comment, "\n")] = '\0'; //change the '\n' of the end of the line to a '\0'

    //reads the type of the problem
    fscanf(file, "%s ", type); //ignore the "TYPE: " string
    fgets(type, 10, file);
    type[strcspn(type,"\n")] = '\0'; //change the '\n' of the end of the line to a '\0'
    
    //reads the dimension of the problem
    fscanf(file, "%s ", dimension_); //ignore the "DIMENSION: " string
    fgets(dimension_, 10, file);
    dimension_[strcspn(dimension_,"\n")] = '\0'; //change the '\n' of the end of the line to a '\0'

    //reads the edge_weight_type of the problem
    fscanf(file, "%s ", edge_weight_type); //ignore the "EDGE_WEIGHT_TYPE: " string
    fgets(edge_weight_type, 32, file);
    edge_weight_type[strcspn(edge_weight_type, "\n")] = '0'; //change the '\n' of the end of the line to a '\0'

    //ignore the NODE_COORD_SECTION line 
    fgets(buffer, 52, file);

    //creates and initializes the TSP struct
    int dimension = atoi(dimension_);
    TSP* tsp = init_tsp(name, comment, type, dimension, edge_weight_type); 



    City** city_array = malloc(dimension * sizeof(*city_array));
    for(int i = 0; i < 4; i++){
        // TODO leitura das cidades e inserção na struct
        fgets(buffer, 52, file); //read the line which contains the id and Xcoord and Ycoord

        char* token = strtok(buffer, " ");
        int city_id = atoi(token);
        printf("city id: %d\n", city_id);

        token = strtok(NULL," ");
        float x = strtod(token, NULL);
        printf("Xcoord: %.2f\n", x);

        token = strtok(NULL," ");
        float y = strtod(token, NULL);
        printf("Ycoord: %.2f\n", y);
    }











    fclose(file);

    return tsp;
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