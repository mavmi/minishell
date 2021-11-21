extern "C" {
	#include "../../include/parser_.h"
}

#include "../debugger.h"

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

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

ostream& operator<<(ostream& out, s_pars_list* list){
	if (!list){
		return out;
	}

	while (list){
		out 
			<< "type: " << list->type << endl
			<< "value: " << list->value << endl;
		if (list->next)
			out << endl;
		list = list->next;
	}
	
	return out;
}

void TEST_GET_OPERATORS(){
	Debugger d(__FUNCTION__);

	char** arr = pars_get_operators();
	cout << arr << endl;
	free (arr);
}

void TEST_ELEM_LIST(){
	Debugger d(__FUNCTION__);

	{
		char val[] = "value";

		t_pars_list* elem = pars_get_new_elem(123, val);
		cout << elem << endl;
		pars_destroy_elem(elem);
	}

	{
		char val[] = "value";

		t_pars_list* elem = pars_get_new_elem(123, val);
		cout << elem << endl;
		pars_destroy_list(elem);
	}

	{
		char val_1[] = "value_1";
		char val_2[] = "value_2";
		char val_3[] = "value_3";

		t_pars_list* list = pars_get_new_elem(1, val_1);
		pars_push_back(list, pars_get_new_elem(2, val_2));
		pars_push_back(list, pars_get_new_elem(3, val_3));
		
		cout << list << endl;
		pars_destroy_list(list);
	}
}

void TEST_STR_LIST(){
	Debugger d(__FUNCTION__);

	{
		char val_1[] = "\'value\'";

		char* output_str = pars_get_whole_string(val_1);
		cout << "whole string: " << string(output_str) << endl;
		assert(string(output_str) == "value");
		free(output_str);
	}

	{
		char val_1[] = "\"value $ $var  \"";

		char* output_str = pars_get_whole_string(val_1);
		cout << "whole string: " << string(output_str) << endl;
		assert(string(output_str) == "value $ 888  ");
		free(output_str);
	}

	{
		char val_1[] = "value $var";

		char* output_str = pars_get_whole_string(val_1);
		cout << "whole string: " << string(output_str) << endl;
		assert(string(output_str) == "value 888");
		free(output_str);
	}

	{
		char val_1[] = "\"value\"$var\'$value'\"$var\"$";

		char* output_str = pars_get_whole_string(val_1);
		cout << "whole string: " << string(output_str) << endl;
		assert(string(output_str) == "value888$value888$");
		free(output_str);
	}
}

void TEST_PARSER(){
	Debugger d(__FUNCTION__);

	{
		Debugger de(">> << || >>> <<<<< $$=$.");

		char cmd[] = ">> << || >>> <<<<< $$=$.";

		t_pars_list* list = pars_split(cmd);
		cout << list << endl;
		pars_destroy_list(list);
	}

	{
		Debugger de("cat ls         man");

		char cmd[] = "cat ls         man";

		t_pars_list* list = pars_split(cmd);
		cout << list << endl;
		pars_destroy_list(list);
	}

	{
		Debugger de("cat>>>ls<<man<$=$$.");

		char cmd[] = "cat>>>ls<<man<$=$$.";

		t_pars_list* list = pars_split(cmd);
		cout << list << endl;
		pars_destroy_list(list);
	}
}

int main(int argc, char** argv, char** envp){
	(void)argc; (void)argv;
	g_data.envp = env_create(envp);
	char var[] = "var=888";
	env_push_back(g_data.envp, var);


	//TEST_GET_OPERATORS();
	//TEST_ELEM_LIST();
	TEST_STR_LIST();
	//TEST_PARSER();


	env_destroy(g_data.envp);
}
