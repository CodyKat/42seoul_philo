CC = cc
NAME = philo
CFLAGS = -g# -Wall -Wextra -Werror
THREAD_FLAGS = -lpthread
SRCS =	main.c	\
		util_1.c	\
		philos_behave.c

OBJS = ${SRCS:.c=.o}

all : ${NAME}

$(NAME) : ${OBJS}
	${CC} -o ${NAME} ${THREAD_FLAGS} ${CFLAGS} ${OBJS}

%.o:%.c
	${CC} ${CFLAGS} -o $@ -c $<

clean : 
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

.PHONY : all clean fclean bonus re

re : fclean all
