#include "ft_philo.h"

void *routine(t_philo *philo)
{

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

int	create_philo(int nb_philo)
{
	int		i;
	t_philo	philo;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(philo, NULL, &routine, t_table);
	}
}

int main(int argc, char **argv)
{
	t_table		table;
	t_dynarray	darr;
	t_philo		philo

	if (argc != 6 || parse_args(argv, &table) != 0)
		return (-1);
	init_dynarray(&darr, 1, sizeof(philo));	
	print_table(table);
//	if (pthread_create(&t1, NULL, &routine2, NULL) != 0)
//		return (-1);
//	if (pthread_create(&t2, NULL, &routine2, NULL) != 0)
//		return (-1);
//	if (pthread_join(t1, NULL) != 0)
//		return (-1);
//	if (pthread_join(t2, NULL) != 0)
//		return (-1);
	return (0);
}
