#include "basix.h"

int main()
{
	/*std::string base_path = "J:/Projets/Matix/matix/assets/textures/welcome_hud/background.png";

	for (int i = 0; i < 1; i++)
	{
		basix::PNG_Image image;
		image.load_from_path(base_path);

		unsigned char* datas = image.data();

		for (int i = 0;i<image.get_height();i++)
		{
			for (int j = 0; j < image.get_width(); j++)
			{
				std::cout << "Pixel " << j << "-" << i << " : " << (int)image.get_pixel(j, i).red << " " << (int)image.get_pixel(j, i).green << " " << (int)image.get_pixel(j, i).blue << " " << (int)image.get_pixel(j, i).alpha << std::endl;
			}
		}

		if (image.is_loadable())
		{
			std::cout << "Path " << base_path << " successfully loaded" << std::endl;
		}
		else
		{
			std::cout << "Path " << base_path << " not loaded : error " << (int)image.get_error_load() << std::endl;
		}
	}//*/

	/*unsigned short loaded = 0;
	unsigned short loaded_successfully = 0;

	for (int i = 0; i < path.size(); i++)
	{
		std::vector<std::string> cutted = basix::cut_string(path[i], ".");
		if (basix::file_exists(path[i]) && cutted[cutted.size() - 1] == "png")
		{
			std::cout << "Loading " << path[i] << std::endl;
			std::string test = "";
			basix::PNG_Image image;
			image.load_from_path(path[i]);
			image.flip_y();
			unsigned char* datas = image.data();
			if (image.is_loadable())
			{
				std::cout << "Path " << path[i] << " successfully loaded" << std::endl;
				loaded_successfully++;
			}
			else
			{
				std::cout << "Path " << path[i] << " not loaded : error " << (int)image.get_error_load() << std::endl;
			}
			loaded++;

			std::cout << loaded_successfully << "/" << loaded << " images loaded successfully, so " << ((float)loaded_successfully / (float)loaded) * 100.0 << "%" << std::endl;
		}
	}

	std::cout << loaded_successfully << "/" << loaded << " images loaded successfully, so " << ((float)loaded_successfully / (float)loaded) * 100.0 << "%" << std::endl;
	//*/

	// basix::Image image = basix::Image(500, 500, 255, 0, 0);
	
	// basix::Image image = basix::Image();
	// image.load_from_path("cool_square.png");
	// image.save_png("test.png");

	char* c = new char[8]; double n = 13475.135478;
	basix::put_8bytes_double_to_char_array(n, c);

	basix::write_in_file_binary("test.bin", c, 8);

	char* d = new char[8];
	basix::read_file_binary("test.bin", d, 8);
	double chiffre = basix::extract_double_from_char_array(d);

	std::cout << std::setprecision(10) << "U " << n << " " << chiffre << " " << c << " " << d << std::endl;

	return 0;
}