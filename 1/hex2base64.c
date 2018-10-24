include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Encode an int value using base64 */
char base64_int2char(u_int32_t value){
	char result;
	if(value<26) // a-z
		result = (char)(value+65);
	else if(value>25 && value<52) // A-Z
		result = (char)(value-26+97);
	else if(value<62) // 0-9
		result = (char)(value-52+48);
	else if(value=63) // +
		result = '+';
	else // /
		result = '/';
	return result;
}


/* convert hex char to dec */
int hex_char2int(char input){
	int result = 0;
	if((int)input>47 && (int)input<58)
		result = (int)input-48;
	else if((int)input>96 && (int)input<104)
		result = (int)input-97+10;
	else
		result = 0;
	return result;
}

/* print binary sequence of dec */
void print_bin(int value){
	for(int i=23; i>=0; i--){
		//print the highest bit first
		int result = (value & (1<<i))!=0;
		printf("%d", result);
	}
}


int main(int argc, char* argv[]){
	
	if(argc!=2){
		printf("Illegal Arguments!\n");
		exit(-1);
	}
	
	u_int8_t padding[] = "=======\0";
	u_int8_t input_len = strlen(argv[1]); // input byte length 
	u_int8_t output_len = (input_len/6)*4; // output byte length
	
	/* if padding is needed */
	if(output_len*6!=input_len*4){
		output_len=4*(input_len/6+1);
	}
	
	u_int8_t hex[output_len/4*6];
	memcpy(hex, argv[1], input_len);
	memcpy(hex+input_len, padding, output_len/4*6-input_len);

	u_int32_t* base64 = malloc(output_len*sizeof(u_int32_t));
	char result[output_len];

	printf("input len: %d\n", input_len);
	printf("output len: %d\n", output_len);
	printf("chunk num: %d\n\n", input_len/6);

	printf("Chunk\tHex\t\tBinary\t\t\t\tBase64\n");
	for(int i=0; i<output_len/4; i++){
		u_int8_t* input_p = hex + i*6;
		u_int32_t* output_p = base64 + i*4;
		u_int32_t chunk = 0;

		printf("%d\t", i+1);
		for(int j=0; j<6; j++){
			chunk = chunk << 4;
			chunk += hex_char2int(*(input_p+j));
		}
		printf("%.*s\t\t", 6, hex + i*6);
		print_bin(chunk);
		printf("\t");

		for(int j=0; j<4; j++){
			*(output_p+j) = (chunk & (63<<j*6)) >> j*6;
			/* uncomment the following to see the whole calculate process
			 * printf("\n");
			 * print_bin(chunk);
			 * printf(" + ");
			 * print_bin((63<<j*6));
			 * printf(" = ");
			 * print_bin(*(output_p+j));
			 * printf(" = %d\t", *(output_p+j));
			 */
			if(((3-j)+i*4)<= input_len*4/6)
				printf("%c", base64_int2char(*(output_p+j)));
			else
				printf("=");
			result[(3-j)+i*4] = base64_int2char(*(output_p+j));
		}
		printf("\n");
	}

	if(output_len*6!=input_len*4){
		int pad_len = output_len - input_len*4/6;
		for(int i=0; i<pad_len; i++)
			result[output_len-i]='=';
	}
	result[output_len] = '\0';
	printf("\nResult: %s\n", result);
}
