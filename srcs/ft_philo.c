#include "ft_philo.h"

void *routine(void *ptr)
{
	t_philo			*philo;
	struct timeval	time;

	(void)time;
	philo = ptr;
	dprintf(1, "STARTING THREAD %i\n", philo->id);
	while (!philo->dead)
	{
		pthread_mutex_lock(philo->mutex);
		if (ft_timeget(&time))
			return (NULL);
	//	ft_putnbr(ft_timediff_us(time, philo->ate_time));
	//	write(1, "\n", 1);
		if (ft_timediff_us(time, philo->ate_time) >=
			philo->table->time_to_die * 1000)
			philo->dead = 1;
		philo->table->dead = 1;
		philo->ate_time = time;
		ft_write("Eeating\n", *philo);
		ft_sleep(philo->table->time_to_eat);
		ft_write("Sleeping\n", *philo);
		ft_sleep(philo->table->time_to_sleep);
		ft_write("Thinking\n", *philo);
		pthread_mutex_unlock(philo->mutex);
	}
	pthread_mutex_lock(philo->mutex);
	ft_write("Died\n", *philo);
	pthread_mutex_unlock(philo->mutex);
	return (philo);
}

int	create_philos(t_table *table)
{
	unsigned long	i;
	t_philo			philo;
	pthread_mutex_t	mutex;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < table->nb_philos)
	{
		ft_memset(&philo, sizeof(t_philo));
		philo.table = table;
		philo.id = i;
		philo.mutex = &mutex;
		if (ft_timeget(&philo.ate_time))
			return (-1);
		if (ft_timeget(&philo.start_time))
			return (-1);
		if (push_dynarray(table->darr, &philo, 1, 0) == -1)
			return (-1);
		if (pthread_create(&((t_philo *)table->darr->list)[i].thread, NULL, &routine, &((t_philo *)table->darr->list)[i]))
			return (-1);
		i++;
	}
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_join(((t_philo *)table->darr->list)[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}

int main(int argc, char **argv)
{
	t_table		table;
	t_dynarray	darr;

	ft_memset(&table, sizeof(t_table));
	if (argc != 6 || parse_args(argv, &table) != 0)
		return (printf("Invalid Args\n"), -1);
	if (init_dynarray(&darr, table.nb_philos, sizeof(t_philo)) == -1)
		return (free_dynarray(&darr), -1);
	table.darr = &darr;
	if (create_philos(&table))
		return (free_dynarray(&darr), -1);
	//print_table(table);
	return (free_dynarray(&darr), 0);
}
