#define TAG "MengluuLog"
#define    LOGI(...)       __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define    LOGD(...)     __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define    LOGE(...)     __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define    LOGW(...)    __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define    LOGF(...)     __android_log_print(ANDROID_LOG_FATAL, TAG, __VA_ARGS__)

#include <jni.h>
#include <android/log.h>
#include <Substrate/CydiaSubstrate.h>
#include <memory.h>
#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>
#import "Utils.h"
#include <string>

typedef struct CString
{
    void *Empty;
    void *WhiteChars;
    int32_t length;
    char start_char[1];
} CString;

int unicode2UTF(long unic, char *pOutput)
{
    if (unic >= 0xFFFF0000)
        unic %= 0xFFFF0000;
    if (unic <= 0x0000007F)
    {
        *pOutput = (unic & 0x7F);
        return 1;
    }
    else if (unic >= 0x00000080 && unic <= 0x000007FF)
    {
        *(pOutput + 1) = (unic & 0x3F) | 0x80;
        *pOutput = ((unic >> 6) & 0x1F) | 0xC0;
        return 2;
    }
    else if (unic >= 0x00000800 && unic <= 0x0000FFFF)
    {
        *(pOutput + 2) = (unic & 0x3F) | 0x80;
        *(pOutput + 1) = ((unic >> 6) & 0x3F) | 0x80;
        *pOutput = ((unic >> 12) & 0x0F) | 0xE0;
        return 3;
    }
    else if (unic >= 0x00010000 && unic <= 0x001FFFFF)
    {
        *(pOutput + 3) = (unic & 0x3F) | 0x80;
        *(pOutput + 2) = ((unic >> 6) & 0x3F) | 0x80;
        *(pOutput + 1) = ((unic >> 12) & 0x3F) | 0x80;
        *pOutput = ((unic >> 18) & 0x07) | 0xF0;
        return 4;
    }
    else if (unic >= 0x00200000 && unic <= 0x03FFFFFF)
    {
        *(pOutput + 4) = (unic & 0x3F) | 0x80;
        *(pOutput + 3) = ((unic >> 6) & 0x3F) | 0x80;
        *(pOutput + 2) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput + 1) = ((unic >> 18) & 0x3F) | 0x80;
        *pOutput = ((unic >> 24) & 0x03) | 0xF8;
        return 5;
    }
    else if (unic >= 0x04000000 && unic <= 0x7FFFFFFF)
    {
        *(pOutput + 5) = (unic & 0x3F) | 0x80;
        *(pOutput + 4) = ((unic >> 6) & 0x3F) | 0x80;
        *(pOutput + 3) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput + 2) = ((unic >> 18) & 0x3F) | 0x80;
        *(pOutput + 1) = ((unic >> 24) & 0x3F) | 0x80;
        *pOutput = ((unic >> 30) & 0x01) | 0xFC;
        return 6;
    }

    return 0;
}

void showMemoryHex(char* text,int length){
	char log[length*3+1];
	char table[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(int i=0;i<length;i++){
		log[3*i]=table[text[i]/0x10];
		log[3*i+1]=table[text[i]%0x10];
		log[3*i+2]=' ';
	}
	log[length*3]=0;
	LOGW("%x:%d:%s",text,length,log);
}

void CString_Print(CString *self)
{
    char *buff = (char *)malloc(self->length * 6);
    memset(buff,0,self->length * 6);
    for (int i = 0, off = 0; i < self->length; ++i)
        off += unicode2UTF(((short *)self->start_char)[i], buff + off);

    LOGW("%s", buff);
    //showMemoryHex(self->start_char, self->length*2);
    free(buff);
}
