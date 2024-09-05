#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}


int main(int argc, char **argv)
{
	int i=0,k=0,j=0,varr=0,vals=0,l=0;
	char * variables[20]={NULL};
	char * values[20]={NULL};

    while (1) {
	printf("Enter a command > ");
	  char *buf=inputString(stdin,10);
	  char **buf2=(char **) malloc(sizeof(char *));
	  buf2[0]=(char *) realloc(NULL,sizeof(char));
	  char *tmp={NULL};
	  int flag=0,dollar_flag=0,equal_flag=0,repeated_flag=0;
	i=0; j=0; k=0;

	if (strlen(buf) == 0)
		continue;

	if(!(strncmp(buf,"exit",4))&&buf[4]=='\0')
		break;
   	
	i=0;
	while(buf[i]!='\0')
	{
			
		if(i==0&&buf[i]==' ')
		{
			i++;
			continue;
		}
		if(buf[i]==' ' && buf[i-1]==' ')
		{
			i++;
			continue;
		}
		else if(buf[i]==' ')
		{
			
			buf2[k]=(char *) realloc(buf2[k],sizeof(char)*(j+1));
			buf2[k][j]='\0';
			k++;
			buf2=(char **) realloc(buf2,sizeof(char *) *(k+1));
			buf2[k]=(char *) realloc(NULL,sizeof(char)*(j+1));
			j=0;
			i++;
			continue;
		}
		
		buf2[k]=(char *) realloc(buf2[k],sizeof(char)*(j+1));
		buf2[k][j]=buf[i];
		i++;
		j++;
	}
	buf2[k][j]='\0';
	buf2=(char **) realloc(buf2,sizeof(char *) *(k+2));
        buf2[k+1]=NULL;	
	printf("buf2[0]=%s buf2[1]=%s\n",buf2[0],buf2[1]);	
	
	i=0; j=0; int l=0;
	values[varr] = (char*) malloc(10);
	variables[varr] = (char*) malloc(10);

	/*Look for equal sign and add the variable and its value*/
	while(buf2[0][i]!='\0')
	{
		if(buf2[0][i]==' ')
		{
			variables[varr]=NULL;
			values[varr]=NULL;
			break;
		}
		variables[varr][i]=buf2[0][i];
		if(buf2[0][i]=='=')
			{
				equal_flag=1;
				variables[varr][i]='\0';
				i++;
				for(l=0;l<varr;l++)
				{
					if(!strncmp(variables[l],buf2[0],i-1))
					{
						repeated_flag=1;
						break;
					}
				}
				if(buf2[0][i]==' ')
				{
					repeated_flag=0;
					equal_flag=0;
					variables[varr]=NULL;
					values[varr]=NULL;
				}
				while((buf2[0][i]!=' ')&&(buf2[0][i]!='\0'))
				{
					if(repeated_flag==1)
					values[l][j]=buf2[0][i];
					
					else values[varr][j]=buf2[0][i];
				j++;
				i++;	
				}
				
			break;	
			}
		i++;
	}

	if(equal_flag==0)
	{
		variables[varr]=NULL;
	}
	else{ if(repeated_flag==0)
		{varr++;
		variables[varr]=NULL;
	        values[varr]=NULL;}
		else variables[varr]=NULL;
		continue;}

	

	/*Look for dollar sign*/
	i=0; j=0; l=0;
	while(l<=k)
	{
		if(buf2[l][i]=='$'&&buf2[l][i+1]!=' ')
		{
			tmp=&buf2[l][i+1];
			dollar_flag=1;
			break;
		}
		i++;
		if(buf2[l][i]=='\0')
		{
			i=0;
			l++;
		}
	}
	i=0; j=0;

	if(dollar_flag==1)
	{
	while(j<=varr)
	{
		if(!strcmp(tmp,variables[j]))
		{
			flag=1;
			strcpy(buf2[l],values[j]);
			break;
		}
		j++;
				
	}
	}
	pid_t ret_pid = fork();

	if (ret_pid < 0) {
	    printf("Fork failed\n");
	    return -1;
	} else if (ret_pid > 0) {
	    // wait for the child
	    int status = 0;
	    
	    pid_t wait_pid = wait(&status);
	} else if (ret_pid == 0) {

	    char *prog_argv[] = { NULL };
	    char *prog_env[] = { NULL };

	    execvpe(buf2[0], buf2 , prog_env);
	    printf("Exec Failed\n");
	    continue;
	    return -1;
	}
	free(buf);
	for(int count=0;count<=k;count++)
	{
		free(buf2[count]);
	}
	free(buf2);
	
    }

    return 0;
}
