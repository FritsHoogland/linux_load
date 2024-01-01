// taken from: https://unix.stackexchange.com/questions/134888/simulate-an-unkillable-process-in-d-state
#include <unistd.h>

int main()
{
	vfork();
	sleep(60);
	return 0;
}
