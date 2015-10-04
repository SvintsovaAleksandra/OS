#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char p_data[15]; // � ��� ������ ����� �������� ������, ������� ����� �������� � �����
	char c_data[15];
	char p_filename[32] =  "parent_process_id"; // � ��� ������ ����� �������� �������� ����������� ���������� ������
	char c_filename[31] = "child_process_id";

	int pid = fork(); // �������� ������������ �������

	if (pid == -1) { printf("Error, child process is not created\n"); } // ���� fork() ���������� ������

	if (pid == 0) // ��� ��������� ��������
	{
		snprintf(c_data, 15, "%d", getpid()); //���������� pid ��������� �������� � ������
		strcat(c_filename, c_data); // �������� ��� �����, ������������ �������� ���������, ���������� pid
		snprintf(c_data, 15, "%d", getppid()); //���������� ppid ��������
		FILE * c_file = fopen(c_filename, "wb");
		fwrite(c_data, strlen(c_data), 1, c_file);
		fclose(c_file);
	}

	else // ��� ������������� �������� (���� fork() ������ pid ���������)
	{
        
		wait();
		snprintf(p_data, 15, "%d", getpid()); // ���������� � ������ pid ������������� ��������
		snprintf(c_data, 15, "%d", pid); // ���������� � ������ pid ��������� ��������
		strcat(p_filename, p_data); // �������� ��� �����, ������������ ������������ ���������

		strcat(p_data, "\n");
		FILE * p_file = fopen (p_filename, "wb");
		fwrite (p_data, strlen(p_data), 1, p_file);
		fwrite (c_data, strlen(c_data), 1, p_file);
		fclose(p_file);
	}

	return 0;
}
