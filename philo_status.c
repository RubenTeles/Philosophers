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

	t_current = time_current();
	philo->t_live = t_current - philo->last_eat;
	if (philo->t_live >= philo->rules->t_die && *philo->dead == 0)
	{
		pthread_mutex_lock(&philo->rules->m_dead);
		if (*philo->dead == 1)
			return (1);
		*philo->dead = 1;
		philo->time_dead = t_current - philo->rules->t_start;
		printf("%lli %i %s\n", philo->time_dead, philo->n, "died");
		pthread_mutex_unlock(&philo->rules->m_dead);
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
	if (*philo->dead == 0)
		ft_mensage(philo->rules->t_start, philo, "is eating");
	if (smart_sleep(philo->rules->t_eat, philo) || *philo->dead == 1
		|| is_dead(philo))
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->fork_2);
		return (1);
	}
	philo->last_eat = time_current();
	philo->eat += 1;
	philo->use_fork = 0;
	*philo->use_fork_2 = 0;
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (philo->eat < 1)
		return (0);
	if (*philo->dead == 1 || is_dead(philo))
		return (1);
	if (*philo->dead == 0)
		ft_mensage(philo->rules->t_start, philo, "is sleeping");
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->fork_2);
	if (smart_sleep(philo->rules->t_sleep, philo) || *philo->dead == 1
		|| is_dead(philo))
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
