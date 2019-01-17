#include <stdio.h>
#include <string.h>
#include "ppm.h"
#include "histo.h"
#include "filter.h"

//these variables are also declared in filter.c so that we can use what the user has written to apply filters
char **global_argv;
int global_argc;

//reminder: argc is the number of command line arguments, argv is the list of these arguments
int main(int argc, char *argv[]){
    
    //test_all_functions();
    global_argv = argv;
    global_argc = argc;
    final_LUT(identify_arguments());


    return 0;
}
