##	START_MAKEFILE	##

#===============================>COLORS<===============================#

_RED		=	\e[31m
_YELLOW		=	\e[33m
_GREEN		=	\e[32m
_END		=	\e[0m

# ===================================================================== #

#===============================>FILES<===============================#

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

# ===================================================================== #

#============================>COMPILATIONS<============================#

GCC			= gcc

CFLAGS		= -Wall -Werror -Wextra

FRAMES		= -framework OpenGL -framework AppKit

#===============================>DELETE<===============================#

RM			= rm -f

OBJS		= ${SRCS:.c=.o}

#============================>HEAD_LIB_PATH<============================#

DIR_HEAD	= ./includes

DIR_LIB		= ./library

#============================>LIB_FILE<============================#

LIBFT		= -lft

LIBMLX		= -lmlx

#============================>LIB_FILE<============================#

MAP			= map.cub

#==========================>COMPILING_SOURCE<==========================#

OBJS		=	${SRCS:%.c=%.o}

NAME		= cub3D

#==========================>COMPILING_RULES<==========================#

all:		${NAME}

${NAME}:	${OBJS}
			@${GCC} -o ${NAME} ${OBJS} -L${DIR_LIB} ${LIBFT} ${LIBMLX} ${FRAMES}
			@printf "\033[2K\r${_GREEN} Game install: '${NAME}'. ${_END}✅\n"


%.o:		%.c
			@${GCC} ${CFLAGS} -I ${DIR_HEAD} -c $< -o $@
			@printf "\033[2K\r${_YELLOW} Compilling $< ⌛${_END}\n"

start:		${NAME}
			@./${NAME} ${MAP}

#==========================>NORM_RULES<===========================#

norm:		
			norminette ./srcs/parsing_map/*.c
			norminette ./srcs/raycasting/*.c
			norminette ./main.c

#==========================>CLEAN_RULES<==========================#

clean:
			@${RM} ${OBJS}
			@printf "\033[2K\r${_RED} '".o"' has been deleted. ${_END}🗑️\n"

fclean:		clean
			@${RM} ${NAME}
			@printf "\033[2K\r${_RED} '"${NAME}"' has been deleted. ${_END}🗑️\n"

re:			fclean all

.PHONY: all clean fclean re
