//
// Created by Weder on 15.12.2020.
//

#ifndef UNTITLED1_DOP_H
#define UNTITLED1_DOP_H
struct form {
    char sign[32];
    char street[18];
    short int house_num;
    short int flat_num;
    char date[10];
};
struct Node{
    form data;
    int w;
    Node *left,*right;
};

void addTree(Node** root, form D,int w);
void searchTreeE(Node** root,Node **prod, char *key);
void searchTree(Node** root,Node **prod, char *key);
void dopA1(Node* &root, form *arr,int *w,int *u,int n);
void LR(Node* x);

#endif//UNTITLED1_DOP_H
