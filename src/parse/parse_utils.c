/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosman <nosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:01:44 by myousaf           #+#    #+#             */
/*   Updated: 2024/10/05 15:30:58 by nosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_signature_check(int case_n, const char *t_file)
{
	int		fd;
	ssize_t	offset;

	offset = 0;
	while (t_file[offset] != '\0')
		offset++;
	if ((MAP == case_n && strcmp_sst(t_file, ".cub", offset - 4))
		|| (TEXTURE == case_n && strcmp_sst(t_file, ".xpm", offset - 4)))
		return (perr("Cub3d: unknown suffix '%s'", t_file));
	fd = open(t_file, O_RDONLY);
	if (fd == -1)
		return (perr("Cub3d: %s '%s'", FOPEN, t_file));
	close(fd);
	return (0);
}

int	is_set(t_soul_catcher *game, char **attribute_arr)
{
	if (ft_strncmp(attribute_arr[0], "NO", 2) == 0)
	{
		if (game->textures->north)
			return (perr("Duplicate north texture detected."));
	}
	else if (ft_strncmp(attribute_arr[0], "SO", 2) == 0)
	{
		if (game->textures->south)
			return (perr("Duplicate south texture detected."));
	}
	else if (ft_strncmp(attribute_arr[0], "WE", 2) == 0)
	{
		if (game->textures->west)
			return (perr("Duplicate west texture detected."));
	}
	else if (ft_strncmp(attribute_arr[0], "EA", 2) == 0)
	{
		if (game->textures->east)
			return (perr("Duplicate east texture detected."));
	}
	return (0);
}

int	check_invalid_char(char *map_line)
{
	static int	player_found;
	int			i;

	i = 0;
	while (map_line[i])
	{
		if (map_line[i] == 'N' || map_line[i] == 'S' || map_line[i] == 'E'
			|| map_line[i] == 'W')
		{
			if (player_found == 0)
				player_found = 1;
			else
				return (perr("Duplicate player found!"));
		}
		if (map_line[i] != '1' && map_line[i] != '0' && map_line[i] != ' '
			&& map_line[i] != 'N' && map_line[i] != 'S'
			&& map_line[i] != 'E' && map_line[i] != 'W')
			return (1);
		i++;
	}
	return (0);
}

int	update_map(t_soul_catcher *game, char *line)
{
	char	*temp;

	if (!game->map->full)
		game->map->full = ft_strdup("");
	temp = game->map->full;
	game->map->full = ft_strjoin(game->map->full, line);
	return (free(temp), 0);
}
