## Parsing Functions

malloc – Allocates memory dynamically on the heap for storing strings, arrays, or structures. Returns a pointer to the allocated block or NULL if allocation fails.
free – Releases memory previously allocated with malloc to avoid memory leaks.
exit – Terminates the process immediately with a given exit code.
write – Outputs data to a file descriptor (stdout, stderr, files, pipes). Often used for error messages.
read – Reads data from a file descriptor into a buffer. Useful for input files or heredocs.
perror – Prints a descriptive error message to stderr based on the global errno.
strerror – Returns a string describing an error code (errno).
isatty – Checks if a file descriptor refers to a terminal.
ttyname – Returns the name of the terminal device associated with a file descriptor.
getcwd – Retrieves the current working directory path.
chdir – Changes the current working directory.


## Execution Functions

fork – Creates a new process (child) that is a duplicate of the parent. Core for executing multiple commands in parallel.
execve – Replaces the current process with a new program, passing arguments and environment. Used to actually run commands.
wait / waitpid – Waits for child processes to finish and retrieves their exit status.
kill – Sends a signal (like SIGKILL or SIGINT) to a process.
pipe – Creates a unidirectional data channel (read/write ends) for inter-process communication.
dup / dup2 – Duplicates file descriptors; dup2 can redirect stdin/stdout/stderr to files or pipes.
close – Closes a file descriptor to free system resources.
open – Opens or creates a file, returning a file descriptor for reading/writing.
access – Checks file accessibility (existence, permissions).
unlink – Deletes a file from the filesystem.
stat / lstat / fstat – Retrieves information about files (size, type, permissions).
getenv – Retrieves the value of an environment variable.
signal – Sets a handler for a signal (like handling CTRL+C).
wait3 / wait4 – Extended versions of wait providing resource usage statistics.
tcgetattr / tcsetattr – Gets or sets terminal attributes (like raw mode or echo).
ioctl – Performs low-level control of devices (often used for terminal settings).



#### Parsing-related

readline / rl_clear_history / rl_on_new_line / rl_replace_line / rl_redisplay: Provide line-editing and input reading with history; helpers manage how the current line is displayed/updated. They let you fetch a full editable command line from the user.

add_history: Appends the last accepted line to the interactive history so it’s recallable with ↑/↓. Useful for a shell-like UX.

getenv: Retrieves the value of an environment variable (e.g., $HOME) for expansion during parsing. Returns NULL if the variable isn’t set.

getcwd: Returns the absolute path of the current working directory as a string. Often used when expanding PWD or printing prompts.

opendir / readdir / closedir: Open a directory stream, iterate its entries, and close it. Handy for wildcard/globbing expansion like *.c.

stat / lstat / fstat: Fetch metadata about files (type, permissions, size); lstat does not follow symlinks. Useful to validate redirection targets or distinguish files vs directories.

access: Checks if a file exists and whether the process has read/write/execute permissions. Commonly used to resolve commands on PATH before exec.

isatty / ttyname / ttyslot: Detect if input/output is a terminal and retrieve terminal identifiers/slot. Helps decide whether to show prompts or adjust interactive behavior.

strerror / perror: Convert errno to a human-readable string or print a prefixed error line to stderr. Standard way to report parsing/validation errors.

tgetent / tgetflag / tgetnum / tgetstr / tgoto / tputs (if termcap is allowed): Query terminal capabilities and emit control sequences. Mostly relevant if you implement your own line editor instead of relying solely on readline.



#### Execution-related

fork: Creates a child process by duplicating the current process. The child then runs a command or sets up pipes/redirections.

execve: Replaces the current process image with a new program, passing argv/envp. Used by the child after fork to run external commands.

wait / waitpid / wait3 / wait4: Reap terminated child processes and obtain their exit status (and optionally resource usage). waitpid can target a specific PID and support non-blocking options.

pipe: Creates a unidirectional data channel (read end, write end) between processes. Core primitive for implementing pipelines like ls | grep foo.

dup / dup2: Duplicate file descriptors and redirect them (e.g., make stdout point to a pipe or a file). dup2 lets you choose the exact target FD (e.g., 1 for stdout, 0 for stdin).

open / close / read / write: Open files, close descriptors, and perform low-level I/O. Essential for implementing <, >, >> redirections and here-docs.

unlink: Removes a directory entry (deletes a file when no links remain). Often used to clean up temporary here-doc files.

chdir: Changes the current working directory (used by the built-in cd). Updates the process’s notion of where relative paths resolve from.

exit: Terminates the current process with a given status code. In a shell, the built-in exit ends the shell (or a child when used in subshells).

kill: Sends a signal to a process or process group (e.g., to forward SIGINT). Useful for job control or interrupting children.

signal / sigaction: Install signal handlers or set default/ignore behavior. sigaction is the robust, portable way to manage signals in the shell.

ioctl / tcsetattr / tcgetattr: Control terminal and device parameters; tc* functions get/set terminal modes. Helpful to tweak canonical mode/echo for interactive behavior.

getpid: Returns the calling process’s PID. Useful for job control, prompts, or signal targeting.