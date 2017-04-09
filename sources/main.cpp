//
// main.cpp for main.cpp in /home/tvigier/cpp_arcade
// 
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
// 
// Started on  Thu Mar 23 14:53:44 2017 thomas vigier
// Last update Sun Apr  9 22:13:04 2017 benito
//

#include "Arcade.hpp"

int	main(int ac, char **av)
{
  if (ac != 2)
    {
      std::cerr << "Usage: " << av[0] << " lib" << std::endl;
      return (84);
    }
  try
    {
      Arcade	menu(av[1]);

      while (menu.isNotOver())
	menu.launch();
    }
  catch (std::exception const& e)
    {
      std::cerr << e.what() << std::endl;
      return (84);
    }
  return (0);
}
