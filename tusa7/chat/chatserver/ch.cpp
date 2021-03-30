#include <unistd.h>
#include <stdlib.h>
void aaamain()
{
    if (fork())
    {
        system("/usr/sbin/chat_pusk");
    }
}
