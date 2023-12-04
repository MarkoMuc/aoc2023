#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "./input.txt"

long calc_cards(int *points, int max){
	long sum = 0;
	int *copies = (int*) calloc(max, sizeof(int));
	for (int i = 0; i < max; i++) {
		for(int j = 1; j <= points[i]; j++){
			copies[i+j] += copies[i] == 0? 1 : copies[i] + 1;
		}
	}
	for (int i = 0; i < max; i++) {
		sum += 1 + copies[i];
	}
	free(copies);
	return sum;
}

long count_cards(char *win, char* cand){
	long points = 0;
	char *token;
	cand++;

	while((token=strtok_r(cand, " ", &cand)) != NULL){
		token[strlen(token) - 1] = token[strlen(token) - 1] == '\n' ? '\0' : token[strlen(token) - 1];
		int len = strlen(win);
		int token_max = strlen(token);
		int index_token = 0;
		int reset = 0;
		for (int i = 0; i < len; i++) {
			if('0' <= win[i] && win[i] <= '9'){
				if(index_token < token_max && win[i] != token[index_token]){
					reset = 1;
				}else if (index_token >= token_max) {
					reset = 1;
				}
				index_token++;

			}else{
				if(!reset && index_token == token_max){
					points++;
				}
				index_token = 0;
				reset = 0;
			}
		}
	}
	return points;
}

long num_cards(const char* path){
	FILE *f = fopen(path, "r");
        char *line = NULL;
        char *save_pntr, *win_nums, *cand_nums;
	int* points;
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
	points = (int*) calloc(num_of_lines, sizeof(int));

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
		ID = ID - 1;
                save_pntr = &line[index + 1];

                win_nums = strtok_r(save_pntr, "|", &save_pntr);
                cand_nums = strtok_r(save_pntr, "|", &save_pntr);

		points[ID] = count_cards(win_nums, cand_nums);
        }
	sum = calc_cards(points, num_of_lines);

	free(points);
        fclose(f);
        return sum;
}

long check_numbers(char *win, char* cand){
	long points = 0;
	char *token;
	cand++;

	while((token=strtok_r(cand, " ", &cand)) != NULL){
		token[strlen(token) - 1] = token[strlen(token) - 1] == '\n' ? '\0' : token[strlen(token) - 1];
		int len = strlen(win);
		int token_max = strlen(token);
		int index_token = 0;
		int reset = 0;
		for (int i = 0; i < len; i++) {
			if('0' <= win[i] && win[i] <= '9'){
				if(index_token < token_max && win[i] != token[index_token]){
					reset = 1;
				}else if (index_token >= token_max) {
					reset = 1;
				}
				index_token++;

			}else{
				if(!reset && index_token == token_max){
					points = points == 0? 1 : points*2;
				}
				index_token = 0;
				reset = 0;
			}
		}
	}
	return points;
}

long sum_scards(const char* path){
	FILE *f = fopen(path, "r");
        char *line = NULL;
        char *save_pntr, *win_nums, *cand_nums;
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

                win_nums = strtok_r(save_pntr, "|", &save_pntr);
                cand_nums = strtok_r(save_pntr, "|", &save_pntr);

		sum += check_numbers(win_nums, cand_nums);
        }

        fclose(f);
        return sum;
}


int main(int argc, char *argv[])
{
	printf("Challenge 1: Result=%ld\n", sum_scards(INPUT));
	printf("Challenge 2: Result=%ld\n", num_cards(INPUT));
	return EXIT_SUCCESS;
}
