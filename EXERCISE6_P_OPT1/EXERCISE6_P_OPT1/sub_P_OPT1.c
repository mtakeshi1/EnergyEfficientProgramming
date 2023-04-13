/* Unroll loops in C sub_P_OPT1.c*/

#define N 20
															 
void Feld_Add(long C[], long A[], long B[]){
	int i;
	for (i=0;i<N;i++){
		C[i++]=A[i]+B[i];
		C[i++]=A[i]+B[i];
		C[i++]=A[i]+B[i];
		C[i]  =A[i]+B[i];
	}
}