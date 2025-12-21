##pipex
pipex is a small Unix project that recreates a shell pipeline using low-level system calls.  

```bash
It reproduces the behavior of:
< infile cmd1 | cmd2 > outfile
```

The program uses pipe(), fork(), dup2(), and execve() to connect two commands through a pipe, handle input/output redirections, resolve executables via the PATH environment variable, and return the exit status of the last command.
