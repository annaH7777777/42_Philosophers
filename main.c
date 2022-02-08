#include "philosophers.h"

void* routine(void* arg)
{
	printf("philo thread ");
	//free(arg);
	//*(int*)arg = sum;
    return (0);
}

void create_threads(t_data *data)
{
	int	i;
	pthread_t th[data->num_phil];

	i = 0;
	while (i < data->num_phil)
	{
    	int* a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
        	perror("failed to create thread");
		i++;
	}
	int global_sum = 0;
	i = 0;
    while (i < data->num_phil)
	{
    	int *r;
		if (pthread_join(th[i], (void **)&r) != 0)
			perror("failed to create thread");
		global_sum += *r;
		free(r);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data	data;
	int		i;
	int		j;
	if(argc < 5 || argc > 6)
		terminate("wrong arguments");
	i = 1;
	//maybe need to split if 2 arguments
	while(argv[i])
	{
		j = 0;
		while(argv[i][j])
		{
			if(!ft_isdigit(argv[i][j]))
				terminate("not digit arguments");
			j++;
		}
		i++;
	}
	data.num_phil = ft_atoi(argv[1]);
	data.time_die = ft_atoi(argv[2]);
	data.time_eat = ft_atoi(argv[3]);
	data.time_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		data.times_phil_eat = ft_atoi(argv[5]);
	else
		data.times_phil_eat = 0;
	printf("%d, %d, %d, %d, %d", data.num_phil, data.time_die, data.time_eat, data.time_sleep, data.times_phil_eat);
	create_threads(&data);
	
	
}