/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:53:11 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/30 21:54:38 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*get_next_line(int fd)
{
	int		i;
	int		read_line;
	char	c;
	char	*buff;

	i = 0;
	read_line = 1;
	buff = (char *)ft_calloc(sizeof(char), BUFF);
	while (read_line > 0)
	{
		read_line = read(fd, &c, 1);
		if (c == '\n')
			break ;
		buff[i] = c;
		i++;
	}
	buff[i] = '\0';
	if ((!buff[i] && !read_line) || read_line == -1)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}

int	get_height(char *map_file)
{
	int		fd;
	int		height;
	char	*get_line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error Open file\n", 1);
		return (0);
	}
	height = 0;
	get_line = get_next_line(fd);
	while (get_line)
	{
		height ++;
		free(get_line);
		get_line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int	get_width(char *map_file, int height)
{
	int		fd;
	int		width;
	char	*get_line;
	int		i;
	size_t	max;

	width = 0;
	i = 0;
	max = 0;
	fd = open (map_file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error Open file\n", 1);
		exit (0);
	}
	while (i < height)
	{
		get_line = get_next_line(fd);
		if (ft_strlen(get_line) > max)
			max = ft_strlen(get_line);
		free(get_line);
		i++;
	}
	close(fd);
	return (max);
}

int	ft_read_maps(char *map_file, t_struct *cub)
{
	int		fd;
	int		i;
	char	*get_line;

	i = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error Open file\n", 1);
		return (0);
	}
	cub->height = get_height(map_file);
	cub->width = get_width(map_file, cub->height);
	cub->map = (char **)ft_calloc(sizeof(char *), (cub->height +1));
	while (i < cub->height)
	{
		get_line = get_next_line(fd);
		cub->map[i] = ft_strdup(get_line);
		free(get_line);
		i++;
	}
	cub->map[i] = NULL;
	close(fd);
	return (1);
}
