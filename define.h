// defines
#define KEY_PRESS 1
#define KEY_RELEASE 0
#define LEFTSHIFT 42
#define RIGHTSHIFT 54
#define CAPSLOCK 58
#define ROOTID 0

// initializations
typedef struct input_event input_event;
input_event event;
int shift = 0;
int caps = 0;					// assuming capslock to be off


// arrays for keys(for both small and capital chars including chars like !@#$%^&*())
static char *keys_upper[] = {"<RESERVED>", "<ESC>", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "<BACKSPACE>", "	", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "\n", "<LEFTCTRL>", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", "<LEFTSHIFT>", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "<RIGHTSHIFT>", "*", "<LEFTALT>", " ", "<CAPSLOCK>", "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>", "<NUMLOCK>", "<SCROLLLOCK>", "7", "8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "" ,"<ZENKAKUHANKAKU>", "102ND", "<F11>", "<F12>", "<RO>", "<KATAKANA>", "<HIRAGANA>", "<HENKAN>", "<KATAKANAHIRAGANA>", "<MUHENKAN>", "<JPCOMMA>", "\n", "<RIGHTCTRL>", "/", "<SYSRQ>", "<RIGHTALT>", "<LINEFEED>", "<HOME>", "<UP>", "<PAGEUP>", "<LEFT>", "<RIGHT>", "<END>", "<DOWN>", "<PAGEDOWN>", "<INSERT>", "<DELETE>", "<MACRO>", "<MUTE>", "<VOLUMEDOWN>", "<VOLUMEUP>", "<POWER>", "<KPEQUAL>", "<KPPLUSMINUS>", "<PAUSE>", "<SCALE>", "<KPCOMMA>", "<HANGEUL>", "<HANJA>", "<YEN>", "<LEFTMETA>", "<RIGHTMETA>", "<COMPOSE>"};
static char *keys_lower[] = {"<reserved>", "<esc>", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "<backspace>", "	", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\n", "<leftctrl>", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", "<leftshift>", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "<rightshift>", "*", "<leftalt>", " ", "<capslock>", "<f1>", "<f2>", "<f3>", "<f4>", "<f5>", "<f6>", "<f7>", "<f8>", "<f9>", "<f10>", "<numlock>", "<scrolllock>", "7", "8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "" ,"<zenkakuhankaku>", "102nd", "<f11>", "<f12>", "<ro>", "<katakana>", "<hiragana>", "<henkan>", "<katakanahiragana>", "<muhenkan>", "<jpcomma>", "\n", "<rightctrl>", "/", "<sysrq>", "<rightalt>", "<linefeed>", "<home>", "<up>", "<pageup>", "<left>", "<right>", "<end>", "<down>", "<pagedown>", "<insert>", "<delete>", "<macro>", "<mute>", "<volumedown>", "<volumeup>", "<power>", "<kpequal>", "<kpplusminus>", "<pause>", "<scale>", "<kpcomma>", "<hangeul>", "<hanja>", "<yen>", "<leftmeta>", "<rightmeta>", "<compose>"};
static char *special_chars[2][21] = {{"`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "[", "]", "\\", ";", "'", ",", ".", "/"},{"~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "{", "}", "|", ":", "\"", "<", ">", "?"}};
