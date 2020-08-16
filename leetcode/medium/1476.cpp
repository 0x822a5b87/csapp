//
// Created by 0x822a5b87 on 2020/8/14.
//
#include "iostream"

#define ROW_MAX 100
#define COL_MAX 100

typedef struct {
	int arr[ROW_MAX][COL_MAX];
} SubrectangleQueries;

SubrectangleQueries *subrectangleQueriesCreate(int **rectangle, int rectangleSize, int *rectangleColSize)
{
	int i, j;
	SubrectangleQueries *obj = NULL;

	obj = (SubrectangleQueries *)malloc(sizeof(SubrectangleQueries));
	if (obj == NULL) {
		return NULL;
	}
	memset(obj, 0, sizeof(SubrectangleQueries));

	for (i = 0; i < rectangleSize; i++) {
		for (j = 0; j < rectangleColSize[i]; j++) {
			obj->arr[i][j] = rectangle[i][j];
		}
	}

	return obj;
}

void subrectangleQueriesUpdateSubrectangle(SubrectangleQueries *obj, int row1, int col1, int row2, int col2, int newValue)
{
	int i, j;

	for (i = row1; i <= row2; i++) {
		for (j = col1; j <= col2; j++) {
			obj->arr[i][j] = newValue;
		}
	}
}

int subrectangleQueriesGetValue(SubrectangleQueries *obj, int row, int col)
{
	return obj->arr[row][col];
}

void subrectangleQueriesFree(SubrectangleQueries *obj)
{
	free(obj);
}
