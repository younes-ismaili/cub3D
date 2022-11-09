/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/09 21:49:25 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void print(char **str)
{
     int i = 0;
    while (str[i])
    {
        printf("|%s|\n",str[i]);
        i++;
    }
}

int main(int ac, char **av)
{
    t_struct cub;

    if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
	ft_read_maps(av[1], &cub);
    ft_check_alltextures(&cub);
    ft_check_rgb(&cub);
    ft_check_map(&cub);
    cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, W_WIDTH, W_HEIGHT, "cub3D");
    cub.img = mlx_new_image(cub.mlx_ptr, W_WIDTH, W_HEIGHT);
	cub.addr = mlx_get_data_addr(cub.img, &cub.bits_per_pixel, &cub.line_length, &cub.endian);
    player_position(&cub);
    directionOfPlayer(&cub);
   // printf("%f\n", cub.player.rottAngle);
    ft_draw_map(&cub);
    mlx_key_hook(cub.win_ptr, player_move, &cub);
    mlx_loop(cub.mlx_ptr);
    // print(ft_jump_lines(&cub));
    // printf("F --> %d ",cub.flr.r);
    // printf("%d ",cub.flr.g);
    // printf("%d \n",cub.flr.b);
    // printf("C --> %d ",cub.clg.r);
    // printf("%d ",cub.clg.g);
    // printf("%d \n",cub.clg.b);
    // printf("NO --->%s\n",cub.drct.north_path);
    // printf("SO --->%s\n",cub.drct.south_path);
    // printf("WE --->%s\n",cub.drct.west_path);
    // printf("EA --->%s\n",cub.drct.east_path);
}