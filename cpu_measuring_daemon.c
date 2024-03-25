/*
 * =====================================================================================
 *
 *       Filename:  cpu_measuring_daemon.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/26/2024 12:09:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

volatile int terminate = false;

static void handle_termination(int signum)
{
    terminate = true;
}

static void init_service(void)
{
    signal(SIGINT, handle_termination);
    signal(SIGTERM, handle_termination);
}

static void main_loop () {

	char temp_str[20];
	FILE *cpu_temp_file = fopen("/home/uriel/work/coding/c/daemon/cpu_temperature_readings.txt", "w");

	while(!terminate){

		FILE *cpu_temp  = fopen("/sys/class/hwmon/hwmon1/temp1_input", "r");

        if (cpu_temp == NULL) {
            fprintf(stderr, "Error opening temperature file\n");
            exit(EXIT_FAILURE); // or handle the error appropriately
        }

		if (fgets(temp_str, sizeof(temp_str), cpu_temp) != NULL) {
            fprintf(stderr, "CPU Temperature: %s", temp_str);
			fprintf(cpu_temp_file, "%s", temp_str);
            fflush(cpu_temp_file); // Flush the buffer to ensure data is written immediately
        } else {
            fprintf(stderr, "Error reading temperature from file\n");
        }

		fclose(cpu_temp);
		sleep(1);
	}

	fclose(cpu_temp_file);	
	system("./cpu_reading_graph.py");

}

int main(int *agrc, char** argv) {

	init_service();
	main_loop();
	return 0;
}
