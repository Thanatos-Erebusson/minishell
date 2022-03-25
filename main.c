#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    while(1)
    {
        readline("myshell: ");
    }
}