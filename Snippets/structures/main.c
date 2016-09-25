#include <stdio.h>
#include <stdlib.h>
#include "DataStructures.h"

int RandInt(int min, int max)
{
  float rnd = (float)rand() / (float)RAND_MAX;
  return (int)(min + (rnd*(max-min)));
}

int main(int argc, char *argv[])
{
  sBinomHeap* Heap = NULL;
  sBinHeapInit(&Heap, sizeof(int), NULL, BINOM_MINHEAP);
  int a = 5;
  sBinHeapInsert(Heap, a, (void*)&a);
  a = 10;
  sBinHeapInsert(Heap, a, (void*)&a);
  a = 19;
  sBinHeapInsert(Heap, a, (void*)&a);
  a = 3;
  sBinHeapInsert(Heap, a, (void*)&a);
  a = 2;
  sBinHeapInsert(Heap, a, (void*)&a);
  a = 4;
  sBinHeapInsert(Heap, a, (void*)&a);
  sBinHeapDeleteExtreme(Heap);
  sBinHeapDelete(Heap, 3);
  a = *(int*)sBinHeapFindExtreme(Heap);
  printf("%d\n", a);
  sBinHeapDestroy(&Heap);
}
