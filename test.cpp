#include "basix.h"

int main()
{
	basix::PNG_Image image;
	image.load_from_path("test.png");

	return 0;
}