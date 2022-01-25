# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/13 16:35:21 by adda-sil          #+#    #+#              #
#    Updated: 2022/01/24 18:39:09 by adda-sil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS_DIR			= srcs
SRCS_FILES			= 	\
						main.cpp \
						test_vector.cpp \

HEAD_DIR			= includes
HEAD_FILES			= \
						tester.hpp \
						utils.hpp \
						awesome.hpp \

TEMPLATE_DIR		= templates
TEMPLATE_FILES		= \
						Stack.hpp \
						vector.hpp \

SRCS				= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
HEADERS				= $(addprefix $(HEAD_DIR)/, $(HEAD_FILES))
TEMPLATES			= $(addprefix $(TEMPLATE_FILES)/, $(TEMPLATE_FILES))
INCLUDES			= -I . -I $(HEAD_DIR) -I $(TEMPLATE_DIR)
LIBS				= 
CXX					= c++
OPTS				=
CXXFLAGS			= -std=c++98 -Wall -Wextra -Werror -Wno-unused-variable -g3 ${OPTS} $(INCLUDES) -MMD
OBJS				= $(SRCS:.cpp=.o)
NAME				= containers
ARGS				= 
OBJ_DIR				= objs
DEP 				= $(OBJS:.o=.d)

all:				
					@$(MAKE) $(NAME)

$(NAME):			$(OBJS)
					$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(NAME)

-include $(DEP)

run:				all
					./$(NAME) $(ARGS)

clean:
					$(RM) $(OBJS)
					$(RM) $(DEPS)

fclean:				clean
					$(RM) $(NAME)

compare:
					$(MAKE) OPTS="-D STL" re && ./$(NAME) > stl.output
					$(MAKE) OPTS="" re && ./$(NAME) > ft.output
					git diff --no-index ft.output stl.output

debug:
					$(MAKE) OPTS="-D STL" re && ./$(NAME) > stl.output
					$(MAKE) OPTS="-D DEBUG" re && ./$(NAME) > ft.output
					git diff --no-index ft.output stl.output


stl:
					$(MAKE) OPTS="-D STL" re && ./$(NAME)

ft:
					$(MAKE) OPTS="" re && ./$(NAME)

dbg:
					$(MAKE) OPTS="-D DEBUG" re && ./$(NAME)

re:					clean all

fre:				fclean all

.PHONY:				all clean fclean re fre run
