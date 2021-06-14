#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <sys/time.h>

typedef struct s_data
{
    int times[5];
    int died;
    pthread_mutex_t write_lock;
    pthread_mutex_t *forks;
    long long start;
} t_data;

typedef struct s_philosopher
{
    int id;
    int eat_time;
    long long last_eat_time;
    pthread_t thread;
    t_data *common_data;

} t_philosopher;


int all_num(char *str);
int init_data(int rc, char **args, t_data *data);
long int get_time_ms();
long long get_time_mic();
void my_sleep(int index, t_philosopher ph);
void *Philosopher(void *data);
int wait_(t_philosopher *ph);
int init_mutex(t_data *data);
int create_threads(t_philosopher **philosophers, t_data *data);
int join_threads(t_philosopher *philosophers, t_data data);
void destroy_forks(t_data *data);
#endif