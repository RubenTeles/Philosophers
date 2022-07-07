/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:52:03 by rteles            #+#    #+#             */
/*   Updated: 2022/07/07 20:04:18 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*gcc philo.c -o philo -lpthread && ./philo*/
void	*myturn(void *arg)
{
	t_philo	*philo;
	int		*result;
	int		i;
	int		fork[2];

	i = 0;
	philo = (t_philo *)arg;
	result = (int *)malloc(sizeof(int));
	philo->t->dif = 0;
	gettimeofday(&philo->t->start, NULL);
	while (philo->eat < philo->p->n_x_eat)
	{
		philo->t->last_dif = philo->t->dif;
		gettimeofday(&philo->t->current, NULL);
		philo->t->dif = philo->t->current.tv_usec - philo->t->start.tv_usec;
		philo->t->last_dif = philo->t->dif - philo->t->last_dif;
		philo->t_live += philo->t->last_dif;
		
		if (philo->t_live >= philo->p->t_die)
		{
			printf("%ld \033[1;32m%i\033[0m is \033[0;37mdied\033[0m\n", philo->t->dif, philo->n);
			philo->status = 4;
			break ;
		}
		if (philo->status == 1)
		{
			printf("%ld \033[1;32m%i\033[0m is \033[0;33meating\033[0m\n", philo->t->dif, philo->n);
			philo->status = 2;
			philo->eat += 1;
			usleep(philo->p->t_eat);
			philo->t_live = 0;
			continue ;
		}
		else if (philo->status == 2)
		{
			printf("%ld \033[1;32m%i\033[0m is \033[0;34msleeping\033[0m\n", philo->t->dif, philo->n);
			philo->status = 3;
			usleep(philo->p->t_sleep);
			//philo->t_live += philo->p->t_sleep;
			continue ;
		}
		else if (philo->status == 3)
		{
			//if (philo->fork)
			printf("%ld \033[1;32m%i\033[0m is \033[0;36mthinking\033[0m\n", philo->t->dif, philo->n);
			philo->status = 1;
			//philo->t_live += philo->t->last_dif;
			continue ;
		}
	}
	*result = i * 2;
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
			all->philo[i].next_philo = all->philo[0].bro;
		else
			all->philo[i].next_philo = all->philo[i + 1].bro;
		pthread_mutex_init(&all->philo[i].fork, NULL);
		if ((i + 1) % 2 == 1)
			all->philo[i].status = 1;
		else
			all->philo[i].status = 3;
		all->philo[i].eat = 0;
		all->philo[i].t_live = 0;
		i++;
	}
	//printf("Number: %i\nTime Die: %i\nTime Eat: %i\nTime Sleep: %i\nTimes Eat: %i\n", all->p.number, all->p.t_die, all->p.t_eat, all->p.t_sleep, all->p.n_x_eat);
}

int	main(int argc, char **argv)
{
	t_all			all;
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
		pthread_create(&all.philo[i].thread, NULL, myturn, &all.philo[i]);
	i = -1;
	while (++i < all.p.number)
		pthread_join(all.philo[i].thread, NULL);
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