#include "my_lab.h"

using namespace std;

size_t _strcspn(const char* str1, const char* str2) {
	int i = 0;
	int n = 0;
	
	while (str1[i] != '\0' && str1[i] != '\n') {
		n = 0;
		while (str2[n] != '\0' && str2[n] != '\n') {
			if (str1[i] == str2[n]) {
				return i;
			}
			n++;
		}
		i++;
	}
	
	return i;
}

int test(char* str1, char* str2) {
	size_t my_result = _strcspn(str1, str2);
	size_t std_result = strcspn(str1, str2);

	cout << "Result of my function: " << my_result << endl;
	cout << "Result of standart function: " << std_result << endl;
	
	if (my_result == std_result) {
		cout << "Test passed" << endl;
	}
	else {
		cout << "Test failed" << endl;
	
	}
	system("pause>nul");
	
	return 0;
}