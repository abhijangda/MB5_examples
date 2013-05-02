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
                        
                        char *ParamNames2[]={"inc"};
                        char *ParamValues2[]={"release-group"};
                        Mb5Metadata Metadata2 = mb5_query_query(Query,"artist",Value,"",1,ParamNames2,ParamValues2);
                    
                        Result=mb5_query_get_lastresult(Query);
                        HTTPCode=mb5_query_get_lasthttpcode(Query);
                    
                        if(Result==eQuery_Success)
                             printf("Success\n");
                        else
                        {
                            mb5_query_get_lasterrormessage(Query,ErrorMessage,sizeof(ErrorMessage));
                            printf("ErrorMessage: '%s'\n",ErrorMessage);
                            continue;
                        }
                        
                        Mb5ReleaseGroupList RGroupList = mb5_metadata_get_releasegroup_list(Metadata2);
                        int ThisRList;
                        for(ThisRList = 0; ThisRList<mb5_releasegroup_list_size(RGroupList); ThisRList++)
                        {
                            Mb5ReleaseGroup RGroup = mb5_releasegroup_list_get_item(RGroupList, ThisRList);
                            mb5_releasegroup_get_name(RGroup,Name,256)
                            printf("Release Group is %s\n",Name);
                        }
                        
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
            int ThisR;
            Mb5ReleaseList ReleaseList=mb5_metadata_get_releaselist(Metadata);
            Mb5ArtistList ArtistList = mb5_metadata_get_artistlist(Metadata);
            printf("Found Artist %d\n",mb5_artist_list_size(ArtistList));
            printf("Found %d releases(s)\n",mb5_release_list_size(ReleaseList));
            for (ThisR=0;ThisR<mb5_release_list_size(ReleaseList);ThisR++)
            {
                Mb5ReleaseList Release=mb5_release_list_item(ReleaseList,ThisR);
                if (Release)
                {
                    int count;
                    char Name[256];
                    char Value[256];
            
                    mb5_release_get_title(Release,Name,sizeof(Name));
                    mb5_release_get_id(Release,Value,sizeof(Value));
                    printf("Release is '%s' ID is %s\n",Name,Value);
                    
                    char *ParamNames2[]={"inc"};
                    char *ParamValues2[]={"artists recordings"};
                    Mb5Metadata Metadata2 = mb5_query_query(Query,"release",Value,"",1,ParamNames2,ParamValues2);
                    
                    Result=mb5_query_get_lastresult(Query);
                    HTTPCode=mb5_query_get_lasthttpcode(Query);
                    
                    if(Result==eQuery_Success)
                         printf("Success\n");
                    else if(Result==eQuery_ResourceNotFound)
                         printf("Resource Not Found\n");
                    else if(Result==eQuery_ConnectionError)
                         printf("ConnectionError\n");
                    else if(Result==eQuery_Timeout)
                         printf("Timeout\n");
                    else if(Result==eQuery_AuthenticationError)
                         printf("AuthenticationError\n");
                    else if(Result==eQuery_FetchError)
                         printf("eQuery_FetchError\n");
                    else if(Result==eQuery_RequestError)
                         printf("RequestError\n");
                        
                        
                    
                    }
                else
                {
                    printf("Couldn't get artist %d\n",ThisR);
                    }
                }
            mb5_metadata_delete(Metadata);
            }
        
        mb5_query_delete(Query);
        }
    return 0;
    }
