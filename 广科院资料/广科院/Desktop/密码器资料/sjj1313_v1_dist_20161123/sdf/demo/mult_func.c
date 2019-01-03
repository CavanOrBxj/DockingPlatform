#include <malloc.h>
#include <memory.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "devdef.h"
#include "SDF.h"
extern unsigned int *hDeviceHandle;


//pthread_mutex_t g_prepare_mutex;

unsigned char		g_input[8192], g_out[8192], g_check[8192];
unsigned int		g_inlen, g_outlen, g_checklen;
unsigned int		g_inlen1, g_outlen1, g_checklen1;

// RSA
RSArefPrivateKey	g_rsa_pri;
RSArefPublicKey		g_rsa_pub;
extern unsigned int		g_iModuls;
extern int		g_sym_index;
extern int		g_rsa_index;
extern int		g_sm2_index;

// SM2
ECCrefPrivateKey	g_sm2_pri;
ECCrefPublicKey		g_sm2_pub;
ECCSignature		g_sm2_sign;
ECCCipher			g_sm2_cipher;
// SM4
void				*g_keyhandle = NULL;
unsigned char		g_sm4_key[16] = { 0 };//{0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};

extern int					g_encdec;  //enc dec
extern int					g_algmod;  //ecb cbc mac || eia eea
extern int					g_inoutkey; //inkey outkey
// 产生随机数
int task_Random_Gen	(unsigned int *session, unsigned int dataLen)
{
	// 随机数长度，默认为1024字节
	dataLen = dataLen <= 0 ? 1024:dataLen;

	return SDF_GenerateRandom(session, dataLen, g_out);
}

// 产生RSA密钥对
int task_RSA_Gen	(unsigned int *session, unsigned int modules)
{
	// 如果modules参数错误，默认为1024比特
	modules = ( modules != 1024 && modules != 2048 ) ? 1024:modules;

	return SDF_GenerateKeyPair_RSA(session, modules, &g_rsa_pub, &g_rsa_pri);
}

// RSA 内部公钥运算
int task_RSAIndex_Public(unsigned int *session)
{
	
	if ( g_iModuls != 1024 && g_iModuls != 2048 )
		return -1;
	
	g_inlen = (g_iModuls+7)/8;

	return SDF_InternalPublicKeyOperation_RSA(session, g_rsa_index, g_input, g_inlen, g_out, &g_outlen);
}

// RSA 内部私钥运算
int task_RSAIndex_Private(unsigned int *session)
{
	int rv;
	if ( g_iModuls != 1024 && g_iModuls != 2048 )
		return -1;

	g_inlen = (g_iModuls+7)/8;

	rv = SDF_GetPrivateKeyAccessRight_Ex(session, g_rsa_index, 1, (unsigned char*)"12345678", 8);
	if ( rv )
		return rv;

	return SDF_InternalPrivateKeyOperation_RSA(session, g_rsa_index, g_input, g_inlen, g_out, &g_outlen);
}

// RSA私钥运算
int task_RSA_Private(unsigned int *session)
{
	if ( g_rsa_pri.bits != 1024 && g_rsa_pri.bits != 2048 )
		return -1;
	else
		g_inlen = (g_rsa_pri.bits+7)/8;

	if(g_inoutkey == 0) //outkey
		return SDF_ExternalPrivateKeyOperation_RSA(session, &g_rsa_pri, g_input, g_inlen, g_out, &g_outlen);
	else if(g_inoutkey == 1)
	{
		return task_RSAIndex_Private(session);
	}
	return 0;
}

// RSA公钥运算
int task_RSA_Public	(unsigned int *session)
{
	if ( g_rsa_pri.bits != 1024 && g_rsa_pri.bits != 2048 )
		return -1;
	else
		g_inlen = (g_rsa_pri.bits+7)/8;

	if(g_inoutkey == 0)
		return SDF_ExternalPublicKeyOperation_RSA(session, &g_rsa_pub, g_input, g_inlen, g_out, &g_outlen);
	else if(g_inoutkey == 1)
	{
		return task_RSAIndex_Public(session);
	}

	return 0;
}

// 产生SM2密钥对
int task_SM2_Gen(unsigned int *session)
{
	return SDF_GenerateKeyPair_ECC(session, PARAID, 256, &g_sm2_pub, &g_sm2_pri);
}

// SM2 内部密钥签名
int task_SM2Index_Sign(unsigned int *session)
{	
	int rv;

	g_inlen = 32;
	rv = SDF_GetPrivateKeyAccessRight_Ex(session, g_sm2_index, 2, (unsigned char*)"12345678", 8);
	if ( rv )
	{
		printf("SDF_GetPrivateKeyAccessRight return error: %d\n", rv);
		return rv;
	}
	
	rv = SDF_InternalSign_ECC(session, g_sm2_index, g_input, g_inlen, &g_sm2_sign);

	return rv;
}

// SM2签名
int task_SM2_Sign(unsigned int *session)
{
	if (g_inoutkey == 0)
	{
		if (g_sm2_pri.bits != 256)
			return -1;
		else
			g_inlen = (g_sm2_pri.bits + 7) / 8;
		return SDF_ExternalSign_ECC(session, PARAID, &g_sm2_pri, g_input, g_inlen, &g_sm2_sign);
	}
	else
	{
		return task_SM2Index_Sign(session);
	}

	return 0;
}

// SM2验证签名
int task_SM2Index_Verify(unsigned int *session)
{
	int rv;

	g_inlen = 32;
	rv = SDF_InternalVerify_ECC(session, g_sm2_index, g_input, g_inlen, &g_sm2_sign);
	return rv;
}

// SM2验证签名
int task_SM2_Verify(unsigned int *session)
{
	if ( g_sm2_pub.bits != 256 ) 
		return -1;
	else
		g_inlen = (g_sm2_pub.bits+7)/8;

	if(g_inoutkey == 0)
		return SDF_ExternalVerify_ECC(session, PARAID, &g_sm2_pub, g_input, g_inlen, &g_sm2_sign);
	else if(g_inoutkey == 1)
	{
		return task_SM2Index_Verify(session);
	}

	return 0;
}

// SM2加密
int task_SM2_Encrypt(unsigned int *session)
{
	if ( g_sm2_pub.bits != 256 ) 
		return -1;
	else
		g_inlen = (g_sm2_pub.bits+7)/8;

	return SDF_ExternalEncrypt_ECC(session, PARAID, &g_sm2_pub, g_input, g_inlen, &g_sm2_cipher);
}

// SM2解密
int task_SM2_Decrypt(unsigned int *session)
{
	if ( g_sm2_pri.bits != 256 ) 
		return -1;
	else
		g_inlen = (g_sm2_pri.bits+7)/8;

	return SDF_ExternalDecrypt_ECC(session, PARAID, &g_sm2_pri, &g_sm2_cipher, g_out, &g_outlen);
}

// SM4加密
int task_SM4_Encrypt(unsigned int *session, unsigned char *input, unsigned int dataLen, unsigned char *check)
{
	int	rv, i;
	unsigned char output[8192], iv[16];
	unsigned int outlen;
	unsigned int *head32;
	unsigned int algmode;
	dataLen = ( dataLen <= 0 ? 1024:dataLen );

	head32 = (unsigned int *)output;
	if ( g_keyhandle == NULL )
		return 0x1234ABCD;

	for (i = 0; i<16; i++)
		iv[i] = 0;

	switch(g_algmod)
	{
	case 0:
		algmode = SGD_SM4_ECB;
		break;
	case 1:
		algmode = SGD_SM4_CBC;
		break;
	case 2:
		algmode = SGD_SM4_MAC;
		break;
	default:
		return -1;
	}

	if(g_encdec == 0)
		rv = SDF_Encrypt(session, g_keyhandle, algmode, iv, input,  dataLen, output, &outlen);
	else
		rv = SDF_Decrypt(session, g_keyhandle, algmode, iv, input,  dataLen, output, &outlen);

	if( rv != 0)
		return rv;

	if(0 != memcmp(output, check, dataLen))
		return 0xABCD1234;
	
	return 0;
}

// SM1加密
int task_SM1_OFB(unsigned int *session, unsigned char *input, unsigned int dataLen, unsigned char *check)
{
	unsigned int i;
	int	rv;
	unsigned char output[8192];
	unsigned char iv[16];
	unsigned int outlen= 8192;
	unsigned int *head32;
	dataLen = ( dataLen <= 0 ? 1024:dataLen );

	for(i=0; i<16; i++)
		iv[i] = i;

	head32 = (unsigned int *)output;
	if ( g_keyhandle == NULL )
		return 0x1234ABCD;

	rv = SDF_Encrypt(session, g_keyhandle, SGD_SM1_OFB_OX, iv, input,  dataLen, output, &outlen);
	if( rv != 0)
		return rv;
	
	if(0 != memcmp(output, check, dataLen))
		return 0xABCD1234;
	
	return 0;
}

// 3DES加密
int task_3DES_Encrypt(unsigned int *session, unsigned char *input, unsigned int dataLen, unsigned char *check)
{
	int	rv;
	unsigned char output[8192];
	unsigned int outlen = 8192;
	unsigned int *head32;
	unsigned int algmode;

	dataLen = ( dataLen <= 0 ? 1024:dataLen );

	head32 = (unsigned int *)output;
	if ( g_keyhandle == NULL )
		return 0x1234ABCD;


	switch(g_algmod)
	{
	case 0:
		algmode = SGD_3DES_ECB;
		break;
	case 1:
		algmode = SGD_3DES_CBC;
		break;
	default:
		return -1;
	}

	if(g_encdec == 0)
		rv = SDF_Encrypt(session, g_keyhandle, algmode, NULL, input,  dataLen, output, &outlen);
	else
		rv = SDF_Decrypt(session, g_keyhandle, algmode, NULL, input,  dataLen, output, &outlen);

	if( rv != 0)
		return rv;

	if(0 != memcmp(output, check, dataLen))
		return 0xABCD1234;

	return 0;
}

int task_SSF33_Encrypt(unsigned int *session, unsigned char *input, unsigned int dataLen, unsigned char *check)
{
	int	rv, i;
	unsigned char output[8192], iv[16];
	unsigned int outlen = 8192;
	unsigned int *head32;
	unsigned int algmode;
	dataLen = (dataLen <= 0 ? 1024 : dataLen);

	head32 = (unsigned int *)output;
	if (g_keyhandle == NULL)
		return 0x1234ABCD;

	for(i=0; i<16; i++)
		iv[i] = i;

	switch (g_algmod)
	{
	case 0:
		algmode = SGD_SSF33_ECB;
		break;
	case 1:
		algmode = SGD_SSF33_CBC;
		break;
	case 2:
		algmode = SGD_SSF33_MAC;
		break;
	default:
		return -1;
	}

	if (g_encdec == 0)
		rv = SDF_Encrypt(session, g_keyhandle, algmode, iv, input, dataLen, output, &outlen);
	else
		rv = SDF_Decrypt(session, g_keyhandle, algmode, iv, input, dataLen, output, &outlen);

	if (rv != 0)
		return rv;

	if(0 != memcmp(output, check, dataLen))
		return 0xABCD1234;
	
	return 0;
}

// SM1加密
int task_SM1_Encrypt(unsigned int *session, unsigned char *input, unsigned int dataLen, unsigned char *check)
{
	int	rv, i;
	unsigned char output[8192];
	unsigned int outlen = 8192;
	unsigned int *head32;
	unsigned int algmode;
	unsigned char iv[16];
	dataLen = (dataLen <= 0 ? 1024 : dataLen);

	head32 = (unsigned int *)output;
	if (g_keyhandle == NULL)
		return 0x1234ABCD;

	for (i = 0; i<16; i++)
		iv[i] = i;

	switch (g_algmod)
	{
	case 0:
		algmode = SGD_SM1_ECB;
		break;
	case 1:
		algmode = SGD_SM1_CBC;
		break;
	case 2:
		algmode = SGD_SM1_MAC;
		break;
	default:
		return -1;
	}

	if (g_encdec == 0)
		rv = SDF_Encrypt(session, g_keyhandle, algmode, iv, input, dataLen, output, &outlen);
	else
		rv = SDF_Decrypt(session, g_keyhandle, algmode, iv, input, dataLen, output, &outlen);
	if (rv != 0)
		return rv;

	if(0 != memcmp(output, check, dataLen))
		return 0xABCD1234;
	
	return 0;
}

// SM3算法
int task_SM3_Encrypt(unsigned int *session, unsigned int dataLen)
{
	int rv;

	dataLen = (dataLen <= 0) ? 1024 : dataLen;
	rv = SDF_HashInit(session, SGD_SM3, NULL, NULL, 0);
	if(rv)
		return rv;

	rv = SDF_HashUpdate(session, g_input, dataLen);
	if(rv)
		return rv;

	rv = SDF_HashFinal(session, g_out, &g_outlen);

	return rv;
}

int task_ZUC(unsigned int *session, unsigned char *input, unsigned int inlen, unsigned char *check)
{
	unsigned char output[8192];
	unsigned char iv[16];
	int i;
	unsigned int algmode;

	for(i=0; i<16; i++)
		iv[i] = i;

	inlen = ( inlen <= 0 ) ? 1024*8:(inlen+7)/8 ;

	switch(g_algmod)
	{
	case 0:
		algmode = SGD_ZUC_EEA;
		break;
	case 1:
		algmode = SGD_ZUC_EIA;
		break;
	default:
		return -1;
	}

	SDF_ZucInit(session, algmode, g_keyhandle, iv, input, inlen, output);
	SDF_ZucFinal(session);

	if(0 != memcmp(output, check, inlen))
		return 0xABCD1234;
	
	return 0;
}

int task_Data_Prepare_Cmp(unsigned int *phSessionHandle, unsigned int sel, unsigned char *input, unsigned int inlen, unsigned char *check)
{
	int rv = 0, i;
	unsigned int checklen = inlen;

	unsigned char tmp[16*1024];
	unsigned int tmplen = 16*1024, algmode;

	unsigned char iv[16];
	for(i=0; i<16; i++)
		iv[i] = 0;
/*
#ifndef UNIX
	InitializeCriticalSection(&g_prepare_mutex);
#endif
	pthread_mutex_lock(&g_prepare_mutex);
*/
	switch( sel )
	{		
		case 10:
			switch (g_algmod)
			{
			case 0:
				algmode = SGD_SM4_ECB;
				break;
			case 1:
				algmode = SGD_SM4_CBC;
				break;
			case 2:
				algmode = SGD_SM4_MAC;
				break;
			default:
				return -1;
			}

			if (g_inoutkey == 0)
			{
				rv = SDF_ImportKey(phSessionHandle, g_sm4_key, 16, &g_keyhandle);
				if (rv != 0)
					break;
			}
			else
				g_keyhandle = &g_sym_index;

			rv = SDF_Encrypt(phSessionHandle, g_keyhandle, algmode, iv, input, inlen, check, &checklen);
			if(rv != 0)
				break;

			for(i=0; i<16; i++)
				iv[i] = 0;
			rv = SDF_Decrypt(phSessionHandle, g_keyhandle, algmode, iv, check, checklen, tmp, &tmplen);
			if(rv != 0)
				break;
			if(0 != memcmp(input, tmp, inlen))
			{
				rv = 0xeeeeee11;
			}
			break;

		case 11:
			switch (g_algmod)
			{
			case 0:
				algmode = SGD_SM1_ECB;
				break;
			case 1:
				algmode = SGD_SM1_CBC;
				break;
			case 2:
				algmode = SGD_SM1_MAC;
				break;
			default:
				return -1;
			}
			if (g_inoutkey == 0)
			{
				rv = SDF_ImportKey(phSessionHandle, g_sm4_key, 16, &g_keyhandle);
				if (rv != 0)
					break;
			}
			else
				g_keyhandle = &g_sym_index;

			rv = SDF_Encrypt(phSessionHandle, g_keyhandle, algmode, iv, input, inlen, check, &checklen);
			if(rv != 0)
				break;
			for(i=0; i<16; i++)
				iv[i] = i;
			rv = SDF_Decrypt(phSessionHandle, g_keyhandle, algmode, iv, check, checklen, tmp, &tmplen);
			if(rv != 0)
				break;
			if(0 != memcmp(input, tmp, inlen))
			{
				rv = 0xeeeeee11;
			}

			break;
		case 12:
			rv = SDF_ImportKey(phSessionHandle, g_sm4_key, 16, &g_keyhandle);
			if(rv != 0)
				break;
			rv = SDF_Encrypt(phSessionHandle, g_keyhandle, SGD_SM1_OFB_OX, iv, input, inlen, check, &checklen);
			if(rv != 0)
				break;
			for(i=0; i<16; i++)
				iv[i] = i;
			rv = SDF_Decrypt(phSessionHandle, g_keyhandle, SGD_SM1_OFB_OX, iv, check, checklen, tmp, &tmplen);
			if(rv != 0)
				break;
			if(0 != memcmp(input, tmp, inlen))
			{
				rv = 0xeeeeee11;
			}
			break;
		case 14:
			switch (g_algmod)
			{
			case 0:
				algmode = SGD_3DES_ECB;
				break;
			case 1:
				algmode = SGD_3DES_CBC;
				break;
			default:
				return -1;
			}
			rv = SDF_ImportKey(phSessionHandle, g_sm4_key, 16, &g_keyhandle);
			if(rv != 0)
				break;
			rv = SDF_Encrypt(phSessionHandle, g_keyhandle, algmode, iv, input, inlen, check, &checklen);
			if(rv != 0)
				break;
			for(i=0; i<16; i++)
				iv[i] = i;
			rv = SDF_Decrypt(phSessionHandle, g_keyhandle, algmode, iv, check, checklen, tmp, &tmplen);
			if(rv != 0)
				break;
			if(0 != memcmp(input, tmp, inlen))
			{
				rv = 0xeeeeee11;
			}

			break;
		case 15:
			switch (g_algmod)
			{
			case 0:
				algmode = SGD_ZUC_STREAM;
				break;
			case 1:
				algmode = SGD_ZUC_EEA;
				break;
			case 2:
				algmode = SGD_ZUC_EIA;
				break;
			default:
				return -1;
			}
			rv = SDF_ImportKey(phSessionHandle, g_sm4_key, 16, &g_keyhandle);
			if(rv != 0)
				break;

			SDF_ZucInit(phSessionHandle, algmode, g_keyhandle, iv, input, inlen, check);
			SDF_ZucFinal(phSessionHandle);
			for(i=0; i<16; i++)
				iv[i] = i;
			SDF_ZucInit(phSessionHandle, algmode, g_keyhandle, iv, check, inlen, tmp);
			SDF_ZucFinal(phSessionHandle);

			if(0 != memcmp(input, tmp, (inlen+7)/8))
			{
				rv = 0xeeeeee11;
			}
			break;
		case 16:
			switch (g_algmod)
			{
			case 0:
				algmode = SGD_SSF33_ECB;
				break;
			case 1:
				algmode = SGD_SSF33_CBC;
				break;
			case 2:
				algmode = SGD_SSF33_MAC;
				break;
			default:
				return -1;
			}
			rv = SDF_ImportKey(phSessionHandle, g_sm4_key, 16, &g_keyhandle);
			if(rv != 0)
				break;
			rv = SDF_Encrypt(phSessionHandle, g_keyhandle, algmode, iv, input, inlen, check, &checklen);
			if(rv != 0)
				break;
			for(i=0; i<16; i++)
				iv[i] = i;
			rv = SDF_Decrypt(phSessionHandle, g_keyhandle, algmode, iv, check, checklen, tmp, &tmplen);
			if(rv != 0)
				break;
			if(0 != memcmp(input, tmp, inlen))
			{
				rv = 0xeeeeee11;
			}
			break;
		case 17:
			rv = SDF_ImportKey(phSessionHandle, g_sm4_key, 16, &g_keyhandle);
			if (rv != 0)
				break;
			rv = SDF_Encrypt(phSessionHandle, g_keyhandle, SGD_SM7_ECB, NULL, input, inlen, check, &checklen);
			if (rv != 0)
				break;
			for (i = 0; i<16; i++)
				iv[i] = i;
			rv = SDF_Decrypt(phSessionHandle, g_keyhandle, SGD_SM7_ECB, NULL, check, checklen, tmp, &tmplen);
			if (rv != 0)
				break;
			if (0 != memcmp(input, tmp, inlen))
			{
				rv = 0xeeeeee11;
			}
			break;
		case 18:
			rv = SDF_ImportKey(phSessionHandle, g_sm4_key, 16, &g_keyhandle);
			if (rv != 0)
				break;
			rv = SDF_Encrypt(phSessionHandle, g_keyhandle, SGD_SM7_OFB, iv, input, inlen, check, &checklen);
			if (rv != 0)
				break;
			break;
		default:
			rv = -1;
			break;
	}


	if ( rv ) {
		return rv;
	}

	return rv ;
}

int task_Data_Preparation( unsigned int sel, unsigned int len)
{
	int rv = 0;
	unsigned int *phSessionHandle = NULL;
	//RSArefPublicKey rsa_pub;

	rv = SDF_OpenSession(hDeviceHandle, (void **)&phSessionHandle);
	if ( rv ) {
		fprintf(stdout, "SDF_OpenSession error. ret=[0x%08x]. \n\n", rv );
		return rv;
	}

	switch ( sel ) 
	{
	case 1: // 随机数（128M）
		break;
	case 2: // RSA 密钥产生
		break;
	case 3: // RSA 私钥运算
		if (g_inoutkey == 1)
			rv = task_RSA_Gen(phSessionHandle, len);
		break;
	case 4: // RSA 公钥运算
		if (g_inoutkey == 1)
			rv = task_RSA_Gen(phSessionHandle, len);
		break;
	case 5: // SM2 密钥产生
		break;
	case 6: // SM2 签名
		if(g_inoutkey == 0)
			rv = task_SM2_Gen(phSessionHandle); 
		break;
	case 7: // SM2 验签
		if(g_inoutkey == 0)
		{
			rv |= task_SM2_Gen(phSessionHandle); 
			rv |= task_SM2_Sign(phSessionHandle);
		}
		else
		{
			rv = task_SM2_Gen(phSessionHandle); 
			rv = task_SM2_Sign(phSessionHandle);
		}
		break;
	case 8: // SM2 加密
		if(g_inoutkey == 0)
			rv = task_SM2_Gen(phSessionHandle); 
		break;
	case 9: // SM2 解密
		if(g_inoutkey == 0)
		{
			rv |= task_SM2_Gen(phSessionHandle); 
			rv |= task_SM2_Encrypt(phSessionHandle);
		}
		else
		{
			rv = task_SM2_Gen(phSessionHandle);
			rv = task_SM2_Encrypt(phSessionHandle);
		}
		break;
	case 13: // SM3 加密
		break;
	default:
		return -1;
	}
	if ( rv ) {
		fprintf(stdout, "task_Data_Preparation error. ret=[0x%08x]. \n\n", rv );
		return rv;
	}

	//SDF_CloseSession(phSessionHandle);

	return rv ;
}

// SM7加密
int task_SM7_Encrypt(unsigned int *session, unsigned char *input, unsigned int dataLen, unsigned char *check)
{
	int	rv, i;
	unsigned char output[8192];
	unsigned int outlen = 8192;
	unsigned int *head32;
	unsigned char iv[16];
	dataLen = (dataLen <= 0 ? 1024 : dataLen);

	head32 = (unsigned int *)output;
	if (g_keyhandle == NULL)
		return 0x1234ABCD;

	for (i = 0; i<16; i++)
		iv[i] = i;

	if (g_encdec == 0)
		rv = SDF_Encrypt(session, g_keyhandle, SGD_SM7_ECB, iv, input, dataLen, output, &outlen);
	else
		rv = SDF_Decrypt(session, g_keyhandle, SGD_SM7_ECB, iv, input, dataLen, output, &outlen);
	if (rv != 0)
		return rv;

	if (0 != memcmp(output, check, dataLen))
		return 0xABCD1234;

	return 0;
}


// SM1加密
int task_SM7_OFB(unsigned int *session, unsigned char *input, unsigned int dataLen, unsigned char *check)
{
	unsigned int i;
	int	rv;
	unsigned char output[8192];
	unsigned char iv[16];
	unsigned int outlen = 8192;
	unsigned int *head32;
	dataLen = (dataLen <= 0 ? 1024 : dataLen);

	for (i = 0; i<16; i++)
		iv[i] = i;

	head32 = (unsigned int *)output;
	if (g_keyhandle == NULL)
		return 0x1234ABCD;

	rv = SDF_Encrypt(session, g_keyhandle, SGD_SM7_OFB, iv, input, dataLen, output, &outlen);
	if (rv != 0)
		return rv;

	if (0 != memcmp(output, check, dataLen))
		return 0xABCD1234;

	return 0;
}
