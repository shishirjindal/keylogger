# Keylogger

A simple C based Keylogger for linux based systems. This will record all the keystrokes the user types and saves it in a log file.

## Installation

Install it by typing these commands

`$ git clone https://github.com/shishirjindal/keylogger`

`$ cd keylogger`

`$ sudo make install`

## Uninstall

To uninstall it type `sudo make uninstall`

To remove the log file type `sudo make remove`

## How to Use

After installation you can start the keylogger by typing `sudo keylogger`. If you want to start the keylogger at boot time then type `sudo make enable` and to disable startup feature type `sudo make disable`

The log file will be located at `/var/log/keystroke.log`

## License

© [Shishir Jindal](https://github.com/shishirjindal)
