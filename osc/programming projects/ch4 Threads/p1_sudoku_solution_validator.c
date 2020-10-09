#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int sudoku[9][9] = {
    {5, 3, 4, 6, 7, 8, 9, 1, 2},
    {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7},
    {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1},
    {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4},
    {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}};
;
int rows[9];
int cols[9];
int squares[9];

typedef struct
{
    int start_row;
    int start_col;
    int end_row;
    int end_col;
} parameters;

void *runner(void *param);
int main(void)
{
    pthread_t pid[30];
    // create and run all row threads
    for (int i = 0; i < 9; i++)
    {
        pthread_attr_t attr;

        parameters *data = malloc(sizeof(parameters));

        data->start_row = i;
        data->end_row = i;
        data->start_col = 0;
        data->end_col = 8;
        pthread_attr_init(&attr);
        pthread_create(&pid[i], &attr, runner, data);
        pthread_join(pid[i], NULL);
    }
    // create and run all col threads
    for (int i = 0; i < 9; i++)
    {
        pthread_t pid;
        pthread_attr_t attr;

        parameters *data = malloc(sizeof(parameters));

        data->start_row = 0;
        data->end_row = 8;
        data->start_col = i;
        data->end_col = i;
        pthread_attr_init(&attr);
        pthread_create(&pid, &attr, runner, data);

        pthread_join(pid, NULL);
    }
    // create and run all square threads
    for (int i = 0; i < 9; i++)
    {
        pthread_t pid;
        pthread_attr_t attr;

        parameters *data = malloc(sizeof(parameters));

        data->start_row = (i / 3) * 3;
        data->end_row = (i / 3) * 3 + 2;
        data->start_col = (i % 3) * 3;
        data->end_col = (i % 3) * 3 + 2;
        pthread_attr_init(&attr);
        pthread_create(&pid, &attr, runner, data);

        pthread_join(pid, NULL);
    }

    // check and print result
    for (int i = 0; i < 9; i++)
    {
        if (rows[i] == 1)
        {
            printf("row %d is false", i);
            return 0;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if (cols[i] == 1)
        {
            printf("col %d is false", i);
            return 0;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if (squares[i] == 1)
        {
            printf("square %d is false", i);
            return 0;
        }
    }
    printf("true");
    return 0;
}

void *runner(void *param)
{
    parameters *params = param;
    int start_row = params->start_row, start_col = params->start_col, end_row = params->end_row, end_col = params->end_col;

    int hash[10];

    for (int i = start_row; i <= end_row; i++)
    {
        for (int j = start_col; j <= end_col; j++)
        {
            if (hash[sudoku[i][j]] == 1)
            {
                // mark as fail and  update result array
                if (start_row == end_row)
                {
                    rows[start_row] = 1;
                }
                else if (start_col == end_col)
                {
                    cols[start_col] = 1;
                }
                else
                {
                    cols[start_row + start_col / 3] = 1;
                }
                pthread_exit(0);
            }
            else
            {
                hash[sudoku[i][j]] = 1;
            }
        }
    }

    pthread_exit(0);
}
