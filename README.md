Philosophers 🧘‍♂️🍝

An implementation of the classic Dining Philosophers problem for the 42 School
 curriculum.
The project explores multithreading, synchronization, and the challenges of avoiding deadlocks and race conditions.

📖 Project Overview

Five philosophers sit at a round table. Each philosopher alternates between:

Thinking 🧠

Eating 🍴 (requires two forks)

Sleeping 😴

Rules:

A philosopher can only eat when holding both forks (left and right).

Forks are shared between neighbors.

Philosophers must avoid starvation and deadlock.

The simulation ends if a philosopher dies (fails to eat within time_to_die ms) or when all have eaten must_eat_count times (if provided).

⚙️ Mandatory Part

Implemented in C with POSIX threads (pthreads).

No philosopher should starve.

Properly handle synchronization with mutexes.

Input validation.

🚀 Bonus Part

Philosophers implemented using processes and semaphores.

Each philosopher is a separate process; forks are protected with semaphores.

🛠️ Build
make            # builds the program
make clean      # removes object files
make fclean     # removes objects and binary
make re         # rebuild everything


Binary produced: ./philo

▶️ Usage
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat_count]

Arguments

number_of_philosophers (int > 0)

time_to_die (ms)

time_to_eat (ms)

time_to_sleep (ms)

must_eat_count (optional: stop when each philosopher ate N times)

Example
./philo 5 800 200 200


➡️ Runs with 5 philosophers:

die if not eating for 800ms

eating takes 200ms

sleeping takes 200ms

🧵 Implementation Notes

Mutexes for forks.

Separate threads for philosophers + one monitor thread to detect death.

Timestamps for precise timing.

Avoid busy waiting with usleep().

✅ Learning Goals

Understand deadlocks and how to avoid them.

Practice with multithreading and synchronization primitives.

Write robust and efficient C code under strict coding rules.
