/*
 * jni基本数据交互
 *
 *  Created on: 2014-4-10
 *      Author: vincexie
 */
 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <jni.h>
#include <assert.h>


// 获取数组的大小
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
// 指定要注册的类，对应完整的java类名
#define JNIREG_CLASS "com/vince/android_c/MainActivity"


// 引入log头文件
#include <android/log.h>

// log标签
#define  TAG    "c log"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

/*
 * 将字符串由JNI传递给Java
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 */
JNIEXPORT jstring JNICALL
stringJfromC(JNIEnv *env, jobject clazz)
{
    // 将“Hello From jni”转行成jstring类型
    jstring str = (*env)->NewStringUTF(env, "Hello From Jni");
    return str;
}


/*
 * 将字符串从java从到C。
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 *        val : java传递给jni的string类型值。
 */
JNIEXPORT void JNICALL
stringJtoC(JNIEnv *env, jobject clazz, jstring val)
{
    // 将java传递给jni的string转行成char *类型。
    // const char * GetStringUTFChars(JNIEnv *env, jstring string, jboolean *isCopy);
    // env:JNI 接口指针。
    // string:Java 字符串对象。
    // isCopy:指向布尔值的指针，JNI_TRUE或JNI_FALSE。
    //         JNI_TRUE  —— 开新内存，然后把java中的string拷贝到这个内存中，然后返回指向这个内存地址的指针。
    //         JNI_FALSE —— 直接返回指向java中String内存的指针，这个时候千万不要改变这个内存的内容，这将破坏String在java中始终是常量这个原则。
    char *str = (char *)(*env)->GetStringUTFChars(env, val, JNI_FALSE);
    LOGD("%s str=%s\n", __func__, str);
}

/*
 * 将“浮点数”由JNI传递给Java
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 */
JNIEXPORT jfloat JNICALL
floatJfromC(JNIEnv *env, jobject clazz)
{
    return (jfloat)1.34;
}
/*
 * 将“浮点数”从Java从到C。
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 *        val : java传递给jni的浮点数。
 */
JNIEXPORT void JNICALL
floatJtoC(JNIEnv *env, jobject clazz, jfloat val)
{
    float f = (float)val;
    LOGD("%s f=%f\n", __func__, f);
}

/*
 * 将“整数”由JNI传递给Java
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 */
JNIEXPORT jint JNICALL
intJfromC(JNIEnv *env, jobject clazz)
{
    return (jint)25;
}
/*
 * 将“整数”从Java从到C。
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 *        val : java传递给jni的整数。
 */
JNIEXPORT void JNICALL
intJtoC(JNIEnv *env, jobject clazz, jint val)
{
    int i = (int)val;
    LOGD("%s i=%d\n", __func__, i);
}

// (Ljava/lang/String;)V：java函数，前面参数后面返回值
static JNINativeMethod method_table[] = {
    { "intJfromC"        , "()I"                    , (void*)intJfromC},
    { "intJtoC"        , "(I)V"                , (void*)intJtoC},
    { "floatJfromC"    , "()F"                    , (void*)floatJfromC},
    { "floatJtoC"        , "(F)V"                , (void*)floatJtoC},
    { "stringJfromC"    , "()Ljava/lang/String;"    , (void*)stringJfromC},
    { "stringJtoC"        , "(Ljava/lang/String;)V", (void*)stringJtoC},
};

// 注册native方法到java中
static int registerNativeMethods(JNIEnv* env, const char* className,
        JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

int register_basic_ndk_param(JNIEnv *env)
{
    // 调用注册方法
    return registerNativeMethods(env, JNIREG_CLASS,
            method_table, NELEM(method_table));
}

// JNI_OnLoad在jni注册时，会被回调执行。
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }

    register_basic_ndk_param(env);

    // 返回jni的版本
    return JNI_VERSION_1_4;
}


