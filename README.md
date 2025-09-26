# catdir

**catdir** is a simple console utility to view the contents of all files in a specified directory. The program recursively traverses all folders and outputs the content of each file to standard output.

## Features

- Recursively browse files in the chosen directory.
- Supports help (`-h`/`--help`) and version (`-v`/`--version`) output.
- Error messages for unable to open individual files or filesystem issues.

## Installation

A C++17 compiler or above is required.

Sample compilation using g++:

```bash
g++ -std=c++17 -o catdir catdir.cpp
```

## Usage

```bash
./catdir <path_to_directory>
```

#### Examples:

- View all files in a directory:
  ```
  ./catdir ./projects
  ```

- Get help:
  ```
  ./catdir --help
  ```

- Check version:
  ```
  ./catdir --version
  ```

## Program Output

For each found file, its name will be followed by the full text of that file. If a file couldn't be opened, an error message will appear, but the program will continue execution.

## Errors

If the specified directory doesn't exist or other filesystem issues arise, the program will output an error message and terminate with a non-zero return code.

## License

This is free software. Use at your own risk.
