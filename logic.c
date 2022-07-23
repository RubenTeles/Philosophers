/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:08:11 by rteles            #+#    #+#             */
/*   Updated: 2022/07/22 21:48:02 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	for_one_philo(t_philo *philo)
{
	usleep(philo->rules->t_die * 1000);
	ft_mensage(philo->rules->t_start, philo, "died");
	return (1);
}

/*void	who_died(t_all *all, int i)
{
	t_philo	*philo_dead;

	philo_dead = NULL;
	while (++i < all->rules.number)
	{
		if (!all->philo[i].is_dead)
			continue;
		if (philo_dead == NULL)
			philo_dead = &all->philo[i];
		else if (all->philo[i].time_dead < philo_dead->time_dead)
			philo_dead = &all->philo[i];
	}
	printf("%lli %i %s\n", philo_dead->time_dead, philo_dead->n, "died");
}*/

void	*logic(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->last_eat = philo->rules->t_start;
	if (philo->rules->number == 1 && for_one_philo(philo))
		return (0);
	if (philo->n % 2)
		usleep(1500);
	while (!(*philo->dead) && philo->eat < philo->rules->n_x_eat)
	{
		if (*philo->dead == 1 || is_dead(philo))
			return (0);
		if (philo->use_fork == 0 && *philo->use_fork_2 == 0
			&& philo->status == 3 && *philo->dead == 0)
		{
			if (*philo->dead == 1 || ft_take_forks(philo) || ft_eat(philo)
				|| ft_sleep(philo) || ft_thinking(philo))
				return (0);
		}
		else if (philo->status == 3 && philo->is_thinking == 0
			&& philo->eat > 0)
		{
			if (*philo->dead == 1 || ft_thinking(philo))
				return (0);
			continue ;
		}
	}
	return (0);
}

int	ft_logic(t_all *all, int i)
{
	all->rules.t_start = time_current();
	while (++i < all->rules.number)
		pthread_create(&all->philo[i].thread, NULL, logic, &all->philo[i]);
	i = all->rules.number;
	while (--i >= 0)
		pthread_join(all->philo[i].thread, NULL);
	while (++i < all->rules.number)
	{
		pthread_mutex_destroy(&all->philo[i].fork);
	}
	pthread_mutex_destroy(&all->speak);
	pthread_mutex_destroy(&all->rules.m_dead);
	return (0);
}

//printf("philo: %i eat %i times\n", all->philo[i].n, all->philo[i].eat);
/*if (*all->dead)
printf("No one Died!\n");*/