//
// LibrarySFML.cpp for  in /home/anthony/rendu/cpp/cpp_arcade/sources/SFML
//
// Made by Anthony Jouvel
// Login   <anthony.jouvel@epitech.eu>
//
// Started on  Mon Apr  3 11:29:39 2017 Anthony Jouvel
// Last update Sun Apr  9 22:11:28 2017 benito
//

#include <iostream>
#include "LibrarySFML.hpp"

LibrarySFML::LibrarySFML()
{
  colorSfml =
    {
      {Element::BLACK, sf::Color::Black},
      {Element::RED, sf::Color::Red},
      {Element::GREEN, sf::Color::Green},
      {Element::YELLOW, sf::Color::Yellow},
      {Element::BLUE, sf::Color::Blue},
      {Element::MAGENTA, sf::Color::Magenta},
      {Element::CYAN, sf::Color::Cyan},
      {Element::WHITE, sf::Color::White}
    };

  sf::RenderWindow *win;

  win = new sf::RenderWindow(sf::VideoMode(1920, 1080), "My window");
  _manage = new ManageKeySFML(win);
  _window = std::unique_ptr<sf::RenderWindow>(win);

  if (!_music.openFromFile("sources/SFML/sounds/wow.ogg"))
    exit(0);

  _music.setLoop(true);
  _music.play();
  _music.setVolume(100);

  DIR		*Dir = opendir("sources/SFML/images/");
  struct dirent *DirEntry;
  std::string	name;
  sf::Texture	tex;

  while ((DirEntry=readdir(Dir)) != NULL)
    {
      name = std::string(DirEntry->d_name);
      if (name.find(".png") != std::string::npos)
	{
	  if (!tex.loadFromFile("./sources/SFML/images/" + name))
	    throw std::runtime_error("An error (occured when loading " + name + ")");
	  _textures["./sources/SFML/images/" + name] = tex;
	}
    }
}

LibrarySFML::~LibrarySFML()
{
  _window->close();
}

void			LibrarySFML::displayMap(State const &state)
{

  for (auto const& it : state.getMap())
    {
      if (it.second.getSpritePath() == "" && it.second.getContent() != "")
	{
	  sf::Font font;
	  _font = font;
	  sf::Text text = textLoader(it.second.getContent(), it.second.getColor());
	  text.setPosition(it.first.first * _resizeFactor + _paddingX,
			   it.first.second * _resizeFactor + _paddingY);
	  _window->draw(text);
	}
      if (it.second.getSpritePath() != "")
	{
	  sf::Sprite sprite;
	  sprite.setTexture(_textures[it.second.getSpritePath()]);
	  sprite = resize(sprite);
	  sprite.setPosition(it.first.first * _resizeFactor + _paddingX,
			     it.first.second * _resizeFactor + _paddingY);
	  _window->draw(sprite);
	}
    }
}

void			LibrarySFML::displayScore(State const &state)
{
  if (state.getScore() < 0)
    return ;
  sf::Font font;
  _font = font;
  sf::Text text = textLoader("SCORE : " + std::to_string(state.getScore()), Element::Colors::RED);
  text.setPosition(_maxCol / 2 - 100, 25);
  _window->draw(text);
}

void			LibrarySFML::displayTimer(State const &state)
{
  if (state.getTime() < 0)
    return ;
  sf::Font font;
  _font = font;
  sf::Text text = textLoader("TIMER : " + std::to_string(state.getTime()), Element::Colors::RED);
  text.setPosition(_maxCol - _maxCol / 10 - 200, _maxRow / 2);
  _window->draw(text);
}

void			LibrarySFML::displayLife(State const &state)
{
  if (state.getLife() < 0)
    return ;
  sf::Font font;
  _font = font;
  sf::Text text = textLoader("LIFE : " + std::to_string(state.getLife()), Element::Colors::RED);
  text.setPosition(_maxCol / 2 - 100, _maxRow - 75);
  _window->draw(text);
}

void			LibrarySFML::displayName(State const &state)
{
  if (state.getName() == "")
    return ;
  sf::Font font;
  _font = font;
  sf::Text text = textLoader(state.getName(), Element::Colors::RED);
  text.setPosition(_maxCol / 10, _maxRow / 2);
  _window->draw(text);
}

sf::Sprite		LibrarySFML::resize(sf::Sprite sprite)
{
  sf::IntRect r = sprite.getTextureRect();
  float factor_w = _resizeFactor / r.width;
  float factor_h = _resizeFactor / r.height;

  sprite.scale(factor_w, factor_h);
  return (sprite);
}

sf::Text		LibrarySFML::textLoader(std::string const &content, Element::Colors color)
{
  sf::Text			text;

  if (!_font.loadFromFile("sources/SFML/fonts/Coalition_v2..ttf"))
    throw std::runtime_error("An error (occured when loading Coalition_v2..ttf)");
  text.setFont(_font);
  text.setString(content);
  text.setCharacterSize(30);
  text.setColor(LibrarySFML::colorSfml[color]); // A VERIFIER (AUTO FIND)
  return (text);
}

void			LibrarySFML::display(State const &state)
{

  sf::Vector2u		vec = _window->getSize();

  _maxRow = vec.y;
  _maxCol = vec.x;
  _resizeFactor = vec.y / (state.getMapSize().getY()
				 + (state.getMapSize().getY() - state.getMapSize().getY() * 0.8)) - 2.25;

  _window->setVerticalSyncEnabled(true);

  sf::RectangleShape rectangle(sf::Vector2f(vec.y * 0.8, vec.y * 0.8));

  _paddingX = vec.x / 2 - rectangle.getSize().y / 2;
  _paddingY = (vec.y - vec.y * 0.8) / 2;

  rectangle.setOutlineThickness(5);
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineColor(sf::Color::White);
  rectangle.setPosition(_paddingX, _paddingY);

  _window->clear(sf::Color::Black);

  displayMap(state);
  _window->draw(rectangle);
  displayScore(state);
  displayName(state);
  displayTimer(state);
  displayLife(state);
  _window->display();
}

void			LibrarySFML::actualize(Observable const &ob)
{
  display(static_cast< const ObservableGame&>(ob).getState());
}

IManageKey		*LibrarySFML::getManager() const
{
  return (_manage);
}

extern "C"
ILibraries		*entryPoint()
{
  return new LibrarySFML;
}
