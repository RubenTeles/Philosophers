/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:26:03 by rteles            #+#    #+#             */
/*   Updated: 2022/07/08 17:26:34 by rteles           ###   ########.fr       */
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



typedef struct i_philosophers {
	int	number;
	int	t_die;
	int	t_eat;
	int t_sleep;
	int	n_x_eat;
}				t_philophers;

typedef struct i_time
{
	struct timeval	current;
	struct timeval	start;
	long int		time;
	long int		time_add;
	long int		last_eat;
}				t_time;

typedef struct i_philo {
	int				n;
	pthread_t		thread;
	int				status;
	int				use_fork;
	int				*use_fork_2;
	int				is_thinking;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_2;
	int				eat;
	long int		t_live;
	t_time			*t;
	t_philophers	*p;
}				t_philo;

typedef struct i_all
{
	t_time			t;
	t_philophers	p;
	t_philo			*philo;
	int				i;
}				t_all;

#endif

//	void *memset(void *b, int c, size_t len);
//	DESCRIPTION
//	     The memset() function writes len bytes of value c (converted to an unsigned char) to the string b.
//	
//	RETURN VALUES
//	     The memset() function returns its first argument.
//
//
//  int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
//  DESCRIPTION
//       The system's notion of the current Greenwich time and the current time zone is obtained with the gettimeofday() call, and set with
//       the settimeofday() call.  The time is expressed in seconds and microseconds since midnight (0 hour), January 1, 1970.  The resolu-
//       tion of the system clock is hardware dependent, and the time may be updated continuously or in ``ticks.''  If tp is NULL and tzp is
//       non-NULL, gettimeofday() will populate the timezone struct in tzp.  If tp is non-NULL and tzp is NULL, then only the timeval struct
//       in tp is populated. If both tp and tzp are NULL, nothing is returned.
//  
//       The structures pointed to by tp and tzp are defined in <sys/time.h> as:
//  
//       struct timeval {
//               time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
//               suseconds_t  tv_usec;  /* and microseconds */
//       };
//  
//       struct timezone {
//               int     tz_minuteswest; /* of Greenwich */
//               int     tz_dsttime;     /* type of dst correction to apply */
//       };
//  
//       The timeval structure specifies a time value in seconds and microseconds.  The values in timeval are opaque types whose length may
//       vary on different machines; depending on them to have any given length may lead to errors.
//  
//       The timezone structure indicates the local time zone (measured in minutes of time westward from Greenwich), and a flag that, if
//       nonzero, indicates that Daylight Saving time applies locally during the appropriate part of the year.
//  
//       Only the super-user may set the time of day or time zone.  If the system securelevel is greater than 1 (see launchd(8) ), the time
//       may only be advanced.  This limitation is imposed to prevent a malicious super-user from setting arbitrary time stamps on files.
//       The system time can still be adjusted backwards using the adjtime(2) system call even when the system is secure.
//  
//  RETURN
//       A 0 return value indicates that the call succeeded.  A -1 return value indicates an error occurred, and in this case an error code
//       is stored into the global variable errno.
//
//