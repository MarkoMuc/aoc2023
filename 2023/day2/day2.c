#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define RED_MAX 12
#define GREEN_MAX 13
#define BLUE_MAX 14

void parse_color_compare(char* token, int *rgb){
	int index = 0;
	int value = 0;
	int digit = 0;
	while(token[index] != ' ' || digit == 0){
		if ('0' <= token[index] && token[index] <= '9') {
			value = (value*10) + (token[index] - '0');
			digit = 1;
		}

		index++;
	}
	index++;

	if(token[strlen(token) - 1] == '\n'){
		token[strlen(token) - 1] = '\0';
	}

	if(strcmp(&token[index], "red") == 0){
		rgb[0] = value > rgb[0] ?  value : rgb[0];
	}else if(strcmp(&token[index], "green") == 0){
		rgb[1] = value > rgb[1] ?  value : rgb[1];
	}else if(strcmp(&token[index], "blue") == 0){
		rgb[2] = value > rgb[2] ? value : rgb[2];
	}
	
}

int parse_token_compare(char* token, int *rgb){
	char* save_pntr = token;
	while((token=strtok_r(save_pntr, ",", &save_pntr)) != NULL){
		parse_color_compare(token, rgb);
	}

	return 0;
}

long min_bag(const char* path){
	FILE *f = fopen(path, "r");
	char *line = NULL;
        char *save_pntr, *token;
	size_t len = 0;
        ssize_t read;
        long sum = 0;
	
	while ((read=getline(&line, &len, f)) != -1) {
		int ID = 0;
		int index = 0;
		int rgb[] = {[0 ... 2]=1};

		while(line[index] != ':'){
			if('0' <= line[index] && line[index] <= '9'){
				ID = (ID * 10) + (line[index] - '0');
			}
			index++;
		}
		save_pntr = &line[index + 1];
		
		while((token=strtok_r(save_pntr, ";", &save_pntr)) != NULL){
			parse_token_compare(token, rgb);
		}
		
		sum += rgb[0] * rgb[1] * rgb[2];
	}

	return sum;
}


int parse_color(char* token){
	int index = 0;
	int value = 0;
	int digit = 0;
	while(token[index] != ' ' || digit == 0){
		if ('0' <= token[index] && token[index] <= '9') {
			value = (value*10) + (token[index] - '0');
			digit = 1;
		}

		index++;
	}
	index++;

	if(token[strlen(token) - 1] == '\n'){
		token[strlen(token) - 1] = '\0';
	}

	if(strcmp(&token[index], "red") == 0){
		return value > RED_MAX ? -1 : 0;
	}else if(strcmp(&token[index], "green") == 0){
		return value > GREEN_MAX ? -1 : 0;
	}else if(strcmp(&token[index], "blue") == 0){
		return value > BLUE_MAX ? -1 : 0;
	}
	
	return -1;
}

int parse_token(char* token){
	char* save_pntr = token;
	while((token=strtok_r(save_pntr, ",", &save_pntr)) != NULL){
		if(parse_color(token) == -1){
			return -1;
		}
	}

	return 0;
}

long check_limits(const char* path){
	FILE *f = fopen(path, "r");
	char *line = NULL;
        char *save_pntr, *token;
	size_t len = 0;
        ssize_t read;
        long sum = 0;
	
	while ((read=getline(&line, &len, f)) != -1) {
		int ID = 0;
		int index = 0;
		int valid = 1;

		while(line[index] != ':'){
			if('0' <= line[index] && line[index] <= '9'){
				ID = (ID * 10) + (line[index] - '0');
			}
			index++;
		}
		save_pntr = &line[index + 1];
		
		while((token=strtok_r(save_pntr, ";", &save_pntr)) != NULL){
			if(parse_token(token) == -1 ){
				valid = 0;
				break;
			}
		}

		if (valid == 1) {
			sum += ID;
		}
	}

	return sum;
}

int main(int argc, char *argv[])
{
	printf("Challenge 1: Result=%ld\n", check_limits("./input.txt"));
	printf("Challenge 2: Result=%ld\n", min_bag("./input.txt"));
	return EXIT_SUCCESS;
}
