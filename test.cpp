#include "basix.h"

int main()
{
	basix::PNG_Image image;
	image.load_from_path("home.png");

	basix::print("Debug", "Developer", basix::replace("Hello world !", "o", "a"));

	return 0;
}