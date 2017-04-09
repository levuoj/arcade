//
// ArcadeCentipede.hpp for ArcadeCentipede.hpp in /home/tvigier/cpp_arcade
//
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
//
// Started on  Thu Apr  6 19:01:33 2017 thomas vigier
// Last update Sun Apr  9 21:26:27 2017 Anthony Jouvel
//

#ifndef ARCADE_CENTIPEDE_HPP
# define ARCADE_CENTIPEDE_HPP_

#include "IGames.hpp"
#include "BugBlaster.hpp"
#include "Snake.hpp"

class			ArcadeCentipede : public IGames
{
public:
  static std::unordered_map<unsigned short, ObservableKey::Keys>        _translator;
private:
  static const int	CENTI_COL = 30;
  static const int	CENTI_ROW = 30;

  std::unordered_map<std::pair<int, int>, Element, pairHash>	_map;
  std::unordered_map<ObservableKey::Keys, std::function<void()>, std::hash<int>> _functors;
  BugBlaster		_bug;
  bool			_canShoot;
  int			_winner;
  std::pair<int, int>	_shoot;
  Snake			_snake;
public:
  BugBlaster const&	getBug() const;
  void			checkWalls(std::unordered_map<std::pair<int, int>, Element, pairHash>&);
  Element		getElement(int, int);
  static Element	getElementByChar(const char c);
  void			fillMap();
  virtual IGames::gameState		manageKey(ObservableKey::Keys);
  std::unordered_map<std::pair<int, int>, Element, pairHash> const& getMap() const;
  void			setMap(std::unordered_map<std::pair<int, int>, Element, pairHash> const&);

  void			up();
  void			down();
  void			left();
  void			right();
  void			shoot();
  void			moveShoot();

  ArcadeCentipede();
  virtual ~ArcadeCentipede();
};

#endif // ARCADE_CENTIPEDE_HPP
