# philosophers_42

This is my philosopher project for 42 school.

Dining philosophers problem is a problem created by Edsger Wybe Dijkstra in 1965 to explain the deadlock state of an operating system, which is traditionally commonly introduced in lectures on operating systems

Subject is presented in the (https://cdn.intra.42.fr/pdf/pdf/66003/fr.subject.pdf)

For example, N philosophers are sitting at a round table and eating. A fork is placed between the philosophers, and the philosophers eat through the following process.

The philosopher repeats three actions:
eating ➔ sleeping ➔ thinking. 
When eating, both forks should be used. If you lift both forks, eat for a certain amount of time. When you're done eating, put down your fork. Not a single philosopher should die due to lack of food for a certain period of time. If all the philosophers were hungry and picked up the left forks at the same time, the right forks would have already been picked up by the philosopher sitting to their right, and everyone would be forever unable to hold the right forks. That is, there is no further progress, and the philosophers remain on standby forever. This phenomenon is called deadlock. Once in a deadlock, philosophers continue to suffer and die of starvation. The task is to implement a program that solves this problem using mutex or semaphore


Some inputs to test :

-5 800 200 200     =  no one should die
-5 600 150 150     =  no one should die
-4 410 200 200     =  no one should die
-100 800 200 200   =  no one should die
-105 800 200 200   =  no one should die
-200 800 200 200   =  no one should die
-200 410 200 200   =  no one should die (only on dell machine 👮)

1 800 200 200     =  a philo should die
4 310 200 100     =  a philo should die
4 200 205 200     =  a philo should die

5 800 200 200 7   =  no one should die, simulation should stop after 7 eats
4 410 200 200 10  =  no one should die, simulation should stop after 10 eats

-5 600 200 200    =  should error and not run (no crashing)
4 -5 200 200      =  should error and not run (no crashing)
4 600 -5 200      =  should error and not run (no crashing)
4 600 200 -5      =  should error and not run (no crashing)
4 600 200 200 -5  =  should error and not run (no crashing)
