#include "ft_philo.h"

int	ft_atoi_sign(char **nstr)
{
	int	sign;

	sign = 1;
	if (**nstr == '-' || **nstr == '+')
	{
		(*nstr)++;
		if (*(*nstr - 1) == '-')
			sign = -1;
	}
	return (sign);
}

int	ft_atoi(char *nstr)
{
	long long	nbr;
	int			sign;

	nbr = 0;
	sign = ft_atoi_sign(&nstr);
	if (*nstr >= '0' && *nstr <= '9')
	{
		while (*nstr >= '0' && *nstr <= '9')
		{
			nbr = nbr * 10 + (*nstr - 48);
			nstr++;
			if ((nbr > 2147483647 && sign == 1) || (nbr > 2147483648))
				return (0);
		}
		if (*nstr != ' ' && *nstr != 0)
			return (0);
	}
	else
		return (0);
	return ((int)nbr * sign);
}

int	parse_args(int argc, char **argv, t_table *table)
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
	if (argc == 6)
	{
		table->nb_meals = ft_atoi(argv[5]);
		if (table->nb_meals <= 0)
			return (-1);
	}
	return (0);
}
