//
// ArcadeNibbler.cpp for arcade in /home/benito/rendu/cpp/cpp_arcade
//
// Made by benito
// Login   <benoit.linsey@epitech.eu>
//
// Started on  Tue Apr  4 22:02:26 2017 benito
// Last update Sun Apr  9 15:56:36 2017 Anthony Jouvel
//

#include <random>
#include <unistd.h>
#include "Protocol.hpp"
#include "ArcadeNibbler.hpp"
#include "Snake.hpp"
#include "Arcade.hpp"

const int ArcadeNibbler::NIBBLER_MAX_ROW = 15;
const int ArcadeNibbler::NIBBLER_MAX_COL = 15;

std::unordered_map<unsigned short, ObservableKey::Keys> ArcadeNibbler::_translator =
  {
    {static_cast<unsigned short>(arcade::CommandType::GO_UP), ObservableKey::Up},
    {static_cast<unsigned short>(arcade::CommandType::GO_DOWN), ObservableKey::Down},
    {static_cast<unsigned short>(arcade::CommandType::GO_LEFT), ObservableKey::Left},
    {static_cast<unsigned short>(arcade::CommandType::GO_RIGHT), ObservableKey::Right},
    {static_cast<unsigned short>(arcade::CommandType::PLAY), ObservableKey::Unknown}
  };

std::unordered_map<int, std::unordered_map<int, std::pair<std::pair<int, int>, Snake::Direction>>> dir =
  {
    {0,
     {
       {0, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(0, 1), Snake::UP)},
       {1, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(0, -1), Snake::DOWN)},
       {2, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(-1, 0), Snake::LEFT)},
       {3, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(1, 0), Snake::RIGHT)}
     }
    },
    {1,
     {
       {0, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(0, -1), Snake::DOWN)},
       {1, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(0, 1), Snake::UP)},
       {2, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(1, 0), Snake::RIGHT)},
       {3, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(-1, 0), Snake::LEFT)}
     }
    },
    {2,
     {
       {0, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(1, 0), Snake::RIGHT)},
       {1, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(-1, 0), Snake::LEFT)},
       {2, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(0, -1), Snake::UP)},
       {3, std::pair<std::pair<int, int>, Snake::Direction>(std::make_pair(0, 1), Snake::DOWN)}
     }
    }
  };

ArcadeNibbler::ArcadeNibbler()
{
  _state = State(-1, 0, 1, Coords(ArcadeNibbler::NIBBLER_MAX_ROW, ArcadeNibbler::NIBBLER_MAX_COL), "Nibbler");
  loadMap("games/nibbler_map/1.map");
}

ArcadeNibbler::~ArcadeNibbler()
{}

Element			ArcadeNibbler::getElementByChar(const char c)
{
  std::string		sprite;
  Element::Colors	color;
  arcade::TileType	type;
  std::string		content;

  content.push_back(c);
  switch (c) {
  case 'X':
    sprite = "./sources/SFML/images/block.png";
    color = Element::YELLOW;
    type = arcade::TileType::BLOCK;
    break;
  case ' ':
    sprite = "";
    color = Element::BLACK;
    type = arcade::TileType::EMPTY;
    break;
  case '~':
    sprite = "./sources/SFML/images/snake_body.png";
    color = Element::GREEN;
    type = arcade::TileType::OTHER;
    break;
  case '>':
    sprite = "./sources/SFML/images/snake_head_right.png";
    color = Element::GREEN;
    type = arcade::TileType::OTHER;
    break;
  case '^':
    sprite = "./sources/SFML/images/snake_head_up.png";
    color = Element::GREEN;
    type = arcade::TileType::OTHER;
    break;
  case '<':
    sprite = "./sources/SFML/images/snake_head_left.png";
    color = Element::GREEN;
    type = arcade::TileType::OTHER;
    break;
  case 'v':
    sprite = "./sources/SFML/images/snake_head_down.png";
    color = Element::GREEN;
    type = arcade::TileType::OTHER;
    break;
  case '*':
    sprite = "./sources/SFML/images/fruit.png";
    color = Element::MAGENTA;
    type = arcade::TileType::POWERUP;
  }
  return (Element(sprite, color, type, content));
}

void		ArcadeNibbler::loadMap(std::string const& fileName)
{
  std::ifstream	file(fileName);
  std::string	line;
  unsigned int	x, y = 0;

  if (file.is_open())
    {
      while (std::getline(file, line))
	{
	  x = 0;
	  for (const char c : line)
	    {
	      _map[std::pair<int, int>(x, y)] = getElementByChar(c);
	      if (c == '>')
		_snake = Snake(x, y);
	      ++x;
	    }
	  ++y;
	}
      putPowerUp();
      file.close();
    }
  else
    throw std::runtime_error("Don't remove my files lil' bastard");
}

IGames::gameState	ArcadeNibbler::manageKey(ObservableKey::Keys key)
{
  Action		action = Action::DEFAULT;

  if (key == ObservableKey::Left)
    action = turn(dir[0]);
  else if (key == ObservableKey::Right)
    action = turn(dir[1]);
  else
    {
      action = turn(dir[2]);
    }
  if (action == Action::ATE)
    {
      _state.setScore(_state.getScore() + 25);
      action = _snake.grow(_map);
      putPowerUp();
    }
  if (action == Action::LOST)
    {
      _state.setLife(0);
      return (IGames::FINISHED);
    }
  _snake.move(_map);
  _state.setMap(_map);

  notify();

  return (IGames::PLAYING);
}

arcade::TileType		ArcadeNibbler::getTileType(std::pair<int, int> xy)
{
  return (_map[std::pair<int, int>(_snake.getHeadX() + xy.first, _snake.getHeadY() + xy.second)].getType());
}

Action				ArcadeNibbler::ateOrDefault(std::pair<int, int> xy)
{
  if (_map[std::make_pair(_snake.getHeadX() + xy.first, _snake.getHeadY() + xy.second)].getType() == arcade::TileType::POWERUP)
    return (Action::ATE);
  return (Action::DEFAULT);
}

Action		ArcadeNibbler::turnOrDie(std::pair<int, int> choiceOne, std::pair<int, int> choiceTwo)
{
  if (getTileType(choiceOne) == arcade::TileType::EMPTY || getTileType(choiceOne) == arcade::TileType::POWERUP)
    {
      if (_snake.getDirection() == Snake::LEFT)
	_snake.setDirection(Snake::DOWN);
      else
	_snake.setDirection(static_cast<Snake::Direction>(_snake.getDirection() - 1));
      return (ateOrDefault(choiceOne));
    }
  if (getTileType(choiceTwo) == arcade::TileType::EMPTY || getTileType(choiceTwo) == arcade::TileType::POWERUP)
    {
      if (_snake.getDirection() == Snake::DOWN)
	_snake.setDirection(Snake::LEFT);
      else
	_snake.setDirection(static_cast<Snake::Direction>(_snake.getDirection() + 1));
      return (ateOrDefault(choiceTwo));
    }
  return (Action::LOST);
}

Action				ArcadeNibbler::turn(std::unordered_map<int,
						    std::pair<std::pair<int, int>, Snake::Direction>>& ope)
{
  Action			act;

  switch (_snake.getDirection()) {
  case Snake::RIGHT :
    if (getTileType(ope[0].first) == arcade::TileType::EMPTY || getTileType(ope[0].first) == arcade::TileType::POWERUP)
      {
	act = ateOrDefault(ope[0].first);
	_snake.setDirection(ope[0].second);
      }
    else if (getTileType(ope[0].first) == arcade::TileType::OTHER)
      act = Action::LOST;
    if (_snake.getDirection() == ope[0].second && getTileType(ope[0].first) == arcade::TileType::BLOCK)
      act = turnOrDie(std::make_pair(0, -1), std::make_pair(0, 1));
    break;

  case Snake::LEFT :
    if (getTileType(ope[1].first) == arcade::TileType::EMPTY || getTileType(ope[1].first) == arcade::TileType::POWERUP)
      {
	act = ateOrDefault(ope[1].first);
	_snake.setDirection(ope[1].second);
      }
    else if (getTileType(ope[1].first) == arcade::TileType::OTHER)
      act = Action::LOST;

    if (_snake.getDirection() == ope[1].second && getTileType(ope[1].first) == arcade::TileType::BLOCK)
      act = turnOrDie(std::make_pair(0, 1), std::make_pair(0, -1));
    break;

  case Snake::UP :
    if (getTileType(ope[2].first) == arcade::TileType::EMPTY || getTileType(ope[2].first) == arcade::TileType::POWERUP)
      {
	act = ateOrDefault(ope[2].first);
	_snake.setDirection(ope[2].second);
      }
    else if (getTileType(ope[2].first) == arcade::TileType::OTHER)
      act = Action::LOST;

    if (_snake.getDirection() == ope[2].second && getTileType(ope[2].first) == arcade::TileType::BLOCK)
      act = turnOrDie(std::make_pair(-1, 0), std::make_pair(1, 0));
    break;

  case Snake::DOWN :
    if (getTileType(ope[3].first) == arcade::TileType::EMPTY || getTileType(ope[3].first) == arcade::TileType::POWERUP)
      {
	act = ateOrDefault(ope[3].first);
	_snake.setDirection(ope[3].second);
      }
    else if (getTileType(ope[3].first) == arcade::TileType::OTHER)
      act = Action::LOST;

    if (_snake.getDirection() == ope[3].second && getTileType(ope[3].first) == arcade::TileType::BLOCK)
      act = turnOrDie(std::make_pair(1, 0), std::make_pair(-1, 0));
    break;
  }
  return (act);
}

void					ArcadeNibbler::putPowerUp()
{
  std::random_device			rd;
  std::default_random_engine		gen(rd());
  std::uniform_int_distribution<int>	row(1, NIBBLER_MAX_ROW - 1);
  std::uniform_int_distribution<int>	col(1, NIBBLER_MAX_COL - 1);
  bool					placed = false;

  while (!placed)
    {
      auto const& pr = std::make_pair(col(gen), row(gen));
      if (_map[pr].getType() == arcade::TileType::EMPTY)
	{
	  _map[pr] = ArcadeNibbler::getElementByChar('*');
	  placed = true;
	}
    }
}

Snake const&		ArcadeNibbler::getSnake() const
{
  return (_snake);
}

std::unordered_map<std::pair<int, int>, Element, pairHash> const& ArcadeNibbler::getMap() const
{
  return (_map);
}

static void		whereAmI(ArcadeNibbler const& nib)
{
  auto const&		body = nib.getSnake().getBody();
  std::unique_ptr<arcade::WhereAmI> sWh(new arcade::WhereAmI[sizeof(arcade::WhereAmI) +
							     sizeof(arcade::Position) * body.size()]);
  sWh->type = arcade::CommandType::WHERE_AM_I;
  sWh->lenght = body.size();
  arcade::Position	tmp;
  for (unsigned int i = 0; i != body.size(); ++i)
    {
      tmp.x = body[i].first;
      tmp.y = body[i].second;
      sWh->position[i] = tmp;
    }
  std::cout.write(reinterpret_cast<char *>(sWh.get()), sizeof(arcade::WhereAmI) + sizeof(arcade::Position) * body.size());
}

static void		getMap(ArcadeNibbler const& nib)
{
  auto const&		map = nib.getMap();
  std::unique_ptr<arcade::GetMap> sGm(new arcade::GetMap[sizeof(arcade::GetMap) +
							 (ArcadeNibbler::NIBBLER_MAX_COL *
							  ArcadeNibbler::NIBBLER_MAX_ROW) *
							 sizeof(arcade::TileType)]);
  sGm->type = arcade::CommandType::GET_MAP;
  sGm->width = ArcadeNibbler::NIBBLER_MAX_COL;
  sGm->height = ArcadeNibbler::NIBBLER_MAX_ROW;
  unsigned int i = 0;
  for (unsigned int y = 0; y != sGm->height; ++y)
    {
      for (unsigned int x = 0; x != sGm->width; ++x)
	{
	  sGm->tile[i++] = map.at(std::make_pair(x, y)).getType();
	}
    }
  std::cout.write(reinterpret_cast<char *>(sGm.get()), sizeof(arcade::GetMap) + (ArcadeNibbler::NIBBLER_MAX_COL *
									    ArcadeNibbler::NIBBLER_MAX_ROW) *
		  sizeof(arcade::TileType));
}

void			ArcadeNibbler::moveMouli(ObservableKey::Keys key)
{
  switch (key) {
  case ObservableKey::Up:
    _snake.setDirection(Snake::UP);
    break;
  case ObservableKey::Down:
    _snake.setDirection(Snake::DOWN);
    break;
  case ObservableKey::Left:
    _snake.setDirection(Snake::LEFT);
    break;
  case ObservableKey::Right:
    _snake.setDirection(Snake::RIGHT);
    break;
  case ObservableKey::Unknown:
    manageKey(ObservableKey::Unknown);
    break;
  default:
    break;
  }
}

extern "C"
void				Play(void)
{
  ArcadeNibbler			nib;
  arcade::CommandType		cmd;

  while (1)
    {
      if (std::cin.read(reinterpret_cast<char *>(&cmd), sizeof(arcade::CommandType)))
	{
	  if (cmd == arcade::CommandType::WHERE_AM_I)
	    whereAmI(nib);
	  else if (cmd == arcade::CommandType::GET_MAP)
	    getMap(nib);
	  else
	    {
	      auto const& fct = ArcadeNibbler::_translator.find(static_cast<unsigned short>(cmd));
	      if (fct != ArcadeNibbler::_translator.end())
		{
		  nib.moveMouli(fct->second);
		}
	    }
	}
    }
}

extern "C"
IGames				*entryPoint()
{
  return (new ArcadeNibbler);
}
