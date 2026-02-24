#include <iostream>
#include <Windows.h>

void InsertionSort(int* array, int length)
{
	if (length <= 1)
		return;

	for (int i = 1; i < length; ++i)
	{
		int key = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > key)
		{
			array[j + 1] = array[j];
			--j;
		}
		array[j + 1] = key;
	}
}

void PrintArray(int* array, int length)
{
	for (int i = 0; i < length; ++i)
	{
		std::cout << array[i];
		if (i < length - 1)
			std::cout << ", ";
	}

	std::cout << "\n";
}

int main()
{
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };
	//int length = _countof(array);
	int length = _ARRAYSIZE(array);

	std::cout << "정렬 전 배열: ";
	PrintArray(array, length);

	InsertionSort(array, length);

	std::cout << "정렬 후 배열: ";
	PrintArray(array, length);

	std::cin.get();
}