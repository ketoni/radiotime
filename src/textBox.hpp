#include <SFML/Graphics.hpp>
#include <iostream>

class TextBox
{
public:
	TextBox(sf::Vector2u position, std::string text, int characterSize, sf::Color color);
	~TextBox(){};

	//return the text
	sf::Text getText();

	//return the shape
	sf::RectangleShape getBox();

	void setText(std::string);

	//add linebreaks to text so it fits the box
	void addLinebreaks(std::string);

private:
	sf::Text text;
	sf::Font font;
	sf::Clock clock;
	sf::RectangleShape box;
	int boxWidth = 700;

};

