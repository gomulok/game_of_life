#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

void printww(char **pr, int sy);
void str3cp(char **fm, char **tm, int sy, int sx);

int main()
{
	initscr();
	int sy, sx;
	getmaxyx(stdscr, sy, sx);
	printw("Hello its game of life in terminal!\n");
	printw("your terminal size = y = %d and x = %d\n", sy, sx);
	printw("To move use:\n   w\n a s d\n");
	printw("To quit from the terminal press \'q\'\n");
	printw("To change the state of your cell press \'e\'\n");
	printw("To get next state press ' ' (space)\n");
	printw("To clear press \'c\'\n");
	printw("Press any key to continue ... ");
	noecho();
	getch();
	move(0, 0);
	clear();
	refresh();
	int x = 0, y = 0;
	char c, count = 0;
	char p = 0;
	char **all = (char **)malloc(((sx + 1) * sy) * sizeof(char *));
	char **all2 = (char **)malloc(((sx + 1) * sy) * sizeof(char *));
	for (int i = 0; i < sy; i++)
	{
		*(all + i) = (char *)malloc((sx + 1) * sizeof(char));
		*(all2 + i) = (char *)malloc((sx + 1) * sizeof(char));
	}
	for (int i = 0; i < sy; i++)
	{
		for (int j = 0; j < sx; j++)
		{
			all[i][j] = ' ';
			all2[i][j] = ' ';
		}
		all[i][sx] = '\0';
		all2[i][sx] = '\0';
	}
	while ((c = getch()) != 'q')
	{
		if (c == 'w' && y != 0)
			move(--y, x);
		else if (c == 's' && y != sy - 1)
			move(++y, x);
		else if (c == 'a' && x != 0)
			move(y, --x);
		else if (c == 'd' && x != sx - 1)
			move(y, ++x);
		else if (c == 'c')
			for (int i = 0; i < sy; i++)
			{
				for (int j = 0; j < sx; j++)
				{
					all[i][j] = ' ';
					all2[i][j] = ' ';
				}
				all[i][sx] = '\0';
				all2[i][sx] = '\0';
			}
		else if (c == 'e')
		{
			p = 0;
			all[y][x] = all[y][x] == ' '? '#': ' ';
			all2[y][x] = all2[y][x] == ' '? '#': ' ';
		}
		else if (c == ' ')
		{
			for (int i = 0; i < sy; i++)
				for (int j = 0; j < sx; j++)
				{
					count = 0;
					if (i != 0 && j != 0)
						if (all[i - 1][j - 1] == '#')
							count++;
					if (i != 0)
						if (all[i - 1][j] == '#')
							count++;
					if (i != 0 && j != sx - 1)
						if (all[i - 1][j + 1] == '#')
							count++;
					if (j != 0)
						if (all[i][j - 1] == '#')
							count++;
					if (j != sx - 1)
						if (all[i][j + 1] == '#')
							count++;
					if (i != sy - 1 && j != 0)
						if (all[i + 1][j - 1] == '#')
							count++;
					if (i != sy - 1)
						if (all[i + 1][j] == '#')
							count++;
					if (i != sy - 1 && j != sx - 1)
						if (all[i + 1][j + 1] == '#')
							count++;
					if (count > 3 || count < 2)
						all2[i][j] = ' ';
					if (count == 3)
						all2[i][j] = '#';
					count = 0;
					p = 1;
				}
			str3cp(all, all2, sy, sx);
		}
		else
			continue;
		clear();
		move(0, 0);
		printww(all, sy);
		refresh();
		move(y, x);
	}
	endwin();
	for (int i = 0; i < sy; i++)
	{
		free(all[i]);
		free(all2[i]);
	}
	free(all);
	free(all2);
	return 0;
}
void printww(char **pr, int sy)
{
	for (int i = 0; i < sy; i++)
		printw("%s", pr[i]);
}
void str3cp(char **fm, char **tm, int sy, int sx)
{
	for (int i = 0; i < sy; i++)
		for (int j = 0; j < sx; j++)
			fm[i][j] = tm[i][j];
}

