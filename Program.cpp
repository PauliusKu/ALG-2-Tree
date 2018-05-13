#include "Program.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <algorithm>
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

unsigned int FindRoot(std::vector<Tree> &T)
{
	struct TempTree{
		bool exist = true;
		unsigned int ID{};
		std::vector<unsigned int> Connect{};
		std::vector<unsigned int> newConnect{};
	};
	std::vector<TempTree> Temp{};
	for (auto & i : T)
	{
		TempTree smallTemp{};
		smallTemp.ID = i.ID;
		smallTemp.Connect = i.Connect;
		smallTemp.newConnect = i.Connect;
		Temp.push_back(smallTemp);
		
	}
	
	
	while(Temp.size() >= 2)
	{
		//std::cout << Temp.size() << std::endl;
		//nuimineja isorinius lapus
		for (auto & i : Temp)
		{
			//std::cout << "size" << i.Connect.size()<< std::endl;
			if (i.Connect.size() == 1)
			{
				//pasalinti sasaja ir nuimti lapa
				for (auto & it : Temp) //iesko sasajos
				{
					if (i.Connect[0] == it.ID) //randa sasaja
					{
						//iesko skaiciaus vektoriuje ir ji pasalina
						it.newConnect.erase(std::remove(it.newConnect.begin(), it.newConnect.end(), i.ID), it.newConnect.end());
					}
				}
				//nuima lapa
				//std::cout << "********* "<< i.ID << std::endl;
				i.exist = false;
			}
		}
		std::vector<TempTree>::iterator itr = Temp.begin();
		for (itr=Temp.begin(); itr!=Temp.end(); ++itr)
		{
			itr->Connect = itr->newConnect;
			//std::cout << itr->ID << std::endl;
			if (itr->exist == false)
			{
				//std::cout << "-Trina-" << std::endl;
				itr = Temp.erase(itr);
				itr--;			
			}
		}
	}
	return Temp.front().ID;
}

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
			if (ID == 0) //jei pirmasis, reikia skaiciuoti visus rysius
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

//void CreateOFF(std::vector<Tree>& T)
//{
//	std::ofstream ofs ("testas.off");
//	ofs << "OFF" << std::endl;
//	ofs << T.size()*8<<" " << T.size()*7-1 << " 0" << std::endl;
//	for (int i = 0; i < T.size(); i++)
//	{
//		double k = 1.0/T.size()+1.0/(i+5);
//		//kubai
//		ofs << T[i].X+ k << " " << T[i].Y+ k << " " << +k << std::endl;
//		ofs << T[i].X+ k << " " << T[i].Y- k << " " << +k << std::endl;
//		ofs << T[i].X- k << " " << T[i].Y- k << " " << +k << std::endl;
//		ofs << T[i].X- k << " " << T[i].Y+ k << " " << +k << std::endl;
//		ofs << T[i].X+ k << " " << T[i].Y+ k << " " << -k << std::endl;
//		ofs << T[i].X+ k << " " << T[i].Y- k << " " << -k << std::endl;
//		ofs << T[i].X- k << " " << T[i].Y- k << " " << -k << std::endl;
//		ofs << T[i].X- k << " " << T[i].Y+ k << " " << -k << std::endl;
//	}
//	std::random_device rd;
//	std::mt19937 mt(static_cast<unsigned int>(time(nullptr)));
//	for (int i = 0; i < T.size(); i++)
//	{
//		std::uniform_int_distribution<unsigned int> d(0,255);
//		unsigned int d1 = d(mt);
//		unsigned int G = d(mt);
//		unsigned int d3 = d(mt);
//		ofs << "4 " << i*8 << " " << i*8+1 << " " << i*8+2 << " " << i*8+3 <<" " << d1 << " "<< d2 <<" " << d3<< std::endl;		
//		ofs << "4 " << i*8+4 << " " << i*8+5 << " " << i*8+6 << " " << i*8+7 <<  " "<< d1 << " "<< d2 <<" " << d3<< std::endl;
//		ofs << "4 " << i*8+4 << " " << i*8+7 << " " << i*8+3 << " " << i*8 << " "<< d1 << " "<< d2 <<" " << d3<< std::endl;		
//		ofs << "4 " << i*8+5 << " " << i*8+6 << " " << i*8+2 << " " << i*8+1<< " " << d1 << " "<< d2 <<" " << d3<< std::endl;
//		ofs << "4 " << i*8+4 << " " << i*8+5 << " " << i*8+1 << " " << i*8 << " "<< d1 << " "<< d2 <<" " << d3<< std::endl;	
//		ofs << "4 " << i*8+7 << " " << i*8+6 << " " << i*8+2 << " " << i*8+3 << " "<< d1 << " "<< d2 <<" " << d3<< std::endl;
//	}	
//	
//	for (int i = 1; i < T.size(); i++)
//	{
//		std::uniform_int_distribution<unsigned int> d(0,255);
//		unsigned int d1 = d(mt);
//		unsigned int d2 = d(mt);
//		unsigned int d3 = d(mt);
//		ofs << "4 ";
//		
//		ofs << T[i].ID*8 << " ";
//		ofs << T[i].ID*8+4 << " ";
//		ofs << T[i].Connect[0]*8+4 << " ";
//		ofs << T[i].Connect[0]*8 << " "<<d1 << " "<< d2 <<" " << d3<< std::endl;
//	}
//	ofs.close();
//}

void SwitchRoot(std::vector<Tree>& T, unsigned int newRoot)
{
//	unsigned int i = newRoot;
//	while(true)
//	{
//		std::cout << "i:  " << i << std::endl;
//		if (i == 0)
//		{
//			break;
//		}
//		for (unsigned int j = 1; true;j++)
//		{
//			if (T[T[i].Connect[0]].Connect[j] == i)
//			{
//				std::cout << "switch " << std::endl;
//				i = T[T[i].Connect[0]].Connect[0];
//				T[T[i].Connect[0]].Connect[0] = T[T[i].Connect[0]].Connect[j];
//				T[T[i].Connect[0]].Connect[j] = i;
//				for (unsigned int l = 0; l < T[T[i].Connect[0]].Connect.size(); l++)
//				{
//					std::cout << T[T[i].Connect[0]].Connect[l] << std::endl;
//				}
//				if (T[i].Connect[0] == 0)
//				{
//					i = 0;
//				}
//				break;
//			}
//		}
//	}
//	iter_swap(T.begin(), T.begin() + newRoot);
}


void CreateCube(coordinate & center, RGB &rgb, float &k, std::vector <Vertices> &V, std::vector<Faces>&F)
{
	unsigned int size = V.size();
	Vertices V1;
	Faces F1;
	
	F1.face.push_back(4); F1.face.push_back(size+3); F1.face.push_back(size+2); F1.face.push_back(size+1); F1.face.push_back(size+0); F1.face.push_back(rgb.r); F1.face.push_back(rgb.g); F1.face.push_back(rgb.b);
	F.push_back(F1);
	F1.face.clear();
	F1.face.push_back(4); F1.face.push_back(size+3); F1.face.push_back(size+0); F1.face.push_back(size+4); F1.face.push_back(size+7); F1.face.push_back(rgb.r); F1.face.push_back(rgb.g); F1.face.push_back(rgb.b);
	F.push_back(F1);
	F1.face.clear();
	F1.face.push_back(4); F1.face.push_back(size+0); F1.face.push_back(size+1); F1.face.push_back(size+5); F1.face.push_back(size+4); F1.face.push_back(rgb.r); F1.face.push_back(rgb.g); F1.face.push_back(rgb.b);
	F.push_back(F1);
	F1.face.clear();
	F1.face.push_back(4); F1.face.push_back(size+1); F1.face.push_back(size+2); F1.face.push_back(size+6); F1.face.push_back(size+5); F1.face.push_back(rgb.r); F1.face.push_back(rgb.g); F1.face.push_back(rgb.b);
	F.push_back(F1);
	F1.face.clear();
	F1.face.push_back(4); F1.face.push_back(size+7); F1.face.push_back(size+6); F1.face.push_back(size+2); F1.face.push_back(size+3); F1.face.push_back(rgb.r); F1.face.push_back(rgb.g); F1.face.push_back(rgb.b);
	F.push_back(F1);
	F1.face.clear();
	F1.face.push_back(4); F1.face.push_back(size+7); F1.face.push_back(size+4); F1.face.push_back(size+5); F1.face.push_back(size+6); F1.face.push_back(rgb.r); F1.face.push_back(rgb.g); F1.face.push_back(rgb.b);
	F.push_back(F1);
	F1.face.clear();
	
	V1.vertice ={center.x+k, center.y+k, center.z+k};
	V.push_back(V1);
	V1.vertice ={center.x+k, center.y-k, center.z+k};
	V.push_back(V1);
	V1.vertice ={center.x-k, center.y-k, center.z+k};
	V.push_back(V1);	
	V1.vertice ={center.x-k, center.y+k, center.z+k};
	V.push_back(V1);	
	V1.vertice ={center.x+k, center.y+k, center.z-k};
	V.push_back(V1);
	V1.vertice ={center.x+k, center.y-k, center.z-k};
	V.push_back(V1);
	V1.vertice ={center.x-k, center.y-k, center.z-k};
	V.push_back(V1);
	V1.vertice ={center.x-k, center.y+k, center.z-k};
	V.push_back(V1);
	
}

void PrintOFF(std::vector <Vertices> &V, std::vector<Faces>&F)
{
	std::ofstream ofs ("testas.off");
	ofs << "OFF" << std::endl;
	ofs << V.size() << " " << F.size() << " 0" << std::endl;
	for (unsigned int i = 0; i < V.size(); i++)
	{
		ofs << V[i].vertice.x << " " << V[i].vertice.y << " " << V[i].vertice.z << std::endl;
	}
	for (unsigned int i = 0; i < F.size(); i++)
	{
		for (unsigned int j = 0; j < F[i].face.size(); j++)
		{
			ofs << F[i].face[j] << " ";
		}
		ofs << std::endl;
	}
	ofs.close();
}
void CreateCylinder(coordinate & start, coordinate & end, RGB &rgb, float &k, std::vector<Vertices>&V, std::vector<Faces>&F)
{
	unsigned int size = V.size();
	Vertices V1;
	Faces F1;
	k = k/2;
	float angle = atan2(end.y - start.y, end.x - start.x) * 180 / PI;
	
	F1.face.push_back(4); F1.face.push_back(size+0); F1.face.push_back(size+1); F1.face.push_back(size+5); F1.face.push_back(size+4); F1.face.push_back(rgb.r); F1.face.push_back(rgb.g); F1.face.push_back(rgb.b);
	F.push_back(F1);
	F1.face.clear();
	F1.face.push_back(4); F1.face.push_back(size+6); F1.face.push_back(size+7); F1.face.push_back(size+3); F1.face.push_back(size+2); F1.face.push_back(rgb.r); F1.face.push_back(rgb.g); F1.face.push_back(rgb.b);
	F.push_back(F1);
	F1.face.clear();
	F1.face.push_back(4); F1.face.push_back(size+1); F1.face.push_back(size+3); F1.face.push_back(size+7); F1.face.push_back(size+5); F1.face.push_back(rgb.r); F1.face.push_back(rgb.g); F1.face.push_back(rgb.b);
	F.push_back(F1);
	F1.face.clear();
	F1.face.push_back(4); F1.face.push_back(size+4); F1.face.push_back(size+6); F1.face.push_back(size+2); F1.face.push_back(size+0); F1.face.push_back(rgb.r); F1.face.push_back(rgb.g); F1.face.push_back(rgb.b);
	F.push_back(F1);
	F1.face.clear();
	
	V1.vertice ={k*cos((angle-90)*PI/180)+start.x, k*sin((angle-90)*PI/180)+start.y, start.z+k};
	V.push_back(V1);
	V1.vertice ={k*cos((angle-90)*PI/180)+start.x, k*sin((angle-90)*PI/180)+start.y, start.z-k};
	V.push_back(V1);
	V1.vertice ={k*cos((angle+90)*PI/180)+start.x, k*sin((angle+90)*PI/180)+start.y, start.z+k};
	V.push_back(V1);
	V1.vertice ={k*cos((angle+90)*PI/180)+start.x, k*sin((angle+90)*PI/180)+start.y, start.z-k};
	V.push_back(V1);
	V1.vertice ={k*cos((angle-90)*PI/180)+end.x, k*sin((angle-90)*PI/180)+end.y, end.z+k};
	V.push_back(V1);
	V1.vertice ={k*cos((angle-90)*PI/180)+end.x, k*sin((angle-90)*PI/180)+end.y, end.z-k};
	V.push_back(V1);
	V1.vertice ={k*cos((angle+90)*PI/180)+end.x, k*sin((angle+90)*PI/180)+end.y, end.z+k};
	V.push_back(V1);
	V1.vertice ={k*cos((angle+90)*PI/180)+end.x, k*sin((angle+90)*PI/180)+end.y, end.z-k};
	V.push_back(V1);
}
void InputPrufer(std::vector<Tree> &T)
{
	unsigned int n{};
	std::vector<unsigned int>Pruf{};
	std::vector<unsigned int>Med{};
	
	std::cout << "Pasirinkote: ivestis per konsole. Noredami pabaigti pazymiu ivedima, iveskite -1" << std::endl;
	
	int a = 0;
	bool t = true;

	do{ //ivedimas is konsoles
		try{
			a = ivestiSk(-1, 100000);
			if (a == -1)
			{
				if (Pruf.size() == 0)
				{
					throw "Neivedete nei vieno pazymio";
				} else t = false;
				std::cout << "Pazymiu ivedimas baigtas" << std::endl;
			} else Pruf.push_back(a);
		}catch (const char* msg) {
    	std::cout << msg << std::endl;
   		}
	}while (t);
	n = Pruf.size();
	for (int i = 0; i < n; i++)
	{
		std::cout << Pruf[i] << std::endl;
	}
	
	//sukuriamas medis
	for (unsigned int i = 0; i < n+2; i++)
	{
		Tree T1{};
		T1.ID = i;
		T.push_back(T1);
	}
	
	for (unsigned int i = 0; i < n; i++) //eina per priuf
	{
		for (unsigned int j = 0; j < n+2; j++) //eina per nodes
		{
			bool c = true;
			for (unsigned int l = 0; l < Med.size(); l++)
			{
				if (Med[l] == j)
				{
					std::cout << "skip...   " << Med[l]<<std::endl;
					for (int z = 0; z < Med.size(); z++)
					{
						std::cout << Med[z] << " ";
					}
					std::cout << std::endl;
					c = false;
					//j++;
					//l = 0;
				}
			}
			if (c)
			{
				bool f = true;
				for (unsigned int l = i; l < n; l++)
				{
					if (T[j].ID == Pruf[l])
					{
						std::cout << i << " " << j << " " << l << std::endl;
						f = false;
					}
				}
				if (f == true)
				{
					std::cout << Pruf[i] << " " << j << std::endl;
					T[j].Connect.push_back(Pruf[i]);
					T[Pruf[i]].Connect.push_back(j);
					Med.push_back(j);
					j = n+2;
				}
			}
		}
	}
	
	//sujungia paskutinius du
	std::vector<unsigned int> Conn{};
	for (unsigned int i = 0; i < n+2; i++)
	{
		bool b = false;
		for (unsigned int j = 0; j < n; j++)
		{
			if (T[i].ID == Med[j])
			{
				b = true;
				j = n;
			}
		}
		if (b == false)
		{
			Conn.push_back(i);
		}
	}
	T[Conn[0]].Connect.push_back(Conn[1]);
	T[Conn[1]].Connect.push_back(Conn[0]);
	for (unsigned int i = 0; i < Conn.size(); i++)
	{
		std::cout << Conn[i] << std::endl;
	}
	
//	for (unsigned int i = 0; i < n+2; i++)
//	{
//		unsigned int j = T[i].Connect.size();
//		for (unsigned int l = 0; l < T[i].Connect.size(); l++)
//		{
//			j--;
//			unsigned int a{};
//			a = T[i].Connect[l];
//			T[i].Connect[l] = T[i].Connect[j];
//			T[i].Connect[j] = a;
//		}
//	}
	T[0].tab = 0;
	T[0].area = 360;
	
	
	//keicia vietomis
//	for (unsigned int i = 1; i < n+2; i++)
//	{
//		if (T[i].ID < T[i].Connect[0])
//		{
//			
//			unsigned int chld = T[i].ID;
//			unsigned int prt = T[i].Connect[0];
//			//vaikai
//			for (unsigned int j = 1; j < T[i].Connect.size(); j++)
//			{
//				T[T[i].Connect[j]].Connect[0] = prt;
//			}
//			//as
//			unsigned int a{};
//			T[i].ID = prt;
//			T[i].Connect[0] = chld;
//			//broliai
//			for (unsigned int j = 1; j < T[prt].Connect.size(); j++)
//			{
//				T[T[prt].Connect[j]].Connect[0] = chld;
//			}
//			//senelis
//			for (unsigned int j = 0; j < T[T[prt].Connect[0]].Connect.size(); j++)
//			{
//				if (T[T[prt].Connect[0]].Connect[j] == prt)
//				{
//					T[T[prt].Connect[0]].Connect[j] = chld;
//					j = T[T[prt].Connect[0]].Connect.size();
//				}
//			}
//			//tevas
//			T[prt].ID = chld;
//			for (unsigned int j = 1; j < T[prt].Connect.size(); j++)
//			{
//				if (T[prt].Connect[j] == chld)
//				{
//					T[prt].Connect[j] = prt;
//					j = T[T[i].Connect[0]].Connect.size();
//				}
//			}			
//			i--;
//		}
//	}
//	PrintList(T);
	//rikiuoti
	for (unsigned int i = 0; i < n+2; i++)
	{
		if (T[i].ID != i)
		{
			Tree T1{};
			T1 = T[i];
			T[i] = T[T[i].ID];
			T[T1.ID] = T1;
			i--;
		}
	}
	PrintList(T);
}

int ivestiSk( int a, int b)
{
	int c{};
	std::string sk{};
	getline(std::cin, sk);
	if (sk == "")
	{
		throw "Nieko neivedete";
	}
	for (int i = 0; i < sk.size(); i++)
	{
		if(((int)sk[i] < 45 || (int)sk[i] > 57) || ((int)sk[i] > 45 && (int)sk[i] < 48))
		{
			throw "Jusu ivesti simboliai neatitinka reikalavimu";
		}
	}
	c = std::stoi(sk);
	if (c >= a && c <= b)
	{
		return c;
	} else throw "Jusu ivestas skaicius yra per didelis arba per mazas";
}
