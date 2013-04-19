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
    long int (*dist) (coordinate_t, coordinate_t);
} hospital_t;

hospital_t *read_information_for_hospitals(int *);
char read_argument(int, char **);
int add_patient(hospital_t *, int);
int place_patient_to_the_hospital(hospital_t *, person_t *);
int free_hospital_beds(hospital_t *, int);
int find_better_hospital(hospital_t *, person_t *, int);
int discharge_patient(hospital_t *);
int print_information_of_hospitals(hospital_t *, int);
int free_memory(hospital_t *, int);

int main(int argc, char **argv)
{
    int num_of_hospitals = 0;
    hospital_t *hosp;

    if (read_argument(argc, argv) == 'h') {
        print_manual();
        return 0;
    }

    hosp = read_information_for_hospitals(&num_of_hospitals);
    printf("Do you want to see the information of hospitals?");
    if(confirm_choice()) {
        print_information_of_hospitals(hosp, num_of_hospitals);
    }  
    while (!(add_patient(hosp, num_of_hospitals)) );
    print_information_of_hospitals(hosp, num_of_hospitals);

    free_memory(hosp, num_of_hospitals);
    return 0;
}

hospital_t *read_information_for_hospitals(int *num_of_hospitals)
{
    int i;
    char input_buffer[128], *endptr;
    FILE *fp = fopen("Input.in", "r");
    hospital_t *hosp;

    fgets(input_buffer, SIZE(input_buffer), fp);
    *num_of_hospitals = strtol(input_buffer, &endptr, 10);
    hosp = (hospital_t *) malloc(*num_of_hospitals * sizeof(*hosp));
    if (!hosp) {
        printf("Memory isn't allocated");
        exit(1);
    }

    for (i = 0; i < *num_of_hospitals; i++) {
        fgets(input_buffer,SIZE(input_buffer),fp);
        hosp[i].num_of_beds = strtol(input_buffer, &endptr, 10);
        hosp[i].num_of_empty_beds = hosp[i].num_of_beds;
        fgets(input_buffer,SIZE(input_buffer),fp);
        hosp[i].coord.x = strtol(input_buffer, &endptr, 10);
        hosp[i].coord.y = strtol(endptr, &endptr, 10);
        hosp[i].dist = calculate_distance;
        hosp[i].first = NULL;
        hosp[i].last = NULL;

    }

    fclose(fp);
    return hosp;
}

int add_patient(hospital_t * hosp, int num_of_hospitals)
{
    int better_hosp_num = 0;
    person_t *patient;
    char input_buffer[128];

    printf("Specify the surname of a patient(end, to exit): ");
    myfgets(input_buffer, 16);
    if (!(strcmp(input_buffer, "end"))) {
        printf("Shutdown\n");
        return 1;
    }
    if (!(patient = (person_t *) malloc(sizeof(*patient)) )) {
        printf("Memory isn't allocated");
        exit(1);
    }
    
    patient->next = NULL;

    strncpy(patient->surname, input_buffer, 16);
    printf("His coordinates:\n x = ");
    patient->coord.x = input_number_in_range(0, 180);
    printf(" y = ");
    patient->coord.y = input_number_in_range(0, 180);

    better_hosp_num = find_better_hospital(hosp, patient, num_of_hospitals);
    if (!better_hosp_num) {
        printf
            ("There is no places in hospitals, do you want to free some of it?\n");
            if(confirm_choice()) {
                free_hospital_beds(hosp, num_of_hospitals);
                free(patient);
                return 0;
            }
        printf("Shutdown\n");
        return 1;
    }
    place_patient_to_the_hospital(&hosp[better_hosp_num - 1], patient);
    hosp[better_hosp_num - 1].num_of_empty_beds--;

    return 0;
}

int free_hospital_beds(hospital_t * hosp, int num_of_hospitals)
{
    int i;

    for (i = 0; i < num_of_hospitals; i++) {
        while (hosp[i].first) {
            printf("Do you want to delete %s from the %d hospital?\n",
                       hosp[i].first->surname, i + 1);
            if (!(confirm_choice()) ) {
                break; 
            }
            printf("Deleting...\n");
            discharge_patient(&hosp[i]);
            hosp[i].num_of_empty_beds++;
        }
    }

    return 0;
}

int discharge_patient(hospital_t *hosp)
{
    person_t *tmp;

    if(!hosp->first) {
        return 1;
    }
    tmp = hosp->first->next;
    free(hosp->first);
    hosp->first = tmp;
    
    return 0;
}

int find_better_hospital(hospital_t * hosp, person_t * patient, int num_of_hospitals)
{
    int i, better_hosp_num = 0;
    for (i = 0; i < num_of_hospitals; i++) {
        if ((hosp[i].num_of_empty_beds > 0) ||
            (hosp[i].dist(hosp[i].coord, patient->coord) <
             hosp[better_hosp_num].dist(hosp[better_hosp_num].coord, patient->coord)) ) {
            better_hosp_num = i + 1;
        }
    }

    return better_hosp_num;
}

int place_patient_to_the_hospital(hospital_t * hospital, person_t * patient)
{
    if (!(hospital->first)) {
        hospital->first = patient;
    } else {
        hospital->last->next = patient;
    }
    hospital->last = patient;

    return 0;
}


char read_argument(int argc, char **argv)
{
    if (argc == 2) {
        if (!(strcmp(argv[1], "-h")) ) {
            return 'h';
        }
    }

    return '0';
}

long int calculate_distance(coordinate_t a, coordinate_t b)
{
    long int square_dist;
    square_dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    return square_dist;
}

int free_memory(hospital_t *hosp, int num_of_hospitals)
{
    int i;

    for (i = 0; i < num_of_hospitals; i++) {
        while (!(discharge_patient(&hosp[i])) );
    }

    free(hosp);
    return 0;
}

int print_information_of_hospitals(hospital_t *hosp, int num_of_hospitals)
{
    int i;
    person_t *some_person;

    for (i = 0; i < num_of_hospitals; i++) {
        
        printf("Information of the %d hospital:\n", i + 1);
        printf("  Number of beds:  %d\n", hosp[i].num_of_beds);
        printf("  Number of emty beds:  %d\n", hosp[i].num_of_empty_beds);
        printf("  Coordinates:  (%ld; %ld)\n", hosp[i].coord.x, hosp[i].coord.y);
        if(hosp[i].first) {
            some_person = hosp[i].first;
            printf("  List of patents:\n");
            while (some_person) {
                printf("    %s\n",some_person->surname);
                some_person = some_person->next;
            }
        }
    }

    return 0;
}
