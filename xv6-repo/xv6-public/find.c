#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

void find(char* path, char* fileToFind) {
  char buf[512], *p;
  int fd;

  if((fd = open(path, 0)) < 0){
    printf(2, "find: cannot open %s\n");
    exit();
  }

  // check length of path is not to long
  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
    printf(1, "find: path too long\n");
    exit();
  }

  struct dirent de;
  struct stat st;
  strcpy(buf, path);
  p = buf+strlen(buf);
  *p++ = '/';

  // reads one directory entry at a time
  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == 0)
      continue;

    // skip .. and . directory entires
    if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0 )
      continue;
   
    memmove(p, de.name, DIRSIZ); // used to copy the file (or directory) name to a fixed size buffer
    p[DIRSIZ] = 0;
    if(stat(buf, &st) < 0){
      printf(1, "find: cannot stat %s\n", buf);
      continue;
    }

    // Check if it's either a file or directory
    if (st.type == T_FILE && strcmp(de.name, fileToFind) == 0 ){
      printf(1, buf);
      printf(1, "\n");
    }
    if (st.type == T_DIR) {
      find(buf, fileToFind); // recursively navigate through directories
    }
  }
  close(fd);
}

int main(int argc, char *argv[]) { 
  if (argc < 3) {
    printf(2, "Need more arguements\n");
    exit();
  }

  struct stat st;
  if (stat(argv[1], &st) < 0 || st.type != T_DIR) {
    printf(2, "Error: no a valid directory\n");
    exit();
  }

  find(argv[1], argv[2]);
  exit();
}
