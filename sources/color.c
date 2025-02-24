/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:31:18 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/24 17:56:29 by cmaubert         ###   ########.fr       */
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

int	check_syntax(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < 4 && str[i] != '\0')
	{
		if ((!ft_isdigit(str[i]) && str[i] != ',')
			|| (str[i] == ',' && str[i + 1] == ','))
			return (FALSE);
		if (ft_isdigit(str[i]))
			i++;
		if (str[i] == ',')
		{
			flag++;
			str += i + 1;
			i = 0;
		}
	}
	if (flag != 2 || str[i] != '\0')
		return (FALSE);
	return (TRUE);
}

int	check_color_params(char *str, int *rgb)
{
	char	**params;
	int		i;
	int		nb;

	if (!str)
		return (FALSE);
	if (!check_syntax(str))
		return (FALSE);
	i = -1;
	params = ft_split(str, ',');
	if (!params)
		return (FALSE);
	while (params[++i])
	{
		if (!is_color_valid(params[i]))
			return (free_tab(params), FALSE);
		nb = ft_atoi(params[i]);
		if (nb < 0 || nb > 255)
			return (free_tab(params), FALSE);
	}
	if (i != 3)
		return (printf("wrong color param\n"), free_tab(params),
			FALSE);
	(*rgb) = rgb_to_int(ft_atoi(params[0]), ft_atoi(params[1]),
			ft_atoi(params[2]));
	return (free_tab(params), TRUE);
}
