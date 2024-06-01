#define __LIBRARY__        
#include "unistd.h" 

_syscall1(int, saveString, const char*, inputStr); 

int main(int argc, char** argv){
    int len = 0; //输入字符串的长度

    //判断输入参数是否为空
    if(argc < 1){
        printf("please input a string!\n");
        return -1;
    }
    //调用系统调用saveString，将输入字符串保存到内核中
    len = saveString(argv[1]);
    return len;
}

