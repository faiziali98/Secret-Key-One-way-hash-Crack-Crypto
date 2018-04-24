#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

char* conspac(char *arr,int l,int n){
    n += l;
    char *toreturn = malloc(n+l);
    for (int i=0; i<n; i++){
        if (i<l-1)
            toreturn[i] = arr[i];
        else
            toreturn[i] = ' ';
    }
    return toreturn;
} 

int do_crypt(char *outfile, FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char cipher[] = "8D20E5056A8D24D0462CE74E4904C1B513E10D1DF4A2EF2AD4540FAE1CA0AAF9";

    while ((read = getline(&line, &len, fp)) != -1) {
        unsigned char outbuf[1024];
        int outlen, tmplen;

        char *key = conspac(line, read, 16-read);
        unsigned char iv[] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

        char intext[] = "This is a top secret.";
        EVP_CIPHER_CTX ctx;

        EVP_CIPHER_CTX_init(&ctx);
        EVP_EncryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, key, iv);

        if(!EVP_EncryptUpdate(&ctx, outbuf, &outlen, intext, strlen(intext))|| !EVP_EncryptFinal_ex(&ctx, outbuf + outlen, &tmplen))
        {
            return 0;
        }

        outlen += tmplen;
        EVP_CIPHER_CTX_cleanup(&ctx);

        char *outword = malloc((outlen-1)*2+1);
        for(int l = 0; l < outlen; l++) sprintf(outword+l*2, "%02X", outbuf[l]);

        if (strcmp(cipher,outword) == 0){
            printf("The key is..., wait for it \"%s\"", line);
            break;
        }
        char *line = NULL;
    }
}

int main(int argc, char *argv[])
{
    if(!argv[1]) {
        printf("Usage: ./execute filename\n");
        exit(1);
    }
    FILE *fp = fopen(argv[2], "r");
    do_crypt(argv[1], fp);
    exit(0);
}
