
#           TODO

## Todo

Optimize: `./philo 100 410 200 200` (school)
Optimize: `./philo 150 410 200 200` (home)
Optimize: `make && valgrind -q --tool=helgrind ./philo 4 410 200 200`

Fork taking conflict: `./philo 3 200 100 100` DONE

##  Tests

Check `must_eat`:

    ./philo 44 410 200 200 4 > out | grep -c eat

> Should return at least 44 x 4 = 176 'is eating'.

Print the two last output line of each simulation that terminate:

    while (true);
    do ./philo 200 205 100 100 > /tmp/out && tail -2 /tmp/out |tee -a out && echo "" |tee -a out;
    done
