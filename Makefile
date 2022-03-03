CC = gcc

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread -g3 -fsanitize=address

SRC = dynarray2.c dynarray.c ft_parse_utils.c main.c ft_mems.c ft_time.c
SRC_D = srcs
SRC_C = $(addprefix ${SRC_D}/, ${SRC})

INC = dynarray.h ft_philo.h
INC_D = includes
INC_H = $(addprefix ${INC_D}/, ${INC})

all: $(NAME)

$(NAME): ${INC_H}
	${CC} ${CFLAGS} ${SRC_C} -I${INC_D} -o ${NAME}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

$%.o: $%.c $(INC_H)
	$(CC) $(CFLAGS) -c $< -o $@
