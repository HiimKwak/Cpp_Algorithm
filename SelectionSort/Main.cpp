#include <iostream>

void SelectionSort(int* array, int length)
{
	if (length <= 1)
		return;

	for (int i = 0; i < length - 1; ++i)
	{
		int minIndex = i;

		for (int j = i + 1; j < length; ++j)
		{
			if (array[minIndex] > array[j])
				minIndex = j;
		}
		if (minIndex != i)
			std::swap<int>(array[i], array[minIndex]);
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
	int length = sizeof(array) / sizeof(array[0]);

	std::cout << "정렬 전 배열: ";
	PrintArray(array, length);

	SelectionSort(array, length);

	std::cout << "정렬 후 배열: ";
	PrintArray(array, length);

	std::cin.get();

}