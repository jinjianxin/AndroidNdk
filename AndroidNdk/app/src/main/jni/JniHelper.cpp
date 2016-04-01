#include <android/log.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "simple_ndk_wxelife_com_ndksimple_NdkHelper.h"

struct NativeWorksArgs
{
    jint id;
    jint iterations;
};

static JavaVM *gVm = NULL;
static jobject gObj = NULL;

static jmethodID gOnNativeMessage = NULL;
static pthread_mutex_t mutex;

JNIEXPORT jstring JNICALL Java_simple_ndk_wxelife_com_androidndk_MainActivity_getCLanguageString
(JNIEnv *env, jobject obj)
{
    __android_log_print(ANDROID_LOG_DEBUG,"guidongli","%s",__FUNCTION__);
    return env->NewStringUTF("This just a test for Android Studio NDK JNI developer!");
}

JNIEXPORT void JNICALL Java_simple_ndk_wxelife_com_androidndk_MainActivity_nativeInit
(JNIEnv *env, jobject obj)
{

if (0 != pthread_mutex_init(&mutex, NULL))
  {
    // Get the exception class
    jclass exceptionClazz = env->FindClass(
        "java/lang/RuntimeException");

    // Throw exception
    env->ThrowNew(exceptionClazz, "Unable to initialize mutex");
    goto exit;
  }


    if(NULL ==gObj)
    {
        gObj = env->NewGlobalRef(obj);

        if(NULL == gObj)
        {
            goto exit;
        }
    }

    if(NULL == gOnNativeMessage)
    {
        jclass clazz = env->GetObjectClass(obj);

        gOnNativeMessage = env->GetMethodID(clazz,"OnNativeMessage","(Ljava/lang/String;)V");

        if(NULL == gOnNativeMessage)
        {
            jclass exceptionsClazz = env->FindClass("java/lang/RuntimeExceptionn");
            env->ThrowNew(exceptionsClazz,"Unable to find method");
        }
    }

exit:
    return ;
}


JNIEXPORT void JNICALL Java_simple_ndk_wxelife_com_androidndk_MainActivity_nativeFree
(JNIEnv *env, jobject obj)
{
    if(NULL !=gObj)
    {
        env->DeleteGlobalRef(gObj);
        gObj = NULL;
    }
}

JNIEXPORT void JNICALL Java_simple_ndk_wxelife_com_androidndk_MainActivity_nativeWorker
(JNIEnv * env, jobject obj,jint id ,jint iterations)
{

#if 0
    for(int i=0; i<iterations; i++)
    {
        char message[26];
        sprintf(message,"Worker %d: Iteration %d",id,i);

        jstring messageString  = env->NewStringUTF(message);

        env->CallVoidMethod(obj,gOnNativeMessage,messageString);

        if(NULL !=env->ExceptionOccurred())
            break;

        sleep(1);

    }

#else

  

    if (0 != pthread_mutex_lock(&mutex))
    {
        // Get the exception class
        jclass exceptionClazz = env->FindClass(
                                    "java/lang/RuntimeException");

        // Throw exception
        env->ThrowNew(exceptionClazz, "Unable to lock mutex");
        goto exit;
    }

    // Loop for given number of iterations
    for (jint i = 0; i < iterations; i++)
    {
        // Prepare message
        char message[26];
        sprintf(message, "Worker %d: Iteration %d", id, i);

        __android_log_print(ANDROID_LOG_DEBUG,"guidongli","%s\t%d\t%d",__FUNCTION__,__LINE__,iterations);
        // Message from the C string
        jstring messageString = env->NewStringUTF(message);

        // Call the on native message method
        env->CallVoidMethod(obj, gOnNativeMessage, messageString);

        // Check if an exception occurred
        if (NULL != env->ExceptionOccurred())
            break;

        // Sleep for a second
        sleep(1);
    }

    // Unlock mutex
    if (0 != pthread_mutex_unlock(&mutex))
    {
        // Get the exception class
        jclass exceptionClazz = env->FindClass(
                                    "java/lang/RuntimeException");

        // Throw exception
        env->ThrowNew(exceptionClazz, "Unable to unlock mutex");
    }

exit:
    return;

#endif
}

static void* nativeWorksThread(void *arg)
{
    JNIEnv *env = NULL;

    if(0 == gVm->AttachCurrentThread(&env,NULL))
    {
        NativeWorksArgs *nativeWorksArgs = (NativeWorksArgs *)arg;

        
        Java_simple_ndk_wxelife_com_androidndk_MainActivity_nativeWorker(env,gObj,nativeWorksArgs->id,nativeWorksArgs->iterations);

        delete nativeWorksArgs;

        gVm->DetachCurrentThread();

    }

    return (void*)1;

}

JNIEXPORT void JNICALL Java_simple_ndk_wxelife_com_androidndk_MainActivity_nativeWThreads
(JNIEnv *env, jobject obj,jint id ,jint iterations)
{

 

    for (int i = 0; i < id; i++)
    {
        NativeWorksArgs  *nativeWorksArgs = new NativeWorksArgs();

        nativeWorksArgs->id=i;
        nativeWorksArgs->iterations =iterations;
      
        pthread_t thread;

        int result = pthread_create(&thread,NULL,nativeWorksThread,(void*)nativeWorksArgs);

        if(0 !=result)
        {
            jclass exceptionsClazz = env->FindClass("java/lang/RuntimeExceptionn");
        }
    }
}

jint JNI_OnLoad (JavaVM* vm, void* reserved)
{
  // Cache the JavaVM interface pointer
  __android_log_print(ANDROID_LOG_DEBUG,"guidongli","%s",__FUNCTION__);
  gVm = vm;

  return JNI_VERSION_1_4;
}