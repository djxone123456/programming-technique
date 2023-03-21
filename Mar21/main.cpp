#pragma pack(1)
#include <iostream>

using namespace std;

typedef struct
{
	int m, n, sizeItem;
	void* Data[1];
} aStruct;

static int headSize = sizeof(int) * 3;

int nRow(void** aData)
{
	aStruct* as = (aStruct*)((char*)aData - headSize);
	if (as != NULL) return as->m;
	return 0;
}

int nCol(void** aData)
{
	aStruct* as = (aStruct*)((char*)aData - headSize);
	if (as != NULL) return as->n;
	return 0;
}

void Free2D(void** aData)
{
	if (aData != NULL) {
		void* p = (char*)aData - headSize;
		free(p);
	}
}

void alloc2D(void*** a, int m, int n, int sz)
{
	if (m <= 0 || n <= 0 || sz <= 0)
		return;

	int szRow = n * sz;
	int sz1 = m * sizeof(void*);
	int sz2 = m * szRow;

	void* buf = calloc(headSize + sz1 + sz2, 1);

	if (buf == NULL) return;

	aStruct* as = (aStruct*)buf;
	as->m = m;
	as->n = n;
	as->sizeItem = sz;

	buf = (char*)buf + headSize + sz1;
	as->Data[0] = buf;

	for (int i = 1; i < m; i++)
	{
		buf = (char*)buf + szRow;
		as->Data[i] = buf;
	}
	*a = as->Data;
}

void arr2D_Input(int** A)
{
	int m = nRow((void**)A);
	int n = nCol((void**)A);
	if (A == NULL) return;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> A[i][j];
		}
	}
}

void arr2D_Output(int** const A)
{
	int m = nRow((void**)A);
	int n = nCol((void**)A);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << A[i][j] <<' ';
		cout << "\n";
	}

}

void main()
{
	int** A;
	int m, n;
	cout << "Nhap dong & cot: ";
	cin >> m >> n;

	alloc2D((void***)&A, m, n, sizeof(int));
	arr2D_Input(A);
	cout << "Ket qua:\n";
	arr2D_Output(A);
	Free2D((void**)A);
	return;
}
