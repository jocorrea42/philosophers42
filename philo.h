/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:47:10 by jocorrea          #+#    #+#             */
/*   Updated: 2023/09/24 13:59:59 by jocorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eating;
	int				meal_eaten;
	int				*dead;
	int				*num_philo;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_t		thread;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				is_dead;
	int				nphilos;
	int				time_eat;
	t_philo			*philos;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}	t_program;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		check_input(char **argv);
int		init_program(t_program *program, char **argv);
int		create_threads(t_program *prog);
int		philosopher_dead(t_philo *philo);
int		ft_usleep(size_t milliseconds);
int		is_alive(t_philo *philo);
void	print_message(char *str, t_philo *philo);
void	think(t_philo philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);
void	*monitor(void *ptr);
void	destroy_all(char *str, t_program *program);
size_t	get_time(void);
#endif
