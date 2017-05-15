# Keylogger

A simple Keylogger for linux based systems. This will records all the keystrokes the user types and save it in a log file.

## Installation

Install it by these commands

` $ git clone https://github.com/shishirjindal/keylogger `

` $ cd keylogger `

` $ make install `

The make command will require sudo access

> Note : Before the make command you need to find your keyboard device file and change the value of DEVICEFILE in define.h

## Uninstall

To uninstall it type ` make uninstall `

To remomve the log file type ` make remove `

## How to Use

You can run it by typing `keylogger`

The log file will be located at `/var/log/keystroke.log`

## License

© [Shishir Jindal](https://github.com/shishirjindal)