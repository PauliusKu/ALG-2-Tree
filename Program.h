#ifndef PROGRAM_H
#define PROGRAM_H 
#include <vector>
#include <vector>
#include <iostream>


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

struct Tree{
	unsigned int ID{};//+
	std::vector<unsigned int> Connect{};//+
	float X{};
	float Y{};
	float Z = 0;
	unsigned int descSum{};//+
	unsigned int level{};//+
	float angle{}; //kampas
	float tab{};
	float area{};
	float start{};
	float anglebtw{};
	
};

void TreeGenerator(unsigned int n, std::vector<Tree> &T);
void PrintList(std::vector<Tree>& T);
unsigned int FindRoot(std::vector<Tree> &T);
unsigned int CountDescLevel(std::vector<Tree> &T, unsigned int ID, unsigned int level);
void GetCoordinates(std::vector<Tree>& T);
void GetArea(std::vector<Tree>& T);
void CreateOFF(std::vector<Tree>& T);
void SwitchRoot(std::vector<Tree>& T, unsigned int newRoot);
void CreateCube(coordinate & center, RGB &rgb, float &k, std::vector<Vertices>&V, std::vector<Faces>&F);
void CreateCylinder(coordinate & start, coordinate & end, RGB &rgb, float &k, std::vector<Vertices>&V, std::vector<Faces>&F);
void PrintOFF(std::vector <Vertices> &V, std::vector<Faces>&F);
void InputPrufer(std::vector<Tree> &T);
int ivestiSk( int a, int b);
#endif
