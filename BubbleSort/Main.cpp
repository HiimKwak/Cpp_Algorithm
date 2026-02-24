#include <iostream>

using Comparer = bool (*)(int, int);

bool IsGreater(int left, int right)
{
	return left > right;
}

bool IsLess(int left, int right)
{
	return left < right;
}

void BubbleSort(int* array, int length, Comparer comparer)
{
	for (int i = 0; i < length - 1; ++i)
	{
		for (int j = 0; j < length - 1 - i; ++j)
		{
			if (comparer(array[j], array[j + 1])) // delegate: 비교 로직을 comparer에게 위임
			{
				std::swap<int>(array[j], array[j + 1]);
			}
		}
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
	int array[] = { 5,2,8,4,1,7,3,6,9,10,15,13,14,12,17,16 };

	int length = sizeof(array) / sizeof(array[0]);

	std::cout << "정렬 전 배열: ";
	PrintArray(array, length);

	BubbleSort(array, length, IsLess);

	std::cout << "정렬 후 배열: ";
	PrintArray(array, length);

	std::cin.get();
}