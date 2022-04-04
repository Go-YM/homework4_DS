#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//<stdio.h>, <stdlib.h>, <time.h>�� ������ ���� �ҽ��� Ȯ���ϵ��� ����

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

//�� ���α׷��� �����Լ�
int main()
{
    int row, col;
    char command;
    int count=0;        //��� �ʱ�ȭ �� �ٸ� ���� ���� ���ϵ��� �ϴ� ������ ���� count ����

    printf("[----- [???????]  [2019038003] -----]\n");

    srand(time(NULL));  //���� ������ �����ϵ��� ����

    //row�� col�� ����ڷκ��� �Է� ����
    printf("Input row and col : ");
    scanf("%d %d", &row, &col);

    int** matrix_a = create_matrix(row, col);   //��� A ���� �� ����
    if (matrix_a == NULL) {return -1;}

    int** matrix_b = create_matrix(row, col);   //��� B ���� �� ����
    if (matrix_b == NULL) {return -1;}

    int** matrix_a_t = create_matrix(col, row); //��� a_t���� �� ����

    printf("Matrix Created.\n");

    //q �Ǵ� Q �Է� �ޱ� ������ ���� ���� �ϴ� do-while ��
    do{//�޴� ���
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        //����ڷκ��� command�� �Է� ����
        printf("Command = ");
        scanf(" %c", &command);

        switch(command) 
        {
            case 'z': case 'Z': //command�� z �Ǵ� Z�϶�
                if(count == 0)  //Initialize Matrix���� ���� �ϵ��� count ����
                {
                    printf("Matrix Initialized\n");
                    fill_data(matrix_a, row, col);
                    fill_data(matrix_b, row, col);
                    count++;    //Initialize Matrix ���� ���� �ٸ� �Լ� ���� ���ϵ��� count++
                }

                break;

            case 'p': case 'P': //command�� p �Ǵ� P�϶�
                if(count != 0)  //Initialize Matrix ���� ���� ���� ���
                {
                    printf("Print matrix\n");
                    printf("matrix_a\n");
                    print_matrix(matrix_a, row, col);
                    printf("matrix_b\n");
                    print_matrix(matrix_b, row, col);
                }

                else            //Initialize Matrix ���� ���� ���� �ʾ�����
                {
                    printf("Please Matrix Initialize first!\n");
                }

                break;

            case 'a': case 'A': //command�� a �Ǵ� A�϶�
                if(count != 0)  //Initialize Matrix ���� ���� ���� ���
                {
                    printf("Add two matrices\n");
                    addition_matrix(matrix_a, matrix_b, row, col);  
                }

                else            //Initialize Matrix ���� ���� ���� �ʾ�����
                {
                    printf("Please Matrix Initialize first!\n");
                }

                break;

            case 's': case 'S': //command�� s �Ǵ� S�϶�
                if(count != 0)  //Initialize Matrix ���� ���� ���� ���
                {
                    printf("Subtract two matrices \n");
                    subtraction_matrix(matrix_a, matrix_b, row, col);
                }

                else            //Initialize Matrix ���� ���� ���� �ʾ�����
                {
                    printf("Please Matrix Initialize first!\n");
                }

                break;

            case 't': case 'T': //command�� t �Ǵ� T�϶�
                if(count != 0)  //Initialize Matrix ���� ���� ���� ���
                {
                    printf("Transpose matrix_a \n");
                    printf("matrix_a_t\n");
                    transpose_matrix(matrix_a, matrix_a_t, row, col);
                    print_matrix(matrix_a_t, col, row);
                    count++;
                }

                else            //Initialize Matrix ���� ���� ���� �ʾ�����
                {
                    printf("Please Matrix Initialize first!\n");
                }

                break;

            case 'm': case 'M': //command�� m �Ǵ� M�϶�
                 if(count != 0) //Initialize Matrix ���� �����������
                {
                    printf("Multiply matrix_a with transposed matrix_a \n");
                    multiply_matrix(matrix_a, matrix_a_t, row, col);
                }

                else            //Initialize Matrix ���� ���� ���� �ʾ�����
                {
                    printf("Please Matrix Initialize first!\n");
                }

                break;

            case 'q': case 'Q': //command�� q �Ǵ� Q�϶�
                printf("Free all matrices..\n");
                free_matrix(matrix_a_t, col, row);
                free_matrix(matrix_a, row, col);
                free_matrix(matrix_b, row, col);
                break;

            default:            //Initialize Matrix ���� ���� ���� �ʾ�����
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;   //1 ��ȯ
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{//malloc()�� �̿��ؼ� row�� col�������� ��� ����� �Լ�
    /* check pre conditions */

    if(row <= 0 || col <=0) //row�� col�� 0 ���� ������
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int **arr = (int**)malloc(sizeof(int*)*row);

    for (int i=0;i<row;i++)
    {
        arr[i] = (int*) malloc(sizeof(int)*col);
    }

    if (arr == NULL) //�޸� �Ҵ翡 ���� ������
    {
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

    return arr;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{//matrix�� ��� �ϴ� �Լ�
    /* Check pre conditions */

	if (row <= 0 || col <= 0) //row�� col�� 0 ���� ������
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
    
    if (matrix == NULL) //�޸� �Ҵ翡 ���� ������
    { 
		printf("Memory Allocation Failed.\n");
		return;
	}
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{//create_matrix()�� �Ҵ��� �޸𸮸� �����ϴ� �Լ�

    if(row <= 0 || col <=0) //row�� col�� 0 ���� ������
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
{//���� ���� matrix�� �ʱ�ȭ �ϴ� �Լ�

    if(row <= 0 || col <=0) //row�� col�� 0 ���� ������
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    //0~19�� ���� �ʱ�ȭ �ϴ� for��
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            matrix[i][j] = rand()%20; //0~19�� ���� �ʱ�ȭ
        }
    }

    if (matrix == NULL) //�޸� �Ҵ翡 ���� ������
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{//matrix_sum�� matrix_a + matrix_b�� �����ϴ� �Լ�

    int** matrix_sum = create_matrix(row, col);

	/* Check pre conditions */
	if (row <= 0 || col <= 0) //row�� col�� 0 ���� ������
    {
		printf("Check the size of row and col!\n");
		return -1;
	}

    //matrix_sum�� matrix_a,b�� ���� �����ϴ� for��
	for (int i = 0; i < row; i++) 
    {
		for (int j = 0; j < col; j++)
        {
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
	}

	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) //�޸� �Ҵ翡 ���� ������
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
{//matrix_sub�� matrix_a - matrix_b�� �����ϴ� �Լ�
    int** matrix_sub = create_matrix(row, col);

	/* Check pre conditions */
	if (row <= 0 || col <= 0) //row�� col�� 0 ���� ������
    {
		printf("Check the size of row and col!\n");
		return -1;
	}

    //matrix_sub�� matrix_a,b�� ���� �����ϴ� for��
	for (int i = 0; i < row; i++) 
    {
		for (int j = 0; j < col; j++)
        {
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
	}

	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) //�޸� �Ҵ翡 ���� ������
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
{//matrix�� ��ġ��� matrix_t�� �����ϴ� �Լ�

    /* Check pre conditions */
	if (row <= 0 || col <= 0) //row�� col�� 0 ���� ������
    {
		printf("Check the size of row and col!\n");
		return -1;
	}

    //��ġ��� matrix_t�� ��ġ����� �����ϴ� for��
    for(int j=0;j<col;j++)
    {
        for(int i=0;i<row;i++)
        {
            matrix_t[j][i] = matrix[i][j];
        }
    }

    if (matrix == NULL || matrix_t ==NULL) //�޸� �Ҵ翡 ���� ������
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{//matrix_axt�� matrix_a X matrix_b�� �����ϴ� �Լ�
    int **matrix_axt = create_matrix(row,row);

    if (row <= 0 || col <= 0)   //row�� col�� 0 ���� ������
    {
		printf("Check the size of row and col!\n");
		return -1;
	}

    //matrix_a,t�� ���� �����ϴ� for��
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

    if (matrix_t == NULL || matrix_axt ==NULL) //�޸� �Ҵ翡 ���� ������
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    
    print_matrix(matrix_axt,row,row);
    free_matrix(matrix_axt,row,row);

    return 1;
}

