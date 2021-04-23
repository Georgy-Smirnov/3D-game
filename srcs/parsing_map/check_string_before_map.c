/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string_before_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:47:31 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/11 12:14:24 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars_head.h"

/*
** Функция получает путь из строки.
*/

char	*add_path(char *str)
{
	int		i;
	char	*rez;

	i = 2;
	while (str[i] == ' ')
		i++;
	rez = ft_substr(str, i, ft_strlen(str));
	return (rez);
}

/*
** Функция получает идентификаторы и распределяет
** и записывает путь в структуру инфо.
*/

int		add_path_info(int ident, char *str, t_all_info *info)
{
	if (ident == 1)
	{
		info->path_no = add_path(str);
		return (++info->ident_no);
	}
	else if (ident == 2)
	{
		info->path_so = add_path(str);
		return (++info->ident_so);
	}
	else if (ident == 3)
	{
		info->path_we = add_path(str);
		return (++info->ident_we);
	}
	else if (ident == 4)
	{
		info->path_ea = add_path(str);
		return (++info->ident_ea);
	}
	else
	{
		info->path_s = add_path(str);
		return (++info->ident_s);
	}
}

/*
** Функция принимает строку которая следует после R.
** Записывает информацию в структуру инфо.
** Если не валидно возвращает 0.
** Функция "check_digit" описана в файле "add.c"
** Она проверяет, чтобы строка состояла только из чисел.
*/

int		add_size_r(char *str, t_all_info *info)
{
	int	i;

	str++;
	while (*str == ' ')
		str++;
	i = check_digit(str);
	if (i == 0 || i > 8)
		return (0);
	if ((info->width = ft_atoi(str)) == 0)
		return (0);
	str += i;
	while (*str == ' ')
		str++;
	i = check_digit(str);
	if (i == 0 || i > 8)
		return (0);
	if ((info->higth = ft_atoi(str)) == 0)
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] == 0)
		return (++info->ident_r);
	return (0);
}

/*
** Принимает строку и проверяет на наличие необходимых символов.
** При наличии продолжает работать с ними выше.
** При отсутствии возвращает 0.
*/

int		check_symb_elem(char *str, t_all_info *info)
{
	if (str[0] == 'R' && str[1] == ' ')
		return (add_size_r(str, info));
	else if (str[0] == 'C' && str[1] == ' ')
		return (write_fc_color('c', str, info));
	else if (str[0] == 'S' && str[1] == ' ')
		return (add_path_info(5, str, info));
	else if (str[0] == 'F' && str[1] == ' ')
		return (write_fc_color('f', str, info));
	else if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		return (add_path_info(1, str, info));
	else if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		return (add_path_info(2, str, info));
	else if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		return (add_path_info(3, str, info));
	else if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		return (add_path_info(4, str, info));
	else
		return (0);
}

/*
** Функция принимает на вход строки до карты, пропускает пробелы и отправлет
** в функцию выше. При пустых строках возвращает 1, т.к. они валидны.
** Возвращает 0, если строки не валидны.
*/

int		check_string_before_map(char *str, t_all_info *info)
{
	char	*tmp;

	tmp = str;
	while (*tmp == ' ')
		tmp++;
	if (*tmp == 0)
		return (1);
	if (check_symb_elem(tmp, info))
		return (1);
	return (0);
}
