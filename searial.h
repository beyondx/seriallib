#ifndef SERIAL_H_
#define SERIAL_H_

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#define VERSION "1.0.0"

int Open(const char *);
int Close(int);
int setSpeed(int,int);
int setAttr(int,int,int,int);
int setTimeout(int fd,int timeout);
int Read(int fd,char *buf,int len);
int Write(int fd, const char *buf,int len);
int Readn(int fd,char *buf,int len);
int Writen(int fd,const char *buf,int len);
int ReadLine(int fd,char *buf,int maxlen);

#endif
