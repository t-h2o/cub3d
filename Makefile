#	Compilation setting

NAME	=	cub3d

CC		=	gcc
DB		=	lldb

CFLAGS	=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFLAGS	+=	-g

OFLAGS	=	-fsanitize=address

#	Libraries

LIBFT	=	libs/libft/libft.a


#	Headers

INCD	=	./headers

INCS	=	$(INCD)/cub3d.h


#	Sources

SRCD	=	./srcs

SRCS	=	$(SRCD)/main.c


#	Objets

OBJD	=	./objs
OBJS	=	$(addprefix $(OBJD)/, $(notdir $(SRCS:.c=.o)))

RM		=	rm -rf

vpath %.c $(SRCD)


all : $(NAME)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(OFLAGS) $^ -o $(NAME)

$(OBJD)/%.o : %.c | $(OBJD)
	$(CC) $(CFLAGS) -I $(INCD) -o $@ -c $^

$(OBJD) :
	mkdir -p $(OBJD)

$(LIBFT):
	@make -C libs/libft

clean:
	@$(RM) $(OBJD)
	@echo Clean the objets...

fclean: clean
	@$(RM) $(NAME)
	@echo Clean the program...

libclean:
	@make fclean -C libs/libft

fullclean: fclean libclean

re:	fclean all


norm:
	clear
	@(norminette $(INCS) $(SRCS) | grep -v  OK\!) || true

db: all
	${DB} $(NAME)
