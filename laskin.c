/**
	* Version: 0.0.1
	* Author: Hannu Harju
	*/

/**
	*
	* Calculate given formula
	*/
	
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/**
	* Calculator
	* @arg 1..n : Numbers and operands (+,-,*,/)
	* Execute calculation
	*
	*/

char Is_Number(char *mjono, int *number)
{
	unsigned char  i = 0;
	int Luku = 0;
	
	while(mjono[i]){
		if(isdigit(mjono[i]))
		{
	//	printf("%c", mjono[i]);
			Luku = Luku *10 + (mjono[i] - '0');
		}else {
			return 0;
		}
		
		i++;
	}
	*number = Luku;
//	printf("  -> %d \n", Luku);
	return 1;
}

char Is_Operator(char *mjono, char *oper)
{
	switch((char)mjono[0]){
		case '+': *oper = -1;
				break;
		case '-': *oper = -2;
				break;
		case 'x': 				
		case '*': *oper = 1;
				break;
		case '/': *oper = 2;
				break;
		default:
			*oper = 0;
			return 0;
	}
	return 1;
}


#define MAX_PARAM 10
double Numbers[MAX_PARAM+1];
char Operators[MAX_PARAM];

void Remove_index(char index){
	unsigned char i;
	for( i = index; i < (MAX_PARAM-1); i++)
	{
		Numbers[i+1] = Numbers[i+2];
		Operators[i] = Operators[i+1];
	}
}

double calculate(double luku1, double luku2, char oper){

	switch(oper)
	{
		case -1: return luku1 + luku2;
		case -2: return luku1 - luku2;
		case 1: return luku1 * luku2;
		case 2: return luku1 / luku2;
		default:
			printf("!! ERROR in count !!!!\n");
	}
	return 0;
}
void print_status(char count)
{
	unsigned char i;
	printf(" O: ");
	for(i=0;i<(count+1);i++){
		printf(" %4d", Operators[i] );
	}
	printf("\n P: ");
	for(i=0;i<(count+1);i++){
	printf(" %4f", Numbers[i] );
	}
	printf("\n");
}


int main(int argc, char *argv[]) {

	int param;
	char oper, o_count, p_count;
	unsigned int i;	
	
	if(argc == 1)
	{
		printf(" Error: No parameters\n");
		return 1;
	} else if(argc == 2){
		printf(" %s =  %s\n", argv[1], argv[1]);
		return 0;
	}
 	o_count = 0;
 	p_count = 0;
 
	/* Check parameters */
	for(i = 1; i < argc; i++){

	/* Should be number */
		if(i & 1){
			printf(" N: %s -> ", argv[i]);
			if(Is_Number(argv[i], &param)){
				printf(" Luku: %d \n", param);
				Numbers[p_count++] = param;
			 } else {
			 	printf(" ERROR: %s not number\n", argv[i]);
			 	return 1;
			 }
		}
		/* Should be operator */
		else {
			printf(" O: %s -> ", argv[i]);
			if(Is_Operator(argv[i], &oper)){
			printf(" Operator: %d \n", oper);
			Operators[o_count++] = oper;
			}else {
			 	printf(" ERROR: %s not Operator\n", argv[i]);
			 	return 1;
			 }		
		}		
	} /* for() */
	
	printf(" o count %d <-> %d p count\n", o_count, p_count);
	if((o_count + 1) != p_count)
	{
		printf(" Error in formula \n");
		return 1;
	}

//	double tulos = 0;
//	double tmp_tulos = 0;
	print_status(o_count);
	/* Actual calculation */
	do{
		/* Next operand have higer priority */
		if((Operators[0] < 0) && (Operators[1]>0))
		{
			Numbers[1] = calculate(Numbers[1], \
				Numbers[2], Operators[1]);
			Remove_index(1);
		}
		/* Current can calculate */
		else{
			Numbers[0] = calculate(Numbers[0], \
				Numbers[1], Operators[0]);
			Remove_index(0);
		}

		o_count--;
		print_status(o_count);
	}while(o_count);
	
	return 0;
}

/* End of file */