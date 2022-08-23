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
UNAME_S	:=	$(shell uname -s)

# Linux
ifeq ($(UNAME_S),Linux)
  OFLAGS	+=	-lmlx -lXext -lX11 -lm
endif

# Apple
ifeq ($(UNAME_S),Darwin)
  OFLAGS	+=	-lmlx -framework OpenGL -framework AppKit
endif


#	Libraries

LIBEXT	+=	libs/libft/libft.a


#	Headers

INCD	=	headers

INCS	=	$(INCD)/cub3d.h
INCS	+=	$(INCD)/keys.h


#	Sources

SRCD	=	srcs

SRCS	=	$(SRCD)/main.c
SRCS	+=	$(SRCD)/window.c


#	Objets

OBJD	=	objs
OBJS	=	$(addprefix $(OBJD)/, $(notdir $(SRCS:.c=.o)))

RM		=	rm -rf

vpath %.c $(SRCD)


all : $(NAME)

$(NAME):	$(LIBEXT) $(OBJS)
	@echo "$(YELLOW)Creating executable..$(DEFAULT)"
	@$(CC) $(OBJS) $(LIBEXT) $(OFLAGS) -o $(NAME)
	@echo "$(GREEN)---> $(NAME) is ready$(DEFAULT)"

$(OBJD)/%.o : %.c | $(OBJD)
	@echo "$(YELLOW)Compiling $(DEFAULT)$<"
	@$(CC) $(CFLAGS) -I$(INCD) -o $@ -c $<

$(OBJD) :
	@mkdir -p $(OBJD)

$(LIBEXT):
	@echo "$(YELLOW)Preparing Libft..$(DEFAULT)"
	@make -C libs/libft 1>/dev/null 2>/dev/null
	@echo "$(CYAN)---> Libft ready$(DEFAULT)"
	@echo "$(YELLOW)Preparing MiniLibX..$(DEFAULT)"
	@echo "$(CYAN)---> MiniLibX ready$(DEFAULT)"

clean:
	@$(RM) $(OBJD)
	@echo "$(RED)Removed $(CYAN)$(OBJD)$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removed $(CYAN)$(NAME)$(DEFAULT)"

libclean:
	@make fclean -C libs/libft 1>/dev/null 2>/dev/null
	@echo "$(RED)Removed $(CYAN)Libft$(DEFAULT)"
	@echo "$(RED)Removed $(CYAN)MiniLibX$(DEFAULT)"

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
