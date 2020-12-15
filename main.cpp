#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#define MAX_TREE_HT 100
using namespace std;
struct form {
    char sign[32];
    char street[18];
    short int house_num;
    short int flat_num;
    char date[10];
};
struct list {
    form data;
    struct list *ptr;
};
struct Node{
    form data;
    int w;
    Node *left,*right;
}*root_,*search_root;


struct Qu {
    struct list *frnt, *rear;
} qu;
struct letter{
       unsigned char let=0;
        float freq=0;

};


int size_arr = 4000;



////////////////////////////////////////////////////////////ДОП а1
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


///////////////////////////////////////////////////////////СОРТИРОВКА
void comparseStreet(form arr[], int n, int i) {
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && strcmp(arr[l].street, arr[max].street) > 0 && strcmp(arr[l].sign, arr[max].sign) == 0) {
        max = l;
    }
    if (r < n && strcmp(arr[r].street, arr[max].street) > 0 && strcmp(arr[r].sign, arr[max].sign) == 0) {
        max = r;
    }
    if (max != i) {
        swap(arr[i], arr[max]);
        comparseStreet(arr, n, max);
    }
}

void comparse(form arr[], int n, int i) {
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int flag = 1;

    if (l < n && strcmp(arr[l].sign, arr[max].sign) > 0) {
        max = l;
    }
    if (r < n && strcmp(arr[r].sign, arr[max].sign) > 0) {
        max = r;
    }

    if (max != i) {
        swap(arr[i], arr[max]);
        comparse(arr, n, max);
    }
}

void sort(form arr[], int n) {

    for (int i = n / 2 - 1; i >= 0; i--) {
        comparse(arr, n, i);
        comparseStreet(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        comparse(arr, i, 0);
        comparseStreet(arr, i, 0);
    }
}
/////////////////////////////////////////////Очередь
void init(struct Qu *q) {
    q->frnt = NULL;
    q->rear = 0;
}

struct list *init(form a)// а- значение первого узла
{
    struct list *lst;
    // выделение памяти под корень списка
    lst = (struct list *) malloc(sizeof(struct list));
    lst->data = a;
    lst->ptr = NULL;
    return (lst);
}

struct list *addelem(list *lst, form x) {
    struct list *temp, *p;
    temp = (struct list *) malloc(sizeof(list));
    p = lst->ptr;
    lst->ptr = temp;
    temp->data = x;
    temp->ptr = p;
    return (temp);
}

void insert(struct Qu *q, form x) {
    if ((q->rear == 0) && (q->frnt == 0)) {
        q->rear = init(x);
        q->frnt = q->rear;
    } else
        q->rear = addelem(q->rear, x);
}

//////////////////////////////////////////////////////////////////////////////////////////////////// Поиск
int binarySearchB( form arr[], char x[3], int n) {
    int l = 0;
    int r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;

        int res = -1;
        if ((strncmp(arr[m].sign, x, 3) == 0) && (strncmp(arr[m - 1].sign, x, 3) < 0)) {
            res = 0;
            cout << arr[m].sign << "\n ";
        }


        // Нашел
        if (res == 0) {
            return m;
        }

        if (strncmp(arr[m].sign, x, 3) < 0)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}
int binarySearchE( form arr[], char x[3], int n) {
    int l = 0;
    int r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;

        int res = -1;
        if ((strncmp(arr[m].sign, x, 3) == 0) && (strncmp(arr[m + 1].sign, x, 3) > 0)) {
            res = 0;
            cout << arr[m].sign << "\n ";
        }


        //Если он нашел искомое
        if (res == 0) {
            return m;
        }
        if (strncmp(arr[m].sign, x, 3) > 0)
            r = m + 1;
        else
            l = m - 1;
    }

    return -1;
}
int Search(struct Qu *q, form arr[], char key[3], int n) {
    int first = binarySearchB( arr, key, n )-1 ;
    int last = binarySearchE(arr, key, n );
    for (int i = first; i <= last; i++) {
        insert(q, arr[i]);
    }
    return (last - first);
}
//////////////////////////////////////////////////////////////////////////////////////////////
struct MinHeapNode {

    // One of the input characters
    char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child of this node
    struct MinHeapNode *left, *right;
};

// A Min Heap:  Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap {

    // Current size of min heap
    unsigned size;

    // capacity of min heap
    unsigned capacity;

    // Array of minheap node pointers
    struct MinHeapNode** array;
};

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
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

// A utility function to create
// a min heap of given capacity
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

// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)

{

    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.
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

// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0]
            = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

// A utility function to insert
// a new node to Min Heap
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

// A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)

{

    return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[], float freq[], int size)

{

    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[], float freq[], int size)

{
    struct MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity
    // equal to size.  Initially, there are
    // modes equal to size.
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap)) {

        // Step 2: Extract the two minimum
        // freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3:  Create a new internal
        // node with frequency equal to the
        // sum of the two nodes frequencies.
        // Make the two extracted node as
        // left and right children of this new node.
        // Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the
    // root node and the tree is complete.
    return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct MinHeapNode* root, int arr[], int top)

{

    // Assign 0 to left edge and recur
    if (root->left) {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (isLeaf(root)) {

        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(char data[], float freq[], int size)

{
    // Construct Huffman Tree
    struct MinHeapNode* root
            = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using
    // the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;

    printCodes(root, arr, top);
}


form* Print(Qu *Q, int N)//вывод начального элемента и забив в массив
{
    form *arr=new form[N];
    list *tmp = Q->frnt;
    int i;
    for (i = 0; i < N; i++) {

        cout << " *|-" << setw(5) << i + 1 << ") ";
        cout << tmp->ptr->data.sign << " ";
        cout << "ul." << tmp->ptr->data.street;
        cout << "d-" << tmp->ptr->data.house_num << "   ";
        cout << "kv-" << tmp->ptr->data.flat_num << "   ";
        cout << "data \"" << tmp->ptr->data.date << "\"  ";
        cout << endl;
        tmp = tmp->ptr;
        arr[i]=tmp->data;
    }
    return arr;
}
letter *reading(char *in,int n){
    letter *arr=0;
    arr=new letter[n];
    for(int i=0;i<n;i++){
        arr[i].let=0;
        arr[i].freq=0;

    }

    arr[0].let=in[0];
    arr[0].freq=1;

    for(int i=0;i<n;i++){
        arr[i].let=in[i];
        arr[i].freq=1;

          //cout<<" "<<i<<"-"<<arr[i].let;
    }
    return arr;
}
letter * frequencyCheck(letter *arr,int n){

    for(int i=0;i<n;i++){
        if(arr[i].let!=0){
            for(int j=i+1;j<n;j++){
                if(arr[i].let==arr[j].let){
                    arr[i].freq++;
                    arr[j].let=0;
                    arr[j].freq=0;
                }
            }}

        if(arr[i].freq>1){
         // cout<<arr[i].let<<" freq="<<arr[i].freq<<" ";
             }
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
int main() {
    root_=0;
    search_root=0;
    int n = 4000;
    struct Qu *q;
    q = new Qu;
    int key = 0;
    form *Base = new form[size_arr];
    form *arr_Search;
    ifstream fin("testBase4.dat", ios::binary);
    fin.read((char *) Base, size_arr * sizeof(form));

    fin.close();
    streampos begin, end;
    ifstream f("testBase4.dat");
    begin = f.tellg();
    f.seekg(0, ios::end);
    end = f.tellg();
    int count=(end - begin);
    cout << "Length: " <<count<< " symbols.\n";
    f.close();
    FILE *file;
    file=fopen("testBase4.dat","rb");

    char c=0;
    char *tmp=new char[count];

    int p=0;

    while(p<count){

        c=fgetc(file);
        tmp[p]=c;

      // cout<<tmp[p]<<endl;
        p++;

    }
    letter *arr=reading(tmp,count);
    cout<<"\n";
    arr=frequencyCheck(arr,count);
int h=0;
    for(int i=0;i<count;i++){
        if(arr[i].freq>=1){
            h++;
           // cout<<"'"<<arr[i].let<<"' "<<arr[i].freq/count;

            //cout<<"1";
}
    }
   // cout<<"\n h"<<h;

    Huffsort(arr,h);
    float *mas=new float[h];
char *let=new char[h];
    int j=0;
    for(int i=h;i>0;i--){
        if(arr[i].freq>1){
            //out<<" "<<arr[i].let;
            mas[j]=arr[i].freq;
            let[j]=arr[i].let;
j++;
            //cout<<"1";
        }
    }
    int size = sizeof(let) / sizeof(let[0]);
    cout<<"\nUNIQUE :"<<size<<"\n";
    for(int i=0;i<j;i++){
        cout<<mas[i]<<endl;

    }
    free(arr);
HuffmanCodes(let,mas,j);
    fclose(file);

    sort(Base, n);
    int temp = 20, i = 0;

    while (1) {
        for (i; i < temp; i++) {
            cout << setw(5) << i + 1 << ") ";
            cout << Base[i].sign << " ";
            cout << "ul." << Base[i].street;
            cout << "d-" << Base[i].house_num << "   ";
            cout << "kv-" << Base[i].flat_num << "   ";
            cout << "data \"" << Base[i].date << "\" ";
            cout << endl;
        }
        cout << "More ? yes 1/ no 2/ search 3: ";
        cin >> key;
        if (key == 2) {
            delete[] Base;
            exit(0);
        }
        if (key == 3) {
            init(q);
            char key_word[3];
            cout << "First 3 letters:\n";
            cin >> key_word;
            int check = 0;
            check = Search(q, Base, key_word, n);
            cout << "\n______________Queue-----------------------\n";
            arr_Search=new form[check];
           arr_Search=Print(q, check);
           int *w=new int [check];
            int *use=new int [check];
            for (int j=0; j < check; j++) {
                w[j]=rand()%200;
            }
            DOP_A1(root_,arr_Search,w,use,check);
            cout << "\n______________DOP A1 tree-----------------------\n";
           LR(root_);
           cout<<"\nFlat number search: ";
           char in[3];
           cin>>in;

           SearchTree(&root_,&search_root,in);

            cout << "\n______________Search-----------------------\n";
            LR(search_root);
            cout << "\n______________Search sequence complete-----------------------\n";
        }
        temp += 20;
    }
    delete[] Base;
}
