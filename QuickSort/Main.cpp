#include <iostream>
#include <utility>

// left, mid, right 중 중위값 선택 후 한쪽 끝 -1 자리로 이동시킴
int MedianOfThree(int* arr, int left, int right)
{
	int mid = left + (right - left) / 2;

	if (arr[left] > arr[mid])
		std::swap(arr[left], arr[mid]);

	if (arr[left] > arr[right])
		std::swap(arr[left], arr[right]);

	if (arr[mid] > arr[right])
		std::swap(arr[mid], arr[right]);

	std::swap(arr[mid], arr[right - 1]);
	return right - 1;
}

int Partition(int* arr, int left, int right)
{
	int pivotIndex = MedianOfThree(arr, left, right);
	int pivot = arr[pivotIndex];

	int i = left;
	int j = right - 1;

	while (true)
	{
		while (arr[++i] < pivot) {} // pivot보다 크면 i 증가가 멈춤
		while (arr[--j] > pivot) {} // pivot보다 작으면 j 감소가 멈춤

		if (i >= j)
			break;

		std::swap(arr[i], arr[j]); // 잘못된 위치에 있는 양쪽 최초 값 두 개를 스왑
	}

	std::swap(arr[i], arr[pivotIndex]);
	return i;
}

void QuickSort(int* arr, int left, int right)
{
	if (left + 10 <= right)
	{
		int pivot = Partition(arr, left, right);
		QuickSort(arr, left, pivot - 1);
		QuickSort(arr, pivot + 1, right);
	}
	else
	{
		// 작은 구간은 insertion sort
		for (int i = left + 1; i <= right; ++i)
		{
			int key = arr[i];
			int j = i - 1;
			while (j >= left && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				--j;
			}
			arr[j + 1] = key;
		}
	}
}

void PrintArray(int* array, int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix];

		if (ix < length - 1)
			std::cout << ", ";
	}

	std::cout << "\n";
}

int main()
{
	int array[] =
	{
		1, 58, 10, 20, 56, 63, 73, 5, 28, 37,
		80, 61, 82, 45, 11, 66, 83, 59, 22, 64,
		52, 89, 94, 76, 44, 40, 75, 2, 23, 57,
		92, 8, 41, 96, 15, 84, 35, 69, 54, 47,
		90, 24, 43, 74, 34, 85, 72, 95, 18, 17,
		98, 9, 29, 53, 27, 79, 39, 51, 31, 16,
		6, 97, 26, 100, 21, 48, 33, 60, 91, 19,
		30, 13, 71, 78, 87, 25, 81, 4, 42, 93,
		49, 12, 14, 7, 62, 77, 38, 99, 88, 50,
		32, 46, 70, 3, 86, 68, 36, 67, 55, 65
	};

	int length = _countof(array);

	std::cout << "정렬 전: ";
	PrintArray(array, length);

	QuickSort(array, 0, length - 1);

	std::cout << "정렬 후: ";
	PrintArray(array, length);

	std::cin.get();
}