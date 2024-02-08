#include "View.h"
#include "types.h"

Status MusicView(char *argv[],Music *music)
{
     
    if(strstr(argv[2],".mp3") != NULL)
    {
	music->fname=argv[2];
	music->fptr=fopen(music->fname,"r");
	if(music->fptr==NULL)
	{
	    perror("fopen");
	    fprintf(stderr, "ERROR: Unable to open file %s\n", music->fname);
	    return m_failure;
	}
    
	//check header and version
	char arr[4];
	rewind(music->fptr);
	int i;
	for(i=0;i<3;i++)
	{
	    fread(&arr[i],1,1,music->fptr);
	}
	arr[i]='\0';


	if(!strcmp(arr,"ID3"))
	{

	    char ch;
	    fread(&ch,1,1,music->fptr);
	
	    if(ch==0x04 || ch==0x03)
	    {
	
		if(ViewTF(music) == m_success)
		{

		    if(printdetails(music)==m_success)
		    {
			printf("---------------------------------DETAILS DISPLAYED SUCCESFULLY-----------------------------\n");
			return m_success;
		    }
		}

	    }
	}
	else
	{
	    printf("please pass the ID3 tag file!!!\n");
	    return m_failure;
	}

    }
    else
    {
	printf("Please pass Music file!!!\n");
	return m_failure;
    }
    return m_success;
}





//for version 3 and 4
Status ViewTF( Music *music)
{
    int s1=0;
    fseek(music->fptr,10,SEEK_SET);
    for(int i=0;i<5;i++)
	{
	char arr[4];
	fread(arr,4,1,music->fptr);
	if(!strcmp(arr,"TIT2"))
	{
		music->pos[m_title] = ftell(music->fptr);
		//printf("\n%d\n",music->pos[m_title]);
	    if(Fetchmusic(music->fptr,&s1,music->title)!=m_success)
	    {
		printf("Unable to Fetch the Title!!!\n");
		return m_failure;
	    }
			music->t_size=s1;
	}
	else if(!strcmp(arr,"TPE1"))
	{
		music->pos[m_artist] = ftell(music->fptr);
		music->ar_size=s1;
	    if(Fetchmusic(music->fptr,&s1,music->artist)!=m_success)
	    {
		printf("Unable to Fetch the artist name!!!\n");
		return m_failure;
	    }
		music->ar_size=s1;
	}
	else if(!strcmp(arr,"TALB"))
	{
		music->pos[m_album] = ftell(music->fptr);
	    if(Fetchmusic(music->fptr,&s1,music->album)!=m_success)
	    {
		printf("Unable to Fetch the album name!!!\n");
		return m_failure;
	    }
		music->al_size=s1;
		
	}
	else if(!strcmp(arr,"TYER"))
	{
		music->pos[m_year] = ftell(music->fptr);
	    if(Fetchmusic(music->fptr,&s1,music->year)!=m_success)
	    {
		printf("Unable to Fetch the year!!!\n");
		return m_failure;
	    }
		music->yr_size=s1;
	}
	else if(!strcmp(arr,"TCON"))
	{
		music->pos[m_contentType] = ftell(music->fptr);
	    if(Fetchmusic(music->fptr,&s1,music->contentType)!=m_success)
	    {
		printf("Unable to Fetch the content type!!!\n");
		return m_failure;
	    }
		music->ct_size=s1;

	}
	
     
   }
    return m_success;
}



//fetch the size and name
Status Fetchmusic(FILE *fptr,int *l,char *ptr)
{
	*l=0;
    unsigned int var1 = 0;
    for(int i=0; i<4; i++)
    {
	fread(&var1, 1,1,fptr);
	*l = *l<<8 | var1;
    }

	(*l)--;

    fseek(fptr,3,SEEK_CUR);
	int i;
    for(i=0;i<*l;i++)
    {
	fread(&ptr[i],1,1,fptr);
    }
	ptr[i]='\0';
    
	

    return m_success;

}

