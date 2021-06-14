#include "philosopher.h"


int main(int rc, char **args)
{
    t_data data;
    t_philosopher *philosophers;


    philosophers = NULL;
    if (!init_data(rc, args, &data))
    {
        printf("ARG ERROR\n");
        return (1);
    }
    if (init_mutex(&data))
        return (1);
    if (create_threads(&philosophers, &data))
        return (1);
    if (join_threads(philosophers, data))
        return (1);
    destroy_forks(&data);
    free (philosophers);
    return (0);
}