#include <iostream>
#include "O3sim_ruby/O3sim_ruby.h"
using namespace std;


int main(int argc, char const *argv[])
{
	O3sim_ruby Osim (4,4,4,4,true,false,1,"lS","med","debugname");
	Osim.initialize();
	Osim.send_request(0x400,16,1,0,false,false,NULL);
	Osim.send_request(0x400,16,0,0,false,false,NULL);
	
	while (Osim.RubyQueueEmpty(1))
	{
		Osim.advance_time();
	}

    Osim.print_stats(std::cout);

	return 0;
}
