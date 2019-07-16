    #include <sys/types.h>
    #include <sys/stat.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <unistd.h>
    #include <syslog.h>
    #include <string.h>
    #include <time.h>
    #include <linux/input.h>
    #define MOUSEFILE "/dev/input/mice"
    int main() 
    {             
            /* Our process ID and Session ID */
            pid_t pid, sid;
            /* Fork off the parent process */
            pid = fork();
            if (pid < 0) {
                    exit(0);
            }
            /* If we got a good PID, then
               we can exit the parent process. */
            if (pid > 0) {
                    exit(0);
            }
            /* Change the file mode mask */
            umask(0);               
            /* Open any logs here */        
            /* Create a new SID for the child process */
            sid = setsid();
            if (sid < 0) {
                    /* Log the failure */
                    exit(0);
            }         
            /* Change the current working directory */
            if ((chdir("/")) < 0) {
                    /* Log the failure */
                    exit(0);
            }          
            /* Daemon-specific initialization goes here */
            /* The Big Loop */
  			int fd;
			struct input_event ie;
            if((fd = open(MOUSEFILE, O_RDONLY)) == -1) 
            {
			 	perror("Cannot access mouse device");
		 		exit(EXIT_FAILURE);
 	        }
		 	int i = 0;
			while(read(fd,&ie,sizeof(struct input_event))>0)
			{
				i++;
				time_t rawtime;
			 	struct tm * timeinfo;
				time ( &rawtime );
			 	timeinfo = localtime ( &rawtime );
			 	if(i % 2 == 0)
			 		printf ( "\n%d -> Mouse clicked at: %s", (i/2), asctime (timeinfo) );
		 	}				       
       		return 0;
    }
