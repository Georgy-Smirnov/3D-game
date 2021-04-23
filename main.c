/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:27:52 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/11 15:48:06 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/parsing_map/pars_head.h"

/*
** В первой main функции выделяется память под список и структуру
** в которые будет записываться информация и файла конфигурации.
** Проверяется кол-во аргументов и вызываются функции, которые находятся
** в папке ./srcs/parsing_map/
**
** Во второй main функции проверяется необходимость в скриншоте и начинаются
** функции рейкастинга которые находятся в папке ./srcs/raycasting/.
*/

int		main_part2(int argc, char **argv, t_all_info *info)
{
	if (argc == 2)
	{
		if (start_raycasting(info, 0) == 0)
			return (0);
	}
	if (argc == 3 && check_third_argv(argv[2]))
	{
		if (start_raycasting(info, 1) == 0)
			return (0);
	}
	else
		printf("Error.\nBad third argument.\n");
	free_struct_info(info);
	return (0);
}

int		main(int argc, char **argv)
{
	t_list		*head;
	t_all_info	*info;

	if (argc != 2 && argc != 3)
	{
		printf("Error.\nWrong count argv.\n");
		return (1);
	}
	if ((head = read_file(argv[1])) == NULL)
		return (0);
	if ((info = make_info(&head)) == NULL)
		return (0);
	return (main_part2(argc, argv, info));
}
