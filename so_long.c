/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:20:39 by inunez-g          #+#    #+#             */
/*   Updated: 2022/03/04 10:48:27 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

int	closer(t_vars *vars)
{
	(void)vars;
	exit(0);
}

void	screen_moves(t_vars *vars)
{
	char	*move_count;
	int		color;

	(void)vars;
	vars->my_map.moves += 1;
	move_count = ft_itoa(vars->my_map.moves);
	color = 0x800080;
	ft_put_image(vars, "so_long_objs/blacksq.xpm",
		(vars->my_map.cols - 1), (vars->my_map.rows));
	mlx_string_put(vars->mlx, vars->win, vars->my_map.cols * TILE_SIZE - 80,
		vars->my_map.rows * TILE_SIZE + 20, color, "Move: ");
	mlx_string_put(vars->mlx, vars->win, vars->my_map.cols * TILE_SIZE - 30,
		vars->my_map.rows * TILE_SIZE + 20, color, move_count);
}

void	mapa_invalido(void)
{
	write(1, "¡ERROR! Invalid map.\n", 21);
	exit (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_data	data;

	vars.my_map.cols = 0;
	vars.my_map.rows = 0;
	(void)data;
	if (argc == 2)
		get_map(argv[1], &vars);
	else
	{
		write(1, "You must submit one map.\n", 25);
		return (0);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.my_map.cols * TILE_SIZE,
			vars.my_map.rows * TILE_SIZE + 30, "My_So_Long");
	vars.img.img = mlx_new_image(vars.mlx, vars.my_map.cols * TILE_SIZE,
			vars.my_map.rows * TILE_SIZE);
	vars.img.data = (int *)mlx_get_data_addr(vars.img.img, &vars.img.bpp,
			&vars.img.line_length, &vars.img.endian);
	draw_rectangles(&vars, 1);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, EXIT, 0, &closer, &vars);
	mlx_loop(vars.mlx);
	exit(0);
}
