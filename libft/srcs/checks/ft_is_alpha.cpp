/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alpha.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:21:16 by ldutriez          #+#    #+#             */
/*   Updated: 2021/09/15 17:44:56 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

bool	ft_is_alpha(const char c)
{
	if (ft_is_upper(c) == true || ft_is_lower(c) == true)
		return (true);
	return (false);
}
