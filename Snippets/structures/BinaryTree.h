/**
 * @file BinaryTree.h
 * @Author Jimmy Holm
 * @date October 7, 2013
 * @brief A Generic binary tree implementation.
 */
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <stdlib.h>

#define BSTTRAVERSE_INORDER  (char)0
#define BSTTRAVERSE_PREORDER (char)1
#define BSTTRAVERSE_POSTORDER (char)2

typedef struct sBSTree sBSTree;

/*! \brief Initialize a Binary Search Tree instance
 *  \param Tree a reference to the tree instance to be initialized.
 *  \param ElementSize size in bytes of the data stored by the tree.
 *  \param EraseFun pointer to a function used to deinitialize stored elements prior to deletion.
 *  \return 1 upon successful initialization, 0 otherwise.
 *  At the end of a successful function call, Tree will contain an initialized sBSTree instance.
 */
int sBSTInit(sBSTree** Tree, size_t ElementSize, void(*EraseFun)(void*));

/*! \brief Insert a copy of data into the tree.
 *  \param Tree a pointer to the tree instance to insert into.
 *  \param Data the data to be copied into the tree.
 *  Inserts a copy of the given data into the tree. If the key exists and Replace is non-null, the data of the existing node will be replaced with a copy of the data given.
 */
void sBSTInsert(sBSTree* Tree, long int Key, void* Data, int Replace);

/*! \brief Search for a given key in the tree
 *  \param Tree a pointer to the tree instance to search in
 *  \param Key the key to be searched for.
 *  \return Returns a pointer to the stored data if found, or NULL if not found.
 *  Searches the tree for a given key, returning the data pointer.
 */
void* sBSTSearch(sBSTree* Tree, long int Key);

/*! \brief Checks if the tree contains a given key.
 *  \param Tree a pointer to the tree instance to search in
 *  \param Key the key to be searched for
 *  \return 1 if the key exists in the tree, 0 if it does not.
 *  Examines the tree, returning a boolean value regarding the existence of a given key. */
int sBSTContains(sBSTree* Tree, long int Key);

/*! \brief Delete a node from the tree, given its key
 *  \param Tree a pointer to the tree instance to delete from
 *  \param Key the key of the node to be deleted
 * Deletes a node from the tree
 */
void sBSTDelete(sBSTree* Tree, long int Key);

/*! \brief Traverses the tree based on a given order.
 *  \param Tree a pointer to the tree instance to traverse
 *  \param Order the traversing order to use
 *  \remark Order can be one of BSTTRAVERSE_INORDER, BSTTRAVERSE_PREORDER or BSTTRAVERSE_POSTORDER.
 *  \param Size if not null, this will contain the number of elements in the array.
 *  \return An n-sized array, where n is the number of nodes in the tree, containing every node's data, sorted by traversation order.
 *  Traverses the tree based on a given order, returning an array containing each node's data.
 */
void** sBSTTraverse(sBSTree* Tree, char Order, size_t* Size);

/*! \brief Delete every node in the given tree as well as the tree itself. Deinitializes all initialized data.
 *  \param Tree reference to the tree instance to be destroyed.
 *  Will delete the entire tree and release all used resources. Upon exiting, the provided Tree pointer will point to NULL.
 */
void sBSTDestroy(sBSTree** Tree);

/*! \brief Returns the number of nodes in a given tree.
 *  \param Tree pointer to an initialized tree instance
 *  \return The number of nodes in the given tree
 *  Returns the number of nodes in a given tree
 */
size_t sBSTSize(sBSTree* Tree);
#endif // BINARYTREE_H
