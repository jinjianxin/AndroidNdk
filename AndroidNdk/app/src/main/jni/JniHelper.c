#include <android/log.h>


#include "simple_ndk_wxelife_com_ndksimple_NdkHelper.h"
JNIEXPORT jstring JNICALL Java_simple_ndk_wxelife_com_androidndk_MainActivity_getCLanguageString
        (JNIEnv *env, jobject obj)
{
    __android_log_print(ANDROID_LOG_DEBUG,"guidongli","%s",__FUNCTION__);
    return (*env)->NewStringUTF(env,"This just a test for Android Studio NDK JNI developer!");
}