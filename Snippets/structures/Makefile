CC = gcc
OBJ = LinkedList.o DynamicArray.o Stack.o BinaryTree.o BinomialHeap.o main.o
TARGET = structures
CFLAGS = -Wall -std=c99 -ggdb
PROFILE = 

release: CFLAGS = -O3 -std=c99
profile: PROFILE = -pg

.PHONY : all
all: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(PROFILE)

.PHONY : profile
profile: all

.PHONY : release
release: all

%.o : %.c
	$(CC) -c $(CFLAGS) $< $(PROFILE)

.PHONY : clean
clean:
	-rm $(TARGET) *.o
