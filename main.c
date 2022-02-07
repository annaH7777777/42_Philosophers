#include "philo.h"

void eat(t_philo* philo)
{
	t_data *data;
	
	data = philo->data;

	pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
	print_action(data, philo->id, "has taken a fork");
	printf("right fork Id %d\n", philo->right_fork_id);
	pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
	print_action(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->eat_check_m));
	print_action(data, philo->id, "philo is eating");
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(data->eat_check_m));
	smart_sleep(data->time_eat, philo);
	//usleep(data->time_eat);
	(philo->times_ate)++;
	pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
}

void smart_sleep(long long time, t_philo *philo)
{
	long long ms;

	ms = timestamp();
	//printf("%lld %d is sleeping\n", ms, philo->id);
	while(!(philo->data->any_died))
	{
		if(time_diff(timestamp(), ms) >= time)
			break;
		usleep(50);
	}
	//usleep(philo->data->time_sleep);
}


void* philo_routine(void* arg)
{
	t_philo philo;
	philo = *(t_philo*)arg;
	//printf("\nphilo thread %d\n", philo.id);
	//free(arg);
	printf("philo thread id %d\n", philo.id);
	if(philo.id % 2)
	{
		printf("before\n");
		usleep(15000);
		printf("after\n");
	}
	while (!(philo.data->any_died))
	{
		eat(&philo);
		if (philo.data->all_ate)
			break ;
		print_action(philo.data, philo.id, "is sleeping");
		smart_sleep(philo.data->time_sleep, &philo);
		print_action(philo.data, philo.id, "is thinking");
	}
    return (NULL);
}

void create_threads(t_data* data)
{
	int	i;

	i = 0;
	while (i < data->num_phil)
	{
		if (pthread_create(&(data->philos[i]).thread, NULL, &philo_routine, (void*)&(data->philos[i])) != 0)
        	perror("failed to create thread");
		data->philos[i].last_meal = timestamp();
		i++;
	}
}

void join_thread(t_data *data)
{
	int i;
	i = 0;
    while (i < data->num_phil)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			perror("failed to create thread");
		i++;
	}
	//Destroy mutexes
	i = -1;
	while (++i < data->num_phil)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->eat_check_m));
	pthread_mutex_destroy(&(data->write_check_m));
}

void init(t_data *data, int argc, char **argv)
{
	int	i;
	int	j;

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
	data->num_phil = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		data->nb_phil_eat = ft_atoi(argv[5]);
	else
		data->nb_phil_eat = -1;
	data->first_timestamp = timestamp();
	data->all_ate = 0;
	data->any_died = 0;
	i = 0;
	while(i < data->num_phil)
	{
		data->philos[i].id = i;
		data->philos[i].left_fork_id = i;
		data->philos[i].right_fork_id = (i + 1) / data->num_phil;
		data->philos[i].times_ate = 0;
		data->philos[i].data = data;
		data->philos[i].last_meal = 0;
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(data->eat_check_m), NULL);
	pthread_mutex_init(&(data->write_check_m), NULL);
	
}


void check_death(t_data *data)
{
	int i;
	while(!(data->all_ate))
	{
		i = -1;
		while (++i < data->num_phil && !(data->any_died))
		{
			pthread_mutex_lock(&(data->eat_check_m));
			if(time_diff(timestamp(), data->philos[i].last_meal) >= data->time_die)
			{
				print_action(data, data->philos[i].id, "died");
				data->any_died = 1;
			}
			pthread_mutex_unlock(&(data->eat_check_m));
			usleep(100); //????
		}
		if(data->any_died)
			break;
		i = 0;
		while (data->nb_phil_eat != -1 && i < data->num_phil && data->philos[i].times_ate >= data->nb_phil_eat)
		{
			//if(data->philos[i].times_ate == data->nb_phil_eat)
				i++;
			//else 
			//	break;
		}
		if(i == data->num_phil)
			data->all_ate = 1;
	}
}

int main(int argc, char **argv)
{
	t_data	data;
	if(argc < 5 || argc > 6)
		terminate("wrong arguments");
	init(&data, argc, argv);
	printf("%d, %d, %d, %d, %d", data.num_phil, data.time_die, data.time_eat, data.time_sleep, data.nb_phil_eat);
	data.first_timestamp = timestamp();
	create_threads(&data);
	check_death(&data);
	join_thread(&data);
	
}