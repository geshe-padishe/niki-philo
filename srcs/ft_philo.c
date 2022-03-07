#include "ft_philo.h"

void *routine(void *ptr)
{
	t_philo			*philo;
	struct timeval	time;

	(void)time;
	philo = ptr;
	ft_putnbr(philo->id);
	while (!philo->dead)
	{
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
	}
	ft_write("Died", *philo);
	return (philo);
}

int	create_philos(t_table *table)
{
	unsigned long	i;
	t_philo			philo;

	i = 0;
	while (i < table->nb_philos)
	{
		ft_memset(&philo, sizeof(t_philo));
		philo.table = table;
		philo.id = i;
		if (ft_timeget(&philo.ate_time))
			return (-1);
		if (ft_timeget(&philo.start_time))
			return (-1);
		if (push_dynarray(table->darr, &philo, 1, 0) == -1)
			return (-1);
		if (pthread_create(&philo.thread, NULL, &routine, &((t_philo *)table->darr->list)[i]))
			return (-1);
		i++;
	}
//	i = 0;
//	while (i < table->nb_philos)
//	{
//		if (pthread_join(philo.thread, NULL) != 0)
//			return (-1);
//		i++;
//	}
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
