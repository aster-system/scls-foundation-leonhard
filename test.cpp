#include "basix.h"

int main()
{
	basix::print("Debug", "Developer", basix::replace("Hello world !", "o", "a"));

	return 0;
}