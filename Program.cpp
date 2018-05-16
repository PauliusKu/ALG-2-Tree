#include "Program.h"
#include <random>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <omp.h> 
#define PI 3.14159265
#define minus -1


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
		T[T1.Connect[0]].Connect.push_back(i);
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
		std::cout << "area: " << i.area << std::endl;
		std::cout << "X: " << i.X << std::endl;
		std::cout << "Y: " << i.Y << std::endl;
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
		//nuimineja isorinius lapus
		for (auto & i : Temp)
		{
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
				i.exist = false;
			}
		}
		std::vector<TempTree>::iterator itr = Temp.begin();
		for (itr=Temp.begin(); itr!=Temp.end(); ++itr)
		{
			itr->Connect = itr->newConnect;
			if (itr->exist == false)
			{
				itr = Temp.erase(itr);
				itr--;			
			}
		}
	}
	return Temp.front().ID;
}

unsigned int CountMagic1(std::vector<Tree> &T, unsigned int ID, unsigned int level, int par)
{

	//randa teva ir perkelia
	for (unsigned int i = 0; i < T[ID].Connect.size(); i++)
	{
		if (T[ID].Connect[i] == par)
		{
			T[ID].Connect[i] = T[ID].Connect[0];
			T[ID].Connect[0] = par;
		}
	}
	//skaiciuoja vaikus
	unsigned int sum{};

	T[ID].level = level;
	for (unsigned int i = 1; i < T[ID].Connect.size(); i++)
	{
		sum += CountMagic1(T, T[ID].Connect[i], level + 1, ID);
		sum++;
		T[ID].descSum = sum;
	}
	return sum;
}
unsigned int CountMagic(std::vector<Tree> &T, unsigned int ID, unsigned int level)
{
	unsigned int sum{};

	T[ID].level = level;
	for (unsigned int i = 0; i < T[ID].Connect.size(); i++)
	{
		sum += CountMagic1(T, T[ID].Connect[i], level + 1, ID);
		sum++;
		T[ID].descSum = sum;
	}
	return sum;
}

void GetNewArea1(std::vector<Tree>& T, unsigned int ID)
{
	for (unsigned int i = 1; i < T[ID].Connect.size(); i++)
	{
		T[T[ID].Connect[i]].tab = T[T[T[ID].Connect[i]].Connect[0]].tab;
		T[T[ID].Connect[i]].area = (T[T[T[ID].Connect[i]].Connect[0]].area / T[T[T[ID].Connect[i]].Connect[0]].descSum*(T[T[ID].Connect[i]].descSum + 1));
		T[T[ID].Connect[i]].angle = T[T[T[ID].Connect[i]].Connect[0]].tab + T[T[ID].Connect[i]].area / 2;
		T[T[T[ID].Connect[i]].Connect[0]].tab += T[T[ID].Connect[i]].area;
		GetNewArea1(T, T[ID].Connect[i]);
	}
}

void GetNewArea(std::vector<Tree>& T, unsigned int ID)
{
	T[ID].tab = 0;
	T[ID].area = 360;
	for (unsigned int i = 0; i < T[ID].Connect.size(); i++)
	{
		T[T[ID].Connect[i]].tab = T[T[T[ID].Connect[i]].Connect[0]].tab;
		T[T[ID].Connect[i]].area = (T[T[T[ID].Connect[i]].Connect[0]].area / T[T[T[ID].Connect[i]].Connect[0]].descSum*(T[T[ID].Connect[i]].descSum + 1));
		T[T[ID].Connect[i]].angle = T[T[T[ID].Connect[i]].Connect[0]].tab + T[T[ID].Connect[i]].area / 2;
		T[T[T[ID].Connect[i]].Connect[0]].tab += T[T[ID].Connect[i]].area;
		GetNewArea1(T, T[ID].Connect[i]);
	}
}

void GetCoordinates(std::vector<Tree>& T)
{

	for (unsigned int i = 0; i < T.size(); i++)
	{
		T[i].X = T[i].level*cos(T[i].angle*PI/180);
		T[i].Y = T[i].level*sin(T[i].angle*PI/180);
	}
}
void CreateCube(coordinate & center, RGB &rgb, double &k, std::vector <Vertices> &V, std::vector<Faces>&F)
{
	auto size = V.size();
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
void CreateCylinder(coordinate & start, coordinate & end, RGB &rgb, double &k, std::vector<Vertices>&V, std::vector<Faces>&F)
{
	auto size = V.size();
	Vertices V1;
	Faces F1;
	k = k/2;
	double angle = atan2(end.y - start.y, end.x - start.x) * 180 / PI;
	
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
				std::cout << "Priuferio kodo ivedimas baigtas" << std::endl;
			} else Pruf.push_back(a);
		}catch (const char* msg) {
    	std::cout << msg << std::endl;
   		}
	}while (t);
	auto n = Pruf.size();
	
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
					c = false;
				}
			}
			if (c)
			{
				bool f = true;
				for (unsigned int l = i; l < n; l++)
				{
					if (T[j].ID == Pruf[l])
					{
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
	
	//atranda teva vektoriuje
	for (unsigned int i = 0; i < n+2; i++)
	{
		unsigned int min = 1000000;
		unsigned int minPos = 0;
		for (unsigned int j = 0; j < T[i].Connect.size(); j++)
		{
			if (T[i].Connect[j] < min)
			{
				min = T[i].Connect[j];
				minPos = j;
			}
		}
		min = T[i].Connect[minPos];
		T[i].Connect[minPos] = T[i].Connect[0];
		T[i].Connect[0] = min;
	}

}

int ivestiSk( int a, int b)
{
	int c{};
	std::string sk{};
	std::getline(std::cin, sk);
	if (sk == "")
	{
		throw "Nieko neivedete";
	}
	for (unsigned int i = 0; i < sk.size(); i++)
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
void CreateShape(std::vector<Tree> &T, std::vector <Vertices> &V, std::vector<Faces>&F, unsigned int &root, unsigned int &deepRoot, std::mt19937 mt)
{

	std::uniform_int_distribution<unsigned int> d(0, 255);
	RGB rgb{ d(mt), d(mt), d(mt) };
	double k = (3.14159265 * T[root].level * T[root].area) / 540;
	if (k > 0.2)
	{
		k = 0.2;
	}
	if ((k >= ((3.14159265 * T[T[root].Connect[0]].level * T[T[root].Connect[0]].area) / 360)) && (T[root].Connect[0] != deepRoot))
	{
		k = (3.14159265 * T[T[root].Connect[0]].level * T[T[root].Connect[0]].area) / 540;
	}
	coordinate center{ T[root].X, T[root].Y, 0 };
	coordinate parent{ T[T[root].Connect[0]].X, T[T[root].Connect[0]].Y, 0 };
	CreateCube(center, rgb, k, V, F);
	CreateCylinder(center, parent, rgb, k, V, F);
	for (unsigned int i = 1; i < T[root].Connect.size(); i++)
	{
		CreateShape(T, V, F, T[root].Connect[i], deepRoot, mt);
	}
}
void CreateShapes(std::vector<Tree> &T, std::vector <Vertices> &V, std::vector<Faces>&F, unsigned int &root)
{
	std::random_device rd;
	std::mt19937 mt(static_cast<unsigned int>(time(nullptr)));
	unsigned int size = T.size();
	coordinate center{ T[root].X, T[root].Y, 0 };
	RGB rgb{ 100, 100, 100 };
	double k = 0.3;
	CreateCube(center, rgb, k, V, F);

	for (unsigned int i = 0; i < T[root].Connect.size(); i++)
	{
		CreateShape(T, V, F, T[root].Connect[i], root, mt);
	}

}
