#include "textBox.hpp"

TextBox::TextBox(sf::Vector2u position, std::string infoText, int characterSize, sf::Color color){


	if (!font.loadFromFile("../fonts/PressStart2P2.ttf"))
	{
	   std::cout << "Font load failed!"<<std::endl;
	}
	text.setFont(font);
	text.setColor(color);
	text.setCharacterSize(characterSize);
	text.setPosition(position.x,position.y);
	addLinebreaks(infoText);

	box.setFillColor(sf::Color(189,4,240));
	box.setPosition(position.x -10, position.y -10);
	box.setSize(sf::Vector2f(text.getGlobalBounds().width+20,text.getGlobalBounds().height+20));

	//timeAlive = time;
	//clock.restart();
}


sf::Text& TextBox::getText(){
	return text;
}

sf::RectangleShape& TextBox::getBox(){
	return box;
}

void TextBox::setText(std::string infoText){
	addLinebreaks(infoText);
}

void TextBox::addLinebreaks(std::string infoText){
	std::cout << "textkoko " << infoText.length()*this->text.getCharacterSize() << std::endl;
	if(infoText.length()*this->text.getCharacterSize() > boxWidth){
		int i = 1;
		int position = (int) (boxWidth/text.getCharacterSize());
		while(1){
			std::cout << "insert tohon " << i*position << " " << i*position*text.getCharacterSize()<< std::endl;
			int j = i*position;
			while(1){
				if(infoText[j] == ' '){
					infoText.insert(j,"\n");
					break;
				}
				j--;
			}

			i++;
			if(i*position > infoText.length()){
				break;
			}
		}
	}
	text.setString(infoText);
}

void TextBox::setInfoText(TextType mode, Tile target, Item item)
{
    std::string text = "", taketext = "", placetext = "";
    switch (mode) {
        case ObjectExamine:
            std::cout << "Examine" << std::endl;
            text = "This is " + target.tooltip + ". " + target.puzzlehint;
            break;
        case NothingHappens:
            std::cout << "Nothing" << std::endl;
            text = "You use " + item.tooltip + " on " + target.tooltip + ". Nothing interesting happens.";
            break;
        case SwapItems:
            std::cout << "Swap" << std::endl;
            if (target.storage.id && item.id) {
                text = "You swap your " + target.storage.tooltip + " for " + item.tooltip;
            }
            else if (target.storage.id) {
                text = "You take " + target.storage.tooltip + " from " + target.tooltip;
            }
            else if (item.id) {
                text = "You place " + item.tooltip + " on " + target.tooltip;
            }
            else {
                text = "This is " + target.tooltip + ". There's nothing on it";
            }
            break;
        case PuzzleProgress:
            std::cout << "Puzzle" << std::endl;
            text = target.puzzleunlock;
            break;
        case UnlockLetter:
            std::cout << "Unlock" << std::endl;
            text = target.puzzlepiece.tooltip;
            break;
    }
    setText(text);
}
