/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:47:10 by jocorrea          #+#    #+#             */
/*   Updated: 2023/09/17 16:21:51 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct	s_philo
{
	int				id;
	int				eating;
	int				meal_eaten;
	int				*dead;
	int				*num_philo;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
}				t_philo;

typedef struct	s_program
{
	int				is_dead;
	int				num_philos;
	int				num_time_eat;
	t_philo			*philos;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}				t_program;


int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int	check_input(char **argv);
int	init_program(t_program *program, char **argv);
int	create_threads(t_program *prog);
int	ft_sleep(size_t milliseconds);
void	print_message(char *str, t_philo *philo);

void	think(t_philo philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);
void	destroy_all(char *str, t_program *program);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
int		is_alive(t_philo *philo);
#endif
