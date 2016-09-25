#include "LinkedList.h"

typedef struct sListNode
{
  void* Data;
  struct sListNode* Next;
} sListNode;

typedef struct sLinkedList
{
  size_t Size;
  sListNode* Head;
  sListNode* Tail;
  size_t ElementSize;
  void (*EraseFun)(void*);
} sLinkedList;

typedef struct sListIterator
{
  sListNode** It;
  sLinkedList* List;
} sListIterator;

void listInitialize(sLinkedList** List, size_t ElementSize, void(*EraseFun)(void*))
{
  if(*List != NULL)
    return;
  *List = malloc(sizeof(sLinkedList));
  (*List)->Size = 0;
  (*List)->Head = NULL;
  (*List)->Tail = NULL;
  (*List)->ElementSize = ElementSize;
  (*List)->EraseFun = EraseFun;
}

void listPushBack(sLinkedList* List, void* Data)
{
  if(List == NULL)
    return;
  sListNode* Node = malloc(sizeof(sListNode));
  Node->Data = malloc(List->ElementSize);
  memcpy(Node->Data, Data, List->ElementSize);
  Node->Next = NULL;
  if(List->Head == NULL)
    List->Head = List->Tail = Node;
  else
  {
    List->Tail->Next = Node;
    List->Tail = Node;
  }
  List->Size++;
}

void listPushFront(sLinkedList* List, void* Data)
{
  if(List == NULL)
    return;
  sListNode* Node = malloc(sizeof(sListNode));
  Node->Data = malloc(sizeof(List->ElementSize));
  memcpy(Node->Data, Data, List->ElementSize);
  Node->Next = List->Head;
  if(List->Head == NULL)
    List->Head = List->Tail = Node;
  else
    List->Head = Node;
  List->Size++;
}

void listPopFront(sLinkedList* List)
{
  if(List == NULL)
    return;
  if(List->Head == NULL)
    return;
  sListNode* Node = List->Head->Next;
  if(List->EraseFun != NULL)
    (*List->EraseFun)(List->Head->Data);
  free(List->Head->Data);
  free(List->Head);
  List->Head = Node;
  List->Size--;
  if(List->Head == NULL)
  {
	  List->Tail = NULL;
	  List->Size = 0;
  }
}
void listPopBack(sLinkedList* List)
{
  if(List == NULL)
    return;
  sListIterator* it = 0;
  listHead(List, &it);
  if(*(it->It) == NULL)
  {
    free(it);
    return;
  }
  sListNode* Node = *(it->It);
  listIteratorNext(it);
  while(1)
  {
    if((*(it->It))->Next == NULL)
    {
      sListNode* erase = *(it->It);
      List->Tail = Node;
      Node->Next = NULL;
      if(List->EraseFun != NULL)
	(*List->EraseFun)(erase->Data);
      free(erase->Data);
      free(erase);
      break;
    }
    Node = *(it->It);
    listIteratorNext(it);
  }
  free(it);
  List->Size--;
  if(List->Tail == NULL)
  {
	  List->Head = NULL;
	  List->Size = 0;
  }
}

void listInsert(sListIterator* Iterator, void* Data)
{
  if(*(Iterator->It) == NULL)
    listPushBack(Iterator->List, Data);
  else
  {
    size_t ElemSize = Iterator->List->ElementSize;
    sListNode* Node = 0;
    Node = malloc(sizeof(sListNode));
    Node->Data = malloc(ElemSize);
    memcpy(Node->Data, Data, ElemSize);
    Node->Next = (*(Iterator->It))->Next;
    (*Iterator->It)->Next = Node;
    Iterator->List->Size++;
    if(Iterator->List->Head == Iterator->List->Tail)
    {
	    sListNode* N1 = Node;
	    sListNode* N2 = Node->Next;
	    while(N2 != NULL)
	    {
		    N1 = N2;
		    N2 = N2->Next;
	    }
	    Iterator->List->Tail = N1;
    }
  }
}

void listErase(sListIterator* Iterator)
{
  if(*(Iterator->It) == NULL)
    return;
  sListNode* Node = (*(Iterator->It));
  void* Data = Node->Data;
  *(Iterator->It) = Node->Next;
  if(*(Iterator->It) == NULL)
    Iterator->List->Tail = NULL;
  free(Node);
  Node = NULL;
  if(Iterator->List->EraseFun != NULL)
    (*Iterator->List->EraseFun)(Data);
  free(Data);
  Data = NULL;
  Iterator->List->Size--;
  if(Iterator->List->Head == NULL)
  {
	  Iterator->List->Tail = NULL;
	  Iterator->List->Size = 0;
  }
  if(Iterator->List->Tail == NULL)
  {
	  Iterator->List->Head = NULL;
	  Iterator->List->Size = 0;
  }
}

void listEraseData(sLinkedList* List, void* Data, int (*cmp)(void*, void*))
{
	sListIterator* It = 0;
	listHead(List, &It);
	while(It != NULL)
	{
		if((*cmp)((*It->It)->Data, Data))
		{
			listErase(It);
			listIteratorDestroy(&It);
			return;
		}
		listIteratorNext(It);
	}
	listIteratorDestroy(&It);
}

void* listGet(sListIterator* Iterator)
{
  if(*(Iterator->It) == NULL)
    return NULL;
  void* Data = (*(Iterator->It))->Data;
  return Data;
}
void* listPeek(sLinkedList* List)
{
  if(List == NULL)
    return NULL;
  if(List->Head == NULL)
    return NULL;
  return List->Head->Data;
}

void* listFind(sLinkedList* List, void* Data, int (*cmp)(void*, void*))
{
	if(List == NULL || Data == NULL || cmp == NULL)
		return NULL;
	if(List->Head == NULL)
		return NULL;
	sListNode* Node = List->Head;
	while(Node != NULL)
	{
		if((*cmp)(Data, Node->Data) == 1)
			return Node->Data;
		Node = Node->Next;
	}
	return NULL;
}

void listHead(sLinkedList* List, sListIterator** It)
{
  if(It == NULL)
    return;
  if(*It == NULL)
    *It = malloc(sizeof(sListIterator));
  (*It)->List = List;
  (*It)->It = &(List->Head);
  return;
}

size_t listSize(sLinkedList* List)
{
  if(List == NULL)
    return 0;
  return List->Size;
}

int listEmpty(sLinkedList* List)
{
  if(List == NULL)
    return 0;
  return (List->Size == 0) ? 1 : 0;
}

void listClear(sLinkedList* List)
{
  if(List == NULL)
    return;
  sListIterator* it = 0;
  listHead(List, &it);
  while(!listIteratorEnd(it))
    listErase(it);
  free(it);
}

void listDestroy(sLinkedList** List)
{
  if(*List == NULL)
    return;
  listClear(*List);
  free(*List);
  *List = NULL;
}

void listIteratorNext(sListIterator* Iterator)
{
  if(Iterator == NULL)
    return;
  if(*(Iterator->It) == NULL)
    return;
  Iterator->It = &(*(Iterator->It))->Next;
}

int listIteratorEnd(sListIterator* Iterator)
{
  if(Iterator == NULL)
    return 1;
  return(*(Iterator->It) == NULL) ? 1 : 0;
}

void listIteratorCopy(sListIterator* Src, sListIterator** Dst)
{
  if(Dst == NULL)
    return;
  if(*Dst == NULL)
    *Dst = malloc(sizeof(sListIterator));  
  (*Dst)->It = Src->It;
  (*Dst)->List = Src->List;
}

void listIteratorDestroy(sListIterator** Iterator)
{
  if(Iterator == NULL || *Iterator == NULL)
    return;
  free(*Iterator);
  *Iterator = NULL;
}
