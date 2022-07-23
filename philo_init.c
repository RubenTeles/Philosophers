/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:11:26 by rteles            #+#    #+#             */
/*   Updated: 2022/07/22 21:44:16 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philo(t_philo *philo, int i)
{
	philo->n = i + 1;
	pthread_mutex_init(&philo->fork, NULL);
	philo->use_fork = 0;
	philo->status = 3;
	philo->eat = 0;
	philo->t_live = 0;
	philo->is_thinking = 0;
	philo->is_dead = 0;
	philo->time_dead = 0;
}

void	ft_philosophers(t_philo *philo, t_philo *philo_2)
{
	philo->fork_2 = &philo_2->fork;
	philo->use_fork_2 = &philo_2->use_fork;
}

int	ft_rules(t_rules *rules, int argc, char **argv)
{
	rules->number = ft_atoi(argv[1]);
	rules->t_die = ft_atoi(argv[2]);
	rules->t_eat = ft_atoi(argv[3]);
	rules->t_sleep = ft_atoi(argv[4]);
	rules->n_x_eat = 2147483647;
	if (argc == 5)
		rules->n_x_eat = ft_atoi(argv[5]);
	return (0);
}

int	ft_organize_philosophers(t_all *all, int argc, char **argv, int i)
{
	if (ft_rules(&all->rules, argc, argv))
		return (1);
	all->philo = malloc(sizeof(t_philo) * all->rules.number);
	if (!all->philo)
		return (1);
	pthread_mutex_init(&all->speak, NULL);
	pthread_mutex_init(&all->rules.m_dead, NULL);
	while (i++ < all->rules.number)
		ft_init_philo(&all->philo[i], i);
	i = 0;
	while (i < all->rules.number)
	{
		all->philo[i].rules = &all->rules;
		all->philo[i].dead = all->dead;
		all->philo[i].speak = &all->speak;
		if (i + 1 < all->rules.number)
			ft_philosophers(&all->philo[i], &all->philo[i + 1]);
		else
			ft_philosophers(&all->philo[i], &all->philo[0]);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all			all;
	int				i;
	static int		dead = 0;

	i = argc - 1;
	if ((argc < 5 || argc > 6) || (ft_atoi(argv[1]) <= 0
			|| ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
			|| ft_atoi(argv[4]) <= 0) || (argc == 6 && ft_atoi(argv[5]) <= 0))
		return (1);
	while (i > 0)
	{
		if (ft_str_s_str(argv[i--], "+-0123456789") == 0)
			return (0);
	}
	all.dead = &dead;
	if (ft_organize_philosophers(&all, argc - 1, argv, -1))
		return (1);
	ft_logic(&all, -1);
	free(all.philo);
	return (0);
}
