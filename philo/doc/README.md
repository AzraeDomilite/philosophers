# Philosophers Project Documentation

## Overview
The Dining Philosophers Problem implementation in C. This program simulates philosophers sitting around a table, alternating between eating, thinking, and sleeping while sharing forks between them.

## Project Structure
- `src/`: Source code files
- `includes/`: Header files
- `doc/`: Documentation

## Core Components

### Data Structures
- `t_data`: Main program data structure
- `t_philo`: Individual philosopher data structure

### Key Functions
1. **Main Control**
   - `start_philo()`: Initiates the simulation
   - `stop_philo()`: Cleanly terminates the simulation
   - `monitor()`: Monitors philosophers' states

2. **Philosopher Actions**
   - `philo()`: Main philosopher routine
   - `philo_eat_sleep()`: Handles eating and sleeping
   - `philo_think()`: Handles thinking state

3. **Initialization**
   - `init_data()`: Sets up program data
   - `init_philo()`: Creates philosopher instances
   - `init_forks()`: Initializes fork mutexes

## Usage
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Error Handling
The program includes comprehensive error checking for:
- Invalid arguments
- Thread creation failures
- Memory allocation errors
- Mutex initialization failures
