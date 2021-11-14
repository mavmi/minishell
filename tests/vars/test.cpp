extern "C" {
	#include "../../include/variables.h"
}

#include "../debugger.h"
#include <assert.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

ostream& operator<<(ostream& out, t_var* elem){
	if (!elem){
		return out;
	}

	while (elem){	
		out
			<< "name: " << elem->name << endl
			<< "value: " << elem->value;
		if (elem->next)
			out << endl << endl;
		elem = elem->next;
	}
	return out;
}

int main(){
	Debugger d(__FUNCTION__);

	{
		char name[] = "name";
		char value[] = "value";

		t_var* elem = var_get_new_elem(name, value);
		assert(elem);
		assert(!elem->next);
		assert(string(name) == string(elem->name));
		assert(string(value) == string(elem->value));

		var_destroy_elem(elem);
	}

	{
		char name[] = "begin";
		char value[] = "value";
		t_var* list = var_get_new_elem(name, value);
		
		assert(list);
		assert(!list->next);
		assert(string(name) == string(list->name));
		assert(string(value) == string(list->value));

		char name_1[] = "name_1";
		char name_2[] = "name_2";
		char name_3[] = "name_3";
		char name_4[] = "name_4";
		char name_5[] = "name_5";

		char value_1[] = "value_1";
		char value_2[] = "value_2";
		char value_3[] = "value_3";
		char value_4[] = "value_4";
		char value_5[] = "value_5";

		var_push_back(list, var_get_new_elem(name_1, value_1));
		var_push_back(list, var_get_new_elem(name_2, value_2));
		var_push_back(list, var_get_new_elem(name_3, value_3));
		var_push_back(list, var_get_new_elem(name_4, value_4));
		var_push_back(list, var_get_new_elem(name_5, value_5));

		cout << list << endl;

		var_destroy_list(list);
	}

	{
		char name[] = "begin";
		char value[] = "value";
		t_var* list = var_get_new_elem(name, value);
		
		assert(list);
		assert(!list->next);
		assert(string(name) == string(list->name));
		assert(string(value) == string(list->value));

		char name_1[] = "name_1";
		char name_2[] = "name_2";
		char name_3[] = "name_3";
		char name_4[] = "name_4";
		char name_5[] = "name_5";

		char value_1[] = "value_1";
		char value_2[] = "value_2";
		char value_3[] = "value_3";
		char value_4[] = "value_4";
		char value_5[] = "value_5";

		var_push_back(list, var_get_new_elem(name_1, value_1));
		var_push_back(list, var_get_new_elem(name_2, value_2));
		var_push_back(list, var_get_new_elem(name_3, value_3));
		var_push_back(list, var_get_new_elem(name_4, value_4));
		var_push_back(list, var_get_new_elem(name_5, value_5));
		cout << endl << "\toriginal list: " << endl << list << endl;

		{
			char tmp[] = "name_6";
			var_remove(&list, tmp);
			cout << endl << "\tnot existing elem removed: " << endl << list << endl;
		}

		{
			char tmp[] = "name_5";
			var_remove(&list, tmp);
			cout << endl << "\tlast elem removed: " << endl << list << endl;
		}

		{
			char tmp[] = "name_2";
			var_remove(&list, tmp);
			cout << endl << "\tmid elem removed: " << endl << list << endl;
		}

		{
			char tmp[] = "begin";
			var_remove(&list, tmp);
			cout << endl << "\tfirst elem removed: " << endl << list << endl;
		}

		var_destroy_list(list);
	}

	{
		char name[] = "begin";
		char value[] = "value";
		t_var* list = var_get_new_elem(name, value);
		
		assert(list);
		assert(!list->next);
		assert(string(name) == string(list->name));
		assert(string(value) == string(list->value));

		char name_1[] = "name_1";
		char value_1[] = "value_1";

		var_push_back(list, var_get_new_elem(name_1, value_1));
		var_remove(&list, name);
		var_remove(&list, name_1);
	
		assert(list == NULL);
	}

	{
		char name[] = "begin";
		char value[] = "value";
		t_var* list = var_get_new_elem(name, value);
		
		assert(list);
		assert(!list->next);
		assert(string(name) == string(list->name));
		assert(string(value) == string(list->value));

		char name_1[] = "name_1";
		char value_1[] = "value_1";

		var_push_back(list, var_get_new_elem(name_1, value_1));
		var_remove(&list, name_1);
		var_remove(&list, name);

		assert(list == NULL);
	}

	{
		char name[] = "begin";
		char value[] = "value";
		t_var* list = var_get_new_elem(name, value);
		
		assert(list);
		assert(!list->next);
		assert(string(name) == string(list->name));
		assert(string(value) == string(list->value));

		char name_1[] = "name_1";
		char name_2[] = "name_2";
		char name_3[] = "name_3";
		char name_4[] = "name_4";
		char name_5[] = "name_5";

		char value_1[] = "value_1";
		char value_2[] = "value_2";
		char value_3[] = "value_3";
		char value_4[] = "value_4";
		char value_5[] = "value_5";

		var_push_back(list, var_get_new_elem(name_1, value_1));
		var_push_back(list, var_get_new_elem(name_2, value_2));
		var_push_back(list, var_get_new_elem(name_3, value_3));
		var_push_back(list, var_get_new_elem(name_4, value_4));
		var_push_back(list, var_get_new_elem(name_5, value_5));

		assert(utils_cmp_strings(name_3, var_get(list, name_3)->name));
		assert(utils_cmp_strings(value_3, var_get(list, name_3)->value));

		assert(utils_cmp_strings(name, var_get(list, name)->name));
		assert(utils_cmp_strings(value, var_get(list, name)->value));

		assert(utils_cmp_strings(name_5, var_get(list, name_5)->name));
		assert(utils_cmp_strings(value_5, var_get(list, name_5)->value));

		var_destroy_list(list);
	}
}
