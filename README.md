# webserv
A 42 project about HTTP

> :warning: **Warning**: It is educational project.

> :warning: **Warning**: You can take inspiration from it but don't copy / paste what you don't understand.

In this repository you will find a server using HTTP protocol write in C++.

# Last changes :
> The libft become a Cpp library to avoid some linking troubles.  
> The ft_get_file() don't fit well to read client's request.  

# Git status return :

        modifié :         Makefile
        modifié :         README.md
        modifié :         includes/classes/Request.hpp
        modifié :         includes/classes/Server.hpp
        modifié :         includes/webserv.hpp
        modifié :         libft/Makefile
        modifié :         libft/README.md
        modifié :         libft/includes/libft_check.h
        modifié :         libft/includes/libft_convert.h
        modifié :         libft/includes/libft_defines.h
        modifié :         libft/includes/libft_error.h
        modifié :         libft/includes/libft_file.h
        modifié :         libft/includes/libft_io.h
        modifié :         libft/includes/libft_list.h
        modifié :         libft/includes/libft_math.h
        modifié :         libft/includes/libft_string.h
        supprimé :        libft/libft.a
        supprimé :        libft/objs/ft_add_to_tab.o
        supprimé :        libft/objs/ft_atoi.o
        supprimé :        libft/objs/ft_error.o
        supprimé :        libft/objs/ft_float_abs.o
        supprimé :        libft/objs/ft_float_floor.o
        supprimé :        libft/objs/ft_float_roof.o
        supprimé :        libft/objs/ft_float_round.o
        supprimé :        libft/objs/ft_free_tab.o
        supprimé :        libft/objs/ft_get_file.o
        supprimé :        libft/objs/ft_get_next_line.o
        supprimé :        libft/objs/ft_int_abs.o
        supprimé :        libft/objs/ft_is_alpha.o
        supprimé :        libft/objs/ft_is_alpha_num.o
        supprimé :        libft/objs/ft_is_char_in_str.o
        supprimé :        libft/objs/ft_is_charset_in_str.o
        supprimé :        libft/objs/ft_is_digit.o
        supprimé :        libft/objs/ft_is_lower.o
        supprimé :        libft/objs/ft_is_only_digits.o
        supprimé :        libft/objs/ft_is_upper.o
        supprimé :        libft/objs/ft_is_valid_file_path.o
        supprimé :        libft/objs/ft_is_white_space.o
        supprimé :        libft/objs/ft_itoa.o
        supprimé :        libft/objs/ft_itoa_base.o
        supprimé :        libft/objs/ft_itoa_hexa.o
        supprimé :        libft/objs/ft_itoa_octa.o
        supprimé :        libft/objs/ft_list_add_back.o
        supprimé :        libft/objs/ft_list_add_front.o
        supprimé :        libft/objs/ft_list_clear.o
        supprimé :        libft/objs/ft_list_iter.o
        supprimé :        libft/objs/ft_list_map.o
        supprimé :        libft/objs/ft_list_remove_node.o
        supprimé :        libft/objs/ft_list_size.o
        supprimé :        libft/objs/ft_malloc_node.o
        supprimé :        libft/objs/ft_nbr_len.o
        supprimé :        libft/objs/ft_print_int_tab.o
        supprimé :        libft/objs/ft_print_int_tab_fd.o
        supprimé :        libft/objs/ft_print_str_tab.o
        supprimé :        libft/objs/ft_print_str_tab_fd.o
        supprimé :        libft/objs/ft_print_str_tab_fp.o
        supprimé :        libft/objs/ft_putchar.o
        supprimé :        libft/objs/ft_putchar_fd.o
        supprimé :        libft/objs/ft_putchar_fp.o
        supprimé :        libft/objs/ft_putnbr.o
        supprimé :        libft/objs/ft_putnbr_fd.o
        supprimé :        libft/objs/ft_putnbr_fp.o
        supprimé :        libft/objs/ft_putstr.o
        supprimé :        libft/objs/ft_putstr_fd.o
        supprimé :        libft/objs/ft_putstr_fp.o
        supprimé :        libft/objs/ft_rm_charset.o
        supprimé :        libft/objs/ft_split.o
        supprimé :        libft/objs/ft_str_add_prefixe.o
        supprimé :        libft/objs/ft_str_add_suffix.o
        supprimé :        libft/objs/ft_str_count_c.o
        supprimé :        libft/objs/ft_strcmp.o
        supprimé :        libft/objs/ft_strcpy.o
        supprimé :        libft/objs/ft_strdup.o
        supprimé :        libft/objs/ft_strdup_c.o
        supprimé :        libft/objs/ft_strjoin.o
        supprimé :        libft/objs/ft_strlen.o
        supprimé :        libft/objs/ft_strnew.o
        supprimé :        libft/objs/ft_strnstr.o
        supprimé :        libft/objs/ft_strstr.o
        supprimé :        libft/objs/ft_strsub.o
        supprimé :        libft/objs/ft_swap.o
        supprimé :        libft/objs/ft_tab_cpy.o
        supprimé :        libft/objs/ft_tab_len.o
        supprimé :        libft/objs/ft_tab_new.o
        renommé :         libft/srcs/checks/ft_is_alpha.c -> libft/srcs/checks/ft_is_alpha.cpp
        renommé :         libft/srcs/checks/ft_is_alpha_num.c -> libft/srcs/checks/ft_is_alpha_num.cpp
        renommé :         libft/srcs/checks/ft_is_char_in_str.c -> libft/srcs/checks/ft_is_char_in_str.cpp
        renommé :         libft/srcs/checks/ft_is_charset_in_str.c -> libft/srcs/checks/ft_is_charset_in_str.cpp
        renommé :         libft/srcs/checks/ft_is_digit.c -> libft/srcs/checks/ft_is_digit.cpp
        renommé :         libft/srcs/checks/ft_is_lower.c -> libft/srcs/checks/ft_is_lower.cpp
        renommé :         libft/srcs/checks/ft_is_only_digits.c -> libft/srcs/checks/ft_is_only_digits.cpp
        renommé :         libft/srcs/checks/ft_is_upper.c -> libft/srcs/checks/ft_is_upper.cpp
        renommé :         libft/srcs/checks/ft_is_valid_file_path.c -> libft/srcs/checks/ft_is_valid_file_path.cpp
        renommé :         libft/srcs/checks/ft_is_white_space.c -> libft/srcs/checks/ft_is_white_space.cpp
        renommé :         libft/srcs/checks/ft_strcmp.c -> libft/srcs/checks/ft_strcmp.cpp
        renommé :         libft/srcs/converts/ft_atoi.c -> libft/srcs/converts/ft_atoi.cpp
        supprimé :        libft/srcs/converts/ft_itoa.c
        nouveau fichier : libft/srcs/converts/ft_itoa.cpp
        renommé :         libft/srcs/converts/ft_itoa_base.c -> libft/srcs/converts/ft_itoa_base.cpp
        supprimé :        libft/srcs/converts/ft_itoa_hexa.c
        nouveau fichier : libft/srcs/converts/ft_itoa_hexa.cpp
        renommé :         libft/srcs/converts/ft_itoa_octa.c -> libft/srcs/converts/ft_itoa_octa.cpp
        renommé :         libft/srcs/file/ft_get_file.c -> libft/srcs/file/ft_get_file.cpp
        renommé :         libft/srcs/file/ft_get_next_line.c -> libft/srcs/file/ft_get_next_line.cpp
        renommé :         libft/srcs/io/ft_error.c -> libft/srcs/io/ft_error.cpp
        renommé :         libft/srcs/io/ft_print_int_tab.c -> libft/srcs/io/ft_print_int_tab.cpp
        renommé :         libft/srcs/io/ft_print_int_tab_fd.c -> libft/srcs/io/ft_print_int_tab_fd.cpp
        renommé :         libft/srcs/io/ft_print_str_tab.c -> libft/srcs/io/ft_print_str_tab.cpp
        renommé :         libft/srcs/io/ft_print_str_tab_fd.c -> libft/srcs/io/ft_print_str_tab_fd.cpp
        renommé :         libft/srcs/io/ft_print_str_tab_fp.c -> libft/srcs/io/ft_print_str_tab_fp.cpp
        renommé :         libft/srcs/io/ft_putchar.c -> libft/srcs/io/ft_putchar.cpp
        renommé :         libft/srcs/io/ft_putchar_fd.c -> libft/srcs/io/ft_putchar_fd.cpp
        renommé :         libft/srcs/io/ft_putchar_fp.c -> libft/srcs/io/ft_putchar_fp.cpp
        renommé :         libft/srcs/io/ft_putnbr.c -> libft/srcs/io/ft_putnbr.cpp
        renommé :         libft/srcs/io/ft_putnbr_fd.c -> libft/srcs/io/ft_putnbr_fd.cpp
        renommé :         libft/srcs/io/ft_putnbr_fp.c -> libft/srcs/io/ft_putnbr_fp.cpp
        renommé :         libft/srcs/io/ft_putstr.c -> libft/srcs/io/ft_putstr.cpp
        supprimé :        libft/srcs/io/ft_putstr_fd.c
        nouveau fichier : libft/srcs/io/ft_putstr_fd.cpp
        renommé :         libft/srcs/io/ft_putstr_fp.c -> libft/srcs/io/ft_putstr_fp.cpp
        renommé :         libft/srcs/lists/ft_list_add_back.c -> libft/srcs/lists/ft_list_add_back.cpp
        renommé :         libft/srcs/lists/ft_list_add_front.c -> libft/srcs/lists/ft_list_add_front.cpp
        renommé :         libft/srcs/lists/ft_list_clear.c -> libft/srcs/lists/ft_list_clear.cpp
        renommé :         libft/srcs/lists/ft_list_iter.c -> libft/srcs/lists/ft_list_iter.cpp
        renommé :         libft/srcs/lists/ft_list_map.c -> libft/srcs/lists/ft_list_map.cpp
        renommé :         libft/srcs/lists/ft_list_remove_node.c -> libft/srcs/lists/ft_list_remove_node.cpp
        renommé :         libft/srcs/lists/ft_list_size.c -> libft/srcs/lists/ft_list_size.cpp
        renommé :         libft/srcs/lists/ft_malloc_node.c -> libft/srcs/lists/ft_malloc_node.cpp
        renommé :         libft/srcs/main.c -> libft/srcs/main.cpp
        renommé :         libft/srcs/math/ft_float_abs.c -> libft/srcs/math/ft_float_abs.cpp
        renommé :         libft/srcs/math/ft_float_floor.c -> libft/srcs/math/ft_float_floor.cpp
        renommé :         libft/srcs/math/ft_float_roof.c -> libft/srcs/math/ft_float_roof.cpp
        renommé :         libft/srcs/math/ft_float_round.c -> libft/srcs/math/ft_float_round.cpp
        renommé :         libft/srcs/math/ft_int_abs.c -> libft/srcs/math/ft_int_abs.cpp
        renommé :         libft/srcs/math/ft_nbr_len.c -> libft/srcs/math/ft_nbr_len.cpp
        renommé :         libft/srcs/math/ft_swap.c -> libft/srcs/math/ft_swap.cpp
        renommé :         libft/srcs/strings/ft_rm_charset.c -> libft/srcs/strings/ft_rm_charset.cpp
        renommé :         libft/srcs/strings/ft_split.c -> libft/srcs/strings/ft_split.cpp
        renommé :         libft/srcs/strings/ft_str_add_prefixe.c -> libft/srcs/strings/ft_str_add_prefixe.cpp
        renommé :         libft/srcs/strings/ft_str_add_suffix.c -> libft/srcs/strings/ft_str_add_suffix.cpp
        renommé :         libft/srcs/strings/ft_str_count_c.c -> libft/srcs/strings/ft_str_count_c.cpp
        renommé :         libft/srcs/strings/ft_strcpy.c -> libft/srcs/strings/ft_strcpy.cpp
        renommé :         libft/srcs/strings/ft_strdup.c -> libft/srcs/strings/ft_strdup.cpp
        renommé :         libft/srcs/strings/ft_strdup_c.c -> libft/srcs/strings/ft_strdup_c.cpp
        renommé :         libft/srcs/strings/ft_strjoin.c -> libft/srcs/strings/ft_strjoin.cpp
        renommé :         libft/srcs/strings/ft_strlen.c -> libft/srcs/strings/ft_strlen.cpp
        renommé :         libft/srcs/strings/ft_strnew.c -> libft/srcs/strings/ft_strnew.cpp
        renommé :         libft/srcs/strings/ft_strnstr.c -> libft/srcs/strings/ft_strnstr.cpp
        supprimé :        libft/srcs/strings/ft_strstr.c
        nouveau fichier : libft/srcs/strings/ft_strstr.cpp
        renommé :         libft/srcs/strings/ft_strsub.c -> libft/srcs/strings/ft_strsub.cpp
        renommé :         libft/srcs/tabs/ft_add_to_tab.c -> libft/srcs/tabs/ft_add_to_tab.cpp
        renommé :         libft/srcs/tabs/ft_free_tab.c -> libft/srcs/tabs/ft_free_tab.cpp
        renommé :         libft/srcs/tabs/ft_tab_cpy.c -> libft/srcs/tabs/ft_tab_cpy.cpp
        renommé :         libft/srcs/tabs/ft_tab_len.c -> libft/srcs/tabs/ft_tab_len.cpp
        renommé :         libft/srcs/tabs/ft_tab_new.c -> libft/srcs/tabs/ft_tab_new.cpp
        modifié :         srcs/classes/Server.cpp
        modifié :         srcs/main.cpp