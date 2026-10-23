NAME = philo
NAME_TSAN = philo_tsan

SRCS = ft_atoi_philo.c utils.c init.c get_time_in_ms.c clean_up_data.c \
	   philo_routine.c spawn_threads.c main.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
GDB_FLAG = -g
TSAN_FLAG = -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(GDB_FLAG) -c $< -o $@

tsan: $(OBJS)
	$(CC) $(CFLAGS) $(GDB_FLAG) $(TSAN_FLAG) $^ -o $(NAME_TSAN)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) $(NAME_TSAN)

