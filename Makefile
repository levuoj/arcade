##
## Makefile for  in /home/anthony/rendu/cpp/cpp_arcade/test
##
## Made by Anthony
## Login   <anthony.jouvel@epitech.eu>
##
## Started on  Mon Mar 20 15:08:51 2017 Anthony
## Last update Sun Apr  9 22:31:14 2017 benito
##

## RULES

RM		=	rm -f

CPP		=	g++

FPIC		=	-fPIC

SHARED		=	-shared

LDL		=	-ldl

## BINARIES / LIBSO

BINARY		=	arcade

NCURSES_SO	=	lib/lib_arcade_ncurses.so

#OPENGL_SO	=	lib/lib_arcade_opengl.so

SFML_SO		=	lib/lib_arcade_sfml.so

NIBBLER_SO	=	games/lib_arcade_nibbler.so

CENTIPEDE_SO	=	games/lib_arcade_centipede.so

## SOURCES

SRC		=	sources/main.cpp \
			sources/Arcade.cpp \
			sources/DLLoader.cpp \
			sources/State.cpp \
			sources/Observable.cpp \
			sources/ObservableGame.cpp \
			sources/ObservableKey.cpp \
			sources/Coords.cpp \
			sources/Element.cpp

NCURSES_SRC	=	sources/State.cpp \
			sources/Observable.cpp \
			sources/ObservableGame.cpp \
			sources/ObservableKey.cpp \
			sources/Coords.cpp \
			sources/Element.cpp \
			sources/src_ncurses/LibraryNcurses.cpp \
			sources/src_ncurses/ManageKeyNcurse.cpp

#OPENGL_SRC	=	sources/o.cpp

SFML_SRC	=	sources/State.cpp \
			sources/Observable.cpp \
			sources/ObservableGame.cpp \
			sources/ObservableKey.cpp \
			sources/Coords.cpp \
			sources/Element.cpp \
			sources/SFML/LibrarySFML.cpp \
			sources/SFML/ManageKeySFML.cpp

NIBBLER_SRC	=	sources/src_nibbler/ArcadeNibbler.cpp \
			sources/src_nibbler/Snake.cpp \
			sources/State.cpp \
			sources/Element.cpp \
			sources/Coords.cpp \
			sources/Observable.cpp


CENTIPEDE_SRC	=	sources/centipede/ArcadeCentipede.cpp \
			sources/centipede/BugBlaster.cpp \
			sources/State.cpp \
			sources/Element.cpp \
			sources/Coords.cpp \
			sources/Observable.cpp \
			sources/centipede/Snake.cpp \

## OBJS

SRC_O		=	$(SRC:.cpp=.o)

NCURSES_O	=	$(NCURSES_SRC:.cpp=.o)

#OPENGL_O	=	$(OPENGL_SRC:.cpp=.o)

SFML_O		=	$(SFML_SRC:.cpp=.o)

NIBBLER_O	=	$(NIBBLER_SRC:.cpp=.o)

CENTIPEDE_O	=	$(CENTIPEDE_SRC:.cpp=.o)

## FLAGS

CXXFLAGS        +=      -std=c++11 -W -Wall -Werror -Wextra -fPIC
CXXFLAGS        +=      -I includes/

all		:	$(NIBBLER_SO) $(CENTIPEDE_SO) $(BINARY)

lib		:	$(NCURSES_SO) $(SFML_SO) #$(OPENGL_SO)

$(NCURSES_SO)	:	$(NCURSES_O)
			$(CPP) -o $(NCURSES_SO) $(NCURSES_O) $(FPIC) $(SHARED) -lncurses -ltinfo

$(OPENGL_SO)	:	$(OPENGL_O)
			$(CPP) -o $(OPENGL_SO) $(OPENGL_O) $(FPIC) $(SHARED)

$(SFML_SO)	:	$(SFML_O)
			$(CPP) -o $(SFML_SO) $(SFML_O) $(FPIC) $(SHARED) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

$(NIBBLER_SO)	:	$(NIBBLER_O)
			$(CPP) -o $(NIBBLER_SO) $(NIBBLER_O) $(FPIC) $(SHARED)

$(CENTIPEDE_SO)	:	$(CENTIPEDE_O)
			$(CPP) -o $(CENTIPEDE_SO) $(CENTIPEDE_O) $(FPIC) $(SHARED)

$(BINARY)	:	$(SRC_O)
			$(CPP) -o $(BINARY) $(SRC_O) $(LDL)

clean		:
			$(RM) $(SRC_O) $(NCURSES_O) $(OPENGL_O) $(SFML_O) $(NIBBLER_O) $(CENTIPEDE_O)

fclean		:	clean
			$(RM) $(BINARY) $(NCURSES_SO) $(OPENGL_SO) $(SFML_SO) $(NIBBLER_SO) $(CENTIPEDE_SO)

re		:	fclean all

.PHONY		:	all lib clean fclean re
