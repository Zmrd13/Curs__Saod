#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

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
struct Qu {
    struct list *frnt, *rear;
} queue;
int size_arr = 4000;

void comparseStreet(form arr[], int n, int i) {
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int flag = 1;


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

void init(struct Qu *q) {
    q->frnt = NULL;
    q->rear = 0;
}

struct list *init(form a) // а- значение первого узла
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

int Search(struct Qu *q, form arr[], char key[3]) {
    int check = 0;
    for (int i; i < 4000; i++) {
        if (strncmp(arr[i].sign, key, 3) == 0) {

            check++;
            insert(q, arr[i]);
        }
    }
    return (check);
}

void Print(Qu *Q, int N) //вывод начального элемента
{
    list *tmp = Q->frnt;
    int i;
    for (i = 0; i < N; i++) {
        cout << setw(5) << i + 1 << ") ";
        cout << tmp->ptr->data.sign << " ";
        cout << "ul." << tmp->ptr->data.street;
        cout << "d-" << tmp->ptr->data.house_num << "   ";
        cout << "kv-" << tmp->ptr->data.flat_num << "   ";
        cout << "data \"" << tmp->ptr->data.date << "\" ";
        cout << endl;
        tmp = tmp->ptr;
    }
}

int main() {
    struct Qu *q;
    q = new Qu;
    int key = 0;
    form *Base = new form[size_arr];
    ifstream fin("testBase4.dat", ios::binary);
    fin.read((char *) Base, size_arr * sizeof(form));
    fin.close();
    sort(Base, 4000);
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
        cout << "More ? yes 0/ no 1";
        cin >> key;
        if (key == 1) {
            delete[]Base;
            exit(0);
        }
        if (key == 3) {
            init(q);
            char key_word[3];
            cout << "First 3 letters:\n";
            cin >> key_word;
            int check = 0;
            check = Search(q, Base, key_word);
            cout << endl << check << " Forms\n";
            Print(q, check - 1);
            cout << "\n______________Result-----------------------\n";
        }
        temp += 20;
    }
    delete[]Base;
}
