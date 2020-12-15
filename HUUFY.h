//
// Created by Weder on 15.12.2020.
//

#ifndef UNTITLED1_HUUFY_H
#define UNTITLED1_HUUFY_H
#include <iostream>
#define MAX_TREE_HT 100
struct letter{
    unsigned char let=0;
    float freq=0;

};
struct MinHeapNode {
    char data;

    unsigned freq;
    int *arr;
    int top;

    struct MinHeapNode *left, *right;
};

letter *reading(char *in,int n);
letter * frequencyCheck(letter *arr,int n);
void Huffcomparse(letter arr[], int n, int i);
void Huffsort(letter arr[], int n);
MinHeapNode* HuffmanCodes(char data[], float freq[], int code[],int size,float sub,MinHeapNode *x);
void printCodes(struct MinHeapNode* root, int arr[], int top,int code[],int size,float sub);
struct MinHeapNode* buildHuffmanTree(char data[], float freq[], int size);
struct MinHeap* createAndBuildMinHeap(char data[], float freq[], int size);
int isLeaf(struct MinHeapNode* root);
int * printArr(int arr[], int n,MinHeapNode* root);
void buildMinHeap(struct MinHeap* minHeap);
void insertMinHeap(struct MinHeap* minHeap,
                   struct MinHeapNode* minHeapNode);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
int isSizeOne(struct MinHeap* minHeap);
void minHeapify(struct MinHeap* minHeap, int idx);
void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b);
struct MinHeap* createMinHeap(unsigned capacity);

struct MinHeapNode* newNode(char data, unsigned freq);


#endif//UNTITLED1_HUUFY_H
