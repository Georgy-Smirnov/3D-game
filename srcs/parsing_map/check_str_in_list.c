/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str_in_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:00:09 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/11 13:10:30 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars_head.h"

/*
** Проверяет заполненную информацию о карте.
** Необходимо, чтобы каждый идентификатор встречался
** только один раз, а так же ничего не отсутствовало.
*/

int			check_struct_info(t_all_info *info)
{
	if (info->ident_r != 1 || info->ident_no != 1 || info->ident_so != 1)
		return (0);
	if (info->ident_we != 1 || info->ident_ea != 1 || info->ident_s != 1)
		return (0);
	if (info->ident_f != 1 || info->ident_c != 1)
		return (0);
	return (1);
}

/*
** Функция получает на вход список и возвращает структуру,
** в которой хранится вся необходимая информацтя.
** Если информация не валидна, возвращается NULL.
*/

t_all_info	*make_info(t_list **head)
{
	t_list		*tmp;
	t_all_info	*info;

	info = (t_all_info *)malloc(sizeof(t_all_info));
	if (info == NULL)
		return (error_step("Memory allocate error", *head, NULL));
	tmp = *head;
	rebut_all_info(info);
	while (tmp)
	{
		if (check_string_before_map(tmp->content, info) == 0)
			break ;
		tmp = tmp->next;
	}
	if (check_struct_info(info) == 0)
		return (error_step("invalid information", *head, info));
	if (map_create(tmp, info) == 0)
		return (error_step("invalid map", *head, info));
	free_list(*head);
	return (info);
}

/*
** Сначала проверяет, чтобы файл был .cub, функции
** check_map_name и error_step находятся в pars_utils.c.
** Читает поданый файл и записывает его в список head
** который и возвращает. Чтение происходит функцией
** get_next_line.
*/

t_list		*read_file(char *argv)
{
	t_list	*head;
	t_list	*tmp;
	char	*line;
	int		fd;

	head = NULL;
	tmp = NULL;
	if (check_map_name(argv) == 0)
		return (error_step("File name error", NULL, NULL));
	fd = open(argv, O_RDONLY);
	if (fd <= 0)
		return (error_step("File read error", NULL, NULL));
	while (get_next_line(fd, &line))
	{
		tmp = ft_lstnew(line);
		if (tmp == NULL)
			return (error_step("Memory allocate error", head, NULL));
		ft_lstadd_back(&head, tmp);
	}
	tmp = ft_lstnew(line);
	if (tmp == NULL)
		return (error_step("Memory allocate error", head, NULL));
	ft_lstadd_back(&head, tmp);
	close(fd);
	return (head);
}
