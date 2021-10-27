#include <iostream>

using namespace std;

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

int minrunlenght(int n) {
	bool flag = 0;
	while (n >= 64) {
		flag |= n & 1;
		n >>= 1;
	}
	return n + flag;
}
int binSearch(int arr[] , int key, int lenght) { 
	int l = -1;                      
	int r = lenght;
	int m;
	while (l < r - 1) {               
		m = (l + r) / 2;            
		if (arr[m] < key) { l = m; }
		else
			r = m;
	}                  
	return r;
}

void merge(int arr[], int l, int m, int r){
	int len1 = m - l + 1, len2 = r - m;
	int* left = new int[len1];
	int* right = new int[len2];
	for (int i = 0; i < len1; i++)
		left[i] = arr[l + i];
	for (int i = 0; i < len2; i++)
		right[i] = arr[m + 1 + i];
	//gallop? nedogallop?
		/*if (left[len1 - 1] > right[0] )*/ {
		int middle = -1;
		for (int w = right[0]; w > left[0]; --w) {
			middle = binSearch(left, w, len1);//look for position in left part where we can put right part
			if (middle != -1) break;
		}
		for (int w = 0; w > middle; ++w) {//put left part before beginning of right part
			arr[w] = left[w];
		}
		int e = 0;
		int w = middle;
		while (middle < len1) {//compare left and right parts, put the least until we reach the end of left part
			if (left[middle] < right[e]) {
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
		for (int r = e + 1; e < len2; ++r) {//put all other from right
			arr[++w] = right[r];
		}
	}
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
	//int arr[] = {-2,7,15,-14,0,15,0,7,-7,-4,-13,5,8,-14,12,9,-8};
	int arr[] = { -4,-26,-10, 4,-18,-22,-5,-25,-6,-9,-11,-15, 2,22,23,27,24, 8,25,-1,13,21, 0,15,12,-21, 3, 1,19,17,30,-7,-27,-19,28,20,10,-14,-16, 5,16,18,-17,-23,-2,-24, 7,-8, 9,11,26,-12,-13,14,29,-30, 6, 3,-29,-20,-28 };
	int n = sizeof(arr) / sizeof(arr[0]);
	timsort(arr, n);
	printarr(arr, n);
	return 0;
}
