#include<stdio.h>
#include<stdlib.h>
#include "edit.h"
#include "types.h"

int main(int argc,char *argv[])
{
    
    Music music;

    if(!strcmp(argv[1],"-v"))
    {
        if(argc != 3)
           WARNING();

        if(MusicView(argv,&music)==m_success)
        {
            printf("View success\n");
        }
    }
    else if(!strcmp(argv[1],"--help"))
    {
        puts("------------------------------------HELP MENU--------------------------------------------\n");
        printf("1.-v -> to view Music file contents\n");
        printf("2.-e -> to edit Music file contents\n");
             printf(" 2.1. -t -> to edit song title\n");
             printf("2.2. -a -> to edit artist name\n");
             printf("2.3. -A -> to edit album name\n");
             printf("2.4. -y -> to edit year\n");
             printf("2.5. -m -> to edit content\n");
        puts("------------------------------------------------------------------------------------------\n");         
    }
    else if(!strcmp(argv[1],"-e"))
    {
        if(argc < 5)
        WARNING();

        printf("You Selected Edit option\n");
        if(strstr(argv[4],".mp3") != NULL)
        {

          if(Mp3Edit(argv,&music)==m_success)
          {
            printf("Successfully Edited\n");
          }
         else
          {
            printf("Unable to Edit\n");
          }
        }
        else
        {
           printf("ERROR : Music File type only\n");
        }
        
    }


  
}




    void WARNING()
    {
    puts("-------------------------------------------------------------------------------------------\n");
    printf("ERROR: ./a.out : INVALID ARGUMENTS\nUSAGE : \n");
    printf("To view please pass like: ./a.out -v Musicfilename\n");
    printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text Musicfilename\n");
    printf("To get help pass like : ./a.out --help\n");
    puts("-------------------------------------------------------------------------------------------\n");
    exit(0);
   }








