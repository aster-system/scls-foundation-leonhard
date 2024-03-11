#include "basix.h"

int main()
{
	std::string base_path = "before.png";

	basix::Image image;
	image.load_from_path(base_path);

	image.draw_rect(0, 0, 500, 500, 255, 255, 255);
	image.save_png("after.png");

	basix::print("Test", "Debugger", "Hello world !");

	return 0;
}
