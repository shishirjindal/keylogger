// checking for shift key
static int isShiftPressed(int eventcode);

// checking for capslock
static int isCapsOn(int eventcode);

// check for chars like !@#$%^&*()_{}:"<>?
static char *checkKey(char *key);

// convert event code to corresponding char
static char *pressedKey(int eventcode);