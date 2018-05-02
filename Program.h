#ifndef PROGRAM_H
#define PROGRAM_H 
#include <vector>
#include <vector>
#include <iostream>

struct Tree{
	unsigned int ID{};//+
	std::vector<unsigned int> Connect{};//+
	float X{};
	float Y{};
	float Z{};
	unsigned int descSum{};//+
	unsigned int level{};//+
	float angle{}; //kampas
	float tab{};
	float area{};
	float start{};
	
};

void TreeGenerator(unsigned int n, std::vector<Tree> &T);
void PrintList(std::vector<Tree>& T);
unsigned int FindRoot(std::vector<Tree> &T);
unsigned int CountDescLevel(std::vector<Tree> &T, unsigned int ID, unsigned int level);
void GetCoordinates(std::vector<Tree>& T);
void GetArea(std::vector<Tree>& T);

#endif
