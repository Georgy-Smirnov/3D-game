/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:50:55 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/11 12:12:51 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars_head.h"

/*
** Проверяет, чтобы вокруг входящего символа
** был хоть какой-нибудь символ.
** Если не будет символа (будет пробел), то возвращает 0.
*/

int	check_around(int i, int j, char **map)
{
	if (i == 0 || map[i + 1] == NULL)
		return (0);
	if (j == 0 || j == ft_strlen(map[i]) - 1)
		return (0);
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		return (0);
	if (ft_strlen(map[i - 1]) <= j || ft_strlen(map[i + 1]) <= j)
		return (0);
	if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
		return (0);
	return (1);
}

/*
** Функция пропускает все пробелы и еденицы.
** А 0, 2, и игрока проверяет на валидность. Записывает координаты
** всех спрайтов в структуру. Функция put_ij_info находится в утилитах.
*/

int	check_map_valid(char **map, t_all_info *info)
{
	int	i;
	int	j;
	int q;

	i = 0;
	j = 0;
	q = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_filling(map[i][j]) == 2)
				put_ij_info(i, j, &q, info);
			if (check_filling(map[i][j]) == 1)
				j++;
			else if (check_around(i, j, map))
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

/*
** Проверяет валидность символов на карте.
** Подсчитывает кол-во игроков в строке. Записывает координаты
** игрока и считает кол-во спрайтов. Функция check_filling в утилитах.
*/

int	check_sym(char *str, int j, t_all_info *info, int f)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (check_filling(str[i]) == -1)
			return (-1);
		if (check_filling(str[i]) == 11)
		{
			count++;
			info->player_see = str[i];
			str[i] = '0';
			info->player_x = (double)(j + 0.5);
			info->player_y = (double)(i + 0.5);
		}
		if (check_filling(str[i]) == 2 && f == 1)
			info->num_spr++;
		i++;
	}
	return (count);
}

/*
** Выделяет память под двумерный массив, записывает
** в него строки из списка, проверяя на валидность.
** count проверяет, чтобы был один игрок на карте.
*/

int	second_map_create(t_list *tmp, t_all_info *info, char **map, int count)
{
	info->spr = (t_sprite *)malloc(sizeof(t_sprite) * info->num_spr);
	if (info->spr == NULL)
		return (0);
	if (tmp != NULL)
		return (0);
	if (count != 1)
		return (0);
	info->finish_map = map;
	return (check_map_valid(map, info));
}

int	map_create(t_list *tmp, t_all_info *info)
{
	int		i;
	char	**map;
	int		count;

	i = 0;
	count = 0;
	map = (char **)malloc(sizeof(char *) * (ft_lstsize(tmp) + 1));
	if (map == NULL)
		return (0);
	while (tmp)
	{
		count += check_sym(tmp->content, i, info, 1);
		if (check_sym(tmp->content, i, info, 0) == -1)
			return (0);
		if (((char *)tmp->content)[0] == 0 && tmp->next != NULL)
			break ;
		map[i] = ft_strdup(tmp->content);
		if (map[i] == NULL)
			return (0);
		tmp = tmp->next;
		i++;
	}
	map[i] = NULL;
	return (second_map_create(tmp, info, map, count));
}
