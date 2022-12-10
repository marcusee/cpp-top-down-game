#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <array>
#include <memory>

class TextureBank {

private:
	static std::unordered_map <std::string, std::shared_ptr<sf::Texture>> textureMap;

public:


	static sf::Texture * getTexture(std::string image_name) {
		auto got = textureMap.find(image_name);
		if (got == textureMap.end()) {
			loadTexture(image_name);
		}
		return textureMap[image_name].get();
	}

	static void loadTexture(std::string image_name) {
		std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
		if (!texture->loadFromFile("resources/" + image_name + ".png"))
			std::cerr << "File not found " << std::endl;
		textureMap[image_name] = texture;
	}


};
