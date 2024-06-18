#include <iostream>
#include <vector>
#include <future>

void multiplyVec(int& MultiplierVec)
{
	MultiplierVec *= 2;
}

void For_Each_AsyncRec(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	auto currSize = std::distance(begin, end);

	if (currSize <= 3)
	{
		std::for_each(begin, end, multiplyVec);
	}
	else
	{
		auto mid = begin;
		std::advance(mid, currSize / 2);
		auto asRes = std::async(For_Each_AsyncRec, begin, mid);
		For_Each_AsyncRec(mid, end);

		asRes.get();
	}
}

void PrintArrey(std::vector<int>& vec) {
	for (int i : vec)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	std::cout << "Было: ";
	PrintArrey(vec);

	For_Each_AsyncRec(vec.begin(), vec.end());

	std::cout << "Стало: ";
	PrintArrey(vec);

	return 0;
}