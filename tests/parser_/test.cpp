extern "C" {
	#include "../../include/parser_.h"
}

#include "../debugger.h"

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

ostream& operator<<(ostream& out, t_strings* list){
	if (!list){
		return out;
	}

	while (list){
		out 
			<< "string: " << string(list->string) << endl;
		if (list->next){
			out << endl;
		}
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
		char val_1[] = "111";
		char val_2[] = "\"$var\"";
		char val_3[] = "222";

		t_strings* list = pars_get_new_str_elem(val_1);
		pars_push_back_str(list, pars_get_new_str_elem(val_2));
		pars_push_back_str(list, pars_get_new_str_elem(val_3));

		char* output_str = pars_get_whole_string(list);
		cout << "whole string: " << string(output_str) << endl;
		free(output_str);

		pars_destroy_str_list(list);
	}

	{
		char val_1[] = "111";
		char val_2[] = "\"000$var 000\"";
		char val_3[] = "222";

		t_strings* list = pars_get_new_str_elem(val_1);
		pars_push_back_str(list, pars_get_new_str_elem(val_2));
		pars_push_back_str(list, pars_get_new_str_elem(val_3));

		char* output_str = pars_get_whole_string(list);
		cout << "whole string: " << string(output_str) << endl;
		free(output_str);

		pars_destroy_str_list(list);
	}

	{
		char val_1[] = "111";
		char val_2[] = "\"000$ 000\"";
		char val_3[] = "222";

		t_strings* list = pars_get_new_str_elem(val_1);
		pars_push_back_str(list, pars_get_new_str_elem(val_2));
		pars_push_back_str(list, pars_get_new_str_elem(val_3));

		char* output_str = pars_get_whole_string(list);
		cout << "whole string: " << string(output_str) << endl;
		free(output_str);

		pars_destroy_str_list(list);
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
	char var[] = "var=123";
	env_push_back(g_data.envp, var);


	TEST_GET_OPERATORS();
	TEST_ELEM_LIST();
	TEST_STR_LIST();
	TEST_PARSER();


	env_destroy(g_data.envp);
}
