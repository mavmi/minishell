// Положи файлы в папку /srcs/parser и запускай через run-файлы

#include "../../include/parser.h"
#include "assert.h"

#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (*(s++))
	{
		counter++;
	}
	return (counter);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				result;
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		result = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (result != 0)
		{
			return (result);
		}
		if (s1[i] == 0 || s2[i] == 0)
		{
			return (0);
		}
		i++;
	}
	return (0);
}

int	cmp_strings(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
	{
		return (0);
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len == s2_len && !ft_strncmp(s1, s2, s1_len))
	{
		return (1);
	}
	return (0);
}

void destroy_array_of_strings(char **array){
	char **ptr = array;
	
	while (*ptr){
		free(*ptr);
		ptr++;
	}

	free(array);
}

void TEST_DEFINES(){
	char **defines = par_get_redirect();
	char **ptr = defines;
	
	while (*ptr){
		printf("%s\n", *ptr);
		ptr++;
	}

	free(defines);
}

void TEST_LIST(){
	{
		t_par_list *list = par_initial_empty_list();
		assert(list);
		assert(!list->size);
		assert(!list->begin);
		assert(!list->end);
		par_destroy_all(list);
	}

	{
		t_par_list *list = par_initial_empty_list();
		t_par_elem *elem_1 = par_get_new_elem(1, "1");
		t_par_elem *elem_2 = par_get_new_elem(2, "22");
		t_par_elem *elem_3 = par_get_new_elem(3, "333");
		t_par_elem *elem_4 = par_get_new_elem(4, "4444");
		t_par_elem *elem_5 = par_get_new_elem(5, "55555");

		assert(list);
		assert(elem_1);
		assert(elem_2);
		assert(elem_3);
		assert(elem_4);
		assert(elem_5);

		par_push_back(elem_1, list);
		par_push_back(elem_2, list);
		par_push_back(elem_3, list);
		par_push_back(elem_4, list);
		par_push_back(elem_5, list);

		assert(list->begin == elem_1);
		assert(list->end == elem_5);

		t_par_elem *iter = list->begin;
		for (int i = 1; i <= 5; i++){
			assert(iter->type == i);
			iter = iter->next;
		}
		assert(!iter);

		par_destroy_all(list);
	}

	{
		t_par_list *list = par_initial_empty_list();
		t_par_elem *elem_1 = par_get_new_elem(1, "1");
		t_par_elem *elem_2 = par_get_new_elem(2, "22");
		t_par_elem *elem_3 = par_get_new_elem(3, "333");
		t_par_elem *elem_4 = par_get_new_elem(4, "4444");
		t_par_elem *elem_5 = par_get_new_elem(5, "55555");

		assert(list);
		assert(elem_1);
		assert(elem_2);
		assert(elem_3);
		assert(elem_4);
		assert(elem_5);

		par_push_back(elem_1, list);
		par_push_back(elem_2, list);
		par_push_back(elem_3, list);
		par_push_back(elem_4, list);
		par_push_back(elem_5, list);

		par_remove_by_pos(list, 100500);
		assert(list->size == 5);

		for (int i = 1; i <= 5; ++i){
			int last_position = 5 - i + 1;

			assert(par_get_by_pos(list, 1)->prev == NULL);
			assert(par_get_by_pos(list, last_position)->type == 5);
		
			assert(list->begin == par_get_by_pos(list, 1));
			assert(list->end == par_get_by_pos(list, last_position));
		
			par_remove_by_pos(list, 1);
		}

		assert(list->size == 0);
		assert(list->begin == NULL);
		assert(list->end == NULL);

		par_destroy_all(list);
	}

	{
		t_par_list *list = par_initial_empty_list();
		t_par_elem *elem_1 = par_get_new_elem(1, "1");
		t_par_elem *elem_2 = par_get_new_elem(2, "22");
		t_par_elem *elem_3 = par_get_new_elem(3, "333");
		t_par_elem *elem_4 = par_get_new_elem(4, "4444");
		t_par_elem *elem_5 = par_get_new_elem(5, "55555");

		assert(list);
		assert(elem_1);
		assert(elem_2);
		assert(elem_3);
		assert(elem_4);
		assert(elem_5);

		par_push_back(elem_1, list);
		par_push_back(elem_2, list);
		par_push_back(elem_3, list);
		par_push_back(elem_4, list);
		par_push_back(elem_5, list);

		for (int i = 5; i >= 1; --i){
			assert(par_get_by_pos(list, i)->next == NULL);
			assert(par_get_by_pos(list, i)->type == i);
		
			assert(list->begin == par_get_by_pos(list, 1));
			assert(list->end == par_get_by_pos(list, i));
		
			par_remove_by_pos(list, i);
		}

		assert(list->size == 0);
		assert(list->begin == NULL);
		assert(list->end == NULL);

		par_destroy_all(list);
	}

	{
		char *str = (char *)malloc(3);
		str[0] = 'a';
		str[1] = 'b';
		str[2] = 0;

		t_par_elem *elem = par_get_new_elem(0, str);
		par_destroy_elem(elem);
		free(str);
	}
}

void TEST_SPLIT(){
	{
		char *orig[] = {"<<", "file", "cat", "|", "grep", ">>", "aaa"};
		char **output = par_split("<<file cat | grep           >> aaa");

		int i = 0;
		while (output[i]){
			assert(cmp_strings(orig[i], output[i]));
			i++;
		}		
		
		destroy_array_of_strings(output);
	}

	{
		char *orig[] = {"<<", "file", "cat", "|", "grep", ">>", "aaa"};
		char **output = par_split("<<file cat|grep>>aaa");

		int i = 0;
		while (output[i]){
			assert(cmp_strings(orig[i], output[i]));
			i++;
		}		
		
		destroy_array_of_strings(output);
	}

	{
		char *orig[] = {"<<", "<", ">>", ">"};
		char **output = par_split("<<<>>>");

		int i = 0;
		while (output[i]){
			assert(cmp_strings(orig[i], output[i]));
			i++;
		}		
		
		destroy_array_of_strings(output);
	}

	{
		char *orig[] = {"<", "|", "<<", "|", "|", "|", ">", "|", ">", "|", ">"};
		char **output = par_split("<|<<|||>|>|>");

		int i = 0;
		while (output[i]){
			assert(cmp_strings(orig[i], output[i]));
			i++;
		}		
		
		destroy_array_of_strings(output);
	}
}

void TEST_QUOTES(){
	{
		char *orig[] = {"cat"};
		char **output = par_split("\"cat\"");

		int i = 0;
		while (output[i]){
			assert(cmp_strings(orig[i], output[i]));
			i++;
		}		
		
		destroy_array_of_strings(output);
	}

	{
		char *orig[] = {"cat"};
		char **output = par_split("\'cat\'");

		int i = 0;
		while (output[i]){
			assert(cmp_strings(orig[i], output[i]));
			i++;
		}		
		
		destroy_array_of_strings(output);
	}

	{
		char *orig[] = {"cat"};
		char **output = par_split("\"cat\'");
		assert(output == NULL);
	}

	{
		char *orig[] = {"cat"};
		char **output = par_split("\'cat\"");
		assert(output == NULL);
	}

	{
		char *orig[] = {"cat<<"};
		char **output = par_split("\"cat\"\"<<\"\"\"");

		int i = 0;
		while (output[i]){
			assert(cmp_strings(orig[i], output[i]));
			i++;
		}		
		
		destroy_array_of_strings(output);
	}

	{
		char *orig[] = {"cat<<"};
		char **output = par_split("\"cat\"\'<<\'\"\"");

		int i = 0;
		while (output[i]){
			assert(cmp_strings(orig[i], output[i]));
			i++;
		}		
		
		destroy_array_of_strings(output);
	}
}

int main(){
	TEST_DEFINES();
	TEST_LIST();
	TEST_SPLIT();
	TEST_QUOTES();
}