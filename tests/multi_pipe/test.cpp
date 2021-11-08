extern "C"{
	#include "../../include/pipex.h"
}

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv, char** envp){
	if (argc == 1){
		return 0;
	}

	t_process* process_list = proc_init_list(argv + 1, envp);
	proc_execute_list(process_list, -1, -1);
	proc_destroy_list(process_list);
}
