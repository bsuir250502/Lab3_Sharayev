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

typedef struct person {
	struct person *next;
    char surname[16];
    coordinate_t coord;
} person_t;

typedef struct hospital {
	person_t *first;
	person_t *last;
    int num_of_beds;
    int num_of_empty_beds;
    coordinate_t coord;
    int (*dist)(coordinate_t, coordinate_t); 
} hospital_t;




int read_information_of_hospitals(hospital_t *);
char read_argument(int, char **);
int add_patient(hospital_t *, int);
int fit_person_to_the_hospital(hospital_t *,person_t *);
/*

int calculate_distance(coordinate_t, coordinate_t);
person_t* fitting_persons_to_the_hospitals(const hospital_t *, int);
*/

int main(int argc, char **argv)
{
    int num_of_hospitals;
    hospital_t *hosp = NULL;

    if (read_argument(argc, argv) == 'h') {
        print_manual();
        return 0;
    }

    num_of_hospitals = read_information_of_hospitals(hosp);
    printf("num_of_hospitals = %d \n", num_of_hospitals);

    return 0;
}

int read_information_of_hospitals(hospital_t * hosp)
{
    int num_of_hospitals, i;
    char input_buffer[128], *endptr;
    FILE *fp = fopen("Input.in", "r");

    fgets(input_buffer, SIZE(input_buffer), fp);
    num_of_hospitals = strtol(input_buffer, &endptr, 10);
    hosp = (hospital_t *) malloc(num_of_hospitals * sizeof(hosp));

	for(i = 0; i < num_of_hospitals;i++) {
		fgets(input_buffer,SIZE(input_buffer),fp);
		hosp[i].num_of_beds = strtol(input_buffer, &endptr, 10);
	}
	for(i = 0; i < num_of_hospitals;i++) {
		fgets(input_buffer,SIZE(input_buffer),fp);
		hosp[i].num_of_empty_beds = strtol(input_buffer, &endptr, 10);
	}

	for(i = 0; i < num_of_hospitals;i++) {
		fgets(input_buffer,SIZE(input_buffer),fp);
		hosp[i].coord.x = strtol(input_buffer, &endptr, 10);
		hosp[i].coord.y = strtol(endptr, &endptr, 10);
		hosp[i].dist = calculate_distance;
	}
	/*
	for(i = 0; i < num_of_hospitals;i++) {
	printf("(%d;%d)", hosp[i].coord.x ,hosp[i].coord.y );
	}
	*/

    return num_of_hospitals;
}


int add_patient(hospital_t *hosp, int num_of_hospitals) {
	int i, better_hosp_num = 0;
	person_t *patient;
	patient = (person_t *) malloc(sizeof(patient));
	patient->next = NULL;

	printf("Specify the surname of patient(end, to exit):  ");
	myfgets(patient->surname, 16);
	printf("His coordinates(x,y): \n");
	patient->coord.x=input_number_in_range(1,100);
	patient->coord.y=input_number_in_range(1,100);
	for(i=0; i < num_of_hospitals; i++) {
		if( (hosp[i].num_of_beds > hosp[i].num_of_empty_beds) || 
			(hosp[i].dist(hosp[i].coord,patient->coord) < hosp[better_hosp_num].dist(hosp[better_hosp_num].coord,patient->coord)) ) {
				better_hosp_num = i;
			}
	}
	fit_person_to_the_hospital(hosp[better_hosp_num], patient);

	return 0;
}

int fit_person_to_the_hospital(hospital_t *hospital,person_t *patient) {
	if(!(hospital->first)) {
		hospital->first = patient;
	}
	else {
		hospital->last->next = patient;
	}
	hospital->last = patient;

	return 0;
}

char read_argument(int argc, char **argv) {
    if (argc == 2) {
        if (!(strcmp(argv[1], "-h"))) {
            return 'h';
        }
    }

    return '0';
}

int calculate_distance(coordinate_t a, coordinate_t b ) {
	int square_dist;
	square_dist = (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
	return square_dist; 
}
