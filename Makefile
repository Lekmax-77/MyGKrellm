##
## EPITECH PROJECT, 2022
## B-PDG-300-PAR-3-1-PDGD06-zacharie.lawson
## File description:
## Makefile
##

NAME		=	MyGKrellm

CPPFLAGS	=	-iquote include/

CC 			=	g++

SFML_FLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system

LDFLAGS		=	-lncurses

CXXFLAGS	=	-std=c++2a -Wall -Wextra

SDIR		=	sources

SRC			=	Monitor/cpu.cpp	\
				Monitor/ram.cpp	\
				Monitor/sysinfo.cpp	\
				Monitor/network.cpp	\
				Monitor/utils.cpp	\
				SFML/Gui.cpp	\
				NCURSES/src/window.cpp \

MAIN		=	main.cpp

OBJ			=	$(SRC:.cpp=.o) \
				$(MAIN:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o  $(NAME) $(OBJ) $(CXXFLAGS) $(SFML_FLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) vgcore.*

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

debug:	CXXFLAGS += -g3
debug: ${OBJ}
	${CC} -o $(NAME) $(OBJ) $(CXXFLAGS) $(SFML_FLAGS) $(LDFLAGS)

.PHONY: all clean fclean re debug