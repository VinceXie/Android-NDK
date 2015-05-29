/*
 * jni_dynamicHello.c
 *
 *	JNI_OnLoad里面动态注册
 *
 *  Created on: 2014-4-10
 *      Author: vincexie
 */
 
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<jni.h>
#include<assert.h>


// 获取数组的大小
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
// 指定要注册的类，对应完整的java类名
#define JNIREG_CLASS "com/vince/android_c/MainActivity"


// 返回字符串"hello load jni"
JNIEXPORT jstring JNICALL native_hello(JNIEnv *env, jclass clazz)
{
    return (*env)->NewStringUTF(env, "hello load dynamic jni.");
}

// Java和JNI函数的绑定表
//name：Java中函数的名字。
//signature：Java中函数的参数和返回值。一般的形式是"(arg-types)return-type"：arg-types对应是参数类型，空白表示没有参数；return-type是返回值类型，不能是空白，若返回void，则应该设置return-type为V。
//fnPtr：指向native函数的函数名称。前面都要接 (void *)
static JNINativeMethod method_table[] = {
    { "dynamicHello", "()Ljava/lang/String;", (void*)native_hello },//绑定
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

int register_ndk_load(JNIEnv *env)
{
    // 调用注册方法
    return registerNativeMethods(env, JNIREG_CLASS,
            method_table, NELEM(method_table));
}

/**
 * 加载时调用register_ndk_load调用registerNativeMethods。
 */
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }

    register_ndk_load(env);

    // 返回jni的版本
    return JNI_VERSION_1_4;
}
