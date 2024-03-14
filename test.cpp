#include "basix.h"

#include <map>

int main()
{
    basix::load_system_font();

    std::string text = "Le char Leclerc";
    basix::Text_Image_Data datas; datas.font = basix::get_system_font("4");
    datas.font_size = 50;datas.red = 255;
    datas.background_alpha = 255; datas.background_blue = 255; datas.background_green = 255; datas.background_red = 255;

    basix::Image* image = basix::text_image(basix::to_utf_8(text), datas);
    image->save_png("text.png");

	return 0;
}
