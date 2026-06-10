TD_Logging
==========

TD_Logging is a powerful single header logging library that helps you with logging.

Installation
------------

## For using it in your Project!

Copy the `TD_Logging.h` file in your include Folder.

### All Functions and Settings

The Global Namespace of the header is `TD_Logging`.

The First thing you want to do is calling `TD_Logging::init();`

To manage the Settings you need to use `TD_Logging::Settings;`

There are many different settings which you can find in `TD_LoggingFlags` and `TD_LoggingLevels`

You dont need to touch `TD_LoggingColors` because this is handled internally


## For Testing!

### What you need

- **CMake** – Version 3.15 or higher
- **Compiler** – e.g., Clang, GCC, or MSVC

## Setting things up

Clone with:
```
git@github.com:Tr1stanDevs/TD_Logging.git
```

Then go in the Project with:
```
cd TD_Logging
```

### How to Build

The build Process is fully automated.

On Windows you start with:
```powershell
.\test-windows.ps1
```

On Linux you start with:
```shell
.\test-linux.sh
```