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
	t_dynarray	*darr;
	long		nb_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nb_meals;
}				t_table;

typedef struct s_philo
{
	pthread_t	thread;
	int			philo_nb;
	int			last_meal_time;
	int			meals;
	bool		alive;
	struct timeval		start_time;
	struct timezone		time_zone;;
}				t_philo;

int	ft_atoi(char *nstr);
int	ft_atoi_sign(char **nstr);
void	*routine(void *ptr);
int	parse_args(char **argv, t_table *table);
void	print_table(t_table table);
int	create_philos(t_table *table);
void	ft_memset(void *ptr, size_t size);

#endif
