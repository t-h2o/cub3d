# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 13:38:20 by gudias            #+#    #+#              #
#    Updated: 2022/04/26 21:22:54 by gudias           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
AR	= ar rcs
RM	= rm -f

INCSDIR	= includes
SRCSDIR	= srcs
OBJSDIR	= objs
SUBDIRS	= checks convert files lists maths memory print print/ft_printf strings

SRCS	= \
$(addprefix checks/, \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_isnumber.c )\
\
$(addprefix strings/, \
	ft_strlen.c \
	ft_strdup.c \
	ft_strchr.c \
	ft_strchr_nl.c \
	ft_strrchr.c \
	ft_strnstr.c \
	ft_strlcpy.c \
	ft_strncmp.c \
	ft_strlcat.c \
	ft_strjoin.c \
	ft_pathjoin.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_split.c \
	ft_strmapi.c \
	ft_striteri.c )\
\
	convert/ft_toupper.c \
	convert/ft_tolower.c \
	convert/ft_atoi.c \
	convert/ft_itoa.c \
\
$(addprefix memory/, \
	ft_free_array.c \
	ft_bzero.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memset.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_calloc.c )\
\
	files/get_next_line.c \
	files/openfile.c \
\
	print/ft_putchar.c \
	print/ft_putstr.c \
	print/ft_putendl.c \
	print/ft_putnbr.c \
	print/ft_putchar_fd.c \
	print/ft_putstr_fd.c \
	print/ft_putendl_fd.c \
	print/ft_putnbr_fd.c \
	print/ft_printf/ft_printf.c \
	print/ft_printf/get_flags.c \
	print/ft_printf/print.c \
	print/ft_printf/print_format.c \
	print/ft_printf/putters_count.c \
\
	lists/ft_lstnew.c \
	lists/ft_lstadd_front.c \
	lists/ft_lstsize.c \
	lists/ft_lstlast.c \
	lists/ft_lstadd_back.c \
	lists/ft_lstdelone.c \
	lists/ft_lstclear.c \
	lists/ft_lstiter.c \
	lists/ft_lstmap.c 

OBJS	= ${SRCS:%.c=$(OBJSDIR)/%.o}

$(OBJSDIR)/%.o: srcs/%.c 
		@echo "$(YELLOW)Compiling $(DEFAULT)$<"
		@mkdir -p $(OBJSDIR) $(addprefix $(OBJSDIR)/, $(SUBDIRS))
		@${CC} ${CFLAGS} -I $(INCSDIR) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
		@echo "$(YELLOW)Creating lib..$(DEFAULT)"
		@$(AR) ${NAME} $^
		@echo "$(GREEN)---> $@ is ready$(DEFAULT)"

clean:
		@$(RM) -r ${OBJSDIR}
		@echo "$(RED)!! Object files deleted !!$(DEFAULT)"

fclean: clean
		@$(RM) ${NAME}
		@echo "$(RED)!! $(NAME) deleted !!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
