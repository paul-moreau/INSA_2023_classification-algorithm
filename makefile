## Makefile for windows 

NAME	= classifier

CFLAGS	= -std=c++14 -Wall -Wextra -Werror

SRC		= main.cpp\
		  algorithm.cpp\
		  algorithm1.cpp\
		  algorithm2.cpp\
		  data.cpp\
		  utils.cpp\
		  compareAlgo.cpp

OBJ		= $(SRC:.cpp=.o)

RM		= del -r -f

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME).exe