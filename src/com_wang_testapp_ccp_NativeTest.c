#include "com_wang_testapp_ccp_NativeTest.h"

JNIEXPORT void JNICALL Java_com_wang_testapp_ccp_NativeTest_sayHello
        (JNIEnv *env, jclass jobject) {
    printf("hello !");
}

JNIEXPORT jstring JNICALL Java_com_wang_testapp_ccp_NativeTest_getString
        (JNIEnv *env, jclass jobject) {
    return (*env)->NewStringUTF(env, "hello world!");
}
