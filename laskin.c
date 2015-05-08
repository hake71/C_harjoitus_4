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

/*	Convert string to integer,
	if string is not number, return 0 as error */
char Is_Number(char *mjono, int *number)
{
	unsigned char  i = 0;
	int Luku = 0;
	/* Convert string to integer */
	
	/* Go through full string */
	while(mjono[i]){
		/* If digit ... */
		if(isdigit(mjono[i]))
		{
			/* ...Add numeric value to result */
			Luku = Luku *10 + (mjono[i] - '0');
		/* If not digit ... */
		}else {
			/* Return error code */
			return 0;
		}
		/* Update index for next char */
		i++;
	}
	
	/* Result number */
	*number = Luku;
	/* return OK code */
	return 1;
}

/* 	Check if correct operand */
char Is_Operator(char *mjono)
{
	switch((char)mjono[0]){
		case '+':
		case '-':
		case 'x': 				
		case '*':
		case '/':
			return 1;
			
		default:
			return 0;
	}
	return 1;
}

/* Define number and operand tables */
#define MAX_PARAM 10
double Numbers[MAX_PARAM+1];
char Operators[MAX_PARAM];

/* 	Remove number and operand when calculation
	is executed */
void Remove_index(char index){
	unsigned char i;
	for( i = index; i < (MAX_PARAM-1); i++)
	{
		Numbers[i+1] = Numbers[i+2];
		Operators[i] = Operators[i+1];
	}
}

/* 	Execute calculation based on operand and
 	and return result */
double calculate(double luku1, double luku2, char oper){

	switch(oper)
	{
		case '+': return luku1 + luku2;
		case '-': return luku1 - luku2;
		case 'x': return luku1 * luku2;
		case '/': return luku1 / luku2;
		default:
			printf("!! ERROR in count !!!!\n");
	}
	return 0;
}

/* 	Compare current and next operand order:
	If first operand is "+" or "-" and next
	operand is '*' or '/', then next operand have
	higer priority asn is executed -> Result = 1 
	If current operand is same or higer priority
	than next one, then execute current operand
	-> Result = 0  */
char CheckCountOrder(char op1, char op2){
	/* If next operand have higer priority .. */
	if(((op2 == 'x') ||(op2 == '/' )) && \
		((op1 == '+') ||(op1 == '-' ))){
		/* Return 1 */
		return 1;
	}
	/* Otherwise return 0 */
	return 0;
}

int main(int argc, char *argv[]) {

	int param;
	unsigned int i;	
	unsigned char o_count, n_count;
	
	/* Check arguments */
	/* There is no arguments */
	if(argc == 1){
		printf(" Error: No parameters\n");
		return 1;
		
	/* There is 2 arguments */
	} else if(argc == 2){
		printf(" %s = %s\n", argv[1], argv[1]);
		return 0;
	}
	
	/* Initialize operand and number count */ 
 	o_count = 0;
 	n_count = 0;
 
	/* Check parameters */
	for(i = 1; i < argc; i++){
		/* Should be number */
		if(i & 1){
			/* Check if parameter is number ... */
			if(Is_Number(argv[i], &param)){
				/* ... parameter is number */
				Numbers[n_count++] = param;
			 } else {
				/* ... parameter is NOT number */
			 	printf(" ERROR: %s not number\n", argv[i]);
			 	return 1;
			 }
		}
		/* Should be operator */
		else {
			/* Check if parameter is operator ... */
			if(Is_Operator(argv[i])){
				/* ... parameter is operator */
				Operators[o_count++] = (char)argv[i][0];
			}else {
				/* ... parameter is NOT operator */
			 	printf(" ERROR: %s not Operator\n", argv[i]);
			 	return 1;
			}		
		}		
	} /* for() */
	
	/* Final check: Compare number and operator amount */
	if((o_count + 1) != n_count){
		printf("ERROR: Operator and number count not match \n");
		return 1;
	}

	/* Print calculus */
	printf(" %d",(int)Numbers[0]);
	for(i=0;i<o_count;i++){
		printf(" %c",Operators[i]);
		printf(" %d",(int)Numbers[i+1]);
	}
	printf(" =");
	
	/* Actual calculation */
	do{
		/* If next operand have higer priority ... */
		if(CheckCountOrder(Operators[0], Operators[1])){
			/* Calculate next operand  */
			Numbers[1] = calculate(Numbers[1], \
				Numbers[2], Operators[1]);
			Remove_index(1);
		}
		/* Can calculate current operand ... */
		else{
			/* Calculate current operand */
			Numbers[0] = calculate(Numbers[0], \
				Numbers[1], Operators[0]);
			Remove_index(0);
		}
		o_count--;
	}while(o_count);
	
	/* Print calculation result */
	printf(" %.2f\n", Numbers[0]);
	
	return 0;
}

/* End of file */
