#	Compilation setting

NAME	=	cub3d

CC		=	gcc
DB		=	lldb

CFLAGS	=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFLAGS	+=	-g

OFLAGS	=	-fsanitize=address


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

$(NAME):	$(OBJS)
	$(CC) $(OFLAGS) $(OBJS) $(CLIB) -o $(NAME)

$(OBJD)/%.o : %.c | $(OBJD)
	$(CC) $(CFLAGS) -I $(INCD) -o $@ -c $^

$(OBJD) :
	mkdir -p $(OBJD)

clean:
	@echo Clean the objets...

fclean: clean
	@echo Clean the program...

re:	fclean all


norm:
	clear
	@(norminette $(INCS) $(SRCS) | grep -v  OK\!) || true

db: all
	${DB} $(NAME)
