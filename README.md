<b>philosophers</b>

Here are the things you need to know if you want to succeed this assignment:<br>
• One or more philosophers sit at a round table.<br>
There is a large bowl of spaghetti in the middle of the table.<br>
• The philosophers alternatively eat, think, or sleep.<br>
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.<br>
• There are also forks on the table. There are as many forks as philosophers.<br>
• Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.<br>
• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.<br>
• Every philosopher needs to eat and should never starve.<br>
• Philosophers don’t speak with each other.<br>
• Philosophers don’t know if another philosopher is about to die.<br>
• No need to say that philosophers should avoid dying!<br>

Your(s) program(s) should take the following arguments:<br>
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
  ◦ number_of_philosophers: The number of philosophers and also the number
of forks.<br>
  ◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.<br>
  ◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.<br>
During that time, they will need to hold two forks.
  ◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.<br>
  ◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
