#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool print_time_string() {
	time_t globaltime = time(NULL);
	struct tm* time = localtime(&globaltime);
	if(time == NULL) {
		perror("Retreiving localtime failed. ");
		return false; // unsuccessful
	}

	size_t const time_string_len = 64; // in characters
	char time_string[time_string_len];
	strftime(time_string, time_string_len, "%k:%M %D", time); // format codes in `man strftime`
	fputs(time_string, stdout);
	return true;
}

// TODO: 
// - volume level module
// - email client notifier (how many unread)
// - weather
// - music player status
// - calendar events
// - task tracking softwares status
// - keyboard layout
// - make a config file to read from that can toggle which modules are active
// - make it so you can reorder it in the config
int main(int argc, char* argv[]) {
	print_time_string();
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
