#include <string.h>
#include <time.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/wait.h>
#include <errno.h>

/* Define */
#define F __func__
#define L __LINE__

#define X __FILE__, __func__, __LINE__

void	ft_exit(const char *file, const char *func, int line)
{
	printf ("\033[0;31m");
	printf ("Error in %s: %s: l.%i\n", file, func, line);
	printf ("\033[0m");
	exit (1);
}

/*
 ** 01 - Youtube/CodeVault/Short introduction to threads (pthreads)
 ** ===============================================================
 **
 ** When we create a thread it executes a function so we need a default routine.
 **
 ** - 'pthread_join' for threads what is 'wait' for forks.
 */

void	*ft_routine_01()
{
	printf ("Test from threads\n");
	sleep (1);
	printf ("Ending thread\n");
	return (NULL);
}

int	ft_thread_01(void)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create (&t1, NULL, &ft_routine_01, NULL))
		ft_exit (X);
	if (pthread_create (&t2, NULL, &ft_routine_01, NULL))
		ft_exit (X);
	if (pthread_join (t1, NULL))
		ft_exit (X);
	if (pthread_join (t2, NULL))
		ft_exit (X);
	return (0);
}

int	ft_main_01(void)
{
	ft_thread_01 ();
	return (0);
}

/*
 ** 02 - Youtube/CodeVault/Difference between processes and threads
 ** ===============================================================
 **
 ** When we create a thread it executes a function so we need a default routine.
 **
 ** Different process = different PIDs
 ** Different thread  = same PIDs
 **
 ** We can have multiple thread in one process.
 ** We can NOT have multiple process in one thread.
 **
 ** Threads share the same memory space.
 ** Processes duplicate the memory space.
 */

int	ft_process_02(void)
{
	int	pid;
	int	x;

	pid = fork ();
	if (pid == -1)
		ft_exit (X);
	x = 0;
	if (pid == 0)
		x++;
	sleep (1);
	printf ("Hello from process %i where x=%i\n", getpid (), x);
	if (pid)
		wait (NULL);
	return (0);
}

int x02 = 2;

void	*routine_02_2()
{
	x02++;
	sleep (1);
	printf ("Hello from thread %i, where x02=%i\n", getpid (), x02);
	return (NULL);
}

void	*routine_02()
{
	sleep (1);
	printf ("Hello from thread %i, where x02=%i\n", getpid (), x02);
	return (NULL);
}

int	ft_thread_02(void)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create (&t1, NULL, &routine_02, NULL))
		ft_exit (X);
	if (pthread_create (&t2, NULL, &routine_02_2, NULL))
		ft_exit (X);
	if (pthread_join (t1, NULL))
		ft_exit (X);
	if (pthread_join (t2, NULL))
		ft_exit (X);
	return (0);
}
int	ft_main_02(void)
{
	ft_thread_02();
	ft_process_02();
	return (0);
}

/*
 ** 03 - Youtube/CodeVault/What are Race Conditions?
 ** ================================================
 **
 ** Race condition happens because the t1 routine is still running
 ** while t2 routine is starting causing an interleaving.
 **
 ** Race condition can only occur on multi-core processor.
 **
 ** mails = 1;
 **              t1   t2       t1   t2
 **              excpect       happens
 ** read mails   23   24       29   23
 ** increment    23   24       29   30 (mails value)
 ** write mails  24   25       30   24 (23+1)
 **
 ** mails = 24;
 **
 */

int mails03 = 0;

void	*routine_03()
{
	for (int i = 0; i < 100000; i++)
		mails03++;
	// read mails
	// increment
	// write mails
	return (NULL);
}

int	ft_thread_03(void)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create (&t1, NULL, &routine_03, NULL))
		ft_exit (X);
	if (pthread_create (&t2, NULL, &routine_03, NULL))
		ft_exit (X);
	if (pthread_join (t1, NULL))
		ft_exit (X);
	if (pthread_join (t2, NULL))
		ft_exit (X);
	printf ("Number of mails: %i\n", mails03);
	return (0);
}

int	ft_main_03(void)
{
	ft_thread_03();
	return (0);
}

/*
 ** 04 - Youtube/CodeVault/What is a mutex in C? (pthread_mutex)
 ** ================================================
 **
 ** - Solve race condition.
 **
 ** If a thread is executing the lines of code between 'mutex_lock' and
 ** and 'mutex_unlock' not any other thread will be able to execute it too.
 **
 ** The trade off is that mutex make the execution slower.
 */

int mails04 = 0;
pthread_mutex_t mutex04;

void	*routine_04()
{
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex04);	// TODO
		mails04++;
		pthread_mutex_unlock(&mutex04);	// TODO
	}
	return (NULL);
}

int	ft_thread_04(void)
{
	pthread_t	t1;
	pthread_t	t2;
	pthread_t	t3;

	pthread_mutex_init (&mutex04, NULL);	// TODO
	if (pthread_create (&t1, NULL, &routine_04, NULL))
		ft_exit (X);
	if (pthread_create (&t2, NULL, &routine_04, NULL))
		ft_exit (X);
	if (pthread_create (&t3, NULL, &routine_04, NULL))
		ft_exit (X);
	if (pthread_join (t1, NULL))
		ft_exit (X);
	if (pthread_join (t2, NULL))
		ft_exit (X);
	if (pthread_join (t3, NULL))
		ft_exit (X);
	pthread_mutex_destroy (&mutex04);		// TODO
	printf ("Number of mails: %i\n", mails04);
	return (0);
}

int	ft_main_04(void)
{
	ft_thread_04();
	return (0);
}

/*
 ** 05 - Youtube/CodeVault/How to create threads in a loop (pthread_create)
 ** =======================================================================
 **
 */

int mails05 = 0;
pthread_mutex_t mutex05;

void	*routine_05()
{
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex05);
		mails05++;
		pthread_mutex_unlock(&mutex05);
	}
	return (NULL);
}

int	ft_thread_05(void)
{
	pthread_t	th[8];
	int			i;

	pthread_mutex_init (&mutex05, NULL);
	// Create all the threads
	for (i = 0; i < 4; i++) {
		if (pthread_create (&th[i], NULL, &routine_05, NULL))
			ft_exit (X);
		dprintf (2, "Thread %d has started\n", i);
	}
	// Wait for each of them to finish
	for (i = 0; i < 4; i++) {
		if (pthread_join (th[i], NULL))
			ft_exit (X);
		dprintf (2, "Thread %d has finished\n", i);
	}
	pthread_mutex_destroy (&mutex05);
	printf ("Number of mails: %i\n", mails05);
	return (0);
}

int	ft_main_05(void)
{
	ft_thread_05();
	return (0);
}

/*
 ** 06 - Youtube/CodeVault/Get return value from a thread (pthread_join)
 ** ====================================================================
 **
 */

void	*roll_dice_06()
{
	int	value;
	int	*result;

	value = (rand () % 6) + 1;
	result = malloc (sizeof (int));
	*result = value;
	dprintf (2, "Thread result: %p\n", result);
	return ((void *) result);
}

int	ft_thread_06(void)
{
	int	*res;
	srand ((unsigned int)time (NULL));
	pthread_t	th;

	if (pthread_create (&th, NULL, &roll_dice_06, NULL))
		ft_exit (X);

	if (pthread_join (th, (void **) &res))
		ft_exit (X);

	dprintf (2, "Main res: %p\n", res);
	dprintf (2, "The result is: %d\n", *res);
	free (res);
	return (0);
}

int	ft_main_06(void)
{
	ft_thread_06();
	return (0);
}

/*
 ** 07 - Youtube/CodeVault/How to pass arguments to threads in C
 **
 */

int	primes07[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void	*routine07(void *arg)
{
	int	index;

	index = *(int *) arg;
	dprintf (2, "%d \n", primes07[index]);
	free (arg); // free 'a'
	return (NULL);
}

int	ft_thread_07(void)
{
	pthread_t	th[10];
	int			*a;

	for (int i = 0; i < 10; i++)
	{
		// We malloc our argument variable to prevent it to change during the
		// execution of the threads like this would happen by passing 'i'
		// directly.
		a = malloc (sizeof (int));
		*a = i;
		if (pthread_create (&th[i], NULL, &routine07, a))
			ft_exit (X);
		// We can't 'free a' cause maybe the thread exec is not done.
	}
	for (int i = 0; i < 10; i++)
	{
		if (pthread_join (th[i], NULL))
			ft_exit (X);
	}
	return (0);
}

int	ft_main_07(void)
{
	ft_thread_07();
	return (0);
}

/*
 ** 08 - Youtube/CodeVault/Practical example for using threads #1
 ** (Summing numbers from an array)
 **
 ** Two threads that each compute the sum of an half of the given array, both
 ** result are then auditioned to return the global sum.
 */

int	primes08[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void	*routine08(void *arg)
{
	int	index;
	int	sum;

	index = *(int *) arg;
	sum = 0;
	for (int j = 0; j < 5; j++)
		sum += primes08[index + j];
	dprintf (2, "Local sum: %i\n", sum);
	*(int *) arg = sum;
	return (arg);
}

int	ft_thread_08(void)
{
	pthread_t	th[2];
	int			*a;
	int			global_sum;

	for (int i = 0; i < 2; i++)
	{
		a = malloc (sizeof (int));
		*a = i * 5;
		if (pthread_create (&th[i], NULL, &routine08, a))
			ft_exit (X);
	}
	global_sum = 0;
	for (int i = 0; i < 2; i++)
	{
		int	*res;
		if (pthread_join (th[i], (void **) &res))
			ft_exit (X);
		global_sum += *res;
		free (res);
	}
	dprintf (2, "Global Sum %i\n", global_sum);
	return (0);
}

int	ft_main_08(void)
{
	ft_thread_08();
	return (0);
}

/*
 ** 09 - Youtube/CodeVault/Difference between trylock and lock in C
 **      (pthread_mutex_trylock())
 **
 ** Lock is always going to wait until mutex is unlocked.
 ** Trylock will not wait but return a non-zero value.
 */

pthread_mutex_t mutex09;

void	*routine09(void *arg)
{
	if (pthread_mutex_trylock (&mutex09) == 0)
	{
		printf("Got lock cause trylock return 0\n");
		sleep(1);
		pthread_mutex_unlock (&mutex09);
	}
	else
	{
		dprintf (2, "Didn't get lock cause trylock return non-zero\n");
	}
	return (arg);
}

int	ft_thread_09(void)
{
	pthread_t	th[4];

	pthread_mutex_init(&mutex09, NULL);
	for (int i = 0; i < 4; i++)
	{
		if (pthread_create (&th[i], NULL, &routine09, NULL))
			ft_exit (X);
	}
	for (int i = 0; i < 4; i++)
	{
		if (!pthread_join (th[i], NULL))
			ft_exit (X);
	}
	pthread_mutex_destroy(&mutex09);
	return (0);
}

int	ft_main_09(void)
{
	ft_thread_09();
	return (0);
}

/*
 ** 10 - Youtube/CodeVault/Condition variables in C
 ** 11 - Youtube/CodeVault/Signaling for condition variables
 **      (pthread_cond_signal vs pthread_cond_broadcast)
 ** 12 - Youtube/CodeVault/Practical example for pthread_mutex_trylock
 ** 13 - Youtube/CodeVault/What is pthread_exit?
 ** 14 - Youtube/CodeVault/Introduction to barriers (pthread_barrier)
 ** 15 - Youtube/CodeVault/Practical example to barriers (pthread_barrier)
 ** 16 - Youtube/CodeVault/What is pthread_t?
 ** 17 - Youtube/CodeVault/What are detached threads?
 ** 18 - Youtube/CodeVault/Static initializers in the PTHREAD API
 **
 **
 */

/*
 ** 19 - Youtube/CodeVault/Deadlocks in C
 **
 ** Deadlock occurs when we lock twice on the same thread.
 ** The program never finishes execution.
 **
 */

#define THREAD_NUM 8

pthread_mutex_t mutexFuel19;
int	fuel = 50;
pthread_mutex_t mutexWater19;
int	water = 50;

void	*routine19(void *arg)
{
	if (rand() % 2 == 0)
	{
		pthread_mutex_lock (&mutexFuel19);
		sleep (1/10);
		pthread_mutex_lock (&mutexWater19);
	}
	else
	{
		pthread_mutex_lock (&mutexWater19);
		sleep (1/10);
		pthread_mutex_lock (&mutexFuel19);
	}
	// A deadlock is when every thread are waiting for each other.
	//
	//        Fuel    Water
	//        Mutex   Mutex
	//
	//   Th1    X     wait
	//
	//   Th2  wait     X
	//
	fuel += 50;
	water = fuel;
	dprintf (2, "Incremented fuel to: %i\n", fuel);
	dprintf (2, "Set water to: %i\n", water);
	pthread_mutex_unlock (&mutexFuel19);
	pthread_mutex_unlock (&mutexWater19);
	return (arg);
}

int	ft_thread_19(void)
{
	pthread_t	th[THREAD_NUM];

	pthread_mutex_init (&mutexFuel19, NULL);
	for (int i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create (&th[i], NULL, &routine19, NULL))
			ft_exit (X);
	}
	for (int i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join (th[i], NULL))
			ft_exit (X);
	}
	printf("Fuel: %i\n", fuel);
	printf("Water: %i\n", fuel);
	pthread_mutex_destroy(&mutexFuel19);
	pthread_mutex_destroy(&mutexWater19);
	return (0);
}

int	ft_main_19(void)
{
	ft_thread_19();
	return (0);
}

/*
 ** TODO continue: https://www.youtube.com/watch?v=Ot-VR3jzQMY&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=20
 */

//////////////
int	main(void)
{
	ft_main_19();
}
