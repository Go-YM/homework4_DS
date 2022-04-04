#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//<stdio.h>, <stdlib.h>, <time.h>을 컴파일 전에 소스에 확장하도록 지시

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

//이 프로그렘의 메인함수
int main()
{
    int row, col;
    char command;
    int count=0;        //행렬 초기화 전 다른 연산 하지 못하도록 하는 정수형 변수 count 선언

    printf("[----- [???????]  [2019038003] -----]\n");

    srand(time(NULL));  //랜덤 난수를 선언하도록 지시

    //row와 col을 사용자로부터 입력 받음
    printf("Input row and col : ");
    scanf("%d %d", &row, &col);

    int** matrix_a = create_matrix(row, col);   //행렬 A 선언 후 생성
    if (matrix_a == NULL) {return -1;}

    int** matrix_b = create_matrix(row, col);   //행렬 B 선언 후 생성
    if (matrix_b == NULL) {return -1;}

    int** matrix_a_t = create_matrix(col, row); //행렬 a_t선언 후 생성

    printf("Matrix Created.\n");

    //q 또는 Q 입력 받기 전까지 무한 루프 하는 do-while 문
    do{//메뉴 출력
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        //사용자로부터 command를 입력 받음
        printf("Command = ");
        scanf(" %c", &command);

        switch(command) 
        {
            case 'z': case 'Z': //command가 z 또는 Z일때
                if(count == 0)  //Initialize Matrix부터 실행 하도록 count 설정
                {
                    printf("Matrix Initialized\n");
                    fill_data(matrix_a, row, col);
                    fill_data(matrix_b, row, col);
                    count++;    //Initialize Matrix 실행 전에 다른 함수 실행 못하도록 count++
                }

                break;

            case 'p': case 'P': //command가 p 또는 P일때
                if(count != 0)  //Initialize Matrix 먼저 실행 했을 경우
                {
                    printf("Print matrix\n");
                    printf("matrix_a\n");
                    print_matrix(matrix_a, row, col);
                    printf("matrix_b\n");
                    print_matrix(matrix_b, row, col);
                }

                else            //Initialize Matrix 먼저 실행 되지 않았을때
                {
                    printf("Please Matrix Initialize first!\n");
                }

                break;

            case 'a': case 'A': //command가 a 또는 A일때
                if(count != 0)  //Initialize Matrix 먼저 실행 했을 경우
                {
                    printf("Add two matrices\n");
                    addition_matrix(matrix_a, matrix_b, row, col);  
                }

                else            //Initialize Matrix 먼저 실행 되지 않았을때
                {
                    printf("Please Matrix Initialize first!\n");
                }

                break;

            case 's': case 'S': //command가 s 또는 S일때
                if(count != 0)  //Initialize Matrix 먼저 실행 했을 경우
                {
                    printf("Subtract two matrices \n");
                    subtraction_matrix(matrix_a, matrix_b, row, col);
                }

                else            //Initialize Matrix 먼저 실행 되지 않았을때
                {
                    printf("Please Matrix Initialize first!\n");
                }

                break;

            case 't': case 'T': //command가 t 또는 T일때
                if(count != 0)  //Initialize Matrix 먼저 실행 했을 경우
                {
                    printf("Transpose matrix_a \n");
                    printf("matrix_a_t\n");
                    transpose_matrix(matrix_a, matrix_a_t, row, col);
                    print_matrix(matrix_a_t, col, row);
                    count++;
                }

                else            //Initialize Matrix 먼저 실행 되지 않았을때
                {
                    printf("Please Matrix Initialize first!\n");
                }

                break;

            case 'm': case 'M': //command가 m 또는 M일때
                 if(count != 0) //Initialize Matrix 먼저 실행했을경우
                {
                    printf("Multiply matrix_a with transposed matrix_a \n");
                    multiply_matrix(matrix_a, matrix_a_t, row, col);
                }

                else            //Initialize Matrix 먼저 실행 되지 않았을때
                {
                    printf("Please Matrix Initialize first!\n");
                }

                break;

            case 'q': case 'Q': //command가 q 또는 Q일때
                printf("Free all matrices..\n");
                free_matrix(matrix_a_t, col, row);
                free_matrix(matrix_a, row, col);
                free_matrix(matrix_b, row, col);
                break;

            default:            //Initialize Matrix 먼저 실행 되지 않았을때
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;   //1 반환
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{//malloc()을 이용해서 row와 col사이즈의 행렬 만드는 함수
    /* check pre conditions */

    if(row <= 0 || col <=0) //row나 col이 0 보다 작을때
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int **arr = (int**)malloc(sizeof(int*)*row);

    for (int i=0;i<row;i++)
    {
        arr[i] = (int*) malloc(sizeof(int)*col);
    }

    if (arr == NULL) //메모리 할당에 실패 했을때
    {
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

    return arr;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{//matrix를 출력 하는 함수
    /* Check pre conditions */

	if (row <= 0 || col <= 0) //row나 col이 0 보다 작을때
    {
		printf("Check the size of row and col!\n");
		return;
	}

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            printf("%d\t", matrix[i][j]);
        }

        printf("\n");
    }
    
    if (matrix == NULL) //메모리 할당에 실패 했을때
    { 
		printf("Memory Allocation Failed.\n");
		return;
	}
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{//create_matrix()로 할당한 메모리를 해제하는 함수

    if(row <= 0 || col <=0) //row나 col이 0 보다 작을때
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    for (int i=0;i<row;i++)
    {
        free(matrix[i]);
    }
    
    free(matrix);

    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{//랜덤 값을 matrix에 초기화 하는 함수

    if(row <= 0 || col <=0) //row나 col이 0 보다 작을때
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    //0~19의 난수 초기화 하는 for문
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            matrix[i][j] = rand()%20; //0~19의 난수 초기화
        }
    }

    if (matrix == NULL) //메모리 할당에 실패 했을때
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{//matrix_sum에 matrix_a + matrix_b를 저장하는 함수

    int** matrix_sum = create_matrix(row, col);

	/* Check pre conditions */
	if (row <= 0 || col <= 0) //row나 col이 0 보다 작을때
    {
		printf("Check the size of row and col!\n");
		return -1;
	}

    //matrix_sum에 matrix_a,b의 합을 저장하는 for문
	for (int i = 0; i < row; i++) 
    {
		for (int j = 0; j < col; j++)
        {
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
	}

	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) //메모리 할당에 실패 했을때
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col);
	free_matrix(matrix_sum, row, col);

	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{//matrix_sub에 matrix_a - matrix_b를 저장하는 함수
    int** matrix_sub = create_matrix(row, col);

	/* Check pre conditions */
	if (row <= 0 || col <= 0) //row나 col이 0 보다 작을때
    {
		printf("Check the size of row and col!\n");
		return -1;
	}

    //matrix_sub에 matrix_a,b의 차를 저장하는 for문
	for (int i = 0; i < row; i++) 
    {
		for (int j = 0; j < col; j++)
        {
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
	}

	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) //메모리 할당에 실패 했을때
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sub, row, col);
	free_matrix(matrix_sub, row, col);

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{//matrix의 전치행렬 matrix_t를 연산하는 함수

    /* Check pre conditions */
	if (row <= 0 || col <= 0) //row나 col이 0 보다 작을때
    {
		printf("Check the size of row and col!\n");
		return -1;
	}

    //전치행렬 matrix_t의 전치행렬을 저장하는 for문
    for(int j=0;j<col;j++)
    {
        for(int i=0;i<row;i++)
        {
            matrix_t[j][i] = matrix[i][j];
        }
    }

    if (matrix == NULL || matrix_t ==NULL) //메모리 할당에 실패 했을때
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{//matrix_axt에 matrix_a X matrix_b를 저장하는 함수
    int **matrix_axt = create_matrix(row,row);

    if (row <= 0 || col <= 0)   //row나 col이 0 보다 작을때
    {
		printf("Check the size of row and col!\n");
		return -1;
	}

    //matrix_a,t의 곱을 저장하는 for문
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<row;j++)
        {
            matrix_axt[i][j] = 0;   

            for(int k=0;k<col;k++)
            {
                matrix_axt[i][j] += matrix_a[i][k] * matrix_t[k][j];
            }
        }
    }

    if (matrix_t == NULL || matrix_axt ==NULL) //메모리 할당에 실패 했을때
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    
    print_matrix(matrix_axt,row,row);
    free_matrix(matrix_axt,row,row);

    return 1;
}

