/*
 * jni_chatPerson.c
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
#define JNIPAR_CLASS "com/vince/android_c/Person"


// 引入log头文件
#include <android/log.h>

// log标签
#define  TAG    "c person"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

// jfieldID结构体，用于保存类“Person.java”的filedID
struct PersonOffsets
{
    jfieldID    name;
    jfieldID    age;
    jfieldID    height;
} gPersonOffsets;

// 与“Person.java”对应的结构体，用于保存数据，并将数据赋值给Person.java的成员
typedef struct tagPerson
{
    char    mName[10];
    int     mAge;
    float   mHeight;
}Person;

// 定义了3个Person
static Person gPersons[] = {
    {"skywang", 25, 175},
    {"eman"   , 30, 166},
    {"Dan"    , 51, 172},
};
#define GPERSON_NUM NELEM(gPersons)

/*
 * 根据index获取Person信息。
 * 参数说明：
 *         env : JNI 接口指针。
 *        claszz : Java 类对象。
 *        person : 输入参数，java对象
 *        index : 输入参数，序列号。
 */
JNIEXPORT jint JNICALL
getPersonInfoByIndex(JNIEnv *env, jobject clazz, jobject person, jint index)
{

    // 若index无效，则直接返回-1。
    if ((int)index<0 || (int)index>=GPERSON_NUM)
        return -1;

    // 将Person数组(gPersons)中的第index个成员赋值给pPerson指针
    Person *pPerson = &gPersons[index];

    // 设置java对象person的mName
    jstring name = (*env)->NewStringUTF(env, pPerson->mName);
    (*env)->SetObjectField(env, person, gPersonOffsets.name, name);
    // 设置java对象person的mAge
    (*env)->SetIntField(env, person, gPersonOffsets.age, pPerson->mAge);
    // 设置java对象person的mHeight
    (*env)->SetFloatField(env, person, gPersonOffsets.height, pPerson->mHeight);

    LOGD("%s index-%d  mName:%s, mAge:%d, mHeight:%f\n",
            __func__, index, pPerson->mName, pPerson->mAge, pPerson->mHeight);

    return 0;
}


// 初始化函数，用于获取Java中各个成员对应的fieldID。
static void nativeClassInit (JNIEnv *env)
{
    jclass personClass = (*env)->FindClass(env, JNIPAR_CLASS);
    // 获取Person的mName成员对应的FieldID，并保存到gPersonOffsets中
    gPersonOffsets.name     = (*env)->GetFieldID(env, personClass, "mName"  , "Ljava/lang/String;");
    // 获取Person的mAge成员对应的FieldID，并保存到gPersonOffsets中
    gPersonOffsets.age      = (*env)->GetFieldID(env, personClass, "mAge"   , "I");
    // 获取Person的mHeight成员对应的FieldID，并保存到gPersonOffsets中
    gPersonOffsets.height   = (*env)->GetFieldID(env, personClass, "mHeight", "F");
}

// Java和JNI函数的绑定表
static JNINativeMethod method_table[] = {
    { "getPersonInfoByIndex", "(Lcom/vince/android_c/Person;I)I", (void*)getPersonInfoByIndex },//绑定
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

int register_ndk_param(JNIEnv *env)
{
    nativeClassInit(env);
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

    register_ndk_param(env);

    // 返回jni的版本
    return JNI_VERSION_1_4;
}
