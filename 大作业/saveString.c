#include <asm/segment.h>
#include <errno.h>
#include <unistd.h>

#define MAX_STRING_SIZE 1024

char input_string[MAX_STRING_SIZE] = {0};

// 保存字符串到内核
int sys_saveString(const char *inputStr)
{

    // 打印提示信息
    printk("write your string to save to kernel:\n");

    int len = 0; // 传入的字符串长度

    // 获取字符串长度
    while (get_fs_byte(inputStr + len) != '\0')
    {
        len++;
    }

    // 判断字符串长度是否超过最大长度
    if (len >= MAX_STRING_SIZE)
    {
        printk("string is too long!\n");
        return -EINVAL;
    }

    int i=0;
    // 复制字符串到input_string
    for (; i <= len; i++)
    {
        input_string[i] = get_fs_byte(inputStr + i);
    }

    // 打印保存成功信息
    printk("string saved to kernel!\n");

    // 返回字符串长度
    return len;
}

// 从内核获取字符串
int sys_getString(char *outputStr, unsigned int size)
{
    int len = 0; // 内核中的字符串长度
    // 获取内核中的字符串长度
    while (input_string[len] != '\0')
    {
        len++;
    }
    // 判断字符串长度是否超过最大长度
    if (len >= size)
    {
        printk("string is too long!\n");
        return -EINVAL;
    }
    int i = 0;
    // 复制字符串到用户空间
    for (; i <= len; i++)
    {
        put_fs_byte(input_string[i], outputStr + i);
    }
    // 打印获取成功信息
    printk("string got from kernel!\n");
    // 返回字符串长度
    return len;
}