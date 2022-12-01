/****************************************************
 * Sudoku solving using the backtracking algorithm  *
 * Author: DzefersonS                               *
 * Date: 2022/10/29                                 *
 ****************************************************/

/*************************************************************
 * TODO v1:                                                  *
 * 1) Make function to read sudoku puzzle from input file,   * DONE
 *    the name of which is specified by the user; also make  * DONE
 *    sure input file format is valid ("input.txt"). If not, * DONE
 *    ask user to re-input until valid filename is entered.  * DONE
 *                                                           *
 * 2) Make function that checks the validity of a sudoku,    * DONE
 *    use it to check validity of sudoku scanned for file    * DONE
 *    and afterwards, use same function to check if sudoku   * DONE
 *    is valid each recursion. (Has to check each row, each  * DONE
 *    column and current square.)                            * DONE
 *                                                           *
 * 3) In main body, using the two aforementioned functions,  * DONE
 *    get a sudoku and check it's validity; if valid, start  * DONE
 *    solving the sudoku by calling a (yet to be described)  * DONE
 *    recursive function in an if statement, that tells the  * DONE
 *    user whether the sudoku gets solved or not.            * DONE
 *                                                           *
 * 4) Make function that outputs (un)solved sudoku to file   * DONE
 *    named "output.txt".                                    * DONE
 *                                                           *
 * 5) Make function that iterates through entire sudoku,     * DONE
 *    looking for an empty spot (position, the value of      * DONE
 *    which is equal to 0); if found, use pointers to        * DONE
 *    retrieve position and return 1. If not, return 0.      * DONE
 *                                                           *
 * 6) Make recursive function, which uses functions 5 and 2  * DONE
 *    to ensure solution is feasible, and in each square     * DONE
 *    iterate through values 1 and 9. Algorithm outline:     * DONE
 *    6.1) Use function 5) to find empty spot.               * DONE
 *    6.2) Use a for loop, going from 1 to 9, and each       * DONE
 *         iteration check validity of entire sudoku, with   * DONE
 *         value i filling the current square. If valid,     * DONE
 *         call function 6). If 1 through 9 are invalid,     * DONE
 *         then set square value back to 0, and return       * DONE
 *         the function to ensure backtracking.              * DONE
 *                                                           *
 ************************************************************/

/***********************************************************************************************
 * TODO v2:                                                                                    *
 * 1) Make function that prints the initial sudoku table, uses a delay specified by the user,  * DONE
 *    then clear console, print and delay each recursion; this way, visualize the entire       * DONE
 *    algorithm. Finally, once solution is reached, clear and print the final result, telling  * DONE
 *    the user that this is the final result.                                                  * DONE
 * 2) Make main body repeatable, allowing for more than one sudoku to be solved when the       * DONE
 *    program is launched.                                                                     * DONE
 * 3) Ask user if they want the algorithm to be visualized.                                    * DONE
 * 4) If no visualization, print how long solving took.                                        * DONE
 ***********************************************************************************************/

/**********************************************************************
 * Sudoku grid scheme:                                                *
 *                                                                    *
 * ? 0 1 2 3 4 5 6 7 8                                                *
 * 0      |     |     |                                               *
 * 1   1  |  2  |  3  |                                               *
 * 2      |     |     |                                               *
 * -------|-----|-----|                                               *
 * 3      |     |     |                                               *
 * 4   4  |  5  |  6  |                                               *
 * 5      |     |     |                                               *
 * -------|-----|-----|                                               *
 * 6      |     |     |                                               *
 * 7   7  |  8  |  9  |                                               *
 * 8      |     |     |                                               *
 * -------|-----|-----|                                               *
 * Bounds:                                                            *
 * 1 - [0][0] to [2][2]	4 - [3][0] to [5][2]	7 - [6][0] to [8][2]  *
 * 2 - [0][3] to [2][5]	5 - [3][3] to [5][5]    8 - [6][3] to [8][5]  *
 * 3 - [0][6] to [2][8]	6 - [3][6] to [5][8]	9 - [6][6] to [8][8]  *
 **********************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define N 9

int sudoku[N][N];
char command;
int ms_delay;
clock_t execution_time;

bool check_duplicate(int arr[N], int num);                 // Comment status: Line 168
void delay(void);                                          // Comment status: line 182
bool find_empty_position(int *row, int *col);              // Comment status: Line 193
bool line_validation(int arr[N], int pos, int param);      // Comment status: Line 221
void null_vars(int arr[N]);                                // Comment status: Line 260
void output_sudoku(void);                                  // Comment status: Line 271
void print_example(void);                                  // Comment status: Line 295
void print_sudoku(void);                                   // Comment status: Line 321
void read_input(void);                                     // Comment status: Line 344
bool solve_sudoku(int row, int col);                       // Comment status: Line 395
bool square_validation(int arr[N], int row, int col);      // Comment status: Line 445
bool validate_filename(char input[]);                      // Comment status: Line 505
bool validate_file_sudoku(void);                           // Comment status: Line 523
bool validate_progress_sudoku(int row, int col);           // Comment status: Line 591
bool validate_square(int arr[N], int mode);                // Comment status: Line 619
bool validate_square_loop(int arr[N], int pos1, int pos2); // Comment status: Line 673

int main(void)
{
    char check;
    do
    {
        check = 0;
        printf("\e[1;1H\e[2J");
        read_input();
        if (validate_file_sudoku() == false)
        {
            printf("Illegal sudoku. Restart program to try again.\n");
            return 0;
        }
        else
        {
            printf("\e[1;1H\e[2J");
            printf("Successfully read file!\nBefore we start solving the sudoku, would you like to see a visualization of the solving process?\nIf so, type Y. Otherwise, type N, and the time it took to solve the sudoku will be shown instead.\n");
            scanf(" %c", &command);
            if (command == 'Y' || command == 'y')
            {
                printf("Very well! What delay between frames would you like? (Note: Anything below 100ms will look laggy.)\n");
                printf("Enter delay in miliseconds: ");
                scanf("%i", &ms_delay);
                print_sudoku();
            }
            else if (command == 'N' || command == 'n')
            {
                printf("Very well! Beginning solving...\n");
                execution_time = clock();
            }
            if (solve_sudoku(0, 0) == true)
            {
                if (command == 'N' || command == 'n')
                {
                    execution_time = clock() - execution_time;
                    print_sudoku();
                    printf("Final result, sudoku successfully solved.\n");
                    printf("Time taken to solve sudoku: %.5f seconds.\n", ((double)execution_time) / CLOCKS_PER_SEC);
                }
                else
                {
                    print_sudoku();
                    printf("Final result, sudoku successfully solved.\n\n");
                }
                output_sudoku();

                printf("Solve another sudoku? (Y/N):");
                scanf(" %c", &check);
            }
            else
            {
                printf("Illegal sudoku. Restart program to try again.\n");
                return 0;
            }
        }
    } while (check == 'Y' || check == 'y');
}

/****************************************************************
 * check_duplicate: Iterating through all arr elements, checks  *
 *                  if num is already present; if yes, returns  *
 *                  true; otherwise, returns false.             *
 ****************************************************************/

bool check_duplicate(int arr[N], int num)
{
    for (int i = 0; i < N; ++i)
        if (num == arr[i])
            return true;

    return false;
}
/***************************************************************************************
 * delay: This function delays the execution of the program by ms_delay miliseconds.   *
 ***************************************************************************************/
void delay(void)
{
    clock_t start_time = clock();

    while ((clock()) < start_time + ms_delay)
        ;
}

/**********************************************************************
 * find_empty_position: This function iterates through every single   *
 *                       cell in the sudoku table, and upon finding   *
 *                       an empty value, it changes the values of     *
 *                       row and col to indicate the index of said    *
 *                       cell, then returns true. If no empty spots   *
 *                       remain in the table, i.e., the sudoku is     *
 *                       complete - it returns false.                 *
 **********************************************************************/

bool find_empty_position(int *row, int *col)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (sudoku[i][j] == 0)
            {
                *row = i;
                *col = j;
                return true;
            }
        }
    }

    return false;
}

/***********************************************************************************************
 * line_validation: Using the pos parameter to indicate whether to check the row or            *
 *                  the column, the function iterates through the entire line in the           *
 *                  sudoku table. Utilizing the check_duplicate function (for more on          *
 *                  the function, read line 117) to make sure there are no duplicates.         *
 *                  If any are found, the function returns false. Otherwise, it returns true.  *
 ***********************************************************************************************/

bool line_validation(int arr[N], int pos, int param)
{
    for (int i = 0; i < N; ++i)
    {
        if (pos == 1)
        {
            if (sudoku[param][i] == 0)
                continue;
            else if (check_duplicate(arr, sudoku[param][i]) == false)
            {
                arr[i] = sudoku[param][i];
            }
            else
                return false;
        }
        else if (pos == 2)
        {
            if (sudoku[i][param] == 0)
                continue;
            else if (check_duplicate(arr, sudoku[i][param]) == false)
            {
                arr[i] = sudoku[i][param];
            }
            else
                return false;
        }
    }

    return true;
}

/****************************************************
 * null_vars: Using a simple 0 to N loop, sets all  *
 *            arr values to 0.                      *
 ****************************************************/

void null_vars(int arr[N])
{
    for (int i = 0; i < N; ++i)
        arr[i] = 0;
}

/************************************************************************************************
 * output_sudoku: This function opens the file "output.txt" in write mode (therefore,           *
 *                also creating it if it doesn't yet exist), and then outputs the entire        *
 *                sudoku table into the file. Afterwards, the file is closed and the function   *
 *                returns.                                                                      *
 ************************************************************************************************/

void output_sudoku(void)
{
    FILE *of = fopen("output.txt", "w");

    for (int row = 0; row < N; ++row)
    {
        for (int col = 0; col < N; ++col)
        {
            fprintf(of, "%d ", sudoku[row][col]);
        }
        fprintf(of, "\n");
    }

    fclose(of);
    return;
}

/**********************************************************************
 * print_example: The function opens a file called "example.txt",     *
 *                and using a combination of printing text and        *
 *                printing the sudoku table from the example file,    *
 *                gives the user general information on the program   *
 *                itself.                                             *
 **********************************************************************/

void print_example(void)
{
    FILE *of = fopen("example.txt", "r");
    char text[9];
    printf("In the input file, the sudoku must be in this format (example sudoku for reference):\n");
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            printf("%c", fgetc(of));
        }
        fgetc(of);
        printf("\n");
    }
    printf("0 stands for empty spaces.\n");
    fclose(of);
}

/************************************************************************************************
 * print_sudoku: Clears the console and prints out the entire sudoku table in a formatted way.  *
 ************************************************************************************************/

void print_sudoku(void)
{
    printf("\e[1;1H\e[2J");
    printf("_______________________________________\n");
    for (int i = 0; i < N; ++i)
    {
        printf("|");
        if ((i + 1) % 3 == 0)
            printf("\033[4m");
        for (int j = 0; j < N; ++j)
        {
            printf(" %i |", sudoku[i][j]);
            if ((j + 1) % 3 == 0 && j + 1 != 9)
                printf("|");
        }
        printf("\033[0m\n");
    }
}

/**************************************************************************************************
 * read_input: This function handles printing the initial information presented to the user,      *
 *             reading the name of the input file and then reading the initial sudoku from        *
 *             the file presented by the user. First, it calls the print_example function to      *
 *             print all the initial information (for more on the function, read line 234)        *
 *             then utilizes validate_filename (for more on the function, read line 416)          *
 *             to verify that the inputted file format is correct. If it is, then                 *
 *             the function opens the file and checks whether the file exists / is empty;         *
 *             if it is empty, then the loop repeats and the user is asked to re-enter the        *
 *             filename. Otherwise, the file is opened in read only mode, reading each character  *
 *             in the file and using ascii to convert it to integers. Upon finishing, it closes   *
 *             the file.                                                                          *
 **************************************************************************************************/

void read_input(void)
{
    print_example();
    char input[100];
    for (;;)
    {
        printf("Enter file name (input format: \"filename.txt\" (without quotation marks)): ");
        scanf("%s", input);
        if (validate_filename(input) == 1)
        {
            FILE *of = fopen(input, "r");
            if (of == NULL)
            {
                printf("Cannot open file. Try again.\n");
                fclose(of);
            }
            else
                break;
        }
        else
            printf("Invalid filename. Try again.\n");
    }

    FILE *of = fopen(input, "r");

    for (int row = 0; row < N; ++row)
    {
        for (int col = 0; col < N; ++col)
        {
            sudoku[row][col] = (int)(fgetc(of) - 48);
        }
        fgetc(of);
    }

    fclose(of);
}

/********************************************************************************************
 * solve_sudoku: Utilizing the find_empty_position function (for more on the function,      *
 *               read line 132), an empty (0) space in the sudoku table is found (if there  *
 *               is no more empty spots, i.e., find_empty_position returns false, then      *
 *               solve_sudoku returns true and ends the recursion process). Then, using     *
 *               a for loop from 1 to 9, the once empty cell is assigned value i. After     *
 *               assignment, the validate_progress_sudoku function is called (for more      *
 *               on the function, read line 502), which returns either true or false - if   *
 *               it returns true, then (for now) the value is correct. If it is the         *
 *               last column, then the function calls itself (i.e., begins the next         *
 *               recursion) on the next row, otherwise - the next recursion begins in       *
 *               the next column. However, if validate_progress_sudoku returns false,       *
 *               then the loop increments i and re-assigns the new value to the current     *
 *               position in the table. If, ultimately, all values from 1 to 9 are found    *
 *               to be rule-breaking, the function sets the current cell's value to 0 and   *
 *               returns false, going back one step in the recursion process.               *
 ********************************************************************************************/

bool solve_sudoku(int row, int col)
{
    if (find_empty_position(&row, &col) == false)
        return true;

    for (int i = 1; i <= 9; ++i)
    {
        sudoku[row][col] = i;
        if (command == 'Y' || command == 'y')
        {
            delay();
            print_sudoku();
        }
        if (validate_progress_sudoku(row, col) == true)
        {
            if (col == 8)
            {
                if (solve_sudoku(row + 1, 0) == true)
                    return true;
            }
            else
            {
                if (solve_sudoku(row, col + 1) == true)
                    return true;
            }
        }
    }

    sudoku[row][col] = 0;
    return false;
}

/*******************************************************************************************
 * square_validation: This is the function used to validate if a square is valid.          *
 *                    By checking which square the current element (using it's             *
 *                    row & column indexes) is in, it then calls the validate_square       *
 *                    function (for more on the function, read line 530). If said          *
 *                    function returns false, then square_validation also returns false,   *
 *                    indicating that the square is invalid. Otherwise, it returns true.   *
 *******************************************************************************************/

bool square_validation(int arr[N], int row, int col)
{
    if (row <= 2 && col <= 2)
    {
        if (validate_square(arr, 1) == false)
            return false;
    }
    else if (row <= 2 && col >= 3 && col <= 5)
    {
        if (validate_square(arr, 2) == false)
            return false;
    }
    else if (row <= 2 && col >= 6 && col <= 8)
    {
        if (validate_square(arr, 3) == false)
            return false;
    }
    else if (row >= 3 && row <= 5 && col <= 2)
    {
        if (validate_square(arr, 4) == false)
            return false;
    }
    else if (row >= 3 && row <= 5 && col >= 3 && col <= 5)
    {
        if (validate_square(arr, 5) == false)
            return false;
    }
    else if (row >= 3 && row <= 5 && col >= 6 && col <= 8)
    {
        if (validate_square(arr, 6) == false)
            return false;
    }
    else if (row >= 6 && row <= 8 && col <= 2)
    {
        if (validate_square(arr, 7) == false)
            return false;
    }
    else if (row >= 6 && row <= 8 && col >= 3 && col <= 5)
    {
        if (validate_square(arr, 8) == false)
            return false;
    }
    else
    {
        if (validate_square(arr, 9) == false)
            return false;
    }

    return true;
}

/************************************************************
 * validate_filename: This function makes sure that the     *
 *                    user-inputted filename ends in .txt,  *
 *                    as the program requests. If it does,  *
 *                    true is returned; if not, false.      *
 ************************************************************/

bool validate_filename(char input[])
{
    int filename_len = strlen(input);
    char validation[5];

    for (int i = 0; i < 4; ++i)
        validation[3 - i] = input[filename_len - i - 1];

    return strcmp(validation, ".txt") == 0 ? true : false;
}

/**********************************************************************************************
 * validate_file_sudoku: This function's purpose is to validate that the sudoku read from     *
 *                       the user file is, in fact, a valid sudoku(i.e., it doesn't break     *
 *                       any of the sudoku rules). Then, utilizing the null_vars function     *
 *                       (for more on the function, read line 199), all values of the array   *
 *                       arr are set to 0. Then, looping through each element of the sudoku   *
 *                       table, all empty (0) values are ignored, whereas actual values are   *
 *                       used in a check_duplicate function (which, as the name implies, is   *
 *                       used to look for duplicates in the array arr) (for more on the       *
 *                       function, read line 117). If no duplicates are found, the value is   *
 *                       added to the array. If none of the rows have a duplicate, then       *
 *                       every column is checked using the same method. If rows and columns   *
 *                       are good, then utilizing the square_validation function (for more    *
 *                       on the function, read line 356), all 9 squares of the sudoku are     *
 *                       checked. If all squares are legal, the function returns true. If     *
 *                       even one illegal row/column/square is detected, then false is        *
 *                       returned.                                                            *
 **********************************************************************************************/

bool validate_file_sudoku(void)
{
    int arr[N];
    null_vars(arr);
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            if (sudoku[row][col] == 0)
                continue;
            else if (check_duplicate(arr, sudoku[row][col]) == false)
            {
                arr[col] = sudoku[row][col];
            }
            else
                return false;
        }
        null_vars(arr);
    }
    null_vars(arr);

    for (int col = 0; col < N; col++)
    {
        for (int row = 0; row < N; row++)
        {
            if (sudoku[row][col] == 0)
                continue;
            else if (check_duplicate(arr, sudoku[row][col]) == false)
            {
                arr[col] = sudoku[row][col];
            }
            else
                return false;
        }
        null_vars(arr);
    }
    for (int i = 2; i <= 8; i += 3)
    {
        for (int j = 2; j <= 8; j += 3)
        {
            if (square_validation(arr, i, j) == false)
                return false;
            else
                null_vars(arr);
        }
    }
    return true;
}

/**********************************************************************************************
 * validate_progress_sudoku: This function is used to verify that, during the solving         *
 *                           of the sudoku, the value in the current cell of the sudoku       *
 *                           table doesn't break any rules. To do this, it utilizes several   *
 *                           functions - null_vars, line_validation and square_validation     *
 *                           (for more on all aforementioned functions, read lines 199, 160   *
 *                           and 356). Using line validation twice (once to check the         *
 *                           row, once to check the column), and then the 3x3 square that     *
 *                           the current cell is in is also checked. If all functions return  *
 *                           true (i.e., no rules are broken) - the function returns true.    *
 *                           Otherwise, it returns false.                                     *
 **********************************************************************************************/

bool validate_progress_sudoku(int row, int col)
{
    int arr[N];
    null_vars(arr);
    if (line_validation(arr, 1, row) == false)
        return false;
    null_vars(arr);
    if (line_validation(arr, 2, col) == false)
        return false;
    null_vars(arr);
    if (square_validation(arr, row, col) == false)
        return false;
    return true;
}

/**************************************************************************************
 * validate_square: This function, utilizing the mode parameter, uses a series        *
 *                  of switch cases, in which the validate_square_loop function       *
 *                  is called (for more on the function, read line 584). The reason   *
 *                  for this approach is to allow for the aforementioned function     *
 *                  to properly loop through each square.                             *
 **************************************************************************************/

bool validate_square(int arr[N], int mode)
{
    switch (mode)
    {
    case 1:
        if (validate_square_loop(arr, 0, 0) == false)
        {
            return false;
        }
        break;
    case 2:
        if (validate_square_loop(arr, 0, 3) == false)
            return false;
        break;
    case 3:
        if (validate_square_loop(arr, 0, 6) == false)
            return false;
        break;
    case 4:
        if (validate_square_loop(arr, 3, 0) == false)
            return false;
        break;
    case 5:
        if (validate_square_loop(arr, 3, 3) == false)
            return false;
        break;
    case 6:
        if (validate_square_loop(arr, 3, 6) == false)
            return false;
        break;
    case 7:
        if (validate_square_loop(arr, 6, 0) == false)
            return false;
        break;
    case 8:
        if (validate_square_loop(arr, 6, 3) == false)
            return false;
        break;
    case 9:
        if (validate_square_loop(arr, 6, 6) == false)
            return false;
        break;
    }
    return true;
}

/*********************************************************************************
 * validate_square_loop: Utilizing the pos1 and pos2 parameters + the            *
 *                       check_duplicate function (for more on the function,     *
 *                       read line 117), the function iterates through every     *
 *                       digit in the 3x3 square and makes sure that there are   *
 *                       no duplicates. If a single duplicate is found, the      *
 *                       function returns false. Otherwise, it returns true.     *
 *********************************************************************************/

bool validate_square_loop(int arr[N], int pos1, int pos2)
{
    int count = 0;
    for (int i = pos1; i <= pos1 + 2; ++i)
    {
        for (int j = pos2; j <= pos2 + 2; ++j)
        {
            if (sudoku[i][j] == 0)
                continue;
            else if (check_duplicate(arr, sudoku[i][j]) == false)
            {
                arr[count] = sudoku[i][j];
                count++;
            }
            else
                return false;
        }
    }
    return true;
}