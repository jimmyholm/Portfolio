#include "Stack.h"
#include <assert.h>
#include <string.h>
typedef struct sStackNode
{
  void* Data;
  struct sStackNode* Next;
} sStackNode;

typedef struct sStack
{
  size_t Size;
  size_t ElementSize;
  void(*EraseFun)(void*);
  sStackNode* Stack;
} sStack;


int sStackInit(sStack** Stack, size_t ElementSize, void(*EraseFun)(void*))
{
  assert(Stack != NULL && "Stack reference must not be Null!\n");
  if(Stack == NULL)
    return 0;
  assert(*Stack == NULL && "Stack must be assigned NULL!\n");
  if(*Stack != NULL)
    return 0;
  *Stack = malloc(sizeof(sStack));
  if(*Stack == NULL)
    return 0;
  (*Stack)->Size = 0;
  (*Stack)->ElementSize = ElementSize;
  (*Stack)->EraseFun = EraseFun;
  (*Stack)->Stack = NULL;
  return 1;
}

void sStackPush(sStack* Stack, void* Data)
{
  assert(Stack != NULL && "Stack must not be Null!\n");
  if(Stack == NULL)
    return;
  sStackNode* Node = malloc(sizeof(sStackNode));
  Node->Data = malloc(Stack->ElementSize);
  memcpy(Node->Data, Data, Stack->ElementSize);
  Node->Next = Stack->Stack;
  Stack->Stack = Node;
  Stack->Size++;
}

void* sStackPeek(sStack* Stack)
{
  assert(Stack != NULL && "Stack must not be Null!\n");
  if(Stack == NULL)
    return NULL;
  
  return (Stack->Stack == NULL) ? NULL : Stack->Stack->Data;
}

void sStackPop(sStack* Stack)
{
  assert(Stack != NULL && "Stack must not be Null!\n");
  if(Stack == NULL)
    return;
  if(Stack->Stack == NULL)
    return;
  sStackNode* del = Stack->Stack;
  Stack->Stack = del->Next;
  if(Stack->EraseFun != NULL)
    (*Stack->EraseFun)(del->Data);
  free(del->Data);
  free(del);
  Stack->Size--;
}

size_t sStackSize(sStack* Stack)
{
  assert(Stack != NULL && "Stack must not be Null!\n");
  if(Stack == NULL)
    return 0;
  return Stack->Size;
}

void sStackDestroy(sStack** Stack)
{
  assert(Stack != NULL && "Stack reference must not be Null!\n");
  if(Stack == NULL)
    return;
  assert(*Stack != NULL && "Stack must not be Null!\n");
  if(*Stack == NULL)
    return;
  while((*Stack)->Stack != NULL)
  {
    sStackPop(*Stack);
  }
  free(*Stack);
  *Stack = NULL;
}
