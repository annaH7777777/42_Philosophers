#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
    int num_phil;
    int time_die;
    int time_eat;
    int time_sleep;
    int times_phil_eat;
}   t_data;

int	ft_isdigit(int c);
int	ft_atoi(char *str);
void    terminate(char *str);