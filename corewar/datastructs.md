# Data structures:

Class GameEnvironment
{
	queue<class Process>	move_queue
	list<class Player>		players
	unsigned char			map[MEM_SIZE]
	int				        cyclestodie = CYCLE_TO_DIE
    int				        counterAlive = 0
}

Class Player
{
	string			description
	string			name
	int				id
	unsigned long   last_live_cycle
}

Class Process
{
	class Player    player
	unsigned char	memory[REG_NUMBER]
	unsigned char	PC - pointer to next command
	bool			carry
	unsigned int	live_executions
	unsigned int    cycles_left
}
