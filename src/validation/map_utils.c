/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosman <nosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:47:39 by myousaf           #+#    #+#             */
/*   Updated: 2024/10/05 15:30:58 by nosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_player(t_soul_catcher *game, int x, int y)
{
	game->player_pos->spawn_y = y;
	game->player_pos->spawn_x = x;
	game->player_pos->direction = game->map->grid[y][x];
	game->map->grid[y][x] = '0';
	if (game->player_pos->spawn_y == 0)
		return (perr("Player must be surrounded by walls"), 1);
	return (0);
}

int	help_check_zero_surrounding(char **map, int y, int x)
{
	if (y == 0 || x == 0)
		return (1);
	else if (!map[y][x + 1])
		return (1);
	else if (!map[y + 1])
		return (1);
	else
	{
		if (map[y - 1][x] == ' ')
			return (1);
		if (map[y + 1][x] == ' ')
			return (1);
		if (map[y][x - 1] == ' ')
			return (1);
		if (map[y][x + 1] == ' ')
			return (1);
	}
	return (0);
}
