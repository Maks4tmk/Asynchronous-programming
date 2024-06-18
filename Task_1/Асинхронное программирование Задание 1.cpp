// Асинхронное программирование Задание 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <cstdlib>
#include <vector>
#include <future>


void VecArrayGen(std::vector<int>& vec) {
	srand(time(0));

	while (vec.size() < 10) {
		int num = rand() % 10;
		if (find(vec.begin(), vec.end(), num) == vec.end()) {
			vec.push_back(num);
		}
	}
}

void FindMinNum(const std::vector<int> vec, int i, std::promise<int> prom)
{
	int minNum = i;

	for (int j = i + 1; j < vec.size(); j++)
	{
		if (vec[j] < vec[minNum])
		{
			minNum = j;
		}
	}
	prom.set_value(minNum);
};

void SortArray(std::vector<int>& vec)
{
	for (int i = 0; i < vec.size() - 1; i++)
	{
		std::promise<int> prom;
		std::future<int> future_res = prom.get_future();

		auto asyncFindMinNum = std::async(std::launch::async, FindMinNum, vec, i, std::move(prom));

		int minNum = future_res.get();
		if (vec[i] != vec[minNum])
		{
			std::swap(vec[i], vec[minNum]);
		}
	}
};

void printVec(const std::vector<int> vec)
{
	for (const auto& i : vec)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}




int main()
{
	setlocale(LC_ALL,"ru");

	std::vector<int> vec;

	VecArrayGen(vec);

	std::cout << "До сортировки: ";
	printVec(vec);

	SortArray(vec);

	std::cout << "После сортировки: ";
	printVec(vec);
}