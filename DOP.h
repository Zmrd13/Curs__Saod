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

void AddTree(Node** root, form D,int w);
void SearchTree_e(Node** root,Node **prod, char key[3]);
void SearchTree(Node** root,Node **prod, char key[3]);
void DOP_A1(Node* &root,form arr[],int w[],int *u,int n);
void LR(Node* x);

#endif//UNTITLED1_DOP_H
