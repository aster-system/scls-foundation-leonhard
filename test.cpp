#include "basix.h"

#include <map>

int main()
{
    std::string text = "Acajou\nBague\nJogging";
    basix::Text_Image_Data datas; datas.font = basix::get_system_font("NotoSans", true, false, true);
    datas.font_size = 50;datas.red = 255;
    datas.background_alpha = 255; datas.background_blue = 255; datas.background_green = 255; datas.background_red = 255;
    datas.out_offset_bottom_width = 20;
    datas.out_offset_left_width = 20;
    datas.out_offset_right_width = 20;
    datas.out_offset_top_width = 20;
    datas.alignment = basix::Right;

    basix::Image* image = basix::text_image(basix::to_utf_8(text), datas);
    image->save_png("text.png");

	return 0;
}
