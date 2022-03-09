#include "ft_philo.h"

void *routine(void *ptr)
{
	t_philo			*philo;
	struct timeval	time;
	bool			dead;

	//(void)time;
	philo = ptr;
	dead = 0;
	//dprintf(1, "STARTING THREAD %i\n", philo->id);
	while (!dead)
	{
		if (ft_timeget(&time))
			return (NULL);
	//	ft_putnbr(ft_timediff_us(time, philo->ate_time));
	//	write(1, "\n", 1);
		if (ft_timediff_us(time, philo->ate_time) >=
			philo->table->time_to_die * 1000)
			dead = 1;
		//pthread_mutex_lock(philo->wr_mutex);
		//philo->table->dead = 1;
		philo->ate_time = time;
		ft_write("Eeating\n", *philo);
		ft_sleep(philo->table->time_to_eat);
		ft_write("Sleeping\n", *philo);
		ft_sleep(philo->table->time_to_sleep);
		ft_write("Thinking\n", *philo);
		//pthread_mutex_unlock(philo->wr_mutex);
	}
	//pthread_mutex_lock(philo->mutex);
	ft_write("Died\n", *philo);
	//pthread_mutex_unlock(philo->mutex);
	return (philo);
}

void	*create_philos(void *ptr)
{
	unsigned long	i;
	t_philo			philo;
	pthread_mutex_t	wr_mutex;
	pthread_mutex_t	rd_mutex;
	t_table			*table;
	bool			dead;

	i = 0;
	table = (t_table *)ptr;
	pthread_mutex_init(&wr_mutex, NULL);
	pthread_mutex_init(&rd_mutex, NULL);
	pthread_mutex_lock(&wr_mutex);
	//pthread_mutex_lock(&rd_mutex);
	while (i < table->nb_philos)
	{
		ft_memset(&philo, sizeof(t_philo));
		philo.wr_mutex = &wr_mutex;
		philo.rd_mutex = &rd_mutex;
		philo.table = table;
		philo.id = i;
		if (ft_timeget(&philo.ate_time))
			return (NULL);
		if (ft_timeget(&philo.start_time))
			return (NULL);
		if (push_dynarray(table->darr, &philo, 1, 0) == -1)
			return (NULL);
		if (pthread_create(&((t_philo *)table->darr->list)[i].thread, NULL,
							&routine, &((t_philo *)table->darr->list)[i]))
			return (NULL);
		i++;
	}
	pthread_mutex_unlock(&wr_mutex);
	//pthread_mutex_unlock(&rd_mutex);
	while (dead == 0)
	{
		dprintf(1, "qo");
		pthread_mutex_lock(&wr_mutex);
		dead = table->dead;
		pthread_mutex_unlock(&wr_mutex);
	}
	pthread_mutex_destroy(&wr_mutex);
	pthread_mutex_destroy(&rd_mutex);
	return (0);
}

int main(int argc, char **argv)
{
	t_table			table;
	t_dynarray		darr;

	ft_memset(&table, sizeof(t_table));
	if (argc != 6 || parse_args(argv, &table) != 0)
		return (printf("Invalid Args\n"), -1);
	if (init_dynarray(&darr, table.nb_philos, sizeof(t_philo)) == -1)
		return (free_dynarray(&darr), -1);
	table.darr = &darr;
	if (pthread_create(&table.main_thread, NULL, create_philos, &table))
		return (-1);
	//printf("addr = %p\n", ((t_philo *)darr.list)[0].wr_mutex);
	if (ft_join_threads(table))
		return (-1);
	return (free_dynarray(&darr), 0);
}
