/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_fc_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 12:26:01 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/11 12:15:55 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars_head.h"

/*
** Проверяет входную строку на валидность
** и возвращает первое число в строке.
*/

int		color_str_num(char **str)
{
	int	i;
	int	num;

	i = 0;
	(*str)++;
	while (**str == ' ')
		(*str)++;
	while ((*str)[i] != ' ' && (*str)[i] != ',' && (*str)[i])
	{
		if (ft_isdigit((*str)[i]) == 0)
			return (-1);
		i++;
	}
	if (i > 8)
		return (-1);
	num = ft_atoi(*str);
	(*str) += i;
	while (**str == ' ')
		(*str)++;
	if (**str == ',' || **str == 0)
		return (num);
	else
		return (-1);
}

/*
** Записывает числа в структуру.
*/

void	write_f_color(int r, int g, int b, t_all_info *info)
{
	info->color_f_r = r;
	info->color_f_g = g;
	info->color_f_b = b;
}

void	write_c_color(int r, int g, int b, t_all_info *info)
{
	info->color_c_r = r;
	info->color_c_g = g;
	info->color_c_b = b;
}

/*
** Проверяет полученные числа на валидность.
*/

int		check_str_color(char *str, int r, int g, int b)
{
	while (*str == ' ')
		str++;
	if (*str == 0)
		if (r != -1 && g != -1 && b != -1 && r <= 255 && g <= 255 && b <= 255)
			return (1);
	return (0);
}

/*
** Функция записывает цвета в переменные r, g, b,
** затем записывает их в структуру. Возвращает 0,
** если входные данные не верные.
*/

int		write_fc_color(char ident, char *str, t_all_info *info)
{
	int	r;
	int	g;
	int	b;

	r = color_str_num(&str);
	g = color_str_num(&str);
	b = color_str_num(&str);
	if (check_str_color(str, r, g, b))
	{
		if (ident == 'f')
		{
			write_f_color(r, g, b, info);
			return (++info->ident_f);
		}
		else if (ident == 'c')
		{
			write_c_color(r, g, b, info);
			return (++info->ident_c);
		}
	}
	return (0);
}
