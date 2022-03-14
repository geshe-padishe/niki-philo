#include "ft_philo.h"

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_join_threads(t_table *table)
{
	long unsigned i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_join(((t_philo *)table->darr->list)[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	ft_fill_philo(t_philo *philo, t_table *table, pthread_mutex_t *mutex_tab)
{
	philo->table = table;
	philo->time_to_eat = table->time_to_eat;
	philo->time_to_sleep = table->time_to_sleep;
	philo->nb_meals = table->nb_meals;
	ft_mutex_philo(philo, &mutex_tab[0], &mutex_tab[1], &mutex_tab[2]);
	ft_timeget(&philo->start_time);
	philo->ate_time = philo->start_time;
}

bool	ft_philos_fed(t_table *table)
{
	unsigned long	i;
	t_philo			*philo;

	philo = table->darr->list;
	i = 0;
	while (i < table->darr->nb_cells)
	{
		pthread_mutex_lock(philo->meal_mutex);
		if (philo[i].nb_meals != philo[i].meals)
		{
			pthread_mutex_unlock(philo->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(philo->meal_mutex);
		i++;
	}
	return (1);
}
