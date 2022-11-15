/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:26:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/15 23:47:10 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* cast all rays */

int castRays(t_struct *cub)
{
    int i;
    i = 0;
    while (i < cub->numOfRays)
    {
       cub->rays[i] = cub->rayAngle;
       cub->rayAngle += cub->fovAngle / cub->numOfRays;
       i++;
    }
    return (0);
}
void draw_player(t_struct *cub, int x, int y, int color)
{
    int 	x_1;
	int 	y_1;
	x_1 = x + cos(cub->player.rottAngle) * 42;
    y_1 = y + sin(cub->player.rottAngle) * 42;
    ddaForLine(cub, x, y, x_1, y_1, color);  
}

void drawRaysOfplyer(t_struct *cub, int x, int y, int color)
{
    int 	x_1;
	int 	y_1;
    int i = 0;
    
    castRays(cub);
    while (cub->rays[i])
    {
            x_1 = x + cos(cub->rays[i]) * 100;
            y_1 = y + sin(cub->rays[i]) * 100;
            ddaForLine(cub, x, y, x_1, y_1, color);  
            i++;
    } 
}

// Function for finding absolute value
int abs(int n) 
{ 
    if (n > 0){
        return (n);
    }
    else {
        return (n *(-1));
    }
}
// DDA Function for line generation
void ddaForLine(t_struct *cub,int x_0, int y_0, int x_1, int y_1, int color)
{
    // calculate dstnc_x & dstnc_y
    int dstnc_x = x_1 - x_0;
    int dstnc_y = y_1 - y_0;
 
    // calculate steps required for generating pixels
    int steps;
    if (abs(dstnc_x) > abs(dstnc_y))
        steps = abs(dstnc_x);
    else
        steps = abs(dstnc_y);
    // calculate increment in x & y for each steps
    float x_inc = dstnc_x / (float)steps;
    float y_inc = dstnc_y / (float)steps;
    // Put pixel for each step
    float x = x_0;
    float y = y_0;
    int i = 0;
    while (i <= steps)
    {
       my_mlx_pixel_put(cub, x, y, color);
       x += x_inc; // increment in x at each step
       y += y_inc; // increment in y at each step
       i++;
    }
}
 
 int check_wall(t_struct *cub, double x, double y)
 {
    char **map;

    map = ft_jump_lines(cub);
    int gred_y = floor(y/cub->scaleHeight); /*The value to round down to the nearest integer*/
    int gred_x = floor(x/cub->scaleWidth);
    if (map[gred_y][gred_x] == '1')
        return (1);
    return (0);
 }

 double normalizeAngle(double angle)
 {
    angle = (int)angle % (int)(2 * M_PI);
    if (angle < 0) 
        angle = (2 * M_PI);
    return (angle);
 }
 
 void castRays(t_struct *cub)
 { 
    int  foundHorzWallHit = 0;
    int  horzWallHitX = 0;
    int  horzWallHitY = 0;

    double y_hrzntlIntrsctn =  floor(cub->player.position_y / cub->scaleHeight) * cub->scaleHeight;
    if (y_hrzntlIntrsctn == cub->ray.rayFacingDown)
    {
        y_hrzntlIntrsctn += cub->ray.rayFacingDown;
    }
    else if (y_hrzntlIntrsctn == cub->scaleHeight)
    {
         y_hrzntlIntrsctn += 0;
    }
     double x_hrzntlIntrsctn = cub->player.position_x + (y_hrzntlIntrsctn - cub->player.position_y) / tan(cub->ray.rayAngle);
     double y_incrmnt = cub->scaleHeight;
     if (y_incrmnt == cub->ray.rayFacingUp)
     {
        y_incrmnt *= -1;
     }
     else {
        y_incrmnt *= 1;
     }
     double x_incrmnt = cub->scaleWidth / tan(cub->ray.rayAngle);
      if (x_incrmnt == cub->ray.rayFacingLeft && x_incrmnt > 0)
        {
            x_incrmnt *= -1;
        }
     else {
        x_incrmnt *= 1;
     }
      if (x_incrmnt == cub->ray.rayFacingRight && x_incrmnt < 0)
        {
            x_incrmnt *= -1;
        }
     else {
        x_incrmnt *= 1;
     }
     double x_nextHrzntal = x_incrmnt;
     double y_nextHrzntal = y_incrmnt;
     if (cub->ray.rayFacingUp)
        y_nextHrzntal--;
    
    }