//
// Snake.hpp for arcade  in /home/anthony/rendu/cpp/cpp_arcade/sources/src_nibbler
//
// Made by Anthony Jouvel
// Login   <anthony.jouvel@epitech.eu>
//
// Started on  Wed Apr  5 10:37:40 2017 Anthony Jouvel
// Last update Sun Apr  9 20:49:20 2017 Anthony Jouvel
//

#ifndef SNAKE_HPP
# define SNAKE_HPP

#include	<vector>
#include	<iterator>
#include	<utility>
#include	<unordered_map>
#include	"State.hpp"

enum class Action : uint16_t;

class		Snake
{
public:
  enum Direction
    {
      LEFT = 0,
      UP = 1,
      RIGHT = 2,
      DOWN = 3
    };
private:
  Snake::Direction			_dir;
  std::vector<std::pair<int, int>>	_body;
public:
  Snake(int, int);
  Snake() {};
  ~Snake();

  std::vector<std::pair<int, int>> const& getBody() const;
  void				move(std::unordered_map<std::pair<int, int>, Element, pairHash>&);
  Action			grow(std::unordered_map<std::pair<int, int>, Element, pairHash>&);

  void				setDirection(Snake::Direction);
  Snake::Direction const&	getDirection() const;
  int				getHeadX() const;
  int				getHeadY() const;
  int				getTailX() const;
  int				getTailY() const;
  int				getSize() const;
  void				loseTail();
  std::pair<int, int>		getPairByDir(std::pair<int, int> const&, Snake::Direction) const;
};

#endif /* !SNAKE_HPP */
