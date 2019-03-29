//
// Created by 王诛魔 on 2019/3/28.
//

#include "list_file.h"

void list_file()
{
    int result;
    AVIODirContext *ctx = NULL;
    AVIODirEntry *entry = NULL;

    av_log_set_level(AV_LOG_INFO);

    result = avio_open_dir(&ctx ,"./",NULL);

    if(result < 0){
        av_log(NULL,AV_LOG_ERROR,"Can't Open Dir : %s\n",av_err2str(result));
    }

    while(1){
        //allo entry
        result = avio_read_dir(ctx, &entry);
        if(result < 0){
            av_log(NULL,AV_LOG_ERROR,"Can't Read Dir : %s\n",av_err2str(result));
            goto __FAIL;
        }
        if(!entry){
            //if entry null, return while
            break;
        }
        av_log(NULL,AV_LOG_INFO,"%12"PRId64"  %s \n",entry->size,entry->name);
        //entry need free
        avio_free_directory_entry(&entry);
    }
    __FAIL:
    //destory resouse
    avio_close_dir(&ctx);
}
