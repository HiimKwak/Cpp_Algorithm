#include <iostream>

void Heapify(int* array, int length, int index)
{
	while (true)
	{
		int largest = index;
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;

		if (leftChild < length && array[leftChild] > array[largest])
			largest = leftChild;

		if (rightChild < length && array[rightChild] > array[largest]) // 완전 이진 힙이 아닌 경우를 위한 fallback
			largest = rightChild;

		if (largest == index) break;

		std::swap<int>(array[index], array[largest]);
		index = largest;
	}
}

void HeapSort(int* array, int length)
{
	for (int i = length / 2 - 1; i >= 0; --i)
		Heapify(array, length, i);

	for (int i = length - 1; i > 0; --i)
	{
		std::swap<int>(array[0], array[i]);
		Heapify(array, i, 0);
	}
}
void PrintArray(int* array, int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix];

		// 마지막 원소 전까지는 콤마 출력.
		if (ix < length - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << "\n";
}

int main()
{
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };
	//int array[] =
	//{
	//	1, 58, 10, 20, 56, 63, 73, 5, 28, 37,
	//	80, 61, 82, 45, 11, 66, 83, 59, 22, 64,
	//	52, 89, 94, 76, 44, 40, 75, 2, 23, 57,
	//	92, 8, 41, 96, 15, 84, 35, 69, 54, 47,
	//	90, 24, 43, 74, 34, 85, 72, 95, 18, 17,
	//	98, 9, 29, 53, 27, 79, 39, 51, 31, 16,
	//	6, 97, 26, 100, 21, 48, 33, 60, 91, 19,
	//	30, 13, 71, 78, 87, 25, 81, 4, 42, 93,
	//	49, 12, 14, 7, 62, 77, 38, 99, 88, 50,
	//	32, 46, 70, 3, 86, 68, 36, 67, 55, 65
	//};

	int length = _countof(array);

	PrintArray(array, length);
	HeapSort(array, length);
	PrintArray(array, length);
	std::cin.get();
}