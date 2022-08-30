
#           TODO

##  Misc

- nb philo impaire avec t_eat > t_sleep puis t_eat= t_sleep et t_eat < t_sleep
  avec t_death = 3 fois t_eath (+ (t_eat - t_sleep) si t_sleep > t_eat) + 1ms de
  sécu (voire 2)

For an **even** `number_of_philosophers`:
`t_die` has to be at least *2 x t_eat*

    philo 2 600 100 100
          +-|---|---|-- number_of_philosophers
            +---|---|-- t_die =
                +---|-- t_eat =
                    +-- t_sleep

For **odd** `number_of_philosophers`,
`t_die` has to be at least

t_eat > t_sleep puis t_eat = t_sleep et t_eat < t_sleep

si t_sleep > t_eat
t_death = 3 fois t_eat + (t_eat - t_sleep)

si t_sleep <= t_eat
avec t_death = 3 fois t_eat

    philo 5 610 200 200

##  Issues

1. Death after eat / print after death: After a death, some actions are printed
from other philos or the dead philo himself.  Occasionally happens with extreme
parameters like:

    ./philo 200 210 100 100

2. Odd numbers of philo behave strangely:
- `./philo 3 300 100 100` -> KO (death)
- `./philo 3 399 100 100` -> KO (death)
- `./philo 3 400 100 100` -> OK

    while (true); do ./philo 100 410 200 200 > /tmp/out && tail -2 /tmp/out |tee -a out && echo "" |tee -a out; done

- `./philo 200 400 100 100`
    philo 2 200 100 100

    philo 3 300 100 100

##  Tests

Check `must_eat`:

    philo 44 410 200 200 4 > out | grep -c eat

> Should return at least 44 x 4 = 176 'is eating'.

Check 'death after eat' or 'print after death' event:

    while (true); do ./philo 200 210 100 100 > /tmp/out && tail -2 /tmp/out |tee -a out && echo "" |tee -a out; done

