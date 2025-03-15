#define _CRT_SECURE_NI_WARNINGS
#include <stdio.h>
#include <stdlib.h>

char* make_bigger(char* array, int cap) {
	char* out = malloc(sizeof(char) * (cap + 11));
	for (int i = 0; i <= cap; i++) {
		out[i] = array[i];
	}
	free(array);
	return out;
}

char* read_input() {
	char ch;
	int i = 0;
	int cap = 9;
	char* data = malloc(sizeof(char) * 10);

	while (ch = getchar(), ch != '\n') {
		if (i == cap) {
			data = make_bigger(data, cap);
			cap += 10;
		}
		data[i++] = ch;
	}
	data[i] = '\0';
	return data;
}

int check_input(int n, int m) {
	if (n == 0) {
		printf("It isn't any words in string");
		return 0;
	}
	if (m == 0) {
		printf("It isn't any word in second string");
		return 0;
	}
	if (m > 1) {
		printf("It's to much words in second string, you must enter only one word");
		return 0;
	}
	return 1;
}

int is_word(char* str, int start_pos) {
	while (str[start_pos] != ' ' && str[start_pos] != '\0') {
		if ((str[start_pos] >= 'A' && str[start_pos] <= 'Z') || (str[start_pos] >= 'a' && str[start_pos] <= 'z')) {
			return 1;
		}
		start_pos++;
	}
	return 0;
}

int get_words_count(char* str) {
	int n = 0;
	int i = 0;

	if (str[0] != ' ') {
		n++;
	}

	while (str[i++] != '\0') {
		if (str[i] == ' ' && str[i + 1] != ' ') {
			n += is_word(str, i + 1);
		}
	}

	return n;
}

int get_len(char* str, int start_pos) {
	int m = 0;
	while (str[m] == ' ') {
		m++;
	}
	if (is_word(str, start_pos + m)) {
		int i = 0;
		while (str[start_pos + i + m] != ' ' && str[start_pos+i + m] != '\0') {
			i++;
		}
		return i;
	}
	return 0;
}

int fill_array(int words_count, char* str, char **array) {
	int len; int min_len;
	int i = -1;
	int j = 0;
	int n = 0;

	while (str[n] == ' ') {
		n++;
	}

	len = get_len(str, n);
	min_len = len;

	while (str[n] != '\0' && i <= words_count) {
		if (is_word(str, n)) {
			len = get_len(str, n);
			if (len < min_len) {
				min_len = len;
			}
			array[++i] = malloc(sizeof(char) * (len + 1));
			while (str[n] != ' ' && str[n] != '\0') {
				array[i][j++] = str[n++];
			}
			array[i][len] = '\0';
			j = 0;
		}
		n++;
	}
	return min_len;
}

char* insert_words_and_create_out_str(char **array, char* word, int min_len, int count, int word_len) {
	int len = 0;
	int cor_len = 0;
	int i = 0; int j = 0;
	int n;

	while (i < count) {
		while (array[i][j++] != '\0') {
			len++; cor_len++;
		}
		if (cor_len == min_len) {
			free(array[i]);
			array[i] = malloc(sizeof(char) * (word_len + 1));			
			j = 0;
			n = 0;
			while (word[n] == ' ') {
				n++;
			}
			while (j < word_len) {
				array[i][j++] = word[n++];
			}
			array[i][word_len] = '\0';
		}
		j = 0;
		cor_len = 0;
		i++;
	}

	n = 0; 
	i = 0; 
	j = 0;

	char* out_str = malloc(sizeof(char) * (len+count));

	while (i < count) {
		while (array[i][j] != '\0') {
			out_str[n++] = array[i][j++];
		}
		j = 0;
		out_str[n++] = '\n';
		i++;
		
	}

	out_str[n] = '\0';

	return out_str;
}

int save_into_file(char* filename, char* str) {
	FILE* fp = fopen(filename, "w");
	fputs(str, fp);
	fclose(fp);

	return 0;
}

int main() {
	printf("Please, input any string: \n");
	char* str = read_input();

	printf("Please, input any werb: \n");
	char* word = read_input();

	int n = get_words_count(str);
	int m = get_words_count(word);

	if (!check_input(n, m)) {
		return 0;
	}

	char** array = (char**)malloc(sizeof(char*) * n);

	int min_len = fill_array(n, str, array);
	
	free(str);

	int word_len = get_len(word, 0);

	int i = 0;

	char* file_str = insert_words_and_create_out_str(array, word, min_len, n, word_len);

	free(word);

	while (i < n) {
		printf("%s ", array[i]);
		free(array[i++]);
	}

	free(array);

	save_into_file("source.txt", file_str);

	return 0;
}

// Каждое слово минимальной длины заменять на введенное; результат сохранить в текстовый файл построчно
// Не сохранять слова не из букв и цифр; знаки - разделители