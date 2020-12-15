//
// Created by Weder on 15.12.2020.
//

#include "DOP.h"
#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;
void AddTree(Node** root, form D,int w)
{
    if ((*root) == NULL)
    {
        (*root) = (Node*) malloc(sizeof(Node));
        (*root)->data = D;
        (*root)->w=w;
        (*root)->left = (*root)->right = NULL;
    }
    else if (strcmp((*root)->data.street, D.street) < 0)
    {
        AddTree(&((*root)->right), D,w);
    }
    else if (strcmp((*root)->data.street, D.street) > 0)
    {
        AddTree(&((*root)->left), D,w);
    }
    else {
        if (strcmp((*root)->data.sign, D.sign) < 0)
        {
            AddTree(&((*root)->right), D,w);
        }
        else if (strcmp((*root)->data.sign, D.sign) > 0)
        {
            AddTree(&((*root)->left), D,w);
        }
    }
}
void SearchTree_e(Node** root,Node **prod, char key[3])
{
    if ((*root) == NULL)
    {
        return ;
    }
    SearchTree_e(&((*root)->right),prod,key);
    SearchTree_e(&((*root)->left),prod,key);
    if (strncmp((*root)->data.street, key,3) == 0)
    {
        AddTree(prod,(*root)->data,(*root)->w);

    }


}
void SearchTree(Node** root,Node **prod, char key[3])
{
    if ((*root) == NULL)
    {
        cout<<"Not found\n\n";
        return ;
    }

    else if (strncmp((*root)->data.street, key,3) < 0)
    {
        SearchTree(&((*root)->right),prod,key);
    }
    else if (strncmp((*root)->data.street, key,3) > 0)
    {
        SearchTree(&((*root)->left),prod,key);
    }
    else {

        AddTree(prod,(*root)->data,(*root)->w);
        SearchTree_e(&(*root),prod,key);
        return;

    }

}


void DOP_A1(Node* &root,form arr[],int w[],int *u,int n){
    for(int i=0;i<n;i++){
        u[i]=0;
    }
    for(int i=0;i<n;i++){
        int max=0,INDEX=0;
        for(int j=0;j<n;j++){
            if(w[j]>max && u[j]==0){
                max=w[j];
                INDEX=j;
            }
        }
        u[INDEX]=1;
        //cout<<w[INDEX]<<endl;
        AddTree(&root,arr[INDEX],w[INDEX]);
    }
}


void LR(Node* x)
{
    if (x == NULL) return;
    LR(x->left);
    cout << x->data.sign << " ";
    cout << "ul." << x->data.street;
    cout << "d-" << x->data.house_num << "   ";
    cout << "kv-" <<setw(4)<< x->data.flat_num << "   ";
    cout << "data \"" <<setw(10)<< x->data.date << " ";
    cout << "weight \"" << x->w << "\" ";
    cout << endl;
    LR(x->right);
}

