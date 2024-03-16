#include "basix.h"

#include <map>

int main()
{
    std::string text = "Le char de combat Leclerc\nLe bijou français";
    basix::Text_Image_Data datas; datas.font = basix::get_system_font("NotoSans", true, true, true);
    datas.font_size = 50;datas.red = 255;
    datas.background_alpha = 255; datas.background_blue = 0; datas.background_green = 255; datas.background_red = 0;
    datas.alignment = basix::Center;

    basix::Image* image = basix::text_image(basix::to_utf_8(text), datas);
    image->save_png("text.png");

	return 0;
}
