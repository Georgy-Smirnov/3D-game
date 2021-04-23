/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:51:53 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/21 18:51:58 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rcast.h"

/*
** Функция проверяет, чтобы 3 аргумент был "--save"
*/

int		check_third_argv(char *str)
{
	int		i;
	char	*save;

	save = "--save";
	i = 0;
	while (str[i] == save[i])
		i++;
	if (i - 1 == ft_strlen(save) && i - 1 == ft_strlen(str))
		return (1);
	else
		return (0);
}

/*
** Функция создает хеддер файла .bmp и заполняет его.
*/

void	*create_file(int size, t_all_info *info, t_data *d)
{
	unsigned char *str;

	if ((str = (unsigned char *)malloc(sizeof(unsigned char) * 54)) == NULL)
		return (error_step("Can't allocate memory", NULL, info));
	str = ft_bzero(str, 54);
	str[0] = 0x42;
	str[1] = 0x4D;
	str[2] = (size << 24) >> 24;
	str[3] = (size << 16) >> 24;
	str[4] = (size << 8) >> 24;
	str[5] = size >> 24;
	str[10] = 0x36;
	str[14] = 0x28;
	str[18] = (d->win.width << 24) >> 24;
	str[19] = (d->win.width << 16) >> 24;
	str[20] = (d->win.width << 8) >> 24;
	str[21] = d->win.width >> 24;
	str[22] = (d->win.hight << 24) >> 24;
	str[23] = (d->win.hight << 16) >> 24;
	str[24] = (d->win.hight << 8) >> 24;
	str[25] = d->win.hight >> 24;
	str[26] = 0x01;
	str[28] = (d->win.bits_per_pixel << 8) >> 8;
	str[29] = d->win.bits_per_pixel >> 8;
	return (str);
}

/*
** Функция записывает полученный хеддер в файл.
** Потом записывает информацию о цветах пикселей.
*/

void	put_img_in_file(char *str, t_data *d, int fd)
{
	int i;

	i = d->win.hight - 1;
	write(fd, str, 54);
	free(str);
	while (i >= 0)
	{
		write(fd, d->win.addr + i * d->win.line_length, d->win.line_length -
		(d->win.line_length - d->win.width * 4));
		i--;
	}
	close(fd);
}

/*
** Функция создает файл .bmp и расчитывает необходимый размер.
** Затем запускает функции, которые заполняют файл.
*/

void	*make_screenshot(t_data *d, t_all_info *info)
{
	int		fd;
	int		size;
	char	*str;

	fd = open("screensot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IREAD);
	if (fd == -1)
		return (error_step("Can't create scrinshot file", NULL, info));
	size = 54 + 4 * (d->win.hight * d->win.width);
	str = create_file(size, info, d);
	if (str == NULL)
		return (NULL);
	my_clear_window(d);
	put_d(d);
	put_img_in_file(str, d, fd);
	my_destroy(d);
	return (d);
}
