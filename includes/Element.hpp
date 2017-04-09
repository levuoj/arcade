//
// Element.hpp for  in /home/anthony/rendu/cpp/cpp_arcade
// 
// Made by Anthony
// Login   <anthony.jouvel@epitech.eu>
// 
// Started on  Thu Mar 23 16:00:00 2017 Anthony
// Last update Sat Apr  8 20:17:04 2017 benito
//

#ifndef ELEMENT_HPP
# define ELEMENT_HPP

#include <iostream>
#include "Protocol.hpp"

class Element
{
public:
    enum Colors
    {
      BLACK		= 0,
      RED		= 1,
      GREEN		= 2,
      YELLOW		= 3,
      BLUE		= 4,
      MAGENTA		= 5,
      CYAN		= 6,
      WHITE		= 7,
      BLOCK_RED		= 11,
      BLOCK_GREEN	= 12,
      BLOCK_YELLOW	= 13,
      BLOCK_BLUE	= 14,
      BLOCK_MAGENTA	= 15,
      BLOCK_CYAN	= 16,
      BLOCK_WHITE	= 17
    };

private:
  std::string		_spritePath;
  Element::Colors	_color;
  arcade::TileType	_type;
  std::string		_content;

public:
  std::string	        const& getSpritePath() const;
  std::string		const& getContent() const;
  Element::Colors	const& getColor() const;
  arcade::TileType	const& getType() const; // GET ASCII CHARACTER
  Element(std::string const&, Element::Colors, arcade::TileType, std::string const&);
  Element();
  ~Element();
  //rajouter setColor
};

#endif /* !ELEMENT_HPP */
