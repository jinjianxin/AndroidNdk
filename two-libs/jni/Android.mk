# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# the purpose of this sample is to demonstrate how one can
# generate two distinct shared libraries and have them both
# uploaded in
#

LOCAL_PATH:= $(call my-dir)

# first lib, which will be built statically
#

#引用第三方的动态库，并调用其函数 ，编译类型为 PREBUILT_SHARED_LIBRARY 
include $(CLEAR_VARS)

LOCAL_MODULE    := libtwolib-first
LOCAL_SRC_FILES := libtwolib-first.so

#include $(BUILD_SHARED_LIBRARY)
include $(PREBUILT_SHARED_LIBRARY)

#引用自己编译的动态库，由源码编译而成，并调用其函数 ，编译类型为 BUILD_SHARED_LIBRARY

include $(CLEAR_VARS)

LOCAL_MODULE    := libtwolib-third
LOCAL_SRC_FILES := third.c

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_SHARED_LIBRARY)



# second lib, which will depend on and include the first one
#
include $(CLEAR_VARS)

LOCAL_MODULE    := libtwolib-second
LOCAL_SRC_FILES := second.c
LOCAL_SHARED_LIBRARIES := libtwolib-first libtwolib-third
#LOCAL_LDFLAGS += -L$(LOCAL_PATH)/libtwolib-first

include $(BUILD_SHARED_LIBRARY)
