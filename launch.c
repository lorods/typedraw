/*
* launch.c
*
*  Created on: Sep 22, 2025
*      Author: lorod | Lorenzo
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int retrieveNval(int funval){
	scanf("%i",&funval);
	return funval;
}

int resetCyclr(int funcycl){
	funcycl=0;
	return funcycl;
}

void remBuffer(void){
	while((getchar())!='\n');
}

void freeArray(char **auxarr, int cyclr, int nval){
	for (cyclr; cyclr<nval; cyclr++) {
		if(auxarr[cyclr]!=NULL) free(auxarr[cyclr]);
	}
	free(auxarr);
}

int main(void){
	int nval=0; //declaring the initial number of values to be provided by user
	int cyclr=0;
	char valtype='-';
	char uppvalt;
	int selctd=-1; //reminder to reset selctd to -1 when leaving loops/blocks
	do{
		printf("What is the type of the values you want to add to the draw? Enter N/n for numbers and S/s for strings with any length.\n");
		valtype = getchar();
		valtype = tolower(valtype);
		if(valtype!='n'&&valtype!='s') printf("You didn't provide a valid data type. Retrying...\n");
	} while (valtype != 'n' && valtype != 's');
	uppvalt = toupper(valtype);
	printf("%c data type successfully validated.\n",uppvalt);

	while (nval <= 1) {
		switch (uppvalt) {
		case 'N': {
			printf("How many of '%c' (numbers) will be in the draw? ", uppvalt);
			nval = retrieveNval(nval);
			break;
		}
		case 'S': {
			printf("How many of '%c' (strings) will be in the draw? ", uppvalt);
			nval = retrieveNval(nval);
			break;
		}
		default: {
			// default here is a formality
		}
			if (nval <= 1)
				printf("Try again--your draw needs at least two elements.\n");
		}
	}
	printf("Gotcha. A total of %i values will enter your draw.\n", nval);

	switch (uppvalt) {
	case 'N': {
		// handle values as integers
		int arrwval[nval];
		printf("You'll now be prompted to type all the values that you want to enter the draw.");
		for (cyclr; cyclr < nval; cyclr++) {
			printf("\nNumber to be added to index #%i: ", cyclr);
			scanf("%i", &arrwval[cyclr]);
			remBuffer();
		}
		cyclr = resetCyclr(cyclr);
		printf("Numbers that are entering the draw: ");
		for (cyclr; cyclr < nval; cyclr++) {
			printf("%i ", arrwval[cyclr]);
			if (nval != (cyclr + 1))
				printf("- ");
		}
		cyclr = resetCyclr(cyclr);
		selctd = arc4random_uniform(nval);
		printf("\nSuccessfully picked number: %i.", arrwval[selctd]);
		break;
	}
	case 'S': {
		// handle values as strings
		char **arrwval = malloc(nval * sizeof(char *));
		int maxslength = 1;
		printf(
			"What is the largest length that one or more of your drawn elements will hold? e.g., 5 if the longest string is 'track'.\n");
		scanf("%i", &maxslength);
		remBuffer();
		maxslength += 2;
		for (cyclr; cyclr < nval; cyclr++) {
			arrwval[cyclr] = malloc(maxslength * sizeof(char));
		}
		cyclr = resetCyclr(cyclr);
		for (cyclr; cyclr < nval; cyclr++) {
			printf("\nEntered loop for %ist/nd/rd/th time.\nPlease input your next string, to be added to index #%i: ",(cyclr + 1), cyclr);
			if (fgets(arrwval[cyclr], maxslength, stdin) != NULL) {
				arrwval[cyclr][strcspn(arrwval[cyclr], "\n")] = 0; // remove trailing newline if somehow present in string
				printf("Successfully read value: %s\n", arrwval[cyclr]);
			}
		}
		selctd = arc4random_uniform(nval);
		printf("\nWE HAVE A WINNER! It is '%s'!", arrwval[selctd]);
		cyclr = resetCyclr(cyclr);
		freeArray(arrwval, cyclr, nval);
		// for debugging
		// printf("\nSize of pointer arrwval: %zu",sizeof(**arrwval));
		break;
	}
	default: {
		selctd = -1;
	}
	}
	return 1;
}
