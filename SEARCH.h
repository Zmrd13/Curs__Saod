//
// Created by Weder on 15.12.2020.
//

#ifndef UNTITLED1_SEARCH_H
#define UNTITLED1_SEARCH_H
#include <iostream>
#include "DOP.h"
#include <string.h>
#include <iomanip>
using namespace std;
struct list {
    form data;
    struct list *ptr;
};


struct Qu {
    struct list *frnt, *rear;
} ;

form* Print(Qu *Q, int N);
void init(struct Qu *q);
struct list *init(form a);
int binarySearchB( form arr[], char x[3], int n);
int binarySearchE( form arr[], char x[3], int n);
int Search(struct Qu *q, form arr[], char key[3], int n);


#endif//UNTITLED1_SEARCH_H
