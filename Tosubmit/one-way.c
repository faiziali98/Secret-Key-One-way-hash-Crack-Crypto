#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
 {
	EVP_MD_CTX *mdctx;
	srand(time(NULL));
	unsigned char md_value[EVP_MAX_MD_SIZE];
	int md_len, i;

	OpenSSL_add_all_digests();
	if(!argv[1]||!argv[2]||!argv[3]) {
	    printf("Usage: ./mdtest digesttype digestvalue word\n");
	    exit(1);
	}
	if(!EVP_get_digestbyname(argv[1])) {
	    printf("Unknown message digest %s\n", argv[1]);
	    exit(1);
	}

	while(1){
		int r = 7;
		char *s = malloc(r+1);
		for(i = 0; i < r; i++) s[i] = (rand()%26)+65;
		s[r] = '\0';

		mdctx = EVP_MD_CTX_create();
		EVP_DigestInit_ex(mdctx, EVP_get_digestbyname(argv[1]), NULL);
		EVP_DigestUpdate(mdctx, s, strlen(s));
		EVP_DigestFinal_ex(mdctx, md_value, &md_len);
		EVP_MD_CTX_destroy(mdctx);
		char *outword = malloc((md_len-1)*2+1);

		printf("Digest of: %s is ",s);
		for(int l = 0; l < 3; l++) sprintf(outword+l*2, "%02X", md_value[l]);
    	printf("%s\n", outword);

    	if (strcmp(argv[2],outword) == 0 && strcmp(argv[3],s) == 0) break;
	}

	EVP_cleanup();
	exit(0);
 }
