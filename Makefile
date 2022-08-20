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
  DIR_LIB_MLX     =	libs/mlx-apple
  OFLAGS	   +=	-L$(DIR_LIB_MLX) -lmlx -framework OpenGL -framework AppKit
endif


#	Libraries

LIBEXT	+=	libs/libft/libft.a


#	Headers

INCD	=	./headers

INCS	=	$(INCD)/cub3d.h
INCS	+=	$(INCD)/keys.h


#	Sources

SRCD	=	./srcs

SRCS	=	$(SRCD)/main.c


#	Objets

OBJD	=	./objs
OBJS	=	$(addprefix $(OBJD)/, $(notdir $(SRCS:.c=.o)))

RM		=	rm -rf

vpath %.c $(SRCD)


all : $(NAME)

$(NAME):	$(OBJS) $(LIBEXT)
	$(CC) $(OFLAGS) $^ -o $(NAME)

$(OBJD)/%.o : %.c | $(OBJD)
	$(CC) $(CFLAGS) -I$(INCD) -o $@ -c $^

$(OBJD) :
	mkdir -p $(OBJD)

$(LIBEXT):
	@make -C libs/libft
	@make -C libs/mlx-linux

clean:
	@$(RM) $(OBJD)
	@echo Clean the objets...

fclean: clean
	@$(RM) $(NAME)
	@echo Clean the program...

libclean:
	@make fclean -C libs/libft
	@make clean -C libs/mlx-linux

fullclean: fclean libclean

re:	fclean all


norm:
	clear
	@(norminette $(INCS) $(SRCS) | grep -v  OK\!) || true

db: all
	${DB} $(NAME)
