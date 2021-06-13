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

void my_sleep(int index, t_philosopher ph)
{
    long long microb;
    microb = get_time_mic();
    usleep(ph.common_data->times[2] * 1000 - 15000);
    while (get_time_mic() - microb < ph.common_data->times[index] * 1000 );
}

int all_num(char *str)
{
    while(*str)
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

int init_data(int rc, char **args, t_data *data)
{
    int i;
    if (rc < 5 || rc > 6)
        return (0);
    args++;
    i = 0;
    data->died = 0;
    data->times[4] = -1;
    while (*args)
    {
        if (!all_num(*args))
            return (0);
        data->times[i++] = ft_atoi(*args);
        args++;
    }
    return (1);
}