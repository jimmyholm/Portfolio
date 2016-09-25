/**
 * @file Stack.h
 * @Author Jimmy Holm
 * @date October 7, 2013
 * @brief A Generic Stack implementation.
 */
#ifndef STACK_H
#define STACK_H
#include <stdlib.h>

typedef struct sStack sStack;
/*! \brief Initialize a stack pointer
 *  \param Stack a reference to the stack pointer to be initialized. Must be NULL.
 *  \param ElementSize size of the data stored.
 *  \param EraseFun function used to deinitialized stored data.
 *  \returns Returns 1 upon successfully initiating Stack, 0 otherwise.
 *  Initializes a stack pointer, preparing it for use.
 */
int sStackInit(sStack** Stack, size_t ElementSize, void(*EraseFun)(void*));

/*! \brief Copies data onto the stack.
 *  \param Stack the stack to have data pushed onto.
 *  \param Data the data to be copied onto the stack.
 *  Pushes a copy of Data onto the top of the stack.
 */
void sStackPush(sStack* Stack, void* Data);

/*! \brief Retrieve the data on the top of the stack.
 *  \param Stack the stack pointer to peek into
 *  \return The data held by the top of the stack
 *  Returns the data held by the top of the stack.
 */
void* sStackPeek(sStack* Stack);

/*! \brief Remove the top-most element on the stack.
 *  \param Stack the stack which is to have its top element removed.
 *  The topmost element of Stack is removed, with EraseFun called on it to deinitialize prior to having its resources released.
 */
void sStackPop(sStack* Stack);

/*! \brief Return the number of elements on the stack.
 *  \param Stack the stack which size is requested.
 *  Returns the number of elements stored on the given stack.
 */
size_t sStackSize(sStack* Stack);

/*! \brief Destroy a stack pointer.
 *  \param Stack a reference to the stack pointer to be destroyed.
 *  Destroy a stack pointer, releasing all its stored resources and resetting the pointer to NULL.
 */
void sStackDestroy(sStack** Stack);
#endif // STACK_H
