#include "philosopher.h"
long int get_time_ms()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}
long long get_time_mic()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000000 + current_time.tv_usec);
}

void eat(void *data)
{
    pthread_mutex_lock(&(((t_philosopher*)data)->common_data->write_lock));
    printf("%ld %d  is eating\n", get_time_ms(),  ((t_philosopher *)data)->id + 1);
    pthread_mutex_unlock(&(((t_philosopher*)data)->common_data->write_lock));
    usleep(100);

}

void sleeep(void *data)
{
    pthread_mutex_lock(&(((t_philosopher*)data)->common_data->write_lock));
    printf("%ld %d  is sleeping\n", get_time_ms(),  ((t_philosopher *)data)->id + 1);
    pthread_mutex_unlock(&(((t_philosopher*)data)->common_data->write_lock));
    usleep(100);

}
void died(void *data)
{
    pthread_mutex_lock(&(((t_philosopher*)data)->common_data->write_lock));
    printf("%ld %d  died\n", get_time_ms(),  ((t_philosopher *)data)->id + 1);
    pthread_mutex_unlock(&(((t_philosopher*)data)->common_data->write_lock));
    usleep(100);
}
void think(void *data)
{
    pthread_mutex_lock(&(((t_philosopher*)data)->common_data->write_lock));
    printf("%ld %d  is think\n", get_time_ms(),  ((t_philosopher *)data)->id + 1);
    pthread_mutex_unlock(&(((t_philosopher*)data)->common_data->write_lock));
    usleep(100);
}

void *Philosopher(void *data)
{
    int id = ((t_philosopher*)data)->id;
    pthread_mutex_t* mutex = ((t_philosopher*)data)->common_data->forks;
    int philo_num = ((t_philosopher*)data)->common_data->times[0];
    while (1)
    {
        pthread_mutex_lock(&mutex[id]);
        pthread_mutex_lock(&mutex[(id + 1) % philo_num]);

        eat(data);
        // relase_forks();
        pthread_mutex_unlock(&mutex[(id + 1) % philo_num]);
        pthread_mutex_unlock(&mutex[id]);
        think(data);
        sleeep(data);
        
    }
    return (NULL);
}

int main(int rc, char **args)
{
    int i, j;
    t_data data;
    t_philosopher *philosophers;

    if (!init_data(rc, args, &data))
    {
        printf("ARG ERROR\n");
        return (1);
    }
    philosophers = malloc(sizeof(t_philosopher) * data.times[0]);
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

    if (pthread_mutex_init(&data.write_lock, NULL))
    {
        printf("MUTEX INIT HAS FAILED !!\n");
        return (1);
    }

    i = -1;
    while (++i < data.times[0])
    {
        philosophers[i].id = i;
        philosophers[i].common_data = &data;
        if (pthread_create(&(philosophers[i].thread), NULL, Philosopher, &philosophers[i]))
        {
            printf("THREAD CREATE HAS FAILED !!\n");
            return (1);
        }
        usleep(100);
    }
    i = -1;
    while (++i < data.times[0])
    {
        if (pthread_join(philosophers[i].thread, NULL))
        {
            printf("THREAD CREATE HAS FAILED !!\n");
            return (1);
        }
    }
    //free mutex
    //free philosophers
    return (0);
}