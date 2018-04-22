#include "Program.h"

using std::cout;
using std::endl;

int main()
{
	unsigned int n{};
	std::cin >> n;
	std::vector<Tree> T;
	TreeGenerator(n, T);
	PrintVector(T);
	unsigned int c = FindCenter(T);
	return 0;
}
