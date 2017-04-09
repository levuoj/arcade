//
// ObservableKey.hpp for ObservableKey in /home/pashervz/Epitech/C++/Arcade/cpp_arcade/header
// 
// Made by Pashervz
// Login   <paul.julien@epitech.eu>
// 
// Started on  Sat Apr  1 18:28:55 2017 Pashervz
// Last update Thu Apr  6 14:37:24 2017 benito
//

#ifndef OBSERVABLEKEY_HPP
# define OBSERVABLEKEY_HPP

#include "Observable.hpp"

class ObservableKey : public Observable
{
public:
  enum Keys
    {
      Unknown = -1,
      A = 0,
      B,
      C,
      D,
      E,
      F,
      G,
      H,
      I,
      J,
      K,
      L,
      M,
      N,
      O,
      P,
      Q,
      R,
      S,
      T,
      U,
      V,
      W,
      X,
      Y,
      Z,
      Num0,
      Num1,
      Num2,
      Num3,
      Num4,
      Num5,
      Num6,
      Num7,
      Num8,
      Num9,
      Escape,
      LControl,
      LShift,
      LAlt,
      LSystem,
      RControl,
      RShift,
      RAlt,
      RSystem,
      Menu,
      LBracket,
      RBracket,
      SemiColon,
      Comma,
      Period,
      Quote,
      Slash,
      BackSlash,
      Tilde,
      Equal,
      Dash,
      Space,
      Return,
      BackSpace,
      Tab,
      PageUp,
      PageDown,
      End,
      Home,
      Insert,
      Delete,
      Add,
      Subtract,
      Multiply,
      Divide,
      Left,
      Right,
      Up,
      Down,
      Numpad0,
      Numpad1,
      Numpad2,
      Numpad3,
      Numpad4,
      Numpad5,
      Numpad6,
      Numpad7,
      Numpad8,
      Numpad9,
      F1,
      F2,
      F3,
      F4,
      F5,
      F6,
      F7,
      F8,
      F9,
      F10,
      F11,
      F12,
      F13,
      F14,
      F15,
      Pause,
      KeyCount
    };
protected:
  ObservableKey::Keys		_key;
  bool				_isFinished;

  ObservableKey();
  ~ObservableKey() {}
public:
  ObservableKey::Keys		getKey() const;
  void				finish();
  bool				isFinished() const;
};

#endif //OBSERVABLEKEY_HPP
