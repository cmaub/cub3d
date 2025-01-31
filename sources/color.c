/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:31:18 by cmaubert          #+#    #+#             */
/*   Updated: 2025/01/31 16:32:45 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	is_color_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	if (ft_strlen(str) > 3)
		return (FALSE);
	return (TRUE);
}

int	check_color_params(char *str, int *rgb)
{
	char **params;
	int	i;
	int	nb;
	
	str += 2;
	i = 0;
	params = ft_split(str, ',');
	if (!params)
		return (printf("line %d\n", __LINE__),FALSE);
	while (params[i])
	{
		if (!is_color_valid(params[i]))
			return (FALSE);
		nb = ft_atoi(params[i]);
		if (nb < 0 || nb > 255)
			return (FALSE);
		i++;
	}
	if (i != 3)
		return (printf("line %d\n", __LINE__),FALSE);
	(*rgb) = rgb_to_int(ft_atoi(params[0]), ft_atoi(params[1]), ft_atoi(params[2]));
	return (TRUE);
}