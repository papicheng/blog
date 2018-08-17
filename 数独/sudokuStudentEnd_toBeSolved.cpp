/*
*       数独学生端程序
*           左妍
*    计算机科学与技术系
*         2017/6/12
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW 9
#define COL 9
#define CORRECT 0
#define WRONG -1 
#define MAXNUM 1000 /*数独游戏个数*/  
int checkSudoku(const char a[][COL]) {
	int i, j, x, y;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			for (x = 0; x < COL; x++)
				if (a[i][x] == a[i][j] && x != j)
					return WRONG;

			for (x = 0; x < ROW; x++)
				if (a[x][j] == a[i][j] && x != i)
					return WRONG;

			for (x = i / 3 * 3; x < i / 3 * 3 + 3; x++)
				for (y = j / 3 * 3; y < j / 3 * 3 + 3; y++)
					if (a[x][y] == a[i][j] && (x != i && y != j))
						return WRONG;
		}
	}
	return CORRECT;
}
void printSudoku(const char a[][COL]) {
	int i, j;
	printf("\n ┌───——─┬───——─┬——────┐\n");
	for (i = 0; i < ROW; i++) {
		if (i != 0 && i % 3 == 0) printf(" ├────——┼——────┼─——───┤\n");
		printf(" │");
		for (j = 0; j < COL; j++) {
			if (j != 0 && j % 3 == 0) printf("  │");
			if (a[i][j])
				printf(" %c", a[i][j]);
			else printf("  ");
		}
		printf("  │\n");
	}
	printf(" └─——───┴───——─┴——────┘\n");
}
void readFromFile(char a[][COL], const char filename[]) {
	// To Be Solved
	// 从文件filename中读取到的数独初盘存储到数组a[][COL]中
	int i = 0, j = 0, num = 81;
	char c = 0;
	FILE *fp = fopen(filename, "r");//读文件 

	while (num)
	{
		fscanf(fp, "%c", &c);
		if (c == 10 || c == 32)
		{
			continue;
		}
		a[i][j] = c;
		num--;
		j++;
		if (j >= 9)
		{
			j = 0;
			i++;
		}
	}
	fclose(fp);
}

int Solve(char arr[ROW][COL], int row, int col)
{
	int i, j;
	char n = 48;
	int flag_next = 0;

	int next_row = 0, next_col = 0;

	while (1) {
	next_num:
		++n;
		if (n > 57) break;

		// 判断行重复
		for (j = 0; j < ROW; j++) {
			if (arr[row][j] == n) {
				goto next_num;
			}
		}

		// 判断列重复
		for (i = 0; i < COL; i++) {
			if (arr[i][col] == n) {
				goto next_num;
			}
		}

		/* 判断所在小九宫格重复*/
		int x = (row / 3) * 3;
		int y = (col / 3) * 3;
		for (i = x; i < x + 3; i++) {
			for (j = y; j < y + 3; j++) {
				if (arr[i][j] == n) {
					goto next_num;
				}
			}
		}

		//该单元可以填充
		arr[row][col] = n;
		//如果9宫格已填满，完成，这里不考虑有多解的情况
		flag_next = 0;
		for (i = 0; i < ROW; i++)
			for (j = 0; j < COL; j++)
				if (arr[i][j] == '0') {
					next_row = i;
					next_col = j;
					flag_next = 1;
					break;
				}
		if (!flag_next)
		{
			return 1;
		}
		//否则继续填下一个未填充的格子
		if (!Solve(arr, next_row, next_col)) {
			//数独填写完毕就不重写以前留下的足迹
			arr[row][col] = 48;
			continue;//一直到本次循环完毕，直接跳出循环后，执行最后的 return 0;
		}
		else
			return 1;//成功的标志，一路返回
	}
	/*flag_next = 0;
		for (i = 0; i < ROW; i++)
			for (j = 0; j < COL; j++)
				if (arr[i][j] == '0') {
					next_row = i;
					next_col = j;
					flag_next = 1;
					break;
				}
    if(!flag_next)
		return 0;
	else
		Solve(arr, next_row, next_col);*/
	return 0;
}
void solveSudoku(const char a[][COL], char b[][COL]) {
	// To Be Solved 
	// 参数const char a[][COL]表示初盘二维数组；
	// 参数char b[][COL]表示解的二维数组。 
	int row = 0, col = 0;
	int flag=0;
	for (int i = 0;i < ROW;i++) {
		for (int j = 0;j < COL;j++)
		{
			b[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			if (b[i][j] == '0') {
				row = i;
				col = j;
				flag=1;
				break;
			}
	Solve(b, row, col);
			/*
	while(flag)
	{
		Solve(b, row, col);
		flag=0;
		for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			if (b[i][j] == '0') {
				row = i;
				col = j;
				flag=1;
				break;
			}
		}
	}*/
}
int main() {
	char starting_grid[ROW][COL] = { 0 };
	char result[ROW][COL] = { 0 };
	char filename[50];
	int rr = 0;
	double time_from, time_to, time_sum = 0;
	int i = 0;
	for (i = 873; i < MAXNUM; i++) {
		sprintf(filename, "sudoku\\%04d.txt", i);
		readFromFile(starting_grid, filename);
		printf("\n\n             *%4d  *", i);
		printSudoku(starting_grid);
		time_from = clock();
		solveSudoku(starting_grid, result);
		time_to = clock();
		time_sum += time_to - time_from;
		printSudoku(result);
		rr = checkSudoku(result);
		if (rr == WRONG) {
			printf("Something goes wrong...\n");
			return WRONG;
		}
		else printf("            Correct!!!\n");
		printf("  ==============================");
	}
	printf("\n Congretulations! ToTal Time:%fs\n", time_sum / CLOCKS_PER_SEC);
	return 0;
}
