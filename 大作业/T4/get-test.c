#define __LIBRARY__        
#include "unistd.h" 

_syscall2(int, getString,char*,outputStr,unsigned int,size);    

int main(int argc, char** argv){
    char buf[1024]; //存储字符串
    int len=0;      //字符串长度
    //调用系统调用，从内核空间获取字符串到用户空间
    len = getString(buf, 30);
    //打印字符串
    printf("%s\n", buf);
    //返回字符串长度
    return len;
}

