#include "types.h"
#include "View.h"

Status printdetails(Music *music)
{ 
  puts("----------------------------------------------SELECTED VIEW DETAILS--------------------------------------------------");


  puts("---------------------------------------------------------------------------------------------------------------------");

  printf("                                     Music TAG READER AND EDITOR FOR IDV32                                          \n");
  puts("---------------------------------------------------------------------------------------------------------------------");

  printf("TITLE\t\t:\t\t%s\n",music->title);
  printf("ARTIST\t\t:\t\t%s\n",music->artist);
  printf("ALBUM\t\t:\t\t%s\n",music->album);
  printf("YEAR\t\t:\t\t%s\n",music->year);
  printf("CONTENT_TYPE\t:\t\t%s\n",music->contentType);

  puts("-----------------------------------------------------------------------------------------------------------------------\n");

return m_success;
}