//
// Arcade.cpp for Arcade.cpp in /home/tvigier/cpp_arcade
// 
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
// 
// Started on  Fri Mar 24 11:24:38 2017 thomas vigier
// Last update Sun Apr  9 22:06:11 2017 benito
//

#include "Arcade.hpp"

const int Arcade::MENU_MAX_ROW = 24;
const int Arcade::MENU_MAX_COL = 80;

Arcade::Arcade(std::string const& libName)
{
  _state = State(-1, -1, -1, Coords(Arcade::MENU_MAX_ROW, Arcade::MENU_MAX_COL), "MENU");

  _loaded = false;
  _changeLib = false;
  changeLibrary(libName);

  //getManager renvoie le gestionaire de touches de la librairie associée au menu.
  _selectedLib = _loader.getLibIdx();
  _selectedGame = 0;

  _normalFunc[ObservableKey::Up] = std::bind(&Arcade::up, this);
  _normalFunc[ObservableKey::Down] = std::bind(&Arcade::down, this);
  _normalFunc[ObservableKey::Unknown] = std::bind(&Arcade::nothing, this);
  _priorityFunc[ObservableKey::Escape] = std::bind(&Arcade::exit, this);
  _priorityFunc[ObservableKey::Return] = std::bind(&Arcade::loadGame, this);
  _priorityFunc[ObservableKey::Num2] = std::bind(&Arcade::prevLibrary, this);
  _priorityFunc[ObservableKey::Num3] = std::bind(&Arcade::nextLibrary, this);
  _priorityFunc[ObservableKey::Num4] = std::bind(&Arcade::prevGame, this);
  _priorityFunc[ObservableKey::Num5] = std::bind(&Arcade::nextGame, this);
  _priorityFunc[ObservableKey::Num8] = std::bind(&Arcade::restartGame, this);
  _priorityFunc[ObservableKey::Num9] = std::bind(&Arcade::backToMenu, this);
}

void			Arcade::changeLibrary(std::string const& libName)
{
  _lib.reset(nullptr);
  _manag.reset(nullptr);
  _lib = std::unique_ptr<ILibraries>(_loader.loadLibrary(libName));
  if (!_loaded)
    setObserver(_lib.get());
  else
    _game->setObserver(_lib.get());

  _manag = std::unique_ptr<IManageKey>(_lib->getManager());
  _manag->setObserver(this);
}

void		Arcade::loadGame()
{
  _loaded = true;
  _game.reset(nullptr);
  _game = std::unique_ptr<IGames>(_loader.loadGame(_loader.getGames()[_selectedGame].second));
  _game->setObserver(_lib.get());
}

void			Arcade::aff_menu()
{
  unsigned int		y = 0;
  Element::Colors	color;

  for (auto const& libname : _loader.getGames())
    {
      color = (y % 10 == _selectedGame ? Element::RED : Element::WHITE);
      _map[std::make_pair(0, y)] =
	Element("", color, arcade::TileType::OTHER, (std::string(libname.first)));
      y += 11;
    }
  _state.setMap(_map);
  notify();
}

void		Arcade::up()
{
  if (_selectedGame == 0)
    _selectedGame = _loader.getGames().size() - 1;
  else
    _selectedGame -= 1;
}

void		Arcade::down()
{
  _selectedGame += 1;
  if (_selectedGame >= _loader.getGames().size())
    _selectedGame = 0;
}

void		Arcade::nothing()
{}

void			Arcade::manageKey(ObservableKey::Keys key)
{
  IGames::gameState	ret = IGames::PLAYING;

  auto const& it = _priorityFunc.find(key);

  if (it != _priorityFunc.end())
    it->second();
  else
    {
      if (_loaded == true)
	{
	  ret = _game->manageKey(key);
	  if (ret == IGames::FINISHED)
	    {
	      setObserver(_lib.get());
	      _loaded = false;
	    }
	}
      else
	{
	  auto it2 = _normalFunc.find(key);

	  if (it2 != _normalFunc.end())
	    it2->second();
	  aff_menu();
	}
    }
}

void		Arcade::nextGame()
{
  up();
  loadGame();
}

void		Arcade::prevGame()
{
  down();
  loadGame();
}

void		Arcade::backToMenu()
{
  _loaded = false;
  _game.reset(nullptr);
  setObserver(_lib.get());
}

void		Arcade::restartGame()
{
  loadGame();
}

void		Arcade::nextLibrary()
{
  _selectedLib += 1;
  if (_selectedLib >= _loader.getLibraries().size())
    _selectedLib = 0;
  exit();
  _changeLib = true;
}

void		Arcade::prevLibrary()
{
  if (_selectedLib == 0)
    _selectedLib = _loader.getLibraries().size() - 1;
  else
    _selectedLib -= 1;
  exit();
  _changeLib = true;
}

void		Arcade::actualize(Observable const& ob)
{
  manageKey(static_cast<const ObservableKey&>(ob).getKey());
}

bool		Arcade::isNotOver() const
{
  if (_manag->isFinished() == false)
    {
      return true;
    }
  return false;
}

void		Arcade::exit()
{
  _changeLib = false;
  _manag->finish();
}

void		Arcade::launch()
{
  _manag->catchKey();
  if (_changeLib == true)
    changeLibrary(_loader.getLibraries()[_selectedLib].second);
}

Arcade::~Arcade()
{
}
