#include<jni.h>
#include<string.h>

/**
 * 静态注册方法
 * 头文件生成后函数记得要加参数
 */
JNIEXPORT jstring JNICALL Java_com_vince_android_1c_MainActivity_sayHello
  (JNIEnv * env, jobject thiz)
{
	return (*env)->NewStringUTF(env, "Hello from JNI !");
}
