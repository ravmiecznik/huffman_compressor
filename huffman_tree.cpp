/*
 * huffman_tree.cpp
 *
 *  Created on: 25 maj 2017
 *      Author: miecznik
 */

#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include <iomanip>
#include <sstream>
#include "huffman_tree.h"

// This constant can be avoided by explicitly calculating height of Huffman Tree
#define MAX_TREE_HT 0xFFFF

// A Huffman tree node
struct MinHeapNode
{
    Word data;  // One of the input characters
    uint32_t freq;  // Frequency of the character
    struct MinHeapNode *left, *right; // Left and right child of this node
};

// A Min Heap:  Collection of min heap (or Hufmman tree) nodes
struct MinHeap
{
    uint32_t size;    // Current size of min heap
    uint32_t capacity;   // capacity of min heap
    MinHeapNode **array;  // Array of minheap node pointers
};

// A utility function allocate a new min heap node with given character
// and frequency of the character
MinHeapNode* newNode(Word data, uint32_t freq)
{
    MinHeapNode* temp = (MinHeapNode*) malloc(sizeof(MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// A utility function to create a min heap of given capacity
MinHeap* createMinHeap(uint32_t capacity)
{
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;  // current size is 0
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(minHeap->capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// A utility function to swap two min heap nodes
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.
void minHeapify(MinHeap* minHeap, int idx)
{
    int smallest = idx;
    uint32_t left = 2 * idx + 1;
    uint32_t right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
      smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
      smallest = right;

    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if size of heap is 1 or not
int isSizeOne(MinHeap* minHeap)
{
    return (minHeap->size == 1);
}

// A standard function to extract minimum value node from heap
MinHeapNode* extractMin(MinHeap* minHeap)
{
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// A utility function to insert a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1)/2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->array[i] = minHeapNode;
}

// A standard funvtion to build min heap
void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(uint32_t arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)
{
    return !(root->left) && !(root->right) ;
}

// Creates a min heap of capacity equal to size and inserts all character of
// data[] in min heap. Initially size of min heap is equal to capacity
MinHeap* createAndBuildMinHeap(Word data[], uint32_t freq[], uint32_t size)
{
    MinHeap* minHeap = createMinHeap(size);
    for (uint32_t i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// The main function that builds Huffman tree
MinHeapNode* buildHuffmanTree(Word data[], uint32_t freq[], uint32_t size)
{
    MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity equal to size.  Initially, there are
    // modes equal to size.
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap))
    {
        // Step 2: Extract the two minimum freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3:  Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted node as
        // left and right children of this new node. Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the root node and the tree is complete.
    return extractMin(minHeap);
}



// Prints huffman codes from the root of Huffman Tree.  It uses arr[] to
// store codes
void printCodes(MinHeapNode* root, uint32_t arr[], uint32_t top, compress_stats* c_stats)
{
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1, c_stats);
    }

    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1, c_stats);
    }

    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (isLeaf(root))
    {	//put_word_content_to_cout(root->data, false, true);
    	//cout << " freq: " << root->freq << " code ";
    	//for(uint32_t i=0; i<top; i++)
    	//	cout << arr[i];
    	//cout << endl;
    	c_stats->total_size = c_stats->total_size + (root->freq*top);
        if(top > c_stats->max_dict_word_len)
        	c_stats->max_dict_word_len = top;
    }
}


// The main function that builds a Huffman Tree and print codes by traversing
// the built Huffman Tree
compress_stats generate_huffman_codes_for_array(Word data[], uint32_t freq[], uint32_t size)
{
   //  Construct Huffman Tree
   MinHeapNode* root = buildHuffmanTree(data, freq, size);

   // Print Huffman codes using the Huffman tree built above
   uint32_t arr[MAX_TREE_HT], top = 0;
   compress_stats c_stats = {0, 0};
   printCodes(root, arr, top, &c_stats);
   c_stats.total_size = c_stats.total_size/8;
   return c_stats;
}

