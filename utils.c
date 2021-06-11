#include "philosopher.h"

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