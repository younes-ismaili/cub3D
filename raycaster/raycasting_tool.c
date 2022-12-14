/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_tool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:03:04 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/30 19:05:34 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	dda(t_struct *cub, int x_0, int y_0)
{
	int		i;
	float	x;
	float	y;

	cub->tmp.dstnc_x = cub->ray.wallhit_x - x_0;
	cub->tmp.dstnc_y = cub->ray.wallhit_y - y_0;
	if (abs(cub->tmp.dstnc_x) > abs(cub->tmp.dstnc_y))
		cub->tmp.steps = abs(cub->tmp.dstnc_x);
	else
		cub->tmp.steps = abs(cub->tmp.dstnc_y);
	cub->tmp.x_inc = cub->tmp.dstnc_x / (float) cub->tmp.steps;
	cub->tmp.y_inc = cub->tmp.dstnc_y / (float) cub->tmp.steps;
	x = x_0;
	y = y_0;
	i = 0;
	while (i <= cub->tmp.steps)
	{
		my_mlx_pixel_put(cub, x, y, 0xFFFF0F);
		x += cub->tmp.x_inc;
		y += cub->tmp.y_inc;
		i++;
	}
}

void	drawrays_of_plyer_mini(t_struct *cub, int x, int y)
{
	int	i;

	i = 0;
	cub->ray.rayangle = cub->player.rottangle - (M_PI / 6);
	while (i < cub->numofrays)
	{
		cub->ray.rayangle = normalize_angle(cub->ray.rayangle);
		cast_all_rays(cub);
		cub->ray.wallhit_x = (cub->ray.wallhit_x / cub->scalewidth) * \
							cub->mini_map.mini_scalewidth;
		cub->ray.wallhit_y = (cub->ray.wallhit_y / cub->scaleheight) * \
							cub->mini_map.mini_scaleheight;
		dda(cub, x, y);
		cub->ray.rayangle += cub->angleincrem;
		i++;
	}
}

int	abs(int n)
{
	if (n > 0)
		return (n);
	else
		return (n * (-1));
}

int	check_wall(t_struct *cub, double x, double y)
{
	int	gred_y;
	int	gred_x;

	gred_y = (int)(y / cub->scaleheight);
	gred_x = (int)(x / cub->scalewidth);
	if (gred_y < cub->heightof_minimap && gred_x < cub->widthof_minimap)
	{
		if (cub->my_map[gred_y][gred_x] == '1' \
		|| cub->my_map[gred_y][gred_x] == ' ')
			return (1);
		if (cub->my_map[gred_y][gred_x] == '0' \
		|| ft_isalpha(cub->my_map[gred_y][gred_x]))
			return (0);
	}
	return (1);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle == M_PI || angle == 0)
		angle += 0.000000000001;
	return (angle);
}
