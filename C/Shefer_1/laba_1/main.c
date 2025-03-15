#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int running = 1;
	printf("if you enter '-1', programm whill be stoped");
	while (running == 1) {
		int N, min_a, max_b;
		printf("\nplease, enter the number: "); scanf(" %d", &N);
		if (N == -1) {
			return 0;
		}
		min_a = my_pow(2, my_log(N, 2));
		max_b = my_pow(2, my_log(N, 2) + 1);
		if (N - min_a < max_b - N) {
			printf("nearest power of two: %d", my_log(min_a, 2));
		}
		else {
			printf("nearest power of two: %d", my_log(max_b, 2));
		}
		check_log(N);
	}

}

int my_log(x, a) {
	int res = -1;
	while (x >= 1) {
		x /= a;
		res += 1;
	}
	return res;
}

int is_log(x, a) {
	while (x > a) {
		x /= a;
	}
	if (x == a) {
		return 1;
	}
	else {
		return 0;
	}
}

int check_log(x) {
	int checking_diapozone[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (int i = 0; i < 6; ++i) {
		if (is_log(x, checking_diapozone[i]) == 1) {
			printf("\n%d is a %d power of %d", x, my_log(x, checking_diapozone[i]), checking_diapozone[i]);
		}
	}
}

int my_pow(x, a) {
	int out = 1;
	for (int i = 0; i < a; ++i) {
		out *= x;
	}
	return out;
}