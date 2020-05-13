#include<stdio.h>
#include<string.h>
#include <windows.h>
#define MAX_SIZE 1000


void BubbleSort(int *arr, int n) {
	
	int tmp;

	for (int i = 1; i < n; i++)
		for (int j = 0; j < n - i; j++)
			if (arr[j] > arr[j + 1]) {
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
}

void InsertionSort(int *arr, int n) {

	int i, j, tmp;
	for (i = 1; i < n; i++) {
		tmp = arr[i];
		for (j = i; j > 0; j--) {
			if (arr[j - 1] > tmp) arr[j] = arr[j - 1];
			else break;
		}
		arr[j] = tmp;
	}
}

void MergeSort(int *arr, int l, int r) {
	
	int m = (l + r) / 2;
	
	int i, j, k;
	int tmp_arr[MAX_SIZE + 1];
	
	if (l < r) {
		MergeSort(arr, l, m);
		MergeSort(arr, m + 1, r);
		
		i = l, j = m+1, k = 0;
		
		while (k <= r - l) {
			if (i > m || (arr[i] > arr[j] && j <= r))
				tmp_arr[k++] = arr[j++];
			else
				tmp_arr[k++] = arr[i++];
		}

		for (int t = 0; t < k; t++)
			arr[l + t] = tmp_arr[t];
	}
	
}

void QuickSort(int *arr, int p, int q) {
	
	int c = p;
	int tmp;

	if (p < q) {
		for (int i = p + 1; i <= q; i++)
			if (arr[i] < arr[p]) {
				tmp = arr[i];
				arr[i] = arr[++c];
				arr[c] = tmp;
			}
		tmp = arr[p];
		arr[p] = arr[c];
		arr[c] = tmp;

		QuickSort(arr, p, c - 1);
		QuickSort(arr, c + 1, q);
	}
}

void RadixSort(int *arr, int n, int d) {

	int cnt_arr[10];
	int tmp_arr[MAX_SIZE + 1];
	int t = 1;

	for (int i = 0; i < d; i++) {
		memset(cnt_arr, 0, sizeof(cnt_arr));

		for (int j = 0; j < n; j++)
			cnt_arr[(arr[j] / t) % 10]++;

		for (int k = 1; k < 10; k++)
			cnt_arr[k] = cnt_arr[k] + cnt_arr[k - 1];

		for (int j = n - 1; j >= 0; j--)
			tmp_arr[cnt_arr[(arr[j] / t) % 10]--] = arr[j];

		for (int j = 0; j < n; j++)
			arr[j] = tmp_arr[j + 1];

		t *= 10;
	}
}

void BucketSort(int *arr, int n) {
	
	int bucket[11][MAX_SIZE] = {0};
	int cnt[11] = {0};
	int tmp = 0;

	for (int i = 0; i < n; i++)
		bucket[arr[i] / 100][cnt[arr[i] / 100]++] = arr[i];
	
	for (int j = 0; j < 11; j++)
		InsertionSort(bucket[j], cnt[j]);

	for (int j = 0; j < 11; j++)
		for (int k = 0; k < cnt[j]; k++)
			arr[tmp++] = bucket[j][k];
}

int main() {

	int n;
	int data_arr[MAX_SIZE];  // 1000

	LARGE_INTEGER start, end, liFrequency;

	printf("---------------------------------------------------------------\n");
	printf("                         Bucket Sort                           \n");
	printf("---------------------------------------------------------------\n");

	printf("\n Input size n : ");
	scanf("%d", &n);

	printf("\n [Input]\n");

	/* simply create the input */
	for (int i = 0; i < n; i++) {
		data_arr[i] = n - i;
		if (i % 10 == 0) printf("\n");
		printf("%5d", data_arr[i]);
	}
	QueryPerformanceFrequency(&liFrequency);
	QueryPerformanceCounter(&start);

	/* Sorting Algorithms */

	//BubbleSort(data_arr, n);
	//InsertionSort(data_arr, n);
	//MergeSort(data_arr, 0, n - 1);
	//QuickSort(data_arr, 0, n - 1);
	//RadixSort(data_arr, n, 4);
	BucketSort(data_arr, n);

	QueryPerformanceCounter(&end);
	printf("\n\n [Output] \n");
	for (int i = 0; i < n; i++) {
		if (i % 10 == 0) printf("\n");
		printf("%5d", data_arr[i]);
	}
	printf("\n\n");
	printf("---------------------------------------------------------------\n");
	printf("                                 execution time : %lf sec \n", (double)(end.QuadPart - start.QuadPart) / (double)liFrequency.QuadPart);
	printf("---------------------------------------------------------------\n");

	return 0;
}
