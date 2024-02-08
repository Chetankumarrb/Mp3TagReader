#include<stdio.h>
#include<string.h>
#include "types.h"

#define maxsize 6

typedef struct music
{
   char *fname;
   FILE *fptr;

   char title[100];
   int t_size;
   char artist[100];
   int ar_size;
   char album[100];
   int al_size;
   char year[50];
   int yr_size;
   char contentType[50];
   int ct_size;
   char comment[4];
   int co_size;
   
   int pos[maxsize];
}Music;



Status MusicView(char *argv[],Music *music);
Status ViewTF(Music *music);
Status Fetchmusic(FILE *fptr,int *l,char *ptr);
Status printdetails(Music *music);
void WARNING();

Status copyContent(FILE *fname, int pos, FILE *fptr_dest);

Status copynewcon(FILE *fptr_src,char *name,FILE *fptr_dest);