#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>

#undef errno
extern int errno;

extern void exit(uint32_t);

void _exit()
{
	exit(ENOTRECOVERABLE);
}

int close(int file)
{
	errno = ENOSYS;
	return -1;
}

// Pointer to array of char * strings that define the current environment variables.
// It is empty for ppu.
char* __env[1] = {0};
char** environ = __env;

int execve(char* name, char** argv, char** env)
{
	errno = ENOMEM;
	return -1;
}

int fork()
{
	errno = ENOSYS;
	return -1;
}

int fstat(int file, struct stat* st)
{
	errno = EBADF;
	return -1;
}

int getpid()
{
	// There's only one process, it has pid=1.
	return 1;
}

int isatty(int file)
{
	errno = EBADF;
	return -1;
}

int kill(int pid, int sig)
{
	errno = ENOSYS;
	return -1;
}

int link(char* old, char* new)
{
	errno = ENOSYS;
	return -1;
}

int lseek(int file, int ptr, int dir)
{
	errno = EBADF;
	return -1;
}

int open(const char* name, int flags, ...)
{
	errno = ENOSYS;
	return -1;
}

int read(int file, char* ptr, int len)
{
	errno = EBADF;
	return -1;
}

caddr_t sbrk(int incr)
{
	extern char heap_base;
	extern char heap_end;
	static char* current_end;
	if (current_end == NULL) {
		current_end = &heap_base;
	}
	char* prev_end = current_end;
	if (current_end + incr > &heap_end) {
		// FIXME: Do nothing. There's no heap overflow protection.
		// Maybe introduce trapping comparison to current stack pointer
		// instead of heap_end to raise exception?
	}
	current_end += incr;
	return (caddr_t) prev_end;
}

int stat(const char* file, struct stat* st)
{
	errno = EBADF;
	return -1;
}

clock_t times(struct tms* buf)
{
	errno = ENOSYS;
	return -1;
}

int unlink(char* name)
{
	errno = ENOSYS;
	return -1;
}

int wait(int* status)
{
	errno = ENOSYS;
	return -1;
}

int write(int file, char* ptr, int len)
{
	errno = EBADF;
	return -1;
}

int gettimeofday(struct timeval* p, void* z)
{
	errno = ENOSYS;
	return -1;
}
