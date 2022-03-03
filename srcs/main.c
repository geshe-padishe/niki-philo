#include "ft_philo.h"

void *routine(void *ptr)
{
	t_philo			*philo;
	long	time_ms;

	philo = ptr;
	while (!philo->dead)
	{
		ft_ms(&time_ms);
		printf("time = %ld\n", time_ms);
		printf("time diff = %ld\n", time_ms - philo->ate_time);
		printf("ate_time = %ld\n", philo->ate_time);
		if (time_ms - philo->ate_time >
			philo->table->time_to_die)
		{
			philo->dead = 1;
			return (NULL); //IS DEAD
		}
		philo->ate_time = time_ms;
		printf("Eating\n");
		ft_sleep(philo->table->time_to_eat);
		printf("Sleeping\n");
		ft_sleep(philo->table->time_to_sleep);
	}
	return (philo);
}

int	parse_args(char **argv, t_table *table)
{
	table->nb_philos = ft_atoi(argv[1]);
	if (table->nb_philos <= 0)
		return (-1);
	table->time_to_die = ft_atoi(argv[2]);
	if (table->time_to_die <= 60)
		return (-1);
	table->time_to_eat = ft_atoi(argv[3]);
	if (table->time_to_eat <= 60)
		return (-1);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->time_to_sleep <= 60)
		return (-1);
	table->nb_meals = ft_atoi(argv[5]);
	if (table->nb_meals <= 60)
		return (-1);
	return (0);
}

void print_table(t_table table)
{
	printf("nb_philos = %ld\n", table.nb_philos);
	printf("time_to_die = %ld\n", table.time_to_die);
	printf("time_to_eat = %ld\n", table.time_to_eat);
	printf("time_to_sleep = %ld\n", table.time_to_sleep);
	printf("nb_meals = %ld\n", table.nb_meals);
}

int	create_philos(t_table *table)
{
	unsigned long	i;
	t_philo			philo;

	i = 0;
	ft_memset(&philo, sizeof(t_philo));
	philo.table = table;
	while (i < table->nb_philos)
	{
		if (ft_ms(&philo.ate_time))
			return (-1);
		if (pthread_create(&philo.thread, NULL, &routine, &philo))
			return (-1);
		if (pthread_join(philo.thread, NULL) != 0)
			return (-1);
		if (push_dynarray(table->darr, &philo, 1, 0) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_table		table;
	t_dynarray	darr;

	ft_memset(&table, sizeof(t_table));
	if (argc != 6 || parse_args(argv, &table) != 0)
		return (printf("Invalid Args\n"), -1);
	if (init_dynarray(&darr, 1, sizeof(t_philo)) == -1)
		return (free_dynarray(&darr), -1);
	table.darr = &darr;
	if (create_philos(&table))
		return (free_dynarray(&darr), -1);
	//print_table(table);
	return (free_dynarray(&darr), 0);
}
