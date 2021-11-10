extern "C"{
	#include "../../include/pipex.h"
}

#include <iostream>
#include <string>

using namespace std;

ostream& operator<<(ostream& out, t_process* list){
	while (list){
		out 
			<< boolalpha
			<< "is default: " << list->is_default << endl
			<< "name: " << list->exec_name << endl
			<< "path: " << list->exec_path << endl
			<< "args: ";

			char **ptr = list->argv;
			while (*ptr){
				out << *ptr << " ";
				ptr++;
			}
			out << endl << endl;

			list = list->next;
	}
	return out;
}

int main(int argc, char** argv, char** envp){
	if (argc == 1){
		cout << "No args: exit" << endl;
		return 0;
	}

	t_process* process_list = proc_init_list(argv + 1, envp);
	//cout << process_list;

	//t_process* elem = process_list;
	//while (elem){
	//	printf("%s: %p\n", elem->exec_name, elem->exec_path);
	//	elem = elem->next;
	//}

	proc_execute_list(process_list, -1, -1);
	proc_destroy_list(process_list);
}
