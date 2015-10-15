#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>

void *print_func (void * arg)
{
    char buffer;
    fread(&buffer, 1, 1, arg);
    while (!feof(arg))
    {
        printw("%c", buffer);
        usleep(10000);
        fread(&buffer, 1, 1, arg);
        refresh();
    }
    refresh();
    pthread_exit(NULL);
}

int main()
{
    initscr();
    printw("Enter the path to the file \n"); /*путь до файла, мои превосходные знания английского*/
    char filename[80];
    getstr(filename);
    FILE * file = fopen(filename, "r");
    if (file==NULL)
    {
        printw("Ошибка при открытии файла");
        return 1;
    }
    else printw("C - start/continue\nS - pause\nQ - quit \n\n");
         /*C - начать/продолжить работу  S - поставить программу на паузу  Q - выход из программы*/
    pthread_t print;
    int buf = getch();
    printw("\n");
    bool work = false;
    while (1)
    {
        if (work == false && (buf=='c' || buf=='C'))
        {
            pthread_create(&print, NULL, print_func, file);
            work = true;
        }
        if (buf=='s' || buf=='S')
        {
            pthread_cancel(print);
            work = false;
        }
        if (buf=='q' || buf=='Q')
        {
            pthread_cancel(print);
            break;
        }
        buf = getch();
        printw("\n");
    }
    pthread_join(print, NULL);
    refresh();
    system("pause");
    endwin();
    return 0;
}
