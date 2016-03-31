LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := JniHelper
LOCAL_SRC_FILES := JniHelper.c
LOCAL_LDFLAGS = -llog
include $(BUILD_SHARED_LIBRARY)