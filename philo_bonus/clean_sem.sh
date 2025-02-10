#!/bin/bash

sem_names=(
    "sem.philo_forks"
    "sem.philo_write"
    "sem.philo_full"
    "sem.philo_dead"
    "sem.philo_stop"
    "sem.philo_meal"
)

for name in "${sem_names[@]}"; do
    sem_path="/dev/shm/$name"
    if [ -f "$sem_path" ]; then
        rm "$sem_path"
        echo "Removed semaphore: $name"
    fi
done

ls -l /dev/shm/philo_* 2>/dev/null

echo "Semaphore cleanup complete!"
