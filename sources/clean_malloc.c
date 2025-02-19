/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:16:57 by anvander          #+#    #+#             */
/*   Updated: 2025/02/19 12:16:43 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_path(t_params *par)
{
	if (par->map->path_no)
		free(par->map->path_no);
	if (par->map->path_so)
		free(par->map->path_so);
	if (par->map->path_we)
		free(par->map->path_we);
	if (par->map->path_ea)
		free(par->map->path_ea);
}

void	free_texure_img(t_params *par)
{
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
}

void	clean(t_params *par)
{
	int	i;

	i = 0;
	if (par->map)
	{
		free_tab(par->map->parse_file);
		free_path(par);
		free_texure_img(par);
		// if (par->mini_map)
		// {
		// 	mlx_destroy_image(par->mlx_ptr, par->mini_map->img);
		// 	free(par->mini_map);
		// }
		(free(par->map), free(par->player));
	}
	if (par->fd != -1)
	{
		close(par->fd);
		par->fd = -1;
	}
}

int	close_window(t_params *par)
{
	clean(par);
	if (par->img)
		mlx_destroy_image(par->mlx_ptr, par->img->img);
	if (par->win_ptr)
		mlx_destroy_window(par->mlx_ptr, par->win_ptr);
	if (par->mlx_ptr)
	{
		mlx_destroy_display(par->mlx_ptr);
		free(par->mlx_ptr);
	}
	if (par->img)
		free(par->img);
	if (par)
		free(par);
	exit(1);
	return (0);
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
