#include <string.h>
#include <assert.h>
#include "BinaryTree.h"

typedef struct sBSTNode
{
  long int Key;
  void* Data;
  struct sBSTNode* Left;
  struct sBSTNode* Right;
} sBSTNode;

typedef struct sBSTree
{
  size_t Size;
  size_t ElementSize;
  sBSTNode* Root;
  void(*EraseFun)(void*);
} sBSTree;


int sBSTInit(sBSTree** Tree, size_t ElementSize, void(*EraseFun)(void*))
{
  assert(*Tree == NULL && "Tree must be assigned NULL before initializing.\n");
  if(*Tree != NULL)
    return 0;
  *Tree = malloc(sizeof(sBSTree));
  (*Tree)->Size = 0;
  (*Tree)->ElementSize = ElementSize;
  (*Tree)->Root = NULL;
  (*Tree)->EraseFun = EraseFun;
  return 1;
}

void sBSTInsert(sBSTree* Tree, long int Key, void* Data, int Replace)
{
  assert(Tree != NULL && "Tree cannot be null!\n");
  if(Tree == NULL)
    return;
  if(Tree->Root == NULL)
  {
    sBSTNode* new = malloc(sizeof(sBSTNode));
    new->Data = malloc(Tree->ElementSize);
    memcpy(new->Data, Data, Tree->ElementSize);
    new->Key = Key;
    new->Left = NULL;
    new->Right = NULL;
    Tree->Root = new;
    Tree->Size++;
    return;
  }
  sBSTNode* Node = Tree->Root;
  while(Node != NULL)
  {
    if(Key == Node->Key)
    {
      if(Replace != 0)
      {
	if(Tree->EraseFun != NULL)
	  (*Tree->EraseFun)(Node->Data);
	free(Node->Data);
	Node->Data = malloc(Tree->ElementSize);
	memcpy(Node->Data, Data, Tree->ElementSize);
      }
      return;
    }
    else if(Key < Node->Key)
    {
      if(Node->Left == NULL)
      {
	sBSTNode* new = malloc(sizeof(sBSTNode));
	new->Data = malloc(Tree->ElementSize);
	memcpy(new->Data, Data, Tree->ElementSize);
	new->Key = Key;
	new->Left = NULL;
	new->Right = NULL;
	Node->Left = new;
	Tree->Size++;
	return;
      }
      else
      {
	Node = Node->Left;
      }
    }
    else
    {
      if(Node->Right == NULL)
      {
	sBSTNode* new = malloc(sizeof(sBSTNode));
	new->Data = malloc(Tree->ElementSize);
	memcpy(new->Data, Data, Tree->ElementSize);
	new->Key = Key;
	new->Left = NULL;
	new->Right = NULL;
	Node->Right = new;
	Tree->Size++;
	return;
      }
      else
      {
	Node = Node->Right;
      }
    }
  }
}

void* sBSTSearch(sBSTree* Tree, long int Key)
{
  assert(Tree != NULL && "Tree cannot be null!\n");
  if(Tree == NULL)
    return NULL;
  if(Tree->Root == NULL)
    return NULL;
  sBSTNode* Node = Tree->Root;
  while(Node != NULL)
  {
    if(Key == Node->Key)
      return Node->Data;
    else if(Key < Node->Key)
      Node = Node->Left;
    else
      Node = Node->Right;
  }
  return NULL;
}

int sBSTContains(sBSTree* Tree, long int Key)
{
  assert(Tree != NULL && "Tree cannot be null!\n");
  if(Tree == NULL)
    return 0;
  if(Tree->Root == NULL)
    return 0;
  sBSTNode* Node = Tree->Root;
  while(Node != NULL)
  {
    if(Key == Node->Key)
      return 1;
    else if(Key < Node->Key)
      Node = Node->Left;
    else
      Node = Node->Right;
  }
  return 0;
}


sBSTNode** sBSTFindMax(sBSTNode** Node)
{
  assert(*Node != NULL && "Node cannot be null!\n");
  if(*Node == NULL)
    return NULL;
  if((*Node)->Right == NULL)
    return Node;
  sBSTNode** ret = &(*Node)->Right;
  while((*ret) != NULL)
    ret = &(*ret)->Right;
  return ret;
}


void sBSTDelete(sBSTree* Tree, long int Key)
{
  assert(Tree != NULL && "Tree cannot be null!\n");
  if(Tree == NULL)
    return;
  if(Tree->Root == NULL)
    return;
  if(Tree->Size == 1)
  {
    if(Tree->Root->Key == Key)
    {
      if(Tree->EraseFun != NULL)
	(*Tree->EraseFun)(Tree->Root->Data);
      free(Tree->Root->Data);
      free(Tree->Root);
      Tree->Root = NULL;
      Tree->Size = 0;
    }
  }
  else
  {
    sBSTNode** chk = &Tree->Root;
    while(*chk != NULL)
    {
      if(Key == (*chk)->Key)
      {
	if((*chk)->Left == NULL && (*chk)->Right == NULL)
	{
	  sBSTNode* del = *chk;
	  if(Tree->EraseFun != NULL)
	    (*Tree->EraseFun)(del->Data);
	  free(del->Data);
	  *chk = NULL;
	  free(del);
	  Tree->Size--;
	}
        else if((*chk)->Left != NULL && (*chk)->Right == NULL)
	{
	  sBSTNode* del = *chk;
	  if(Tree->EraseFun != NULL)
	    (*Tree->EraseFun)(del->Data);
	  free(del->Data);
	  *chk = del->Left;
	  free(del);
	  Tree->Size--;
	}
	else if((*chk)->Right != NULL && (*chk)->Left == NULL)
	{
	  sBSTNode* del = *chk;
	  if(Tree->EraseFun != NULL)
	    (*Tree->EraseFun)(del->Data);
	  free(del->Data);
	  *chk = del->Right;
	  free(del);
	  Tree->Size--;
	}
	else
	{
  	  sBSTNode* del = *chk;
	  sBSTNode** replace = sBSTFindMax(&del->Left);
	  if(Tree->EraseFun != NULL)
	    (*Tree->EraseFun)(del->Data);
	  free(del->Data);
	  del->Data = (*replace)->Data;
	  free(*replace);
	  *replace = NULL;
	  Tree->Size--;	  
	}
	return;
      }
      else if(Key < (*chk)->Key)
	chk = &(*chk)->Left;
      else
	chk = &(*chk)->Right;
    }
  }
}

void sBSTDeleteLeaf(sBSTree* Tree, sBSTNode* Node)
{
  if(Node == NULL)
    return;
  if(Node->Left != NULL)
    sBSTDeleteLeaf(Tree, Node->Left);
  if(Node->Right != NULL)
    sBSTDeleteLeaf(Tree, Node->Right);
  if(Tree->EraseFun != NULL)
    (*Tree->EraseFun)(Node->Data);
  free(Node->Data);
  free(Node);
}

void sBSTDestroy(sBSTree** Tree)
{
  assert(*Tree != NULL && "Tree cannot be null!\n");
  if(*Tree == NULL)
    return;
  sBSTDeleteLeaf((*Tree), (*Tree)->Root);
  free(*Tree);
  *Tree = NULL;  
}

void sBSTInorder(void** arr, sBSTNode* Node, int* i)
{
  if(Node == NULL)
    return;
  sBSTInorder(arr, Node->Left, i);
  arr[*i] = Node->Data;
  (*i)++;
  sBSTInorder(arr, Node->Right, i);
}

void sBSTPreorder(void** arr, sBSTNode* Node, int* i)
{
  if(Node == NULL)
    return;
  arr[*i] = Node->Data;
  (*i)++;
  sBSTPreorder(arr, Node->Left, i);
  sBSTPreorder(arr, Node->Right, i);
}

void sBSTPostorder(void** arr, sBSTNode* Node, int* i)
{
  if(Node == NULL)
    return;
  sBSTPostorder(arr, Node->Left, i);
  sBSTPostorder(arr, Node->Right, i);
  arr[*i] = Node->Data;
  (*i)++;;
}

void** sBSTTraverse(sBSTree* Tree, char Order, size_t* Size)
{
  assert(Tree != NULL && "Tree cannot be null!\n");
  if(Tree == NULL)
    return NULL;
  if(Tree->Root == NULL)
    return NULL;
  if(Size != NULL)
    *Size = Tree->Size;
  if(Tree->Size == 1)
    return &Tree->Root->Data;
  void** ret = malloc(sizeof(void*) * (Tree->Size));
  int i = 0;
  if(Order == BSTTRAVERSE_INORDER)
  {
    sBSTInorder(ret, Tree->Root, &i);
  }
  else if(Order == BSTTRAVERSE_PREORDER)
  {
    sBSTPreorder(ret, Tree->Root, &i);
  }
  else
  {
    sBSTPostorder(ret, Tree->Root, &i);
  }
  return ret;
}

size_t sBSTSize(sBSTree* Tree)
{
  assert(Tree != NULL && "Tree cannot be null!\n");
  if(Tree == NULL)
    return 0;
  return Tree->Size;
}
