#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileWriter.h"

FILE* mst_file;

void write_mst_info(char* name, char* type, int dimension){
    char filename[52] = "mst/";
    sprintf(filename + strlen(filename), "%s", name); //creates a name to be the file name
    sprintf(filename + strlen(filename), ".mst");

    mst_file = fopen(filename, "w");
    if(!mst_file)
        printf("Could not open %s. Aborting!", filename);

    fprintf(mst_file, "NAME: %s\n", name);
    fprintf(mst_file, "TYPE: %s\n", type);
    fprintf(mst_file, "DIMENSION: %d\n", dimension);
    fprintf(mst_file, "MST_SECTION\n");
}

void write_mst_arc(int id1, int id2){
    fprintf(mst_file, "%d %d\n", id1, id2);
}

void write_mst_eof(){
    fprintf(mst_file, "EOF");
}

void close_mst_file(){
    fclose(mst_file);
}
