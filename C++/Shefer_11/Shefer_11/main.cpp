#include "my_lab.h"

using namespace std;

int main() {
	char str1[100];
	char str2[100];

	cout << "Enter first string: ";
	cin.getline(str1, 100);

	cout << "Enter second string: ";
	cin.getline(str2, 100);

	test(str1, str2);

	return 0;
}