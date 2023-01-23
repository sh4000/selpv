// as4h
// Resolution de systeme d'equations lineaires a plusieurs variables en C


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3 

void printMatrix(double mat[N][N+1]) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j <= N; j++) {
            printf("%lf ", mat[i][j]);
        }
        printf("\n");
    }
}

void gaussJordan(double mat[N][N+1]) {
    int i, j, k;
    double temp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (j != i) {
                temp = mat[j][i] / mat[i][i];
                for (k = 0; k <= N; k++) {
                    mat[j][k] -= mat[i][k] * temp;
                }
            }
        }
    }

    for (i = 0; i < N; i++) {
        mat[i][N] = mat[i][N] / mat[i][i];
        mat[i][i] = 1;
    }
}

void findSolutions(double mat[N][N+1], double solutions[N]) {
    int i;
    for (i = 0; i < N; i++) {
        solutions[i] = mat[i][N];
    }
}

double calculateResidual(double mat[N][N+1], double solutions[N]) {
    int i, j;
    double residual = 0, sum;
    for (i = 0; i < N; i++) {
        sum = 0;
        for (j = 0; j < N; j++) {
            sum += mat[i][j] * solutions[j];
        }
        residual = fmax(residual, fabs(sum - mat[i][N]));
    }
    return residual;
}

int main() {
	double mat[N][N+1] = { { 2, 1, -1, 8 }, { -3, -1, 2, -11 }, { -2, 1, 2, -3}
	};
	double solutions[N];
	double residual;
	
	printf("Matrice augmentée du système : \n");
	printMatrix(mat);
	printf("\n");
	gaussJordan(mat);
	printf("Matrice réduite en forme échelonnée : \n");
    
    printMatrix(mat);
    printf("\n");
    
    findSolutions(mat, solutions);
    printf("Solutions : \n");
    for (int i = 0; i < N; i++) {
	    printf("x%d = %lf\n", i+1, solutions[i]);
    }
    printf("\n");
    residual = calculateResidual(mat, solutions);
    printf("Norme infinie des résidus : %lf\n", residual);
    if (residual <= 0.0001) {
	    printf("Le système a été résolu avec succès.\n");
    }
    else {
	    printf("Le système n'a pas été résolu avec succès.\n");
    }
    return 0;
}


