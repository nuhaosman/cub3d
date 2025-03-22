/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosman <nosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:47:39 by myousaf           #+#    #+#             */
/*   Updated: 2024/10/05 15:30:58 by nosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_player_position(t_soul_catcher *game, t_point *player)
{
	int	x;
	int	y;

	y = -1;
	while (game->map->grid[++y])
	{
		x = -1;
		while (game->map->grid[y][++x])
		{
			if (ft_strchr("NEWS", game->map->grid[y][x]))
			{
				if (update_player(game, x, y) == 1)
					return (1);
				break ;
			}
		}
	}
	if (!player->direction)
		return (perr("No player found"));
	game->map->width = y;
	return (0);
}

short int	check_zero_surrounding(t_soul_catcher *game)
{
	int		x;
	int		y;
	char	**map;

	y = -1;
	map = game->map->grid;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '0')
				if (help_check_zero_surrounding(map, y, x) == 1)
					return (1);
	}
	return (0);
}

int	is_surrounded_by_walls(t_soul_catcher *game, t_point *player_pos)
{
	char	**visited;

	visited = ft_tabdup(game->map->grid, 1, -1, -1);
	if (!is_closed(game, visited, player_pos->spawn_x, player_pos->spawn_y))
		return (freearr(visited), perr("Player must be surrounded by walls"));
	freearr(visited);
	if (check_zero_surrounding(game))
		return (perr("Map must be surrounded by walls"));
	return (0);
}

int	is_map_valid(t_soul_catcher *game)
{
	if (!game->map->full)
		return (perr("No map found"), 1);
	game->map->grid = ft_split(game->map->full, '\n');
	if (!game->map->grid)
		return (perr("gird malloc error -- No map found"));
	if (find_player_position(game, game->player_pos))
		return (1);
	if (is_surrounded_by_walls(game, game->player_pos))
		return (1);
	return (0);
}
