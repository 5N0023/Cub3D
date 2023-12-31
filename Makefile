NAME = cub3D
SOURCES =		main.c \
				load_normal.c	\
				cast_rays.c	\
				loading.c \
				startmenu.c \
				cursor.c \
				options.c \
				textures.c \
				door.c \
				collision.c \
				castrayver.c\
				castrayhor.c\
				draw_gun.c\
				minimap.c\
				init.c\
				game.c\
				hooks.c\
				pixels.c\
				moveplayer.c\
				options_sens.c\
				options_ps.c\
				render_doors.c\
				draw_walls_sides.c\
				load_wall_textures.c\
				doors_utils.c\
				doors_utils2.c\

OBJECTS = $(SOURCES:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
MLX42 = MLX42/libmlx42.a
PARSER = parsing/parser.a

all :  parser $(NAME)

parser:
	@make -s -C parsing

$(NAME):$(OBJECTS)
	gcc $(OBJECTS)  $(MLX42) $(PARSER)  -Iinclude -lglfw -L$(shell brew --prefix glfw)/lib -I$(shell brew --prefix glfw)/include -o $(NAME)

%.o: %.c 
	@$(CC) $(FLAGS)  -c $< -o $@

clean:
	make -s -C parsing clean
	rm -f $(OBJECTS)
	
fclean: clean
	make -s -C parsing fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re