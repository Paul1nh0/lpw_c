#ifndef __CULJNISTRING_H__
#define __CULJNISTRING_H__


char* jstringTostrGBK(JNIEnv* env, jstring jstr);
char* jstringTostrUTF8(JNIEnv* env, jstring jstr);
jstring strToJstring(JNIEnv* env, const char* pStr);

#endif
