
#           ISSUES

TODO
Check if there are no '**death after eat**' or '**print after death**' event:

    while (1); do ./philo 200 400 100 100 > /tmp/out && tail -2 /tmp/out |tee -a out && echo "" |tee -a out; done
    while (1); do ./philo 100 410 200 200 > /tmp/out && tail -2 /tmp/out |tee -a out && echo "" |tee -a out; done

Check **must_eat**:

    philo 44 410 200 200 4 > out | grep -c eat

> Should return at least 44 x 4 = 176 'is eating'.



For an **even** `number_of_philosophers`, `time_to_die` has to be at least… TODO

    philo 2 200 100 100

For **odd** `number_of_philosophers`, `time_to_die` has to be at least… TODO

    philo 3 400 100 100
    philo 5 610 200 200

