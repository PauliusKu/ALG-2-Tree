#ifndef PROGRAM_H
#define PROGRAM_H 
#include <vector>
#include <iostream>

struct Tree{
	unsigned int ID{};
	std::vector<unsigned int> Connect{};
};

void TreeGenerator(unsigned int i, std::vector<Tree>& T);
void PrintVector(std::vector<Tree>& T);
unsigned int FindCenter(std::vector<Tree>& T);

#endif
