#include "philosopher.h"

void eat(t_philosopher *ph)
{
    pthread_mutex_lock(&ph->common_data->write_lock);
    printf("%lld %d  is eating\n", get_time_ms() - ph->common_data->start,  ph->id + 1);
    pthread_mutex_unlock(&ph->common_data->write_lock);
    ph->last_eat_time = get_time_mic();
    ph->eat_time++;
    my_sleep(2, *ph);


}

void sleeep(t_philosopher *ph)
{
    pthread_mutex_lock(&ph->common_data->write_lock);
    printf("%lld %d  is sleeping\n", get_time_ms() - ph->common_data->start,  ph->id + 1);
     pthread_mutex_unlock(&ph->common_data->write_lock);
     my_sleep(3, *ph);
}

void think(t_philosopher *ph)
{
    pthread_mutex_lock(&ph->common_data->write_lock);
    printf("%lld %d  is think\n", get_time_ms() - ph->common_data->start,  ph->id + 1);
    pthread_mutex_unlock(&ph->common_data->write_lock);
}
int condition(t_philosopher *ph)
{
    if (ph->common_data->died)
        return (0);
    if (get_time_mic() - ph->last_eat_time > ph->common_data->times[1] * 1000)
    {
        printf("%lld %d  died\n", get_time_ms() - ph->common_data->start,  ph->id + 1);
        ph->common_data->died = 1;
        return (0);
    }
    if (ph->common_data->times[4] > 0 && ph->eat_time >= ph->common_data->times[4])
        return (0);
    return (1);
}

void *Philosopher(void *data)
{
    t_philosopher *ph = ((t_philosopher*)data);
    int id = ph->id;
    pthread_mutex_t* mutex = ph->common_data->forks;
    int philo_num = ph->common_data->times[0];
    while (condition(ph))
    {
        /*
            pickup forks
        */
        pthread_mutex_lock(&mutex[id]);
        pthread_mutex_lock(&mutex[(id + 1) % philo_num]);

        eat(ph);
        /* 
            drop forks
        */
        pthread_mutex_unlock(&mutex[(id + 1) % philo_num]);
        pthread_mutex_unlock(&mutex[id]);
        sleeep(ph);
        think(ph);
        
    }
    return (NULL);
}

int main(int rc, char **args)
{
    int i;
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
        philosophers[i].eat_time = 0;
        philosophers[i].common_data = &data;
        philosophers[i].last_eat_time = get_time_mic();
        philosophers[i].common_data->start = get_time_ms();
        if (pthread_create(&(philosophers[i].thread), NULL, Philosopher, &philosophers[i]))
        {
            printf("THREAD CREATE HAS FAILED !!\n");
            return (1);
        }
        usleep(100);
    }
    // check if someone died or not;
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