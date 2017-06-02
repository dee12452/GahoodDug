LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main
LOCAL_CFLAGS += -std=c99
LOCAL_CFLAGS += -Wall
LOCAL_CFLAGS += -Werror

SDL_PATH := ../SDL2
SDL_IMG_PATH := ../SDL2_image
FILE_LIST_GAME := $(wildcard $(LOCAL_PATH)/game/*.c)
FILE_LIST_INPUT := $(wildcard $(LOCAL_PATH)/input/*.c)
FILE_LIST_GRAPHICS := $(wildcard $(LOCAL_PATH)/graphics/*.c)
FILE_LIST_UTIL := $(wildcard $(LOCAL_PATH)/util/*.c)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(SDL_IMG_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(FILE_LIST_GAME:$(LOCAL_PATH)/%=%) \
	$(FILE_LIST_UTIL:$(LOCAL_PATH)/%=%) \
	$(FILE_LIST_INPUT:$(LOCAL_PATH)/%=%) \
	$(FILE_LIST_GRAPHICS:$(LOCAL_PATH)/%=%)

LOCAL_SHARED_LIBRARIES := SDL2
LOCAL_SHARED_LIBRARIES += SDL2_image

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
