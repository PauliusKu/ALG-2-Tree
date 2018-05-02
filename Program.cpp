#include "Program.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <math.h>
#define PI 3.14159265

void TreeGenerator(unsigned int n, std::vector<Tree> &T)
{
	std::random_device rd;
	std::mt19937 mt(static_cast<unsigned int>(time(nullptr)));
	
	
	Tree T1{};
	T1.ID = 0;
	T1.tab = 0;
	T1.area = 360;
	T.push_back(T1);
	
	for (unsigned int i = 1; i < n; i++)
	{
		Tree T1{};
		T1.ID = i;
		
		std::uniform_int_distribution<unsigned int> dist(0,i-1);
		T1.Connect.push_back(dist(mt));
		for (auto& it : T)
		{
			if (it.ID == T1.Connect[0])
			{
				it.Connect.push_back(i);
			}
		}
		
		T.push_back(T1);	
	}
}

void PrintList(std::vector<Tree>& T)
{
	std::cout << "-------------------------------------" << std::endl;
	for (auto & i : T)
	{
		std::cout << "ID: " << i.ID << std::endl;
		std::cout << "DescSum: " << i.descSum << std::endl;
		std::cout << "level: " << i.level << std::endl;
		std::cout << "angle: " << i.angle << std::endl;
		std::cout << "tab: " << i.tab << std::endl;
		for (unsigned int j = 0; j < i.Connect.size(); j++)
		{
			std::cout << i.Connect[j] << " ";
		}
		std::cout << std::endl;
		std::cout << "----------------------------" << std::endl;
	}
	std::cout << std::endl;
}

//unsigned int FindRoot(std::list<Tree> &T)
//{
//	struct TempTree{
//		bool exist = true;
//		unsigned int ID{};
//		std::vector<unsigned int> Connect{};
//		std::vector<unsigned int> newConnect{};
//	};
//	std::list<TempTree> Temp{};
//	for (auto & i : T)
//	{
//		TempTree smallTemp{};
//		smallTemp.ID = i.ID;
//		smallTemp.Connect = i.Connect;
//		smallTemp.newConnect = i.Connect;
//		Temp.push_back(smallTemp);
//		
//	}
//	
//	
//	while(Temp.size() >= 2)
//	{
//		std::cout << Temp.size() << std::endl;
//		//nuimineja isorinius lapus
//		for (auto & i : Temp)
//		{
//			//std::cout << "size" << i.Connect.size()<< std::endl;
//			if (i.Connect.size() == 1)
//			{
//				//pasalinti sasaja ir nuimti lapa
//				for (auto & it : Temp) //iesko sasajos
//				{
//					if (i.Connect[0] == it.ID) //randa sasaja
//					{
//						//iesko skaiciaus vektoriuje ir ji pasalina
//						it.newConnect.erase(std::remove(it.newConnect.begin(), it.newConnect.end(), i.ID), it.newConnect.end());
//					}
//				}
//				//nuima lapa
//				//std::cout << "********* "<< i.ID << std::endl;
//				i.exist = false;
//			}
//		}
//		std::list<TempTree>::iterator itr = Temp.begin();
//		for (itr=Temp.begin(); itr!=Temp.end(); ++itr)
//		{
//			itr->Connect = itr->newConnect;
//			std::cout << itr->ID << std::endl;
//			if (itr->exist == false)
//			{
//				std::cout << "-Trina-" << std::endl;
//				itr = Temp.erase(itr);
//				itr--;			
//			}
//		}
//	}
//	return Temp.front().ID;
//}

unsigned int CountDescLevel(std::vector<Tree> &T, unsigned int ID, unsigned int level)
{
	unsigned int sum{};
	
	//std::cout << "------------------------" << ID << std::endl;
	std::vector<Tree>::iterator itr = T.begin();
	while(true)
	{
		if(itr->ID == ID)
		{
			unsigned int start = 1;
			if (ID == 0) //jei pirmasis, reikia skaiciuti visus rysius
			{
				start = 0;
			}
			itr->level = level;
			sum++;
			for (unsigned int i = start; i < itr->Connect.size(); i++)
			{
				//std::cout << i << ": "<< itr->Connect[i] << std::endl;
				sum += CountDescLevel(T, itr->Connect[i], level+1);
				//std::cout << sum << std::endl;
			}
			itr->descSum = sum-1;
			break;
		}
		itr++;
	}
	return sum;
}

void GetArea(std::vector<Tree>& T)
{
	//tarkim, kad gerai
	for (unsigned int i = 1; i < T.size(); i++)
	{
		T[i].tab = T[T[i].Connect[0]].tab;
		T[i].area = (T[T[i].Connect[0]].area/T[T[i].Connect[0]].descSum*(T[i].descSum+1));
		T[i].angle = T[T[i].Connect[0]].tab + T[i].area/2;
		T[T[i].Connect[0]].tab += T[i].area;
	}
	
}

void GetCoordinates(std::vector<Tree>& T)
{

	for (unsigned int i = 0; i < T.size(); i++)
	{
		T[i].X = T[i].level*cos(T[i].angle*PI/180);
		T[i].Y = T[i].level*sin(T[i].angle*PI/180);
		//std::cout << T[i].X << std::endl;
		//std::cout << T[i].Y << std::endl;
	}
}
