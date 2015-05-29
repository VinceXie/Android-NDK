#http://mobilepearls.com/labs/native-android-api/#logging
#解释Android.mk用法

#每个Android.mk文件都必须在开头定义 LOCAL_PATH 变量。
#这个变量被用来寻找C/C++源文件。在该例中，my-dir 是一个由编译系统提供的宏函数，用于返回Android.mk所在目录的路径。
LOCAL_PATH := $(call my-dir)

#编译每个模块之前清除变量，消除影响。
include $(CLEAR_VARS)
#指定生成模块
LOCAL_MODULE    := vince_c_exe
#指定代码路径 多个文件用 \隔开
LOCAL_SRC_FILES := vince_c_exe.c
#include $(BUILD_EXECUTABLE) //可执行
#include $(BUILD_SHARED_LIBRARY) //动态链接可被调用如jni
#include $(BUILD_STATIC_LIBRARY) //静态链接
include $(BUILD_EXECUTABLE)


#例子
#include $(CLEAR_VARS)  
#LOCAL_MODULE := foo  
#LOCAL_SRC_FILES := foo/foo.c  
#LOCAL_EXPORT_LDLIBS := -llog  
#include $(BUILD_STATIC_LIBRARY)  
#  
#include $(CLEAR_VARS)  
#LOCAL_MODULE := bar  
#LOCAL_SRC_FILES := bar.c  
#LOCAL_STATIC_LIBRARIES := foo  
#include $(BUILD_SHARED_LIBRARY)
#此处在编译bar模块的时候，它的链接器标志将加上一个 -llog，表示它依赖于系统提供的 liblog.so，因为它依赖 foo 模块。