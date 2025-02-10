# Philosophers Project Architecture

## Core Architecture

### Thread Management
- Each philosopher runs in a separate thread
- One monitor thread oversees the simulation
- Thread synchronization using mutexes

### Mutex System
1. **Fork Locks**
   - One mutex per fork
   - Prevents multiple philosophers from using the same fork

2. **Print Lock**
   - Ensures atomic printing operations
   - Prevents message interleaving

3. **Meal Time Lock**
   - Protects last meal time access
   - Critical for death detection

### State Management
1. **Philosopher States**
   - Eating (requires two forks)
   - Sleeping (after eating)
   - Thinking (between sleeping and eating)

2. **Simulation States**
   - Running
   - Ended (death or meal count reached)

## Data Flow
```
main() -> init_data() -> start_philo()
                     ├─> philo threads
                     └─> monitor thread
```

## Synchronization Strategy
1. **Fork Assignment**
   - Even-numbered philosophers take left fork first
   - Odd-numbered philosophers take right fork first
   - Prevents deadlocks

2. **Timing Control**
   - Precise microsecond sleep implementation
   - Staggered start times for load balancing
