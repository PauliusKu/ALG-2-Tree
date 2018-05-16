#include "Program.h"


int main()
{
	Timer tm;
	std::vector<Tree> T;
	unsigned int root{};
	std::cout << "1 - generuoti faila, 2 - ivesti priuferio koda." << std::endl;
	unsigned int in;
	bool t{};
	do{
		t = false;
		try
		{
			in = ivestiSk(1, 2);
		} catch (const char* msg) {
    	std::cout << msg << std::endl;
    	t = true;
   		}
	}while (t);
	switch(in)
	{
		case 1:{
			std::cout << "Pasirinkote: Generuoti faila ---------------------" <<  std::endl;
			do{
				t = false;
				try
				{
					in = ivestiSk(1, 1000000);
				} catch (const char* msg) {
		    	std::cout << msg << std::endl;
		    	t = true;
		   		}
			}while (t);
			std::cout << "Generuojamas Failas ------------------------------" <<  std::endl;
			tm.reset();
			TreeGenerator(in, T);
			std::cout << tm.elapsed() << " s\n";
			break;
		}
		case 2: {
			std::cout << "Iveskite priuferio koda --------------------------" <<  std::endl;
			InputPrufer(T);
			break;
		}
		default: system("pause");
	}
	std::cout << "Ieskoma saknis -----------------------------------" << std::endl;
	tm.reset();
	root = FindRoot(T);
	std::cout << tm.elapsed() << " s\n";
	std::cout << "Skaiciuojami Vaikai ------------------------------" <<  std::endl;
	tm.reset();
	std::cout << CountMagic(T, root, 0) <<" dbgdhthb"<< std::endl;
	std::cout << tm.elapsed() << " s\n";
	std::cout << "Skaiciuojami Kampai ------------------------------" <<  std::endl;
	tm.reset();
	GetNewArea(T, root);
	std::cout << tm.elapsed() << " s\n";
	std::cout << "Skaiciuojamos Koordinates ------------------------" <<  std::endl;
	tm.reset();
	GetCoordinates(T);
	std::cout << tm.elapsed() << " s\n";
	std::cout << "Sudaromi figuros ---------------------------------" <<  std::endl;
	tm.reset();
	std::vector<Vertices> V{};
	std::vector<Faces> F{};
	CreateShapes(T, V, F, root);
	std::cout << tm.elapsed() << " s\n";
	std::cout << "Kuriamas OFF failas ------------------------------" <<  std::endl;
	tm.reset();
	PrintOFF(V, F);
	std::cout << tm.elapsed() << " s\n";
	system("pause");
	return 0;
}
