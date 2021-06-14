#include "philosopher.h"

void	eat(t_philosopher *ph)
{
	pthread_mutex_lock(&ph->common_data->write_lock);
	printf("%lld %d  is eating\n", get_time_ms() - ph->common_data->start,
		ph->id + 1);
	pthread_mutex_unlock(&ph->common_data->write_lock);
	ph->last_eat_time = get_time_mic();
	ph->eat_time++;
	my_sleep(2, *ph);
}

void	sleeep(t_philosopher *ph)
{
	pthread_mutex_lock(&ph->common_data->write_lock);
	printf("%lld %d  is sleeping\n", get_time_ms() - ph->common_data->start,
		ph->id + 1);
	pthread_mutex_unlock(&ph->common_data->write_lock);
	my_sleep(3, *ph);
}

void	think(t_philosopher *ph)
{
	pthread_mutex_lock(&ph->common_data->write_lock);
	printf("%lld %d  is think\n", get_time_ms() - ph->common_data->start,
		ph->id + 1);
	pthread_mutex_unlock(&ph->common_data->write_lock);
}

int	condition(t_philosopher *ph)
{
	if (get_time_mic() - ph->last_eat_time > ph->common_data->times[1] * 1000)
		return (0);
	if (ph->common_data->times[4] > 0 && \
			ph->eat_time >= ph->common_data->times[4])
		return (0);
	return (1);
}

void	*Philosopher(void *data)
{
	t_philosopher	*ph;
	pthread_mutex_t	*mutex;
	int				id;
	int				philo_num;

	ph = ((t_philosopher *)data);
	id = ph->id;
	mutex = ph->common_data->forks;
	philo_num = ph->common_data->times[0];
	while (condition(ph))
	{
		pthread_mutex_lock(&mutex[id]);
		printf("%lld %d  has taken a fork\n",
			get_time_ms() - ph->common_data->start, ph->id + 1);
		pthread_mutex_lock(&mutex[(id + 1) % philo_num]);
		printf("%lld %d  has taken a fork\n",
			get_time_ms() - ph->common_data->start, ph->id + 1);
		eat(ph);
		pthread_mutex_unlock(&mutex[(id + 1) % philo_num]);
		pthread_mutex_unlock(&mutex[id]);
		sleeep(ph);
		think(ph);
	}
	return (NULL);
}
