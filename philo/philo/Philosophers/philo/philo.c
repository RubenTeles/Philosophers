/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:52:03 by rteles            #+#    #+#             */
/*   Updated: 2022/07/08 18:32:16 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*gcc philo.c -o philo -lpthread && ./philo*/

int	is_dead(t_philo *philo, int a)
{
	long int	dif;
	long int	dif_2;

	gettimeofday(&philo->t->current, NULL);
	dif = philo->t->current.tv_usec - philo->t->start.tv_usec;
	if (dif < 0)
	{
		dif_2 = 999999 - philo->t->start.tv_usec;
		philo->t->time_add = dif_2 + philo->t->current.tv_usec;
		philo->t->start = philo->t->current;
	}
	philo->t->time = dif + philo->t->time_add;
	if (philo->status == 2)
		philo->t->last_eat = philo->t->current.tv_usec;
	philo->t_live = philo->t->current.tv_usec - philo->t->last_eat;
	if (philo->t_live >= philo->p->t_die && a == 0)
	{
		printf("%ldms \033[1;32m%i\033[0m is \033[0;37mdied\033[0m\n", philo->t->time, philo->n);
		//pthread_detach(philo->thread);
		//printf("%ld \033[1;32m%i\033[0m is \033[0;37mdied\033[0m TIME LIVE: %ld\n", philo->t->time, philo->n, philo->t_live);
		return (1);
	}
	return (0);
}

void	*myturn(void *arg)
{
	t_philo	*philo;
	int		*result;
	static int		a = 0;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	result = (int *)malloc(sizeof(int));
	philo->t->time = 0;
	philo->t->time_add = 0;
	gettimeofday(&philo->t->start, NULL);
	while (philo->eat < philo->p->n_x_eat)
	{
		if (a == 1 || is_dead(philo, a))
		{
			a = 1;
			return (0);
		}
		if (philo->use_fork == 0 && *philo->use_fork_2 == 0 && philo->status == 3 && a == 0)
		{
			pthread_mutex_lock(&philo->fork);
			philo->use_fork = 1;
			if (a == 1 || is_dead(philo, a))
			{
				a = 1;
				pthread_mutex_unlock(&philo->fork);
				return (0);
			}
			printf("%ldms \033[1;32m%i\033[0m is \033[0;33mhas taken a fork\033[0m\n", philo->t->time, philo->n);
			pthread_mutex_lock(philo->fork_2);
			if (a == 1 || is_dead(philo, a))
			{
				a = 1;
				pthread_mutex_unlock(&philo->fork);
				pthread_mutex_unlock(philo->fork_2);
				return (0);
			}
			printf("%ldms \033[1;32m%i\033[0m is \033[0;33mhas taken a fork\033[0m\n", philo->t->time, philo->n);
			philo->status = 1;
		}
		if (philo->status == 1 && a == 0)
		{
			if (a == 1 || is_dead(philo, a))
			{
				a = 1;
				pthread_mutex_unlock(&philo->fork);
				pthread_mutex_unlock(philo->fork_2);
				return (0);
			}
			printf("%ldms \033[1;32m%i\033[0m is \033[0;33meating\033[0m\n", philo->t->time, philo->n);
			philo->eat += 1;
			usleep(philo->p->t_eat);
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_unlock(philo->fork_2);
			philo->use_fork = 0;
			*philo->use_fork_2 = 0;
			philo->status = 2;
			//gettimeofday(&philo->t->current, NULL);
			//philo->t->last_eat = philo->t->current.tv_usec;
			if (a == 1 || is_dead(philo, a))
			{
				a = 1;
				return (0);
			}
			//philo->t_live = 0;
			// Apos Comer Dormir
			//ft_get_time(philo->t);
			//philo->t_live += philo->t->last_dif;
			printf("%ldms \033[1;32m%i\033[0m is \033[0;34msleeping\033[0m\n", philo->t->time, philo->n);
			usleep(philo->p->t_sleep);
			if (a == 1 || is_dead(philo, a))
			{
				a = 1;
				return (0);
			}
			philo->status = 3;
			philo->is_thinking = 0;
			continue ;
		}
		else if (philo->status == 3 && philo->is_thinking == 0)
		{
			philo->is_thinking = 1;
			if (a == 1 || is_dead(philo, a))
			{
				a = 1;
				return (0);
			}
			printf("%ldms \033[1;32m%i\033[0m is \033[0;36mthinking\033[0m\n", philo->t->time, philo->n);
			continue ;
		}
	}
	//*result = i * 2;
	return (result);
}

/*printf("%ld\n", time.current.tv_usec - time.start.tv_usec);*/
void	yourturn(void)
{
	int	i;

	i = -1;
	while (++i < 10)
	{
		usleep(200000);
		printf("\033[1;31mYour Turn\033[0m %i\n", i);
	}
}

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

void	ft_organize_philosophers(t_all *all, int argc, char **argv)
{
	int	i;
	int	*result; //Teste = return o resultado da thread

	i = 0;
	all->p.number = ft_atoi(argv[1]);
	all->p.t_die = ft_atoi(argv[2]);
	all->p.t_eat = ft_atoi(argv[3]);
	all->p.t_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		all->p.n_x_eat = ft_atoi(argv[5]);
	all->philo = malloc(sizeof(t_philo) * all->p.number);
	if (!all->philo)
		exit(0);
	while (i < all->p.number)
	{
		all->philo[i].n = i + 1;
		all->philo[i].t = &all->t;
		all->philo[i].p = &all->p;
		if (i + 1 == all->p.number)
		{
			all->philo[i].fork_2 = &all->philo[0].fork;
			all->philo[i].use_fork_2 = &all->philo[0].use_fork;
		}
		else
		{
			all->philo[i].fork_2 = &all->philo[i + 1].fork;
			all->philo[i].use_fork_2 = &all->philo[i + 1].use_fork;
		}
		pthread_mutex_init(&all->philo[i].fork, NULL);
		all->philo[i].use_fork = 0;
		//if ((i + 1) % 2 == 1)
		//	all->philo[i].status = 1;
		//else
		all->philo[i].status = 3;
		all->philo[i].eat = 0;
		all->philo[i].t_live = 0;
		all->philo[i].is_thinking = 0;
		i++;
	}
	//printf("Number: %i\nTime Die: %i\nTime Eat: %i\nTime Sleep: %i\nTimes Eat: %i\n", all->p.number, all->p.t_die, all->p.t_eat, all->p.t_sleep, all->p.n_x_eat);
}

int	main(int argc, char **argv)
{
	t_all			all;
	int				*result;
	int				i;

	(void)argc;
	(void)argv;
	i = argc - 1;
	if ((argc < 5 || argc > 6)  || (ft_atoi(argv[1]) <= 0
		|| ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0) || (argc == 6 && ft_atoi(argv[5]) <= 0))
		return (0);
	while (i > 0)
	{
		if (ft_str_s_str(argv[i--], "+-0123456789") == 0)
			return (0);
	}
	ft_organize_philosophers(&all, argc - 1, argv);
	i = -1;
	while (++i < all.p.number)
	{
		pthread_create(&all.philo[i].thread, NULL, myturn, &all.philo[i]);
		//pthread_detach(all.philo[i].thread);
	}
	i = -1;
	while (++i < all.p.number)
	{
		pthread_join(all.philo[i].thread, (void *)&result);
		/*printf("Result: %i\n", *result);
		if (*result == 4)
			pthread_detach(all.philo[i].thread);*/
		pthread_mutex_destroy(&all.philo[i].fork);
	}
	//printf("%ld\n", all.t.current.tv_usec - all.t.start.tv_usec);
	//printf("Result: %i\n", *result);
	free(all.philo);
	all.philo = 0;
	return (0);
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