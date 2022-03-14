#include "ft_philo.h"

bool	routine_meals(t_philo *philo)
{
	if (philo->nb_meals != 0)
	{
		pthread_mutex_lock(philo->meal_mutex);
		if (philo->meals == philo->nb_meals)
		{
			pthread_mutex_unlock(philo->meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(philo->meal_mutex);
	}
	return (0);
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	int				first_time;

	philo = ptr;
	first_time = 1;
	pthread_mutex_lock(philo->forks_mutex);
	pthread_mutex_unlock(philo->forks_mutex);
	if (philo->id % 2)
		ft_sleep(30, 0, NULL);
	while (philo->dead == 0)
	{
		if (ft_eat(philo, first_time))
			return (NULL);
		first_time = 0;
		if (ft_write("is sleeping\n", philo, philo->dead))
			return (NULL);
		if (ft_sleep(philo->table->time_to_sleep, philo->dead, philo))
			return (NULL);
		if (ft_write("is thinking\n", philo, philo->dead))
			return (NULL);
		if (routine_meals(philo))
			return (NULL);
//		if (philo->nb_meals != 0)
//		{
//			pthread_mutex_lock(philo->meal_mutex);
//			if (philo->meals == philo->nb_meals)
//			{
//				pthread_mutex_unlock(philo->meal_mutex);
//				return (NULL);
//			}
//			pthread_mutex_unlock(philo->meal_mutex);
//		}
	}
	return (philo);
}

char	*create_philos(t_table *table, pthread_mutex_t *mutex_tab)
{
	unsigned long	i;
	t_philo			philo;

	i = 0;
	ft_memset(&philo, sizeof(t_philo));
	ft_init_mutex(&mutex_tab[0], &mutex_tab[1], &mutex_tab[2], &mutex_tab[3]);
	ft_fill_philo(&philo, table, mutex_tab);
	while (i < table->nb_philos)
	{
		philo.id = i;
		if (push_dynarray(table->darr, &philo, 1, 0) == -1)
			return (NULL);
		pthread_mutex_init(&((t_philo *)table->darr->list)[i].fork, NULL);
		i++;
	}
	i = 0;
	pthread_mutex_lock(&mutex_tab[3]);
	while (i < table->nb_philos)
	{
		if (pthread_create(&((t_philo *)table->darr->list)[i].thread, NULL,
			&routine, &((t_philo *)table->darr->list)[i]))
			return (NULL);
		i++;
	}
	pthread_mutex_unlock(&mutex_tab[3]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table			table;
	t_dynarray		darr;
	pthread_mutex_t	mutex_tab[4];

	ft_memset(&table, sizeof(t_table));
	if ((argc != 6 && argc != 5) || parse_args(argc, argv, &table) != 0)
		return (printf("Invalid Args\n"), -1);
	if (init_dynarray(&darr, table.nb_philos, sizeof(t_philo)) == -1)
		return (free_dynarray(&darr), -1);
	table.darr = &darr;
	create_philos(&table, (pthread_mutex_t *)&mutex_tab);
	if (ft_join_threads(&table))
		return (-1);
	ft_destroy_mutex(&mutex_tab[0], &mutex_tab[1],
		&mutex_tab[2], &mutex_tab[3]);
	return (free_dynarray(&darr), 0);
}
