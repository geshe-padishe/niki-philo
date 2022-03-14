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

void	ft_fill_philo(t_philo *philo, int id, t_table *table, long tm_to_s)
{
	philo->table = table;
	philo->time_to_eat = tm_to_s;
	philo->id = id;
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
