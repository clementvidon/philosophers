<h1 align="center">
	PHILOSOPHERS 42
</h1>

<h3 align="center">
	<a href="#Summary">Summary</a>
	<span> · </span>
	<a href="#Usage">Usage</a>
	<span> · </span>
	<a href="#Resources">Resources</a>
	<span> · </span>
	<a href="#Algo">Algo</a>
	<span> · </span>
	<a href="#Optimization">Optimization</a>
	<span> · </span>
	<a href="#Tools">Tools</a>
	<span> · </span>
	<a href="#helgrind-tutor">Helgrind tutor</a>
</h3>

##  Summary

Solution of classical synchronization problem about
[dining philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
where each philosopher is a thread and mutexes are used to prevent deadlocks. - **[detailed subject](doc/subject.md)** 

The code is written in accordance with 42 C coding style and ***all the functions are documented with docstrings*** (start from the **[header](include/philo.h)** file). 

##  Usage

Run `make` in the root of the projet and launch as follows:

    ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [ <must_eat> ]

- `number_of_philosophers` -- the number of philosophers and forks.
- `time_to_die` -- A philosopher dies if he doesn't start to eat `time_to_die`
  ms after **the beginning of his last meal** (or the simulation).
- `time_to_eat` -- The time it takes for a philosopher to eat.
- `time_to_sleep` -- The time it takes for a philosopher to sleep.
- `must_eat` -- (optional) simulation stops if all philosophers ate at least such
  amount of times.

For example with `./philo 4 410 200 200` the dinner should never stop.

If a number of meals is not specified the simulation stops at the death of any
philosophers.

A `number_of_philosophers` > 200 and `time_to_die`/`time_to_eat`/`time_to_sleep`
< 60 ms may cause undefined behavior.

***Makefile rules***

- `make` -- compiles philo.
- `make clean` -- deletes object files.
- `make fclean` -- deletes object files and philo.
- `make re` -- `fclean` + `make`.

- `make update` -- update the repo to its newer version.
- `make norm` -- check 42 C coding style.

##  Resources

- **[CodeVault](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)**<br>
- **[Concurrent programming](https://begriffs.com/posts/2020-03-23-concurrent-programming.html)**<br>

##  Algo

* **Philosophers**

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

* **Forks**

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

##  Optimization

1. **Locking granularity**:

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

2. **[Performance Analysis with Callgrind and Cachegrind](https://www.vi-hps.org/cms/upload/material/tw10/vi-hps-tw10-KCachegrind.pdf)**

##  Tools

- **[philosophers-visualizer](https://nafuka11.github.io/philosophers-visualizer/)**

###  Memory

- **[ft_mallocator](https://github.com/tmatis/ft_mallocator)**

> Don't forget to protect '**pthread_create**', ft_mallocator won't warn you
> about this one.
>
> Don't forget to protect '**gettimeofday**', no malloc behind but easily
> crash-able from the user side.

- **valgrind**: `valgrind -q --leak-check=yes --show-leak-kinds=all`

###  Thread

- **sanitizer**: `-fsanitize=thread`

- **valgrind**: `valgrind -q --tool=helgrind`

##  Helgrind tutor

How to track and fix a data race?

1. **Output example**

`DATA RACE` and `CONFLICTS` are the main terms that interest us `1>` in the
output of helgrind, `utils.c:35` and `utils.c:40` the location of the two
variables that he indicates to us as being in conflict and that we must protect
with a mutex `2>`.

    1> ==174034== Possible DATA RACE during write of size 1 at 0x4A44062 by thread #1
       ==174034== Locks held: none
    2> ==174034==    at 0x40262C: ft_died (simulator_utils.c:47)
       ==174034==    by 0x401C81: ft_monitor (simulator.c:93)
       ==174034==    by 0x401B14: ft_simulator (simulator.c:132)
       ==174034==    by 0x4012B8: main (main.c:79)
       ==174034==
    1> ==174034== This CONFLICTS with a previous read of size 1 by thread #4
       ==174034== Locks held: 3, at addresses 0x4A44128 0x4A44250 0x4A442A0
    2> ==174034==    at 0x40240C: ft_msleep (time_utils.c:77)
       ==174034==    by 0x402093: ft_eating (simulation.c:103)
       ==174034==    by 0x401F0A: ft_simulation (simulation.c:136)
       ==174034==    by 0x483F876: mythread_wrapper (hg_intercepts.c:387)
       ==174034==    by 0x4862EA6: start_thread (pthread_create.c:477)
       ==174034==    by 0x4979DEE: clone (clone.S:95)
       ==174034==  Address 0x4a44062 is 34 bytes inside a block of size 48 alloc'd
       ==174034==    at 0x48397CF: malloc (vg_replace_malloc.c:307)
       ==174034==    by 0x401930: ft_init (init.c:114)
       ==174034==    by 0x401289: main (main.c:77)
       ==174034==  Block was alloc'd by thread #1

2. **Fix example**<br>

At `simulator_utils.c:47` we have:

    data->died = true;

That can be protected like this:

    pthread_mutex_lock (&data->mutex[DIED]);
    data->died = true;
    pthread_mutex_unlock (&data->mutex[DIED]);

At `time_utils.c:47` we have:

    if (philo->data->died)
        return ;

That can be protected like this:

    pthread_mutex_lock (&philo->data->mutex[DIED]);
    if (philo->data->died)
        return ((void)pthread_mutex_unlock (&philo->data->mutex[DIED]));
    pthread_mutex_unlock (&philo->data->mutex[DIED]);

Or like this:

    int died;
    pthread_mutex_lock (&philo->data->mutex[DIED]);
    died = philo->data->died;
    pthread_mutex_unlock (&philo->data->mutex[DIED]);
    if (died)
       return ;
