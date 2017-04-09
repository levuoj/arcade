//
// Element.cpp for Element.cpp in /home/tvigier/cpp_arcade/sources
// 
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
// 
// Started on  Mon Mar 27 18:45:58 2017 thomas vigier
// Last update Sun Apr  9 22:15:41 2017 benito
//

#include "Element.hpp"

Element::Element(std::string const& path, Element::Colors color, arcade::TileType tile, std::string const& content) : _spritePath(path), _color(color), _type(tile), _content(content) {}

Element::Element() {}

Element::~Element() {}

std::string const&	Element::getSpritePath() const
{
  return (_spritePath);
}

Element::Colors const&	Element::getColor() const
{
  return (_color);
}

arcade::TileType const&	Element::getType() const
{
  return (_type);
}

std::string const&	Element::getContent() const
{
  return (_content);
}
