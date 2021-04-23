/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:19:10 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/11 13:10:32 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars_head.h"

/*
** Функция вызывается в случае каких-либо ошибок.
** Печатает сообщение об ошибки и при необходимости
** освобождает память free функции описаны в фалйле add.c
*/

void	*error_step(char *message, t_list *head, t_all_info *info)
{
	printf("Error.\n%s.\n", message);
	if (head != NULL)
		free_list(head);
	if (info != NULL)
		free_struct_info(info);
	return (NULL);
}

/*
** Проверяет, чтобы имя карты оканчивалось на .cub
*/

int		check_map_name(char *name)
{
	int i;

	i = 0;
	while (name[i])
		i++;
	if (name[i - 4] == '.' && name[i - 3] == 'c')
	{
		if (name[i - 2] == 'u' && name[i - 1] == 'b')
			return (1);
	}
	return (0);
}

/*
** Получает координаты спрайтов и записывает их в структуру.
*/

void	put_ij_info(int i, int j, int *q, t_all_info *info)
{
	info->spr[*q].sp_x = i + 0.5;
	info->spr[*q].sp_y = j + 0.5;
	(*q)++;
}

/*
** Проверяет все символы в строке на валидность. Возвращает:
** -1 - Если символ не валидный.
** 1 - Если это стена или пустое место.
** 0 - Если это пол.
** 11 - Если это игрок.
*/

int		check_filling(char filling)
{
	if (filling == '1' || filling == ' ')
		return (1);
	if (filling == '0')
		return (0);
	if (filling == '2')
		return (2);
	if (filling == 'W' || filling == 'N')
		return (11);
	if (filling == 'S' || filling == 'E')
		return (11);
	return (-1);
}
