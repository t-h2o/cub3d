#	Compilation setting

NAME	=	cub3d

CC		=	gcc
DB		=	lldb

CFLAGS	=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFLAGS	+=	-g

OFLAGS	=	-fsanitize=address

# Find the os
UNAME_S := $(shell uname -s)

# Linux
ifeq ($(UNAME_S),Linux)
  LIBEXT	+=	libs/mlx-linux/libmlx.a
  LIBEXT	+=	libs/mlx-linux/libmlx_Linux.a
  DIR_LIB_MLX	=	libs/mlx-linux
  OFLAGS	   +=	-L$(DIR_LIB_MLX) -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
endif

# Apple
ifeq ($(UNAME_S),Darwin)
  LIBEXT	+=	libs/mlx-apple/libmlx.a
  DIR_LIB_MLX     =	libs/mlx-apple
  OFLAGS	   +=	-L$(DIR_LIB_MLX) -lmlx -framework OpenGL -framework AppKit
endif


#	Libraries

LIBEXT	+=	libs/libft/libft.a
CLIB	=	-lm

#	Headers

INCD	=	headers

INCS	=	$(INCD)/cub3d.h
INCS	+=	$(INCD)/keys.h


#	Sources

SRCD	=	srcs

SRCS	=	$(SRCD)/main.c
SRCS	+=	$(SRCD)/check_map.c
SRCS	+=	$(SRCD)/close.c
SRCS	+=	$(SRCD)/frame.c
SRCS	+=	$(SRCD)/init.c
SRCS	+=	$(SRCD)/mini_map.c
SRCS	+=	$(SRCD)/parsing.c
SRCS	+=	$(SRCD)/player.c
SRCS	+=	$(SRCD)/ray.c
SRCS	+=	$(SRCD)/rendering.c
SRCS	+=	$(SRCD)/textures.c
SRCS	+=	$(SRCD)/utils_math.c
SRCS	+=	$(SRCD)/utils_mlx.c
SRCS	+=	$(SRCD)/utils_parsing.c
SRCS	+=	$(SRCD)/utils_ray.c
SRCS	+=	$(SRCD)/utils_tx.c
SRCS	+=	$(SRCD)/window.c


#	Objets

OBJD	=	objs
OBJS	=	$(addprefix $(OBJD)/, $(notdir $(SRCS:.c=.o)))

RM		=	rm -rf

vpath %.c $(SRCD)


all : $(NAME)

$(NAME):	$(LIBEXT) $(OBJS)
	@printf "$(YELLOW)Creating executable..$(DEFAULT)\n"
	@$(CC) $(OBJS) $(OFLAGS) $(LIBEXT) $(CLIB) -o $(NAME)
	@printf "$(GREEN)---> $(NAME) is ready$(DEFAULT)\n"

$(OBJD)/%.o : %.c | $(OBJD)
	@printf "$(YELLOW)Compiling $(DEFAULT)$<\n"
	@$(CC) $(CFLAGS) -I$(INCD) -o $@ -c $<

$(OBJD) :
	@mkdir -p $(OBJD)

$(LIBEXT):
	@printf "$(YELLOW)Preparing Libft..$(DEFAULT)\n"
	@make -C libs/libft 1>/dev/null 2>/dev/null
	@printf "$(CYAN)---> Libft ready$(DEFAULT)\n"
	@printf "$(YELLOW)Preparing MiniLibX..$(DEFAULT)\n"
	@make -C $(DIR_LIB_MLX) 1>/dev/null 2>/dev/null
	@printf "$(CYAN)---> MiniLibX ready$(DEFAULT)\n"

$(LIBFT):
	@make -C libs/libft

clean:
	@$(RM) $(OBJD)
	@printf "$(RED)Removed $(CYAN)$(OBJD)$(DEFAULT)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)Removed $(CYAN)$(NAME)$(DEFAULT)\n"

libclean:
	@make fclean -C libs/libft 1>/dev/null 2>/dev/null
	@printf "$(RED)Removed $(CYAN)Libft$(DEFAULT)\n"
	@make clean -C $(DIR_LIB_MLX) 1>/dev/null 2>/dev/null
	@printf "$(RED)Removed $(CYAN)MiniLibX$(DEFAULT)\n"

fullclean: fclean libclean

re:	fclean all

norm:
	@clear
	@(norminette $(INCS) $(SRCS) | grep -v  OK\!) || true

db: all
	$(DB) $(NAME)

.PHONY: all clean fclean libclean fullclean

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
DEFAULT = \033[0m
