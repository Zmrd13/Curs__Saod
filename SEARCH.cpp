//
// Created by Weder on 15.12.2020.
//

#include "SEARCH.h"
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