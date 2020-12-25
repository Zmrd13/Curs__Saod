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

form*print(Qu *Q, int N);
void init(struct Qu *q);
struct list *init(form a);
int search(struct Qu *q, form *arr, char *key, int n);


#endif//UNTITLED1_SEARCH_H
