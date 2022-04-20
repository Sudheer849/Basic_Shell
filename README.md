


### **Input/Output Redirection** ###

Initally I have duplicated the standard input file discriptor(STDIN) and standard output discriptor STDOUT using dup command and stored the return values in two global variables(one for STDIN and another for STDOUT),which are used to give the control back to terminal using dup2 after the required work is done. 

I had made STDIN point to the given file for the input redirection and STDOUT point to the given file in output redirection using dup2 and exectute the command . I opened the output file using the flag O_TRUNC for ">" and O_APPEND for ">>".

### **Command pipelines** ###

I have declared a matrix for the file discriptors in which no of rows are the total no of commands that are seperated by pipes and coloumb no 2 . Every command has two file discriptors fd[i][0] and fd[i][1].

I applied pipe(fd[i]) for every command which produces two virtual file discriptors fd[i][0] and fd[i][1], I copied the output of the previous command into a virtual file represented by fd[i][0] and the output of the current command is copied to fd[i][1] using certian number of dup2 commands.For the final command the output will be printed to the terminal

### **Command pipelines with input and output redirection** ###

We should be careful in this specification. For the output redirection commands like echo hello > a.txt i had made the output point to virtual file instead of redirecting to a.txt with a status variable and did the same for input redirection as well.

### **User-defined Commands** ###

#### **Jobs** ####

I have traversed the array of all background process id's and copied the required information in a array of struct. I sorted the array of structs and print in on the terminal and did the similar for jobs -r and jobs -s as well.

#### **sig** ####

I passed the corresponding signalnumber to the process with the job number given as input using KILL system call.

#### **fg** ####

We have to bring the correspoding background process to the foreground , for this i have used tcsetgpid system call , which creates a foreground process group and pushes the background job to that newly created foreground process group. But as the background process tries to read or write from the terminal , Operating system will prevent this by incuring signals SIGTTOU and SIGTTIN , which i ignored though the signal handler SIGIGN and as the terminal is asscoiated with foreground process group , we have to use tcsetgpid again for the shell program , which will make it continue even if the foreground process gets terminated.

#### **bg** ####

In this specification I passed the signal SIGCONT to the corresponding background process which ensures to make the process continue even if it is stopped.

### **Signal handling** ###

We can identify that the user has pressed ctrl C by SIGINT signal and similarly SIGTSTP for ctrl Z with which we can give control to the signal handler function. For ctrl C I again passed SIGINT to the corresponding process id and SIGTSTP for the ctrl Z , which will ensure that they work as per the specification.Ctrl D sets a EOF chracter which will make getline function return -1 from which we can exit if the getline returns -1.



| File                           | Functions    
| :---                           |    :----:   
| shell_extend.h                 | Include all the headers and protocalls    
| main.c                         | To take the input from terminal      
| break_input_command.c          | To break the command using the delimeter ; and store the commands in a matrix
| display.c                      | To print the prompt
| execute.c                      | Inculde the if conditions to check the main command( for ex cd)
| echo.c                         | Execute echo command
| cd.c                           | Execute cd command
| ls_basic.c                     | Execute ls command with no flags and directories given
| ls.c                           | Execute ls command with flags and directories
| pwd.c                          | Execute pwd command
| pinfo.c                        | Execute pinfo command
| fg.c                           | Execute fg process
| bg.c                           | Execute bg process
| terminated_bg.c                | Signal handler to check for the terminated background process
| input_output_redirect.c        | Execute input output redirection
| pipes.c                        | Execute pipe commands
| jobs.c                         | Execute jobs command
| sig.c                          | Execute sig command
| fg_jobs.c                      | Execute fg command
| bg_jobs.c                      | Execute bg command
| signal_handling.c              | Execute ctrlC and ctrlZ
| Makefile                       | all the files in the current directory

Note :  run make all to execute all the files at once


