# Philosophers Project

## Introduction
The Philosophers project is part of the curriculum at 42 School, focusing on solving the Dining Philosophers problem using concurrency and synchronization techniques. The project aims to help students understand the challenges of resource sharing and deadlock prevention in multi-threaded environments.

## Project Description
In this project, you will simulate a group of philosophers who alternate between thinking and eating. Each philosopher needs two forks to eat, and there is a limited number of forks. The goal is to ensure that no philosopher starves, and that the solution avoids deadlock and resource contention issues.

### Objectives
- Implement a solution to the Dining Philosophers problem.
- Use mutexes for synchronization.
- Ensure that no two philosophers access the same fork simultaneously.
- Prevent deadlock and starvation.

## Requirements
- A UNIX-like operating system (Linux or macOS recommended).
- Knowledge of C programming and POSIX threads.
- Basic understanding of concurrency and synchronization concepts.

## Installation
Follow these steps to set up the project locally:

1. **Clone the Repository:**
   ```bash
   git clone git@github.com:dwbessa/42cursus_philosophers.git
   cd philo
   make
   ```

2. **Follow the requirements of the program, example**
- ./philo 4 310 200 100 [7]
- 4 being the number of Philosophers (threads)
- 310 being the time to 'die' (if don't 'eat')
- 200 being the time to 'eat'
- 100 being the time to 'sleep'
- Optional: 7 being the number of times each philosopher eat
- Try custom inputs, like ./philo 5 800 200 200 (infinite loop, no philosopher die)
