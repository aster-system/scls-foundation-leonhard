#include "basix.h"

int main()
{
	basix::PNG_Image image;
	image.load_from_path("test.png");

	basix::print("Debug", "Developer", basix::replace("Hello world !", "o", "a"));

	return 0;
}