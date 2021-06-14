#include "philosopher.h"

int wait_(t_philosopher *ph)
{
    int i;
    int all;
    
    while(1)
    {
        i = 0;
        all = 0;
        while(i < ph[0].common_data->times[0])
        {
            if (get_time_mic() - ph[i].last_eat_time > ph[i].common_data->times[1] * 1000)
            {
                printf("%lld %d  died\n", get_time_ms() - ph[i].common_data->start, ph[i].id + 1);
                return (0);
            }
            if (ph[0].common_data->times[4] > 0 && ph[i].eat_time >= ph[0].common_data->times[4])
                all++;
            i++;
        }
        if (all == ph[0].common_data->times[0])
            return (1);
    }
}

int init_mutex(t_data *data)
{
    int i;

    i = -1;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->times[0]);
    while (++i < data->times[0])
    {
        if (pthread_mutex_init(&data->forks[i], NULL))
        {
            printf("MUTEX INIT HAS FAILED !!\n");
            return (1);
        }
    }

    if (pthread_mutex_init(&data->write_lock, NULL))
    {
        printf("MUTEX INIT HAS FAILED !!\n");
        return (1);
    }
    return (0);
}

int create_threads(t_philosopher **philosophers, t_data *data)
{
    int i;

    *philosophers = malloc(sizeof(t_philosopher) * data->times[0]);
    i = -1;
    while (++i < data->times[0])
    {
        (*philosophers)[i].id = i;
        (*philosophers)[i].eat_time = 0;
        (*philosophers)[i].common_data = data;
        (*philosophers)[i].last_eat_time = get_time_mic();
        (*philosophers)[i].common_data->start = get_time_ms();
        if (pthread_create(&((*philosophers)[i].thread), NULL, Philosopher, &(*philosophers)[i]))
        {
            printf("THREAD CREATE HAS FAILED !!\n");
            return (1);
        }
        usleep(100);
    }
    if (!wait_(*philosophers))
        return (1);
    return (0);
}

int join_threads(t_philosopher *philosophers, t_data data)
{
    int i;

    i = -1;
    while (++i < data.times[0])
    {
        if (pthread_join(philosophers[i].thread, NULL))
        {
            printf("THREAD CREATE HAS FAILED !!\n");
            return (1);
        }
    }
    return (0);
}

void destroy_forks(t_data *data)
{
    int i;

    i = -1;
    while(++i < data->times[0])
        pthread_mutex_destroy(&data->forks[i]);
    free(data->forks);
}