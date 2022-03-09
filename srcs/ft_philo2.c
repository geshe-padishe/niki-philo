#include "ft_philo.h"

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_join_threads(t_table table)
{
	long unsigned i;

	i = 0;
	if (pthread_join(table.main_thread, NULL) != 0)
		return (-1);
	while (i < table.nb_philos)
	{
		if (pthread_join(((t_philo *)table.darr->list)[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
