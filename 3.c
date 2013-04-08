#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#define MAX_NUM_OF_HOSPITALS 20

typedef struct hospital {
    int num_of_beds;
    int num_of_empty_beds;
    int *(distance)(int);
} hospital_t;

typedef struct person {
    char surname[16];
    hospital_t hospital;
    struct person *next;
} person_t;

char read_argument(int, char **);
int calculate_distance(int);
int read_information(int *);

int main(int argc, char **argv) 
{
    int num_of_hospitals=0;
    if(read_argument(argc,argv) == 'h') {
        print_manual();
        return 0;
    }
	read_information(&num_of_hospitals);
    
    return 0;
}

char read_argument(int argc, char **argv) {
	if(argc == 2) {
		if(!(strcmp(argv[1], "-h")) ) {
			return 'h';
		} 
	}

	return '0';
}

int calculate_distance(int max_distance) {
	return random_number_in_range(1, max_distance); 
}

int read_information(int *num_of_hospitals) {
	char input_buffer[128], *endptr;
	int i, num_of_beds[MAX_NUM_OF_HOSPITALS], num_of_empty_beds[MAX_NUM_OF_HOSPITALS];
	FILE *fp = fopen("Input.in", "r");
	hospital_t *hosp;

	for(i=0; (fgets(input_buffer,strlen(input_buffer),fp));i++) {
		num_of_beds[i]=strtol(input_buffer, &endptr, 4);
		
	}
	*num_of_hospitals = i;
	for(i=0; i < *num_of_hospitals; i++) {
		fgets(input_buffer,strlen(input_buffer),fp);
		num_of_empty_beds[i]=strtol(input_buffer, &endptr, 4);
	}
	hosp=(hospital_t *)malloc(*num_of_hospitals * sizeof(hospital_t));
	for(i=0; i < *num_of_hospitals; i++) {
		hosp[i].num_of_beds = num_of_beds[i];
		hosp[i].num_of_empty_beds = num_of_empty_beds[i];
	}

	return 0;
}

