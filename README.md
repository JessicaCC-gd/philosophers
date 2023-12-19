# philosophers (Project from 42 school)

## Grade: 100/100

## HOW TO USE
#### 1º - Clone the repository
```bash
git clone git@github.com:LeRandomJess/philosophers.git
```
#### 2º - Enter the project folder philo and run `make`
```bash
cd philo
make
```

#### 3º - Run the program with parameters [number_of_philosophers] [time_to_starve] [time_to_eat] [time_to_sleep] [number_of_times_to_eat]
> Time arguments are in miliseconds;
> [number_of_times_to_eat] is an optional parameter;
> [number_of_philosophers] shouldn't exceed 200;
> [time_to_starve] [time_to_eat] and [time_to_sleep] shouldn't be lower than 60;
```bash
./philo [number_of_philosophers] [time_to_starve] [time_to_eat] [time_to_sleep] [number_of_times_to_eat]

or

./philo [number_of_philosophers] [time_to_starve] [time_to_eat] [time_to_sleep]
```

#### MAKEFILE RULES

`make` - Compile all files.

`make all`  - Compile all files.

`make clean`  - Delete all .o (object files) files.

`make fclean`  - Delete all .o (object files) and .a (executable) files.

`make re` - Use rules `fclean` + `all`.
