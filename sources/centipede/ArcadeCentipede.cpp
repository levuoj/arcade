//
// ArcadeCentipede.cpp for ArcadeCentipede.cpp in /home/tvigier/cpp_arcade/sources
//
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
//
// Started on  Thu Apr  6 18:20:29 2017 thomas vigier
// Last update Sun Apr  9 22:25:25 2017 benito
//

#include <random>
#include "ArcadeCentipede.hpp"

std::unordered_map<unsigned short, ObservableKey::Keys> ArcadeCentipede::_translator =
  {
    {static_cast<unsigned short>(arcade::CommandType::GO_UP), ObservableKey::Up},
    {static_cast<unsigned short>(arcade::CommandType::GO_DOWN), ObservableKey::Down},
    {static_cast<unsigned short>(arcade::CommandType::GO_LEFT), ObservableKey::Left},
    {static_cast<unsigned short>(arcade::CommandType::GO_RIGHT), ObservableKey::Right},
    {static_cast<unsigned short>(arcade::CommandType::SHOOT), ObservableKey::Space},
    {static_cast<unsigned short>(arcade::CommandType::PLAY), ObservableKey::Unknown}
  };

ArcadeCentipede::ArcadeCentipede()
{
  _state = State(-1, 0, 1, Coords(30, 30), "Centipede");
  _canShoot = true;
  _winner = 0;

  fillMap();

  _functors[ObservableKey::Up] = std::bind(&ArcadeCentipede::up, this);
  _functors[ObservableKey::Down] = std::bind(&ArcadeCentipede::down, this);
  _functors[ObservableKey::Left] = std::bind(&ArcadeCentipede::left, this);
  _functors[ObservableKey::Right] = std::bind(&ArcadeCentipede::right, this);
  _functors[ObservableKey::Space] = std::bind(&ArcadeCentipede::shoot, this);

}

ArcadeCentipede::~ArcadeCentipede()
{
}

std::unordered_map<std::pair<int, int>, Element, pairHash> const& ArcadeCentipede::getMap() const
{
  return (_map);
}

void			ArcadeCentipede::setMap(std::unordered_map<std::pair<int, int>, Element, pairHash> const& map)
{
  _map = map;
}

Element                 ArcadeCentipede::getElementByChar(const char c)
{
  std::string           sprite;
  Element::Colors       color;
  arcade::TileType      type;
  std::string           content;

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

Element			ArcadeCentipede::getElement(int x, int y)
{
  std::string		sprite;
  Element::Colors	color;
  arcade::TileType	type;
  std::string		content;
  std::random_device	rd;
  std::default_random_engine generator(rd());
  std::uniform_int_distribution<int> distribution(0,10);

  if(x == 0 || x == CENTI_COL - 1)
    {
      content = "X";
      sprite = "./sources/SFML/images/block.png";
      color = Element::YELLOW;
      type = arcade::TileType::BLOCK;
    }
  else if(y == 0 || y == CENTI_ROW -1)
    {
      content = "X";
      sprite = "./sources/SFML/images/block.png";
      color = Element::YELLOW;
      type = arcade::TileType::BLOCK;
    }
  else
    {
      if ((distribution(generator)) == 0 && y <= 24 && y != 1)
	{
	  content = "*";
	  sprite = "./sources/SFML/images/mushroom.png";
	  color = Element::WHITE;
	  type = arcade::TileType::OBSTACLE;
	  return (Element(sprite, color, type, content));
	}
      else
	{
	  content = " ";
	  sprite = "";
	  color = Element::BLACK;
	  type = arcade::TileType::EMPTY;
	}
    }
  return (Element(sprite, color, type, content));
}

void			ArcadeCentipede::fillMap()
{
  int		x, y = 0;

  while (y < CENTI_ROW)
    {
      x = 0;
      while (x < CENTI_COL)
	{
	  _map[std::make_pair(x, y)] = getElement(x, y);
	  ++x;
	}
      ++y;
    }

  _snake = Snake(16, 1);
  bool head = true;
  for (auto it : _snake.getBody())
    {
      if (head == true)
	{
	_map[std::make_pair(it.first, it.second)] =
	  Element("./sources/SFML/images/snake_head_right.png", Element::GREEN, arcade::TileType::OTHER, ">");
	head = false;
	}
      else
  _map[std::make_pair(it.first, it.second)] =
    Element("./sources/SFML/images/snake_body.png", Element::GREEN, arcade::TileType::OTHER, "~");
    }
  _map[std::make_pair(_bug.getPos().first,_bug.getPos().second)] =
    Element("./sources/SFML/images/bug_blaster.png", Element::RED, arcade::TileType::OTHER, "A");
}

void			ArcadeCentipede::up()
{
  if (_bug.getPos().second != 25)
    {
      _map[std::make_pair(_bug.getPos().first,_bug.getPos().second)] =
	Element("", Element::BLACK, arcade::TileType::EMPTY, " ");
      _bug.setPos(std::make_pair(_bug.getPos().first, _bug.getPos().second - 1));
      _map[std::make_pair(_bug.getPos().first,_bug.getPos().second)] =
	Element("./sources/SFML/images/bug_blaster.png", Element::RED, arcade::TileType::OTHER, "A");
    }
}

void			ArcadeCentipede::down()
{
  if (_bug.getPos().second != 28)
    {
      _map[std::make_pair(_bug.getPos().first,_bug.getPos().second)] =
	Element("", Element::BLACK, arcade::TileType::EMPTY, " ");
      _bug.setPos(std::pair<int, int>(_bug.getPos().first, _bug.getPos().second + 1));
      _map[std::make_pair(_bug.getPos().first,_bug.getPos().second)] =
	Element("./sources/SFML/images/bug_blaster.png", Element::RED, arcade::TileType::OTHER, "A");
    }
}

void			ArcadeCentipede::left()
{
  if (_bug.getPos().first != 1)
    {
      _map[std::make_pair(_bug.getPos().first,_bug.getPos().second)] =
	Element("", Element::BLACK, arcade::TileType::EMPTY, " ");
      _bug.setPos(std::pair<int, int>(_bug.getPos().first - 1, _bug.getPos().second));
      _map[std::make_pair(_bug.getPos().first,_bug.getPos().second)] =
	Element("./sources/SFML/images/bug_blaster.png", Element::RED, arcade::TileType::OTHER, "A");
    }
}

void			ArcadeCentipede::right()
{
  if (_bug.getPos().first != 28)
    {
      _map[std::make_pair(_bug.getPos().first,_bug.getPos().second)] =
	Element("", Element::BLACK, arcade::TileType::EMPTY, " ");
      _bug.setPos(std::pair<int, int>(_bug.getPos().first + 1, _bug.getPos().second));
      _map[std::make_pair(_bug.getPos().first,_bug.getPos().second)] =
	Element("./sources/SFML/images/bug_blaster.png", Element::RED, arcade::TileType::OTHER, "A");
    }
}

void			ArcadeCentipede::shoot()
{
  if (_canShoot == true)
    {
      _shoot = std::make_pair(_bug.getPos().first, _bug.getPos().second - 1);
      _map[std::make_pair(_shoot.first, _shoot.second)] = Element("./sources/SFML/images/projectile.png", Element::RED, arcade::TileType::MY_SHOOT, "|");
      _canShoot = false;
    }
}

void			ArcadeCentipede::moveShoot()
{
  if (_shoot.second == 1)
    {
      _map[std::make_pair(_shoot.first, _shoot.second)] =
	Element("", Element::BLACK, arcade::TileType::EMPTY, " ");
      _canShoot = true;
    }
  else if (_map[std::make_pair(_shoot.first, _shoot.second -1)].getContent() == "*")
    {
      _state.setScore(_state.getScore() + 10);
      _map[std::make_pair(_shoot.first, _shoot.second - 1)] =
	Element("", Element::BLACK, arcade::TileType::EMPTY, " ");
      _map[std::make_pair(_shoot.first, _shoot.second)] =
	Element("", Element::BLACK, arcade::TileType::EMPTY, " ");
      _canShoot = true;
    }
  else if (_map[std::make_pair(_shoot.first, _shoot.second - 1)].getColor() == Element::GREEN)
    {
      _state.setScore(_state.getScore() + 25);
      _map[std::make_pair(_shoot.first, _shoot.second - 1)] =
	Element("./sources/SFML/images/mushroom.png", Element::WHITE, arcade::TileType::OBSTACLE,"*");
      while (_shoot.first != _snake.getTailX())
	{
	  _map[std::make_pair(_snake.getTailX(), _snake.getTailY())] =
	    Element("", Element::BLACK, arcade::TileType::EMPTY, "*");
	  _snake.loseTail();
	}
      if (_snake.getSize() < 2)
	{
	  _snake.~Snake();
	  _state.setScore(_state.getScore() + 10000000);
	  _winner = true;
	}
      _map[std::make_pair(_shoot.first, _shoot.second)] =
	Element("", Element::BLACK, arcade::TileType::EMPTY, " ");
      _canShoot = true;
    }
  else
    {
      _map[std::make_pair(_shoot.first, _shoot.second)] =
	Element("", Element::BLACK, arcade::TileType::EMPTY, " ");
      _shoot = std::make_pair(_shoot.first, _shoot.second - 1);
      _map[std::make_pair(_shoot.first, _shoot.second)] =
	Element("./sources/SFML/images/projectile.png", Element::RED, arcade::TileType::MY_SHOOT, "|");
    }
}

void					ArcadeCentipede::checkWalls(std::unordered_map<std::pair<int, int>, Element, pairHash>& map)
{
  if (_snake.getHeadY() == 28)
    {
      _snake.~Snake();
      _state.setScore(_state.getScore() - _state.getScore());
      _winner = 10;
    }
  if (_snake.getHeadX() == 28 ||
      map[std::make_pair(_snake.getHeadX() + 1, _snake.getHeadY())].getContent() == "*"
      || _snake.getHeadX() == 1 ||
      map[std::make_pair(_snake.getHeadX() - 1, _snake.getHeadY())].getContent() == "*")
    {
      if (_snake.getDirection() == Snake::Direction::RIGHT)
	{
	  _snake.setDirection(Snake::Direction::DOWN);
	  _snake.move(map);
	  _snake.setDirection(Snake::Direction::LEFT);
	  _state.setMap(map);
	  notify();
	}
      else
	{
	  _snake.setDirection(Snake::Direction::DOWN);
	  _snake.move(map);
	  _snake.setDirection(Snake::Direction::RIGHT);
	  _state.setMap(map);
	  notify();
	}
    }
}

BugBlaster const&	ArcadeCentipede::getBug() const
{
  return (_bug);
}

IGames::gameState	ArcadeCentipede::manageKey(ObservableKey::Keys key)
{
  auto const&		it = _functors.find(key);

  if (it != _functors.end())
    it->second();
  if (_canShoot == false)
    moveShoot();
  checkWalls(_map);
  _snake.move(_map);
  _state.setMap(_map);
  notify();
  if (_winner > 0)
    ++_winner;
  if ((_snake.getHeadX() == _bug.getPos().first && _snake.getHeadY() == _bug.getPos().second) || _winner >= 10)
    return (IGames::FINISHED);
  return (IGames::PLAYING);
}

static void             getMap(ArcadeCentipede const& centi)
{
  auto const&           map = centi.getMap();
  std::unique_ptr<arcade::GetMap> sGm(new arcade::GetMap[sizeof(arcade::GetMap) +
							 (30 * 30) *
							 sizeof(arcade::TileType)]);
  sGm->type = arcade::CommandType::GET_MAP;
  sGm->width = 30;
  sGm->height = 30;
  unsigned int i = 0;
  for (unsigned int y = 0; y != sGm->height; ++y)
    {
      for (unsigned int x = 0; x != sGm->width; ++x)
	{
	  sGm->tile[i++] = map.at(std::make_pair(x, y)).getType();
	}
    }
  std::cout.write(reinterpret_cast<char *>(sGm.get()), sizeof(arcade::GetMap) + (30 * 30) *
		  sizeof(arcade::TileType));
}

static void             whereAmI(ArcadeCentipede const& centi)
{
  std::unique_ptr<arcade::WhereAmI> sWh(new arcade::WhereAmI[sizeof(arcade::WhereAmI) +
							     sizeof(arcade::Position)]);
  sWh->type = arcade::CommandType::WHERE_AM_I;
  sWh->lenght = 1;
  sWh->position[0].x = centi.getBug().getPos().first;
  sWh->position[0].y = centi.getBug().getPos().second;
  std::cout.write(reinterpret_cast<char *>(sWh.get()), sizeof(arcade::WhereAmI) + sizeof(arcade::Position));
}

extern "C"
void			Play(void)
{
  ArcadeCentipede	centi;
  arcade::CommandType	cmd;

  while (1)
    {
      if (std::cin.read(reinterpret_cast<char *>(&cmd), sizeof(arcade::CommandType)))
	{
	  if (cmd == arcade::CommandType::WHERE_AM_I)
	    whereAmI(centi);
	  else if (cmd == arcade::CommandType::GET_MAP)
	    getMap(centi);
	  else
	    {
	      auto const& fct = ArcadeCentipede::_translator.find(static_cast<unsigned short>(cmd));
	      if (fct != ArcadeCentipede::_translator.end())
		{
		  centi.manageKey(fct->second);
		}
	    }
	}
    }
}

extern "C"
IGames			*entryPoint()
{
  return (new ArcadeCentipede);
}
