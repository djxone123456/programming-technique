// Group 12 - 22CTT4
#include <iostream>
#include <memory>

using namespace std;

const int headSize = sizeof(int) + sizeof(int);

int memSize(int nItem, int szItem)
{
    return headSize + nItem * szItem;
}

void* origin_addr(void* aData)
{
    if (aData != NULL)
    {
        return (char*)aData - headSize;
    }
    return NULL;
}

void* data_addr(void* aOrigin)
{
    if (aOrigin != NULL)
    {
        return (char*)aOrigin + headSize;
    }
    return NULL;
}

void* sizeItem_addr(void* aData)
{

    if (aData != NULL)
    {
        return (char*)aData - sizeof(int);
    }
    return NULL;
}

int arrSize(void* aData)
{
    if (aData != NULL)
    {
        return *(int*)origin_addr(aData);
    }
    return 0;
}

int arrItemSize(void* aData)
{
    if (aData != NULL)
    {
        return *(int*)sizeItem_addr(aData);
    }
    return 0;
}

void* arrInit(int nItem, int szItem)
{
    int sz = memSize(nItem, szItem);
    void* aOrigin = malloc(sz);

    if (aOrigin != NULL)
    {
        memset(aOrigin, 0, sz);
        void* aData = data_addr(aOrigin);
        *(int*) origin_addr(aData) = nItem;
        *(int*)sizeItem_addr(aData) = szItem;
        return aData;
    }
    return NULL;
}

void* arrResize(void* aData, int nItem)
{
    if (aData == NULL || nItem < 0)
        return NULL;

    void* aOrigin = origin_addr(aData);
    int sizeItem = *(int*)sizeItem_addr(aData);
    int sz = memSize(nItem, sizeItem);
    void* aNew = realloc(aOrigin, sz);

    if (aNew != NULL)
    {
        aData = data_addr(aNew);
        *(int*)origin_addr(aData) = nItem;
        return aData;
    }

    return NULL;
}

int arrPushback(void** aData, void* x)
{
    int nItem = arrSize(*aData);
    int szItem = arrItemSize(*aData);

    void* aNew = arrResize(*aData, nItem + 1);

    if (aNew != NULL)
    {
        memmove((char*)aNew + nItem * szItem, x, szItem);
        *aData = aNew;
        return 1;
    }
    return 0;
}

void* arrPopback(void** aData)
{
    int nItem = arrSize(*aData);
    int szItem = arrItemSize(*aData);
    void* x = malloc(szItem);

    if (*aData != NULL && nItem > 0)
    {
        nItem--;
        memmove(x, (char*)(*aData) + nItem * szItem, szItem);
        void* aNew = arrResize(*aData, nItem);

        if (aNew != NULL)
        {
            *aData = aNew;
        }
    }
    return x;
}

void arrFree(void* aData)
{
    if (aData != NULL)
        free(origin_addr(aData));
}

struct SoPhuc
{
    float thuc, ao;
};

istream& operator >> (istream& input, SoPhuc &x)
{
    input >> x.thuc >> x.ao;
    return input;
}

ostream& operator << (ostream& output, SoPhuc& x)
{
    output << x.thuc;
    
    if (x.ao > 0)
    {
        output << " + " << x.ao << "i";
    }
    else if (x.ao < 0)
    {
        output << " - " << abs(x.ao) << "i";
    }

    return output;
}

SoPhuc* SoPhucArrIn()
{
    SoPhuc* a = (SoPhuc*)arrInit(0, sizeof(SoPhuc));

    SoPhuc x = { 0, 0 };

    while (cin >> x)
    {
        arrPushback((void**)&a, &x);
    }

    cin.clear();
    return a;
}

void SoPhucArrOut(SoPhuc* &a)
{
    int n = arrSize((void*) a);

    for (int i = 0; i < n; i++)
    {
        cout << *(a + i) << "\n";
    }
}

void main()
{
    cout << "Input complex items:\n";
    SoPhuc* B = SoPhucArrIn();
    SoPhuc* x = (SoPhuc*)arrPopback((void**)&B);
    cout << "After pop:\n";
    SoPhucArrOut(B);
    cout << "\nPopped element: " << *x << endl;
    free(x);
    arrFree(B);

    return;
}
