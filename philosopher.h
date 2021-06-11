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
    int philo_index;
} t_data;

int all_num(char *str);
int init_data(int rc, char **args, t_data *data);
#endif