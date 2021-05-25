/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_round.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 18:54:18 by tguilbar          #+#    #+#             */
/*   Updated: 2021/05/25 18:44:54 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_round(float value)
{
	float	floor;
	float	roof;

	floor = ft_floor(value);
	roof = ft_roof(value);
	if ((value - floor) < (roof - value))
		return (floor);
	else
		return (roof);
}
