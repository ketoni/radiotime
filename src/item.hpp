#ifndef ITEM_HH
#define ITEM_HH

#include <SFML/Graphics.hpp>

struct Item
{
    unsigned id;
   
    std::string tooltip;
    std::string texname;

    sf::Texture texture;
    sf::Sprite sprite;
};

#endif /* ITEM_HH */
