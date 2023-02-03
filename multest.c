/*+++++++++++++++++++++++++++++++++++
.COPYRIGHT	Copyright statement	Required, Header
.IDENTifier	File name of module	Required, Header
.MODULE	Type of module	 
.AUTHOR	Name of creator	Required, Header
.KEYWORDs	Subject keywords	Required
.LANGUAGE	Language of module	Required, Header
.PURPOSE	General purpose of module	Required
.COMMENTs	Comments	Optional
.VERSION	Version no., date, etc.	Required, Header
.RETURNS	Return values for functions	Required, Routine
.ENVIRONment	Special environment requirements	Required
multest.c
Author: Edgar Rene Ramos Acosta
Lenguage: C
Purpose: Next code below shows how matrices can be multiplied by using the sequential algorithm

--------------------------------------*/
#include <stdio.h>


void multiply(float A[8][8], float B[8][8], float C[8][8])
{

}
void main()
{
    int ROW= 8;
    int COL= 8;
    int i=0, j=0, k=0;
    
    printf("Enters size of matrices (default is 8): ");
    scanf("%d", &ROW);
    COL=ROW;
    printf("Size of matrices are %d by %d", ROW, COL);



}