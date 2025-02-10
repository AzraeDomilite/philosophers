/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:45:24 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 12:46:10 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* ************************************************************************** */
/*                                  LIBS                                      */
/* ************************************************************************** */

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <pthread.h>

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
# define START_ERROR_MSG	"Simulation did not start properly"
# define STOP_ERROR_MSG		"Simulation dit not stop properly"
# define NON_DIGIT_ARGS		"Args should be only digits"
# define PHILOS_MAX_REACH	"Please enter no more than 200 philos"
# define NO_NEG				"Args should be positives integers"
# define MALLOC_ERROR		"Error : malloc failed"
# define MUTEX_ERROR		"Error : mutex init failed"
# define THREAD_ERROR		"Error : thread create failed"
# define FORK_ERROR			"Error : fork failed"
# define SEM_ERROR			"Error : semaphore failed"
/* ************************************************************************** */
/*                                OUTPUT CODES                                */
/* ************************************************************************** */

# define CHILD_EXIT_PTHREAD_ERROR	3
# define CHILD_EXIT_SEM_ERROR		4
# define CHILD_EXIT_FULL			5
# define CHILD_EXIT_DEAD			6

/* ************************************************************************** */
/*                             SEMAPHORES NAMES                               */
/* ************************************************************************** */

# define SEM_NAME_FORKS "/philo_forks"
# define SEM_NAME_WRITE "/philo_write"
# define SEM_NAME_FULL	"/philo_full"
# define SEM_NAME_DEAD	"/philo_dead"
# define SEM_NAME_STOP	"/philo_stop"
# define SEM_NAME_MEAL	"/philo_meal"

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
	time_t			start_timer;
	size_t			nb_of_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				nb_time_ph_must_eat;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_philo_full;
	unsigned int	philo_full_count;
	sem_t			*sem_philo_dead;
	sem_t			*sem_stop;
	bool			sim_status;
	t_philo			**philos;
	t_philo			*current_philo;
	pid_t			*pids;
	pthread_t		ate_enought_monitor;
	pthread_t		death_monitor;
}	t_data;

typedef struct s_philo
{
	pthread_t			monitor;
	sem_t				*sem_forks;
	sem_t				*sem_write;
	sem_t				*sem_philo_full;
	sem_t				*sem_philo_dead;
	sem_t				*sem_meal;
	char				*sem_meal_name;
	unsigned int		nb_forks_held;
	unsigned int		id;
	unsigned int		nb_meal_eat;
	bool				ate_enough;
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

// args_handler.c
bool	arg_valid(int ac, char **av);

// error_handling.c
void	*null_error_msg(char *str);
int		error_msg(char *str, int exit_nb);
void	child_exit(t_data *data, int exit_code);
int		error_failure(char *str, t_data *data);

// exit.c
bool	has_simulation_stopped(t_data *data);
int		stop_philo(t_data *data);
void	cleanup_zombies(t_data *data);

// free.c
void	*free_data(t_data *data);
int		sem_error_cleanup(t_data *data);
int		data_cleanup(t_data *data, int exit_code);

// init_data.c
t_data	*init_data(char **av);
bool	init_sem(t_data *data);

//init_monitor_sem.c
void	init_monitor_sem(t_data *data, t_philo *philo);

// init_philo.c
bool	start_philo(t_data *data);

// monitors.c
int		kill_all_philos(t_data *data, int exit_code);
void	*ate_enought_monitor(void *data_monitor);
void	*death_monitor(void *data_monitor);
bool	tread_monitor(t_data *data);

// one_philo.c
void	one_philo(t_philo *philo);

// philo_monitor.c
void	*philo_monitor(void *data_monitor);

// philo.c
void	philo(t_data *data);

// print_output.c
void	print_output(t_philo *philo, bool monitor, t_status status);
void	print_status(t_philo *philo, char *str, char *color);

// sem_names.c
bool	set_names(t_philo *philo);

// time.c
time_t	get_time(void);
void	start_delay(time_t start_time);
void	philo_sleep(time_t sleep_time);

// utils.c
size_t	ft_strlen(const char *s);
char	*ft_strcat(char	*dst, const char *src);
char	*ft_utoa(unsigned int nb, size_t len);
void	*set(void *vtarget, void *void_new);

// utils2.c
void	unlink_sems(void);
bool	ft_is_str_digit(char *str);
int		ft_atoi(const char *nptr);

#endif