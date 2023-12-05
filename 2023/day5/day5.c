#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define INPUT "./input.txt"

void map_d2s_r(FILE *f, long *dst, long size){
	long *old_src = (long*) malloc(sizeof(long) * size);
	char *line = NULL;
	char *token = NULL;
	char *str = NULL;
	size_t len = 0;
        ssize_t read;
	
	memcpy(old_src, dst, size*sizeof(long));
	
        while ((read=getline(&line, &len, f)) != -1) {
	
		if(line[0] < '0' || line[0] > '9'){
			break;
		}
		long dest_s = 0;
		long src_s = 0;
		long range = 0;
		
		token=strtok_r(line, " ", &str);
		dest_s = atol(token);
		
		token=strtok_r(NULL, " ", &str);
		src_s = atol(token);

		token=strtok_r(NULL, " ", &str);
		range = atol(token);
		
		for (long i = 0; i < size; i++) {
			if(src_s <= old_src[i] && old_src[i] < src_s + range){
				dst[i] = dest_s + (old_src[i] - src_s); 
			}
		}
	}
	free(old_src);
}

long seed_to_location_r(const char *path){
	FILE *f = fopen(path, "r");
        char *line = NULL;
        long *source;
	size_t len = 0;
        ssize_t read;
        long min = 0;
	long numbers = 0;
	read=getline(&line, &len, f);
	
	for (size_t i = 7; i < read; i++) {
		if((line[i] < '0' || line[i] > '9')){
			numbers++;
		}
	}

	source = (long*) malloc(sizeof(long) * numbers);

	long num = 0;
	long index = 0;
	
	for (size_t i = 7; i < read; i++) {
		if('0' <= line[i] && line[i] <= '9'){
			num = (num * 10) + (line[i] - '0');
		}else {
			source[index] = num;
			index++;
			num = 0;
		}
	}

        while ((read=getline(&line, &len, f)) != -1) {
		if(line[0] >= 'a' && line[0] <= 'z'){
			map_d2s_r(f, source, numbers);
		}
        }

	min = source[0];
	for (long i = 1; i < numbers; i++) {
		min = min > source[i] ? source[i] : min;
	}

	free(source);
        fclose(f);
        return min;

}
void map_d2s(FILE *f, long *dst, long size){
	long *old_src = (long*) malloc(sizeof(long) * size);
	char *line = NULL;
	char *token = NULL;
	char *str = NULL;
	size_t len = 0;
        ssize_t read;
	
	memcpy(old_src, dst, size*sizeof(long));
	
        while ((read=getline(&line, &len, f)) != -1) {
		if(line[0] < '0' || line[0] > '9'){
			break;
		}
		long dest_s = 0;
		long src_s = 0;
		long range = 0;
		
		token=strtok_r(line, " ", &str);
		dest_s = atol(token);
		
		token=strtok_r(NULL, " ", &str);
		src_s = atol(token);

		token=strtok_r(NULL, " ", &str);
		range = atol(token);
		
		for (long i = 0; i < size; i++) {
			if(src_s <= old_src[i] && old_src[i] < src_s+range){
				dst[i] = dest_s + (old_src[i]-src_s); 
			}
		}
	}
	free(old_src);
}

long seed_to_location(const char *path){
	FILE *f = fopen(path, "r");
        char *line = NULL;
        long *source;
	size_t len = 0;
        ssize_t read;
        long min = 0;
	long numbers = 0;
	read=getline(&line, &len, f);
	int a = strlen(line);
	for (size_t i = 7; i < read; i++) {
		if((line[i] < '0' || line[i] > '9')){
			numbers++;
		}
	}
	source = (long*) malloc(sizeof(long) * numbers);

	long num = 0;
	long index = 0;

	for (size_t i = 7; i < read; i++) {
		if('0' <= line[i] && line[i] <= '9'){
			num = (num * 10) + (line[i] - '0');
		}else {
			source[index] = num;
			index++;
			num = 0;
		}
	}
	
        while ((read=getline(&line, &len, f)) != -1) {
		if(line[0] >= 'a' && line[0] <= 'z'){
			map_d2s(f, source, numbers);
		}
        }

	min = source[0];
	for (long i = 1; i < numbers; i++) {
		min = min > source[i] ? source[i] : min;
	}

	free(source);
        fclose(f);
        return min;

}

int main(int argc, char *argv[])
{
	printf("Challenge 1: Result=%ld\n", seed_to_location(INPUT));
	printf("Challenge 2: Result=%ld\n", seed_to_location_r(INPUT));
	return EXIT_SUCCESS;
}
