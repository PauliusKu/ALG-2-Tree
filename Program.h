#ifndef PROGRAM_H
#define PROGRAM_H 
#include <vector>
#include <iostream>
#include <string>
#include <chrono>


typedef struct {
  double x, y, z;
} coordinate;

typedef struct {
  unsigned int r, g, b;
} RGB;

struct Vertices{
	coordinate vertice;
};
struct Faces{
	std::vector <unsigned int> face{};
};

class Tree{
	public:
		unsigned int ID{};
		std::vector<unsigned int> Connect{};
		double X{};
		double Y{};
		double Z = 0;
		unsigned int descSum{};
		unsigned int level{};
		float angle{}; //kampas
		float tab{};
		float area{};
		float start{};
	
};

class Timer {
private:
	// panaudojame using
	using hrClock = std::chrono::high_resolution_clock;
	using durationDouble = std::chrono::duration<double>;
	std::chrono::time_point<hrClock> start;
public:
	Timer() : start{ hrClock::now() } {}
	void reset() {
		start = hrClock::now();
	}
	double elapsed() const {
		return durationDouble(hrClock::now() - start).count();
	}
};
void TreeGenerator(unsigned int n, std::vector<Tree> &T);
void PrintList(std::vector<Tree>& T);
unsigned int FindRoot(std::vector<Tree> &T);
void GetCoordinates(std::vector<Tree>& T);
void CreateCube(coordinate & center, RGB &rgb, double &k, std::vector<Vertices>&V, std::vector<Faces>&F);
void CreateCylinder(coordinate & start, coordinate & end, RGB &rgb, double &k, std::vector<Vertices>&V, std::vector<Faces>&F);
void PrintOFF(std::vector <Vertices> &V, std::vector<Faces>&F);
void InputPrufer(std::vector<Tree> &T);
int ivestiSk( int a, int b);
void CreateShapes(std::vector<Tree> &T, std::vector <Vertices> &V, std::vector<Faces>&F, unsigned int &root);
unsigned int CountMagic(std::vector<Tree> &T, unsigned int ID, unsigned int level);
void GetNewArea(std::vector<Tree>& T, unsigned int ID);
#endif
