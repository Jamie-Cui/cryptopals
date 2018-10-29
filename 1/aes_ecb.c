#include <openssl/evp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* This program is just a simple example of asymmetric encryption and decrytion
 * Encrypt: 
 * 	int envelope_seal(EVP_PKEY **pub_key, unsigned char *plaintext, int plaintext_len,
	unsigned char **encrypted_key, int *encrypted_key_len, unsigned char *iv,
	unsigned char *ciphertext)
 * Decrypt:
 * 	int envelope_open(EVP_PKEY *priv_key, unsigned char *ciphertext, int ciphertext_len,
	unsigned char *encrypted_key, int encrypted_key_len, unsigned char *iv,
	unsigned char *plaintext)
 * Key and Param Gen (example of rsa key generation):
 * 	Param: 	kctx = EVP_PKEY_CTX_new_id(type, NULL)
 *	Key: 	EVP_PKEY_keygen_init(kctx) 
 *		EVP_PKEY_CTX_set_rsa_keygen_bits(kctx, 2048)
 *		EVP_PKEY_keygen(kctx, &key)
 * To compile: gcc aes_ecb.c -o aes_ecb -lcrypto, make sure you have successully installed openssl.
*/

/*
 * Base64 single char decoding
 */
u_int32_t base64_char2int(char value){
	u_int32_t result;
	if(value == '+')
		result = 62;
	else if(value == '/')
		result = 63;
	else if(value >= 65 && value <= 90)
		result = value - 65;
	else if(value >= 97 && value <= 122)
		result = value - 97 + 26;
	else if(value >= 48 && value <=57)
		result = value-48+52;
	else 
		result = 0;// deal with padding '='
	return result;
}

/* 
 * Takes a byte array (base64 encoded not hex) as input 
 * Return a ascii string
 */
unsigned char* base64_decode(u_int8_t* in, u_int32_t in_len){
	int chunk_num = in_len/4;
	int out_len = chunk_num*3;	
	u_int8_t* out = (u_int8_t*)malloc(sizeof(u_int8_t)*out_len);
	
	for(int i=0; i<in_len; i++){
		in[i] = base64_char2int(in[i]);
	}
	for(int i=0; i< chunk_num; i++){
		u_int32_t chunk_z = 0;
		u_int8_t* chunk_p = in + i*4;
		for(int j=0; j<4; j++)
			chunk_z += chunk_p[j]<<(3-j)*6;
		for(int j=0; j<3; j++){
			*(out + i*3 + 2-j) = (chunk_z & (255<<j*8)) >> j*8;		
		}	
	}
	return out;
}

/*use openssl library to decrypt ciphertext, use aes_128_ecb
 * A block has size of 128 bits, 128/8 = 16 bytes
*/
void aes_decrypt(char* ciphertext, char* key){
	EVP_CIPHER_CTX* ctx; // context
	int len; // temp length value
	unsigned char plaintext[128]; //output plaintext
	int plaintext_len;// plaintext length
	
	/* without complete error handling process*/
	ctx = EVP_CIPHER_CTX_new(); // init context
	EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
	/* Defining behavior for each block decryption */
	EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, strlen(ciphertext));
	plaintext_len = len;
	/* Defining the final behavior for final block*/
	EVP_DecryptFinal_ex(ctx, plaintext+len, &len);
	plaintext_len += len;

	plaintext[plaintext_len-1] = '\0'; // notify the end of string

	EVP_CIPHER_CTX_free(ctx);
	printf("%s\n", plaintext);

}

int main(){
	char* plaintext;
	FILE *fp;
	char temp[60];
	char ciphertext[3840];
	char key[] = "YELLOW SUBMARINE";	

	if((fp = fopen("aes_ecb.txt", "r")) == NULL)
		exit(-1);
	
	while(fscanf(fp, "%s", temp) != EOF){
		char* temp2;
		printf("Decrypting...Result:");
		strcat(ciphertext, temp); // add temp to the end of ciphertext
		/* Base 64 decoding using openssl library*/
		temp2 = base64_decode(temp, sizeof(temp));
		// printf("%s\n", temp2);
		aes_decrypt(temp2, key);
	}
	// printf("%s\n", ciphertext);		
}
