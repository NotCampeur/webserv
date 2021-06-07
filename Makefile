# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/09 11:13:40 by ldutriez          #+#    #+#              #
#    Updated: 2021/06/07 14:39:16 by ldutriez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		webserv
NAME_DEV =	webserv_dev

CXX =		clang++

SRC_DIR =	$(shell find Srcs -type d)

INC_DIR =	$(shell find Includes -type d) \
			$(shell find Libft/Includes -type d)

LIB_DIR =	Libft

OBJ_DIR =	Objs
OBJ_DIR_DEV =	DevObjs

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

LIB = ft

SRC	=	main.cpp \
		server.cpp client_request.cpp

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))
OBJ_DEV = $(addprefix $(OBJ_DIR_DEV)/, $(SRC:%.cpp=%.o))

#Compilation flag
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

DEBUG =
ifdef DEBUG
    CPPFLAGS += -fsanitize=address
endif

IFLAGS =	$(foreach dir, $(INC_DIR), -I$(dir))

LDFLAGS =	$(foreach dir, $(LIB_DIR), -L $(dir)) \
			$(foreach lib, $(LIB), -l$(lib))

# Colors

_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m

all:			$(NAME)

show:
				@echo "$(_BLUE)SRC :\n$(_YELLOW)$(SRC)$(_WHITE)"
				@echo "$(_BLUE)SRC_DIR :\n$(_YELLOW)$(SRC_DIR)$(_WHITE)"
				@echo "$(_BLUE)OBJ :\n$(_YELLOW)$(OBJ)$(_WHITE)"
				@echo "$(_BLUE)OBJ_DIR :\n$(_YELLOW)$(OBJ_DIR)$(_WHITE)"
				@echo "$(_BLUE)CPPFLAGS :\n$(_YELLOW)$(CPPFLAGS)$(_WHITE)"
				@echo "$(_BLUE)IFLAGS :\n$(_YELLOW)$(IFLAGS)$(_WHITE)"
				@echo "$(_BLUE)LDFLAGS :\n$(_YELLOW)$(LDFLAGS)$(_WHITE)"
				@echo "$(_BLUE)LIB_DIR:\n$(_YELLOW)$(LIB_DIR)$(_WHITE)"
				@echo "$(_BLUE)INC_DIR :\n$(_YELLOW)$(INC_DIR)$(_WHITE)"

libft/libft.a:
				@echo -n "$(_PURPLE)"
				@$(foreach dir, $(LIB_DIR), make --no-print-directory DEBUG=$(DEBUG) -C $(dir) ; )
				@echo -n "$(_WHITE)"		

re-install:
				@echo "$(_PURPLE)"
				@$(foreach dir, $(LIB_DIR), make --no-print-directory DEBUG=$(DEBUG) -C $(dir) re ; )
				@echo "$(_WHITE)"

$(OBJ_DIR)/%.o : %.cpp
				@echo -n "Compiling $(_YELLOW)$@$(_WHITE) ... "
				@mkdir -p $(OBJ_DIR)
				@$(CXX) $(CPPFLAGS) $(IFLAGS) -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"

$(NAME): 		libft/libft.a $(INC_DIR) $(OBJ) Makefile
				@echo -n "-----\nCreating Executable $(_YELLOW)$@$(_WHITE) ... "
				@$(CXX) $(CPPFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

exec:			$(NAME)
				@echo -n "-----\nExecuting $(_YELLOW)$<$(_WHITE) ... \n"
				@./$(NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

$(OBJ_DIR_DEV)/%.o : %.cpp
				@echo -n "Compiling dev $(_YELLOW)$@$(_WHITE) ... "
				@mkdir -p $(OBJ_DIR_DEV)
				@$(CXX) $(CPPFLAGS) $(IFLAGS) -D DEBUG=true -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"
				
$(NAME_DEV):	libft/libft.a $(INC_DIR) $(OBJ_DEV) Makefile
				@echo -n "-----\nCreating Dev Executable $(_YELLOW)$@$(_WHITE) ... "
				@$(CXX) $(CPPFLAGS) $(OBJ_DEV) $(LDFLAGS) -o $(NAME_DEV)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

exec_dev:		$(NAME_DEV)
				@echo -n "-----\nExecuting $(_YELLOW)$<$(_WHITE) in verbose mode ... \n"
				@./$(NAME_DEV)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

norme:
				norminette $(SRC_DIR)

re:				fclean all

clean:
				@echo -n "$(_WHITE)Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... "
				@rm -rf $(OBJ_DIR)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

clean_dev:
				@echo -n "$(_WHITE)Deleting Development Objects Directory $(_YELLOW)$(OBJ_DIR_DEV)$(_WHITE) ... "
				@rm -rf $(OBJ_DIR_DEV)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

fclean:			clean clean_dev
				@echo -n "Deleting Binaries Files $(_YELLOW)$(NAME) | $(NAME_DEV)$(_WHITE) ... "
				@rm -f $(NAME) $(NAME_DEV)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

.PHONY: all clean clean_dev flcean re show norme exec exec_dev re-install
