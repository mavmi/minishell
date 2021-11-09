extern "C"{
	#include "../../include/pipex.h"
}

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv, char** envp){
	if (argc == 1){
		cout << "No args: exit" << endl;
		return 0;
	}

	t_process* process_list = proc_init_list(argv + 1, envp);

	//t_process* elem = process_list;
	//while (elem){
	//	printf("%s: %p\n", elem->exec_name, elem->exec_path);
	//	elem = elem->next;
	//}

	proc_execute_list(process_list, -1, -1);
	proc_destroy_list(process_list);
}
