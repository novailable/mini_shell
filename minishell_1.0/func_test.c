
#include "mini_shell.h"

// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
// printf, malloc, free, write, access, open, read,
// close, fork, wait, waitpid, wait3, wait4, signal,
// sigaction, sigemptyset, sigaddset, kill, exit,
// getcwd, chdir, stat, lstat, fstat, unlink, execve,
// dup, dup2, pipe, opendir, readdir, closedir,
// strerror, perror, isatty, ttyname, ttyslot, ioctl,
// getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
// tgetnum, tgetstr, tgoto, tputs
char *get_timestamp() 
{
    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strcspn(timestamp, "\n")] = '\0'; // Remove newline
    return strdup(timestamp);
}

void	signal_handler()
{
	printf("pressed : %d, time : %s\n", SIGINT, get_timestamp());
	exit(0);
	
}

int main()
{
	char    *input;
	struct sigaction	sa;

	while (1)
	{
		input = readline("mini-shell : ");
		add_history(input);
		HIST_ENTRY *entry = history_get(history_length);
		if (entry)
		{
			entry->timestamp = get_timestamp();
			entry->data = "YOUGODOWNJUSTLIKEHOLYMARYMARYONAMARYONACROSSYOUJUSTNOTANOTHERBLOODMARYYOUGODOWNJUSTLIKEHOLYMARYMARYONAMARYONACROSSYOURBEAUTYNEVERGONNASCAREMEMARYONAMARYONACROSS\n";
		}
		if (strcmp("a", input) == 0)
		{
			rl_on_new_line();
			rl_replace_line("tst", 0);
			rl_redisplay();
		}
		if (strcmp("h", input) == 0)
		{
			HIST_ENTRY  **h_data = history_list();
			for (int i = 0; h_data[i]; i++)
				printf("%s\n%s\n%s\n\n",h_data[i]->line, h_data[i]->timestamp, (char *)h_data[i]->data);
		}
		if (strcmp("b", input) == 0)
		{
			rl_replace_line("tst", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		if (strcmp("d", input) == 0)
		{
			rl_replace_line("tst", 0);
			rl_redisplay();
		}
		if (strcmp("s", input) == 0)
		{
			sa.sa_handler = signal_handler;
            sigemptyset(&sa.sa_mask);
            sa.sa_flags = 0;
            if (sigaction(SIGINT, &sa, NULL) == -1)
            {
                perror("sigaction");
                return 1;
            }
            while (1)
            {
				printf("Running... Press Ctrl+C to interrupt.\n");
                sleep(1); // Simulate some work
            }
		}
		if (strcmp("c", input) == 0)
		{
			struct stat file_info;
    
			//"txt" with the name of an actual file or directory on your system
			if (stat("func_test.c", &file_info) == -1) {
				perror("stat");
				return 1;
			}

			// Printing the values of the struct stat members
			printf("Device ID (st_dev): %lu\n", (unsigned long)file_info.st_dev);  // Device ID
			printf("Inode number (st_ino): %lu\n", (unsigned long)file_info.st_ino); // Inode number
			printf("File type and permissions (st_mode): %o\n", (unsigned int)file_info.st_mode); // File type and permissions
			printf("Number of hard links (st_nlink): %lu\n", (unsigned long)file_info.st_nlink); // Number of hard links
			printf("User ID of the file owner (st_uid): %u\n", file_info.st_uid); // User ID of file owner
			printf("Group ID of the file owner (st_gid): %u\n", file_info.st_gid); // Group ID of file owner
			printf("Device ID (st_rdev): %lu\n", (unsigned long)file_info.st_rdev); // Device ID (if special file)
			printf("Total file size (st_size): %ld bytes\n", (long)file_info.st_size); // File size in bytes
			printf("Block size (st_blksize): %ld\n", (long)file_info.st_blksize); // Block size for I/O
			printf("Number of blocks (st_blocks): %ld\n", (long)file_info.st_blocks); // Number of 512-byte blocks allocated
			printf("Time of last access (st_atime): %s", ctime(&file_info.st_atime)); // Time of last access
			printf("Time of last modification (st_mtime): %s", ctime(&file_info.st_mtime)); // Time of last modification
			printf("Time of last status change (st_ctime): %s", ctime(&file_info.st_ctime)); // Time of last status change
		}
	}


	

}
