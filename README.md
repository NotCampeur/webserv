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
*  Comment each methods  

### :boom: Known bugs.. I mean features :boom:  
* Getting "Relais brisé (pipe)" error sometimes when trying to read clients' requests.  

## :writing_hand: Change log :writing_hand:  
* The whole project has been normed  

### Git status return :

        renommé :         includes/classes/Request.hpp -> Includes/Classes/request.hpp
        renommé :         includes/classes/Server.hpp -> Includes/Classes/server.hpp
        renommé :         includes/webserv.hpp -> Includes/webserv.hpp
        renommé :         libft/includes/libft.hpp -> Libft/Includes/libft.hpp
        renommé :         libft/includes/libft_array.hpp -> Libft/Includes/libft_array.hpp
        renommé :         libft/includes/libft_check.hpp -> Libft/Includes/libft_check.hpp
        renommé :         libft/includes/libft_convert.hpp -> Libft/Includes/libft_convert.hpp
        renommé :         libft/includes/libft_defines.hpp -> Libft/Includes/libft_defines.hpp
        renommé :         libft/includes/libft_error.hpp -> Libft/Includes/libft_error.hpp
        renommé :         libft/includes/libft_file.hpp -> Libft/Includes/libft_file.hpp
        renommé :         libft/includes/libft_includes.hpp -> Libft/Includes/libft_includes.hpp
        renommé :         libft/includes/libft_io.hpp -> Libft/Includes/libft_io.hpp
        renommé :         libft/includes/libft_list.hpp -> Libft/Includes/libft_list.hpp
        renommé :         libft/includes/libft_math.hpp -> Libft/Includes/libft_math.hpp
        renommé :         libft/includes/libft_string.hpp -> Libft/Includes/libft_string.hpp
        renommé :         libft/Makefile -> Libft/Makefile
        renommé :         libft/README.md -> Libft/README.md
        renommé :         libft/srcs/checks/ft_is_alpha.cpp -> Libft/Srcs/Checks/ft_is_alpha.cpp
        renommé :         libft/srcs/checks/ft_is_alpha_num.cpp -> Libft/Srcs/Checks/ft_is_alpha_num.cpp
        renommé :         libft/srcs/checks/ft_is_char_in_str.cpp -> Libft/Srcs/Checks/ft_is_char_in_str.cpp
        renommé :         libft/srcs/checks/ft_is_charset_in_str.cpp -> Libft/Srcs/Checks/ft_is_charset_in_str.cpp
        renommé :         libft/srcs/checks/ft_is_digit.cpp -> Libft/Srcs/Checks/ft_is_digit.cpp
        renommé :         libft/srcs/checks/ft_is_lower.cpp -> Libft/Srcs/Checks/ft_is_lower.cpp
        renommé :         libft/srcs/checks/ft_is_only_digits.cpp -> Libft/Srcs/Checks/ft_is_only_digits.cpp
        renommé :         libft/srcs/checks/ft_is_upper.cpp -> Libft/Srcs/Checks/ft_is_upper.cpp
        renommé :         libft/srcs/checks/ft_is_valid_file_path.cpp -> Libft/Srcs/Checks/ft_is_valid_file_path.cpp
        renommé :         libft/srcs/checks/ft_is_white_space.cpp -> Libft/Srcs/Checks/ft_is_white_space.cpp
        renommé :         libft/srcs/checks/ft_strcmp.cpp -> Libft/Srcs/Checks/ft_strcmp.cpp
        renommé :         libft/srcs/converts/ft_atoi.cpp -> Libft/Srcs/Converts/ft_atoi.cpp
        renommé :         libft/srcs/converts/ft_itoa.cpp -> Libft/Srcs/Converts/ft_itoa.cpp
        renommé :         libft/srcs/converts/ft_itoa_base.cpp -> Libft/Srcs/Converts/ft_itoa_base.cpp
        renommé :         libft/srcs/converts/ft_itoa_hexa.cpp -> Libft/Srcs/Converts/ft_itoa_hexa.cpp
        renommé :         libft/srcs/converts/ft_itoa_octa.cpp -> Libft/Srcs/Converts/ft_itoa_octa.cpp
        renommé :         libft/srcs/file/ft_get_file.cpp -> Libft/Srcs/File/ft_get_file.cpp
        renommé :         libft/srcs/file/ft_get_next_line.cpp -> Libft/Srcs/File/ft_get_next_line.cpp
        renommé :         libft/srcs/io/ft_error.cpp -> Libft/Srcs/Io/ft_error.cpp
        renommé :         libft/srcs/io/ft_print_int_tab.cpp -> Libft/Srcs/Io/ft_print_int_tab.cpp
        renommé :         libft/srcs/io/ft_print_int_tab_fd.cpp -> Libft/Srcs/Io/ft_print_int_tab_fd.cpp
        renommé :         libft/srcs/io/ft_print_str_tab.cpp -> Libft/Srcs/Io/ft_print_str_tab.cpp
        renommé :         libft/srcs/io/ft_print_str_tab_fd.cpp -> Libft/Srcs/Io/ft_print_str_tab_fd.cpp
        renommé :         libft/srcs/io/ft_print_str_tab_fp.cpp -> Libft/Srcs/Io/ft_print_str_tab_fp.cpp
        renommé :         libft/srcs/io/ft_putchar.cpp -> Libft/Srcs/Io/ft_putchar.cpp
        renommé :         libft/srcs/io/ft_putchar_fd.cpp -> Libft/Srcs/Io/ft_putchar_fd.cpp
        renommé :         libft/srcs/io/ft_putchar_fp.cpp -> Libft/Srcs/Io/ft_putchar_fp.cpp
        renommé :         libft/srcs/io/ft_putnbr.cpp -> Libft/Srcs/Io/ft_putnbr.cpp
        renommé :         libft/srcs/io/ft_putnbr_fd.cpp -> Libft/Srcs/Io/ft_putnbr_fd.cpp
        renommé :         libft/srcs/io/ft_putnbr_fp.cpp -> Libft/Srcs/Io/ft_putnbr_fp.cpp
        renommé :         libft/srcs/io/ft_putstr.cpp -> Libft/Srcs/Io/ft_putstr.cpp
        renommé :         libft/srcs/io/ft_putstr_fd.cpp -> Libft/Srcs/Io/ft_putstr_fd.cpp
        renommé :         libft/srcs/io/ft_putstr_fp.cpp -> Libft/Srcs/Io/ft_putstr_fp.cpp
        renommé :         libft/srcs/lists/ft_list_add_back.cpp -> Libft/Srcs/Lists/ft_list_add_back.cpp
        renommé :         libft/srcs/lists/ft_list_add_front.cpp -> Libft/Srcs/Lists/ft_list_add_front.cpp
        renommé :         libft/srcs/lists/ft_list_clear.cpp -> Libft/Srcs/Lists/ft_list_clear.cpp
        renommé :         libft/srcs/lists/ft_list_iter.cpp -> Libft/Srcs/Lists/ft_list_iter.cpp
        renommé :         libft/srcs/lists/ft_list_map.cpp -> Libft/Srcs/Lists/ft_list_map.cpp
        renommé :         libft/srcs/lists/ft_list_remove_node.cpp -> Libft/Srcs/Lists/ft_list_remove_node.cpp
        renommé :         libft/srcs/lists/ft_list_size.cpp -> Libft/Srcs/Lists/ft_list_size.cpp
        renommé :         libft/srcs/lists/ft_malloc_node.cpp -> Libft/Srcs/Lists/ft_malloc_node.cpp
        renommé :         libft/srcs/math/ft_float_abs.cpp -> Libft/Srcs/Math/ft_float_abs.cpp
        renommé :         libft/srcs/math/ft_float_floor.cpp -> Libft/Srcs/Math/ft_float_floor.cpp
        renommé :         libft/srcs/math/ft_float_roof.cpp -> Libft/Srcs/Math/ft_float_roof.cpp
        renommé :         libft/srcs/math/ft_float_round.cpp -> Libft/Srcs/Math/ft_float_round.cpp
        renommé :         libft/srcs/math/ft_int_abs.cpp -> Libft/Srcs/Math/ft_int_abs.cpp
        renommé :         libft/srcs/math/ft_nbr_len.cpp -> Libft/Srcs/Math/ft_nbr_len.cpp
        renommé :         libft/srcs/math/ft_swap.cpp -> Libft/Srcs/Math/ft_swap.cpp
        renommé :         libft/srcs/strings/ft_rm_charset.cpp -> Libft/Srcs/Strings/ft_rm_charset.cpp
        renommé :         libft/srcs/strings/ft_split.cpp -> Libft/Srcs/Strings/ft_split.cpp
        renommé :         libft/srcs/strings/ft_str_add_prefixe.cpp -> Libft/Srcs/Strings/ft_str_add_prefixe.cpp
        renommé :         libft/srcs/strings/ft_str_add_suffix.cpp -> Libft/Srcs/Strings/ft_str_add_suffix.cpp
        renommé :         libft/srcs/strings/ft_str_count_c.cpp -> Libft/Srcs/Strings/ft_str_count_c.cpp
        renommé :         libft/srcs/strings/ft_strcpy.cpp -> Libft/Srcs/Strings/ft_strcpy.cpp
        renommé :         libft/srcs/strings/ft_strdup.cpp -> Libft/Srcs/Strings/ft_strdup.cpp
        renommé :         libft/srcs/strings/ft_strdup_c.cpp -> Libft/Srcs/Strings/ft_strdup_c.cpp
        renommé :         libft/srcs/strings/ft_strjoin.cpp -> Libft/Srcs/Strings/ft_strjoin.cpp
        renommé :         libft/srcs/strings/ft_strlen.cpp -> Libft/Srcs/Strings/ft_strlen.cpp
        renommé :         libft/srcs/strings/ft_strnew.cpp -> Libft/Srcs/Strings/ft_strnew.cpp
        renommé :         libft/srcs/strings/ft_strnstr.cpp -> Libft/Srcs/Strings/ft_strnstr.cpp
        renommé :         libft/srcs/strings/ft_strstr.cpp -> Libft/Srcs/Strings/ft_strstr.cpp
        renommé :         libft/srcs/strings/ft_strsub.cpp -> Libft/Srcs/Strings/ft_strsub.cpp
        renommé :         libft/srcs/tabs/ft_add_to_tab.cpp -> Libft/Srcs/Tabs/ft_add_to_tab.cpp
        renommé :         libft/srcs/tabs/ft_free_tab.cpp -> Libft/Srcs/Tabs/ft_free_tab.cpp
        renommé :         libft/srcs/tabs/ft_tab_cpy.cpp -> Libft/Srcs/Tabs/ft_tab_cpy.cpp
        renommé :         libft/srcs/tabs/ft_tab_len.cpp -> Libft/Srcs/Tabs/ft_tab_len.cpp
        renommé :         libft/srcs/tabs/ft_tab_new.cpp -> Libft/Srcs/Tabs/ft_tab_new.cpp
        renommé :         libft/srcs/main.cpp -> Libft/Srcs/main.cpp
        modifié :         Makefile
        renommé :         ressources/index.html -> Ressources/index.html
        renommé :         srcs/classes/Server.cpp -> Srcs/Classes/server.cpp
        renommé :         srcs/main.cpp -> Srcs/main.cpp
