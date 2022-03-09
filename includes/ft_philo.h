#ifndef FT_PHILO_H
# define FT_PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "dynarray.h"

typedef struct s_table
{
	pthread_t			main_thread;
	bool				dead;
	t_dynarray			*darr;
	unsigned long		nb_philos;
	bool				done;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nb_meals;
}				t_table;

typedef struct s_philo
{
	int	id;
	pthread_mutex_t	*wr_mutex;
	pthread_mutex_t	*rd_mutex;
	bool			fork;
	t_table			*table;
	pthread_t		thread;
	int				philo_nb;
	int				meals;
	bool			dead;
	struct timeval	ate_time;
	struct timeval	start_time;
}				t_philo;

int	ft_atoi(char *nstr);
int	ft_atoi_sign(char **nstr);
void	*routine(void *ptr);
int	parse_args(char **argv, t_table *table);
void	print_table(t_table table);
void	*create_philos(void *ptr);
void	ft_memset(void *ptr, size_t size);
int	ft_sleep(long microsec);
int	ft_ms(long *ms);
int	ft_timeget(struct timeval *time_val);
int	ft_timediff_us(struct timeval time_val, struct timeval time_val2);
void	ft_putnbr(int nbr);
int	ft_puttime(struct timeval start_time);
int	ft_strlen(char *str);
void	ft_write(char *str, t_philo philo);
int	ft_join_threads(t_table table);

#endif
