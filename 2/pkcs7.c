#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* main PKCS#7 padding function 
	m: message
	m_len: message length in bytes
	blocksize: blocksize in bytes
*/
char* pkcs7(char* m, int m_len, int blocksize){
	if(strlen(m)!=m_len)
		return NULL;
	int padding = (blocksize - m_len%blocksize)%blocksize;
	char* out = (char*) malloc((m_len+padding)* sizeof(char));
	
//	printf("Block Size: %d\n", blocksize);
//	printf("Input Size: %d\n", m_len);
//	printf("Padding: %d\n", padding);
	memcpy(out, m, m_len-1);
//	printf("%s\n", out);
	
	for(int i=0; i<padding; i++){
		out[m_len -1 + i] = (char) padding;
	}
//	printf("out length: %ld\n", strlen(out));
	out[m_len+padding] = '\0';
//	printf("%s\n", out);
	return out;
}

/* test purpose only */
void main(int argc, char* argv[]){
	if(argc!=3){
		printf("Illegal Argument!\n");
		exit(-1);
	}
	
	int blocksize = atoi(argv[1]); // first argument is blocksize
	char* message = argv[2]; // second argument is message string
	
	char * out = pkcs7(message, strlen(message), blocksize);
	printf("%s\n", out);
}
