#make语句解释：目标是得到一个名为tedit的可执行文件，而要得到它需要tedit.c源文件。在第二行写具体的实现步骤。记得第二行要TAB一下(要按TAB键，四个空格没用)
#$(CC)是一个变量，默认make会将其当做操作系统中的"cc"命令。-Wall -Wextra -pedantic三个选项展开所有的告警信息。学习阶段最好采纳所有警告信息保证规范代码。
#-std=c99指定C语言版本。
tedit: tedit.c
		$(CC) tedit.c -o tedit -Wall -Wextra -pedantic -std=c99