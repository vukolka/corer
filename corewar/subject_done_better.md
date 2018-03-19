####### AT START UP ######

### Flags

-dump n

Make n ammount of cycles, print memory to stdout in the format of 32 octets per line in 16-base.

-n n
must be followed by someplayer.cor
Specifies manualy player's number which must be written to r1 of the 1st process.

if given more than CHAMP_MAX_SIZE display error

###### PRELOAD ######

At preload phase each player initiate a process. VM gives player's id to initial processes r1.

When we set up a player on the map, we must give its process initial location which to be written to Program Counter.

entry points of players must be spread up evenly.

##### PROCESSES ######

Each process has its own isolated attributes.
1. Player Id
2. Memory - REG NUMBER units of REG_SIZE.
3. PC -- pointer to a command on the game field to be executed next.
4. bool carry.
5. Ammount of live executions

##### VM ########

The game stops when all processes are dead.

Process is to be killed if it has not executed 'live' command since last "check if alive" which is executed every CYCLE_TO_DIE cycles.

if live command has been executed more than NBR_LIVE, we decrease CYCLE_TO_DIE by CYCLE_DELTA

If CYCLE_TO_DIE wasn’t decreased since MAX_CHECKS checkups, decrease it.

To win you must be the last who executed live command.

The game board is of MEM_SIZE octets.

