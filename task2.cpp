#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

int do_crypt_io(FILE *in, FILE *out, int do_encrypt)
{
        unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
        int inlen, outlen;
        EVP_CIPHER_CTX *ctx;

        unsigned char key[] = "";
        unsigned char iv[] = "";

        ctx = EVP_CIPHER_CTX_new();
        EVP_CipherInit_ex(ctx, EVP_aes_128_cbc(), NULL, NULL, NULL,do_encrypt);

        OPENSSL_assert(EVP_CIPHER_CTX_key_length(ctx) == 16);
        OPENSSL_assert(EVP_CIPHER_CTX_iv_length(ctx) == 16);

        EVP_CipherInit_ex(ctx, NULL, NULL, key, iv, do_encrypt);

        while (1)
        {
            inlen = fread(inbuf, 1, 1024, in);
            if(inlen <= 0) break;
            if(!EVP_CipherUpdate(ctx, outbuf, &outlen, inbuf, inlen))
            {
                EVP_CIPHER_CTX_free(ctx);
                return 0;
            }
            fwrite(outbuf, 1, outlen, out);
        }
        if(!EVP_CipherFinal_ex(ctx, outbuf, &outlen))
        {
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }
        fwrite(outbuf, 1, outlen, out);

        char *outword = malloc((outlen-1)*2+1);
        printf("Encryption is: ");
        for(int l = 0; l < outlen; l++) sprintf(outword+l*2, "%02X", outbuf[l]);
        printf("%s\n", outword);

        EVP_CIPHER_CTX_free(ctx);
        return 1;
}
int main(int argc, char *argv[])
{
    if(!argv[1]||!argv[2]) {
        printf("Usage: ./execute filename\n");
        exit(1);
    }
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "wb");;
    do_crypt_io(in,out,1);
    exit(0);
}
