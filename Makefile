# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/09 11:13:40 by ldutriez          #+#    #+#              #
#    Updated: 2021/09/24 03:20:21 by notcampeur       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		webserv
NAME_DEV =	webserv_dev

CXX =		clang++

SRC_DIR =	$(shell find srcs -type d)

INC_DIR =	$(shell find includes -type d) \
			$(shell find srcs -type d)

OBJ_DIR =	objs/srcs
PCH_DIR =	objs/pch
OBJ_DIR_DEV =	dev_objs/srcs/

vpath %.hpp $(foreach dir, $(INC_DIR), $(dir):)
vpath %.hpp.pch $(PCH_DIR)

INC = webserv.hpp json.hpp webserv_param.hpp webserv_sig_handler.hpp \
	HeadMethod.hpp GetMethod.hpp DeleteMethod.hpp IHttpMethod.hpp \
	PostMethod.hpp JsonFileReader.hpp JsonString.hpp IJsonValue.hpp \
	JsonObject.hpp JsonArray.hpp ServerConfig.hpp RequestConfig.hpp \
	LocationConfig.hpp ConfigParser.hpp Config.hpp Request.hpp Mime.hpp \
	Server.hpp Validator.hpp Response.hpp WriteHandler.hpp ServerHandler.hpp \
	ClientHandler.hpp ReadHandler.hpp HandlerTable.hpp Timer.hpp CgiHandler.hpp\
	IEventHandler.hpp RequestBodyParser.hpp RequestHeaderParser.hpp RequestParser.hpp\
	RequestUriParser.hpp Client.hpp InitiationDispatcher.hpp Demultiplexer.hpp \
	HttpErrorManager.hpp StatusCodes.hpp Utils.hpp CgiHeaderParser.hpp CgiParser.hpp \
	Environment.hpp Arguments.hpp ServerSystemException.hpp ClientException.hpp \
	SystemException.hpp HttpException.hpp Exception.hpp ClientSystemException.hpp \
	Singleton.hpp Logger.hpp

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
PCH = $(addprefix $(PCH_DIR)/, $(INC:%.hpp=%.hpp.pch))
OBJ_DEV = $(addprefix $(OBJ_DIR_DEV)/, $(SRC:%.cpp=%.o))

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
				@echo "$(_BLUE)INC :\n$(_YELLOW)$(INC)$(_WHITE)"
				@echo "$(_BLUE)INC_DIR :\n$(_YELLOW)$(INC_DIR)$(_WHITE)"
				@echo "$(_BLUE)PCH :\n$(_YELLOW)$(PCH)$(_WHITE)"
				@echo "$(_BLUE)PCH_DIR :\n$(_YELLOW)$(PCH_DIR)$(_WHITE)"				
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

$(OBJ_DIR)/%.o : %.cpp Makefile
				@echo "Compiling $(_PURPLE)sources $(_YELLOW)$@$(_WHITE) ... \c"
				@mkdir -p $(OBJ_DIR)
				@$(CXX) $(CPPFLAGS) $(IFLAGS) -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"

$(PCH_DIR)/%.hpp.pch : %.hpp Makefile
				@echo "Compiling $(_CYAN)headers $(_YELLOW)$@$(_WHITE) ... \c"
				@mkdir -p $(PCH_DIR)
				@$(CXX) $(CPPFLAGS) $(IFLAGS) -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"
				
$(NAME): 		$(INC_DIR) $(PCH) $(OBJ) Makefile
				@echo "-----\nCreating $(_BLUE)Executable $(_YELLOW)$@$(_WHITE) ... \c"
				@$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

exec:			$(NAME)
				@echo "-----\nExecuting $(_YELLOW)$<$(_WHITE) ... \n"
				@./$(NAME) 3
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

$(OBJ_DIR_DEV)/%.o : %.cpp
				@echo "Compiling dev $(_YELLOW)$@$(_WHITE) ... \c"
				@mkdir -p $(OBJ_DIR_DEV)
				@$(CXX) $(CPPFLAGS) $(IFLAGS) -D DEBUG=true -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"
				
$(NAME_DEV):	$(INC_DIR) $(OBJ_DEV) Makefile
				@echo "-----\nCreating Dev Executable $(_YELLOW)$@$(_WHITE) ... \c"
				@$(CXX) $(CPPFLAGS) $(OBJ_DEV) $(LDFLAGS) -o $(NAME_DEV)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

exec_dev:		$(NAME_DEV)
				@echo "-----\nExecuting $(_YELLOW)$<$(_WHITE) in verbose mode ... \n"
				@./$(NAME_DEV) 3
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

re:				fclean all

clean:
				@echo "$(_WHITE)Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
				@rm -rf $(OBJ_DIR) $(PCH_DIR)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

clean_dev:
				@echo "$(_WHITE)Deleting Development Objects Directory $(_YELLOW)$(OBJ_DIR_DEV)$(_WHITE) ... \c"
				@rm -rf $(OBJ_DIR_DEV)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

fclean:			clean clean_dev
				@echo "Deleting Binaries Files $(_YELLOW)$(NAME) | $(NAME_DEV)$(_WHITE) ... \c"
				@rm -f $(NAME) $(NAME_DEV)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

.PHONY: all clean clean_dev flcean re show norme exec exec_dev re-install
