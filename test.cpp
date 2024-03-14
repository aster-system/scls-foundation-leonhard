#include "basix.h"

#include <map>

int main()
{
    std::string text = "Étude du mouvement des étoiles à la lunette inclinée";
    basix::Text_Image_Data datas; datas.font_family = "FreeMono.ttf"; datas.blue = 0;
    basix::Image* image = basix::text_image(basix::to_utf_8(text), datas);
    image->save_png("text.png");

	return 0;
}
