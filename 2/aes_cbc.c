#include <openssl/evp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* In this case we are using 128bit AEC with ECB mode (simpliest one)*/
#define BLOCKSIZE 128

/* structured context for better reading*/
typedef struct{
	EVP_CIPHER_CTX* ctx;
}aes_cbc_ctx;

/* To use this function, m1 must have the same length as m2 */
u_int8_t* xor(u_int8_t* m1, u_int8_t* m2, int len){
	u_int8_t* out = malloc(len * sizeof(u_int8_t));
	for(int i=0; i< len; i++){
		out[i] = m1[i]^m2[i];
	} 
	return out;
}

/* initilization of context and defines */
aes_cbc_ctx* aes_cbc_init(){
	aes_cbc_ctx* context = (aes_cbc_ctx*)malloc(sizeof(aes_cbc_ctx));
	context->ctx = EVP_CIPHER_CTX_new();
	
	/* for different blockszie, define different functions for EVP */
	switch(BLOCKSIZE){
	case 128:
		#ifndef EVPFUNC
		#define EVPFUNC EVP_aes_128_ecb()
		#endif
		break;
	case 256:
		#ifndef EVPFUNC
		#define EVPFUNC EVP_aes_256_ecb()
		#endif
		break;
	case 512:
		#ifndef EVPFUNC
		#define EVPFUNC EVP_aes_512_ecb()
		#endif
		break;
	/* other keysizes are not supported */
	default:
		printf("Key Size Not Supported!\n");
		return NULL;
	}
	return context;
}

/* Decryption function for aes_cbc */
void aes_cbc_decrypt(char* ciphertext, char* key){
	aes_cbc_ctx* context = aes_cbc_init();
	int len, plaintext_len;
	unsigned char plaintext[BLOCKSIZE];
	
	EVP_DecryptInit_ex(context->ctx, EVPFUNC, NULL, key, NULL);
	EVP_DecryptUpdate(context->ctx, plaintext, &len, ciphertext, strlen(ciphertext));
	plaintext_len = len;
	EVP_DecryptFinal_ex(context->ctx, plaintext+len, &len);
	plaintext_len += len;

	plaintext[plaintext_len-1] = '\0';

	EVP_CIPHER_CTX_free(context->ctx);
	printf("%s\n", plaintext);
}

void aes_cbc_encrypt(char* plaintext, char* key, char* iv){
	aes_cbc_ctx* context = aes_cbc_init();
	int len, ciphertext_len;
	unsigned char ciphertext[BLOCKSIZE];
	
	/* init encrypting keys and function */
	EVP_EncryptInit_ex(context->ctx, EVPFUNC, NULL, key, NULL);
	
	EVP_EncryptUpdate(context->ctx, xor(plaintext, ciphertext, BLOCKSIZE), &len, ciphertext, strlen(ciphertext));
	EVP_EncryptFinal_ex(context->ctx, plaintext+len, &len);
	ciphertext_len += len;
	printf("%s\n", ciphertext);
	EVP_CIPHER_CTX_free(context->ctx);
}

void main(){
	char key[] = "YELLOW SUBMARINE";
	char message[] = "This is the secret that everyone desires";
	char iv[] = "Published by me";
	aes_cbc_encrypt(message, key, iv);	
}
