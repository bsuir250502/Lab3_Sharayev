#include "mylib.h"

char* myfgets(char *str, int num)
{
    if( !(fgets(str, num, stdin)) ){
      return 0;
    }
    else {
      str[strlen(str)-1]='\0';
    }

    return str;
}

int print_manual(int argc,char **argv){
    int i;
    
    char input_buffer[128];
  if(argc > 1 && !(strcmp(argv[1] ,"-h")) ) {
        FILE *fp=fopen("D:\Manual.txt","r");
        while(fgets(input_buffer,strlen(input_buffer),fp))
        {
            printf("%s",input_buffer);
        }
        printf("\n");
        fclose(fp);
        return 1;
    }

    return 0;
}

int input_number_in_range(int from, int to)
{
    int n;
    char *endptr;
    char input_buffer[128];
    int first = 1;
    do {
        if(!first){
            printf("Please enter number between %d and %d\n", from, to);
        }
        myfgets(input_buffer, 128);
        n = strtol(input_buffer, &endptr, 10);
        first = 0;
    } while( *endptr || n < from || n > to);
    return n;
}
