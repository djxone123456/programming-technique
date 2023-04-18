#include <iostream>

using namespace std;
typedef long long ll;

ll Tich(int a[], int n)
{
	if (n == 0) return a[0];
	return Tich(a, n - 1) * a[n];
}

bool ngto(int n)
{
	if (n < 2) return 0;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0) return 0;
	return 1;
}

void VitriNT(int a[], int n)
{
	if (n < 0) return;

	if (ngto(a[n]) == 1) cout << n << ' ';
	VitriNT(a, n - 1);
}

ll TichNT(int a[], int n)
{
	if (n < 0) return 1;

	if (ngto(a[n]) == 1) return a[n] * TichNT(a, n - 1);
	return TichNT(a, n - 1);
}

bool CoDangTangKhong(int a[], int n)
{
	if (n <= 0) return 1;

	if (CoDangTangKhong(a, n - 1) == 0) return 0;
	if (a[n - 1] <= a[n]) return 1;
	else return 0;
}

int main()
{
	int a[] = {1,2,3,4,5,6,7 };
	int n = sizeof(a) / sizeof(a[0]);

	cout << "Tich cua mang la: " << Tich(a, n - 1);
	cout << "\nVi tri cac so nguyen to la: ";
	VitriNT(a, n - 1);
	cout << "\nTich so nguyen to la: " << TichNT(a, n - 1);

	if (CoDangTangKhong(a, n - 1) == 1) cout << "\nMang co tang";
	else cout << "\nMang khong tang";
}
