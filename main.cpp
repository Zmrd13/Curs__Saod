#include "DOP.h"
#include "HUUFY.h"
#include "SEARCH.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <string.h>
#include <windows.h>
using namespace std;

int size_arr = 4000;
Node *root_, *search_root;


////////////////////////////////////////////////////////////ДОП а1


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

//////////////////////////////////////////////////////////////////////////////////////////////////// Поиск

//////////////////////////////////////////////////////////////////////////////////////////////

int *LR(MinHeapNode *x, char temp) {
    char *buffer = new char;
    if (x == NULL) return (NULL);
    LR(x->left, temp);
    FILE *mf;
    mf = fopen("text.txt", "ab");
    int i = 0;
    if (x->data == temp) {
        // std::cout<<x->data<<"===";
        while (i < x->top) {
            if (x->arr[i] >= 0) {
                if (x->arr[i] == 1) {
                    fputc('1', mf);
                }
                if (x->arr[i] == 0) {
                    fputc('0', mf);
                }
            }
            i++;
        }
    }
    fclose(mf);
    LR(x->right, temp);
}

int main() {
    SetConsoleCP(1251);
    set<wchar_t> x;

    root_ = 0;
    search_root = 0;
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
    int count = (end - begin);
    cout << "Length: " << count << " symbols.\n";
    f.close();
    FILE *file;
    file = fopen("testBase4.dat", "rb");

    wchar_t c = 0;
    wchar_t *tmp = new wchar_t[count];

    int p = 0;

    while (p <= count) {

        c = getc(file);
        tmp[p] = c;
        x.insert(c);
        //cout<<tmp[p]<<endl;
        p++;
    }
    for (auto i : x) {
        // cout << i << endl;
    }

    letter *arr = reading(x, count);
    cout << "\n";

    int h = x.size();
    p = 0;
    for (int l = 0; l <= count; l++) {

        for (int i = 0; i < h - 1; i++) {
            if (arr[i].let == tmp[l]) {
                arr[i].freq++;
            }
        }
    }
    double H = 0;
    for (int i = 0; i < h - 1; i++) {
        cout << " \n " << arr[i].let << "  " << arr[i].freq;
      H = H - (arr[i].freq / count) * log2(arr[i].freq / count);
        cout << "EHNTROPY:" << H << endl;
    }

    Huffsort(arr, h);
    float *mas = new float[h];
    char *let = new char[h];
    int j = 0;
    for (int i = 0; i < h; i++) {
        mas[j] = arr[i].freq;
        let[j] = arr[i].let;
        j++;
        //cout<<endl<<i<<": "<<arr[i].let;
    }
    j++;
    cout << "\nUNIQUE :" << h << "\n";
    free(arr);
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
        cout << "More ? yes 1/ no 2/ search 3/encrypt 4 ";
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
            arr_Search = new form[check];
            arr_Search = Print(q, check);
            int *w = new int[check];
            int *use = new int[check];
            for (int j = 0; j < check; j++) {
                w[j] = rand() % 200;
            }
            DOP_A1(root_, arr_Search, w, use, check);
            free(w);
            free(use);

            cout << "\n______________DOP A1 tree-----------------------\n";
            LR(root_);
            cout << "\nFlat number search: ";
            char in[3];
            cin >> in;

            SearchTree(&root_, &search_root, in);

            cout << "\n______________Search-----------------------\n";
            LR(search_root);
        }
        cout << "\n______________ENCRYPTING-----------------------\n";
        if (key == 4) {
            cout << j << "\n";
            HuffmanCodes(let, mas, j, count);
            cout << "EHNTROPY:" << H << endl;
            //            file=fopen("testBase4.dat","rb");
            //            c=0;
            //            *tmp=0;
            //
            //            p=0;

            //            while(p<count){
            //                c=fgetc(file);
            //                tmp[p]=c;
            //                LR(&root,tmp[p]);
            //                // cout<<tmp[p]<<endl;
            //                p++;
            //            //}

            //            fclose(file);
            return 0;
        }
    }
    delete[] Base;
}
