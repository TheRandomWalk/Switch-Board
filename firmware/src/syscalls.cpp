#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>

#include "usart.h"


extern "C"
{
    extern int __io_putchar(int ch) __attribute__((weak));
    extern int __io_getchar(void) __attribute__((weak));

    char *__env[1] = { 0 };
    char **environ = __env;


    /* Functions */
    void initialise_monitor_handles()
    {
    }


    int _getpid(void)
    {
        return 1;
    }


    int _kill(int pid, int sig)
    {
        errno = EINVAL;
        return -1;
    }


    void _exit (int status)
    {
        _kill(status, -1);
        while (true);
    }


    __attribute__((weak)) int _read(int file, char *ptr, int len)
    {
        int DataIdx;

        for (DataIdx = 0; DataIdx < len; DataIdx++)
        {
            *ptr++ = __io_getchar();
        }

    return len;
    }


    __attribute__((weak)) int _write(int file, char *ptr, int len)
    {
        if (file == 1)
            for (int i = 0; i < len; i++)
                usart_tx(static_cast<uint8_t>(*ptr++));

        return len;
    }


    int _close(int file)
    {
        return -1;
    }


    int _fstat(int file, struct stat *st)
    {
        st->st_mode = S_IFCHR;
        return 0;
    }


    int _isatty(int file)
    {
        return 1;
    }


    int _lseek(int file, int ptr, int dir)
    {
        return 0;
    }


    int _open(char *path, int flags, ...)
    {
        return -1;
    }


    int _wait(int *status)
    {
        errno = ECHILD;
        return -1;
    }


    int _unlink(char *name)
    {
        errno = ENOENT;
        return -1;
    }


    int _times(struct tms *buf)
    {
        return -1;
    }


    int _stat(char *file, struct stat *st)
    {
        st->st_mode = S_IFCHR;
        return 0;
    }


    int _link(char *old_file, char *new_file)
    {
        errno = EMLINK;
        return -1;
    }


    int _fork(void)
    {
        errno = EAGAIN;
        return -1;
    }


    int _execve(char *name, char **argv, char **env)
    {
        errno = ENOMEM;
        return -1;
    }


    void *_sbrk(int incr) 
    {
        extern char _bss_end;

        static unsigned char *heap = 0;
        unsigned char *prev_heap;
        if (heap == 0) heap = (unsigned char *)&_bss_end;
        prev_heap = heap;
        heap += incr;
        return prev_heap;
    }
}