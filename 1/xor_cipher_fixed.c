#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/*
 * This prgrame takes two hex string as input. Those two strings must have the same length
 * Retruns the XOR of these two strings.
 * */
void main(int argc, char* argv[]){
	/* input validation*/
	if(argc!=3 || strlen(argv[1])!= strlen(argv[2])){
		printf("Illegal Arguments!\n");
		exit(-1);
	}

	u_int32_t len = strlen(argv[1]); // length of input string (both)
	printf("\nLength: %d bytes\n", len);
	printf("\nM1\t:%s\n", argv[1]);
	printf("M2\t:%s\n", argv[2]);
	printf("M1^M2\t:");	
	/* Caluculate 2 hex string at a time*/
	for(int i=0, j=0; i<len; i+=2, j++){
		u_int8_t var1[3]; // load 2 hex chars from string 1
		u_int8_t var2[3]; // load 2 hex chars from string 2
		unsigned int var3;		

		var1[3] = '\0'; // indicating the end of var1
		var2[3] = '\0'; // indicating the end if var2
		
		memcpy(var1, argv[1]+i, 2); 	
		memcpy(var2, argv[2]+i, 2);
		var3 = (int)strtol(var1, NULL, 16) ^ (int)strtol(var2, NULL, 16); //xor operation
		printf("%.2x", var3); // output
	}
	printf("\n\n");
}
