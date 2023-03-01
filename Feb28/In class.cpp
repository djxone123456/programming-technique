//Bài làm trên lớp
// Group 12 - 22CTT4
#include <iostream>
using namespace std;

void InputArray_1D(int* &a, int& n);
void FreeArray_1D(int* &a);
void OutputArray_1D(int* a, int n);

void main()
{
    int n = 0;
    int* a = NULL;
    
    InputArray_1D(a, n);
    OutputArray_1D(a, n);
    FreeArray_1D(a);

    return;
}

void InputArray_1D(int* &a, int& n)
{
    cout << "Nhap n = ";
    cin >> n;

    if (n < 1) return;

    a = new int[n];

    if (a == NULL) return;
    
    cout << "Nhap cac phan tu cua mang (cach nhau boi dau cach): ";
    for (int i = 0; i < n; i++)
        cin >> a[i];
}

void FreeArray_1D(int* &a)
{
    delete[] a;
}

void OutputArray_1D(int* a, int n)
{
    cout << "Mang da nhap la: \n";
    for (int i = 0; i < n; i++)
        cout << a[i] << '\t';
}
