#ifndef UF_H
#define UF_H
#include <stdbool.h>

void UF_init(int size);

int UF_find(int i);

void UF_union(int p, int q);

bool UF_connected(int p, int q);

void UF_free();

#endif //UF_H