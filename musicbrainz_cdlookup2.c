#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <musicbrainz5/mb5_c.h>
#include<discid/discid.h>

int main(int argc, const char *argv[])
{
    
  DiscId *disc = discid_new();
  if(discid_read(disc,NULL)==0)
  {
    printf("Error in reading Disc\n");
    return 0;
  }
  const char *DiscID=discid_get_id(disc);

  Mb5Query Query=mb5_query_new("cdlookupcexample-1.0",NULL,0);
  if (Query)
  {
   Mb5Metadata Metadata1=mb5_query_query(Query,"discid",DiscID,"",0,NULL,NULL);
   char ErrorMessage[256];

   tQueryResult Result=mb5_query_get_lastresult(Query);
   int HTTPCode=mb5_query_get_lasthttpcode(Query);

   mb5_query_get_lasterrormessage(Query,ErrorMessage,sizeof(ErrorMessage));
   printf("Result: %d\nHTTPCode: %d\nErrorMessage: '%s'\n",Result,HTTPCode,ErrorMessage);

   if (Metadata1)
   {
    Mb5Disc Disc=mb5_metadata_get_disc(Metadata1);
    if (Disc)
    {
     Mb5ReleaseList ReleaseList=mb5_disc_get_releaselist(Disc);
     if (ReleaseList)
     {
      int ThisRelease=0;

      printf("Found %d release(s)\n",mb5_release_list_size(ReleaseList));

      for (ThisRelease=0;ThisRelease<mb5_release_list_size(ReleaseList);ThisRelease++)
      {
        Mb5Metadata Metadata2=0;
        Mb5Release Release=mb5_release_list_item(ReleaseList,ThisRelease);

        if (Release)
        {
            //Everything else is same as in the last tutorials. 
        }
      }
     }
    }
   }
 return 0;
}
