#ifndef TEXTBOX_HH
#define TEXTBOX_HH

#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.hpp"

class TextBox
{
public:
	TextBox(sf::Vector2u position, std::string text, int characterSize, sf::Color color);
	~TextBox(){};

    enum TextType {
        ObjectExamine,
        NothingHappens,
        SwapItems,
        PuzzleProgress,
        UnlockLetter
    };

	//return the text
	sf::Text getText();

	//return the shape
	sf::RectangleShape getBox();

	void setText(std::string);

    void setInfoText(TextType, Tile, Item = {});

	//add linebreaks to text so it fits the box
	void addLinebreaks(std::string);

private:
	sf::Text text;
	sf::Font font;
	sf::Clock clock;
	sf::RectangleShape box;
	int boxWidth = 1420;

};

#endif /* TEXTBOX_HH */
