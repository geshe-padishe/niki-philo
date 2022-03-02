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
	t_dynarray			*darr;
	unsigned long		nb_philos;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	unsigned long		nb_meals;
}				t_table;

typedef struct s_philo
{
	unsigned long	philo_id;
	t_table			*table;
	pthread_t		thread;
	int				philo_nb;
	int				meals;
	bool			alive;
	struct timeval	start_time;
	struct timezone	time_zone;;
}				t_philo;

int	ft_atoi(char *nstr);
int	ft_atoi_sign(char **nstr);
void	*routine(void *ptr);
int	parse_args(char **argv, t_table *table);
void	print_table(t_table table);
int	create_philos(t_table *table);
void	ft_memset(void *ptr, size_t size);
int	ft_sleep(unsigned long microsec);

#endif
