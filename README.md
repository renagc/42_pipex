# Pipex

This project allows you to explore and implement a familiar UNIX mechanism within your program.

## Requirements
_Arguments: file1, cmd1, cmd2, file2_
External functions allowed:
open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
This project involves handling pipes. Your program will be executed as follows:

## Example
### Program will be executed as follows:
`./pipex file1 cmd1 cmd2 file2`
<br></br>
It must take 4 arguments:
<br></br>
**file1** and **file2** are file names.
<br></br>
**cmd1** and **cmd2** are shell commands with their parameters.
Your program must behave exactly the same as the following shell command

##### Example 1:
`$> < file1 cmd1 | cmd2 > file2`

##### Example 2:
`$> ./pipex infile "ls -l" "wc -l" outfile`
_Should behave like:_ `< infile ls -l | wc -l > outfile`

##### Example 3:
`$> ./pipex infile "grep a1" "wc -w" outfile`
_Should behave like:_ `< infile grep a1 | wc -w > outfile`
