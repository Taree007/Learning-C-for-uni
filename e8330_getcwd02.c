/* Gintare Jasiukeviciute IFD-3/2 e8330  loginas */
/* Failas: e8330_getcwd02.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int gk_test_getcwd();
int gk_test_open();
int gk_test_goTo();
int gk_test_goBack();

int gk_test_getcwd(){
	int d;
   char *cwd;
   cwd = getcwd( NULL, pathconf( ".", _PC_PATH_MAX) );
   puts( cwd );
   
   d=gk_test_open(cwd); //pirmiau perduodam o poto tik free 
   free( cwd );   
   
   return d;
}
int gk_test_open(const char *name){
   int dskr;
   dskr = open( name, O_RDONLY );
   
   if( dskr == -1 ){
      perror( name );
      exit(1);
   }
   printf( "dskr = %d\n", dskr );
   return dskr;
}

int gk_test_goTo(){
	char *cwd;
	chdir("/tmp");
	cwd = getcwd( NULL, pathconf( ".", _PC_PATH_MAX) );
	//cwd = gk_test_getcwd();
	puts( cwd );
	free( cwd );
	return 1;
}
int gk_test_goBack(int d){
	char *cwd;
	fchdir(d);
	cwd = getcwd( NULL, pathconf( ".", _PC_PATH_MAX) );
	//cwd = gk_test_getcwd();
	puts( cwd );
	free( cwd );
	return 1;
}

int main( int argc, char * argv[] ){
	int d;
   printf( "(C) 2025 Gintare Jasiukeviciute, %s\n", __FILE__ );
   d=gk_test_getcwd();
   //d = gk_test_open();
   gk_test_goTo();
   gk_test_goBack(d);
   
   return 0;
}