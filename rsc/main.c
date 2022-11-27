/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/27 14:41:33 by yismaili         ###   ########.fr       */
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
void hooking(t_struct *cub)
{
    mlx_hook(cub->win_ptr, 02, 0, KeyPress ,cub);
    mlx_hook(cub->win_ptr, 03, 0, KeyRelease, cub);
    mlx_loop_hook(cub->mlx_ptr, player_move, cub);
    mlx_hook(cub->win_ptr, 04, (1L<<6), ButtonPress ,cub);
    mlx_hook(cub->win_ptr, 05, (1L<<6), ButtonRelease, cub);
    mlx_hook(cub->win_ptr, 06, (1L<<8), MotionNotify, cub);
    mlx_loop(cub->mlx_ptr);
}

int ButtonPress(int button, int x, int y, t_struct *cub)
{
float angle;
if (button)
{
    printf("hey\n");
}
    if (x > 0 && x < W_WIDTH && y > 0 && y < W_HEIGHT)
    {
        angle = (y - cub->player.position_y)/ (x - cub->player.position_x);
         printf("in button press%f   -----\n", angle);
         cub->player.rottAngle += angle;
    }
    return (0);
}

int ButtonRelease(int button, int x, int y, t_struct *cub)
{(void)cub;
   
        printf("hey i` am in relese\n");
    y = 0;
    x = 0;
    button = 0;
    return (0);
}

int MotionNotify(int x, int y, t_struct *cub)
{(void)cub;
    if (x > 0 && x < W_WIDTH && y > 0 && y < W_HEIGHT)
    {
        printf("in moves of mouse%d   -----   %d\n", x, y);
    }
    return (0);
}
int typeofmap(char *path, char *type, int len)
{
    int i = 0;
   while (path[i])
   {
        if(path[i] == '.')
        {
            break;
        }
        i++;
   }
   if (ft_strncmp(path + i, type, len))
        return (-2);
    return (0);
}
int main(int ac, char **av)
{
    t_struct cub;
    int i;
    cub.scaleHeight = 64;
    cub.scaleWidth = 64;
    cub.texture_height = 64;
    cub.texture_width = 64;
    
    if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
    if (typeofmap(av[1], ".cub", 4) == -2)
        return (ft_putstr_fd("type of map incorrect\n", 0), 0);
	if (ft_read_maps(av[1], &cub) == 0)
        return (0);
    ft_jump_lines(&cub);
    if (!ft_check_alltextures(&cub))
        return (0);
   if (!ft_check_rgb(&cub))
        return (0);
    if (!ft_check_map(&cub))
        return (0);
    cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, W_WIDTH, W_HEIGHT, "cub3D");
    cub.color_buffer = (unsigned int **) ft_calloc(sizeof(unsigned int *), W_HEIGHT);
	i = -1;
	while (++i < W_HEIGHT)
		cub.color_buffer[i] = (unsigned int *)ft_calloc(sizeof(unsigned int), W_WIDTH);
	ft_colorBuffer(&cub);
    cub.wallTexture = (unsigned int *) ft_calloc (sizeof(unsigned int), (unsigned int)cub.scaleWidth * (unsigned int)cub.scaleHeight);
    for(int x=0; x < cub.scaleWidth; x++)
    {
        for(int y = 0; y < cub.scaleHeight;y++)
        {
            //put the value black or blue based on x and y being a multiple
            if(x % 8  && y % 8 )
            {
                cub.wallTexture[(cub.scaleWidth * y) + x] = 0xadd8e6;
            }
            else{
                cub.wallTexture[(cub.scaleWidth * y) + x] = 0xFFF0000;
            }
        }
    }
    cub.img = mlx_new_image(cub.mlx_ptr, W_WIDTH, W_HEIGHT);
	cub.addr = (int *)mlx_get_data_addr(cub.img, &cub.bits_per_pixel, &cub.line_length, &cub.endian);
    player_position(&cub);
    directionOfPlayer(&cub);
    cub.widthofmap = cub.scaleWidth * cub.widthof_minimap;
    cub.heightofmap = cub.scaleHeight * cub.heightof_minimap;
    loading_map(&cub);
    ft_draw_map(&cub);
    hooking(&cub);
    return (0);
}

void	loading_map(t_struct *cub)
{
    // if (cub->ray.rayFacingDown){
    //     cub->img2 = mlx_xpm_file_to_image(cub->mlx_ptr, cub->drct.north_path,&cub->texture_width, &cub->texture_height); 
    // }
    // if (cub->ray.rayFacingLeft){
    //     cub->img2 = mlx_xpm_file_to_image(cub->mlx_ptr, cub->drct.south_path,&cub->texture_width, &cub->texture_height);
    // }
    // if (cub->ray.rayFacingRight){
    //     cub->img2 = mlx_xpm_file_to_image(cub->mlx_ptr, cub->drct.west_path,&cub->texture_width, &cub->texture_height);
    // }
    // if (cub->ray.rayFacingUp){
    //     cub->img2 = mlx_xpm_file_to_image(cub->mlx_ptr, cub->drct.east_path,&cub->texture_width, &cub->texture_height);
    // }
      cub->img2 = mlx_xpm_file_to_image(cub->mlx_ptr, cub->drct.north_path,&cub->texture_width, &cub->texture_height);
	if (!cub->img2)
		return ;
	cub->data = (int *)mlx_get_data_addr(cub->img2, &cub->bits_per_pixel2, &cub->size_line, &cub->endian2);
	if (!cub->data || cub->texture_width != cub->texture_height)
		return ;
}