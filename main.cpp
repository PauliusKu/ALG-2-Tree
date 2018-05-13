#include "Program.h"
#include <random>
#include <chrono>
using std::cout;
using std::endl;


int main()
{
	unsigned int n{};
	//std::cin >> n;
	std::vector<Tree> T;
	std::vector<Vertices> V{};
	std::vector<Faces> F{};
	std::cout << "Generuojamas Failas ------------------------------" <<  std::endl;
	//TreeGenerator(n, T);
	InputPrufer(T);
	std::cout << "Skaiciuojami Vaikai ------------------------------" <<  std::endl;
	CountDescLevel(T, 0, 0);
	//std::cout << FindRoot(T) << std::endl;
	std::cout << "Skaiciuojami Kampai ------------------------------" <<  std::endl;
	GetArea(T);
	std::cout << "Skaiciuojamos Koordinates ------------------------" <<  std::endl;
	GetCoordinates(T);
	std::cout << "Sudaromi kubai -----------------------------------" <<  std::endl;
	std::random_device rd;
	std::mt19937 mt(static_cast<unsigned int>(time(nullptr)));
	unsigned int size = T.size();
	coordinate center{T[0].X, T[0].Y, 0};
	RGB rgb{100, 100, 100};
	float k = 1.0/size+1.0/(0+5);
	CreateCube(center,rgb, k, V, F);
	for (unsigned int i = 1; i < size; i++)
	{
		std::uniform_int_distribution<unsigned int> d(0,255);
		RGB rgb{d(mt), d(mt), d(mt)};
		float k = 0.5/size+1.0/(i+5);
		coordinate center{T[i].X, T[i].Y, 0};
		coordinate parent{T[T[i].Connect[0]].X, T[T[i].Connect[0]].Y, 0};
		CreateCube(center,rgb, k, V, F);
		CreateCylinder(center, parent, rgb, k, V, F);
	}
	
	std::cout << "Kuriamas OFF failas ------------------------------" <<  std::endl;
	PrintOFF(V, F);
	//PrintList(T);
	return 0;
}
