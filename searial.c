#include "serial.h"

int Open(const char * name)
{
    int ret;
    ret=open(name,O_RDWR);
    if(ret<0)
    {
        perror("Serial Port Open Failed!");
    }
    return ret;
}

int Close(int fd)
{
    int ret=close(fd);
    if(ret<0)
    {
        perror("Close Serial Fialed!");
    }
    return ret;
}

int setSpeed(int fd, int s)
{
    int i=0;
    int ret=0;
    int speed1[]={115200,57600,38400,19200,9600};
    int speed2[]={B115200,B57600,B38400,B19200,B9600};
    for(i=0;i<sizeof(speed1)/sizeof(int);i++)
    {
        if(speed1[i]==s)
        {
            break;
        }
    }
    struct termios attr;
    ret=tcgetattr(fd,&attr);
    if(ret<0)
    {
        perror("get attr failed!");
        return ret;
    }
    ret=cfsetspeed(&attr,speed2[i]);
    if(ret<0)
    {
        perror("set speed failed!");
        return ret;
    }
    tcflush(fd,TCIOFLUSH);
    ret=tcsetattr(fd,TCSANOW,&attr);
    if(ret<0)
    {
        perror("set attr failed!");
        return ret;
    }
    return 0;
}

int setAttr(int fd, int databits, int stopbits, int parity)
{
    struct termios attr;
    int ret=tcgetattr(fd,&attr);
    if(ret<0)
    {
        perror("get attr failed!");
        return ret;
    }

    switch(databits)
    {
    case 5:
        attr.c_cflag &= ~CSIZE;
        attr.c_cflag |= CS5;
        break;
    case 6:
        attr.c_cflag &= ~CSIZE;
        attr.c_cflag |= CS6;
        break;
    case 7:
        attr.c_cflag &= ~CSIZE;
        attr.c_cflag |= CS7;
        break;
    case 8:
        attr.c_cflag &= ~CSIZE;
        attr.c_cflag |= CS8;
        break;
    default:
        printf("Unsupported argument!\n");
    }

    switch(stopbits)
    {
    case 1:
        attr.c_cflag &= ~CSTOPB;
        break;
    case 2:
        attr.c_cflag |= CSTOPB;
        break;
    default:
        printf("Unsupported argument!\n");
    }

    switch(parity)
    {
    case 'n':
    case 'N':
        attr.c_iflag &= ~INPCK;
        attr.c_cflag &= ~PARENB;
        break;
    case 'E':
    case 'e':
        attr.c_iflag |= INPCK;
        attr.c_cflag |= PARENB;
        attr.c_cflag &= ~PARODD;
        break;
    case 'O':
    case 'o':
        attr.c_iflag |= INPCK;
        attr.c_cflag |= PARENB;
        attr.c_cflag |= PARODD;
        break;
    default:
        printf("Unsupported argument!\n");
    }
    attr.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    attr.c_oflag &=~(INLCR|IGNCR|ICRNL);
    attr.c_oflag &=~(ONLCR|OCRNL);
    attr.c_iflag &= ~(IXON | IXOFF | IXANY);


    tcflush(fd,TCIOFLUSH);
    ret=tcsetattr(fd,TCSANOW,&attr);
    if(ret<0)
    {
        perror("set attr failed!");
        return ret;
    }
    return 0;
}

int setTimeout(int fd, int timeout)
{
    struct termios attr;
    int ret=tcgetattr(fd,&attr);
    if(ret<0)
    {
        perror("get attr failed!");
        return ret;
    }
    attr.c_cc[VTIME]=timeout*10;
    attr.c_cc[VMIN]=0;
    tcflush(fd,TCIOFLUSH);
    ret=tcsetattr(fd,TCSANOW,&attr);
    if(ret<0)
    {
        perror("set attr failed!");
        return ret;
    }
    return 0;
}

int Read(int fd, char *buf, int len)
{
    int ret;
    while((ret=read(fd,buf,len))==-1)
    {
        if(errno!=EINTR)
        {
            perror("read serial error!");
            return ret;
        }
    }
    return 0;
}

int Write(int fd, const char *buf, int len)
{
    int ret;
    while((ret=write(fd,buf,len))==-1)
    {
        if(errno!=EINTR)
        {
            perror("write serial error!");
            return ret;
        }
    }
    return 0;
}

int Readn(int fd, char *buf, int len)
{
    return 0;
}

int Writen(int fd, const char *buf, int len)
{
    return 0;
}

int ReadLine(int fd, char *buf, int maxlen)
{
    return 0;
}
