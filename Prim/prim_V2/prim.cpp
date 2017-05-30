#include < stdio.h > 
#include <iostream>
#include <fstream>
using namespace std;
#define max 100

typedef struct Egde {
	int x, y;

};

//doc du lieu tu tap tin
void Doc_File(int A[max][max], int & n) {
	ifstream f;
	f.open("input.txt", ios::in);
	f >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) 
		{
			f >> A[i][j];
		}
	}
	f.close();
}

//xuat du lieu ra tap tin
void Ghi_File(Egde L[max], int n, int Sum) {
	ofstream Output("output.txt");
	Output << Sum<<"\n";
	for (int i = 0; i < n - 1;i++)
	{
		Output << L[i].x + 1 << "-" << L[i].y + 1<<"\n";
	}
	Output.close();
}

//thuat toan Prim
void Prim(int A[max][max], int n) {
	char D[max];
	Egde L[max];
	int min = INT_MAX, Dem = 0, Sum = 0;
	for (int i = 0; i < n; i++)
		D[i] = 0;
	for (int j = 1; j < n; j++)
		if (min > A[0][j] && A[0][j] != 0) {
			min = A[0][j];
			L[0].y = j;
		}
	L[0].x = 0;
	D[0] = 1;
	D[L[0].y] = 1;
	Sum += min;
	Dem++;
	do {
		min = INT_MAX;
		for (int i = 0; i < n; i++)
			if (D[i] == 1) for (int j = 0; j < n; j++)
				if (A[i][j] > 0 && min > A[i][j] && D[j] == 0) {
					min = A[i][j];
					L[Dem].x = i;
					L[Dem].y = j;
				}
		Sum += min;
		D[L[Dem].y] = 1;
		Dem++;
	} while (Dem < n - 1);
	Ghi_File(L, n, Sum);
}

//chuong trinh chinh
void main() {
	int A[max][max], n;
	Doc_File(A, n);
	Prim(A, n);
}
/*
Mô tả bài toán :

Cho đồ thị vô hướng có trọng số G = (V, E) hãy tìm đường đi sao cho tất cả các đỉnh điều có đường đi với nhau và tổng trọng số của đường đi là nhỏ nhất.
Tức là tìm đồ thị con liên thông G' của G sao cho tổng trọng số của G’ là nhỏ nhất.

Ý tưởng thuật toán :

Bước 1 : Xuất phát từ đỉnh k bất kỳ(thông thường chọn đỉnh đầu tiên) chọn một cạnh có trọng số nhỏ nhất liền kề với đỉnh k(min{ A[k][j] }j = 1..n) 
ta đánh dấu 2 đỉnh đi qua cạnh đó và số cạnh tìm được là 1. Chuyển sang Bước 2.

Bước 2 : Tìm cạnh nhỏ nhất của đồ thị với điều kiện cạnh tìm được phải có 1 đỉnh chưa đánh dấu và 1 đỉnh đã đánh dấu.Nghĩa là, ta tìm min{ A[i][j] }j = 1..n, i = 1..n 
sao cho i đánh đấu và j chưa đánh dấu để tránh trường hợp tạo thành chu trình con.
Ta tăng số cạnh tìm được lên 1 và chuyển sang Bước 3.

Bước 3 : Nếu số cạnh tìm được bằng n - 1 kết thúc thuật toán, ngược lại quay về Bước 2.

Mô tả dữ liệu đầu vào và đầu ra của bài toán :

+Dữ liệu vào : lưu trong tập tin Input.txt
- Dòng đầu ghi số n là số đỉnh của một đồ thị(0 < n < 100)
- Dòng i + 1 (1 < i < n) lưu ma trận kề của đồ thị với n số A[i, 1], A[i, 2]…A[i, n] mỗi số cách nhau bởi một khoảng trắng.

+ Dữ liệu ra : lưu trong file Output.txt
- Dòng đầu ghi trọng số nhỏ nhất của cây bao trùm.
- Các dòng còn lại lưu đường đi giữa đỉnh i nối với đỉnh j.*/
