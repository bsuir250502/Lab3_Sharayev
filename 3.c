#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include <math.h>
#define MAX_NUM_OF_HOSPITALS 16
#define MAX_NUM_OF_BEDS 16

typedef struct {
    long int x;
    long int y;
} coordinate_t;

long int calculate_distance(coordinate_t, coordinate_t);

typedef struct person {

    char surname[16];
    coordinate_t coord;
    struct person *next;
} person_t;

typedef struct hospital {
	person_t *first;
	person_t *last;
    int num_of_beds;
    int num_of_empty_beds;
    coordinate_t coord;
    long int (*dist)(coordinate_t, coordinate_t); 
} hospital_t;




hospital_t * read_information_for_hospitals(int *);
char read_argument(int, char **);
int add_patient(hospital_t *, int);
int fit_patient_to_the_hospital(hospital_t *,person_t *);
int find_patient(hospital_t *, char *, int);
int find_better_hospital(person_t *,hospital_t *);

int main(int argc, char **argv)
{
    int num_of_hospitals = 0;
    hospital_t *hosp;

    if (read_argument(argc, argv) == 'h') {
        print_manual();
        return 0;
    }

    hosp = read_information_for_hospitals(&num_of_hospitals);
    while(!(add_patient(hosp, num_of_hospitals)) );

    return 0;
}

hospital_t* read_information_for_hospitals(int *num_of_hospitals)
{
    int i;
	hospital_t *hosp;

	printf("Specify number of hospitals:  ");
    *num_of_hospitals = input_number_in_range(1,MAX_NUM_OF_HOSPITALS);
    hosp = (hospital_t *) malloc(*num_of_hospitals * sizeof(hosp));
    if(!hosp) {
    	printf("Memory isn't allocated");
    	exit(1);
    }

	for(i = 0; i < *num_of_hospitals;i++) {
		printf("Specify number of beds for the %d hospital:  ", i+1);
		hosp[i].num_of_beds = input_number_in_range(1,MAX_NUM_OF_BEDS);
		hosp[i].num_of_empty_beds = hosp[i].num_of_beds;
		printf("Specify coordinates:\n x = ");
		hosp[i].coord.x = input_number_in_range(1,180);
		printf(" y = ");
		hosp[i].coord.y = input_number_in_range(1,180);
		hosp[i].dist = calculate_distance;
		hosp[i].first = NULL;
		hosp[i].last = NULL;

	}

    return hosp;
}


int add_patient(hospital_t *hosp, int num_of_hospitals)
 {
	int i, better_hosp_num = 0;
	person_t *patient;
	char input_buffer[128;]
	
	printf("Specify the surname of a patient(end, to exit):  ");
	myfgets(input_buffer, 16);
	if(!(strcmp(input_buffer, "end")) ) {
		printf("Shutdown\n");
		return 1;
	}
	if(find_patient(hosp, input_buffer, num_of_hospitals)) {
		printf("Enter another surname\n");
		return 0;
	}

	if(!(patient = (person_t *)malloc(sizeof(patient)) )) {
    	printf("Memory isn't allocated");
    	exit(1);
    }
	patient->next = NULL;

	strncpy(patient->surname,input_buffer,16);
	printf("His coordinates(x,y): \n");
	patient->coord.x=input_number_in_range(1,100);
	patient->coord.y=input_number_in_range(1,100);
	
	better_hosp_num = find_better_hospital(patient, hosp);
	if(!better_hosp_num) {
		printf("There is no places in hospitals, you need to specify someone to out of the hospital");
		return 0;
	}
	fit_patient_to_the_hospital(&hosp[better_hosp_num - 1], patient);

	return 0;
}

int find_patient(hospital_t * hosp, char *surname, int num_of_hospitals)
 {
	int i;
	person_t *some_person;

	some_person = (person_t *)malloc(sizeof(some_person));

	for(i=0; i< num_of_hospitals; i++) {
		some_person = hosp[i]->first;
		while(some_person) {
			if(!(strcmp(some_person->surname, surname)) ) {
				printf("Do you want to delete %s from the %d hospital?\n", surname, i + 1);
				if(confirm_choice) {
					printf("deleting");
				}
				return 1;
				}
			}
			some_person = some_person->next;
		}
	}

	return 0;
}

int find_better_hospital(person_t * patient,hospital_t *hosp) 
{
	int i, better_hosp_num = 0;
	for(i=0; i < num_of_hospitals; i++) {
		if( (hosp[i].num_of_beds > hosp[i].num_of_empty_beds) || 
			(hosp[i].dist(hosp[i].coord,patient->coord) < hosp[better_hosp_num].dist(hosp[better_hosp_num].coord,patient->coord)) ) {
				better_hosp_num = i+1;
		}
	}
	return better_hosp_num;
}

int fit_patient_to_the_hospital(hospital_t *hospital,person_t *patient) {
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

long int calculate_distance(coordinate_t a, coordinate_t b ) {
	long int square_dist;
	square_dist = (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
	return square_dist; 
}
