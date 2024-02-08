#include "edit.h"


Status Mp3Edit(char *argv[], Music *music)
{

    music->fname = argv[4];
    // open source music file
    music->fptr = fopen(music->fname, "rb+");
    if (music->fptr == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", music->fname);
        return m_failure;
    }

    if (Editmusic(music, argv[2], argv[3]) == m_success)
    {
        printf("version and header tag validated & Destination file opened Successfully\n");
    }
    else
    {
        return m_failure;
    }

    return m_success;
}

Status Editmusic(Music *music, char *ch, char *name)
{
    // open destination music file
    FILE *fptr_dest = fopen("output.mp3", "wb+");
    if (fptr_dest == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", "Output.mp3");
        return m_failure;
    }

    // check header and version
    char arr[4];
    int i;
    for (i = 0; i < 3; i++)
    {
        fread(&arr[i], 1, 1, music->fptr);
    }
    arr[i] = '\0';

    if (!strcmp(arr, "ID3"))
    {
        char size;
        fread(&size, 1, 1, music->fptr);
        if (size == 0x03)
        {
            // read the file information
            if (ViewTF(music) == m_success)
            {
                if(RenameInfo(music, ch, name, fptr_dest)==m_success)                       ///
                {
        
                    copyallContents(music->fptr,fptr_dest);
                }
            }

            return m_success;
        }
        else
        {
            printf("Pass Version 2.3 file\n");
            return m_failure;
        }
    }
    else
    {
        printf("please pass the ID3 tag file!!!\n");
        return m_failure;
    }
}

Status RenameInfo(Music *music, char *op, char *name, FILE *fptr_dest)
{
    if (copyheader(music->fptr, fptr_dest) == m_success)
    {
        switch (checkoption(op))
        {
        case t:
            copyContent(music->fptr, music->pos[m_title], fptr_dest);
            copynewcon(music->fptr,name,fptr_dest);
            copyreminingcon(music->fptr,music->t_size,fptr_dest);
            break;
        case a:
            copyContent(music->fptr, music->pos[m_artist], fptr_dest);
            copynewcon(music->fptr,name,fptr_dest);
            copyreminingcon(music->fptr,music->ar_size,fptr_dest);
            break;
        case A:
            copyContent(music->fptr, music->pos[m_album], fptr_dest);
            copynewcon(music->fptr,name,fptr_dest);
            copyreminingcon(music->fptr,music->al_size,fptr_dest);
            break;
        case y:
            copyContent(music->fptr, music->pos[m_year], fptr_dest);
            copynewcon(music->fptr,name,fptr_dest);
            copyreminingcon(music->fptr,music->yr_size,fptr_dest);
            break;
        case m:
            copyContent(music->fptr, music->pos[m_contentType], fptr_dest);
            copynewcon(music->fptr,name,fptr_dest);
            copyreminingcon(music->fptr,music->ct_size,fptr_dest);
            break;
            
       case c:
           copyContent(music->fptr, music->pos[m_comment], fptr_dest);
           copynewcon(music->fptr,name,fptr_dest);
            copyreminingcon(music->fptr,music->co_size,fptr_dest);
            break;
           
        }
    }
    return m_success;
}

Status copyheader(FILE *fptr, FILE *fptr_dest)
{
    rewind(fptr);
    char buffer[10];
    fread(buffer, 10, 1, fptr);
    fwrite(buffer, 10, 1, fptr_dest);
    return m_success;
}

etags checkoption(char *ch)
{
    if (!strcmp(ch, "-t"))
        return t;
    else if (!strcmp(ch, "-a"))
        return a;
    else if (!strcmp(ch, "-A"))
        return A;
    else if (!strcmp(ch, "-y"))
        return y;
    else if (!strcmp(ch, "-m"))
        return m;
    else if (!strcmp(ch, "-c"))
        return c;
}

Status copyContent(FILE *fptr_src, int pos, FILE *fptr_dest)
{
    char ch;
    for (int i = 10; i < pos; i++)
    {
        fread(&ch, 1, 1, fptr_src);
        fwrite(&ch, 1, 1, fptr_dest);
    }
    return m_success;
}

Status copynewcon(FILE *fptr_src,char *name,FILE *fptr_dest)
{
    int size=strlen(name)+1;    //including NULL 
    //encode size
    char bytes[4];
    for(int i=0;i<4;i++)
    {
        bytes[3-i]=(size >> i*8) & 0xFF;
    }
    fwrite(bytes,4,1,fptr_dest);
    fseek(fptr_src,4,SEEK_CUR);
    char buff[3];
    fread(buff,3,1,fptr_src);
    fwrite(buff,3,1,fptr_dest);
    fwrite(name,size-1,1,fptr_dest);
    return m_success;
}

Status copyreminingcon(FILE *fptr_src,int s,FILE *fptr_dest)
{
    char ch;
    fseek(fptr_src,s,SEEK_CUR);
    while(fread(&ch,1,1,fptr_src))
    {
        fwrite(&ch,1,1,fptr_dest);
    }
    return m_success;
}

Status copyallContents(FILE *fptr_src,FILE *fptr_dest)
{
    rewind(fptr_src);
    rewind(fptr_dest);
    char ch;
    while(fread(&ch,1,1,fptr_dest) > 0)
    {
        fwrite(&ch,1,1,fptr_src);
    }
    fclose(fptr_dest);
    return m_success;
}

