#include <iostream>

#define FAIL -1

int RecursiveBinarySearch(
	int* array,
	int target,
	int start,
	int end
) {
	if (start > end)
		return FAIL;

	int mid = (start + end) / 2;

	if (array[mid] == target)
		return mid;

	else if (array[mid] > target)
		return RecursiveBinarySearch(
			array,
			target,
			start,
			mid - 1
		);

	return RecursiveBinarySearch(
		array,
		target,
		mid + 1,
		end
	);
}

int IterativeBinarySearch(
	int* array,
	int target,
	int start,
	int end
) {
	while (start <= end)
	{
		int mid = (start + end) / 2;

		if (array[mid] == target)
			return mid;

		if (array[mid] > target)
			end = mid - 1;
		else
			start = mid + 1;
	}
	return FAIL;
}

int main()
{
	int array[] = { 1, 3, 5, 7, 9, 11, 13, 15 };
	int target = 7;
	int length = sizeof(array) / sizeof(array[0]);

	//int index = RecursiveBinarySearch(
	//	array, target, 0, length - 1
	//);
	int index = IterativeBinarySearch(
		array, target, 0, length - 1
	);

	if (index != FAIL)
	{
		std::cout
			<< "값: " << target
			<< "을 인덱스 " << index
			<< " 에서 찾음\n";
	}
	else
	{
		std::cout << "값: " << target << "을 찾지 못함\n";
	}

	std::cin.get();
}