/* Gintare Jasiukeviciute IFD-3/2 e8330  loginas */
/* Failas: e8330_frw01.c */

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


#define BUFSIZE 4096

FILE *gk_test_open_read(const char *name);
FILE *gk_test_open_write(const char *name);
int gk_test_copywrite(int bytesToCopy, FILE *d, FILE *d2);
int gk_test_close(FILE *d);

FILE *gk_test_open_read(const char *name){
	
   FILE *file = fopen( name, "rb" );
   
   if( file == NULL ){
      perror( name );
      exit(1);
   }
   return file;
}
FILE *gk_test_open_write(const char *name){
	
   FILE *file = fopen( name, "wb" );
   if( file == NULL ){
      perror( name );
      exit(1);
   }
   return file;
}
int gk_test_close(FILE *d)
{
	int closing;
	closing=fclose(d);
	
	if(closing!=0) perror("close failed");
	else puts("closed");
	
	return closing;
}

int gk_test_copywrite(int bytesToCopy, FILE *d, FILE *d2){
	char buffer[BUFSIZE];
    int bytes_read, bytesCopied;
	while(bytesToCopy>0)
	{
		int toRead = BUFSIZE; 
		if(BUFSIZE>bytesToCopy)
		{
			toRead=bytesToCopy;
		}
		
		bytes_read=fread(buffer, 1, toRead, d);
		
		if(bytes_read == -1)
		{
			perror("read() klaida");
			exit(1);
		}
		else if(bytes_read==0)
		{
			break;
		}
		
		bytesCopied=fwrite(buffer, 1, bytes_read, d2);
		
		if(bytesCopied == -1)
		{
			perror("write() klaida");
			exit(1);
		}
		bytesToCopy = bytesToCopy-bytes_read;
	}
	
	return 0;
	
}


int main( int argc, char * argv[] ){
	FILE *d, *d2;
   printf( "(C) 2025 Gintare Jasiukeviciute, %s\n", __FILE__ );
   if( argc != 4 ){
      printf( "Naudojimas:\n %s failas\n", argv[0] );
      exit( 255 );
   }
   
   d=gk_test_open_read(argv[1]);
   d2=gk_test_open_write(argv[2]);
   gk_test_copywrite(atoi(argv[3]), d, d2);
   gk_test_close(d);
   gk_test_close(d2);
   
   return 0;
}