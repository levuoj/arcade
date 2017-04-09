//
// Coord.hpp for Coord.hpp in /home/tvigier/cpp_arcade/includes
// 
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
// 
// Started on  Fri Mar 24 14:22:49 2017 thomas vigier
// Last update Mon Mar 27 16:06:45 2017 thomas vigier
//

#ifndef COORDS_HPP
# define COORDS_HPP

class		Coords
{
  int		_x;
  int		_y;
public:
  Coords(int, int);
  Coords();
  ~Coords() {};
  int		getX() const;
  int		getY() const;
  bool		operator==(const Coords &other) const; // TRUE IF BOTH COORDS ARE EQUAL
};

#endif // COORDS_HPP_
