LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE := wjj
LOCAL_SRC_FILES := wjjcode/lapi.c \
wjjcode/lcode.c \
wjjcode/lctype.c \
wjjcode/ldebug.c \
wjjcode/ldo.c \
wjjcode/ldump.c \
wjjcode/lfunc.c \
wjjcode/lgc.c \
wjjcode/llex.c \
wjjcode/lmem.c \
wjjcode/lobject.c \
wjjcode/lopcodes.c \
wjjcode/lparser.c \
wjjcode/lstate.c \
wjjcode/lstring.c \
wjjcode/ltable.c \
wjjcode/ltm.c \
wjjcode/lundump.c \
wjjcode/lvm.c \
wjjcode/lzio.c \
wjjcode/lauxlib.c \
wjjcode/lbaselib.c \
wjjcode/lbitlib.c \
wjjcode/lcorolib.c \
wjjcode/ldblib.c \
wjjcode/liolib.c \
wjjcode/lmathlib.c \
wjjcode/loslib.c \
wjjcode/lstrlib.c \
wjjcode/ltablib.c \
wjjcode/lutf8lib.c \
wjjcode/loadlib.c \
wjjcode/linit.c
LOCAL_CFLAGS := -DLUA_DL_DLOPEN
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/wjjcode
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := mis
LOCAL_SRC_FILES := mis/cul_interface.c
LOCAL_CFLAGS := -DJNI_SUPPORT
LOCAL_STATIC_LIBRARIES := wjj
include $(BUILD_SHARED_LIBRARY)