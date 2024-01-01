#include <unistd.h>

int main()
{
	vfork();
	sleep(60);
	return 0;
}
