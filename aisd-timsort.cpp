#include <iostream>
/*� ���������� ������ ���� ��������� ��� �������� �������� ���������: 
+���������� ���������, +?����� ������������������� run, +������� minrun, 
+������� ������������������� run, ����� ������ ��� �������.*/

using namespace std;

//���������� ��������� - ���
void insertionsort(int arr[], int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		int temp = arr[i];
		int j = i - 1;
		while (j >= left && arr[j] > temp) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}
//������ - ���
int minrunlenght(int n) {
	bool flag = 0;
	while (n >= 64) {
		flag |= n & 1;
		n >>= 1;
	}
	return n + flag;
}
int binSearch(int arr[] , int key, int lenght) {  // ��������� �������� �����
	int l = -1;                      // l, r � ����� � ������ �������
	int r = lenght;
	int m;
	while (l < r - 1) {                // ��������� ����
		m = (l + r) / 2;            // m � �������� ������� ������
		if (arr[m] < key) { l = m; }
		else
			r = m;
	}                  // ������� ������
	return r;
}
//������� ����� - ���
void merge(int arr[], int l, int m, int r){
	int len1 = m - l + 1, len2 = r - m;
	int* left = new int[len1];
	int* right = new int[len2];
	for (int i = 0; i < len1; i++)
		left[i] = arr[l + i];
	for (int i = 0; i < len2; i++)
		right[i] = arr[m + 1 + i];
	//gallop?
	/*if (left[len1 - 1] <= right[0]) {//������ ����� ������ ������ ������ ������
		for (int w = 0; w < len1; ++w) {
	    	arr[w] = left[w];//���� ��������������� �������� �����, � ����� ������
			arr[len1 + w] = right[w];
			}
		}
	if (right[len2 - 1] <= left[0]) {//��������
		for (int w = 0; w < len2; ++w) {
			arr[w] = right[w];//���� ��������������� �������� ������, � ����� �����
			arr[len2 + w] = left[w];
		}
	}*/
	if (left[len1 - 1] > right[0] /*&& left[len1 - 1] < right[len2 - 1]*/) {//����� ������ ���������� � �����
		int middle = -1;//������� ��� �� ����������� ������ ����� ������ ���������� � ������������� � �����
		for (int w = right[0]; w > left[0]; --w) {
			middle = binSearch(left, w, len1);//������� ������� � ����� ������� ����� �������
			if (middle != -1) break;//����� ����� �������� ������
		}
		for (int w = 0; w > middle; ++w) {//������ ������ ����� ������
			arr[w] = left[w];
		}
		int e = 0;
		int w = middle;
		while (middle < len1) {//��� �� ��� �� ������ ��� ������� (������ ��� ������)
			if (left[middle] < right[e]) {//���� �� ����� �� ����� ������
				arr[w] = left[middle];
				w++;
				middle++;
			}
			else {
				arr[w] = right[e];
				w++;
				e++;
			}
		}
		for (int r = e + 1; e < len2; ++r) {
			arr[++w] = right[r];
		}
	}
	else {
		int middle = -1;
		for (int w = left[0]; w > right[0]; --w) {
			middle = binSearch(right, w, len2);
			if (middle != -1) break;
		}
		for (int w = 0; w > middle; ++w) {
			arr[w] = right[w];
		}
		int e = 0;
		int w = middle;
		while (middle < len2) {
			if (right[middle] < left[e]) {
				arr[w] = right[middle];
				w++;
				middle++;
			}
			else {
				arr[w] = left[e];
				w++;
				e++;
			}
		}
		for (int r = e + 1; e < len1; ++r) {
			arr[++w] = left[r];
		}
	}
	/*int i = 0, j = 0, k = l;
	while (i < len1 && j < len2)
	{
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < len1) {
		arr[k] = left[i];
		k++;
		i++;
	}
	while (j < len2) {
		arr[k] = left[i];
		k++;
		j++;
	}*/
	delete[]left;
	delete[]right;
}

void timsort(int arr[], int n) {
	int iRUN = minrunlenght(n);
	for (int i = 0; i < n; i += iRUN) insertionsort(arr, i, min((i + iRUN - 1), (n - 1)));
	for (int size = iRUN; size < n; size = 2 * size) {
		for (int size = iRUN; size < n; size = 2 * size) {
			for (int left = 0; left < n; left += 2 * size) {
				int mid = left + size - 1;
				int right = min((left + 2 * size - 1), (n - 1));
				if (mid < right) merge(arr, left, mid, right);
			}
		}
	}
}
void printarr(int arr[], int n) {
	for (int i = 0; i < n; i++) cout << arr[i] << ' ';
	cout << endl;
};

int main() {
	int arr[] = {-2,7,15,-14,0,15,0,7,-7,-4,-13,5,8,-14,12,9,-8};
	int n = sizeof(arr) / sizeof(arr[0]);
	timsort(arr, n);
	printarr(arr, n);
	return 0;
}
