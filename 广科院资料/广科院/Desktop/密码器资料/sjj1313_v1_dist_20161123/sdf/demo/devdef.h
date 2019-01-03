#ifndef __DEVTEST_DEFINE_H__
#define __DEVTEST_DEFINE_H__

#define SGD_SCH_ID SGD_SM3

#define MAX_DATA_LENGTH			1024
#define MAX_RAND_LENGTH			128*1024
#define RAND_BLOCK_LENGTH		1024

#define FNAME_SM1PLAINDATA		"sm1plain.dat"
#define FNAME_SM2PLAINDATA		"sm2plain.dat"
#define FNAME_SM3PLAINDATA		"sm3plain.dat"
#define FNAME_SM4PLAINDATA		"sm4plain.dat"
#define FNAME_SM7PLAINDATA		"sm7plain.dat"
#define FNAME_DESPLAINDATA		"desplain.dat"
#define FNAME_SSF33PLAINDATA	"ssf33plain.dat"

#define FNAME_DECRYPTEDDATA		"decrypted.dat"
#define FNAME_SM2PUBKEY			"sm2pubkey.dat"
#define FNAME_SM2PRIKEY			"sm2prikey.dat"
#define FNAME_SM2CIPHER			"sm2cipher.dat"
#define FNAME_SM2SIGN			"sm2signature.dat"
#define FNAME_SM3USERID			"sm3userid.txt"
#define FNAME_SM1KEY			"sm1key.dat"
#define FNAME_SM4KEY			"sm4key.dat"
#define FNAME_SM7KEY			"sm7key.dat"
#define FNAME_DESKEY			"deskey.dat"
#define FNAME_SSF33KEY			"ssf33key.dat"
#define FNAME_ZUCKEY			"zuckey.dat"
#define FNAME_ZUCIV  			"zuciv.dat"
#define FNAME_ZUCPLAIN 			"zucplain.dat"
#define FNAME_SM1CBCIV			"sm1cbciv.dat"
#define FNAME_SM4CBCIV			"sm4cbciv.dat"
#define FNAME_SM7CBCIV			"sm7iv.dat"
#define FNAME_DESCBCIV			"descbciv.dat"
#define FNAME_SSF33CBCIV		"ssf33cbciv.dat"

#define FNAME_SM1CIPHER			"sm1cipher.dat"
#define FNAME_SM4CIPHER			"sm4cipher.dat"
#define FNAME_SM7CIPHER			"sm7cipher.dat"
#define FNAME_DESCIPHER			"descipher.dat"
#define FNAME_RANDOM			"random_data"

#define FNAME_RSAPRIKEY			"rsaprikey.dat"
#define FNAME_RSAPUBKEY			"rsapubkey.dat"
#define FNAME_RSAPLAIN			"rsaplain.dat"
#define FNAME_RSACIPHER			"rsacipher.dat"

#define FNAME_SESSIONPLAIN		"sessionplain.dat"
#define FNAME_SESSIONCIPHER		"sessioncipher.dat"
#define FNAME_RSACIPHERKEY		"rsacipherkey.dat"
#define FNAME_SM2CIPHERKEY		"sm2cipherkey.dat"

#ifdef UNIX
#include "pthread.h"
#else
#include <windows.h>
#define	pthread_mutex_t CRITICAL_SECTION
extern void pthread_mutex_lock(pthread_mutex_t *t);
extern void pthread_mutex_unlock(pthread_mutex_t *t);
extern void sleep(int sec);
#endif

#endif	// __DEVTEST_DEFINE_H__

