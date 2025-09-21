#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<unistd.h>
#include<wait.h>
#include<fcntl.h>
#define MAX_ARGS 5
#define MAX_command_3400 50
void parse_args_3400(char *command_3400, char **args)
{
char *arg = strtok(command_3400, "\t\n");
int i = 0;
while (arg != NULL && i<MAX_ARGS)
{
args[i++] = arg;
arg = strtok(NULL, "\t\n");
}
args[i] = NULL;
}
void run_command_3400(char **args, int input_fd, int output_fd)
{
if (output_fd != STDOUT_FILENO)
{
dup2(output_fd, STDOUT_FILENO);
close(output_fd);
}
if (input_fd != STDIN_FILENO)
{
dup2(input_fd, STDIN_FILENO);

close(input_fd);
}
execvp(args[0], args);
perror("Error running command_3400");
exit(1);
}
int main()
{
char command_3400[MAX_command_3400];
char *args[MAX_ARGS];
int pipes[2];
while (1)
{
printf(">");
if (!fgets(command_3400, sizeof(command_3400),stdin))
{
perror("Error reading command_3400");
return 1;
}
command_3400[strcspn(command_3400,"\n")] = 0;
if (strlen(command_3400) == 0)
continue;
if (strcmp(command_3400,"exit") == 0)
break;
char *ptr = strtok(command_3400,"|");
int num_command_3400s = 0;
char *command_3400s[MAX_ARGS];
while (ptr != NULL && num_command_3400s<MAX_ARGS)
{
command_3400s[num_command_3400s++] = ptr;
ptr = strtok(NULL, "|");
}
int input_fd = STDIN_FILENO;
for (int i = 0; i < num_command_3400s - 1; ++i)
{

pipe(pipes);
parse_args_3400(command_3400s[i], args);
run_command_3400(args, input_fd, pipes[1]);
close(pipes[1]);
input_fd = pipes[0];
close(pipes[0]);
}
parse_args_3400(command_3400s[num_command_3400s - 1], args);
run_command_3400(args, input_fd,STDOUT_FILENO);
}
return 0;
}