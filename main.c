#include "philosopher.h"

int	just_for_norm(t_philosopher *ph)
{
	pthread_mutex_lock(&ph->common_data->write_lock);
	printf("%lld %d  died\n",
		get_time_ms() - ph->common_data->start, ph->id + 1);
	pthread_mutex_unlock(&ph->common_data->write_lock);
	return (0);
}

int	wait_(t_philosopher *ph)
{
	int	i;
	int	all;

	while (1)
	{
		i = 0;
		all = 0;
		while (i < ph[0].common_data->times[0])
		{
			if (get_time_mic() - ph[i].last_eat_time > \
				ph[i].common_data->times[1] * 1000)
				return (just_for_norm(&ph[i]));
			if (ph[0].common_data->times[4] > 0 && \
				ph[i].eat_time >= ph[0].common_data->times[4])
				all++;
			i++;
		}
		if (all == ph[0].common_data->times[0])
			return (1);
	}
}

int	main(int rc, char **args)
{
	t_data			data;
	t_philosopher	*philosophers;

	philosophers = NULL;
	if (!init_data(rc, args, &data))
	{
		printf("ARG ERROR\n");
		return (1);
	}
	if (init_mutex(&data))
		return (1);
	if (create_threads(&philosophers, &data))
		return (1);
	if (join_threads(philosophers, data))
		return (1);
	destroy_forks(&data);
	free(philosophers);
	return (0);
}
