### Pooja Desur
### 2019101112

# OS Assignment 2

### Compilation
This assignment is compiled through a makefile. By typing "make" into the terminal, all files that are in the directory are compiled. 

To run the code, run "./code".
Use command "quit" to exit the shell.

There are 8 '.c' files, 1 '.h' file and one makefile. The .h file called functions.h in the header file which includes all the header files used throught all the .c files and all the functions in each file which can thus be accessed by any file.

This shell can handle I/O redirection, piping, and I/O redirection within command pipelines.

The functioning of the 8 '.c' files are described below.

### functions.h
- contains all the header files and function declarations of all functions used throughout the various files

### main.c
- The main() function is ran first on executing the shell. The directory from which the shell has been run is saved here and passed as an argument to remaining functions.
- A shellStart() function is called to distinguish the starting point between the bash shell and my shell.
- signal() is called before the while input loop.
- To mimick shell behaviour, a while loop is continuously run to take input from stdin. In this while loop, display(), which is defined in display.c displays the username and hostname to stdout, and command(), which is defined in command.c, takes input from stdin.
- The signal handler function signal_handler() which checks for singals sent to any child process is defined here.
- insert(), search(), and delet() are functions used to create and use a linked list data structure to save the names of the child processes called.

### shellstart.c
- shellStart() displays a pattern as soon as the shell is ran to distinguish between bash shell and the executed shell.
-
### display.c
- display() is called from main function. It displays the username and hostname of the machine.

### command.c
- command() takes input from stdin using getline().
- More than one command can be input into one line by splitting with ';'. Tabs and spaces do not affect input.
- by tokenising the input with strtok_r(), it calls the various required functions.
- built in commands are
  -  cd with flags . , '..' , ~
  -  pwd
  -  echo
  -  ls with flags . , .. , ~ , -l, -a , -al , -la
  -  pinfo
  -  nightswatch with commands interrupt and newborn 
- other commands are executed using execvp() by forming child processes. If a command is inputted with a "&", and is not built-in, it will run as a background proccess. It can be killed by executing kill -9 'pid'. (pid can be observed from ps command.)
- after a background process has finished either normally or abnormally, message will be displayed to stderr along with the process's pid.
- Dir() is a function to check if a given input is a valid existing directory or file.

### builtIn.c
- ExecuteCd() function executes the cd functionality. The shell will move to the directory mentioned. If it moves to a parent directory to where the shell was created (root directory), the absolute path of the directory will be displayed. If it moves to directories within the root, they will be displayed as '~/newdir'.
  - cd . represents changing to the same current directory
  - cd .. changes to parent directory
  - cd ~ changes to root directory where shell was executed first
  - cd '/dir' changes to dir with a valid path
- ExecutePwd() function executes the pwd functionality and prints the present working directory.
- ExecuteEcho() function will display the argument input to echo. If there were spaces and tabs, it will display the line without them.

### ls.c
- ExecuteLs() executes the ls command along with its various flags. Flags such as -l, -a, -la, -al, must be inputted as described to get desired output.
  - -a displays hidden files and directories as well
  - -l displays the long format
  - -al and -la display the long format of all files including hidden.
  - ls . lists files and directories in current directory/file
  - ls .. lists files/directories in parent of root directory
  - ls ~ lists files/directories in root directory
- longFormat() displays more details of the files and directories when the -l, -al, or -la flag is used, just as the bash shell.
- isDir() and isFile() are used to check if a given parameter is a Directory or File respectively.
- if one or more arguments are given to ls to be listed, the name of the argument to be listed is displayed followed by a colon, and the list follows from a new line.

### pinfo.c
- pinfo() will display the following information of the shell if a pid is not mentioned, of the proccess info of a given pid.
  - pid
  - process status
  - virtual memory in bytes
  - executable path

### nightswatch.c
- input must be given as 'nightswatch -n x command' where x is the number of seconds the in which to execute the command periodically and command can be either interrupt or newborn, which are executed by the interrupt() and newborn() functions respectively.
- nightswatch() will call the functions interrupt() and newborn() when required, or return if input is entered wrong. The output will be printed onto stdout for the given -n x seconds as <option> until q is pressed on the keyboard.
- interrupt() displays the number of times the CPU(s) has/have been interrupted by the keyboard controller every x seconds.
- newborn() displays the proccess id of the most recently created process on the system every x seconds

### redirect.c 
- redirec() implements redirection through multiple files

### pipe.c
- piping() implements piping along with redirection through multiple commands and files.

### EnvVar.c

To set an environment variable provide input as:
setenv var [value]

To remove an environment variable, provide input as:
unsetenv var

- in this file function Setenv() and Unsetenv() set and remove environment variables respectively.

### jobs.c

Through the shell session, a list of jobs in order of when they were created is maintained (most recently created job will have the highest job number). When a job is deleted, other job numbers will not change.

- implemented through Jobs() in jobs.c


### kjob.c

- send a signal to a specific job number with kjobs() in kjob.c
- provide input as
kjob <job number> <signal number>

### fg

- if the provided job number exists, fg() in fg.c will bring the background job to the foreground and change its state to running.

### bg

- if the provided job number exists, bg() in bg.c will change the state of the background job to running.

### overkill.c

- overkill command will kill all the background proccesses.
- contains overkill() 

### bgproccesses.c

- this file consists of the linked list functions used to keep track of the background jobs
- 

### controlz.c

- on typing control z, any currently running foreground process gets pushed into the background with state as stopped. 
- this will not effect the shell if there are no currently running foreground processes
- implemented with a signal handler funciton set for signal SIGTSTP, called z_signal_handler in controlz.c

### controlc.c

- on typing control c, any currently running foreground process will stop.
- implemented with signal handler function set for signal SIGINT,  called c_signal_handler in controlc.c
















