#include "jni.h"
#include "math.h"

void func1(JNIEnv *env, jclass jobject) {
    printf("func1 !");
}

jstring func2(JNIEnv *env, jclass jobject) {
    printf("func2 !");
    return (*env)->NewStringUTF(env, "hello world! from func2");
}

jint func3(JNIEnv *env, jclass jobject, int a) {
    printf("func3 %d", (a + 1));
    return a + 1;
}

/**
 * 在jni_h中声明
 * mClassName 需要反射的类的全类名
 * mMethods 函数映射表
 * @param vm
 * @param reserved
 * @return
 */
static const char *mClassName = "com/wang/testapp/ccp/NativeTest";

static const JNINativeMethod mMethods[] = {
        //java函数名，函数签名，对应的函数
        {"sayHello",  "()V",                  (void *) func1},
        {"getString", "()Ljava/lang/String;", (char *) func2},
        {"getInt",    "(I)I",                 (void *) func3},
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    printf("JNI_OnLoad \n");
    JNIEnv *env = NULL;
    //获得 JniEnv
    int r = (*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_4);
    if (r != JNI_OK) {
        return -1;
    }
    jclass mainActivityCls = (*env)->FindClass(env, mClassName); // 注册 如果小于0则注册失败
    r = (*env)->RegisterNatives(env, mainActivityCls, mMethods, 3);
    if (r != JNI_OK) {
        return -1;
    }
    return JNI_VERSION_1_4;
}
