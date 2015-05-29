LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE    := exe_helloworld
LOCAL_SRC_FILES := exe_helloworld.c
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE    := jni_hello
LOCAL_SRC_FILES := \
jni_hello/jni_hello.c \
jni_hello/jni_dynamicHello.c \

include $(BUILD_SHARED_LIBRARY) 


include $(CLEAR_VARS)
LOCAL_MODULE    := jni_chatBasic
LOCAL_SRC_FILES := jni_chatBasic.c
# 添加对log库的支持
LOCAL_LDLIBS:=-L$(SYSROOT)/usr/lib -llog
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := jni_chatPerson
LOCAL_SRC_FILES := jni_chatPerson.c
# 添加对log库的支持
LOCAL_LDLIBS:=-L$(SYSROOT)/usr/lib -llog
include $(BUILD_SHARED_LIBRARY)