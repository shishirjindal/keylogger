# Keylogger [![Build Status](https://travis-ci.org/shishirjindal/keylogger.svg?branch=master)](https://travis-ci.org/shishirjindal/keylogger)

A simple C based Keylogger for linux based systems. This will record all the keystrokes the user types and saves it in a log file. You can read the technical details [here](https://gist.github.com/shishirjindal/b59b0caf3595938901bed6200618d2e6)

## Installation

Install it by typing these commands

`$ git clone https://github.com/shishirjindal/keylogger`

`$ cd keylogger`

`$ sudo make install`

## Uninstall

To uninstall it type `sudo make uninstall`

To remove the log file type `sudo make remove`

## How to Use

After installation you can start the keylogger(for this session only) by typing either

`sudo keylogger`  or by 

`sudo make start`

To stop the service for this session type `sudo make stop`

If you want to start the keylogger at boot time then type `sudo make enable` and to disable startup feature type `sudo make disable`

The log file will be located at `/var/log/keystroke.log`

## License

© [Shishir Jindal](https://github.com/shishirjindal)
