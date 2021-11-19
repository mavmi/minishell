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

	out << "size: " << list->size << endl;

	t_par_elem* elem = list->begin;
	while (elem){
		out << elem << endl;
		if (elem->next){
			out << endl;
		}
	}

	return out;
}

int main(){

}
