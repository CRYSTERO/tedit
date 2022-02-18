#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <termios.h>

struct termios orig_termios;                    /*保存修改前的终端属性*/

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);  //将终端属性恢复为修改前的
}

void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);                     //在修改终端属性之前将原来的保存在orig_termios结构体中
    atexit(disableRawMode);                                     //传入函数指针，主函数返回或exit()退出程序时自动执行指向的函数

    struct termios raw_termios = orig_termios;                  //termios是一个表示终端属性的结构体
    raw_termios.c_lflag &= ~(ECHO | ICANON);                    //ECHO是32位数，仅第四位为1。它使得用户在shell上输入的每个字符都同步显示出来，这里将其关闭，原因后面会说。这里将c_lflag的第四位强制变为0，其余位不变。
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios);           //将修改过的终端属性写回结构体
}

int main(void)
{
    enableRawMode();

    char ch;
    while(read(STDIN_FILENO, &ch, 1) == 1 && ch != 'q')
    {
        if(iscntrl(ch))
        {
            printf("%d\n", ch);
        }
        else
        {
            printf("%d ('%c') \n",ch, ch);
        }
    }
    return 0;
}
