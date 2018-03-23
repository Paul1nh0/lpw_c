
#include "jni.h"
#include "cul_jnistring.h"
#include "stdio.h"

#include <android/log.h>
#define LOG_TAG "System.out"  
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

jstring JNICALL Java_com_culmis_zero_culmis_JniInterface_CulInterface(JNIEnv *env, jobject obj, jstring in_str,jint mode)
{
#if 0
    char* strOut = (char*)malloc(8192);
	char* strInBuf = (char*)malloc(8192);

	if(strOut==NULL ||in_str ==NULL)
		return NULL;

	memset(strOut,0x00,8192);
	memset(strInBuf,0x00,8192);

	strInBuf = jstringTostrGBK(env,in_str);
    strcpy(strOut,strInBuf);
	jstring strResult = strToJstring(env,strOut);
	if(strOut!=NULL)
		free(strOut);
	if(strInBuf!=NULL)
		free(strInBuf);
#endif
	LOGD("[culmis] from C");
	return 0;//strResult;
}

