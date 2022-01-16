# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/13 16:35:21 by adda-sil          #+#    #+#              #
#    Updated: 2022/01/16 12:29:02 by adda-sil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS_DIR			= srcs
SRCS_FILES			= 	\
						main.cpp \

HEAD_DIR			= includes
HEAD_FILES			= \

TEMPLATE_DIR		= templates
TEMPLATE_FILES		= \
						Stack.hpp \
						Vector.hpp \

SRCS				= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
HEADERS				= $(addprefix $(HEAD_DIR)/, $(HEAD_FILES))
TEMPLATES			= $(addprefix $(TEMPLATE_FILES)/, $(TEMPLATE_FILES))
INCLUDES			= -I . -I $(HEAD_DIR) -I $(TEMPLATE_DIR)
LIBS				= 
CXX					= c++
OPTS				=
CXXFLAGS			= -std=c++98 -Wall -Wextra -Werror ${OPTS} $(INCLUDES) -MMD
OBJS				= $(SRCS:.cpp=.o)
NAME				= mutantstack
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

re:					clean all

fre:				fclean all

.PHONY:				all clean fclean re fre run
