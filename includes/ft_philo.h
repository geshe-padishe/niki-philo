#ifndef FT_PHILO_H
# define FT_PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_table
{
	long	 nb_philos;
	long	 time_to_die;
	long	 time_to_eat;
	long	 time_to_sleep;
	long	 nb_meals;
}				t_table;

typedef struct s_philo
{
	pthread_t	*thread;
	int			philo_nb;
	int			last_meal_time;
	int			meals;
}				t_philo;

int	ft_atoi(char *nstr);
int	ft_atoi_sign(char **nstr);

#endif
