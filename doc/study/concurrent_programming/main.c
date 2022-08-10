/* banker.c */

/*
 ** Concurrent programming:
 **  https://begriffs.com/posts/2020-03-23-concurrent-programming.html
 **
 ** "The amount of data that a mutex protects is called its granularity, and
 ** smaller granularity can often be more efficient." (PS. not always true)
 **
 ** TODO Concurrency problem:
 **  https://begriffs.com/posts/2017-08-01-practical-guide-sql-isolation.html
 **
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N_ACCOUNTS 10
#define N_THREADS  20
#define N_ROUNDS   10000

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))

// 10 accounts with $100 apiece means there's $1,000
// in the system. Let's hope it stays that way...

#define INIT_BALANCE 100

struct account
{
	long			balance;
	pthread_mutex_t	mtx;
}			accts[N_ACCOUNTS];

/*
 ** @brief		Help bankers to choose rand account and amount.
 **
 ** Cf. http://c-faq.com/lib/randrange.html
 */

int	ft_rand_range(int N)
{
	return ((int)((double)rand () / ((double)RAND_MAX + 1) * N));
}

/*
 ** @brief		Market Maker routine.
 **
 ** Pick distinct 'from' and 'to' accounts and operate transactions if the
 ** sender is not overdraft.
 **
 ** Each banker will run this function concurrently. The weird signature is
 ** required for a thread function.
 */

void	*ft_disburse(void *arg)
{
	size_t	i;
	size_t	from;
	size_t	to;
	long	payment;

	(void)arg;
	for (i = 0; i < N_ROUNDS; i++)
	{
		from = (size_t)ft_rand_range (N_ACCOUNTS);
		do {
			to = (size_t)ft_rand_range (N_ACCOUNTS);
		} while (to == from);

		// Get an exclusive lock on both balances before updating.
		pthread_mutex_lock(&accts[MIN(from, to)].mtx);
		pthread_mutex_lock(&accts[MAX(from, to)].mtx);
		// Overdraft security
		if (accts[from].balance > 0)
		{
			payment = 1 + ft_rand_range ((int)accts[from].balance);
			if (from == 5 || to == 5)
				dprintf (2, "Account_%i = %i	- %i	= %i	Account_%i = %i	+ %i	%i\n", (int)from, (int)accts[from].balance, (int)payment, (int)accts[from].balance - (int)payment, (int)to, (int)accts[to].balance, (int)payment, (int)accts[to].balance + (int)payment);
			accts[from].balance -= payment;
			accts[to].balance += payment;
		}
		pthread_mutex_unlock(&accts[MAX(from, to)].mtx);
		pthread_mutex_unlock(&accts[MIN(from, to)].mtx);
	}
	return (NULL);
}

int	main(void)
{
	size_t		i;
	long		total;
	pthread_t	ts[N_THREADS];

	srand ((unsigned int)time(NULL));

	for (i = 0; i < N_ACCOUNTS; i++)
	{
		accts[i].balance = INIT_BALANCE;
		pthread_mutex_init (&accts[i].mtx, NULL);
	}

	printf("Initial money in system: %d\n", N_ACCOUNTS * INIT_BALANCE);

	// Start the threads, using whatever parallelism the system happens to
	// offer. Note that pthread_create is the *only* function that creates
	// concurrency.
	for (i = 0; i < N_THREADS; i++)
		pthread_create (&ts[i], NULL, ft_disburse, NULL);

	for (i = 0; i < N_THREADS; i++)
		pthread_join (ts[i], NULL);

	for (total = 0, i = 0; i < N_ACCOUNTS; i++)
		total += accts[i].balance;

	printf ("Final money in system: %ld\n", total);
	return (0);
}
