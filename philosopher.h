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
    pthread_mutex_t write_lock;
    pthread_mutex_t *forks;
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
#endif