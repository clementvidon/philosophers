
#           PHILOSOPHERS 42

Solution of classical synchronization problem about
[dining philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
where each philosopher is a thread and mutexes are used to prevent deadlocks.
The code is written in accordance with The Norm (42 coding style). 

Also ***the whole code is documented with docstrings*** (start from the [header](include/philo.h) file).

[Subject dissection](doc/subject.md)

#  Usage

Run `make` in the root of the projet and launch as follows:

    ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [ <must_eat> ]

- `number_of_philosophers`: the number of philosophers and forks.
- `time_to_die`: A philosopher dies if he doesn't start eating
  `time_to_die` ms after **the beginning of his last meal** (or the simulation).
- `time_to_eat`: The time it takes for a philosopher to eat.
- `time_to_sleep`: The time it takes for a philosopher to sleep.
- `must_eat`: (optional) simulation stops if all philosophers ate at least such
  amount of times.

For example with `./philo 4 410 200 200` the dinner should never stop.

If a number of meals is not specified the simulation stops at the death of any
philosophers.

A `number_of_philosophers` > 200 and `time_to_die`/`time_to_eat`/`time_to_sleep`
< 60 ms may cause undefined behavior.

***Makefile rules***

- make -- compiles philo.
- make clean -- deletes object files.
- make fclean -- deletes object files and philo.
- make re -- fclean + make.

#  Resources

- [CodeVault](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)

- [Concurrent programming](https://begriffs.com/posts/2020-03-23-concurrent-programming.html)

#  Algo

* Philosophers

Philosophers are **named with identifier** numbers starting at 1.
We can cycle through each of them with the following formula:

    while (1)
    {
        index = (index + 1) % number_of_philosophers;
        printf ("I am %i.\n", philo[index]->id);
    }

Where `index` is equal to `philo[index]->id - 1`:

    philo[0] = 1;
    philo[1] = 2;
    philo[2] = 3;

* Forks

Each philosopher uses his own fork plus his left neighbor's one:

Philos Identifiers:

    RFork   Philo   LFork
     -------------------
      2     ← 1 →     1
      1     ← 3 →     3
      3     ← 2 →     2

To obtain the `indexes` of `philo->id`'s two forks we can use:

    LFork = philo->id - 1;
    RFork = philo->id % number_of_philosophers;

#  Optimization

1. Locking granularity:

"The **granularity of a lock is how much data it protects**. A lock with coarse
granularity will protect a large amount of data, and a lock with fine
granularity will protect a small amount of data.

Although it is tempting **to place locks at the finest level of granularity**
possible, it **is not usually the best strategy**. Having many locks with fine
granularity tends to introduce overhead. The overhead comes from the increased
amount of memory needed to hold these locks and the decreased likelihood that
the locks will be cache resident when they are needed.

However, having few locks usually results in those locks becoming contended by
multiple threads, which limits the scaling of the application. Therefore, the
granularity of the locks is usually some kind of **trade-off** between a few
contended locks and many uncontended locks. The appropriate balancing point will
**depend on the number of threads**, so it may actually change if the application
is run with different workloads of with different numbers of threads. Hence, it
is important to test an application with both representative workloads and on a
representative system with sufficient virtual CPUs.

The key to picking the **optimal locking strategy** is often a good grasp of the
**theoretical performance** of the application, in comparison with the actual
profile of the application. It is also important to examine the actual scaling
of the application as the number of threads increase."

*Source: Multicore Application Programming by Darryl Gove*

2. [Performance Analysis with Callgrind and Cachegrind](https://www.vi-hps.org/cms/upload/material/tw10/vi-hps-tw10-KCachegrind.pdf)

#  Tools

- [philosophers-visualizer](https://nafuka11.github.io/philosophers-visualizer/)

- [ft_mallocator](https://github.com/tmatis/ft_mallocator)

> Don't forget to protect '**pthread_create**', ft_mallocator won't warn you
> about this one.
>
> Don't forget to protect '**gettimeofday**', no malloc behind but easily
> crash-able from the user side.

- valgrind: `valgrind -q --tool=helgrind`
- valgrind: `valgrind -q --leak-check=yes --show-leak-kinds=all`

- sanitizer: `-fsanitize=thread`
- sanitizer: `-fsanitize=address`
# philosophers_42
