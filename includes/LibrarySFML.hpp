//
// LibrarySFML.hpp for LibrarySFML.hpp in /home/tvigier/cpp_arcade
// 
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
// 
// Started on  Mon Apr  3 19:39:05 2017 thomas vigier
// Last update Sat Apr  8 16:18:51 2017 thomas vigier
//

#ifndef LIBRARYSFML_HPP_
# define LIBRARYSFML_HPP_

#include <sys/types.h>
#include <dirent.h>
#include "ManageKeySFML.hpp"
#include "ILibraries.hpp"
#include "State.hpp"

class			LibrarySFML : public ILibraries
{
private:
  int			_paddingX;
  int			_paddingY;
  sf::SoundBuffer	_buffer;
  sf::Music		_music;
  float			_resizeFactor;
  sf::Font		_font;
  ManageKeySFML		*_manage;
  std::unique_ptr<sf::RenderWindow> _window;
  int			_maxRow;
  int			_maxCol;

  std::unordered_map<std::string, sf::Texture> _textures;

  virtual void		display(State const &);

  virtual void		displayMap(State const &);
  virtual void		displayScore(State const &);
  virtual void		displayTimer(State const &);
  virtual void		displayLife(State const &);
  virtual void		displayName(State const &);

  virtual IManageKey	*getManager() const;


  std::unordered_map<Element::Colors,sf::Color, std::hash<int>> colorSfml;
 
public:
  LibrarySFML();
  virtual		~LibrarySFML();
  virtual void		actualize(Observable const &);

  sf::Sprite		spriteLoader(std::string const&);
  sf::Text		textLoader(std::string const&, Element::Colors);
  sf::Sprite		resize(sf::Sprite);

};

#endif // LIBRARYSFML_HPP_
