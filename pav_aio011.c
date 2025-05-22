/* Gintare Jasiukeviciute IFD-3/2 e8330  loginas */
/* Failas: e8330_aio02.c */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int vp_open_read(const char *name);
int vp_read_data(int fd, char *buffer, int position, int count);
int vp_write_data(const char *name, char *buffer, int count);
int vp_set_permissions(const char *name);
int vp_close(int fd);

int vp_open_read(const char *name) {
   int dskr;
   dskr = open(name, O_RDONLY);
   if(dskr == -1) {
      perror(name);
      abort();
   }
   printf("Input file opened, dskr = %d\n", dskr);
   return dskr;
}
int vp_close(int fd) {
   int rv;
   rv = close(fd);
   if(rv != 0) {
      perror("close() failed");
      abort();
   } else {
      puts("File closed");
   }
   return rv;
}

int vp_read_data(int fd, char *buffer, int position, int count) {
   int bytes_read;
   
   if(lseek(fd, position, SEEK_SET) == -1) {
      perror("lseek() error");
      abort();
   }
   
   bytes_read = read(fd, buffer, count);
   if(bytes_read == -1) {
      perror("read() error");
      abort();
   }
   
   printf("Read %d bytes from position %d\n", bytes_read, position);
   return bytes_read;
}

int vp_write_data(const char *name, char *buffer, int count) {
   int fd, bytes_written;
   
   fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
   if(fd == -1) {
      perror("output file open error");
      abort();
   }
   
   bytes_written = write(fd, buffer, count);
   if(bytes_written == -1) {
      perror("write() error");
      abort();
   }
   
   printf("Wrote %d bytes to file %s\n", bytes_written, name);
   close(fd);
   return bytes_written;
}

int vp_set_permissions(const char *name) {
   int result;
   
   result = chmod(name, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
   if(result == -1) {
      perror("chmod() error");
      abort();
   }
   
   printf("File permissions set successfully\n");
   return result;
}

int main(int argc, char *argv[]) {
   int fd, position, count, bytes_read;
   char *buffer;
   struct stat st;
   
   printf("(C) 2025 Gintare Jasiukeviciute, %s\n", __FILE__);
   
   // Check arguments
   if(argc != 4) {
      printf("Usage: %s file_name N M\n", argv[0]);
      exit(205);
   }
   
   // Parse N and M
   position = atoi(argv[2]);
   count = atoi(argv[3]);
   
   if(position < 0 || count <= 0) {
      printf("Error: N must be non-negative and M must be positive\n");
      exit(205);
   }
   
   // Open input file
   fd = vp_open_read(argv[1]);
   
   // Check if there's enough data
   if(fstat(fd, &st) == -1) {
      perror("fstat() error");
      abort();
   }
   
   if(position >= st.st_size || (position + count) > st.st_size) {
      printf("Not enough data in file\n");
      close(fd);
      return 0;
   }
   
// Allocate buffer
   char buffer[count];  // Fixed-size array allocation on stack
   
   // Read data
   bytes_read = vp_read_data(fd, buffer, position, count);
   
   // Check if we read enough data
   if(bytes_read < count) {
      printf("Not enough data read\n");
      free(buffer);
      close(fd);
      return 0;
   }
   
   // Write data to output file
   vp_write_data("data.bin", buffer, bytes_read);
   
   // Set permissions
   vp_set_permissions("data.bin");
   
	vp_close(fd);
	
   return 0;
}