#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char p_data[15]; // в эти строки будут записаны данные, которые нужно записать в файлы
	char c_data[15];
	char p_filename[32] =  "parent_process_id"; // в эти строки будут записаны названия создаваемых процессами файлов
	char c_filename[31] = "child_process_id";

	int pid = fork(); // копируем родительский процесс

	if (pid == -1) { printf("Error, child process is not created\n"); } // если fork() возвращает ошибку

	if (pid == 0) // для дочернего процесса
	{
		snprintf(c_data, 15, "%d", getpid()); //записываем pid дочернего процесса в строку
		strcat(c_filename, c_data); // получаем имя файла, создаваемого дочерним процессом, содержащее pid
		snprintf(c_data, 15, "%d", getppid()); //записываем ppid процесса
		FILE * c_file = fopen(c_filename, "wb");
		fwrite(c_data, strlen(c_data), 1, c_file);
		fclose(c_file);
	}

	else // для родительского процесса (если fork() вернул pid дочернего)
	{
        
		wait();
		snprintf(p_data, 15, "%d", getpid()); // записываем в строку pid родительского процесса
		snprintf(c_data, 15, "%d", pid); // записываем в строку pid дочернего процесса
		strcat(p_filename, p_data); // получаем имя файла, создаваемого родительским процессом

		strcat(p_data, "\n");
		FILE * p_file = fopen (p_filename, "wb");
		fwrite (p_data, strlen(p_data), 1, p_file);
		fwrite (c_data, strlen(c_data), 1, p_file);
		fclose(p_file);
	}

	return 0;
}
