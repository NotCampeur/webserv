# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldutriez_home <ldutriez@student.42.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/22 11:30:37 by ldutriez_ho       #+#    #+#              #
#    Updated: 2021/07/20 17:55:53 by jmaydew          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		webclient

CXX =		clang++

SRC_DIR =	$(shell find srcs -type d)

INC_DIR =	$(shell find includes -type d) \
			$(shell find srcs -type d)

LIB_DIR =	

OBJ_DIR =	objs

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

LIB = 

SRC	=	main.cpp \
		UserAgent.cpp \
		Logger.cpp

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))

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

$(OBJ_DIR)/%.o : %.cpp
				@echo "Compiling $(_YELLOW)$@$(_WHITE) ... \c"
				@mkdir -p $(OBJ_DIR)
				@$(CXX) $(CPPFLAGS) $(IFLAGS) -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"

$(NAME): 		$(INC_DIR) $(OBJ) Makefile
				@echo "-----\nCreating Executable $(_YELLOW)$@$(_WHITE) ... \c"
				@$(CXX) $(CPPFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

exec:			$(NAME)
				@echo "-----\nExecuting $(_YELLOW)$<$(_WHITE) ... \n"
				@./$(NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

norme:
				norminette $(SRC_DIR)

re:				fclean all

clean:
				@echo "$(_WHITE)Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
				@rm -rf $(OBJ_DIR)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

fclean:			clean 
				@echo "Deleting Binaries Files $(_YELLOW)$(NAME) | $(NAME_DEV)$(_WHITE) ... \c"
				@rm -f $(NAME) $(NAME_DEV)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

.PHONY: all clean flcean re show norme exec re-install
