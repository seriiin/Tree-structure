//2018203043_최세린
//Visucal C++ 2017

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>


using namespace std;

//방향을 의미하는 배열이다. 
int V[4][2] = { { -1, 0 },{ 1, 0 },{ 0, 1 },{ 0, -1 } };

int Center(int n) { return n <= 1 ? 0 : 2 * Center(n / 4) + 1; }
int Depth(int n) { return n <= 7 ? 1 : 2 * Depth(n / 4); }

void rotated(vector<char> v, int i, int depth) {
	int width = 0;
	if (i < v.size())
	{
		rotated(v, 2 * i + 2, depth + 1);//재귀호출을 통해서 right subtree의 node에 접근
		width = depth * 2 + 1;
		cout.width(width);
		cout << v[i] << endl;
		rotated(v, 2 * i + 1, depth + 1);//재귀호출을 통해서 left subtree의 node에 접근
	}

}

void not_rotated(vector<char> v, int depth) {
	int j = 1;
	int width;
	for (int k = 0; k < v.size(); k++)
	{
		if (k == 0) {
			width = pow(2, depth);
			cout.width(width);
			cout << v[0] << endl;
			--depth;
		}
		//k의 parent가 모두 왼쪽이고, k도 왼쪽일 경우
		else if (k == pow(2, j) - 1) {
			width = pow(2, depth);
			cout.width(width);
			cout << v[k];
		}
		//출력되는 라인의 첫번재 요소가 아닌 경우
		else {
			width = pow(2, depth + 1);
			cout.width(width);
			cout << v[k];
			//k의 parent가 모두 오른쪽이고, k도 오른쪽일 경우
			if (k == pow(2, j + 1) - 2) {
				cout << endl;
				++j; --depth;
			}
		}
	}
	cout << endl;
}

char** H_array(int size) {//인자로 넘겨받은 size로 이차원 동적배열을 할당
	char **arr = new char*[size];
	for (int i = 0; i < size; ++i) {
		arr[i] = new char[size];
		memset(arr[i], 0, sizeof(char)*size); // 메모리 공간을 0으로 초기화 
	}
	return arr;
}

char ** H(char** H_tree, vector<char>& v, int node, int i, int j, int d, int U, int D, int R, int L) {
	if (node > v.size()) return NULL;
	H_tree[i][j] = v[node - 1];
	if (2 * node <= v.size()) {
		H_tree[i + d * V[L][0]][j + d * V[L][1]] = v[2 * node - 1];
		H(H_tree, v, 4 * node, i + d * (V[L][0] + V[U][0]),
			j + d * (V[L][1] + V[U][1]), d / 2, D, U, L, R);
		H(H_tree, v, 4 * node + 1, i + d * (V[L][0] + V[D][0]),
			j + d * (V[L][1] + V[D][1]), d / 2, U, D, R, L);
	}
	if (2 * node + 1 <= v.size()) {
		H_tree[i + d * V[R][0]][j + d * V[R][1]] = v[2 * node];
		H(H_tree, v, 4 * node + 2, i + d * (V[R][0] + V[D][0]),
			j + d * (V[R][1] + V[D][1]), d / 2, U, D, R, L);
		H(H_tree, v, 4 * node + 3, i + d * (V[R][0] + V[U][0]),
			j + d * (V[R][1] + V[U][1]), d / 2, D, U, L, R);
	}
	return H_tree;
}


void h_tree(char**& H_tree, vector<char> v, int size) {
	//H함수를 호출하여 h-tree형태의 배열로 저장한 이중포인터를 htree에 대입
	char**htree = H(H_tree, v, 1, Center(v.size()), Center(v.size()), Depth(v.size()), 0, 1, 2, 3);
	//htree를 출력
	for (int i = 0; i < size; ++i) {
		//cout << i << " ";
		for (int j = 0; j < size; ++j) {
			if (j == 0)
				cout.width(1);
			else
				cout.width(2);
			cout << htree[i][j];
		}
		cout << endl;
	}
	//메모리 해제
	for (int i = 0; i < size; ++i) { delete[] htree[i]; } delete[] htree;
}

int main(void) {
	char i;
	vector<char> v;
	string s;
	int lmt = 0;
	int depth = 1;
	int hSize = 1;
	int hhSize = 0;
	while (cin >> s) {
		++lmt;
		if (s == "DEL" && v.size() != 0) {
			pop_heap(v.begin(), v.end());//0번째 요소를 가장 뒤로 보낸 후, 나머지 원소들을 heap으로 정렬
			v.pop_back();//가장 마지막 요소 제거
		}
		else if (s == "INS"&& cin >> i)
		{
			if (((int)i > 47 && (int)i < 58) || ((int)i > 64 && (int)i < 91) || ((int)i > 96 && (int)i < 123) || (int)i == 63)
			{
				v.push_back(i);//i를 벡터의 마지막에 push
				push_heap(v.begin(), v.end());//heap으로 정렬
			}
		}
		else if (s == "EOI") {
			for (int k = 1; k < v.size(); k++)//v의 depth를 구함
				if (k == pow(2, depth) - 1) {
					++depth;
				}
			--depth;

			cout << "1. rotated form" << endl;
			rotated(v, 0, 0);
			cout << endl;
			cout << "2. not-rotated form" << endl;
			not_rotated(v, depth);
			cout << endl;
			cout << "3. H-tree form" << endl << endl;

			for (int k = 1; k < Depth(v.size()); k++)
				if (k == pow(2, hSize) - 1) {
					++hSize;
				}
			hhSize = pow(2, hSize + 1) - 1;//동적배열 사이즈
			char** H_tree = H_array(hhSize);//동적배열 할당
			h_tree(H_tree, v, hhSize);

			break;
		}
		if (lmt == 200)
			break;
	}

	return 0;
}
