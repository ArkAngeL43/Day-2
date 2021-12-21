#include <stdio.h> 
#include<sys/utsname.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/utsname.h>
#include <sys/utsname.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


int a[10];
void brandString(int eaxValues)
{
     if (eaxValues == 1) {
     __asm__("mov $0x80000002 , %eax\n\t");
     }
     else if (eaxValues == 2) {
         __asm__("mov $0x80000003 , %eax\n\t");
     }
     else if (eaxValues == 3) {
         __asm__("mov $0x80000004 , %eax\n\t");
     }
     __asm__("cpuid\n\t");
     __asm__("mov %%eax, %0\n\t":"=r" (a[0]));
     __asm__("mov %%ebx, %0\n\t":"=r" (a[1]));
     __asm__("mov %%ecx, %0\n\t":"=r" (a[2]));
     __asm__("mov %%edx, %0\n\t":"=r" (a[3]));
     printf("%s", &a[0]);
}
 
void getCpuID()
{
     __asm__("xor %eax , %eax\n\t");
     __asm__("xor %ebx , %ebx\n\t");
     __asm__("xor %ecx , %ecx\n\t");
     __asm__("xor %edx , %edx\n\t");///
     printf("|                        |CPU/CORE                |=> ");
     brandString(1);
     brandString(2);
     brandString(3);
     printf("\n");
 }

int clear()
{
    printf("\x1b[H\x1b[2J\x1b[3J");
}

int grabinter(int argc, char *argv[])
{
    if(argc == 2) {

            int fd;
	struct ifreq ifr;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name , argv[1] , IFNAMSIZ-1);
	ioctl(fd, SIOCGIFADDR, &ifr);
	close(fd);
	printf("%s - %s\n" , argv[1] , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
	return 0;
    }

}

int main_system()
{
     struct utsname buf1;
     errno =0;
     if(uname(&buf1)!=0)
     {
         perror("Error => Uname returned 0");
         exit(EXIT_FAILURE);
     }
    printf("__________________________________________________________________________\n");
    printf("|System Name             |=> %s\n", buf1.sysname);
    printf("|                        ");
    printf("|Node/System Name        |=> %s\n", buf1.nodename);
    printf("|                        ");
    printf("|System Current Version  |=> %s\n", buf1.version);
    printf("|                        ");
    printf("|Release Version         |=> %s\n", buf1.release);
    printf("|                        ");
    printf("|Machine ARCH            |=> %s\n", buf1.machine);
}



int banner()
{
    FILE *fptr;
    char filename[100], c;
    fptr = fopen("banner.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }  
    c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }

    fclose(fptr);
    return 0;
}

int main(char *argv[])
{
    clear();
    banner();
    main_system();
    getCpuID();
}