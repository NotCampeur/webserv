/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alpha.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:21:16 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/26 14:31:21 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.hpp"

t_bool	ft_is_alpha(const char c)
{
	if (ft_is_upper(c) == b_true || ft_is_lower(c) == b_true)
		return (b_true);
	return (b_false);
}
