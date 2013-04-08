#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

typedef struct {
    int num_of_beds;
	int num_of_empty_beds;
	int *(distance)(int, int);
}hospital_t;

char read_argument(int, char **);
int calculate_distance(int);

int main(int argc, char **argv) 
{
    if(read_argument(argc,argv) == "h") {
        print_manual();
        return 0;
    }
    
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

