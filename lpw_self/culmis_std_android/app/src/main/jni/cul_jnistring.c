#include "jni.h"
#include "cul_jnistring.h"
#include "stdio.h"
#include "string.h"


/*java字符串转C字符串GBK编码方式*/
char* jstringTostrGBK(JNIEnv* env, jstring jstr)
{
    char* pStr = NULL;

    jclass     jstrObj   = (*env)->FindClass(env, "java/lang/String");
    jstring    encode    = (*env)->NewStringUTF(env, "gbk");
    jmethodID  methodId  = (*env)->GetMethodID(env, jstrObj, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray byteArray = (jbyteArray)(*env)->CallObjectMethod(env, jstr, methodId, encode);
    jsize      strLen    = (*env)->GetArrayLength(env, byteArray);
    jbyte      *jBuf     = (*env)->GetByteArrayElements(env, byteArray, JNI_FALSE);

    if (jBuf > 0)
    {
        pStr = (char*)malloc(strLen + 1);

        if (!pStr)
        {
            return NULL;
        }

        memcpy(pStr, jBuf, strLen);

        pStr[strLen] = 0;
    }

    (*env)->ReleaseByteArrayElements(env, byteArray, jBuf, 0);

    return pStr;
}

/*java字符串转C字符串UTF8编码方式*/
char* jstringTostrUTF8(JNIEnv* env, jstring jstr)
{
    char* pStr = NULL;

    jclass     jstrObj   = (*env)->FindClass(env, "java/lang/String");
    jstring    encode    = (*env)->NewStringUTF(env, "utf-8");
    jmethodID  methodId  = (*env)->GetMethodID(env, jstrObj, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray byteArray = (jbyteArray)(*env)->CallObjectMethod(env, jstr, methodId, encode);
    jsize      strLen    = (*env)->GetArrayLength(env, byteArray);
    jbyte      *jBuf     = (*env)->GetByteArrayElements(env, byteArray, JNI_FALSE);

    if (jBuf > 0)
    {
        pStr = (char*)malloc(strLen + 1);

        if (!pStr)
        {
            return NULL;
        }

        memcpy(pStr, jBuf, strLen);

        pStr[strLen] = 0;
    }

    (*env)->ReleaseByteArrayElements(env, byteArray, jBuf, 0);

    return pStr;
}
/*C字符串转java字符串*/
jstring strToJstring(JNIEnv* env, const char* pStr)
{
    int        strLen    = strlen(pStr);
    jclass     jstrObj   = (*env)->FindClass(env, "java/lang/String");
    jmethodID  methodId  = (*env)->GetMethodID(env, jstrObj, "<init>", "([BLjava/lang/String;)V");
    jbyteArray byteArray = (*env)->NewByteArray(env, strLen);
    jstring    encode    = (*env)->NewStringUTF(env, "gbk");

    (*env)->SetByteArrayRegion(env, byteArray, 0, strLen, (jbyte*)pStr);

    return (jstring)(*env)->NewObject(env, jstrObj, methodId, byteArray, encode);
}

/*JAVA调用LoadLibrary时会执行到的函数*/ 
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    void *venv;

    return JNI_VERSION_1_6;
}

/*JNI_OnLoad相反*/ 
jint JNI_OnUnLoad(JavaVM* vm, void* reserved)
{

    return JNI_VERSION_1_6;
}
