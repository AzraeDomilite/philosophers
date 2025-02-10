# Philosophers

This project is an implementation of the classic dining philosophers problem in C, demonstrating process synchronization and deadlock avoidance. It consists of two parts: mandatory (threads and mutexes) and bonus (processes and semaphores).

## The Problem

N philosophers sit at a round table with N forks placed between them. Each philosopher needs two forks to eat. The challenge is to create a solution where no philosopher starves while avoiding deadlocks.

## Features

### Mandatory Part (./philo)
- Multi-threaded implementation using pthread
- Mutex-based synchronization
- Real-time status monitoring
- Death detection system

### Bonus Part (./philo_bonus)
- Multi-process implementation using fork
- Semaphore-based synchronization
- Improved resource management
- Process-wide synchronization

## Multi-threading Challenges

### Race Conditions
When multiple threads access shared resources simultaneously, the final outcome depends on the timing of their execution. This can lead to unpredictable results and bugs that are hard to reproduce.

### Deadlocks
A situation where two or more threads are blocked forever, waiting for each other. In the philosophers' context, this happens when each philosopher holds one fork and waits for another, creating a circular wait.

### Starvation
Occurs when a thread is perpetually denied access to necessary resources. In our case, a philosopher might never get the chance to eat if their neighbors are too greedy.

### Resource Management
Proper initialization and cleanup of mutexes, semaphores, and other shared resources is crucial to prevent memory leaks and undefined behavior.

## Installation

```bash
git clone <repository-url>
cd philosophers

# For mandatory part
cd philo
make -C philo

# For bonus part
cd philo_bonus
make -C philo_bonus
```

## Usage

### Mandatory Part
```bash
./philo/philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

### Bonus Part
```bash
./philo_bonus/philo_bonus [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

### Parameters

- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die`: Time in milliseconds until a philosopher dies from starvation
- `time_to_eat`: Time in milliseconds it takes to eat
- `time_to_sleep`: Time in milliseconds spent sleeping
- `number_of_times_each_philosopher_must_eat`: (Optional) Program stops when all philosophers eat this many times

### Example

```bash
# Mandatory part
./philo/philo 5 800 200 200 5

# Bonus part
./philo_bonus/philo_bonus 5 800 200 200 5
```

## Project Structure

```
.
├── philo/          # Mandatory part
│   ├── includes/   # Header files
│   ├── src/        # Source files
│   └── Makefile    # Build configuration
├── philo_bonus/    # Bonus part
│   ├── includes/   # Header files
│   ├── src/        # Source files
│   └── Makefile    # Build configuration
└── README.md       # This file
```

## Resources

- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [POSIX Semaphores](https://man7.org/linux/man-pages/man7/sem_overview.7.html)
- [Fork System Call](https://man7.org/linux/man-pages/man2/fork.2.html)
