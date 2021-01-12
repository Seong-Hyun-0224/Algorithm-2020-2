#include <stdio.h>

void quick_sort(int list[], int left, int right)
{
	int q;
	if (left < right) { // 리스트에 2개 이상의 항목이 있으면
		q = partition(list, left, right);// q = 분할(partition) 후 피벗 저장 인덱스
		quick_sort(list, left, q - 1); // 왼쪽 리스트 정렬 (left~q-1)
		quick_sort(list, q + 1, right);// 오른쪽 리스트 정렬 (q+1~right)
	}
}

int partition(int list[], int left, int right) {
	int low, high, pivot, temp;
	low = left; // 1
	high = right + 1; // 2
	pivot = list[left]; // 3
	do {
		do // 4
			low++;
		while (low <= right && list[low] < pivot);
		do // 5
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp); // 6
	} while (low < high); // 7
	SWAP(list[left], list[high], temp); // 8
	return high;
}

void main() {
	int list[4] = {1, 4, 2, 6};		//n과 리스트의 주요 양의 정수는 사용자가 직접 수정.
	quick_sort(list, 0, 4);
	int length = sizeof(list);
	int half1[] = malloc(sizeof(int));
	for (int i = 0; i < length/2; i++) {
		half1[i] = list[i];
	}
	int half2[] = malloc(sizeof(int));
	for (int j = length / 2; j < length; j++) {
		int temp = 0;
		half2[temp] = list[j];
		temp++;
	}
}