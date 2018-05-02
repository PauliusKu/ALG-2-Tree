#include "Program.h"
#include <fstream>
#include <random>
#include <chrono>
using std::cout;
using std::endl;


int main()
{
	unsigned int n{};
	std::cin >> n;
	std::vector<Tree> T;
	std::cout << "Generuojamas Failas ------------------------------" <<  std::endl;
	TreeGenerator(n, T);
	std::cout << "Skaiciuojami Vaikai ------------------------------" <<  std::endl;
	CountDescLevel(T, 0, 0);
	std::cout << "Skaiciuojami Kampai ------------------------------" <<  std::endl;
	GetArea(T);
	std::cout << "Skaiciuojamos Koordinatës ------------------------" <<  std::endl;
	GetCoordinates(T);
	PrintList(T);
	std::cout << "Isvedimas ----------------------------------------" <<  std::endl;
	std::ofstream ofs ("testas.off");
	ofs << "OFF" << endl;
	ofs << T.size()*8<<" " << T.size()*7-1 << " 0" << endl;
	for (int i = 0; i < T.size(); i++)
	{
		double k = 1.0/T.size()+1.0/(i+5);
		//kubai
		ofs << T[i].X+ k << " " << T[i].Y+ k << " " << k << endl;
		ofs << T[i].X+ k << " " << T[i].Y- k << " " << k << endl;
		ofs << T[i].X- k << " " << T[i].Y- k << " " << k << endl;
		ofs << T[i].X- k << " " << T[i].Y+ k << " " << k << endl;
		ofs << T[i].X+ k << " " << T[i].Y+ k << " " << -k << endl;
		ofs << T[i].X+ k << " " << T[i].Y- k << " " << -k << endl;
		ofs << T[i].X- k << " " << T[i].Y- k << " " << -k << endl;
		ofs << T[i].X- k << " " << T[i].Y+ k << " " << -k << endl;
	}
	std::random_device rd;
	std::mt19937 mt(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < T.size(); i++)
	{
		std::uniform_int_distribution<unsigned int> d(0,255);
		unsigned int d1 = d(mt);
		unsigned int d2 = d(mt);
		unsigned int d3 = d(mt);
		ofs << "4 " << i*8 << " " << i*8+1 << " " << i*8+2 << " " << i*8+3 <<" " << d1 << " "<< d2 <<" " << d3<< endl;		
		ofs << "4 " << i*8+4 << " " << i*8+5 << " " << i*8+6 << " " << i*8+7 <<  " "<< d1 << " "<< d2 <<" " << d3<< endl;
		ofs << "4 " << i*8+4 << " " << i*8+7 << " " << i*8+3 << " " << i*8 << " "<< d1 << " "<< d2 <<" " << d3<< endl;		
		ofs << "4 " << i*8+5 << " " << i*8+6 << " " << i*8+2 << " " << i*8+1<< " " << d1 << " "<< d2 <<" " << d3<< endl;
		ofs << "4 " << i*8+4 << " " << i*8+5 << " " << i*8+1 << " " << i*8 << " "<< d1 << " "<< d2 <<" " << d3<< endl;		
		ofs << "4 " << i*8+7 << " " << i*8+6 << " " << i*8+2 << " " << i*8+3 << " "<< d1 << " "<< d2 <<" " << d3<< endl;	
	}	
	
	for (int i = 1; i < T.size(); i++)
	{
		std::uniform_int_distribution<unsigned int> d(0,255);
		unsigned int d1 = d(mt);
		unsigned int d2 = d(mt);
		unsigned int d3 = d(mt);
		ofs << "4 ";
		
		ofs << T[i].ID*8 << " ";
		ofs << T[i].ID*8+4 << " ";
		ofs << T[i].Connect[0]*8+4 << " ";
		ofs << T[i].Connect[0]*8 << " "<<d1 << " "<< d2 <<" " << d3<< endl;	
	}
	ofs.close();
	return 0;
}
