# webserv
A 42 project about HTTP

> :warning: **Warning**: It is educational project.

> :warning: **Warning**: You can take inspiration from it but don't copy / paste what you don't understand.

In this repository you will find a server using HTTP protocol write in C++.

# Last changes :
> Adding the libft to the project  
> The server get a request of a client and send a never changing response.  
> Everything has been split up into a class.  
> Trying to read request with ft_get_file.  

# Git status return :

        modifié :         Makefile
        nouveau fichier : includes/classes/Request.hpp
        nouveau fichier : includes/classes/Server.hpp
        modifié :         includes/webserv.hpp
        nouveau fichier : libft/Makefile
        nouveau fichier : libft/README.md
        nouveau fichier : libft/includes/libft.h
        nouveau fichier : libft/includes/libft_array.h
        nouveau fichier : libft/includes/libft_check.h
        nouveau fichier : libft/includes/libft_convert.h
        nouveau fichier : libft/includes/libft_defines.h
        nouveau fichier : libft/includes/libft_error.h
        nouveau fichier : libft/includes/libft_file.h
        nouveau fichier : libft/includes/libft_includes.h
        nouveau fichier : libft/includes/libft_io.h
        nouveau fichier : libft/includes/libft_list.h
        nouveau fichier : libft/includes/libft_math.h
        nouveau fichier : libft/includes/libft_string.h
        nouveau fichier : libft/libft.a
        nouveau fichier : libft/objs/ft_add_to_tab.o
        nouveau fichier : libft/objs/ft_atoi.o
        nouveau fichier : libft/objs/ft_error.o
        nouveau fichier : libft/objs/ft_float_abs.o
        nouveau fichier : libft/objs/ft_float_floor.o
        nouveau fichier : libft/objs/ft_float_roof.o
        nouveau fichier : libft/objs/ft_float_round.o
        nouveau fichier : libft/objs/ft_free_tab.o
        nouveau fichier : libft/objs/ft_get_file.o
        nouveau fichier : libft/objs/ft_get_next_line.o
        nouveau fichier : libft/objs/ft_int_abs.o
        nouveau fichier : libft/objs/ft_is_alpha.o
        nouveau fichier : libft/objs/ft_is_alpha_num.o
        nouveau fichier : libft/objs/ft_is_char_in_str.o
        nouveau fichier : libft/objs/ft_is_charset_in_str.o
        nouveau fichier : libft/objs/ft_is_digit.o
        nouveau fichier : libft/objs/ft_is_lower.o
        nouveau fichier : libft/objs/ft_is_only_digits.o
        nouveau fichier : libft/objs/ft_is_upper.o
        nouveau fichier : libft/objs/ft_is_valid_file_path.o
        nouveau fichier : libft/objs/ft_is_white_space.o
        nouveau fichier : libft/objs/ft_itoa.o
        nouveau fichier : libft/objs/ft_itoa_base.o
        nouveau fichier : libft/objs/ft_itoa_hexa.o
        nouveau fichier : libft/objs/ft_itoa_octa.o
        nouveau fichier : libft/objs/ft_list_add_back.o
        nouveau fichier : libft/objs/ft_list_add_front.o
        nouveau fichier : libft/objs/ft_list_clear.o
        nouveau fichier : libft/objs/ft_list_iter.o
        nouveau fichier : libft/objs/ft_list_map.o
        nouveau fichier : libft/objs/ft_list_remove_node.o
        nouveau fichier : libft/objs/ft_list_size.o
        nouveau fichier : libft/objs/ft_malloc_node.o
        nouveau fichier : libft/objs/ft_nbr_len.o
        nouveau fichier : libft/objs/ft_print_int_tab.o
        nouveau fichier : libft/objs/ft_print_int_tab_fd.o
        nouveau fichier : libft/objs/ft_print_str_tab.o
        nouveau fichier : libft/objs/ft_print_str_tab_fd.o
        nouveau fichier : libft/objs/ft_print_str_tab_fp.o
        nouveau fichier : libft/objs/ft_putchar.o
        nouveau fichier : libft/objs/ft_putchar_fd.o
        nouveau fichier : libft/objs/ft_putchar_fp.o
        nouveau fichier : libft/objs/ft_putnbr.o
        nouveau fichier : libft/objs/ft_putnbr_fd.o
        nouveau fichier : libft/objs/ft_putnbr_fp.o
        nouveau fichier : libft/objs/ft_putstr.o
        nouveau fichier : libft/objs/ft_putstr_fd.o
        nouveau fichier : libft/objs/ft_putstr_fp.o
        nouveau fichier : libft/objs/ft_rm_charset.o
        nouveau fichier : libft/objs/ft_split.o
        nouveau fichier : libft/objs/ft_str_add_prefixe.o
        nouveau fichier : libft/objs/ft_str_add_suffix.o
        nouveau fichier : libft/objs/ft_str_count_c.o
        nouveau fichier : libft/objs/ft_strcmp.o
        nouveau fichier : libft/objs/ft_strcpy.o
        nouveau fichier : libft/objs/ft_strdup.o
        nouveau fichier : libft/objs/ft_strdup_c.o
        nouveau fichier : libft/objs/ft_strjoin.o
        nouveau fichier : libft/objs/ft_strlen.o
        nouveau fichier : libft/objs/ft_strnew.o
        nouveau fichier : libft/objs/ft_strnstr.o
        nouveau fichier : libft/objs/ft_strstr.o
        nouveau fichier : libft/objs/ft_strsub.o
        nouveau fichier : libft/objs/ft_swap.o
        nouveau fichier : libft/objs/ft_tab_cpy.o
        nouveau fichier : libft/objs/ft_tab_len.o
        nouveau fichier : libft/objs/ft_tab_new.o
        nouveau fichier : libft/srcs/checks/ft_is_alpha.c
        nouveau fichier : libft/srcs/checks/ft_is_alpha_num.c
        nouveau fichier : libft/srcs/checks/ft_is_char_in_str.c
        nouveau fichier : libft/srcs/checks/ft_is_charset_in_str.c
        nouveau fichier : libft/srcs/checks/ft_is_digit.c
        nouveau fichier : libft/srcs/checks/ft_is_lower.c
        nouveau fichier : libft/srcs/checks/ft_is_only_digits.c
        nouveau fichier : libft/srcs/checks/ft_is_upper.c
        nouveau fichier : libft/srcs/checks/ft_is_valid_file_path.c
        nouveau fichier : libft/srcs/checks/ft_is_white_space.c
        nouveau fichier : libft/srcs/checks/ft_strcmp.c
        nouveau fichier : libft/srcs/converts/ft_atoi.c
        nouveau fichier : libft/srcs/converts/ft_itoa.c
        nouveau fichier : libft/srcs/converts/ft_itoa_base.c
        nouveau fichier : libft/srcs/converts/ft_itoa_hexa.c
        nouveau fichier : libft/srcs/converts/ft_itoa_octa.c
        nouveau fichier : libft/srcs/file/ft_get_file.c
        nouveau fichier : libft/srcs/file/ft_get_next_line.c
        nouveau fichier : libft/srcs/io/ft_error.c
        nouveau fichier : libft/srcs/io/ft_print_int_tab.c
        nouveau fichier : libft/srcs/io/ft_print_int_tab_fd.c
        nouveau fichier : libft/srcs/io/ft_print_str_tab.c
        nouveau fichier : libft/srcs/io/ft_print_str_tab_fd.c
        nouveau fichier : libft/srcs/io/ft_print_str_tab_fp.c
        nouveau fichier : libft/srcs/io/ft_putchar.c
        nouveau fichier : libft/srcs/io/ft_putchar_fd.c
        nouveau fichier : libft/srcs/io/ft_putchar_fp.c
        nouveau fichier : libft/srcs/io/ft_putnbr.c
        nouveau fichier : libft/srcs/io/ft_putnbr_fd.c
        nouveau fichier : libft/srcs/io/ft_putnbr_fp.c
        nouveau fichier : libft/srcs/io/ft_putstr.c
        nouveau fichier : libft/srcs/io/ft_putstr_fd.c
        nouveau fichier : libft/srcs/io/ft_putstr_fp.c
        nouveau fichier : libft/srcs/lists/ft_list_add_back.c
        nouveau fichier : libft/srcs/lists/ft_list_add_front.c
        nouveau fichier : libft/srcs/lists/ft_list_clear.c
        nouveau fichier : libft/srcs/lists/ft_list_iter.c
        nouveau fichier : libft/srcs/lists/ft_list_map.c
        nouveau fichier : libft/srcs/lists/ft_list_remove_node.c
        nouveau fichier : libft/srcs/lists/ft_list_size.c
        nouveau fichier : libft/srcs/lists/ft_malloc_node.c
        nouveau fichier : libft/srcs/main.c
        nouveau fichier : libft/srcs/math/ft_float_abs.c
        nouveau fichier : libft/srcs/math/ft_float_floor.c
        nouveau fichier : libft/srcs/math/ft_float_roof.c
        nouveau fichier : libft/srcs/math/ft_float_round.c
        nouveau fichier : libft/srcs/math/ft_int_abs.c
        nouveau fichier : libft/srcs/math/ft_nbr_len.c
        nouveau fichier : libft/srcs/math/ft_swap.c
        nouveau fichier : libft/srcs/strings/ft_rm_charset.c
        nouveau fichier : libft/srcs/strings/ft_split.c
        nouveau fichier : libft/srcs/strings/ft_str_add_prefixe.c
        nouveau fichier : libft/srcs/strings/ft_str_add_suffix.c
        nouveau fichier : libft/srcs/strings/ft_str_count_c.c
        nouveau fichier : libft/srcs/strings/ft_strcpy.c
        nouveau fichier : libft/srcs/strings/ft_strdup.c
        nouveau fichier : libft/srcs/strings/ft_strdup_c.c
        nouveau fichier : libft/srcs/strings/ft_strjoin.c
        nouveau fichier : libft/srcs/strings/ft_strlen.c
        nouveau fichier : libft/srcs/strings/ft_strnew.c
        nouveau fichier : libft/srcs/strings/ft_strnstr.c
        nouveau fichier : libft/srcs/strings/ft_strstr.c
        nouveau fichier : libft/srcs/strings/ft_strsub.c
        nouveau fichier : libft/srcs/tabs/ft_add_to_tab.c
        nouveau fichier : libft/srcs/tabs/ft_free_tab.c
        nouveau fichier : libft/srcs/tabs/ft_tab_cpy.c
        nouveau fichier : libft/srcs/tabs/ft_tab_len.c
        nouveau fichier : libft/srcs/tabs/ft_tab_new.c
        modifié :         ressources/index.html
        nouveau fichier : srcs/classes/Server.cpp
        modifié :         srcs/main.cpp