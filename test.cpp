#include "basix.h"

int main()
{
	std::string base_path = "J:/Projets/Matix/matix/assets/textures";
	std::vector<std::string> path = basix::directory_content(base_path, true);

	unsigned short loaded = 0;
	unsigned short loaded_successfully = 0;

	for (int i = 0; i < path.size(); i++)
	{
		std::vector<std::string> cutted = basix::cut_string(path[i], ".");
		if (basix::file_exists(path[i]) && cutted[cutted.size() - 1] == "png")
		{
			std::cout << "Loading " << path[i] << std::endl;
			basix::PNG_Image image;
			image.load_from_path(path[i]);
			if (image.is_loadable())
			{
				std::cout << "Path " << path[i] << " successfully loaded" << std::endl;
				loaded_successfully++;
			}
			else
			{
				std::cout << "Path " << path[i] << " not loaded" << std::endl;
			}
			loaded++;
		}
	}

	std::cout << loaded_successfully << "/" << loaded << " images loaded successfully, so " << ((float)loaded_successfully / (float)loaded) * 100.0 << "%" << std::endl;

	return 0;
}