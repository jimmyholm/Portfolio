/**
 * @file DynamicArray.h
 * @Author Jimmy Holm
 * @date October 7, 2013
 * @brief A Generic Dynamic Array implementation.
 */
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdlib.h>

typedef struct sDynamicArray sDynamicArray;

/*! \brief Initialize an Array object
 *  \param Array reference to the Array instance to be initialized. The Array instance should be set to NULL before being passed to the function.
 *  \param Size the number of elements to allocate for at initialization
 *  \param ElementSize the size, in bytes, of a single stored element
 *  \param EraseFun a function pointer to a function used to deinitialize a stored object before it's freed.
 *  \return 1 upon successfully creating and initializing, 0 otherwise
 *  Creates a useable Array object of a given size.
 */
int dArrayInit(sDynamicArray** Array, size_t Size, size_t ElementSize, void(*EraseFun)(void*));

/*! \brief Destroy a previously initialized array.
 *  \param Array reference to a previously initialized Array instance
 *  Erase all valid elements in the array and reset the Array instance pointer
 */
void dArrayDestroy(sDynamicArray** Array);

/*! \brief Set the value stored at a given index in the array
 *  \param Array pointer to an initialized array instance.
 *  \param Index index into the array to be updated.
 *  \param Data void pointer to the data to be copied into the array.
 *  \param Erase boolean value to determine whether the data already stored should be erased and freed.
 *  dArraySet sets the stored value of an array element to a new value Data. If Erase is set to 1, the data already stored will be freed.
 */
void dArraySet(sDynamicArray* Array, size_t Index, void* Data, int Erase);

/*! \brief Get the data stored at a given index in the array
 *  \param Array pointer to an initialized array instance.
 *  \param Index index into the array to be update.
 *  dArrayGet returns the data stored at a given index.
 */
void* dArrayGet(sDynamicArray* Array, size_t Index);

/*! \brief Erase the data stored at a given index in the array

 *  \param Array pointer to an initialized array instance.
 *  \param Index the index of the array element to erase
 *  dArrayErase erases the data stored at a given index
 */
void dArrayErase(sDynamicArray* Array, size_t Index);

/*! \brief Erase all elements in the array, without resizing it.
 *  \param Array to be cleared.
 *  dArrayClear erases all the elements stored in the array without resizing the array.
 */
void dArrayClear(sDynamicArray* Array); 

/*! \brief Resize the array to fit more or fewer elements.
 *  \param Array pointer to an initialized array instance
 *  \param NewSize the size, in maximum number of elements, of the array.
 *  dArrayResize returns 1 on successful resize, 0 otherwise.
 */
int dArrayResize(sDynamicArray* Array, size_t NewSize);


/*! \brief Return the maximum number of elements the given array fits.
 *  \param Array pointer to an initialized array instance
 *  \return The maximum number of elements the given array can store.
 *  dArraySize returns the maximum number of elements the given array fits.
 */
int dArraySize(sDynamicArray* Array);

/*! \brief Add data to the first available element slot, resizing if necessary.
 *  \param Array pointer to an initialized array instance
 *  \param Data void pointer to the data to be copied.
 *  \param Erase boolean value to determine whether the data already stored should be erased and freed.
 *  \return Returns the index of the newly added element.
 *  dArrayAdd adds a copy of the given data to the array, resizing the array if necessary.
 */
int dArrayAdd(sDynamicArray* Array, void* Data, int Erase);
#endif // DYNAMICARRAY_H
