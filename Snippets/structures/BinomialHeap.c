#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "BinomialHeap.h"
#include "Stack.h"

#define LONG_MIN (sizeof(long int) >= 8) ? 0xF000000000000000 : 0xF0000000
#define LONG_MAX (sizeof(long int) >= 8) ? 0x7FFFFFFFFFFFFFFF : 0x7FFFFFFF

typedef struct sBinomTree
{
	size_t Size;
	size_t Order;
	long int Key;
	void* Data;
	struct sBinomTree* Children;
	struct sBinomTree* Siblings;
} sBinomTree;

typedef struct sBinomHeap
{
	size_t Size;
	size_t ElementSize;
	void (*EraseFun)(void*);
	sBinomTree* Head;
	sBinomTree* Extreme;
	int(*cmp)(long, long);
	char HeapType;
} sBinomHeap;

int sBTCompareMin(long i1, long i2)
{
	return (i1 < i2) ? 1 : 0;
}

int sBTCompareMax(long i1, long i2)
{
	return (i1 > i2) ? 1 : 0;
}

void sBTDestroyTree(sBinomTree* Tree, void(*Erase)(void*))
{
	if(Tree == NULL)
		return;
	sBTDestroyTree(Tree->Children, Erase);
	sBTDestroyTree(Tree->Siblings, Erase);
	if(Erase != NULL)
		(*Erase)(Tree->Data);
	free(Tree->Data);
	free(Tree);
}

sBinomTree* sBTMerge(sBinomTree* T1, sBinomTree* T2, int(*cmp)(long, long))
{
	assert((T1 != NULL && T2 != NULL) && "Trees to merge cannot be null.\n");
	if(T1 == NULL || T2 == NULL)
		return NULL;
	assert((T1->Order == T2->Order) && "Trees to merge must be of the same order!\n");
	if(T1->Order != T2->Order)
		return NULL;
	if ((*cmp)(T1->Key, T2->Key))
	{
		if(T2->Siblings == NULL)
		{
			T2->Siblings = T1->Children;
			T1->Children = T2;
		}
		else
		{
			sBinomTree* sib = T2->Siblings;
			while(sib->Siblings != NULL)
				sib = sib->Siblings;
			sib->Siblings = T1->Children;
			T1->Children = T2;
		}
		T1->Order +=1;
		T1->Size += T2->Size;
		return T1;
	}
	if(T1->Siblings == NULL)
	{
		T1->Siblings = T2->Children;
		T2->Children = T1;
	}
	else
	{
		sBinomTree* sib = T1->Siblings;
		while(sib->Siblings != NULL)
			sib = sib->Siblings;
		sib->Siblings = T2->Children;
		T2->Children = T1;
	}
	T2->Order +=1;
	T2->Size += T1->Size;
	return T2;
}

int sBinHeapInit(sBinomHeap** Heap, size_t ElementSize, void (*EraseFun)(void*), char HeapType)
{
	assert((*Heap) == NULL && "Heap must be NULL-assigned before initialization.\n");
	if(*Heap != NULL)
		return 0;
	*Heap = malloc(sizeof(sBinomHeap));
	assert((*Heap) != NULL && "Heap allocation failed!\n");
	if(*Heap == NULL)
		return 0;
	(*Heap)->Size = 0;
	(*Heap)->ElementSize = ElementSize;
	(*Heap)->EraseFun = EraseFun;
	(*Heap)->Head = NULL;
	(*Heap)->Extreme = NULL;
	(*Heap)->cmp = (HeapType == BINOM_MINHEAP) ? *sBTCompareMin : *sBTCompareMax;
	(*Heap)->HeapType = HeapType;
	return 1;
}

void sBinHeapAddTree(sBinomHeap* Heap, sBinomTree* Tree)
{
	if(Heap == NULL)
		return;
	if(Tree == NULL)
		return;
	sBinomTree** Head = &Heap->Head;
	while(*Head != NULL)
	{
		if(Tree->Order < (*Head)->Order)
		{
			Tree->Siblings = (*Head);
			*Head = Tree;
			Heap->Size += Tree->Size;
			return;
		}
		else if(Tree->Order == (*Head)->Order)
		{
			Heap->Size -= (*Head)->Size;
			sBinomTree* Sib = (*Head)->Siblings;
			(*Head)->Siblings = NULL;
			sBinomTree* New = sBTMerge((*Head), Tree, Heap->cmp);
			(*Head) = Sib;
			sBinHeapAddTree(Heap, New);
			return;
		}
		else
			Head = &(*Head)->Siblings;
	}
	*Head = Tree;
	Heap->Size += Tree->Size;
}

void sBinHeapMerge(sBinomHeap** Heap1, sBinomHeap** Heap2)
{
	assert((Heap1 != NULL && Heap2 != NULL) && "Neither pointer must be NULL!\n");
	if(Heap1 == NULL || Heap2 == NULL)
		return;
	assert((*Heap1 != NULL && *Heap2 != NULL) && "Neither heap can be NULL!\n");
	if(*Heap1 == NULL || *Heap2 == NULL)
		return;
	sBinomHeap* H1 = *Heap1;
	sBinomHeap* H2 = *Heap2;
	assert(H1->ElementSize == H2->ElementSize && "Both heaps must store the same type data!\n");
	if(H1->ElementSize != H2->ElementSize)
		return;
	assert(H1->HeapType == H2->HeapType && "Both heaps must be of the same type!\n");
	if(H1->HeapType != H2->HeapType)
		return;
	sBinomTree* T2 = H2->Head;
	sBinomTree* Add = NULL;
	while(T2 != NULL)
	{
		Add = T2;
		T2 = T2->Siblings;
		sBinHeapAddTree(H1, Add);
	}
	//H1->Size += H2->Size;
	free(H2);
	*Heap2 = NULL;
}

void sBinHeapInsert(sBinomHeap* Heap, long Key, void* Data)
{
	sBinomHeap* New = NULL;
	sBinHeapInit(&New, Heap->ElementSize, Heap->EraseFun, Heap->HeapType);
	sBinomTree* T = malloc(sizeof(sBinomTree));
	T->Size = 1;
	T->Order = 0;
	T->Key = Key;
	T->Data = malloc(Heap->ElementSize);
	memcpy(T->Data, Data, Heap->ElementSize);
	T->Children = NULL;
	T->Siblings = NULL;
	sBinHeapAddTree(New, T);
	sBinHeapMerge(&Heap, &New);
}

void* sBinHeapFindExtreme(sBinomHeap* Heap)
{
	assert(Heap != NULL && "Heap must not be NULL!\n");
	if(Heap == NULL)
		return NULL;
	long extreme = (Heap->HeapType == BINOM_MINHEAP) ? LONG_MAX : LONG_MIN;
	sBinomTree* T = Heap->Head;
	void* ret = NULL;
	while(T != NULL)
	{
		if((*Heap->cmp)(T->Key, extreme))
		{
			ret = T->Data;
			extreme = T->Key;
		}
		T = T->Siblings;
	}
	return ret;
}

void sBinHeapDeleteExtreme(sBinomHeap* Heap)
{
	assert(Heap != NULL && "Heap must not be NULL!\n");
	if(Heap == NULL)
		return;
	long extreme = Heap->Head->Key;//(Heap->HeapType == BINOM_MINHEAP) ? LONG_MAX : LONG_MIN;
	sBinomTree** find = &Heap->Head;
	sBinomTree** T = &Heap->Head->Siblings;
	while((*T) != NULL)
	{
		if((*Heap->cmp)((*T)->Key, extreme))
			find = T;
		T = &(*T)->Siblings;
	}
	sBinomTree* del= (*find);
	*find = del->Siblings;
	sBinomTree* Children = del->Children;
	if(Heap->EraseFun != NULL)
		(*Heap->EraseFun)(del->Data);
	free(del->Data);
	free(del);
	sBinomTree* Add = NULL;
	while(Children != NULL)
	{
		Add = Children;
		Children = Children->Siblings;
		Add->Siblings = NULL;
		sBinHeapAddTree(Heap, Add);
	}
}

void sBinTreeSwap(sBinomTree* T1, sBinomTree* T2)
{
	if(T1 == NULL || T2 == NULL)
		return;
	long Key = T1->Key;
	void* Data = T1->Data;
	T1->Key = T2->Key;
	T1->Data = T2->Data;
	T2->Key = Key;
	T2->Data = Data;
}

void sBTAddToStack(sBinomTree* Tree, sStack* Stack)
{
	if(Tree == NULL || Stack == NULL)
		return;
	sStackPush(Stack, (void*)Tree);
	sBinomTree* Children = Tree->Children;
	while(Children != NULL)
		sBTAddToStack(Children, Stack);
	sBTAddToStack(Tree->Siblings, Stack);
}

void sBTMaintainOrder(sBinomTree* Tree, int(*cmp)(long, long))
{
	assert(Tree != NULL && "Tree can't be NULL.\n");
	if(Tree == NULL)
		return;
	if(Tree->Children == NULL)
		return;
	sStack* Stack = NULL;
	sStackInit(&Stack, sizeof(sBinomTree*), NULL);
	sBTAddToStack(Tree, Stack);
	sBinomTree* T = (sBinomTree*)sStackPeek(Stack);
	sStackPop(Stack);
	sBinomTree* P = 0;
	while(sStackSize(Stack) != 0)
	{
		P = (sBinomTree*)sStackPeek(Stack);
		sStackPop(Stack);
		if((*cmp)(T->Key, P->Key))
			sBinTreeSwap(T, P);
		T = P;
	}
	sStackDestroy(&Stack);
}

sBinomTree* sBTFindKey(sBinomTree* Tree, long Key, int(*cmp)(long, long))
{
	if(Tree == NULL)
		return NULL;
	sBinomTree* ret = NULL;
	sBinomTree* list = Tree;
	while(list != NULL)
	{
		if(Key == list->Key)
			return list;
		if((*cmp)(list->Key, Key))
		{
			ret = sBTFindKey(list->Children, Key, cmp);
			if(ret != NULL)
				return ret;
		}
		list = list->Siblings;
	}
	return NULL;
}

sBinomTree* sBTFindData(sBinomTree* Tree, void* Data, int(*cmp)(void*, void*))
{
	if(Tree == NULL)
		return NULL;
	sBinomTree* ret = NULL;
	sBinomTree* list = Tree;
	while(list != NULL)
	{
		if((*cmp)(Data, list->Data))
			return list;
		ret = sBTFindData(list->Children, Data, cmp);
		if(ret != NULL)
			return ret;
		list = list->Siblings;
	}
	return NULL;
}

int  sBinHeapChangeKey(sBinomHeap* Heap, long Key, long NewKey)
{
	assert(Heap != NULL && "Heap cannot be NULL!");
	if(Heap == NULL)
		return 0;
	if(Key == NewKey)
		return 0;
	if(Heap->HeapType == BINOM_MINHEAP)
	{
		assert(NewKey < Key && "New key must be LESS than original key for min heap.\n");
		if(Key < NewKey)
			return 0;
	}
	else
	{
		assert(NewKey > Key && "New key must be GREATER than the original key for max heap.\n");
		if(Key > NewKey)
			return 0;
	}
	sBinomTree* Find = sBTFindKey(Heap->Head, Key, Heap->cmp);
	if(Find != NULL)
	{
		Find->Key = NewKey;
		sBTMaintainOrder(Heap->Head, Heap->cmp);
		return 1;
	}
	return 0;
}

int sBinHeapChangeKeyData(sBinomHeap* Heap, void* Data, long NewKey, int (*cmp)(void*, void*))
{
	assert(Heap != NULL && "Heap cannot be NULL!");
	if(Heap == NULL)
		return 0;
	sBinomTree* Find = sBTFindData(Heap->Head, Data, cmp);
	if(Find != NULL)
	{
		Find->Key = NewKey;
		sBTMaintainOrder(Heap->Head, Heap->cmp);
		return 1;
	}
	return 0;
}

void sBinHeapDelete(sBinomHeap* Heap, long Key)
{
	assert(Heap != NULL && "Heap cannot be NULL!");
	if(Heap == NULL)
		return;
	long NK = (Heap->HeapType == BINOM_MINHEAP) ? LONG_MIN : LONG_MAX;
	if(sBinHeapChangeKey(Heap, Key, NK) == 1)
	{
		sBinHeapDeleteExtreme(Heap);
	}
}

void sBinHeapDeleteData(sBinomHeap* Heap, void* Data, int (*cmp)(void*, void*))
{
	assert(Heap != NULL && "Heap cannot be NULL!");
	if(Heap == NULL)
		return;
	long NK = (Heap->HeapType == BINOM_MINHEAP) ? LONG_MIN : LONG_MAX;
	if(sBinHeapChangeKeyData(Heap, Data, NK, cmp) == 1)
	{
		sBinHeapDeleteExtreme(Heap);
	}
}

void sBinHeapDestroy(sBinomHeap** Heap)
{
	sBinomHeap* h = *Heap;
	assert(h != NULL && "Heap cannot be null!\n");
	if(h == NULL)
		return;
	if(h->Head != NULL)
		sBTDestroyTree(h->Head, h->EraseFun);
	free(h);
	*Heap = NULL;
}

int sBinHeapEmpty(sBinomHeap* Heap)
{
	assert(Heap != NULL && "Heap cannot be null!\n");
	if(Heap == NULL)
		return 0;
	return (Heap->Size == 0) ? 1 : 0;
}

size_t sBinHeapSize(sBinomHeap* Heap)
{
	assert(Heap != NULL && "Heap cannot be null!\n");
	if(Heap == NULL)
		return 0;
	return Heap->Size;
}

int sBinHeapContains(sBinomHeap* Heap, void* Data, int (*cmp)(void*, void*))
{
	assert(Heap != NULL && "Heap cannot be null!\n");
	if(Heap == NULL)
		return 0;
	assert(cmp != NULL && "Compare function cannot be null!\n");
	if(Heap == NULL)
		return 0;
	assert(Data != NULL && "Data cannot be null!\n");
	if(Heap == NULL)
		return 0;
	
	return (sBTFindData(Heap->Head, Data, cmp) != NULL) ? 1 : 0;
}

void* sBinHeapFind(sBinomHeap* Heap, void* Data, int (*cmp)(void*, void*))
{
	assert(Heap != NULL && "Heap cannot be null!\n");
	if(Heap == NULL)
		return 0;
	assert(cmp != NULL && "Compare function cannot be null!\n");
	if(Heap == NULL)
		return 0;
	assert(Data != NULL && "Data cannot be null!\n");
	if(Heap == NULL)
		return 0;
	sBinomTree* T = sBTFindData(Heap->Head, Data, cmp);
	return (T != NULL) ? T->Data : NULL;
}
