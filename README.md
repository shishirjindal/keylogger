# Keylogger [![Build Status](https://travis-ci.org/shishirjindal/keylogger.svg?branch=master)](https://travis-ci.org/shishirjindal/keylogger)

A simple C based Keylogger for linux based systems. This will record all the keystrokes the user types and saves it in a log file. You can read the technical details [here](https://gist.github.com/shishirjindal/b59b0caf3595938901bed6200618d2e6)

## Installation

Install it by typing these commands

```bash
$ git clone https://github.com/shishirjindal/keylogger
$ cd keylogger
$ sudo make install
```

## Features
- [x] StartUp Feature
- [x] Saves Timestamp
- [ ] Email log file

## Uninstall

To uninstall
```bash
$ sudo make uninstall
```

To remove the log file
```bash
$ sudo make remove
```

## How to Use

Run the keylogger
```bash
$ sudo make start
```

Stop the keylogger
```bash
$ sudo make stop
```

Run at startup
```bash
$ sudo make enable
```

Disable startup feature
```bash
$ sudo make disable
```


The log file will be located at `/var/log/keystroke.log`

## License

© [Shishir Jindal](https://github.com/shishirjindal)
