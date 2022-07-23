/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:52:03 by rteles            #+#    #+#             */
/*   Updated: 2022/07/22 21:59:35 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int			i;
	int			s;
	long long	n;

	i = 0;
	s = 1;
	n = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		if (n * s > 2147483647)
			return (-1);
		else if (n * s < -2147483648)
			return (0);
		i++;
	}
	return (n * s);
}

int	ft_str_s_str(char *s1, char *s2)
{
	size_t	i;
	size_t	a;

	i = -1;
	if (!s1 || !s2)
		return (0);
	while (s1[++i])
	{
		a = -1;
		while (s2[++a])
		{
			if (s1[i] == s2[a])
				break ;
		}
		if (s1[i] == s2[a])
			continue ;
		return (0);
	}
	return (1);
}

long long	time_current(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000000 + t.tv_usec) / 1000);
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

int	smart_sleep(long long time, t_philo *philo)
{
	long long	i;
	long long	a;

	i = time_current();
	while (!(*philo->dead))
	{
		a = time_current();
		if (a - philo->last_eat >= philo->rules->t_die && is_dead(philo))
			return (1);
		if (time_diff(i, a) >= time)
			return (0);
		usleep(50);
	}
	return (1);
}

void	ft_mensage(long long t_start, t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->speak);
	if (!(*philo->dead))
	{
		printf("%lli ", time_current() - t_start);
		printf("%i %s\n", philo->n, status);
	}
	pthread_mutex_unlock(philo->speak);
}

/*
Criar uma Threads

	pthread_create(&newthread, NULL, myturn, &x); 
(&variavel_criada, (nao sei),
funcao que fica a correr ao mesmo tempo, endereco de variavel que quero passar)

Gerir a Threads Criada

	pthread_join(newthread, (void *)&result);
(variavel_criada, (conversao)endereco do pointer)

Bloquear e Desbloquear a thread, ou seja deixar de correr ao mesmo tempo
quando bloqueada esta acaba o que esta a fazer e ao desbloquear volta ao normal

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&lock)
pthread_mutex_unlock(&lock)
*/

//number_of_philosophers 
//time_to_die time_to_eat 
//time_to_sleep
//[number_of_times_each_philosopher_must_eat]