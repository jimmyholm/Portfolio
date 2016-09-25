#include "DynamicArray.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct sDynamicArray
{
  void** Array;
  size_t Size;
  size_t ElementSize;
  void (*EraseFun)(void*);
} sDynamicArray;

int dArrayInit(sDynamicArray** Array, size_t Size, size_t ElementSize, void (*EraseFun)(void*))
{
  assert(*Array == NULL && "Array needs to be assigned 0!\n");
  if(*Array != NULL)
    return 0;
  *Array = malloc(sizeof(sDynamicArray));
  (*Array)->Array = malloc(sizeof(void*)*Size);
  memset((*Array)->Array, 0, sizeof(void*)*Size);
  (*Array)->Size = Size;
  (*Array)->ElementSize = ElementSize;
  (*Array)->EraseFun = EraseFun;
  return 1;
}


void dArrayDestroy(sDynamicArray** Array)
{
  assert(*Array != NULL && "Array neeeds to be initialized!\n");
  if(*Array == NULL)
    return;
  dArrayClear(*Array);
  free((*Array)->Array);
  free(*Array);
  *Array = NULL;
}

void dArraySet(sDynamicArray* Array, size_t Index, void* Data, int Erase)
{
  assert(Array != NULL && "Array neeeds to be initialized!\n");
  if(Array == NULL)
    return;
  assert(Index < Array->Size && "Array index out of range.\n");
  if(Index >= Array->Size)
     return;
  if(Erase)
  {
    if(Array->Array[Index] != NULL)
      dArrayErase(Array, Index);
  }
  Array->Array[Index] = malloc(Array->ElementSize);
  memcpy(Array->Array[Index], Data, Array->ElementSize);
}

void* dArrayGet(sDynamicArray* Array, size_t Index)
{
  assert(Array != NULL && "Array neeeds to be initialized!\n");
  if(Array == NULL)
    return NULL;
  assert(Index < Array->Size && "Array index out of range.\n");
  if(Index >= Array->Size)
     return NULL;
  return Array->Array[Index]; 
}

void dArrayErase(sDynamicArray* Array, size_t Index)
{
  assert(Array != NULL && "Array neeeds to be initialized!\n");
  if(Array == NULL)
    return;
  assert(Index < Array->Size && "Array index out of range.\n");
  if(Index >= Array->Size)
     return;
  if(Array->Array[Index] != NULL)
  {
    if(Array->EraseFun != NULL)
      (*Array->EraseFun)(Array->Array[Index]);
    free(Array->Array[Index]);
    Array->Array[Index] = NULL;
  }
}

void dArrayClear(sDynamicArray* Array)
{
  assert(Array != NULL && "Array neeeds to be initialized!\n");
  if(Array == NULL)
    return;
  for(size_t i = 0; i < Array->Size; i++)
  {
    dArrayErase(Array, i);
  }
}

int dArrayResize(sDynamicArray* Array, size_t NewSize)
{
  assert(Array != NULL && "Array neeeds to be initialized!\n");
  if(Array == NULL)
    return 0;
  void** new = malloc(NewSize * sizeof(void*));
  memset(new, 0, NewSize*sizeof(void*));
  for(size_t i = 0; i < NewSize && i < Array->Size; i++)
  {
    if(Array->Array[i] != NULL)
    {
      new[i] = malloc(Array->ElementSize);
      memcpy(new[i], Array->Array[i], Array->ElementSize);
    }
    else
      new[i] = NULL;
  }
  dArrayClear(Array);
  free(Array->Array);
  Array->Array = new;
  Array->Size = NewSize;
  return 1;
}

int dArraySize(sDynamicArray* Array)
{
  assert(Array != NULL && "Array neeeds to be initialized!\n");
  if(Array == NULL)
    return 0;
  return Array->Size;
}

int dArrayAdd(sDynamicArray* Array, void* Data, int Erase)
{
  assert(Array != NULL && "Array neeeds to be initialized!\n");
  if(Array == NULL)
    return 0;
  for(int i = 0; i < Array->Size; i++)
  {
    if(Array->Array[i] == NULL)
    {
      dArraySet(Array, i, Data, Erase);
      return i;
    }
  }
  int r = Array->Size;
  dArrayResize(Array, Array->Size+1);
  dArraySet(Array, r, Data, Erase);
  return r;
}
