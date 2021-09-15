/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alpha_num.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:30:13 by ldutriez          #+#    #+#             */
/*   Updated: 2021/09/15 17:44:56 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

bool	ft_is_alpha_num(const char c)
{
	if (ft_is_digit(c) == true || ft_is_alpha(c) == true)
		return (true);
	return (false);
}
