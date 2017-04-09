//
// Arcade.hpp for  in /home/anthony/rendu/cpp/cpp_arcade/sources
//
// Made by Anthony Jouvel
// Login   <anthony.jouvel@epitech.eu>
//
// Started on  Tue Apr  4 19:06:34 2017 Anthony Jouvel
// Last update Sun Apr  9 19:01:55 2017 benito
//

#ifndef ARCADE_HPP_
# define ARCADE_HPP_

#include "IGames.hpp"
#include "ILibraries.hpp"
#include "ObservableGame.hpp"
#include "ObservableKey.hpp"
#include "DLLoader.hpp"
#include "IManageKey.hpp"

class Arcade : public ObservableGame, public AObserver
{
public:
  static const int	MENU_MAX_ROW;
  static const int	MENU_MAX_COL;
private:
  DLLoader			_loader;
  unsigned int			_selectedLib;
  unsigned int			_selectedGame;
  std::unordered_map<std::pair<int, int>, Element, pairHash>    _map;
  std::unordered_map<ObservableKey::Keys, std::function<void()>, std::hash<int>> _priorityFunc;
  std::unordered_map<ObservableKey::Keys, std::function<void()>, std::hash<int>> _normalFunc;
  std::unique_ptr<ILibraries>	_lib;
  std::unique_ptr<IManageKey>	_manag;
  std::unique_ptr<IGames>	_game;
  bool				_loaded;
  bool				_changeLib;

  void		manageKey(ObservableKey::Keys);

  void		manageKey(std::string const&);
  void		nextLibrary(); // '3'
  void		prevLibrary(); // '2'
  void		exit(); // 'Escape'
  void		actualize(Observable const&);

  void		up();
  void		down();
  void		nothing();
  void		loadGame();
  void		changeLibrary(std::string const&);
  void		nextGame();
  void		prevGame();
  void		backToMenu();
  void		restartGame();
public:
  void		launch();
  void		aff_menu();
  bool		isNotOver() const;

public:
  Arcade(std::string const&);
  ~Arcade();
};

#endif // ARCADE_HPP_
