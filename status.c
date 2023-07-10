#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>

bool print_time_string() {
	// Get the current time
	time_t globaltime = time(NULL);
	struct tm* time = localtime(&globaltime);
	if(time == NULL) {
		perror("Retreiving localtime failed. ");
		return false; // unsuccessful
	}

	// Format it to a string
	size_t const time_string_len = 64; // in characters
	char time_string[time_string_len];
	strftime(time_string, time_string_len, "%k:%M %D", time); // format codes in `man strftime`

	// Print the string and return exit status
	fputs(time_string, stdout);
	return true;
}

bool print_volume_level() {

	// Open the command for reading
	FILE* fp = popen("amixer -D pulse get Master | grep -o '[0-9]*%'", "r");
	if(fp == NULL) {
		perror("Error opening amixer command. ");
		return false;
	}

	// Read the output from the command
	char volume[3];
	size_t i = 0;
	for(char curr = fgetc(fp); curr != EOF && curr != '%' && i < 3; curr = fgetc(fp)) {
		volume[i] = curr;
		i += 1;
	}
	fputs(volume, stdout);

	// Print appropriate speaker symbol
	const char* no_volume   = "󰖁";
	const char* low_volume  = "󰕿";
	const char* med_volume  = "󰖀";
	const char* high_volume = "󰕾";

	int volume_num = atoi(volume);
	if(volume_num > 70) {
		printf(high_volume);
	}
	else if(volume_num > 30) {
		printf(med_volume);
	}
	else if(volume_num > 0){
		printf(high_volume);
	}
	else {
		printf(no_volume);
	}

	// close the pipe and return exit status
	pclose(fp);
	return true;
}

int main(int argc, char* argv[]) {
	print_volume_level();
	fputc(' ', stdout);
	print_time_string();
	fputc(' ', stdout);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
