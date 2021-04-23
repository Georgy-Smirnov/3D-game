SRCS		=	main.c\
				./srcs/parsing_map/add.c\
				./srcs/parsing_map/check_str_in_list.c\
				./srcs/parsing_map/check_string_before_map.c\
				./srcs/parsing_map/map_create.c\
				./srcs/parsing_map/pars_utils.c\
				./srcs/parsing_map/write_fc_color.c\
				./srcs/raycasting/calc_for_draw.c\
				./srcs/raycasting/make_screenshot.c\
				./srcs/raycasting/move_calculated.c\
				./srcs/raycasting/move_player.c\
				./srcs/raycasting/put_sprites.c\
				./srcs/raycasting/raycast_utils.c\
				./srcs/raycasting/start_raycasting.c\
				./srcs/raycasting/add.c\

OBJS		= ${SRCS:.c=.o}

NAME		=cub3D

.c.o:	
			gcc -g -Wall -Werror -Wextra -I ./srcs/parsing_map/pars_head.h -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${MAKE} -C ./srcs/libft
			${MAKE} -C ./srcs/mlx
			gcc -o ${NAME} ./srcs/libft/Libft.a ./srcs/mlx/libmlx.a ${SRCS} -framework OpenGL -framework AppKit

all:		${NAME}

norm:		
			norminette ./srcs/libft/*.c
			norminette ./srcs/parsing_map/*.c
			norminette ./srcs/raycasting/*.c
			norminette ./srcs/parsing_map/*.h
			norminette ./srcs/raycasting/*.h
			norminette ./main.c

clean:
			${MAKE} clean -C ./srcs/libft
			${MAKE} clean -C ./srcs/mlx
			rm -f ${OBJS}

fclean:		clean
			${MAKE} fclean -C ./srcs/libft
			rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re
