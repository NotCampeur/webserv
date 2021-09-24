# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/09 11:13:40 by ldutriez          #+#    #+#              #
#    Updated: 2021/09/24 13:49:44 by notcampeur       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		webserv

CXX =		clang++

SRC_DIR =	$(shell find srcs -type d)

INC_DIR =	$(shell find includes -type d) \
			$(shell find srcs -type d)

OBJ_DIR =	objs

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

SRC	=	main.cpp \
		Logger.cpp \
		Arguments.cpp \
		\
		sigint_handler.cpp \
		InitiationDispatcher.cpp Demultiplexer.cpp HandlerTable.cpp \
		ServerHandler.cpp ClientHandler.cpp ReadHandler.cpp WriteHandler.cpp\
		Timer.cpp \
		Server.cpp Client.cpp \
		Request.cpp Response.cpp\
		RequestParser.cpp RequestUriParser.cpp RequestHeaderParser.cpp RequestBodyParser.cpp\
		Validator.cpp \
		Exception.cpp HttpException.cpp ClientException.cpp \
		SystemException.cpp ServerSystemException.cpp ClientSystemException.cpp \
		DeleteMethod.cpp GetMethod.cpp HeadMethod.cpp PostMethod.cpp \
		CgiHandler.cpp CgiParser.cpp CgiHeaderParser.cpp Environment.cpp \
		Utils.cpp \
		StatusCodes.cpp Mime.cpp HttpErrorManager.cpp\
		\
		JsonFileReader.cpp JsonObject.cpp JsonArray.cpp JsonString.cpp \
		ServerConfig.cpp LocationConfig.cpp Config.cpp RequestConfig.cpp \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))

#Compilation flag
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

DEBUG =
ifdef DEBUG
    CPPFLAGS += -g3 -fsanitize=address
endif

IFLAGS =	$(foreach dir, $(INC_DIR), -I$(dir))

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
				@echo "$(_BLUE)INC_DIR :\n$(_YELLOW)$(INC_DIR)$(_WHITE)"
				@echo "$(_BLUE)CPPFLAGS :\n$(_YELLOW)$(CPPFLAGS)$(_WHITE)"
				@echo "$(_BLUE)IFLAGS :\n$(_YELLOW)$(IFLAGS)$(_WHITE)"
				@echo "$(_BLUE)LDFLAGS :\n$(_YELLOW)$(LDFLAGS)$(_WHITE)"
				@echo "$(_BLUE)LIB_DIR:\n$(_YELLOW)$(LIB_DIR)$(_WHITE)"
				@echo "$(_BLUE)INC_DIR :\n$(_YELLOW)$(INC_DIR)$(_WHITE)"

print-%: ; @echo $*=$($*)

re-install:
				@echo "$(_PURPLE)"
				@$(foreach dir, $(LIB_DIR), make --no-print-directory DEBUG=$(DEBUG) -C $(dir) re ; )
				@echo "$(_WHITE)"

$(OBJ_DIR)/%.o : %.cpp
				@echo "Compiling $(_PURPLE)sources $(_YELLOW)$@$(_WHITE) ... \c"
				@mkdir -p $(OBJ_DIR)
				@$(CXX) $(CPPFLAGS) $(IFLAGS) -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"

$(NAME): 		$(INC_DIR) $(OBJ)
				@echo "-----\nCreating $(_BLUE)Executable $(_YELLOW)$@$(_WHITE) ... \c"
				@$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

re:				fclean all

clean:
				@echo "$(_WHITE)Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
				@rm -rf $(OBJ_DIR)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

fclean:			clean
				@echo "Deleting Binaries Files $(_YELLOW)$(NAME)$(_WHITE) ... \c"
				@rm -f $(NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

.PHONY: all clean flcean re show norme re-install
