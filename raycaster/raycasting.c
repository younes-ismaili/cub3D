/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:26:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/13 13:29:54 by yismaili         ###   ########.fr       */
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
        //  printf("hey %f\n",cub->rays[i]);
       i++;
    }
    return (0);
}