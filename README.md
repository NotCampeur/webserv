# webserv
A 42 project about HTTP  

> :warning: **Warning**: It is educational project.  

> :warning: **Warning**: You can take inspiration from it but don't copy / paste what you don't understand.  

## Install  
You only need to run **make**.  
All libraries will be build and the binary will be ready to launch  

## Content
* A simple read/write communication HTTP server.  

## The Norm
<img align="center" src="Norm.png" alt="Screenshot of the project norm" />

### :zzz: TODO :zzz:  
*    

### :boom: Known bugs.. I mean features :boom:  
*

## :writing_hand: Change log :writing_hand:  
* The libft become a Cpp library to avoid some linking troubles. (The .h are now .hpp)  
* The ft_get_file() don't fit well to read client's request.  

### Git status return :

        modifié :         Makefile
        modifié :         includes/classes/Request.hpp
        modifié :         includes/classes/Server.hpp
        modifié :         includes/webserv.hpp
        renommé :         libft/includes/libft.h -> libft/includes/libft.hpp
        renommé :         libft/includes/libft_array.h -> libft/includes/libft_array.hpp
        renommé :         libft/includes/libft_check.h -> libft/includes/libft_check.hpp
        renommé :         libft/includes/libft_convert.h -> libft/includes/libft_convert.hpp
        renommé :         libft/includes/libft_defines.h -> libft/includes/libft_defines.hpp
        renommé :         libft/includes/libft_error.h -> libft/includes/libft_error.hpp
        renommé :         libft/includes/libft_file.h -> libft/includes/libft_file.hpp
        renommé :         libft/includes/libft_includes.h -> libft/includes/libft_includes.hpp
        renommé :         libft/includes/libft_io.h -> libft/includes/libft_io.hpp
        renommé :         libft/includes/libft_list.h -> libft/includes/libft_list.hpp
        renommé :         libft/includes/libft_math.h -> libft/includes/libft_math.hpp
        renommé :         libft/includes/libft_string.h -> libft/includes/libft_string.hpp
        modifié :         libft/srcs/checks/ft_is_alpha.cpp
        modifié :         libft/srcs/checks/ft_is_alpha_num.cpp
        modifié :         libft/srcs/checks/ft_is_char_in_str.cpp
        modifié :         libft/srcs/checks/ft_is_charset_in_str.cpp
        modifié :         libft/srcs/checks/ft_is_digit.cpp
        modifié :         libft/srcs/checks/ft_is_lower.cpp
        modifié :         libft/srcs/checks/ft_is_only_digits.cpp
        modifié :         libft/srcs/checks/ft_is_upper.cpp
        modifié :         libft/srcs/checks/ft_is_valid_file_path.cpp
        modifié :         libft/srcs/checks/ft_is_white_space.cpp
        modifié :         libft/srcs/checks/ft_strcmp.cpp
        modifié :         libft/srcs/converts/ft_atoi.cpp
        modifié :         libft/srcs/converts/ft_itoa.cpp
        modifié :         libft/srcs/converts/ft_itoa_base.cpp
        modifié :         libft/srcs/converts/ft_itoa_hexa.cpp
        modifié :         libft/srcs/converts/ft_itoa_octa.cpp
        modifié :         libft/srcs/file/ft_get_file.cpp
        modifié :         libft/srcs/file/ft_get_next_line.cpp
        modifié :         libft/srcs/io/ft_error.cpp
        modifié :         libft/srcs/io/ft_print_int_tab.cpp
        modifié :         libft/srcs/io/ft_print_int_tab_fd.cpp
        modifié :         libft/srcs/io/ft_print_str_tab.cpp
        modifié :         libft/srcs/io/ft_print_str_tab_fd.cpp
        modifié :         libft/srcs/io/ft_print_str_tab_fp.cpp
        modifié :         libft/srcs/io/ft_putchar.cpp
        modifié :         libft/srcs/io/ft_putchar_fd.cpp
        modifié :         libft/srcs/io/ft_putchar_fp.cpp
        modifié :         libft/srcs/io/ft_putnbr.cpp
        modifié :         libft/srcs/io/ft_putnbr_fd.cpp
        modifié :         libft/srcs/io/ft_putnbr_fp.cpp
        modifié :         libft/srcs/io/ft_putstr.cpp
        modifié :         libft/srcs/io/ft_putstr_fd.cpp
        modifié :         libft/srcs/io/ft_putstr_fp.cpp
        modifié :         libft/srcs/lists/ft_list_add_back.cpp
        modifié :         libft/srcs/lists/ft_list_add_front.cpp
        modifié :         libft/srcs/lists/ft_list_clear.cpp
        modifié :         libft/srcs/lists/ft_list_iter.cpp
        modifié :         libft/srcs/lists/ft_list_map.cpp
        modifié :         libft/srcs/lists/ft_list_remove_node.cpp
        modifié :         libft/srcs/lists/ft_list_size.cpp
        modifié :         libft/srcs/lists/ft_malloc_node.cpp
        modifié :         libft/srcs/main.cpp
        modifié :         libft/srcs/math/ft_float_abs.cpp
        modifié :         libft/srcs/math/ft_float_floor.cpp
        modifié :         libft/srcs/math/ft_float_roof.cpp
        modifié :         libft/srcs/math/ft_float_round.cpp
        modifié :         libft/srcs/math/ft_int_abs.cpp
        modifié :         libft/srcs/math/ft_nbr_len.cpp
        modifié :         libft/srcs/math/ft_swap.cpp
        modifié :         libft/srcs/strings/ft_rm_charset.cpp
        modifié :         libft/srcs/strings/ft_split.cpp
        modifié :         libft/srcs/strings/ft_str_add_prefixe.cpp
        modifié :         libft/srcs/strings/ft_str_add_suffix.cpp
        modifié :         libft/srcs/strings/ft_str_count_c.cpp
        modifié :         libft/srcs/strings/ft_strcpy.cpp
        modifié :         libft/srcs/strings/ft_strdup.cpp
        modifié :         libft/srcs/strings/ft_strdup_c.cpp
        modifié :         libft/srcs/strings/ft_strjoin.cpp
        modifié :         libft/srcs/strings/ft_strlen.cpp
        modifié :         libft/srcs/strings/ft_strnew.cpp
        modifié :         libft/srcs/strings/ft_strnstr.cpp
        modifié :         libft/srcs/strings/ft_strstr.cpp
        modifié :         libft/srcs/strings/ft_strsub.cpp
        modifié :         libft/srcs/tabs/ft_add_to_tab.cpp
        modifié :         libft/srcs/tabs/ft_free_tab.cpp
        modifié :         libft/srcs/tabs/ft_tab_cpy.cpp
        modifié :         libft/srcs/tabs/ft_tab_len.cpp
        modifié :         libft/srcs/tabs/ft_tab_new.cpp
        modifié :         srcs/classes/Server.cpp
