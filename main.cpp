#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
struct form {
    char sign[32];
    char street[18];
    short int house_num;
    short int flat_num;
    char date[10];
};
int size_arr = 4000;
void comparseSign(form arr[], int n, int i)
{
    int max = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && arr[l].sign[0] > arr[max].sign[0]){
        max = l;}
    if (r < n && arr[r].sign[0] > arr[max].sign[0]){
        max = r;}
    if (max != i)
    {
        swap(arr[i], arr[max]);
        comparseSign(arr, n, max);
    }
}
void comparseStreet(form arr[], int n, int i)
{
    int max = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && arr[l].street[0] > arr[max].street[0]){
        max = l;}
    if (r < n && arr[r].street[0] > arr[max].street[0]){
        max = r;}
    if (max != i)
    {
        swap(arr[i], arr[max]);
        comparseStreet(arr, n, max);
    }
}

void sort(form arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--){
        comparseSign(arr, n, i);
}
    for (int i=n-1; i>0; i--)
    {
        swap(arr[0], arr[i]);
        comparseSign(arr, i, 0);
    }

    for (int i = n / 2 - 1; i >= 0; i--){
        comparseSign(arr, n, i);}

    for (int i=n-1; i>0; i--)
    {
        swap(arr[0], arr[i]);
        comparseSign(arr, i, 0);
    }
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
    cout<<"More ? yes 1/ no 0";
    cin>>key;
    if(key==0){
        delete[]Base;
        exit(0);
    }
    temp+=20;
    }
    delete[]Base;
}
