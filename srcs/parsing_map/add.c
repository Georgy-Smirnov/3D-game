/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:51:18 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/11 13:10:27 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars_head.h"

/*
** Функция проверяет, чтобы строка состояла только
** из чисел.
*/

int		check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (i);
}

/*
** Функция обнуляет все переменные в структуре инфо.
*/

void	rebut_all_info(t_all_info *info)
{
	info->ident_r = 0;
	info->width = 0;
	info->higth = 0;
	info->ident_no = 0;
	info->path_no = NULL;
	info->ident_so = 0;
	info->path_so = NULL;
	info->ident_we = 0;
	info->path_we = NULL;
	info->ident_ea = 0;
	info->path_ea = NULL;
	info->ident_s = 0;
	info->path_s = NULL;
	info->ident_f = 0;
	info->color_f_r = 0;
	info->color_f_g = 0;
	info->color_f_b = 0;
	info->ident_c = 0;
	info->color_c_r = 0;
	info->color_c_g = 0;
	info->color_c_b = 0;
	info->num_spr = 0;
	info->spr = 0;
	info->finish_map = NULL;
}

/*
** Функция освобождает всю память, которая была
** выделена под список.
*/

void	free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head;
		free(head->content);
		head = head->next;
		free(tmp);
	}
}

/*
** Функция освобождает память, которая была
** выделена под двумерный массив карты.
*/

void	free_finish_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/*
** Функция освобождает все память, которая была
** выделена под структуру инфо
*/

void	free_struct_info(t_all_info *info)
{
	if (info != NULL)
	{
		if (info->path_no != NULL)
			free(info->path_no);
		if (info->path_so != NULL)
			free(info->path_so);
		if (info->path_we != NULL)
			free(info->path_we);
		if (info->path_ea != NULL)
			free(info->path_ea);
		if (info->path_s != NULL)
			free(info->path_s);
		if (info->spr != NULL)
			free(info->spr);
		if (info->finish_map != NULL)
			free_finish_map(info->finish_map);
		free(info);
	}
}
