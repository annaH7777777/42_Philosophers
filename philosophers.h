#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef struct s_philo
{
    int	id;
	int	left_fork_id;
	int	right_fork_id;
	int	times_ate;
	long long last_meal;
	pthread_t thread;
	t_data data;
}	t_philo;

typedef struct s_data
{
    int num_phil;
    int time_die;
    int time_eat;
    int time_sleep;
    int nb_phil_eat;
	int any_died;
	pthread_mutex_t forks[200];
	pthread_mutex_t eat_check_m;
	pthread_mutex_t write_check_m;
	t_philo philos[200];

}   t_data;



int	ft_isdigit(int c);
int	ft_atoi(char *str);
void    terminate(char *str);