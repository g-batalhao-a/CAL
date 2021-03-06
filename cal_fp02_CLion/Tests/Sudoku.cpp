/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conte�do inicial.
 * Lan�a excep��o IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conte�do actual (s� para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku j� est� completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}


pair<int,int> Sudoku::nextPos(int currentI , int currentJ) {
    if (currentI == 8) {
        return make_pair(0 , currentJ + 1);
    }
    else {
        return make_pair(currentI + 1 ,currentJ);
    }
}
/**
 * Resolve o Sudoku.
 * Retorna indica��o de sucesso ou insucesso (sudoku imposs�vel).
 */
bool Sudoku::solve(int i, int j)
{
    if(isComplete()||j>8||i>8){
        return true;
    }
    pair<int,int> pos;
    if(numbers[i][j]!=0){   //Check if already solved
        if(i==8 && j==8){return true;}
        //go to next square
        pos=nextPos(i,j);
        return solve(pos.first,pos.second);
    }
    // Reduction Case
    for (int n=1 ; n<=9 ; n++){
        // Check if the number can be here
        if (block3x3HasNumber[i/3][j/3][n] || columnHasNumber[j][n] || lineHasNumber[i][n]) {
            continue;
        }
        else {
            checkSquare(i,j,n);
            pos = nextPos(i,j);
            // Check for number success
            if (solve(pos.first , pos.second)) {return true;}
                // Check for number insuccess
            else {
                uncheckSquare(i,j,n);
                continue;
            }
        }
    }
    // None of the numbers fit in this square
    return false;
}


/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}

void Sudoku::checkSquare(int i, int j, int n) {
    if(i<0||i>8||j<0||j>8||n<0||n>9){return;}

    numbers[i][j]=n;
    block3x3HasNumber[i/3][j/3][n]= true;
    columnHasNumber[j][n]=true;
    lineHasNumber[i][n]= true;
    countFilled++;
}

void Sudoku::uncheckSquare(int i, int j, int n) {
    if(i<0||i>8||j<0||j>8||n<0||n>9){return;}

    numbers[i][j]=0;
    block3x3HasNumber[i/3][j/3][n]= false;
    columnHasNumber[j][n]=false;
    lineHasNumber[i][n]= false;
    countFilled--;
}

bool Sudoku::solve() {
    return solve(0,0);
}
