/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:31:18 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/25 10:08:06 by anvander         ###   ########.fr       */
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
	char	**tab;
	int		i;
	int		nb;

	if (!str)
		return (FALSE);
	if (!check_syntax(str))
		return (FALSE);
	i = -1;
	tab = ft_split(str, ',');
	if (!tab)
		return (FALSE);
	while (tab[++i])
	{
		if (!is_color_valid(tab[i]))
			return (free_tab(tab), FALSE);
		nb = ft_atoi(tab[i]);
		if (nb < 0 || nb > 255)
			return (free_tab(tab), FALSE);
	}
	if (i != 3)
		return (printf("Error\nwrong color param\n"), free_tab(tab), FALSE);
	(*rgb) = rgb_to_int(ft_atoi(tab[0]), ft_atoi(tab[1]),
			ft_atoi(tab[2]));
	return (free_tab(tab), TRUE);
}
