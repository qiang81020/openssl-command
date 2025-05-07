#include <iostream>
#include <cstring>
#include <openssl/bio.h>
#include <openssl/evp.h>

void test_bio_mem(){
	BIO *b=NULL; 
	int len=0;
	char *out=NULL;

	b=BIO_new(BIO_s_mem()); 
	len=BIO_write(b,"openssl",4);
	//len=BIO_write(b,"openssl",7);
	len=BIO_printf(b,"%s","zcp"); 
	len=BIO_ctrl_pending(b);
	out=(char *)OPENSSL_malloc(len); 
	len=BIO_read(b,out,len); 
	printf(" %zu :  %s \n" ,strlen(out), out);
	//printf(" %d :  %s \n" ,len, out);

	OPENSSL_free(out);
	BIO_free(b);
}

void test_bio_file(){
    BIO *b=NULL; 
	int len=0,outlen=0;

	char *out=NULL;

	b=BIO_new_file("bf.txt","w"); 
	len=BIO_write(b,"openssl",4); 
	len=BIO_printf(b,"%s","zcp"); 
	BIO_free(b); 

	b=BIO_new_file("bf.txt","r");

	len=BIO_pending(b);
	len=50;
	out=(char *)OPENSSL_malloc(len); 
	len=1;
	while(len>0) {
		len=BIO_read(b,out+outlen,1);
		outlen+=len; 
	}
	printf("outlen = %d \n" , outlen);
	printf("%s\n", out);

// end:
	BIO_free(b); 
	// free(out); 
	OPENSSL_free(out);
}

void test_bio_md(){
    BIO *bmd=NULL,*b=NULL;
	// const  EVP_MD *md=EVP_md5();
	int len, i;  
	char tmp[1024]={0};

	bmd=BIO_new(BIO_f_md()); 
	BIO_set_md(bmd, EVP_md5());
	b= BIO_new(BIO_s_null()); 
	b=BIO_push(bmd,b); 
	len=BIO_write(b,"openssl",7); 
	len=BIO_gets(b,tmp,1024); 
	
	len = len;
	for ( i=0 ; i < 16; i++)
		printf("0x%02x: ", (uint8_t)tmp[i]);
	printf("\n");
	BIO_free(b);
}

void test_bio_md_push(){
	BIO *bio, *mdtmp;
	char buf[1024];
	int rdlen;
	bio = BIO_new_file("mdfile.txt", "rb");
	mdtmp = BIO_new(BIO_f_md());
	BIO_set_md(mdtmp, EVP_sha1());
	bio = BIO_push(mdtmp, bio);
	mdtmp = BIO_new(BIO_f_md());
	BIO_set_md(mdtmp, EVP_md5());
	bio = BIO_push(mdtmp, bio);
	do {
		// rdlen = BIO_read(bio, buf, sizeof(buf));
		rdlen = BIO_read(mdtmp, buf, sizeof(buf));
		/* Might want to do something with the data here */
		for (int i=0 ; i < rdlen; i++)
			printf("0x%02x: ", (uint8_t)buf[i]);
			// printf ("%s", buf);
		printf("\n");

	} while(rdlen > 0);

}

void test_bio_fd(){
	BIO *b=NULL;
	b=BIO_new_fd(fileno(stdout),BIO_NOCLOSE);
	BIO_free(b);
}

int main(){
	test_bio_mem();
	test_bio_file();
	test_bio_md();
	test_bio_md_push();
	return 0;
}