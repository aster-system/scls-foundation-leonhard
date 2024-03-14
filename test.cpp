#include "basix.h"

#include <map>

int main()
{
    std::string text = "Español";
    basix::Text_Image_Data datas; datas.font_family = "DejaVu"; datas.font_presentation = "Bold"; datas.font_type = "Sans";
    datas.font_size = 500;datas.red = 255;
    datas.background_alpha = 255; datas.background_blue = 255; datas.background_green = 255; datas.background_red = 255;
    basix::Image* image = basix::text_image(basix::to_utf_8(text), datas);
    image->save_png("text.png");

	return 0;
}
