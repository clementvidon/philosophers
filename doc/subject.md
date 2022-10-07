
#           SUBJECT

**[Original Subject](https://cdn.intra.42.fr/pdf/pdf/58800/en.subject.pdf)**

- Philosophers (at least one) sitting around a round table with pasta in the
  center.
- Philos alternatively *eat* or *think* or *sleep*.
- As many *forks* as philos.
- Each philo needs its *2 adjacent forks to eat*.
- Once *done with eating*, philos *puts down the forks* and *start sleeping*.
- Once *awake* they *start thinking* again.
- Simulation *stops if a philo dies of starvation*.

- They don't **[communicate](https://en.wikipedia.org/wiki/Dining_philosophers_problem)** with each other.
- They *don't know if one is about to die*.
- They *should never die*.

##  Program input

- `number_of_philosophers`: number of philos (also number of forks).
> Each philo *has a number* from 1 to `number_of_philosophers`. 'Philo_1' sits
> next to 'Philo_`number_of_philosophers`.'
> Any other 'Philo_N' sits between 'Philo_N-1' and 'Philo_N+1'.

- `time_to_die`: (in ms) if a philo didn't start eating `time_to_die` ms since
  the *beg of its last meal* or the *beg of the simulation*, he dies.
- `time_to_eat`: philo *eating time* (and *2 forks holding time*).
- `time_to_sleep`: philo sleeping time.
- `number_of_times_each_philosopher_must_eat`: cap the simulation before any
  death.

##  Logs

For any philo state change:

    <TS> <N> has taken a fork
    <TS> <N> is eating
    <TS> <N> is sleeping
    <TS> <N> is thinking
    <TS> <N> died

> Where <TS> is the current timestamp in ms and <N> the philo number.

- Message announcing a death should be displayed 10ms MAX after actual death.
- Philo should avoid dying.
- The program must not have any data races.

> A **data race occurs** when when one thread accesses a mutable object while
> another thread is writing to it.

##  Functions

###     string.h

Memset: `void *memset(void *s, int c, size_t n);`

Fills *the first* `n` *bytes* of the memory *area pointed to by* `s` with
the *const byte* `c`.

Return a pointer to the *memory area* `s`.


###     stdio.h

Printf: `int printf(const char *format, ...);`

###     stdlib.h

Malloc: `void *malloc(size_t size);`

Free: `void free(void *ptr);`

###     unistd.h

Write: `size_t write(int fd, const void *buf, size_t count);`

Usleep: `int usleep(useconds_t usec);`

Suspends execution of the calling thread for *(at least) usec microseconds*.
> The sleep may be lengthened slightly by any system activity or by the time
> spent processing the call or by the granularity of system timers.

Returns 0 on success,  -1 on error + set errno:
- EINTR Interrupted by a signal.
- EINVAL usec is greater than or equal to 1000000. (On systems where that is
  considered an error.)

###     sys/time.h

Gettimeofday: `int gettimeofday(struct timeval *tv, struct timezone *tz);`

Get time and timezone.

The `tv` argument is a struct that gives the number of sec and ms since the Epoch:

    struct timeval {
        time_t      tv_sec;     /* seconds */
        suseconds_t tv_usec;    /* microseconds */
    };

The `tz` argument is obsolete and should be specified as NULL.

###     pthread.h

- Threads are used to create multitasking programs.
- Compared to fork, a thread is 30 times faster.
- The number of simultaneous threads is limited to `PTHREAD_THREADS_MAX`.

Pthread_create: `int pthread_create(pthread_t *thread, const pthread_attr_t
*attr,`
                          void *(*start_routine) (void *), void *arg);

Compile and link with `-pthread`.

Starts a new thread in the calling process.
The new thread *starts execution by invoking* `start_routine()` with *arg*, its
sole argument.

The new thread *terminates if*:
- It *returns from* `start_routine()` (same as a `pthread_exit(3)`) specifying
  an exit status value available to another thread in the same process that
  calls `pthread_join(3)`.

- Any of the process threads calls `exit(3),` or the *main thread* performs a
  *return from* `main().`  -> Causes the *termination of all threads* in the
  process.

The `attr` argument points to a `pthread_attr_t` structure whose contents are
used at thread creation time to determine attributes for the new thread. If
`attr` *is NULL*, then the thread is created with *default* attributes.

Before returning, a *successful call to* `pthread_create()` stores the ID of the
new thread in the buffer pointed to by thread; this identifier is used to refer
to the thread.

Returns 0 otherwise an error number: (and `*thread` contents are undefined)
  EAGAIN Insufficient resources to create another thread.

Pthread_detach: `int pthread_detach(pthread_t thread);`

Compile and link with `-pthread`.

Marks the thread identified by thread as detached. When a detached thread
terminates, its resources are automatically released back to the system without
the need for another thread to join with the terminated thread.

Detach an *already detached* thread results = unspecified behavior.

Returns 0 otherwise an error number:
  EINVAL thread is not a joinable thread.
  ESRCH No thread with the ID thread could be found.

Pthread_join: `int pthread_join(pthread_t thread, void **retval);`

Compile and link with `-pthread`.

Waits for the thread specified by thread to terminate.
If that thread has *already terminated*, then `pthread_join()` returns immediately.
The thread specified by thread must be joinable.

If retval not NULL, *copies the exit status* of the target thread into the
*location pointed to by retval*.

If *multiple threads simultaneously try to join with the same thread* = undefined.

Returns 0 otherwise returns an error number:
  EDEADLK A deadlock was detected (e.g., two threads tried to join with each
          other); or thread specifies the calling thread.
  EINVAL  thread is not a joinable thread.
  EINVAL  Another thread is already waiting to join with this thread.
  ESRCH   No thread with the ID thread could be found.

###     pthread.h (mutex)

A mutex is a *MUTual EXclusion* device, and is useful for protecting shared data
structures from concurrent modifications, and implementing critical sections and
monitors.

A mutex has *two possible states*:
- unlocked (*not owned* by any thread)
- locked (*owned* by one thread)
A mutex *can't be owned by 2 different threads simultaneously*.
A thread attempting to *lock a mutex that is already locked* by another thread
is *suspended* until the owning thread unlocks the mutex first.

Pthread_mutex_init:

       int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);

Init the mutex object pointed to by mutex according to the mutex attributes
specified in mutexattr.
If mutexattr is NULL, default attributes are used instead.

The LinuxThreads implementation supports only one mutex attributes, the mutex
kind, which is either "*fast*", "*recursive*", or "*error checking*".
The kind of a mutex determines whether it can be locked again by a thread that
already owns it. The *default kind is "fast"*.

Variables of type pthread_mutex_t can statically init, using the consts:
 PTHREAD_MUTEX_INITIALIZER                  (for fast mutexes)
 PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP     (for recursive mutexes)
 PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP    (for error checking mutexes)

       pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;
       pthread_mutex_t recmutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
       pthread_mutex_t errchkmutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;

Always return 0.

Pthread_mutex_lock: `int pthread_mutex_lock(pthread_mutex_t *mutex);`

Locks the given mutex.
- If the mutex is *currently unlocked*, it becomes locked and owned by the
  calling thread, and `pthread_mutex_lock` returns immediately.
- If the mutex is *already locked* by another thread, `pthread_mutex_lock`
  suspends the calling thread until the mutex is unlocked.

If the mutex is already locked by the calling thread, the behavior of
`pthread_mutex_lock` depends on the kind of the mutex.
If the mutex is of the "*fast*" kind, the calling thread is suspended until the
mutex is unlocked, thus effectively causing the calling thread to *deadlock*.
If the mutex is of the "*error checking*" kind, `pthread_mutex_lock` returns
immediately with the error code *EDEADLK*.
If the mutex is of the "*recursive*" kind, `pthread_mutex_lock` succeeds and
returns immediately, recording the number of times the calling thread has locked
the mutex.
An equal number of `pthread_mutex_unlock` operations must be performed before
the mutex returns to the unlocked state.

Return 0 on success and a non-zero on error.
  EINVAL the mutex has not been properly initialized.
  EDEADLK the mutex is already locked by the calling thread ("error checking" mutexes only).

Pthread_mutex_unlock: `int pthread_mutex_unlock(pthread_mutex_t *mutex);`

Unlocks the given mutex.
The mutex is assumed to be locked and owned by the calling thread on entrance to
`pthread_mutex_unlock.`
If the mutex is of the "*fast*" kind, `pthread_mutex_unlock` always returns it to
the unlocked state.
If it is of the "*recursive*" kind, it decrements the locking count of the mutex
(number of `pthread_mutex_lock` operations performed on it by the calling thread),
and only when this count reaches zero is the mutex actually unlocked.

On "*error checking*" and "*recursive*" mutexes, `pthread_mutex_unlock` actually
checks at run-time that the mutex is locked on entrance, and that it was locked
by the same thread that is now calling `pthread_mutex_unlock.`
If these conditions are not met, an error code is returned and the mutex remains
unchanged.
"*Fast*" mutexes perform no such checks, thus allowing a locked mutex to be
unlocked by a thread **other than its owner**.
This is non-portable behavior and must not be relied upon.

Return 0 on success and a non-zero on error.
  EINVAL the mutex has not been properly initialized.
  EPERM the calling thread does not own the mutex ("error checking" mutexes only).

Pthread_mutex_destroy: `int pthread_mutex_destroy(pthread_mutex_t *mutex);`

Destroys a mutex object, freeing the resources it might hold.
The mutex must be unlocked on entrance.
In the LinuxThreads implementation, no resources are associated with mutex
objects, thus `pthread_mutex_destroy` actually *does nothing except checking that
the mutex is unlocked*.

Return 0 on success and a non-zero on error:
  EBUSY the mutex is currently locked.
