NAME	=		libft.a

CC 		=		clang++

SRC_DIR = 		$(shell find srcs -type d)
INC_DIR = 		$(shell find includes -type d)
OBJ_DIR = 		objs

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

SRC 	=		ft_itoa_base.cpp ft_itoa.cpp ft_atoi.cpp ft_itoa_hexa.cpp ft_itoa_octa.cpp \
				\
				ft_strdup.cpp ft_strdup_c.cpp ft_strlen.cpp ft_strnew.cpp \
				ft_strcpy.cpp ft_strsub.cpp ft_strstr.cpp ft_str_count_c.cpp ft_rm_charset.cpp\
				ft_strjoin.cpp ft_split.cpp ft_str_add_prefixe.cpp ft_str_add_suffix.cpp \
				ft_str_count_c.cpp ft_strnstr.cpp \
				\
				ft_is_only_digits.cpp ft_is_digit.cpp ft_strcmp.cpp ft_is_charset_in_str.cpp \
				ft_is_alpha.cpp ft_is_lower.cpp ft_is_upper.cpp ft_is_alpha_num.cpp \
				ft_is_char_in_str.cpp ft_is_white_space.cpp ft_is_valid_file_path.cpp\
				\
				ft_putchar.cpp ft_putchar_fd.cpp ft_putchar_fp.cpp \
				ft_putstr.cpp ft_putstr_fd.cpp ft_putstr_fp.cpp \
				ft_putnbr.cpp ft_putnbr_fd.cpp ft_putnbr_fp.cpp \
				ft_print_str_tab.cpp ft_print_str_tab_fd.cpp ft_print_str_tab_fp.cpp\
				ft_print_int_tab_fd.cpp ft_print_int_tab.cpp \
				ft_error.cpp \
				\
				ft_free_tab.cpp ft_tab_cpy.cpp ft_tab_new.cpp ft_tab_len.cpp \
				ft_add_to_tab.cpp \
				\
				ft_nbr_len.cpp ft_float_abs.cpp ft_float_floor.cpp ft_float_roof.cpp \
				ft_int_abs.cpp ft_float_round.cpp ft_swap.cpp \
				\
				ft_get_next_line.cpp ft_get_file.cpp \
				\
				ft_list_add_back.cpp ft_list_clear.cpp ft_list_map.cpp \
				ft_list_size.cpp ft_list_add_front.cpp ft_malloc_node.cpp \
				ft_list_iter.cpp ft_list_remove_node.cpp

OBJ		=		$(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))

#Compilation flag
CFLAGS	=		-Wall -Wextra -Werror -std=c++98

DEBUG =
ifdef DEBUG
    CFLAGS += -fsanitize=address -g3
endif

#Include flag
IFLAGS	=		$(foreach dir, $(INC_DIR), -I$(dir))

all:			$(NAME)

$(NAME):		$(OBJ) Makefile
				@echo "-----\nCompiling $@ ... \c"
				@ar rc $(NAME) $(OBJ)
				@ranlib $(NAME)
				@echo "DONE\n-----"

show:
				@echo "\nSRC :\n$(SRC)\n"
				@echo "OBJ :\n$(OBJ)\n"
				@echo "CFLAGS :\n$(CFLAGS)\n"
				@echo "IFLAGS :\n$(IFLAGS)\n"
				@echo "LIB_DIR :\n$(LIB_DIR)\n"

$(OBJ_DIR)/%.o : 	%.cpp
				@echo "Compiling $@ ... \c"
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
				@echo "DONE"

re:				fclean all

debug:			$(OBJ) $(NAME) srcs/main.cpp
				@echo "Creating Binary File $(_YELLOW)$@$(_WHITE) ... \c"
				@$(CC) $(CFLAGS) $(IFLAGS) srcs/main.cpp -o debug -L . -l ft
				@echo "$(_GREEN)DONE$(_WHITE)\n"

norme:
				norminette $(SRC_DIR)

clean:
				@echo "Deleting Objects Directory $(OBJ_DIR) ... \c"
				@rm -rf $(OBJ_DIR) debug
				@echo "DONE\n-----"

fclean:			clean
				@echo "Deleting library File $(NAME) ... \c"
				@rm -f $(NAME)
				@echo "DONE\n-----"

.PHONY:			all show re clean fclean debug norme