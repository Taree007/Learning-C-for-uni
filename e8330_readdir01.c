/* Gintare Jasiukeviciute IFD-3/2 e8330  loginas */
/* Failas: readdir01.c */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int gj_test_openDir();
int gj_test_closeDir();
int gj_test_readDir();

int gj_test_openDir(){
   DIR *dir;
   dir = opendir(".");
   if (dir==NULL)
   {
	   perror("nepavyko atidaryti katalogo");
	   exit(1);
   }
   gj_test_readDir(dir);
   return 0;
}
int gj_test_readDir(DIR *dir){
	struct dirent *e;
	while((e=readdir(dir))!=NULL)
	{
		printf("inode nr: %lu, failo vardas: %s\n", (unsigned long)e->d_ino, e->d_name);
	}
	
	gj_test_closeDir(dir);
	//return dir;
	return 0;
}
int gj_test_closeDir(DIR *dir){
	closedir(dir);
    return 0;
}

int main( int argc, char * argv[] ){
   printf( "(C) 2025 Gintare Jasiukeviciute, %s\n", __FILE__ );
   gj_test_openDir();
   
   return 0;
}