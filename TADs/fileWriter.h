#ifndef FILE_WRITER_H
#define FILE_WRITER_H

void write_mst_info(char* name, char* type, int dimension);

void write_mst_arc(int id1, int id2);

void write_mst_eof();

void close_mst_file();

#endif //FILE_WRITER_H