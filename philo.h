/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:26:03 by rteles            #+#    #+#             */
/*   Updated: 2022/07/22 21:56:57 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct i_rules {
	pthread_mutex_t	m_dead;
	long int		t_start;
	int				number;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_x_eat;
}				t_rules;

typedef struct i_philo {
	int				n;
	pthread_t		thread;
	int				status;
	int				use_fork;
	int				*use_fork_2;
	long int		last_eat;
	int				eat;
	long int		t_live;
	int				is_thinking;
	int				is_dead;
	long long		time_dead;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_2;
	int				*dead;
	pthread_mutex_t	*speak;
	t_rules			*rules;
}				t_philo;

typedef struct i_all
{
	t_rules			rules;
	t_philo			*philo;
	int				i;
	int				*dead;
	pthread_mutex_t	speak;
}				t_all;

//------ Utils -----//
int			ft_atoi(char *str);
int			ft_str_s_str(char *s1, char *s2);
void		sleeping(int time_max);
long long	time_current(void);
void		ft_mensage(long long t_start, t_philo *philo, char *status);
int			smart_sleep(long long time, t_philo *philo);

//------ Init -----//
int			ft_organize_philosophers(t_all *all, int argc, char **argv, int i);
int			ft_rules(t_rules *rules, int argc, char **argv);
void		ft_philosophers(t_philo *philo, t_philo *philo_2);

//------ Logic -----//
int			ft_logic(t_all *all, int i);
void		*logic(void *arg);

//------ Status -----//
int			is_dead(t_philo *philo);
int			ft_take_forks(t_philo *philo);
int			ft_eat(t_philo *philo);
int			ft_sleep(t_philo *philo);
int			ft_thinking(t_philo *philo);

#endif

/*	void *memset(void *b, int c, size_t len);
	DESCRIPTION
	     The memset() function writes len bytes of value c (converted to an unsigned char) to the string b.
	
	RETURN VALUES
	     The memset() function returns its first argument.


  int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
  DESCRIPTION
       The system's notion of the current Greenwich time and the current time zone is obtained with the gettimeofday() call, and set with
      the settimeofday() call.  The time is expressed in seconds and microseconds since midnight (0 hour), January 1, 1970.  The resolu-
      tion of the system clock is hardware dependent, and the time may be updated continuously or in ``ticks.''  If tp is NULL and tzp is
      non-NULL, gettimeofday() will populate the timezone struct in tzp.  If tp is non-NULL and tzp is NULL, then only the timeval struct
      in tp is populated. If both tp and tzp are NULL, nothing is returned.
  
       The structures pointed to by tp and tzp are defined in <sys/time.h> as:
  
       struct timeval {
               time_t       tv_sec;    seconds since Jan. 1, 1970 
               suseconds_t  tv_usec;   and microseconds 
       };
  
       struct timezone {
               int     tz_minuteswest;  of Greenwich 
               int     tz_dsttime;      type of dst correction to apply 
       };
  
       The timeval structure specifies a time value in seconds and microseconds.  The values in timeval are opaque types whose length may
       vary on different machines; depending on them to have any given length may lead to errors.
  
       The timezone structure indicates the local time zone (measured in minutes of time westward from Greenwich), and a flag that, if
       nonzero, indicates that Daylight Saving time applies locally during the appropriate part of the year.
  
       Only the super-user may set the time of day or time zone.  If the system securelevel is greater than 1 (see launchd(8) ), the time
       may only be advanced.  This limitation is imposed to prevent a malicious super-user from setting arbitrary time stamps on files.
       The system time can still be adjusted backwards using the adjtime(2) system call even when the system is secure.
  
  RETURN
       A 0 return value indicates that the call succeeded.  A -1 return value indicates an error occurred, and in this case an error code
       is stored into the global variable errno.
*/
