extern "C"{
	#include "../../include/processes.h"
}

#include <iostream>
#include <string>

using namespace std;

enum STATUS {
	none,
	input,
	output,
	io,
	heredoc
};

ostream& operator<<(ostream& out, t_process* list){
	while (list){
		out 
			<< boolalpha
			<< "is default: " << list->is_built_in << endl
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

ostream& operator<<(ostream& out, char** arr){
	while (*arr){
		out << *arr << endl;
		arr++;
	}
	return out;
}

void check_input(int argc){
	if (argc == 1){
		cout 
			<< "Awaiting input: " << endl
			<< " > input [input_file] {commands}" << endl
			<< " > output [output_file] {commands}" << endl
			<< " > io [input_file] [output_file] {commands}" << endl
			<< " > heredoc {commands}" << endl
			<< " > {commands}" << endl;
		exit(1);
	}
}

STATUS get_status(const string& str){
	if (str == "input"){
		return STATUS::input;
	} else if (str == "output"){
		return STATUS::output;
	} else if (str == "io"){
		return STATUS::io;
	} else if (str == "heredoc"){
		return STATUS::heredoc;
	} else {
		return STATUS::none;
	}
}

void open_files(char*** argv, int& input_fd, int& output_fd){
	STATUS status = get_status((*argv)[1]);

	if (status == STATUS::input){
		input_fd = open((*argv)[2], O_RDONLY);
		if (input_fd < 0){
			perror(strerror(errno));
			exit(1);
		}
		(*argv) += 3;
	} else if (status == STATUS::output){
		output_fd = open((*argv)[2], O_WRONLY);
		if (output_fd < 0){
			perror(strerror(errno));
			exit(1);
		}
		(*argv) += 3;
	} else if (status == STATUS::io){
		input_fd = open((*argv)[2], O_RDONLY);
		output_fd = open((*argv)[3], O_WRONLY);
		if (input_fd < 0 || output_fd < 0){
			perror(strerror(errno));
			exit(1);
		}
		(*argv) += 4;
	} else if (status == STATUS::heredoc){
		input_fd = proc_here_doc();
		if (input_fd < 0){
			perror(strerror(errno));
			exit(1);
		}
		(*argv) += 2;
	} else if (status == STATUS::none){
		(*argv)++;
	}
}

int main(int argc, char** argv, char** envp){
	check_input(argc);

	int input_fd = STDIN_FILENO; (void)input_fd;
	int output_fd = STDOUT_FILENO; (void)output_fd;
	open_files(&argv, input_fd, output_fd);

	g_data.envp = env_create(envp);
	t_process* process_list = proc_init_list(argv, envp);

	proc_execute_list(process_list);

	proc_destroy_list(process_list);
	env_destroy(g_data.envp);
}
