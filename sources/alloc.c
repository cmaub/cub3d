/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:46:20 by anvander          #+#    #+#             */
/*   Updated: 2025/02/20 16:29:04 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*clean_malloc(size_t size, t_params *par)
{
	void	*p;

	p = malloc(size);
	if (p == NULL)
	{
		write(1, "fatal: out of memory\n", 21);
		if (par)
			close_window(par);
		return (NULL);
	}
	ft_bzero(p, size);
	return (p);
}

int	count_alloc(t_map *map, char *file)
{
	int		fd;
	char	*str;
	int		size;

	size = 0;
	fd = open(file, R_OK);
	if (fd == -1)
		return (printf("Error\nthe file cannot be open\n"), FALSE);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		map->nb_lines++;
		if ((int)ft_strlen(str) > map->length_max)
			map->length_max = (int)ft_strlen(str);
		free(str);
	}
	close(fd);
	size = map->nb_lines * map->length_max + 1;
	map->parse_file = clean_malloc(sizeof(char *) * size, map->par);
	return (TRUE);
}
