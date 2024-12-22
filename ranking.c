#include <stdio.h>

int check_highscore(char *filename, int score)
{
    FILE *fp;
	int highscore;

	fp = fopen(filename, "r");
	if (!fp)
		return (-1);
	if (fscanf(fp, "%d", &highscore) == 1)
	{
		if (score > highscore)
		{
			fclose(fp);
			fp = fopen(filename, "w");
			fprintf(fp, "%d", score);
		}
		fclose(fp);
		return (highscore);
	}
	fclose(fp);
	return (-1);
}
