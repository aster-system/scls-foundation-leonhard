#include "basix.h"

int main()
{
	std::string base_path = "before.png";

	basix::Image image(base_path);

	std::string content = basix::replace(basix::read_file("bin/very_long_text.txt").substr(0, 500), "\n", " ");
	content = "a";
	// basix::Image* text_image = basix::text_image(content);
	basix::Image* text_image = new basix::Image(500, 500, 255, 0, 0);
	text_image->fill(255, 0, 0);
	text_image->draw_rect(0, 498, 500, 1, 0, 255, 0);
	std::cout << (int)text_image->get_pixel(495, 499).blue << std::endl;
    text_image->save_png("text.png");
	delete text_image; text_image = 0;

	basix::print("Test", "Debugger", "Hello world !");

	return 0;
}
