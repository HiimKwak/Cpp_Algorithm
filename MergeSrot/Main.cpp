#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void Merge(int* array, int* leftArray, int leftArrayLength, int* rightArray, int rightArrayLength)
{
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	while (leftIndex < leftArrayLength && rightIndex < rightArrayLength)
	{
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[mergedIndex] = leftArray[leftIndex];
			++leftIndex;
		}
		else
		{
			array[mergedIndex] = rightArray[rightIndex];
			++rightIndex;
		}
		++mergedIndex;
	}

	while (leftIndex < leftArrayLength)
	{
		array[mergedIndex] = leftArray[leftIndex];
		++leftIndex;
		++mergedIndex;
	}
	while (rightIndex < rightArrayLength)
	{
		array[mergedIndex] = rightArray[rightIndex];
		++rightIndex;
		++mergedIndex;
	}
}

void MergeSort(int* array, int length)
{
	if (length <= 1)
		return;

	int mid = length / 2;
	int* leftArray = new int[mid];
	int* rightArray = new int[length - mid];

	// array 메모리 내용을 left/rightArray에 복사
	memcpy(leftArray, array, sizeof(int) * mid);
	memcpy(rightArray, (array + mid), sizeof(int) * (length - mid));

	MergeSort(leftArray, mid);
	MergeSort(rightArray, length - mid);

	Merge(array, leftArray, mid, rightArray, (length - mid));

	delete[] leftArray;
	delete[] rightArray;
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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

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

	MergeSort(array, length);

	std::cout << "정렬 후: ";
	PrintArray(array, length);

	std::cin.get();
}