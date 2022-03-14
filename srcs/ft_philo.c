#include "ft_philo.h"

void *routine(void *ptr)
{
	t_philo			*philo;

	philo = ptr;
	if (philo->id % 2)
		ft_sleep(30, 0, NULL);
	while (philo->dead == 0)
	{
		if (ft_eat(philo))
			return (NULL);
		if (ft_write("is sleeping\n", philo, philo->dead))
			return (NULL);
		if (ft_sleep(philo->table->time_to_sleep, philo->dead, philo))
			return (NULL);
		if (ft_write("is thinking\n", philo, philo->dead))
			return (NULL);
		if (philo->nb_meals != 0)
		{
			pthread_mutex_lock(philo->meal_mutex);
			//printf("meals = %i, nb_meals = %i\n", philo->meals, philo->nb_meals);
			if (philo->meals == philo->nb_meals)
			{
				pthread_mutex_unlock(philo->meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(philo->meal_mutex);
		}
	}
	return (philo);
}

char	*create_philos(t_table *table, pthread_mutex_t *mutex_tab)
{
	unsigned long	i;
	t_philo			philo;
	bool			dead;

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
	while (i < table->nb_philos)
	{
		if (pthread_create(&((t_philo *)table->darr->list)[i].thread, NULL,
						&routine, &((t_philo *)table->darr->list)[i]))
			return (NULL);
		i++;
	}
	dead = 0;
	while (dead == 0)
	{
		//printf("CA BOUCLE ICI %li\n", i++);
		if (philo.nb_meals != 0)
			if (ft_philos_fed(table))
				return (0);
		pthread_mutex_lock(&mutex_tab[0]);
		dead = table->dead;
		pthread_mutex_unlock(&mutex_tab[0]);
	}
	return (0);
}

int main(int argc, char **argv)
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
	ft_destroy_mutex(&mutex_tab[0], &mutex_tab[1], &mutex_tab[2], &mutex_tab[3]);
	return (dprintf(1, "MAIN RETURN\n"), free_dynarray(&darr), 0);
}
