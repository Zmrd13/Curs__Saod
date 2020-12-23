//
// Created by Weder on 15.12.2020.
//

#ifndef UNTITLED1_HUUFY_H
#define UNTITLED1_HUUFY_H
#include <iostream>
#include<set>
using namespace std;
#define MAX_TREE_HT 60
struct letter{
    unsigned char let=0;
     double freq=0;

};
struct MinHeapNode {
    char data;
    unsigned freq;
    int *arr;
    int top;

    struct MinHeapNode *left, *right;
};

letter *reading(set<wchar_t>x,int n);
letter * frequencyCheck(letter *arr,const wchar_t *tmp,int n,int size);
void Huffcomparse(letter arr[], int n, int i);
void Huffsort(letter arr[], int n);
void HuffmanCodes(char data[], float freq[],int size,int n);


#endif//UNTITLED1_HUUFY_H
