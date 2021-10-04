// parser.h

/*
    Объявим названия синонимом для структур заранее,
    чтобы переменные в структурах имели немного более лаконичные названия.
*/
typedef struct s_parser_elem    t_parser_elem; 
typedef struct s_parser_list    t_parser_list;


/*
    Здесь будут лежать дефайны ключевых
    элементов команды терминала,
    которые нужно уметь находить.
    Типы данных дефайнов должны быть одинаковыми.
*/
#define DEFAULT ""          // Заглушка, которая не зарезервирована терминалом. Например, путь к папке.
#define REDIRECT_INPUT "<<" // Команда перенаправления инпута. Зарезервирована терминалом.
// ...


/*
    Структура для хранение элемента терминала,
    описанного дефайнами выше.
    Эта структура - элемент двусвязного списка.

    Давай условимся, что все строки в структурах
    будут замолоченными.
    Тогда у нас не будет вопросов, например,
    как разрушать очередную строку при удалении списка.
*/
struct s_parser_elem
{
    char    *type;          // Тип элемента, определнный дефайном выше. Например, REDIRECT_INPUT.
    char    *value;         /*
                                Строка с содержимым подстроки команды из терминала.
                                Для ключевых элементов терминала будет содержать значение
                                переменной *type или NULL. Решай сама.
                             */
    t_parser_elem   *next;  // Соседи справа 
    t_parser_elem   *prev;  // и слева.
    // ...
};


/*
    Структура для хранения основаных данных о двусвязном списке.
*/
struct s_parser_list
{
    size_t          size;   // Размер списка.
    t_parser_elem   *begin; // Указатели на начало списка
    t_parser_elem   *end;   // и конец.
    // ...
};


/*
    Функции для работы со списком.
    Пусть у функций из одной группы будет
    одинаковый префикс.
    В данном случае, например, "parser_(название_функции)".

    Не добавляй в хидер вспомогательные функции, которые нужны
    только для полноценной работы какой-то другой функции.
    Они там напрочь не нужны. 
    На то они и вспомогательные.
    И пиши сразу по норме, если получится.

    Не забывай о потенциальных NULL'ах от маллока,
    указателей на строки, структуры и т.д.
    Всегда делай проверку.
*/

/*
    Маллочит новый элемент списка и возвращает его
    или NULL в случае ошибки.
*/
t_parser_elem   *parser_get_new_elem(char *type, char *value, /*...*/);

/*
    Кидает в конец списка [list] новый элемент [elem] и возвращает
    код работы. Пусть в случае удачи возвращается 0, а в случае ошибки - 1.
    
    Не забудь сделать проверку на NULL'и и обноваить все необходимые данные
    в структуре или структурах.
*/
int             parser_push_back(t_parser_list *list, t_parser_elem *elem);

/*
    Думаю, не помешает, если у нас будет функция взятия элемента
    листа по его номеру?

    Очевидно же, что здесь стоит добавить проверку и на NULL'и,
    и на принадлежность номера [position] списку, да?
    Я больше не буду об этом напоминать)
*/
t_parser_elem   *parset_get_by_pos(t_parser_list *list, size_t position);

/*
    Удаляет элемент листа по его позиции.
*/
void            parser_remove_pos(t_parser_list *list, size_t position);

/*
    Последовательно разрушает весь двусвязный список и все,
    что в нем содержится.
*/
void            pareser_destroy(t_parser_list *list);

/*
    Инициализирует пустой список.
*/
t_parser_list   parser_init_list(void);

// ...
