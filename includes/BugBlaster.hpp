//
// BugBlaster.hpp for BugBlaster.hpp in /home/tvigier/cpp_arcade
// 
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
// 
// Started on  Fri Apr  7 09:14:46 2017 thomas vigier
// Last update Sun Apr  9 17:08:40 2017 benito
//

#ifndef BUGBLASTER_HPP_
# define BUGBLASTER_HPP_

#include <utility>
#include "Protocol.hpp"
#include "Element.hpp"

class BugBlaster
{
private:
  enum Direction
    {
      LEFT,
      UP,
      RIGHT,
      DOWN
    };

  std::pair<int, int>	_pos;
public:
  void		setPos(std::pair<int, int> const&);
  std::pair<int, int> const&	getPos() const;

  BugBlaster();
  BugBlaster(std::pair<int, int>);
  ~BugBlaster();
};

#endif // BUGBLASTER_HPP_
