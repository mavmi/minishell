extern "C" {
	#include "../../include/parser.h"
}

#include "../debugger.h"

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, t_par_elem* elem){
	if (!elem){
		return out;
	}

	return out
		<< "type: " << elem->type << endl
		<<	"value: " << string(elem->value);
}

ostream& operator<<(ostream& out, t_par_list* list){
	if (!list){
		return out;
	}

	out << "\t list size: " << list->size << endl;

	t_par_elem* elem = list->begin;
	while (elem){
		out << elem << endl;
		elem = elem->next;
		if (elem){
			out << endl;
		}
	}

	return out;
}

ostream& operator<<(ostream& out, char** arr){
	if (!arr){
		return out;
	}

	while (*arr){
		out << *arr;
		if (*(arr + 1)){
			out << endl;
		}
		arr++;
	}
	
	return out;
}

int main(){
	{
		char cmd[] = "cmd1 >> >>>> >>> ls ||| cat $$ ===";
		t_par_list* list = par_split(cmd);
		cout << list << endl;
		par_destroy_all(list);
	}
}
