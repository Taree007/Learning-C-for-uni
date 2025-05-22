/* Gintare Jasiukeviciute IFD-3/2 e8330  loginas */
/* Failas: e8330_mmapo2.c */

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <string.h>

int gk_test_open_read(const char *name);
int gk_test_open_write(const char *name);
int gk_test_close(int fd);
void* gk_test_mmapw(int d, int size);
void* gk_test_mmapw2(int d, int size);
int gk_test_usemaped( void *a, void *a2, int size );
int gk_test_munamp( void *a, int size );


int gk_test_open_read(const char *name){
   int dskr;
   dskr = open( name, O_RDONLY );
   if( dskr == -1 ){
      perror( name );
      exit(1);
   }
   printf( "dskr = %d\n", dskr );
   return dskr;
}
int gk_test_open_write(const char *name){
   int dskr;
   dskr = open( name, O_RDWR );
   if( dskr == -1 ){
      perror( name );
      exit(1);
   }
   printf( "dskr = %d\n", dskr );
   return dskr;
}

int gk_test_close(int fd){
   int rv;
   rv = close( fd );
   if( rv != 0 ) perror ( "close() failed" );
   else puts( "closed" );
   return rv;
}
void* gk_test_mmapw(int d, int size){
	void *a = NULL;
	
	//desired address, len, read, shared, file to map,    OFFSET!
   a = mmap( NULL, size, PROT_READ, MAP_SHARED, d, 0 );
   if( a == MAP_FAILED ){
      perror( "mmap failed" );
      abort();
   }
   return a;
}
void* gk_test_mmapw2(int d, int size){
	void *a2 = NULL;
	lseek( d, size - 1, SEEK_SET ); 
    write( d, &d , 1 );
	
	//PROT_READ | PROT_WRITE (read-write)
   a2 = mmap( NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, d, 0 );
   if( a2 == MAP_FAILED ){
      perror( "mmap failed" );
      abort();
   }
   return a2;
}

//----------------------------------------------------------------------------------------------------------
//is pirmo failo suraso i antra per mapping
int gk_test_usemaped( void *a, void *a2, int size ){
	memcpy(a2, a, size);
   return 1;
}
//----------------------------------------------------------------------------------------------------------

int gk_test_munamp( void *a, int size ){
   int rv;
   rv = munmap( a, size );
   if( rv != 0 ){
      puts( "munmap failed" );
      abort();
   }
   return 1;
}

int main( int argc, char * argv[] ){
	int d, d2;  //failai
	
   void *a = NULL;    //pointers i maps
   void *a2 = NULL;
   printf( "(C) 2025 Gintare Jasiukeviciute, %s\n", __FILE__ );
   if( argc != 3 ){
      printf( "Naudojimas:\n %s failas1 failas2\n", argv[0] );
      exit( 255 );
   }
   //--------------
   d=gk_test_open_read(argv[1]);
   
   d2=gk_test_open_write(argv[2]);
   //--------------
   struct stat st;
    if (stat(argv[1], &st) != 0)
		perror("klaida stat()");     //getting file size 
	int size =st.st_size;
	//----------
   a = gk_test_mmapw( d, size );  //mapping into read
   a2 = gk_test_mmapw2(d2, size);  //mapping into read-write
   
   gk_test_usemaped(a, a2, size);
   //unpam---------
   gk_test_munamp(a, size);
   gk_test_munamp(a2, size);
   //-----------close
   gk_test_close(d);
   gk_test_close(d2);
   
   return 0;
}