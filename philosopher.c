#include "philosopher.h"
long int get_time_ms()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void eat(void *data)
{

    printf("%ld X  is eating\n", get_time_ms());
    usleep(10);
}

void sleeep(void *data)
{
    printf("%ld X  is sleeping\n", get_time_ms());
    usleep(10);

}

void think(void *data)
{
    printf("%ld X  is thinking\n", get_time_ms());
    usleep(10);

}

void *Philosopher(void *data)
{
    eat(data);
    sleeep(data);
    think(data);
    return (NULL);
}



int main(int rc, char **args)
{
    pthread_t *philo;
    pthread_mutex_t *forks;
    int i, j;
    t_data data;

    if (!init_data(rc, args, &data))
    {
        printf("ARG ERROR\n");
        return (1);
    }
    philo = malloc(sizeof(pthread_t) * data.times[0]);
    forks = malloc(sizeof(pthread_mutex_t) * data.times[0]);
    i = -1;
    while (++i < data.times[0])
    {
        if (pthread_mutex_init(&forks[i], NULL))
        {
            printf("MUTEX INIT HAS FAILED !!\n");
            return (1);
        }
    }
    i = -1;
    while (++i < data.times[0])
    {
        if (pthread_create(&philo[i], NULL, Philosopher, &data))
        {
            printf("THREAD CREATE HAS FAILED !!\n");
            return (1);
        }
    }
    i = -1;
    while (++i < data.times[0])
    {
        if (pthread_join(philo[i], NULL))
        {
            printf("THREAD CREATE HAS FAILED !!\n");
            return (1);
        }
    }

    return (0);
}