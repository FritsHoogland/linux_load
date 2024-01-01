# Linux load generator
This is a very simple and small toolset to increase the load figure of a linux system to the figure you want.

Usage:

1. create the `uninterruptible` executable: 
```
make
```
2. run the `loader` script with the number for which you want to increase the load, for example:
```
./loader 40
```
3. The `loader` script will run the set number `uninterruptible` executables in the background. These executables will run for 60 seconds. If you want to cancel running the `uninterruptible` processes, press enter and the script will stop them right away. If you run the `uninterruptible` executable in your shell directly, the session is stuck, because the execution itself is not interruptible, as the name suggests.

This actually means that the uninterruptible executable CANNOT be stopped or signalled with `kill`. However, the uninterruptible executable has an uninterruptible shell as parent, which, when killed/terminated will take down the uninterruptible executable as child.

For high number of tasks, the 60 seconds might not be enough for the load figure to reach this number. If you still want the load figure to reach the number, increase the sleep in `uninterruptible.c`.

Use at your own risk.

# Background
The load figure originally showed the number of of running and willing to run processes/processes in the runqueue. On linux, the load figure was changed to include processes in task state D/uninterruptible sleep. Brendan Gregg has an excellent article explain the history of the load figure, and when it was changed on linux to include the uninterruptible sleep state: <https://www.brendangregg.com/blog/2017-08-08/linux-load-averages.html>.

By making the load figure include linux tasks in running state both on and off cpu, as well as tasks in uninterruptible sleep on and off cpu, the load figure can mean a lot of things, which is not bound to CPU load. That makes the number hard to interpret or usable as an absolute statistic.

If the addition of the uninterruptible sleep state would strictly have only meant a task waiting on ALL forms disk IO, it would more usable because the load would mean either CPU or disk IO or both (which is still not very usable). But it does not include all disk IO (think asynchronous IO), and the uninterruptible state is USUALLY disk IO, but not limited to that. This mini-toolkit uses a totally different uninterruptible state reason (vfork()).

Today, there is the weird situation that many people are using this figure, yet it has become reasonably meaningless in real life. If you doubt my words, take a look at the `loadavg.c` linux kernel source file: <https://github.com/torvalds/linux/blob/master/kernel/sched/loadavg.c>

```
/*
 * kernel/sched/loadavg.c
 *
 * This file contains the magic bits required to compute the global loadavg
 * figure. Its a silly number but people think its important. We go through
 * great pains to make it work on big machines and tickless kernels.
 */
```
If you weren't turned down by my comments and this remark, read on in the comments in the source starting from:
```
* Due to a number of reasons the above turns in the mess below:
```
So overall, if you are serious about performance, this is not the number your are looking for. 

Use at your own risk!

The c program was copied from a stackexchange example: <https://unix.stackexchange.com/questions/134888/simulate-an-unkillable-process-in-d-state>
