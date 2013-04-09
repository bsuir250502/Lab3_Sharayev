#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include <math.h>
#define MAX_NUM_OF_HOSPITALS 12

typedef struct {
	int x;
	int y;
} coordinate_t;

int calculate_distance(coordinate_t, coordinate_t);

typedef struct hospital {
	int num_of_beds;
	int num_of_empty_beds;
	coordinate_t coord;
	int *(distance)(coordinate_t, coordinate_t);
} hospital_t;

typedef struct person {
	char surname[16];
	int hospital;
	coordinate_t coord;
	struct person *next;
} person_t;

char read_argument(int, char **);
int calculate_distance(coordinate_t, coordinate_t);
hospital_t* read_information(int *);
person_t* fitting_persons_to_the_hospitals(hospital_t *, int);

int main(int argc, char **argv) 
{
	int num_of_hospitals=0;
	hospital_t *hosp;
	person_t *person;
    if(read_argument(argc,argv) == 'h') {
        print_manual();
        return 0;
    }
    hosp = read_information(&num_of_hospitals);
	person = fitting_persons_to_the_hospitals(hosp, num_of_hospitals);
	
    return 0;
}

person_t* fitting_persons_to_the_hospitals(const hospital_t *hosp, const int num_of_hospitals) {
	int num_of_persons, i, j, hospital_num;
	person_t *person;
	num_of_persons=input_number_in_range(1,100);
	person = (person_t *)malloc(num_of_persons * sizeof(person_t));
	for(i = 0; i < num_of_persons; i++) {
		printf("Supply surname of the %d person:\n", i+1);
		myfgets(person[i].surname,16);
		for(j = 0; j < num_of_hospitals; j++) {
			if( hosp[j].num_of_beds > hosp[j].num_of_empty_beds) {
				hospital_num=j;
			}
		}
		person[i].hospital = hospital_num;
	}

	return person;
}


char read_argument(int argc, char **argv) {
	if(argc == 2) {
		if(!(strcmp(argv[1], "-h")) ) {
			return 'h';
		} 
	}

	return '0';
}

int calculate_distance(coordinate_t a, coordinate_t b ) {
	int square_dist;
	square_dist = (a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y);
	return dist(square_dist); 
}

hospital_t* read_information(int *num_of_hospitals) {
	char input_buffer[128], *endptr;
	int i, num_of_beds[MAX_NUM_OF_HOSPITALS], num_of_empty_beds[MAX_NUM_OF_HOSPITALS];
	FILE *fp = fopen("D:\Input.txt", "r");
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

	return hosp;
}
