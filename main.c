#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>

#define KEY_PRESS 1
#define KEY_RELEASE 0

int main(){
	typedef struct input_event input_event;
	input_event event;
	int shift = 0;
	int caps = 0;
	if(geteuid() != 0){
		printf("You must be root\n");
		exit(0);
	}
	int fp = open("/dev/input/event4", O_RDONLY);
	if(fp == -1){
		perror("Device file not found");
		exit(0);
	}
	while(1){
		if(read(fp, &event, sizeof(input_event))>0){
			if(event.type == EV_KEY){
				if(event.value == KEY_PRESS){
					printf("%d\n", event.code);
				}
			}
		}
	}
	close(fp);
	return 0;
}
