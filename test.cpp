#include "basix.h"

int main()
{
	std::string base_path = "before.png";

	basix::Image image(base_path);

	std::string content = basix::replace(basix::read_file("bin/very_long_text.txt").substr(0, 998), ". ", ".\n");
	basix::Text_Image_Data datas;
	datas.blue = 255; datas.red = 124;
	datas.font_size = 50; datas.font_family = "arial.ttf";

	basix::Image* text_image_l = basix::text_image(content, datas); datas.alignment = basix::Center;
	basix::Image* text_image_c = basix::text_image(content, datas); datas.alignment = basix::Right;
	basix::Image* text_image_r = basix::text_image(content, datas);
	text_image_l->save_png("text1.png");
	text_image_c->save_png("text2.png");
	text_image_r->save_png("text3.png");

    delete text_image_l; text_image_l = 0;
    delete text_image_c; text_image_c = 0;
    delete text_image_r; text_image_r = 0;

	basix::print("Test", "Debugger", "Hello world !");

	return 0;
}
