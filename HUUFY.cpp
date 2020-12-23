//
// Created by Weder on 15.12.2020.
//
#include <cmath>
#include "HUUFY.h"

using namespace std;
float EQ=0;
float  H=0;
int counter=0;

letter *reading(set<wchar_t>x,int n){
    letter *arr;
    arr=new letter[n];
int j=0;
   for(auto i:x){
       arr[j].let=i;
       j++;
   }
    return arr;
}
letter * frequencyCheck( letter *arr,const wchar_t *tmp,int n,int size){
for(int i=0;i<=size;i++){
    arr[i].freq=0;
}
for(int i=0;i<size;i++){
    for(int j=0;j<=n;j++){
if(arr[i].let==tmp[j]){
arr[i].freq++;
}
    }
}
    float d=0;
for(int i=0;i<=size;i++) {
    cout<<" \n "<<arr[i].let<<"  "<<arr[i].freq;
    }
    return arr;
}
void Huffcomparse(letter arr[], int n, int i) {
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int flag = 1;

    if (l < n && arr[l].freq<arr[max].freq) {
        max = l;
    }
    if (r < n && arr[r].freq<arr[max].freq ) {
        max = r;
    }

    if (max != i) {
        swap(arr[i], arr[max]);
        Huffcomparse(arr, n, max);
    }
}

void Huffsort(letter arr[], int n) {

    for (int i = n / 2 - 1; i >= 0; i--) {
        Huffcomparse(arr, n, i);

    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        Huffcomparse(arr, i, 0);

    }
}
struct MinHeap {

    unsigned size;

    unsigned capacity;

    struct MinHeapNode** array;
};


struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp
            = (struct MinHeapNode*)malloc
                    (sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}


struct MinHeap* createMinHeap(unsigned capacity)

{

    struct MinHeap* minHeap
            = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array
            = (struct MinHeapNode**)malloc(minHeap->
            capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}


void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)

{

    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->
            freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->
            freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}


int isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}


struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0]
            = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

void insertMinHeap(struct MinHeap* minHeap,
                   struct MinHeapNode* minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}


void buildMinHeap(struct MinHeap* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printArr(int arr[], int n,float freq)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}


int isLeaf(struct MinHeapNode* root)

{

    return !(root->left) && !(root->right);
}


struct MinHeap* createAndBuildMinHeap(char data[], float freq[], int size)

{

    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}


struct MinHeapNode* buildHuffmanTree(char data[], float freq[], int size)

{
    struct MinHeapNode *left, *right, *top;


    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);


    while (!isSizeOne(minHeap)) {


        left = extractMin(minHeap);
        right = extractMin(minHeap);


        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}


void printCodes(struct MinHeapNode* root, int arr[], int top,int n)

{




    if (root->left) {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1,n);
    }


    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1,n);
    }


    if (isLeaf(root)) {
        EQ+=top*(root->freq/(double)n);
        printf("%c: ", root->data);
        printArr(arr, top,n);
        cout<<endl<<H<<endl;
        cout<<endl<<counter<<endl;
counter++;

    }
}


void HuffmanCodes(char data[], float freq[], int size,int n)

{

    struct MinHeapNode* root
            = buildHuffmanTree(data, freq, size);


    int arr[MAX_TREE_HT], top = 0;
    double long d=0;

    printCodes(root, arr, top, n);

    cout<<"AVERAGE:"<<EQ<<endl;

}