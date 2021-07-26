#include "com_wang_testapp_ccp_NativeTest.h"
#include "string.h"

JNIEXPORT jstring JNICALL Java_com_wang_testapp_ccp_NativeTest_sayHello
        (JNIEnv *env, jclass jobject, jstring jstr) {
    const char *c_str = NULL;
    c_str = (*env)->GetStringUTFChars(env, jstr, NULL);
    if (c_str == NULL) {
        return NULL;
    }
    int size = strlen(c_str) + 4 * 2;
    printf("buf.size: %d \n", size);
    char buf[128] = {0};
    sprintf(buf, "hey %s", c_str);
    (*env)->ReleaseStringUTFChars(env, jstr, c_str);//释放资源
    jstr = NULL;
    c_str = NULL;
    return (*env)->NewStringUTF(env, buf);
}

JNIEXPORT jstring JNICALL Java_com_wang_testapp_ccp_NativeTest_getString
        (JNIEnv *env, jclass jobject) {
    return (*env)->NewStringUTF(env, "hello world!");
}

JNIEXPORT jint JNICALL Java_com_wang_testapp_ccp_NativeTest_getProperties
        (JNIEnv *env, jobject jobj) {
    jclass jclz = (*env)->GetObjectClass(env, jobj);
    jfieldID fieldId = (*env)->GetFieldID(env, jclz, "properties", "I");
    return (*env)->GetIntField(env, jobj, fieldId);
}

JNIEXPORT void JNICALL Java_com_wang_testapp_ccp_NativeTest_callStaticMethod
        (JNIEnv *env, jclass jclz) {
    //1,找到类
    jclass methodClassClz = (*env)->FindClass(env, "com/wang/testapp/ccp/ClassMethod");
    if (methodClassClz == NULL) {
        return;
    }
    //2,找到方法, class, 方法名，方法签名           (Ljava/lang/String;I)V
    jmethodID callStaticMethodID = (*env)->GetStaticMethodID(env, methodClassClz, "callStaticMethod",
                                                             "(Ljava/lang/String;I)V");
    if (callStaticMethodID == NULL) {
        return;
    }
    //3,转化成java对应的jstring c中只有char*指针，没有String概念
    jstring str = (*env)->NewStringUTF(env, "i am static");
    //4,调用方法吗
    (*env)->CallStaticVoidMethod(env, methodClassClz, callStaticMethodID, str, 10086);
    //5,释放变量
    (*env)->DeleteLocalRef(env, methodClassClz);
    (*env)->DeleteLocalRef(env, str);
    methodClassClz = NULL;
    str = NULL;
}

JNIEXPORT void JNICALL Java_com_wang_testapp_ccp_NativeTest_callInstanceMethod
        (JNIEnv *env, jclass jclz) {
    //1,找到类，全类名
    jclass methodClassClz = (*env)->FindClass(env, "com/wang/testapp/ccp/ClassMethod");
    if (methodClassClz == NULL) {
        return;
    }
    //2,找到构造方法, 所有的构造方法的名都为init
    jmethodID constructor = (*env)->GetMethodID(env, methodClassClz, "<init>", "()V");
    if (constructor == NULL) {
        return;
    }
    //3,生成对象实例
    jobject methodClassObj = (*env)->NewObject(env, methodClassClz, constructor);
    if (methodClassObj == NULL) {
        return;
    }
    //4,获得属性方法
    jmethodID callInstanceMethodID = (*env)->GetMethodID(env, methodClassClz, "callInstanceMethod",
                                                         "(Ljava/lang/String;I)V");
    //5,调用属性方法
    jstring str = (*env)->NewStringUTF(env, "respect ");
    (*env)->CallStaticVoidMethod(env, methodClassClz, callInstanceMethodID, str, 110);
    //6,释放变量
    (*env)->DeleteLocalRef(env, methodClassClz);
    (*env)->DeleteLocalRef(env, str);
    methodClassClz = NULL;
    str = NULL;
}

JNIEXPORT jstring JNICALL Java_com_wang_testapp_ccp_NativeTest_testPoint
        (JNIEnv *env, jclass jclz) {
    static jclass strClz = NULL;
    static jmethodID methodID = NULL;
    printf("line one ---------------- \n");
    //获取String
    if (strClz == NULL) {
        printf("strClz is NULL \n");
        strClz = (*env)->FindClass(env, "java/lang/String");
    }
    if (methodID == NULL) {
        printf("methodID is NULL \n");
        methodID = (*env)->GetMethodID(env, strClz, "<init>", "([C)V");
    }
    printf("line two ---------------- \n");
    jcharArray charArray = (*env)->NewCharArray(env, 10);
    jstring str = (*env)->NewObject(env, strClz, methodID, charArray);
    printf("line three ---------------- \n");

    (*env)->DeleteLocalRef(env, strClz);
    strClz = NULL;
    return str;
}
