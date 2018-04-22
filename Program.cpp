#include "Program.h"
#include <random>
#include <chrono>

void TreeGenerator(unsigned int n, std::vector<Tree>& T)
{
	std::cout << "Generuojamas Failas ------------------------------" <<  std::endl;
	std::random_device rd;
	std::mt19937 mt(static_cast<unsigned int>(time(nullptr)));
	
	Tree T1{};
	T1.ID = 0;
	T.push_back(T1);
	
	for (unsigned int i = 1; i < n; i ++)
	{
		Tree T1{};
		T1.ID = i;
		
		std::uniform_int_distribution<unsigned int> dist(0,i-1);
		T1.Connect.push_back(dist(mt));
		T[T1.Connect[0]].Connect.push_back(i);
		
		T.push_back(T1);
	}
}

void PrintVector(std::vector<Tree>& T)
{
	std::cout << "-------------------------------------" << std::endl;
	for (unsigned int i = 0; i < T.size(); i++)
	{
		std::cout << T[i].ID << std::endl;
		for (unsigned int j = 0; j < T[i].Connect.size(); j++)
		{
			std::cout << T[i].Connect[j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
unsigned int FindCenter(std::vector<Tree>& T)
{
	
	
	return 0;
}
