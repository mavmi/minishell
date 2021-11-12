extern "C"{
	#include "../../include/pipex.h"
}

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

using namespace std;

const int buffer_size = 1024;

int main(){
	char buffer[buffer_size];

	int hd = proc_here_doc();
	int count = read(hd, buffer, buffer_size);
	if (count < 1){
		perror(strerror(errno));
		return 0;
	}
	buffer[count] = 0;
	cout << buffer << endl;

	close(hd);
}
