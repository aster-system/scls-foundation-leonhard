#include "basix.h"

int main()
{
	std::string base_path = "before.png";

	basix::Image image(base_path);

	image.paste("croix.png", 0, 0);

	image.save_png("after.png");

	basix::print("Test", "Debugger", "Hello world !");

	return 0;
}
