#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    sleep(10);
    if (fork() != 0)
    {
        sleep(10);
        if (fork() != 0)
        {
            sleep(10);
        }
        else
        {
            sleep(10);
            if (fork() != 0)
            {
                sleep(20);
            }
            else
            {
                sleep(10);
                if (fork() != 0)
                {
                    sleep(20);
                }
                else
                {
                    sleep(10);
                    if (fork() != 0)
                    {
                        sleep(20);
                    }
                    else
                    {
                        sleep(10);
                        if (fork() != 0)
                        {
                            sleep(20);
                        }
                        else
                        {
                            sleep(20);
                        }
                    }
                }
            }
            sleep(20);
        }
    } else
    {
        if (fork() != 0)
        {
            sleep(20);
        }
        else
        {
            if (fork() != 0)
            {
                sleep(20);
            }
            else
            {
                sleep(20);
            }
            sleep(20);
        }
    }
    
}
