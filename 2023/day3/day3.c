#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int Y1 = -1;
int Y2 = -1;

int get_number(int y, char *line){
	int number = 0;
	int start_y;
	for (start_y = y; start_y >= 0; start_y--) {
		char c = line[start_y];
		if(c < '0' || c > '9'){
			start_y++;
			break;
		}
	}
	start_y = start_y < 0 ? 0 : start_y;
	Y1 = start_y;
	while(start_y < strlen(line) - 1  && '0' <= line[start_y] && line[start_y] <= '9'){
		number = (number*10) + (line[start_y] - '0');
		start_y++;
	}

	Y2 = start_y - 1;

	return number;
	
}

int valid_number(char c){
	if ('0' <= c && c <= '9'){
		return 1;
	}else{
		return 0;
	}
}

long check_around_gear(char **schematic, int index, int curr_i, int max, int line_max){
	int counter = 0;
	long gear_value = 1;
	if(index > 0){
		if(valid_number(schematic[index-1][curr_i])){
			counter++;
			if(!(Y1 <= curr_i &&  curr_i <= Y2)){
				gear_value *= get_number(curr_i, schematic[index-1]);
			}else {
				counter--;
			}

		}
		if(curr_i > 0 && valid_number(schematic[index-1][curr_i-1])){
			counter++;
			if(!(Y1 <= curr_i - 1 &&  curr_i - 1 <= Y2)){
				gear_value *= get_number(curr_i-1, schematic[index-1]);
			}else {
				counter--;
			}
		}
		if (curr_i < (line_max - 1) && valid_number(schematic[index-1][curr_i+1])) {
			counter++;
			if(!(Y1 <= curr_i + 1 &&  curr_i + 1 <= Y2)){
				gear_value *= get_number(curr_i+1, schematic[index-1]);
			}else {
				counter--;
			}

		}
		Y1 = -1;
		Y2 = -1;
	}

	if(index < max - 1){
		if(valid_number(schematic[index+1][curr_i])){
			counter++;
			if(!(Y1 <= curr_i &&  curr_i <= Y2)){
				gear_value *= get_number(curr_i, schematic[index+1]);
			}else {
				counter--;
			}

		}
		if(curr_i > 0 && valid_number(schematic[index+1][curr_i-1])){
			counter++;
			if(!(Y1 <= curr_i-1 &&  curr_i-1 <= Y2)){
				gear_value *= get_number(curr_i-1, schematic[index+1]);
			}else {
				counter--;
			}
		}
		if (curr_i < (line_max - 1) && valid_number(schematic[index+1][curr_i+1])) {
			counter++;
			if(!(Y1 <= curr_i+1 &&  curr_i+1 <= Y2)){
				gear_value *= get_number(curr_i+1, schematic[index+1]);
			}else {
				counter--;
			}
		}

		Y1 = -1;
		Y2 = -1;
	}

	if(curr_i > 0){
		if(valid_number(schematic[index][curr_i - 1])){
			counter++;
			gear_value *= get_number(curr_i-1, schematic[index]);
		}
	}

	if(curr_i < line_max-1){
		if(valid_number(schematic[index][curr_i + 1])){
			counter++;
			gear_value *= get_number(curr_i+1, schematic[index]);
		}
	}
	
	gear_value = counter == 2? gear_value : 0;

	return gear_value;
}

long search_gearline(char **schematic, int index, int max){
	char *line = schematic[index];
	int found = 0;
	int line_length;
	long part_numbers = 0;

	line_length = strlen(line) - 1;
	for (int i = 0; i < line_length; i++) {
		if(line[i] == '*') {
			part_numbers += check_around_gear(schematic, index, i, max, line_length);
		}
	}


	return part_numbers;
}

long find_gears(const char* path){
	FILE *f = fopen(path, "r");
        char *line = NULL;
	char **schematic;
        size_t len = 0;
        ssize_t read;
        long sum = 0;
	int num_of_lines = 0;

	for (char c = getc(f); c != EOF; c = getc(f)) {
        	if (c == '\n'){
			num_of_lines++;
		}
	}

	fseek(f, 0, SEEK_SET);
	schematic = (char**) malloc(num_of_lines * sizeof(char*));
	
	for (int i = 0; i < num_of_lines; i++) {
		schematic[i] = NULL;
	}

	num_of_lines = 0;
	
	while ((read=getline(&schematic[num_of_lines], &len, f)) != -1) {
		num_of_lines++;
	}

	for (size_t i = 0; i < num_of_lines; i++) {
		sum += search_gearline(schematic, i, num_of_lines);

	}

	for (int i = 0; i < num_of_lines; i++) {
		free(schematic[i]);
	}

	free(schematic);
	fclose(f);

	return sum;
}

int valid(char c){
	if(c == '.'){
		return 0;
	}else if ('0' <= c && c <= '9' ){
		return 0;
	}else{
		return 1;
	}
}

int check_around(char **schematic, int index, int curr_i, int max, int line_max){
	if(index > 0){
		if(valid(schematic[index-1][curr_i])){
			return 1;
		}
		if(curr_i > 0 && valid(schematic[index-1][curr_i-1])){
			return 1;
		}
		if (curr_i < (line_max - 1) && valid(schematic[index-1][curr_i+1])) {
			return 1;
		}
	}

	if(index < max - 1){
		if(valid(schematic[index+1][curr_i])){
			return 1;
		}
		if(curr_i > 0 && valid(schematic[index+1][curr_i-1])){
			return 1;
		}
		if (curr_i < (line_max - 1) && valid(schematic[index+1][curr_i+1])) {
			return 1;
		}
	}

	if(curr_i > 0){
		if(valid(schematic[index][curr_i - 1])){
			return 1;
		}
	}

	if(curr_i < line_max-1){
		if(valid(schematic[index][curr_i + 1])){
			return 1;
		}
	}

	return 0;
}

long traverse_line(char **schematic, int index, int max){
	char *line = schematic[index];
	int found = 0;
	int line_length;
	long part_numbers = 0;
	int number = 0;

	line_length = strlen(line) - 1;
	for (int i = 0; i < line_length; i++) {
		if('0' <= line[i] && line[i] <= '9') {
			number = (number*10) + (line[i] - '0');
			if (found == 0) {
				if(check_around(schematic, index, i, max, line_length)){
					found = 1;
				}
			}
		}else {
			if(found == 1){
				part_numbers += number;
				found = 0;
			}
			number = 0;
		}
	}
	if(found == 1){
		part_numbers += number;
		found = 0;
	}


	return part_numbers;
}

long find_parts(const char* path){
	FILE *f = fopen(path, "r");
        char *line = NULL;
	char **schematic;
        size_t len = 0;
        ssize_t read;
        long sum = 0;
	int num_of_lines = 0;

	for (char c = getc(f); c != EOF; c = getc(f)) {
        	if (c == '\n'){
			num_of_lines++;
		}
	}

	fseek(f, 0, SEEK_SET);
	schematic = (char**) malloc(num_of_lines * sizeof(char*));

	for (int i = 0; i < num_of_lines; i++) {
		schematic[i] = NULL;
	}

	num_of_lines = 0;
	
	while ((read=getline(&schematic[num_of_lines], &len, f)) != -1) {
		num_of_lines++;
	}

	for (size_t i = 0; i < num_of_lines; i++) {
		sum += traverse_line(schematic, i, num_of_lines);
	}
	
	for (int i = 0; i < num_of_lines; i++) {
		free(schematic[i]);
	}

	free(schematic);
	fclose(f);

	return sum;
}

int main(int argc, char *argv[])
{
	printf("Challenge 1: Result=%ld\n", find_parts("./input.txt"));
	printf("Challenge 2: Result=%ld\n", find_gears("./input.txt"));
	return EXIT_SUCCESS;
}
