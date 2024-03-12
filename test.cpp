#include "basix.h"

int main()
{
	std::string base_path = "before.png";

	basix::Image image(base_path);

    basix::Image* text = basix::text("Hello world !");
    text->save_png("after.png");
	delete text; text = 0;

	basix::print("Test", "Debugger", "Hello world !");

	return 0;
}
