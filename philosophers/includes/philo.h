/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:02:10 by blucken           #+#    #+#             */
/*   Updated: 2025/02/09 14:02:12 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                                  LIBS                                      */
/* ************************************************************************** */

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>

/* ************************************************************************** */
/*                                   CONST                                    */
/* ************************************************************************** */

# define MAX_PHILOS 200

/* ************************************************************************** */
/*                                   MODES                                    */
/* ************************************************************************** */

# ifndef COLOR_MODE
#  define COLOR_MODE 0
# endif

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

/* ************************************************************************** */
/*                               STRING MESSAGES                              */
/* ************************************************************************** */

# define USAGE_MSG			"Usage </philo <number_of_philosophers> \
								<time_to_die> <time_to_eat> <time_to_sleep> \
								[number_of_times_each_philosopher_must_eat]"
# define NON_VALID_ARGS		"Args are not vailds, please enter integers only"
# define INIT_ERROR			"Error in data init"
# define START_ERROR_MSG	"Simultation did not start properly"
# define NON_DIGIT_ARGS		"Args should be only digits"
# define PHILOS_MAX_REACH	"Please enter no more than 200 philos"
# define NO_NEG				"Args should be positives integers"
# define MALLOC_ERROR		"Error : malloc failed"
# define MUTEX_ERROR		"Error : mutex init failed"
# define THREAD_ERROR		"Error : thread create failed"

/* ************************************************************************** */
/*                                   COLORS                                   */
/* ************************************************************************** */

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define ORANGE	"\e[33m"
# define CYAN	"\e[36m"

/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_data
{
	size_t			nb_of_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				nb_time_ph_must_eat;
	pthread_t		monitor;
	bool			sim_status;
	pthread_mutex_t	*fork_locks;
	pthread_mutex_t	sim_status_lock;
	pthread_mutex_t	print_lock;
	t_philo			**philos;
	time_t			start_timer;
}	t_data;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		nb_meal_eat;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal_time;
	t_data				*data;
}	t_philo;

/* ************************************************************************** */
/*                                   STATUS                                   */
/* ************************************************************************** */

typedef enum e_status
{
	DIE = 0,
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	FORK_1 = 4,
	FORK_2 = 5
}	t_status;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */

// args_handling.c
bool	arg_valid(int ac, char **av);

// init_data.c
t_data	*init_data(char **av);

// init_philos.c
t_philo	**init_philo(t_data *data);

// start.c
bool	start_philo(t_data *data);

// monitor.c
void	*monitor(void *in_data);

// philo.c
void	*philo(void *data);
bool	all_philo_is_alive(t_data *data);

// print_output.c
void	print_output(t_philo *philo, bool monitor, t_status status);
void	print_debug(t_philo *philo, char *str, int i);
void	print_data(t_data *data);

// exit.c
void	*free_data(t_data *data);
void	stop_philo(t_data *data);

// error_handling.c
int		error_msg(char *str, int exit_nb);
void	*null_error_msg(char *str);

// utils.c
void	*set(void *vtarget, void *void_new);
bool	ft_is_str_digit(char *str);
int		ft_atoi(const char *nptr);

// time.c
time_t	get_time(void);
void	start_delay(time_t start_time);
void	philo_sleep(t_data *data, time_t sleep_time);

#endif