#include "philosopher.h"
long int get_time_ms()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void eat(void *data)
{

    printf("%ld %d  is eating\n", get_time_ms(), (*(t_data *)data).philo_index);
    usleep(100000);
}

void sleeep(void *data)
{
    printf("%ld %d  is sleeping\n", get_time_ms(), (*(t_data *)data).philo_index);
    usleep(100000);
}

void think(void *data)
{
    printf("%ld %d  is thinking\n", get_time_ms(), (*(t_data *)data).philo_index);
    usleep(100000);
}

void *Philosopher(void *data)
{
    while (1)
    {
        eat(data);
        think(data);
        sleeep(data);
    }
    return (NULL);
}

int main(int rc, char **args)
{
    int i, j;
    t_data data;

    if (!init_data(rc, args, &data))
    {
        printf("ARG ERROR\n");
        return (1);
    }
    data.philo = malloc(sizeof(pthread_t) * data.times[0]);
    data.forks = malloc(sizeof(pthread_mutex_t) * data.times[0]);
    i = -1;
    while (++i < data.times[0])
    {
        if (pthread_mutex_init(&data.forks[i], NULL))
        {
            printf("MUTEX INIT HAS FAILED !!\n");
            return (1);
        }
    }
    i = -1;
    while (++i < data.times[0])
    {
        data.philo_index = i + 1;
        if (pthread_create(&data.philo[i], NULL, Philosopher, &data))
        {
            printf("THREAD CREATE HAS FAILED !!\n");
            return (1);
        }
    }
    i = -1;
    while (++i < data.times[0])
    {
        if (pthread_join(data.philo[i], NULL))
        {
            printf("THREAD CREATE HAS FAILED !!\n");
            return (1);
        }
    }

    return (0);
}