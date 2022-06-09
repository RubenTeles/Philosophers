/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:52:03 by rteles            #+#    #+#             */
/*   Updated: 2022/06/09 17:04:04 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*myturn(void *arg)
{
	int	*x;
	int	*result;

	x = (int *)arg;
	result = (int *)malloc(sizeof(int));
	while (*x < 20)
	{
		usleep(100000);
		printf("\033[1;32mMy Turn\033[0m %i\n", *x);
		(*x)++;
	}
	*result = *x * 2;
	return (result);
}

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

int	main(int argc, char **argv)
{
	pthread_t	newthread;
	int			x;
	int			*result;

	x = 0;
	pthread_create(&newthread, NULL, myturn, &x);
	yourturn();
	pthread_join(newthread, (void *)&result);
	printf("Result: %i\n", *result);
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