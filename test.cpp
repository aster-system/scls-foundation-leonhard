#include "basix.h"

int main()
{
	std::string base_path = "before.png";

	basix::Image image(base_path);

	std::string content = basix::replace(basix::read_file("bin/very_long_text.txt").substr(0, 500), "\n", " ");
	basix::Image* text_image = basix::text_image(content);
	text_image->save_png("text.png");

    delete text_image; text_image = 0;

	basix::print("Test", "Debugger", "Hello world !");

	return 0;
}
