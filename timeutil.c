#define _POSIX_C_SOURCE 200809L

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

void help() {
    printf("Command to display time in different formats and perform some basic operations.\n");
    printf("\nUsage: timeutil [-h|n|t] [number]");
    printf("\nThe following options are available:\n");
    printf("Everything is done is milliseconds and UTC tz_offset_sec\n");
    printf("-h Display this help\n");
    printf("-n Do everything in nanoseconds\n");
    printf("-t Do everything above in current tz_offset_sec\n");
    printf("-c Convert the number from millis (or nanos) to human readable timestamp\n");
    printf("-d Subtract (diff) the number (millis or nanos) from current time\n");
}

int main(int argc, char *argv[]) {
     int option;
     bool is_nanos = false;
     bool is_current_timezone = false;
     int number = 0;
     // put ':' at the starting of the string so compiler can distinguish between '?' and ':'
     while((option = getopt(argc, argv, ":hntc:d:")) != -1){ //get option from the getopt() method
        switch(option){
            case 'h':
                help();
                return 0;
            case 'n': //here f is used for some file name
                is_nanos = true;
                break;
            case 't':
                is_current_timezone = true;
                break;
            case 'c':
                number = atoi(optarg);
                break;
            case 'd':
                number = atoi(optarg);
                break;
            case '?': //used for some unknown options
                if (optopt == 'c' || optopt == 'd') {
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                }
                return 1;
        }
    }
    
    
    time_t          s;  // Seconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);
    tzset();
    int tz_offset_sec = timezone;
    s  = spec.tv_sec;
    long ns = spec.tv_nsec;
    long nanos = s * 1.0e9 + ns;
    long curr_time = nanos;
    if (is_current_timezone) {
        curr_time = curr_time - (tz_offset_sec * 1.0e9);
    }
    if (!is_nanos) {
        curr_time = curr_time / 1.0e6;
    }
    printf("Current time: %ld\n", curr_time);
       
    
}
