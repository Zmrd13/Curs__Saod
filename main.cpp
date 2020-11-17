#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <queue>
using namespace std;
struct form {
    char sign[32];
    char street[18];
    short int house_num;
    short int flat_num;
    char date[10];
};
queue<form>q;
int size_arr = 4000;

void comparseStreet(form arr[], int n, int i) {
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int flag = 1;


    if (l < n && strcmp(arr[l].street, arr[max].street) > 0 &&strcmp(arr[l].sign,arr[max].sign)==0) {
        max = l;
    }
    if (r < n && strcmp(arr[r].street, arr[max].street) > 0 && strcmp(arr[r].sign,arr[max].sign)==0) {
        max = r;
    }

    if (max != i) {
        swap(arr[i], arr[max]);
        comparseStreet(arr, n, max);


    }
}

void comparse(form arr[], int n, int i)
{
    int max = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    int flag = 1;

    if (l < n && strcmp(arr[l].sign,arr[max].sign)>0) {
        max = l;
    }
    if (r < n && strcmp(arr[r].sign,arr[max].sign)>0) {
        max = r;
    }

    if (max != i)
    {
        swap(arr[i], arr[max]);
        comparse(arr, n, max);

    }

}
void sort(form arr[], int n) {

    for (int i = n / 2 - 1; i >= 0; i--){

        comparse(arr, n, i);
       comparseStreet(arr, n, i);
    }
    for (int i=n-1; i>0; i--)
    {
        swap(arr[0], arr[i]);
        comparse(arr, i, 0);
       comparseStreet(arr, i, 0);
    }

}
int Search(form arr[],char key[3]){
    int check=0;
    for(int i;i<4000;i++){
        if(strncmp(arr[i].sign,key,3)==0){
            if(check==0){
                check=i;
            }
           q.push(arr[i]);
        }
    }
    return(check);
}
void print_queue(queue<form>q,int i)
{form temp;

    while (!q.empty())
    {
        temp=q.front();
        cout<<setw(5)<<i<<") ";
        cout << temp.sign << " ";
        cout<< "ul." <<temp.street ;
        cout<< "d-" << temp.house_num << "   ";
        cout << "kv-"<< temp.flat_num << "   ";
        cout << "data \""<< temp.date << "\" ";
        cout << endl;
        q.pop();
        i++;
    }
    std::cout << std::endl;
}


int main() {

    int key=0;
    form *Base = new form[size_arr];
    ifstream fin("testBase4.dat", ios::binary);
    fin.read((char *) Base, size_arr * sizeof(form));
    fin.close();
    sort(Base,4000);
    int temp=20,i=0;
    while(1){
        for (i ; i < temp; i++) {
            cout<<setw(5)<<i+1<<") ";
            cout << Base[i].sign << " ";
            cout<< "ul." << Base[i].street ;
            cout<< "d-" << Base[i].house_num << "   ";
            cout << "kv-"<< Base[i].flat_num << "   ";
            cout << "data \""<< Base[i].date << "\" ";
            cout << endl;
        }
        cout<<"More ? yes 0/ no 1";
        cin>>key;
        if(key==1){
            delete[]Base;
            exit(0);
        }
        if(key==3){
            char *word=new char[3];
            cin>>word;
            int j=Search(Base,word);
print_queue(q,j);
                delete[]Base;
                exit(0);
            }
        temp+=20;
    }
    delete[]Base;
}
