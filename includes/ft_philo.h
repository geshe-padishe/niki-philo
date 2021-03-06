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
	bool				printed_death;
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
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	fork;
	pthread_mutex_t	*forks_mutex;
	t_table			*table;
	pthread_t		thread;
	int				meals;
	int				nb_meals;
	long			time_to_eat;
	long			time_to_sleep;
	bool			dead;
	struct timeval	ate_time;
	struct timeval	start_time;
}				t_philo;

int	ft_atoi(char *nstr);
int	ft_atoi_sign(char **nstr);
void	*routine(void *ptr);
int	parse_args(int argc, char **argv, t_table *table);
void	print_table(t_table table);
void	ft_memset(void *ptr, size_t size);
int	ft_sleep(long millisec, bool dead, t_philo *philo);
int	ft_ms(long *ms);
int	ft_timeget(struct timeval *time_val);
int	ft_timediff_us(struct timeval time_val, struct timeval time_val2);
int	ft_strlen(char *str);
bool	ft_write(char *str, t_philo *philo, bool death);
int	ft_join_threads(t_table *table);
void	ft_mutex_philo(t_philo *philo, pthread_mutex_t *wr_mutex,
		pthread_mutex_t *rd_mutex, pthread_mutex_t *sleep_mutex);
void	ft_init_mutex(pthread_mutex_t *wr_mutex, pthread_mutex_t *rd_mutex,
					pthread_mutex_t *sleep_mutex, pthread_mutex_t *forks_mutex);
void	ft_destroy_mutex(pthread_mutex_t *wr_mutex, pthread_mutex_t *rd_mutex,
						pthread_mutex_t *sleep_mutex,
						pthread_mutex_t *forks_mutex);
bool	ft_eat(t_philo *philo, int first_time);
int	ft_fork_index(int	id, int nb_cells);
char	*create_philos(t_table *table, pthread_mutex_t *mutex_tab);
void	ft_fill_philo(t_philo *philo, t_table *table,
					pthread_mutex_t *mutex_tab);
int	ft_philo_death(t_philo *philo);
bool	ft_fork_and_eat(t_philo *philo, pthread_mutex_t *l_mtx,
		pthread_mutex_t	*r_mtx, int first_time);
bool	ft_put_fork_eat(t_philo *philo);
void	ft_put_death(t_philo *philo);
bool	ft_philos_fed(t_table *table);

#endif
