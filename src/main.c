#include <stdio.h>
#include <string.h>
#include "ppm.h"
#include "histo.h"
#include "filter.h"

char **global_argv;
int global_argc;

//reminder: argc is the number of command line arguments, argv is the list of these arguments
int main(int argc, char *argv[]){
    
    //test_all_functions();
    global_argv = argv;
    global_argc = argc;
    identify_arguments();

    return 0;
}
