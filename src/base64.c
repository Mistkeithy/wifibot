#include <stdio.h>

#define BASE64_MAP_SIZE 64

const char base64_map[BASE64_MAP_SIZE] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
    'w', 'x', 'y', 'z', '0', '1', '2', '3', 
    '4', '5', '6', '7', '8', '9', '+', '/'
};

char* base64_encode(const char* plain) {

	char buffer[3];
	int plain_len = strlen(plain);
	char* cipher = malloc(plain_len * 4 / 3 + 4);
	int i = 0, c = 0;

	while (plain[i] != '\0') {
		buffer[c++] = plain[i++];
		if (c == 3) {
			cipher[c] = base64_map[buffer[0] >> 2];
			cipher[++c] = base64_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
			cipher[++c] = base64_map[((buffer[1] & 0x0f) << 2) + (buffer[2] >> 6)];
			cipher[++c] = base64_map[buffer[2] & 0x3f];
			c = 0;
		}
	}

	if (c > 0) {
		cipher[c] = base64_map[buffer[0] >> 2];
		if (c == 1) {
			cipher[++c] = base64_map[(buffer[0] & 0x03) << 4];
			cipher[++c] = '=';
		} else {
			cipher[++c] = base64_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
			cipher[++c] = base64_map[(buffer[1] & 0x0f) << 2];
		}
		cipher[++c] = '=';
	}

	cipher[++c] = '\0';
	return cipher;
}