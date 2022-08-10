#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PH_NUM 3

typedef	struct s_philo
{
	int	age;
}               t_philo;

typedef	struct s_data
{
	t_philo	*ph;
	int		id;
}               t_data;

void	test(t_data dat)
{

	// 1. Last element
	// ---------------

	printf("1. %i\n", dat.ph[0].age); 		//> 1
	printf("1. %i\n", dat.ph[1].age); 		//> 2
	printf("1. %i\n", dat.ph[2].age); 		//> 3
	printf("1. %i\n", dat.ph[3].age); 		//> -1094795586
    // We notice that the 4th element is not set to NULL.

	// while (dat.ph)
	// {
	// 	printf("> %i\n", (*dat.ph).age);
	// 	dat.ph++;
	// }
	//
	// Segfault because dat.ph[3] is NOT set to NULL and isn't a s_data.


	// 2. Dereferencement notations
	// ----------------------------

	for (int i = 0; i < PH_NUM; i++)
		printf("2. subscript notation > %i\n", dat.ph[i].age);

	for (int i = 0; i < PH_NUM; i++)
		printf("2. pointer notation   > %i\n", (*(dat.ph + i)).age);

	free (dat.ph);
}

int	main(void)
{
	t_data	dat;

	dat.id = 1;
	dat.ph = malloc(sizeof(dat.ph) * PH_NUM);

	for (int i = 0; i < PH_NUM; i++)
		dat.ph[i].age = i + 1;

	test (dat);
	return (0);
}
