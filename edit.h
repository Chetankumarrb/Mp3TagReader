#include<stdio.h>
#include"View.h"

Status Mp3Edit(char *argv[],Music *music);

Status Editmusic(Music *music,char *ch,char *name);
Status copyheader(FILE *fptr, FILE *fptr_dest);
Status copyContent(FILE *fptr_src, int pos, FILE *fptr_dest);
etags checkoption(char *ch);
Status RenameInfo(Music *music,char *op,char *name,FILE *fptr_dest);
Status copyreminingcon(FILE *fptr_src,int s,FILE *fptr_dest);
Status copyallContents(FILE *fptr_src,FILE *fptr_dest);