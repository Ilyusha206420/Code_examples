#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

typedef struct ListSlot {
	char* data;
	int len;
	struct ListSlot* next;
	struct ListSlot* prev;
} ListSlot;

//функци€, определ€юща€, остались ли слова в строке
int is_words_in_str(char* str, int start_pos) {
	int i = 0;
	while (str[start_pos + i] != '\0') {
		if (str[start_pos + i] != ' ') {
			return 1;
		}
		i++;
	}
	return 0;
}

//функци€ включени€ в список элемента
int insert(ListSlot* prev, ListSlot* cor, ListSlot* next) {
	cor->next = next;
	cor->prev = prev;

	if (prev) {
		prev->next = cor;
	}
	if (next) {
		next->prev = cor;
	}
	
	return 0;
}

int mesh(ListSlot* t1, ListSlot* t2) {
	while (t1->next) {
		t1 = t1->next;
	}
	while (t2->prev) {
		t2 = t2->prev;
	}
	t1->next = t2;
	t2->prev = t1;
	return 0;
}

//фукци€ создани€ и заполнен€ €чейки списка
ListSlot* create_and_fill_list_slot(char* str, int start_pos) {
	ListSlot* t = (ListSlot*)malloc(sizeof(ListSlot));
	t->next = NULL;
	t->prev = NULL;
	t->len = 0;
	while (str[t->len + start_pos] != ' ' && str[t->len + start_pos] != '\0') {
		t->len++;
	}
	t->data = malloc(sizeof(char) * (t->len + 1));
	t->data[t->len] = '\0';
	int i = 0;
	while (i < t->len) {
		t->data[i++] = str[start_pos + i];
	}
	return t;
}

//функци€ определ€ет позицию элемента, после которого нужно вставить принимаемый
ListSlot* find_insert_pos(ListSlot* slot, int arg) {
	while (slot->next) {
		slot = slot->next;
	}

	while (slot->prev && slot->len > arg) {
		slot = slot->prev;
	}
	
	return slot;
}

//создает по прин€той строке упор€доченный по длине слов линейный список
ListSlot* init(char* str) {
	int i = 0;
	while (str[i] == ' ') {
		i++;
	}

	ListSlot* t1 = (ListSlot*)malloc(sizeof(ListSlot)); //создаем временный нулевой элемент дл€ корректной работы кода
	t1->prev = NULL;
	t1->next = NULL;

	while (str[i] != '\0') {
		if (str[i] != ' ') {
			ListSlot* t2 = create_and_fill_list_slot(str, i);
			t1 = find_insert_pos(t1, t2->len);
			insert(t1, t2, t1->next);
			i += t2->len;
		}
		else {
			while (str[i] == ' ') {
				i++;
			}
		}
	}

	while (t1->prev) {
		t1 = t1->prev;
	}

	t1 = t1->next;
	free(t1->prev); //удал€ем временный нулевой элемент
	t1->prev = NULL;

	return t1;
}

//функци€ вывода списка
int print_list(ListSlot* t) {
	while (t->prev) {
		t = t->prev;
	}
	while (t->next) {
		printf("%s ", t->data);
		t = t->next;
	}
	printf("%s ", t->data);
	
	return 0;
}

//чтение из файла(возвращает char*)
char* read_from_file(char* filename) {
	int i = 0;
	int cap = 10;
	char ch;
	char* out_str = malloc(sizeof(char) * cap);
	
	FILE* f = fopen(filename, "r");
	
	while (ch = fgetc(f), ch != EOF) {
		if (i >= cap - 1) {
			cap += 10;
			char* new = malloc(sizeof(char) * cap);

			for (int n = 0; n < i; n++) {
				new[n] = out_str[n];
			}
			
			free(out_str);
			out_str = new;
		}
		out_str[i++] = ch;
	}
	out_str[i] = '\0';
	
	return out_str;
}

//освобождение пам€ти, занимаемой списком
int clean(ListSlot* t) {
	while (t->prev) {
		t = t->prev;
	}

	while (t->next) {
		free(t->data);
		t = t->next;
		free(t->prev);
	}

	free(t->data);
	free(t);

	return 0;
}



int main() {
	char* str_1 = read_from_file("file_1.txt");
	char* str_2 = read_from_file("file_2.txt");
	char* str_3 = read_from_file("file_3.txt");

	ListSlot* list_1 = init(str_1);
	ListSlot* list_2 = init(str_2);
	ListSlot* list_3 = init(str_3);

	free(str_1);
	free(str_2);
	free(str_3);

	mesh(list_1, list_2);
	mesh(list_1, list_3);

	print_list(list_1);

	clean(list_1);

	return 0;
}