//
// IManageKey.hpp for IManageKey in /home/pashervz/Epitech/C++/Arcade/cpp_arcade
// 
// Made by Pashervz
// Login   <paul.julien@epitech.eu>
// 
// Started on  Wed Mar 29 18:05:21 2017 Pashervz
// Last update Mon Apr  3 11:53:51 2017 benito
//

#ifndef _IMANAGEKEY_HPP_
# define _IMANAGEKEY_HPP_

#include "ObservableKey.hpp"

class IManageKey : public ObservableKey
{
public:
  virtual void		catchKey() = 0;
  virtual ~IManageKey() {};
};

#endif // MANAGEKEY_HPP
