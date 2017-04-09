//
// ArcadeNibbler.hpp for arcade in /home/benito/rendu/cpp/cpp_arcade
//
// Made by benito
// Login   <benoit.linsey@epitech.eu>
//
// Started on  Tue Apr  4 21:34:43 2017 benito
// Last update Sun Apr  9 03:10:52 2017 benito
//

#ifndef ARCADE_NIBBLER_HPP
# define ARCADE_NIBBLER_HPP

#include <fstream>
#include <unordered_map>
#include "IGames.hpp"
#include "Snake.hpp"

enum class		Action : uint16_t
{
  DEFAULT		= 0,
  ATE			= 1,
  LOST			= 2
};

class			ArcadeNibbler : public IGames
{
public:
  static const int	NIBBLER_MAX_ROW;
  static const int	NIBBLER_MAX_COL;

  static std::unordered_map<unsigned short, ObservableKey::Keys>	_translator;
private:
  Snake			_snake;
  std::unordered_map<std::pair<int, int>, Element, pairHash>	_map;
  std::unordered_map<ObservableKey::Keys,
		     std::function<Action()>, std::hash<int>> _functors;
  bool			_gameOver;
public:
  virtual IGames::gameState		manageKey(ObservableKey::Keys);

public:
  ArcadeNibbler();
  virtual ~ArcadeNibbler();
  static Element			getElementByChar(const char);
  Snake const&				getSnake() const;
  std::unordered_map<std::pair<int, int>, Element, pairHash> const& getMap() const;
  void					moveMouli(ObservableKey::Keys);
private:
  void					loadMap(std::string const&);
  Action				turn(std::unordered_map<int, std::pair<std::pair<int, int>, Snake::Direction>>&);
  Action				turnOrDie(std::pair<int, int>, std::pair<int, int>);
  Action				ateOrDefault(std::pair<int, int>);
  arcade::TileType			getTileType(std::pair<int, int>);
  void					putPowerUp();
};

# endif // ARCADE_NIBBLER_HPP
