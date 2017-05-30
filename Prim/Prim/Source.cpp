#include <stdio.h>
#include <limits.h>
#include <iostream>

// số đỉnh của đồ thị
#define  V 5
using namespace std;
// Một hàm tiện ích để tìm đỉnh với giá trị khóa cực tiểu từ
// tập các đỉnh không có trong MST
int minKey(int key[], bool mstSet[])
{
	// khởi tạo giá trị min
	int min = INT_MAX; int min_index=0;
	for (int v = 0; v < V;v++)
	{
		if (mstSet[v]==false&&key[v]<min)
		{
			min = key[v], min_index = v;
		}
		return min_index;
	}
}

//Một chức năng tiện ích để in các MST xây dựng được lưu trữ trong parent[]
int printMST(int parent[], int n, int graph[V][V])
{
	printf("Edge   Weight\n");
	for (int i = 1; i < V; i++)
		printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
	return 0;
}

//Chức năng để xây dựng và in MST cho một biểu đồ được biểu diễn bằng sự kề nhau
// biểu diễn ma trận
void primMST(int graph[V][V])
{
	int parent[V]; //Mảng để lưu trữ được xây dựng MST
	int key[V]; //Các giá trị chính được sử dụng để chọn cạnh trọng lượng tối thiểu trong cắt
	bool mstSet[V]; //Để đại diện cho tập các đỉnh không có trong MST

	//Khởi tạo tất cả các phím dưới dạng INFINITE
	for (int i = 0; i < V;i++)
	{
		key[i] = INT_MAX, mstSet[i] = false;
	}
	// Luôn bao gồm đỉnh đầu tiên thứ nhất trong MST.
	key[0] = 0; //Đặt phím 0 để đỉnh này được chọn là đỉnh đầu tiên
	parent[0] = -1; //Nút đầu tiên luôn luôn là gốc của MST

	//MST sẽ có đỉnh V
	for (int count = 0; count < V - 1;count++)
	{
		// Chọn đỉnh quan trọng tối thiểu từ tập các đỉnh
		//Chưa có trong MST
		int u = minKey(key, mstSet);

		// Thêm đỉnh đã chọn vào Bộ MST
		mstSet[u] = true;

		// Cập nhật giá trị khóa và chỉ mục cha của các đỉnh liền kề của
		// Đỉnh được chọn.Xem xét chỉ những đỉnh chưa được
		// Bao gồm trong MST
		for (int v = 0; v < V; v++)
		{
			//graph[u][v] Không phải là không chỉ cho các đỉnh liền kề của m
			//mstSet[v] Sai cho các đỉnh chưa có trong MST
			//Cập nhật khóa chỉ khi graph[u][v] nhỏ hơn key [v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
		}
		// in cây mst 
	}
	printMST(parent, V, graph);
}
int main()
{
	int graph[V][V] = { { 0, 2, 0, 6, 0 },
	{ 2, 0, 3, 8, 5 },
	{ 0, 3, 0, 0, 7 },
	{ 6, 8, 0, 0, 9 },
	{ 0, 5, 7, 9, 0 },
	};
	primMST(graph);
	return 0;
}

