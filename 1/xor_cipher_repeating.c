#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
 * this program is the c implementation of repeating xor cipher.
 * Param: message string
 * Output: encrypted cipher
 */
void main(int argc, char* argv[]){
	
	/* input validation*/
	if(argc!=2){
		printf("Illegal Argument!\n");
		exit(-1);
	}
	
	/* set the encryption key to "ICE"*/
	char key[] = "ICE";
	char* m = argv[1];
	int m_len = strlen(m);
	int count = 0;
	u_int8_t result[m_len];

	/* encrypting using xor*/
	for(int i=0; i<m_len; i++, count++){
		result[i] = (int)m[i]^(int)key[count%3];
		printf("%.2x", result[i]);
	}

	printf("\n");
}
