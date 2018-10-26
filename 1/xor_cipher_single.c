#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
 * this program is the c implementation of repeating xor cipher.
 * Param: message string
 * Output: encrypted cipher
 * Notice for xor decrypt function is the same as encrypt function
 */
char* encrypt(char* m, char key, int len){
	char* out = (char*)malloc(len*sizeof(char));

	for(int i=0; i<len; i++){
		out[i] = (int)m[i]^(int)key;
		printf("%.2x", out[i]);
	}
	printf("\n");
	return out;
}

void main(int argc, char* argv[]){

	/* input validation*/
	if(argc!=2){
		printf("Illegal Argument!\n");
		exit(-1);
	}

	char key = 'I';
	char* m = argv[1]; // message
	int m_len = strlen(m); //length of the message

	/* encrypting using xor*/
	encrypt(m,key,m_len);
}
