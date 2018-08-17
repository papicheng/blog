/*
 *       �������ɳ���
 *           ���� 
 *    �������ѧ�뼼��ϵ 
 *         2017/6/12 
 */
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#define ROW 9
#define COL 9
#define CORRECT 0
#define WRONG -1 
#define MAXNUM 1000   /*��������*/ 
#define SEED 20171212 /*�������������*/ 
unsigned int seed = SEED;
int Digit(char a[][COL], int i, int j){	/*�ݹ��������Ԫ��*/
	if(i < ROW && j < COL){	
		int x,y,k;
		char check[COL+1]={CORRECT};/*�����ų��Ѿ�ʹ�ù��ĵ�����*/
		for(x = 0 ; x < i ; x++)
			check[a[x][j]] = WRONG;
		for(x = 0 ; x < j ; x++)
			check[a[i][x]] = WRONG;
		for(x = i/3*3 ; x <= i; x++){
			if(x == i)
				for(y = j/3*3 ; y < j; y++)
					check[a[x][y]] = WRONG;
			else
				for(y = j/3*3 ; y < j/3*3 + 3; y++)
					check[a[x][y]] = WRONG;		
		}
		int flag = 0;
		for(k = 1; k <= COL && flag == 0 ; k++){/*��check�����в��Ұ�ȫ������*/ 
			if(check[k] == CORRECT){
				flag = 1;
				a[i][j] = k;
				if(j == COL-1 && i != ROW-1){
					if(Digit(a,i+1,0) == CORRECT) return CORRECT;
					else flag = 0;
				} 	
				else if(j != COL-1){
					if(Digit(a,i,j+1) == CORRECT) return CORRECT;
					else flag = 0;	
				}  
			}	 	
		}
		if( flag == 0 ){
			a[i][j] = 0;
			return WRONG;
		}	 	
	}
	return CORRECT;			
}
void randomFirstRow(char a0[], int n){/*������ɵ�һ��*/
	int i,j;
	srand(seed++);
	for( i = 0 ; i < n ; i++){
		a0[i] = rand()%9 + 1;
		j = 0 ; 
		while(j < i){
			if(a0[i] == a0[j]){
				a0[i] = rand()%9 + 1;
				j = 0;	
			}
			else j++;
		}				
	}
}
void createSudoku(char a[][COL]){	/*��������*/
	randomFirstRow(a[0],COL);
	Digit(a,1,0);	
}
void createStartinggrid(const char a[][COL], char b[][COL], int numDigits){/*������ɳ���*/
	int i,j,k;
	srand(seed ++);
	for( i = 0; i < ROW ; i ++)
		for( j = 0; j < COL ; j++)
			b[i][j] = a[i][j];
	
	char c[numDigits][2];
	int m,flag = 0;
	
	for( i = 0; i < numDigits ; i++){
		j = rand()%9;
		k = rand()%9;
		
		flag = 0;
		for(m = 0; m < i ; m++)
			if( j == c[m][0] && k == c[m][1])
				flag = 1;		
		
		if(flag == 0){
			b[j][k] = 0;
			c[i][0] = j;
			c[i][1] = k;
		}
		else
			i--;	
	}
}
int checkSudoku(const char a[][COL]){/*��麯��*/
	int i,j,x,y;
	for( i = 0; i < ROW ; i++){
		for(j = 0 ; j < COL ; j++){		
			for(x = 0 ; x < COL ; x++)
				if(a[i][x] == a[i][j] && x != j ) 
					return WRONG;
			
			for(x = 0 ; x < ROW ; x++)
				if(a[x][j] == a[i][j] && x != i ) 
					return WRONG;
		
			for(x = i/3*3 ; x < i/3*3+3 ; x ++)
				for(y = j/3*3 ; y < j/3*3+3 ; y++)
			 		if(a[x][y] == a[i][j] && (x != i && y != j)) 
					 	return WRONG;	 	
		}	
	}
	return CORRECT;
}

void printToFile(const char a[][COL], const char filename[]){/*��ӡ�������鵽�ļ�*/
	FILE * fp;
	int i,j;
	fp = fopen(filename,"w");
	for( i = 0 ; i < ROW ; i++){
		for( j = 0 ; j < COL ; j++)
			fprintf(fp , "%d ", a[i][j]);
		fprintf(fp , "\n");
	}
	fclose(fp);	
}
void createSudokuToFile(void){/*�����������̵��ļ���*/
	char sudoku[ROW][COL]={0};
	char starting_grid[ROW][COL]={0};
	char filename[50];
	int i;
	mkdir("sudoku");
	for( i = 0; i < MAXNUM ; i++){
		createSudoku(sudoku);
		createStartinggrid(sudoku,starting_grid,i%81+1);
		
		sprintf(filename,"sudoku\\%04d.txt",i);
		printToFile(starting_grid,filename);
	}
}
int main(){
	createSudokuToFile();	
}
