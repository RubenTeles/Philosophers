#include "philo.h"

void	*logic(void *arg)
{		
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->last_eat = philo->t->start;
    /*if (philo->n % 2)
        usleep(15000);*/
	while (*philo->dead != 1)
	{
        if (philo->eat >= philo->rules->n_x_eat)
            break ;
		if (*philo->dead == 1 || is_dead(philo))
		{
			*philo->dead = 1;
			return (0);
		}
		if (philo->use_fork == 0 && *philo->use_fork_2 == 0 && philo->status == 3 && *philo->dead == 0)
		{
			if (*philo->dead == 1 || ft_take_forks(philo))
			{
				*philo->dead = 1;
				return (0);
			}
		}
		if (philo->status == 1 && *philo->dead == 0)
		{
			if (*philo->dead == 1 || ft_eat(philo))
			{
				*philo->dead = 1;
				return (0);
			}
			if (*philo->dead == 1 || ft_sleep(philo))
			{
				*philo->dead = 1;
				return (0);
			}
			//continue ;
		}
		else if (philo->status == 3 && philo->is_thinking == 0)
		{
			if (*philo->dead == 1 || ft_thinking(philo))
			{
				*philo->dead = 1;
				return (0);
			}
			//continue ;
		}
	}
	return (0);
}

int ft_logic(t_all *all, int i)
{
    all->t.start = time_current();
	while (++i < all->rules.number)
		pthread_create(&(all->philo[i].thread), NULL, logic, &(all->philo[i]));
	while (--i >= 0)
	{
		pthread_join(all->philo[i].thread, NULL);
		pthread_mutex_destroy(&all->philo[i].fork);
	}
	pthread_mutex_destroy(&all->speak);
	return (0);
}
