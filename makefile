NAME	:= philo
CC 		:= cc
CFLAGS	:= -Werror -Wextra -Wall -g3 -pthread
HEADERS	:= -I ./include
SRCS	:= src/philo.c \
			src/actions.c \
			src/aff.c \
			src/init.c \
			src/little_things.c \
			src/verif_mutexes.c \
			src/verif.c \
			
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

 %.o: %.c
	 @$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libmlx