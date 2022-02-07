#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_atoi(char *str)
{
	int i;
	int j;
	int sign_min;
	int sum;

	i = 0;
	j = 0;
	sign_min = 1;
	sum = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign_min = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + str[i] - '0';
		i++;
	}
	return (sign_min * sum);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	else
		return (0);
}

void    terminate(char *str)
{
	write(1, &str, ft_strlen(str));
	exit(1);
}

long long timestamp()
{
	struct timeval t;
	long long a;
	gettimeofday(&t, NULL);
	a = t.tv_sec * 1000 + t.tv_usec  / 1000;
	return (a);
}

long long time_diff(long long a, long long b)
{
	return (a - b);
}

void print_action (t_data *data, int id, char *str)
{
	long long ms;

	pthread_mutex_lock(&(data->write_check_m));
	if(!(data->any_died))
	{
		ms = timestamp() - data->first_timestamp;
		printf("%lld %d %s\n", ms, id + 1, str);
	}
	pthread_mutex_unlock(&(data->write_check_m));
}
