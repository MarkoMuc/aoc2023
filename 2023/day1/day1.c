#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int check_word_num(char* test, int line_count);

int shift_check(char* line, int size, int line_count){
	if(size - line_count < 3) return -1;

	char *check_array = (char*) malloc(sizeof(char) * 6);
	int res = -1;
	for (size_t i = 3; i <= 5; i++) {
		memcpy(check_array, line, i);
		if((res=check_word_num(check_array, i)) > 0){
			return res;
		}
	}
	
	free(check_array);
	return res;
	
}

int check_word_num(char* test, int line_count){
	test[line_count] = '\0';
	if (line_count == 0) {
		return -1;
	}

	if (strcmp(test, "one") == 0) {
		return 1;
	}else if (strcmp(test, "two") == 0) {
		return 2;
	}else if (strcmp(test, "three") == 0) {
		return 3;
	}else if (strcmp(test, "four") == 0) {
		return 4;
	}else if (strcmp(test, "five") == 0) {
		return 5;
	}else if (strcmp(test, "six") == 0) {
		return 6;
	}else if (strcmp(test, "seven") == 0) {
		return 7;
	}else if (strcmp(test, "eight") == 0) {
		return 8;
	}else if (strcmp(test, "nine") == 0) {
		return 9;
	}

	return -1;
}

long find_sum(const char* path){
	FILE *f = fopen(path, "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	long result = 0;
	char num_line[256];
	while((read = getline(&line, &len, f)) != -1){
		int first_digit = 0;
		int first = 0;
		int last = 0;
		int line_count = 0;

		for(int i = 0; i < read; i++){

			if ('0' <= line[0] && line[0] <= '9'){

				if (first_digit != -1){
					first = line[0] - '0';
					last = first;
					first_digit = -1;
				}else{
					last = line[0] - '0';
				}

			}else{
				int num = 0;
				if ((num=shift_check(line, read, line_count)) > -1){
					if (first_digit != -1){
						first = num;
						last = first;
						first_digit = -1;
					}else {
						last = num;
					}
				}

			}

			memmove(line, &line[1], sizeof(char)*(read - i));
		}
		result += (10*first) + last;
	}
	
	fclose(f);
	return result;
}

long find_sum_digits(const char* path){
	FILE *f = fopen(path, "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	long result = 0;

	while((read = getline(&line, &len, f)) != -1){
		int first_digit = 0;
		int first = 0;
		int last = 0;

		for(int i = 0; i < read; i++){

			if ('0' <= line[i] && line[i] <= '9'){

				if (first_digit != -1){
					first = line[i] - '0';
					last = first;
					first_digit = -1;
				}else{
					last = line[i] - '0';
				}

			}
		}
		result += (10*first) + last;
	}
	
	fclose(f);
	return result;
}
int main(int argc, char **argv)
{
	printf("Challenge 1: Result=%ld\n",find_sum_digits("./input.txt"));
	printf("Challenge 2: Result=%ld\n",find_sum("./input.txt"));
	return EXIT_SUCCESS;
}
