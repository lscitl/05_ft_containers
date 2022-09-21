# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seseo <seseo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/15 20:27:06 by seseo             #+#    #+#              #
#    Updated: 2022/09/22 01:19:19 by seseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			:=	src/main.cpp

OBJS			:=	$(SRCS:.cpp=.o)

TARGET			:=	./containers
CXX				:=	c++
RM				:=	rm -rf
CXXFLAGS		:=	-Wall -Wextra -Werror -std=c++98 -g -pedantic -fsanitize=address

%.o				:	%.cpp
					$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET)		:	$(OBJS)
					$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

all				:	$(TARGET)

clean			:
					$(RM) $(OBJS)

fclean			:	clean
					$(RM) $(TARGET)

re				:	fclean
					@$(MAKE) all

.PHONY			:	all clean fclean re

