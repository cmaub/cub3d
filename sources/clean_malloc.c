/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:16:57 by anvander          #+#    #+#             */
/*   Updated: 2025/02/18 15:35:12 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] /*&& tab[i][0]*/)
	{
		// if (tab[i][0] != '\0')
			free(tab[i]);
		i++;
	}
	free(tab);
}

void	clean(t_params *par)
{
	int	i;

	i = 0;
	if (par->map)
	{
		free_tab(par->map->parse_file);
		// if (par->map->parse_file)
		// {
		// 	while (par->map->parse_file[i])
		// 	{
		// 		if (par->map->parse_file[i] != NULL && par->map->parse_file[i][0] != '\0')
		// 			free(par->map->parse_file[i]);
		// 		par->map->parse_file[i] = NULL;
		// 		printf("*****   i = %d\n", i);
		// 		i++;
		// 	}
		// 	free(par->map->parse_file);
		// }
		// map_tab
		if (par->map->path_no)
			free(par->map->path_no);
		if (par->map->path_so)
			free(par->map->path_so);
		if (par->map->path_we)
			free(par->map->path_we);
		if (par->map->path_ea)
			free(par->map->path_ea);
		if (par->map->wall_no)
		{
			mlx_destroy_image(par->mlx_ptr, par->map->wall_no->img);
			free(par->map->wall_no);
		}
		if (par->map->wall_so)
		{
			mlx_destroy_image(par->mlx_ptr, par->map->wall_so->img);
			free(par->map->wall_so);
		}
		if (par->map->wall_ea)
		{
			mlx_destroy_image(par->mlx_ptr, par->map->wall_ea->img);
			free(par->map->wall_ea);
		}
		if (par->map->wall_we)
		{
			mlx_destroy_image(par->mlx_ptr, par->map->wall_we->img);
			free(par->map->wall_we);
		}
		// if (par->mini_map)
		// {
		// 	mlx_destroy_image(par->mlx_ptr, par->mini_map->img);
		// 	free(par->mini_map);
		// }
		free(par->map);
		free(par->player);
	}
	if (par->fd != -1)
	{
		close(par->fd);
		par->fd = -1;
	}
	// close_window(par);
}


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
