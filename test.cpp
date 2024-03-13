#include "basix.h"

#include <map>

int main()
{
    std::string text = "Étude du mouvement des étoiles à la lunette inclinée";
    basix::Image* image = basix::text_image(basix::to_utf_8(text));
    image->save_png("text.png");

	return 0;
}
