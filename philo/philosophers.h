/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:11:06 by aserebry          #+#    #+#             */
/*   Updated: 2024/01/27 12:50:36 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

//nof - number of philsophers
//tod - time to die
//toe - time to eat
//tos - time to sleep
//nom - number of eat/meal
//st_t - time;
//eat counter - meal counter
//err_num - exit code
//mut - write
typedef struct s_base
{
	int			nof;
	int			ttd;
	int			tte;
	int			tts;
	int			nom;
	int			meal_counter;
	long long	time;
	t_mutex		mut;
	t_mutex		meal_mut;
}	t_base;

//lfork - left_f
//rfork - right_f
//final - finish act
//meals - eat_iter
//time of meal - tom - st_eat
typedef struct s_phil
{
	int			id;
	t_mutex		rfork;
	t_mutex		*lfork;
	t_mutex		get_time;
	int			meals;
	long long	start;
	long long	tom;
	int			final;
	t_base		*base;
	pthread_t	phil_thread;
}	t_phil;

int			err_exit(char err_code);
void		monitor(t_phil *philo, t_base *data);

void		*phil_lifecycle(void *phil);
t_phil		*create_phil(t_base *data);
int			create_thread(t_base *data, t_phil *phil);
void		finish_all(t_phil *phil);

int			err_msg(char *err);
long long	actual_time(void);
void		usleep_custom(long long time);
void		print_status(t_phil *ph, long long tictac, char type);

int			ft_atoi(const char *nptr);
size_t		ft_strlen(const char *s);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(long long n, int fd);

#endif