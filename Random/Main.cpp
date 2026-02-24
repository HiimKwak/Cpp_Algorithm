#include <iostream>
#include <time.h>

int RandomRange(int min, int max)
{
	int diff = (max - min) + 1;
	//return (rand() % diff) + min;
	return ((diff * rand()) / (RAND_MAX + 1)) + min;
}

float RandomPercent()
{
	return rand() / static_cast<float>(RAND_MAX);
}

float RandomRange(float min, float max)
{
	int diff = max - min;
	return RandomPercent() * diff + min;
}

int main()
{
	//srand(100);
	srand((unsigned int)(time(NULL)));
	std::cout << "Random: " << RandomRange(1.0f, 10.0f) << "\n";
	std::cout << "Random: " << RandomRange(1.0f, 10.0f) << "\n";
	std::cout << "Random: " << RandomRange(1.0f, 10.0f) << "\n";
	std::cin.get();
}