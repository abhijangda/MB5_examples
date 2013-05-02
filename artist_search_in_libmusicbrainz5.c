#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <musicbrainz5/mb5_c.h>

int main(int argc, const char *argv[])
{
    Mb5Query Query;    
    argc=argc;
    argv=argv;

    Query=mb5_query_new("westlife-search-example",NULL,0);
    if (Query)
    {
        char *ParamNames[] = {"query","limit"};
        char *ParamValues[] = {"artist:Westlife","5"}

        Mb5Metadata Metadata;
        char ErrorMessage[256];
        tQueryResult Result;
        int HTTPCode;
    
        Metadata=mb5_query_query(Query,"artist","","",1,ParamNames,ParamValues);
    
        Result=mb5_query_get_lastresult(Query);
        HTTPCode=mb5_query_get_lasthttpcode(Query);
        
        printf("HTTPCode: %d\n",HTTPCode);

        if(Result==eQuery_Success)
             printf("Result: Success\n");
        else
        { 
            if(Result==eQuery_ResourceNotFound)          
               printf("Result: Resource Not Found\n");
        
            else if(Result==eQuery_ConnectionError)            
                printf("Result: ConnectionError\n");
        
            else if(Result==eQuery_Timeout)        
                printf("Result: Timeout\n");
  	    
            else if(Result==eQuery_AuthenticationError)        
                printf("Result: AuthenticationError\n");
        
            else if(Result==eQuery_FetchError)        
                printf("Result: eQuery_FetchError\n");
        
            else if(Result==eQuery_RequestError)        
                printf("Result: RequestError\n");

            mb5_query_get_lasterrormessage(Query,ErrorMessage,sizeof(ErrorMessage));
            printf("ErrorMessage: '%s'\n",ErrorMessage);
            return;
        }
    
        if (Metadata)
        {
            int ThisArtist;
            Mb5ArtistList ArtistList=mb5_metadata_get_artistlist(Metadata);
            
            printf("Found %d artist(s)\n",mb5_artist_list_size(ArtistList));
            for (ThisArtist=0;ThisArtist&ltmb5_artist_list_size(ArtistList);ThisArtist++)
            {
                Mb5Artist Artist=mb5_artist_list_item(ArtistList,ThisArtist);
                if (Artist)
                {
                    char Name[256];
                    char Value[1024];
                    
                    mb5_artist_get_name(Artist,Name,sizeof(Name));
                    printf("Artist is '%s'\n",Name);
                    mb5_artist_get_id(Artist,Value,sizeof(Value));
                    printf("Artist ID is %s\n",Value);
                }
                    
                else
                {
                    printf("Couldn't get artist %d\n",ThisArtist);
                }
            }
            mb5_metadata_delete(Metadata);
        }
        mb5_query_delete(Query);
    }
    return 0;
}