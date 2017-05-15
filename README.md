# Keylogger

A simple C based Keylogger for linux based systems. This will record all the keystrokes the user types and saves it in a log file.

## Installation

Install it by typing these commands

`$ git clone https://github.com/shishirjindal/keylogger`

`$ cd keylogger`

`$ make install`

The make command will require `sudo` access

> Note : Before the make command you need to find your keyboard device file and change the value of DEVICEFILE in define.h

## Uninstall

To uninstall it type `make uninstall`

To remove the log file type `make remove`

## How to Use

You can run it by typing `keylogger`

The log file will be located at `/var/log/keystroke.log`

## License

© [Shishir Jindal](https://github.com/shishirjindal)
