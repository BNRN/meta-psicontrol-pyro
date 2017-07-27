/*
*
*
*/

#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <byteswap.h>
#include <getopt.h>
#include <inttypes.h>

char *memdev="/dev/mem";

int write_flg=0;
int dump_flg=0;
int binary_dump_flg=0;
int fill_flg;
void *fill_pat_val;
int fill_pat_len;
char *file_format=NULL;
int nommap_flg=0;

int blockmode=0;
int erase_block=-1;

unsigned long mem_start=0;
unsigned long mem_length=0;
unsigned long mem_offs=0;

int mem_dump(void *buf, unsigned long start, unsigned long len, int blen)
{
  unsigned long addr=start;
  volatile unsigned char *p=buf;
  int i;

  while(len){
    printf("%08lX:",addr);
    i=len>16?16:len;
    addr+=i;
    len-=i;
    while(i>0){
      switch(blen){
    case 4:
      i-=4;
          printf("%08X%c",*(uint32_t*)p,i>0?' ':'\n');
      p+=4;
      break;
    case 2:
      i-=2;
          printf("%04X%c",*(uint16_t*)p,i>0?' ':'\n');
      p+=2;
      break;
    default:
      i--;
          printf("%02X%c",*(p++),i>0?' ':'\n');
      break;
      }
    }
  }
  return 0;
}

int mem_binary(void *buf, unsigned long start, unsigned long len, int blen)
{
  volatile unsigned char *p=buf;

  while(len){
    if(blen > len)
      blen = len;
    switch(blen){
      case 4:
        len-=4;
        fwrite((uint32_t*)p,4,1,stdout);
        p+=4;
        break;
      case 3:
      case 2:
        len-=2;
        fwrite((uint16_t*)p,2,1,stdout);
        p+=2;
        break;
      default:
        len-=1;
        fwrite((uint8_t*)p,1,1,stdout);
        p+=1;
        break;
    }
  }
  return 0;
}

int mem_fill(void *buf, unsigned long start, unsigned long len,
        unsigned char *pat_val, int pat_len, int blen)
{
  volatile unsigned char *p=buf;
  unsigned char *r;
  unsigned char *pat_end=pat_val+pat_len;
  uint16_t u16;
  uint32_t u32;

  if(pat_len<=0) return -1;
  if(!len) return 0;

  switch(blen){
    case 4:
      r=pat_val;
      for(;;){
        u32=*(r++);
    if(r>=pat_end) r=pat_val;
        u32|=(uint32_t)*(r++) << 8;
    if(r>=pat_end) r=pat_val;
        u32|=(uint32_t)*(r++) << 16;
    if(r>=pat_end) r=pat_val;
        u32|=(uint32_t)*(r++) << 24;
    if(r>=pat_end) r=pat_val;
        *(uint32_t*)p=u32;
    p+=4;
        if(len<=4) break;
    len-=4;
      }
      break;
    case 2:
      r=pat_val;
      for(;;){
        u16=*(r++);
    if(r>=pat_end) r=pat_val;
        u16|=(unsigned)*(r++) << 8;
    if(r>=pat_end) r=pat_val;
        *(uint16_t*)p=u16;
    p+=2;
        if(len<=2) break;
    len-=2;
      }
    default:
      r=pat_val;
      while(len--){
        *(p++)=*(r++);
    if(r>=pat_end) r=pat_val;
      }
      break;
  }

  return 0;
}


/*----------------------------------------------------------------*/


int si_long(char **ps,long *val,int base)
{
  char *p;
  *val=strtol(*ps,&p,base);
  if(*ps==p) return -1;
  *ps=p;
  return 1;
}

int si_ulong(char **ps,unsigned long *val,int base)
{
  char *p;
  *val=strtoul(*ps,&p,base);
  if(*ps==p) return -1;
  *ps=p;
  return 1;
}

int add_to_arr(void **pdata,int *plen,int base,char *str, int blen)
{
  char *s=str;
  unsigned long val;
  unsigned char *p;
  int i;

  if(!blen)
    blen=1;
  if(blen>4)
    return -1;

  do{
    while(*s && strchr(", \t:;",*s)) s++;
    if(!*s) break;
    if(si_ulong(&s,&val,base)<0){
      return -1;
    }
    if(*pdata==NULL){
      *plen=0;
      *pdata=p=malloc(blen);
    }else{
      p=realloc(*pdata,*plen+blen);
      if(p==NULL) return -1;
      *pdata=p;
    }

    p+=*plen;
    for(i=blen;i--;){
      *(p++)=val;
      val>>=8;
    }
    (*plen)+=blen;
  } while(1);
  return 1;
}

/*----------------------------------------------------------------*/

static void
usage(void)
{
  printf("usage: x -b <location> -l <length> [-1|-2|-4]\n");
  printf("  -b, --base  <num>        base address of transfer\n");
  printf("  -l, --length <num>       length of transfer\n");
  printf("  -1, --1                  byte read\n");
  printf("  -2, --2                  word read\n");
  printf("  -4, --4                  long read\n");
  printf("  -h, --help               this usage screen\n");
}


int main(int argc, char *argv[])
{
  int fd;
  int res;
  unsigned long pagesize;
  unsigned char *mm;
  unsigned char *mem;
  static struct option long_opts[] = {
    { "base",1,0,'b' },
    { "length",1, 0, 'l' },
    { "format",1, 0, 'f' },
    { "help",  0, 0, 'h' },
    { "1",  0, 0, '1' },
    { "2",  0, 0, '1' },
    { "4",  0, 0, '1' },
    { 0, 0, 0, 0}
  };
  int opt;

  while ((opt = getopt_long(argc, argv, ":b:l:h124",
                &long_opts[0], NULL)) != EOF)
  switch (opt) {
    case '1':
      blockmode = 1;
      break;
    case '2':
      blockmode = 2;
      break;
    case '4':
      blockmode = 4;
      break;
      break;
    case 'b':
      mem_start=strtoul(optarg,NULL,0);
      dump_flg=1;
      break;
    case 'l':
      mem_length=strtoul(optarg,NULL,0);
      break;
    case 'h':
    case ':':
    default:
      usage();
      exit(opt == 'h' ? 0 : 1);
  }

  if ((0 == mem_start) || (0 == mem_length))
  {
      usage();
      return 1;
  }

  fd = open(memdev, (write_flg?O_RDWR:O_RDONLY)|O_SYNC);
  if (fd < 0) {
    fprintf(stderr,"%s: cannot open %s\n",argv[0],memdev);
    return 1;
  }

  {
    unsigned long mem_window_size;

    /*
    pagesize=getpagesize();
    */
    pagesize=sysconf(_SC_PAGESIZE);

    mem_window_size = ((mem_start & (pagesize-1)) + mem_length + pagesize-1) & ~(pagesize-1);

    mm = mmap(NULL, mem_window_size, write_flg?PROT_WRITE|PROT_READ:PROT_READ,
              MAP_SHARED, fd, mem_start & ~(pagesize-1));
    mem = mm + (mem_start & (pagesize-1));

    if (mm == MAP_FAILED) {
      fprintf(stderr,"%s: mmap error\n",argv[0]);
      return 1;
    }

    //printf("mmap 0x%lx -> %p\n",mem_start,mem);

    //write(fileno(stdout), mm, 0x1000);

    mem_dump(mem, mem_start, mem_length?mem_length:1, blockmode);


    munmap(mm, mem_window_size);
  }
  close(fd);

  return 0;
}
