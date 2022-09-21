# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/15 20:27:06 by seseo             #+#    #+#              #
#    Updated: 2022/09/21 13:29:44 by seseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			:=	src/main.cpp

OBJS			:=	$(SRCS:.cpp=.o)

TARGET			:=	./containers
CXX				:=	c++
RM				:=	rm -rf
CXXFLAGS		:=	-Wall -Wextra -Werror -std=c++98 -g #-pedantic -fsanitize=address

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

