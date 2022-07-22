/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:10:57 by rteles            #+#    #+#             */
/*   Updated: 2022/07/22 21:59:48 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	long int	t_current;
	//long int	dif;

	t_current = time_current();
	//dif = t_current - philo->t->start;
	/*if (dif < 0)
	{
		dif_2 = 999999 - philo->t->start.tv_usec;
		philo->t->time_add = dif_2 + philo->t->current.tv_usec;
		philo->t->start = philo->t->current;
	}
	philo->t->time = dif + philo->t->time_add;*/
	if (philo->status == 1)
		philo->last_eat = t_current;
	philo->t_live = t_current - philo->last_eat;
	if (philo->t_live >= philo->rules->t_die && *philo->dead == 0)
	{
		*philo->dead = 1;
		philo->time_dead = t_current - philo->rules->t_start;
		philo->is_dead = 1;
		ft_mensage(philo->rules->t_start, philo, "died x");
		return (1);
	}
	return (0);
}

int	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo->use_fork = 1;
	if (*philo->dead == 1 || is_dead(philo))
	{
		pthread_mutex_unlock(&philo->fork);
		return (1);
	}
	if (*philo->dead == 0)
		ft_mensage(philo->rules->t_start, philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_2);
	*philo->use_fork_2 = 1;
	if (*philo->dead == 1 || is_dead(philo))
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->fork_2);
		return (1);
	}
	if (*philo->dead == 0)
		ft_mensage(philo->rules->t_start, philo, "has taken a fork");
	philo->status = 1;
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (*philo->dead == 1 || is_dead(philo))
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->fork_2);
		return (1);
	}
	if (*philo->dead == 0)
		ft_mensage(philo->rules->t_start, philo, "is eating");
	philo->eat += 1;
	//sleeping(philo->rules->t_eat);
	usleep(philo->rules->t_eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->fork_2);
	philo->use_fork = 0;
	*philo->use_fork_2 = 0;
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (*philo->dead == 1 || is_dead(philo))
		return (1);
	if (*philo->dead == 0)
		ft_mensage(philo->rules->t_start, philo, "is sleeping");
	//sleeping(philo->rules->t_sleep);
	usleep(philo->rules->t_sleep * 1000);
	if (*philo->dead == 1 || is_dead(philo))
		return (1);
	philo->status = 3;
	philo->is_thinking = 0;
	return (0);
}

int	ft_thinking(t_philo *philo)
{
	philo->is_thinking = 1;
	if (*philo->dead == 1 || is_dead(philo))
		return (1);
	if (*philo->dead == 0)
		ft_mensage(philo->rules->t_start, philo, "is thinking");
	return (0);
}

