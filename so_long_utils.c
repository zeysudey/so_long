/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:13:01 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/23 17:13:21 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ber_check(char *folder)
{
	int	i;

	i = ft_strlen(folder);
	if (folder[i - 4] == '.' && folder[i - 3] == 'b'
		&& folder[i - 2] == 'e' && folder[i - 1] == 'r')
		return (0);
	else
		handle_error("Error\nInvalid file extension\n", NULL);
	return (1);
}

void	walls(t_game *game)
{
	int		index;
	char	**map_data;

	map_data = game->map;
	index = 0;
	while (map_data[0][index] && map_data[game->map_y - 1][index])
	{
		if (map_data[0][index] != '1'
			|| map_data[game->map_y - 1][index] != '1')
			handle_error("Error\nMap boundaries are not enclosed\n", game);
		index++;
	}
	index = 1;
	while (index < game->map_y - 1)
	{
		if (map_data[index][0] != '1'
			|| map_data[index][game->map_x - 1] != '1')
			handle_error("Error\nSide walls are not enclosed\n", game);
		index++;
	}
}

char	**clonemap(t_game *game)
{
	int		i;
	char	**clone;

	i = 0;
	clone = malloc(sizeof(char *) * (game->map_y + 1));
	if (!clone)
		handle_error("Error\nmalloc error\n", game);
	while (i < game->map_y)
	{
		clone[i] = ft_strdup(game->map[i]);
		i++;
	}
	clone[i] = NULL;
	return (clone);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*dest;

	len = 0;
	len = ft_strlen(s1);
	if (!s1)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	end_file_check(char *next, char *line, int fd)
{
	if (next == NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
		{
			close(fd);
			free(line);
			free(next);
			handle_error("Error\nThe last line mustn't newline\n", NULL);
		}
	}
}
