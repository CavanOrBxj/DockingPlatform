#include <malloc.h>
#include <memory.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#elif UNIX
#include <error.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#include "SDF.h"
#include "devdef.h"

#define bool int
#define true 1
#define false 0

void PrintBuf( char *title, unsigned char *buf, int buflen);
int readFile( char *fname, unsigned char *readbuf, int *buflen ); 
int readFileString( char *fname, unsigned char *readbuf, int *buflen ); 
int writeFile( char *fname, unsigned char *writebuf, int buflen ); 

int TestSm3Hash( void *hSessionHandle, ECCrefPublicKey *pucPublicKey, 
	unsigned char *pucUserid, int iUseridLen,
	unsigned char *pucData, int iDataLen,
	unsigned char *pucHash, int *piHashLen );
int TestGenRandomData( void *hSessionHandle, int randlen, unsigned char *randdata );


void T_Sm1( void *hSessionHandle );
void T_Sm2( void *hSessionHandle );
void T_Sm3( void *hSessionHandle );
void T_Sm4( void *hSessionHandle );
void T_Sm7(void *hSessionHandle);
void T_DES( void *hSessionHandle );
void T_SSF33( void *hSessionHandle );
void T_Random( void *hSessionHandle );

void T_ImportKeyPair( void *hSessionHandle );
void T_ExportKeyPair( void *hSessionHandle );
void T_Rsa( void *hSessionHandle );
void T_Exchange(void *hSessionHandle );
void T_File(void *hSessionHandle );
void T_DevInfo(void *hSessionHandle );
void T_GetKeyInfo(void *hSessionHandle );

void T_ZUC( void *hSessionHandle );

int main(void)
{
	int rv, sel;

	unsigned int *hDeviceHandle = NULL;
	unsigned int *hSessionHandle = NULL;

	rv = SDF_OpenDevice((void **)&hDeviceHandle);
	if (rv != SDR_OK)
	{
		printf("SDF_OpenDevice Failed!!! Error: %#x! DeviceHandle: %08x\r\n", rv, *hDeviceHandle);
		return -1;
	}
	else
		printf("SDF_OpenDevice success.\r\n");

	rv = SDF_OpenSession(hDeviceHandle,(void **)&hSessionHandle);
	if (rv != SDR_OK)
	{
		printf("SDF_OpenSession Failed!!! Error: %#x!\r\n", rv);
		return -1;
	}
	else
		printf("SDF_OpenSession success.\r\n");	

	/*
	DEVICEINFO devinfo;
	rv = SDF_GetDeviceInfo(hSessionHandle, &devinfo);
	if ( rv ) {
		printf("SDF_GetDeviceInfo Failed!!! Error: %#x!\r\n", rv);
		return ;
	}

	printf("IssuerName %s\n", devinfo.IssuerName);
	printf("DeviceName %s\n", devinfo.DeviceName);
	printf("DeviceSerial %s\n", devinfo.DeviceSerial);
	printf("DeviceVersion %d\n", devinfo.DeviceVersion);
	printf("StandardVersion %d\n", devinfo.StandardVersion);
	printf("AsymAlgAbility[0] %d\n", devinfo.AsymAlgAbility[0]);
	printf("AsymAlgAbility[1] %d\n", devinfo.AsymAlgAbility[1]);
	printf("SymAlgAbility %d\n", devinfo.SymAlgAbility);
	printf("HashAlgAbility %d\n", devinfo.HashAlgAbility);
	printf("BufferSize %d\n", devinfo.BufferSize);
	*/
	printf("SDF Initialized success.\r\n\r\n");	
	printf("**************************************************************************\r\n\r\n");

	for ( ; ; )
	{
		printf( "------------- Test Ccs Functions ------------\n" );
		printf( "|                                           |\n" );
		printf( "|        1.  SM1 Algorithm Test.            |\n" );
		printf( "|        2.  SM2 Algorithm Test.            |\n" );
		printf( "|        3.  SM3 Algorithm Test.            |\n" );
		printf( "|        4.  SM4 Algorithm Test.            |\n" );
		printf( "|        5.  Random Data Test.              |\n" );
		printf( "|        6.  RSA Algorithm Test.            |\n" );
		printf( "|        7.  Exchange Session Key Test.     |\n" );
		printf( "|        8.  The File read and write Test.  |\n" );
		printf( "|        9.  Get Device Information Test.   |\n" );
		printf( "|        10.  Get Key Info.                 |\n" );
		printf( "|        11.  SSF33    Algorithm Test.      |\n" );
		printf( "|        12.  ZUC      Algorithm Test.      |\n" );
		printf( "|        13.  Import Key or Key Pair Test.  |\n" );
		printf( "|        14.  Export Key or Key Pair Test.  |\n" );
		printf( "|        15.  DES/3DES Algorithm Test.      |\n" );
		printf( "|        16.  SM7 Algorithm Test.           |\n" );
		printf( "|                                           |\n" );
		printf( "|        0.  Exit.                          |\n" );
		printf( "|                                           |\n" );
		printf( "---------------------------------------------\n" );
		printf( "\nPlease Select:" );
		scanf( "%d", &sel );

		switch( sel )
		{
		case 1:		// SM1 Algorithm Test
			T_Sm1( hSessionHandle );
			break;
		case 2:		// SM2 Algorithm Test
			T_Sm2( hSessionHandle );
			break;
		case 3:		// SM3 Algorithm Test
			T_Sm3( hSessionHandle );
			break;
		case 4:		// SM4 Algorithm Test
			T_Sm4( hSessionHandle );
			break;
		case 5:		// Random Dat Test
			T_Random( hSessionHandle );
			break;
		case 6:		// RSA  Test
			T_Rsa( hSessionHandle );
			break;
		case 7:		// 
			T_Exchange( hSessionHandle );
			break;
		case 8:		// 
			T_File( hSessionHandle );
			break;
		case 9:		// 
			T_DevInfo( hSessionHandle );
			break;
		case 10:		// 
			T_GetKeyInfo( hSessionHandle );
			break;
		case 11:
			T_SSF33( hSessionHandle );
			break;
		case 12:
			T_ZUC( hSessionHandle );
			break;
		case 13:		// 
			T_ImportKeyPair( hSessionHandle );
			break;
		case 14:		// 
			T_ExportKeyPair( hSessionHandle );
			break;
		case 15:
			T_DES( hSessionHandle );
			break;
		case 16:
			T_Sm7(hSessionHandle);
			break;
		case 0:		// 
			SDF_CloseSession( hSessionHandle );
			SDF_CloseDevice( hDeviceHandle );
			printf( "Test Finished.\n" );
			return -1;
		default:
			printf( "Invalid Input, Press <Enter> Key to Continue...\n" );
			break;
		}
		getchar();
		getchar();
	}

	return 0;
}

void T_ExportKeyPair(void *hSessionHandle)
{
	int sel, rv, index;
	unsigned char symmkey[128];
	unsigned int symmkeylen = 128;
	for(;;)
	{
		printf( "\n------------- Test Import Functions --------------\n" );
		printf( "|      1.  Export Symmetrical Key                  |\n" );
		printf( "|                                                  |\n" );
		printf( "|      0.  Return.                                 |\n" );
		printf( "----------------------------------------------------\n" );
		printf( "\nPlease Select:" );
		scanf("%d", &sel);
		switch( sel )
		{
		case 1:
			printf("Please input the key index that you want to export:  ");
			scanf("%d", &index);
			if(index <= 0 || index > 128){
				printf("key index is out of limition.\n");
				break;
			}

			rv = SDF_ExportSymmKey_Ex(hSessionHandle, index, symmkey, &symmkeylen);
			if ( rv )
			{
				printf( "Export Symmetrical Key at index %d Failed, 0x%08X.\n", index, rv );
				return;
			}
			printf( "Export Symmetrical Key at index %d tOKOK.\n\n", index);

			PrintBuf("Symm Key", symmkey, symmkeylen);

			writeFile(FNAME_SM1KEY, symmkey, symmkeylen);

			break;
		case 0:	
			return;
		}
	}
}

void T_ImportKeyPair(void *hSessionHandle)
{
	int sel, rv, len, index, type;
	unsigned char tmpbuf[8192], enckey[1024], encryptedkey[1024];
	ECCrefPublicKey sm2pubkey;
	ECCrefPrivateKey sm2prikey;
	RSArefPublicKey rsapubkey;
	RSArefPrivateKey rsaprikey;

	unsigned char sm1key[16];
	void *hKeyHandle;
	unsigned int sm1keylen = 16;
	ECCCipher sm2Cipher;

	memset(&sm2pubkey, 0, sizeof(ECCrefPublicKey));
	memset(&sm2prikey, 0, sizeof(ECCrefPrivateKey));
	memset(&rsapubkey, 0, sizeof(RSArefPublicKey));
	memset(&rsaprikey, 0, sizeof(RSArefPrivateKey));
	for(;;)
	{
		printf( "\n------------- Test Import Functions --------------\n" );
		printf( "|                                                  |\n" );
		printf( "|      1.  Import RSA Key Pair.                    |\n" );
		printf( "|      2.  Import SM2 Key Pair.                    |\n" );
		printf( "|      3.  Import SM2 Key Pair Encrypted by SM1.   |\n" );
		printf( "|      4.  Import Symmetrical Key with a Tag.      |\n" );
		printf( "|                                                  |\n" );
		printf( "|      0.  Return.                                 |\n" );
		printf( "----------------------------------------------------\n" );
		printf( "\nPlease Select:" );
		scanf( "%d", &sel );

		switch( sel )
		{
		case 1:
			len = 8192;
			readFile( FNAME_RSAPUBKEY, tmpbuf, &len );
			memcpy(&rsapubkey, tmpbuf , len);
			
			len = 8192;
			readFile( FNAME_RSAPRIKEY, tmpbuf, &len );
			memcpy(&rsaprikey, tmpbuf, len);

			printf("Please input key type: 1 signatue key, 2 exchange key\n");
			scanf("%d", &type);
			if(type != 1 && type != 2){
				printf("key type is not in exception.\n");
				break;
			}

			(type == 1)? (type = SGD_RSA_SIGN_EX): (type = SGD_RSA_ENC_EX);

			printf("Please input key index:");
			scanf("%d", &index);
			if(index <= 0 || index > 16){
				printf("key index is out of limition.\n");
				break;
			}
			rv = SDF_ImportKeyPair_Ex(hSessionHandle, SGD_RSA, index, type, &rsaprikey,NULL, NULL);
			if ( rv )
			{
				printf( "Import RSA Key Pair Failed, 0x%08X.\n", rv );
				break;
			}
			printf("Import RSA Key Pair OKOK.\n\n");
			break;
		case 2:
			len = 1024;
			readFile( FNAME_SM2PUBKEY, tmpbuf, &len );
			memcpy(&sm2pubkey.x[32], tmpbuf , 32);
			memcpy(&sm2pubkey.y[32], &tmpbuf[32], 32);
			sm2pubkey.bits = 256;
			
			readFile( FNAME_SM2PRIKEY, tmpbuf, &len );
			memcpy(&sm2prikey.D[32], tmpbuf, 32);
			sm2prikey.bits = 256;

			printf("Please input key type. 1 signatue key, 2 exchange key:  ");
			scanf("%d", &type);
			if(type != 1 && type != 2){
				printf("key type is not in exception.\n");
				break;
			}

			(type == 1)? (type = SGD_SM2_1): (type = SGD_SM2_2);

			printf("Please input key index:  ");
			scanf("%d", &index);
			if(index <= 0 || index > 16){
				printf("key index is out of limition.\n");
				break;
			}
			rv = SDF_ImportKeyPair_Ex(hSessionHandle, SGD_SM2, index, type, NULL, &sm2pubkey, &sm2prikey);
			if ( rv )
			{
				printf( "Import SM2 Key Pair Failed, 0x%08X.\n", rv );
				break;
			}
			printf("Import SM2 Key Pair OKOK.\n\n");

			break;
		case 3:
			len = 1024;
			rv = readFile( FNAME_SM2PUBKEY, enckey, &len );
			if ( rv )
				break;
			rv = readFile( FNAME_SM2PRIKEY, &enckey[64], &len );
			if ( rv )
				break;
			rv = readFile( FNAME_SM1KEY, sm1key, &len);
			if ( rv )
				break;

			type = SGD_SM2_2;

			printf("Please input the key index that you want to import:  ");
			scanf("%d", &index);
			if(index <= 0 || index > 16){
				printf("key index is out of limition.\n");
				break;
			}

			printf("If encrypt the SM2 Public Key? 0-NO; 1-Yes\n");
			scanf("%d", &sel);
			if(sel != 0 && sel != 1){
				printf("The input number is not in expectation.\n");
				break;
			}

			rv = SDF_ImportKey( hSessionHandle, sm1key, sm1keylen, &hKeyHandle );
			if ( rv )
			{
				printf( "Import Session Key(SM1) Failed, 0x%08X.\n", rv );
				return;
			}
			printf( "Import Session Key(SM1) OKOK.\n\n" );

			if(sel == 1)
			{
				rv = SDF_Encrypt(hSessionHandle, hKeyHandle, SGD_SM1_ECB, NULL, enckey, 96, encryptedkey, (unsigned int *)&len);
			}
			else if(sel == 0)
			{
				memcpy(encryptedkey, enckey, 64);
				rv = SDF_Encrypt(hSessionHandle, hKeyHandle, SGD_SM1_ECB, NULL, &enckey[64], 32, &encryptedkey[64], (unsigned int *)&len);
				len += 64;
			}

			if ( rv )
			{
				printf( "Encrypt SM2 Key Pair with SM1 key Failed, 0x%08X.\n", rv );
				return;
			}
			printf( "Encrypt SM2 Key Pair with SM1 key OKOK.\n\n" );

			rv = SDF_ExportSignPublicKey_ECC(hSessionHandle, index, &sm2pubkey);
			if ( rv )
			{
				printf( "Export SM2 Public Key at index %d Failed, 0x%08X.\n", index, rv );
				return;
			}
			printf( "Export SM2 Public Key at index %d OKOK.\n\n", index );

			rv = SDF_ExternalEncrypt_ECC( hSessionHandle, PARAID, &sm2pubkey, 
				sm1key, sm1keylen, &sm2Cipher );
			if ( rv )
			{
				printf( "Encrypt symmetric key with SM2 external public key Failed, 0x%08X.\n", rv );
				return;
			}
			printf( "Encrypt symmetric key with SM2 external public key OKOK.\n\n");

			rv = S_ImportEncKeyPair_ECC(hSessionHandle, index, SGD_SM1_ECB, &sm2Cipher, encryptedkey, len, sel);
			if ( rv )
			{
				printf( "Import SM2 ENC KeyPair at index %d that Encrypted by SM1 Key Failed, 0x%08X.\n", index, rv );
				return;
			}
			printf( "Import SM2 ENC KeyPair at index %d that Encrypted by SM1 Key OKOK.\n\n", index);

			break;
		case 4:
			len = 1024;
			rv = readFile( FNAME_SM1KEY, sm1key, &len);
			if ( rv )
				break;

			printf("Please input the key index that you want to import:  ");
			scanf("%d", &index);
			getchar();
			if(index <= 0 || index > 128){
				printf("key index is out of limition.\n");
				break;
			}

			memset(tmpbuf, 0, 32);
			printf("Please input the key tag (1 - 32 bytes): ");
			fflush(stdin);
			gets((char *)tmpbuf);

			printf("Please choose a key type: 1-SM1, 2-SM4, 3-DES, 4-DES2, 5-DES3 ... ");
			scanf("%d", &type);

			switch(type)
			{
			case 1:
				type = 'P';
				break;
			case 2:
				type = 'R';
				break;
			case 3:
				type = 'X';
				break;
			case 4:
				type = 'Y';
				break;
			case 5:
				type = 'Z';
				break;
			}

			rv = SDF_ImportKey_Ex(hSessionHandle, index, type, sm1key, len, (char *)tmpbuf);
			if ( rv )
			{
				printf( "Import Symmetrical Key at index %d Failed, 0x%08X.\n", index, rv );
				return;
			}
			printf( "Import Symmetrical Key at index %d OKOK.\n\n", index);

			break;
		case 0:	
			return;
		}

		getchar();
	}
}

void T_Sm2( void *hSessionHandle )
{
	int sel, rv, len;
	ECCrefPublicKey sm2pubkey;
	ECCrefPrivateKey sm2prikey;
	ECCCipher sm2Cipher;
	ECCSignature sm2Signature;
	unsigned char plainbuf[MAX_DATA_LENGTH], tmpbuf[MAX_DATA_LENGTH+128];
	int plainlen, tmplen;
	int sm2index;
	char pwd[32];
	int index;

	for ( ; ; )
	{
		printf( "\n------------- Test SM2 Functions ------------\n" );
		printf( "|                                           |\n" );
		printf( "|      1.  Generate SM2 Key Pair.           |\n" );
		printf( "|      2.  SM2 Public Key Encryption.       |\n" );
		printf( "|      3.  SM2 Private Key Decryption.      |\n" );
		printf( "|      4.  SM2 Private Key Signature.       |\n" );
		printf( "|      5.  SM2 Public Key Sign-Verify.      |\n" );
		printf( "|                                           |\n" );
		printf( "|      6.  SM2 Export Sign Public Key.      |\n" );
		printf( "|      7.  SM2 Export Encrypt Public Key.   |\n" );
		printf( "|                                           |\n" );
		printf( "|      8.  SM2 index Key Signature.         |\n" );
		printf( "|      9.  SM2 index Key Sign-Verify.       |\n" );
		printf( "|      10.  SM2 index Key Decryption.       |\n" );
		printf( "|                                           |\n" );
		printf( "|      0.  Return.                          |\n" );
		printf( "|                                           |\n" );
		printf( "---------------------------------------------\n" );
		printf( "\nPlease Select:" );
		scanf( "%d", &sel );

		switch( sel )
		{
		case 1:		// Generate SM2 Key Pair
			rv = SDF_GenerateKeyPair_ECC( hSessionHandle, PARAID, 256, &sm2pubkey, &sm2prikey );
			if ( rv )
			{
				printf( "Generate SM2 Key Pair Failed, 0x%08X.\n", rv );
				break;
			}

			printf( "Generate SM2 Key Pair OKOK.\n\nbits = %d.\n\n", sm2pubkey.bits );

			PrintBuf( "pub_x", sm2pubkey.x, ECCref_MAX_LEN );
			PrintBuf( "pub_y", sm2pubkey.y, ECCref_MAX_LEN );
			PrintBuf( "pri_d", sm2prikey.D, ECCref_MAX_LEN );

			memcpy(tmpbuf, &sm2pubkey.x[32], 32);
			memcpy(&tmpbuf[32], &sm2pubkey.y[32], 32);
			writeFile( FNAME_SM2PUBKEY, tmpbuf, 64 );

			memcpy(tmpbuf, &sm2prikey.D[32], 32);
			writeFile( FNAME_SM2PRIKEY, tmpbuf, 32 );

			break;
		case 2:		// SM2 Public Key Encryption
			len = sizeof( sm2pubkey );
			memset( &sm2pubkey, 0x0, len );
			rv = readFile( FNAME_SM2PUBKEY, tmpbuf, &len );
			if ( rv )
				break;
			
			sm2pubkey.bits = 256;
			memcpy(&sm2pubkey.x[32], tmpbuf, 32);
			memcpy(&sm2pubkey.y[32], &tmpbuf[32], 32);

			plainlen = sizeof( plainbuf );

			memset( plainbuf, 0x0, plainlen );
			rv = readFile( FNAME_SM2PLAINDATA, plainbuf, &plainlen );
			if ( rv )
				break;

			PrintBuf( "plain data", plainbuf, plainlen );
			memset( &sm2Cipher, 0x0, sizeof(sm2Cipher) );
			rv = SDF_ExternalEncrypt_ECC( hSessionHandle, PARAID, &sm2pubkey, 
				plainbuf, plainlen, &sm2Cipher );
			if ( rv )
			{
				printf( "\nSM2 Public Key Encrypt Failed, 0x%08X.\n\n", rv );
				break;
			}
			printf( "\nSM2 Public Key Encrypt OKOK.\n\n" );
			PrintBuf( "cipher data", sm2Cipher.C, sm2Cipher.L );
			PrintBuf( "cipher  M", sm2Cipher.M, sizeof(sm2Cipher.M) );

			tmplen = sizeof(tmpbuf);
			memset(tmpbuf, 0, tmplen);

			memcpy(tmpbuf, &sm2Cipher.x[32], 32);
			memcpy(&tmpbuf[32], &sm2Cipher.y[32], 32);
			memcpy(&tmpbuf[64], sm2Cipher.C, sm2Cipher.L);
			memcpy(&tmpbuf[64 + sm2Cipher.L], &sm2Cipher.M, 32);
	
			writeFile( FNAME_SM2CIPHER, tmpbuf, 96+sm2Cipher.L);
			break;
		case 3:		// SM2 Private Key Decryption
			len = sizeof( sm2prikey );
			memset( &sm2prikey, 0x0, len );
			rv = readFile( FNAME_SM2PRIKEY, (unsigned char*)tmpbuf, &len );
			if ( rv )
				break;
			PrintBuf( "SM2 Private Key", tmpbuf, len );

			sm2prikey.bits = 256;
			memcpy(&sm2prikey.D[32], tmpbuf, 32);

			len = MAX_DATA_LENGTH+128;
			memset( &sm2Cipher, 0x0, sizeof(ECCCipher) );
			rv = readFile( FNAME_SM2CIPHER, (unsigned char*)tmpbuf, &len );
			if ( rv )
				break;
			PrintBuf( "SM2 ciphter data", tmpbuf, len );

			memcpy(&sm2Cipher.x[32], tmpbuf, 32);
			memcpy(&sm2Cipher.y[32], &tmpbuf[32], 32);
			memcpy(sm2Cipher.C, &tmpbuf[64], len-96);
			sm2Cipher.L = len-96;
			memcpy(sm2Cipher.M, &tmpbuf[64+sm2Cipher.L], 32);
			
			tmplen = sizeof( tmpbuf );
			memset(tmpbuf, 0, tmplen);
			rv = SDF_ExternalDecrypt_ECC( hSessionHandle, PARAID,
				&sm2prikey, &sm2Cipher, tmpbuf, (unsigned int*)&tmplen );
			if ( rv )
			{
				printf( "\nSM2 Private Key Decrypt Failed, 0x%08X.\n\n", rv );
				break;
			}
			printf( "\nSM2 Private Key Decrypt OKOK.\n\n" );
			PrintBuf( "data after decrypt", tmpbuf, tmplen );
			writeFile( FNAME_DECRYPTEDDATA, tmpbuf, tmplen );

			break;
		case 4:		// SM2 Private Key Signature
			len = sizeof( sm2prikey );
			memset( &sm2prikey, 0x0, len );
			rv = readFile( FNAME_SM2PRIKEY, (unsigned char*)tmpbuf, &len );
			if ( rv )
				break;

			memcpy(&sm2prikey.D[32], tmpbuf, 32);
			sm2prikey.bits = 256;

			plainlen = sizeof( plainbuf );
			memset( plainbuf, 0x0, plainlen );

			rv = readFile( FNAME_SM2PLAINDATA, plainbuf, &plainlen );
			if ( rv )
				break;
			PrintBuf( "plain data", plainbuf, plainlen );

			rv = SDF_ExternalSign_ECC( hSessionHandle, PARAID, 
				&sm2prikey, plainbuf, plainlen, &sm2Signature );
			if ( rv )
			{
				printf( "\nSM2 Private Key Sign Data Failed, 0x%08X.\n\n", rv );
				break;
			}
			printf( "\nSM2 Private Key Sign Data  OKOK.\n\n" );
			PrintBuf( "data's signature", (unsigned char*)&sm2Signature, sizeof(sm2Signature) );

			writeFile( FNAME_SM2SIGN, (unsigned char*)&sm2Signature, sizeof(sm2Signature) );

			break;
		case 5:		// SM2 Public Key Sign-Verify
			len = sizeof( sm2pubkey );
			memset( &sm2pubkey, 0x0, len );
			rv = readFile( FNAME_SM2PUBKEY, (unsigned char*)tmpbuf, &len );
			if ( rv )
				break;

			memcpy(&sm2pubkey.x[32], tmpbuf, 32);
			memcpy(&sm2pubkey.y[32], &tmpbuf[32], 32);

			plainlen = sizeof( plainbuf );
			memset( plainbuf, 0x0, plainlen );
			rv = readFile( FNAME_SM2PLAINDATA, plainbuf, &plainlen );
			if ( rv )
				break;
			PrintBuf( "plain data", plainbuf, plainlen );

			len = sizeof( sm2Signature );
			memset( &sm2Signature, 0x0, len );
			rv = readFile( FNAME_SM2SIGN, (unsigned char*)&sm2Signature, &len );
			if ( rv )
				break;

			PrintBuf( "data's signature", (unsigned char*)&sm2Signature, len );

			rv = SDF_ExternalVerify_ECC( hSessionHandle, PARAID,
				&sm2pubkey, plainbuf, plainlen, &sm2Signature );
			if ( rv )
			{
				printf( "\nSM2 Public Key Verify Data's Signature Failed, 0x%08X.\n\n", rv );
				break;
			}
			printf( "\nSM2 Public Key Verify Data's Signature OKOK.\n\n" );

			break;
		case 6:	
			printf( "Please Input SM2 Key Pair Index [ 1 - 16 ]: " );
			scanf( "%d", &sm2index );
			if ( 1 > sm2index || 16 < sm2index ) {
				printf( "\n The SM2 Key Pair Index[%d] invalid.\n\n", sm2index );
				break;
			}

			memset(&sm2pubkey, 0x0, sizeof(ECCrefPublicKey));
			rv = SDF_ExportSignPublicKey_ECC( hSessionHandle, sm2index, &sm2pubkey);
			if ( rv ) {
				printf( "\n SDF_ExportSignPublicKey_ECC error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nSM2 Export Encrypted Public Key Operation OKOK.\n\n" );

			PrintBuf( "PUB_X", sm2pubkey.x, ECCref_MAX_LEN);
			PrintBuf( "PUB_Y", sm2pubkey.y, ECCref_MAX_LEN);

			memcpy(tmpbuf, &sm2pubkey.x[32], 32);
			memcpy(&tmpbuf[32], &sm2pubkey.y[32], 32);
			writeFile( FNAME_SM2PUBKEY, tmpbuf, 64 );

			printf("\n\n");
			break;
		case 7:	
	
			printf( "Please Input SM2 Key Pair Index [ 1 - 16 ]: " );
			scanf( "%d", &sm2index );
			if ( 1 > sm2index || 16 < sm2index ) {
				printf( "\n The SM2 Key Pair Index[%d] invalid.\n\n", sm2index );
				break;
			}

			memset(&sm2pubkey, 0x0, sizeof(ECCrefPublicKey));
			rv = SDF_ExportEncPublicKey_ECC( hSessionHandle, sm2index, &sm2pubkey);
			if ( rv ) {
				printf( "\n SDF_ExportEncPublicKey_ECC error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nSM2 Export Encrypted Public Key Operation OKOK.\n\n" );

			PrintBuf( "PUB_X", sm2pubkey.x, ECCref_MAX_LEN);
			PrintBuf( "PUB_Y", sm2pubkey.y, ECCref_MAX_LEN);

			memcpy(tmpbuf, &sm2pubkey.x[32], 32);
			memcpy(&tmpbuf[32], &sm2pubkey.y[32], 32);
			writeFile( FNAME_SM2PUBKEY, tmpbuf, 64 );

			printf("\n\n");
			break;
		case 8:		

			printf( "Please Input Internal ECC Key Pair Index: " );
			scanf( "%d", &index );

			printf( "Please Input Internal Private Key PassWord: " );
			scanf( "%s", pwd );

			rv = SDF_GetPrivateKeyAccessRight_Ex(hSessionHandle, index, 2, (unsigned char*)pwd, strlen(pwd) );
			if ( rv ) {
				printf( "\nSDF_GetPrivateKeyAccessRight error. rv = 0x%08x. \n\n", rv );
				break;
			}

			plainlen = sizeof( plainbuf );
			memset( plainbuf, 0x0, plainlen );
			rv = readFile( FNAME_SM2PLAINDATA, plainbuf, &plainlen );
			if ( rv )
				break;
			PrintBuf( "plain data", plainbuf, plainlen );

			memset( &sm2Cipher, 0x0, sizeof(sm2Cipher) );
			rv = SDF_InternalSign_ECC( hSessionHandle, index, plainbuf, plainlen, &sm2Signature );
			if ( rv )
			{
				printf( "\nSM2 Public Key Encrypt Failed, 0x%08X.\n\n", rv );
				break;
			}

			SDF_ReleasePrivateKeyAccessRight(hSessionHandle, index);

			printf( "\nSM2 index Key Sign Data  OKOK.\n\n" );
			PrintBuf( "data's signature", (unsigned char*)&sm2Signature, sizeof(sm2Signature) );
			writeFile( FNAME_SM2SIGN, (unsigned char*)&sm2Signature, sizeof(sm2Signature) );

			break;
		case 9:		// 

			printf( "Please Input Internal ECC Key Pair Index: " );
			scanf( "%d", &index );

			len = sizeof( sm2Signature );
			memset( &sm2Signature, 0x0, len );
			rv = readFile( FNAME_SM2SIGN, (unsigned char*)&sm2Signature, &len );
			if ( rv )
				break;

			plainlen = sizeof( plainbuf );
			memset( plainbuf, 0x0, plainlen );
			rv = readFile( FNAME_SM2PLAINDATA, plainbuf, &plainlen );
			if ( rv )
				break;
			PrintBuf( "plain data", plainbuf, plainlen );

			tmplen = sizeof( tmpbuf );
			rv = SDF_InternalVerify_ECC( hSessionHandle, index, plainbuf, plainlen, &sm2Signature);
			if ( rv )
			{
				printf( "\nSM2 index Key verify Failed, 0x%08X.\n\n", rv );
				break;
			}
			printf( "\nSM2 index Key verify OKOK.\n\n" );

			break;
		case 10:
			printf("Please input key index[1-16]: ");
			scanf("%d", &index);

			printf( "Please Input Internal RSA Private Key PassWord: " );
			scanf( "%s", pwd );

			printf("Please select a private key. 0-sig key; 1-enc key: ");
			scanf("%d", &sel);

			rv = SDF_GetPrivateKeyAccessRight_Ex(hSessionHandle, index, 2, (unsigned char*)pwd, strlen(pwd) );
			if ( rv ) {
				printf( "\nSDF_GetPrivateKeyAccessRight error. rv = 0x%08x. \n\n", rv );
				break;
			}

			len = MAX_DATA_LENGTH+128;
			memset( &sm2Cipher, 0x0, sizeof(ECCCipher) );
			rv = readFile( FNAME_SM2CIPHER, (unsigned char*)tmpbuf, &len );
			if ( rv )
				break;
			PrintBuf( "SM2 ciphter data", tmpbuf, len );

			memcpy(&sm2Cipher.x[32], tmpbuf, 32);
			memcpy(&sm2Cipher.y[32], &tmpbuf[32], 32);
			memcpy(sm2Cipher.C, &tmpbuf[64], len-96);
			sm2Cipher.L = len-96;
			memcpy(sm2Cipher.M, &tmpbuf[64+sm2Cipher.L], 32);
			
			tmplen = sizeof( tmpbuf );
			memset(tmpbuf, 0, tmplen);
			(sel == 0)?(sel = SGD_SM2_1):(sel = SGD_SM2_2);

			rv = SDF_InternalDecryptEx_ECC( hSessionHandle, index, sel,
				&sm2Cipher, tmpbuf, (unsigned int*)&tmplen );
			if ( rv )
			{
				printf( "\nSM2 Private Key Decrypt Failed, 0x%08X.\n\n", rv );
				break;
			}
			printf( "\nSM2 Private Key Decrypt OKOK.\n\n" );
			PrintBuf( "data after decrypt", tmpbuf, tmplen );
			writeFile( FNAME_DECRYPTEDDATA, tmpbuf, tmplen );

			break;
		case 0:	
			return;
		default:
			printf( "Invalid Input, Press <Enter> Key to Continue...\n" );
			break;
		}
		getchar();
		getchar();
	}
}

unsigned char check[32];

int TestSm3Hash( void *hSessionHandle, ECCrefPublicKey *pucPublicKey, 
	unsigned char *pucUserid, int iUseridLen,
	unsigned char *pucData, int iDataLen,
	unsigned char *pucHash, int *piHashLen )
{

	int rv;

	rv = SDF_HashInit( hSessionHandle, SGD_SCH_ID, pucPublicKey, pucUserid, iUseridLen );	
//	rv = SDF_HashInit( hSessionHandle, SGD_SHA1, pucPublicKey, pucUserid, iUseridLen );	
	if(rv != SDR_OK)
	{
		printf("Hash Init Failed, 0x%08X.\n\n", rv );
		return rv;
	}

	rv = SDF_HashUpdate(hSessionHandle, pucData, iDataLen);
	if (rv != SDR_OK)
	{
		printf("Hash Update Failed, 0x%08X.\n\n", rv);
		return rv;
	}

	rv = SDF_HashFinal( hSessionHandle, pucHash, (unsigned int*)piHashLen );
	if(rv != SDR_OK)
	{
		printf("Hash Final Failed, 0x%08X.\n\n", rv );
		return rv;
	}
	
	return 0;
}

int TestGenRandomData( void *hSessionHandle, int randlen, unsigned char *randdata )
{
	int rv, len = 0;
	unsigned char *p = randdata;

	for (;;)
	{
		rv = SDF_GenerateRandom( hSessionHandle, RAND_BLOCK_LENGTH, p );
		if(rv != SDR_OK)
		{
			printf("Generate Random Data[%d] Failed, 0x%08X.\n\n", RAND_BLOCK_LENGTH, rv );
			return rv;
		}

		len += RAND_BLOCK_LENGTH;
		p += RAND_BLOCK_LENGTH;
		if ( len >= randlen )
			return 0;
	}
}

void T_Sm3( void *hSessionHandle )
{
	int sel, rv, len;
	ECCrefPublicKey sm2pubkey;
	unsigned char plainbuf[8192], hashbuf[MAX_DATA_LENGTH], userid[MAX_DATA_LENGTH], tmpbuf[8192];
	int plainlen, hashlen, useridlen;

	for ( ; ; )
	{
		printf( "\n------------- Test SM3 Functions ------------\n" );
		printf( "|                                           |\n" );
		printf( "|    1. Generate SM3 Hash Without UserID.   |\n" );
		printf( "|    2. Generate SM3 Hash With UserID.      |\n" );
		printf( "|                                           |\n" );
		printf( "|    0.  Return.                            |\n" );
		printf( "|                                           |\n" );
		printf( "---------------------------------------------\n" );
		printf( "\nPlease Select:" );
		scanf( "%d", &sel );

		switch( sel )
		{
		case 1:		// Generate SM3 Hash Without UserID.
			plainlen = sizeof( plainbuf );
			memset( plainbuf, 0x0, plainlen );
			rv = readFile( FNAME_SM3PLAINDATA, plainbuf, &plainlen );
			if ( rv )
				return;

			PrintBuf( "plain data", plainbuf, plainlen );

			rv = TestSm3Hash( hSessionHandle, NULL, NULL, 0, 
				plainbuf, plainlen, hashbuf, &hashlen );
			if ( rv )
			{
				printf( "Generate Data's Hash(SM3) Failed, 0x%08X.\n", rv );
				break;
			}
			printf( "Generate Data's Hash(SM3) OKOK.\n\n" );

			PrintBuf( "data's sm3 hash", hashbuf, hashlen );
			break;
		case 2:		// Generate SM3 Hash With UserID.
			plainlen = 1792;
			memset( plainbuf, 0x01, plainlen );
			
			rv = readFile( FNAME_SM3PLAINDATA, plainbuf, &plainlen );
			if ( rv )
				return;
	
			PrintBuf( "plain data", plainbuf, plainlen );
			
			len = sizeof( sm2pubkey );
			memset( &sm2pubkey, 0x0, len );
			rv = readFile( FNAME_SM2PUBKEY, tmpbuf, &len );
			if ( rv )
				break;

			sm2pubkey.bits = 256;
			memcpy(&sm2pubkey.x[32], tmpbuf, 32);
			memcpy(&sm2pubkey.y[32], &tmpbuf[32], 32);

			useridlen = sizeof( userid );
			memset( userid, 0x0, useridlen );
			rv = readFile( FNAME_SM3USERID, userid, &useridlen );
			if ( rv )
				break;
			printf( "user id: %s.\n\n", userid );

			rv = TestSm3Hash( hSessionHandle, &sm2pubkey, userid, useridlen, 
				plainbuf, plainlen, hashbuf, &hashlen );
			if ( rv )
			{
				printf( "Generate Data's Hash(SM3) Failed, 0x%08X.\n", rv );
				break;
			}
			printf( "Generate Data's Hash(SM3) OKOK.\n\n" );

			PrintBuf( "data's sm3 hash", hashbuf, hashlen );
			break;
		case 0:	
			return;
		default:
			printf( "Invalid Input, Press <Enter> Key to Continue...\n" );
			break;
		}
		getchar();
		getchar();
	}

	return;
}

void Zun_EIA3_GenStdIV(unsigned int Count, unsigned int Bearer, unsigned int Direction, unsigned char *IV)
{
	IV[0] = (Count>>24) & 0xFF;
	IV[1] = (Count>>16) & 0xFF;
	IV[2] = (Count>>8) & 0xFF;
	IV[3] = Count & 0xFF;
	IV[4] = (Bearer << 3) & 0xF8;
	IV[5] = IV[6] = IV[7] = 0;
	IV[8] = ((Count>>24) & 0xFF) ^ ((Direction & 1)<<7);
	IV[9] = (Count>>16) & 0xFF;
	IV[10] = (Count>>8) & 0xFF;
	IV[11] = Count & 0xFF;
	IV[12] = IV[4];
	IV[13] = IV[5];
	IV[14] = IV[6] ^ ((Direction&1)<<7);
	IV[15] = IV[7];
}

void Zun_EEA3_GenStdIV(unsigned int Count, unsigned int Bearer, unsigned int Direction, unsigned char *IV)
{
	char cBear, cDir, c1, c2;

	cBear = Bearer & 0xff;
	cDir = Direction & 0xff;

	c1 = cBear << 3;
	c2 = cDir << 2;

	IV[0] = (Count>>24) & 0xFF;
	IV[1] = (Count>>16) & 0xFF;
	IV[2] = (Count>>8) & 0xFF;
	IV[3] = Count & 0xFF;
	IV[4] = (c1 | c2) & 0xFC;
	IV[5] = 0;
	IV[6] = 0;
	IV[7] = 0;
	IV[8] = IV[0];
	IV[9] = IV[1];
	IV[10] = IV[2];
	IV[11] = IV[3];
	IV[12] = IV[4];
	IV[13] = IV[5];
	IV[14] = IV[6];
	IV[15] = IV[7];
}

void T_ZUC( void *hSessionHandle )
{
	int sel, rv;
	unsigned char plainbuf[8192], tmpbuf[8192], key[32], ivparam[32], iv[32];
	int plainlen, keylen, ivlen, zuckeylen, count, bearer, direction, bitlen;
	void *keyHandle = NULL;

	for ( ; ; )
	{
		printf( "\n------------- Test SM3 Functions ------------\n" );
		printf( "|                                           |\n" );
		printf( "|    1. Generate ZUC Key Stream.            |\n" );
		printf( "|    2. ZUC EEA Algorithm calculation.      |\n" );
		printf( "|    3. ZUC EIA Algorithm calculation.      |\n" );
		printf( "|                                           |\n" );
		printf( "|    0.  Return.                            |\n" );
		printf( "|                                           |\n" );
		printf( "---------------------------------------------\n" );
		printf( "\nPlease Select:" );
		scanf( "%d", &sel );

		switch( sel )
		{
		case 1:		// Generate ZUC KEY STREAM.
			keylen = sizeof(key);
			memset( key, 0x0, 32 );
			rv = readFile( FNAME_ZUCKEY, key, &keylen );
			if ( rv )
				return;
			PrintBuf( "Key", key, keylen );

			memset( iv, 0x0, 32 );
			ivlen = sizeof(iv);
			rv = readFile( FNAME_ZUCIV, iv, &ivlen );
			if ( rv )
				return;
			PrintBuf( "IV", iv, ivlen );

			printf("Please input the key stream Length(DWORD TYPE): ");
			scanf("%d", &zuckeylen);
			if(zuckeylen > 128 || zuckeylen <= 0)
			{
				printf("key stream len (1 - 128) DWORDs.\n");
				return;
			}

			rv = SDF_ImportKey(hSessionHandle, key, 16, &keyHandle);
			if ( rv )
			{
				printf( "SDF_ImportKey Failed, 0x%08X.\n", rv );
				break;
			}

			rv = SDF_ZucInit(hSessionHandle, SGD_ZUC_STREAM, keyHandle, iv, NULL, zuckeylen, tmpbuf);
			if ( rv )
			{
				printf( "SDF_ZucInit Failed, 0x%08X.\n", rv );
				break;
			}

			PrintBuf( "ZUC KEY STREAM: ", tmpbuf, zuckeylen*4 );

			rv = SDF_ZucFinal(hSessionHandle);
			if ( rv )
			{
				printf( "SDF_ZucFinal Failed, 0x%08X.\n", rv );
				break;
			}

			printf( "Generate ZUC KEY STREAM OKOK.\n\n" );
			break;
		case 2:
			keylen = sizeof(key);
			memset( key, 0x0, 32 );
			rv = readFile( FNAME_ZUCKEY, key, &keylen );
			if ( rv )
				return;
			PrintBuf( "Key", key, keylen );

			memset( iv, 0x0, 32 );
			ivlen = sizeof(iv);
			rv = readFile( FNAME_ZUCIV, ivparam, &ivlen );
			if ( rv )
				return;
			PrintBuf( "IV PARAM", ivparam, ivlen );

			count = bearer = direction = 0;
			count = ((ivparam[0] << 24) & 0xff000000) | ((ivparam[1] << 16) & 0xff0000) | ((ivparam[2] << 8) & 0xff00) | (ivparam[3] & 0xff);
			bearer = ((ivparam[4] << 24) & 0xff000000) | ((ivparam[5] << 16) & 0xff0000) | ((ivparam[6] << 8) & 0xff00) | (ivparam[7] & 0xff);
			direction = ((ivparam[8] << 24) & 0xff000000) | ((ivparam[9] << 16) & 0xff0000) | ((ivparam[10] << 8) & 0xff00) | (ivparam[11] & 0xff);

			Zun_EEA3_GenStdIV(count, bearer, direction, iv);

			plainlen = sizeof(plainbuf);
			rv = readFile( FNAME_ZUCPLAIN, plainbuf, &plainlen );
			if ( rv )
				return;
			PrintBuf( "PLAIN DATA", plainbuf, plainlen );

			printf("Please input the plain data bit Length(Hex): ");
			scanf("%08x", &bitlen);

			rv = SDF_ImportKey(hSessionHandle, key, 16, &keyHandle);
			if ( rv )
			{
				printf( "SDF_ImportKey Failed, 0x%08X.\n", rv );
				break;
			}

			rv = SDF_ZucInit(hSessionHandle, SGD_ZUC_EEA, keyHandle, iv, plainbuf, bitlen, tmpbuf);
			if ( rv )
			{
				printf( "SDF_ZucInit Failed, 0x%08X.\n", rv );
				break;
			}

			PrintBuf( "ZUC EEA: ", tmpbuf,  plainlen);

			rv = SDF_ZucFinal(hSessionHandle);
			if ( rv )
			{
				printf( "SDF_ZucFinal Failed, 0x%08X.\n", rv );
				break;
			}

			printf( "Generate ZUC EEA OKOK.\n\n" );			
			break;
		case 3:
			keylen = sizeof(key);
			memset( key, 0x0, 32 );
			rv = readFile( FNAME_ZUCKEY, key, &keylen );
			if ( rv )
				return;
			PrintBuf( "Key", key, keylen );

			memset( iv, 0x0, 32 );
			ivlen = sizeof(iv);
			rv = readFile( FNAME_ZUCIV, ivparam, &ivlen );
			if ( rv )
				return;
			PrintBuf( "IV PARAM", ivparam, ivlen );

			count = bearer = direction = 0;
			count = ((ivparam[0] << 24) & 0xff000000) | ((ivparam[1] << 16) & 0xff0000) | ((ivparam[2] << 8) & 0xff00) | (ivparam[3] & 0xff);
			bearer = ((ivparam[4] << 24) & 0xff000000) | ((ivparam[5] << 16) & 0xff0000) | ((ivparam[6] << 8) & 0xff00) | (ivparam[7] & 0xff);
			direction = ((ivparam[8] << 24) & 0xff000000) | ((ivparam[9] << 16) & 0xff0000) | ((ivparam[10] << 8) & 0xff00) | (ivparam[11] & 0xff);

			Zun_EIA3_GenStdIV(count, bearer, direction, iv);

			plainlen = sizeof(plainbuf);
			rv = readFile( FNAME_ZUCPLAIN, plainbuf, &plainlen );
			if ( rv )
				return;
			PrintBuf( "PLAIN DATA", plainbuf, plainlen );

			printf("Please input the plain data bit Length(Hex): ");
			scanf("%08x", &bitlen);

			rv = SDF_ImportKey(hSessionHandle, key, 16, &keyHandle);
			if ( rv )
			{
				printf( "SDF_ImportKey Failed, 0x%08X.\n", rv );
				break;
			}

			rv = SDF_ZucInit(hSessionHandle, SGD_ZUC_EIA, keyHandle, iv, plainbuf, bitlen, tmpbuf);
			if ( rv )
			{
				printf( "SDF_ZucInit Failed, 0x%08X.\n", rv );
				break;
			}

			PrintBuf( "ZUC EIA: ",  tmpbuf, 4 );

			rv = SDF_ZucFinal(hSessionHandle);
			if ( rv )
			{
				printf( "SDF_ZucFinal Failed, 0x%08X.\n", rv );
				break;
			}

			printf( "Generate ZUC EIA OKOK.\n\n" );		
			break;
		case 0:	
			return;
		default:
			printf( "Invalid Input, Press <Enter> Key to Continue...\n" );
			break;
		}
		getchar();
		getchar();
	}

	return;
}

void T_DES( void *hSessionHandle )
{
	int rv, mech, algid, flag;
	int inout, index;
	unsigned char deskey[128], ivbuf[128];
	unsigned char plainbuf[MAX_DATA_LENGTH], cipherbuf[MAX_DATA_LENGTH], tmpbuf[MAX_DATA_LENGTH];
	int deskeylen, ivlen, plainlen, tmplen, cipherlen;
	void *hKeyHandle;

	printf("Please choose key location, 1: outside key; 2: internal key\n");
	scanf("%d", &inout);

	if((inout != 1) && (inout != 2))
		return;

	printf("Please choose algorithm, 1: DES; 2: 3DES\n");
	scanf("%d", &mech);

	if((mech != 1) && (mech != 2))
		return;	

	if(inout == 1)
	{
		deskeylen = sizeof( deskey );
		rv = readFile( FNAME_DESKEY, deskey, &deskeylen );
		if ( rv )
			return;

		if(mech == 1){
			deskeylen = 8;
			PrintBuf( "DES key", deskey, 8 );
		}
		else
			PrintBuf( "3DES key", deskey, deskeylen );

		rv = SDF_ImportKey( hSessionHandle, deskey, deskeylen, &hKeyHandle );
		if ( rv )
		{
			printf( "Import Session Key(DES) Failed, 0x%08X.\n", rv );
			return;
		}
		printf( "Import Session Key(DES) OKOK.\n\n" );
	}
	else
	{
		printf("Please input key index: ");
		scanf("%d", &index);
		hKeyHandle = &index;
	}

	printf( "Please Input Encryption-Mode[ 1-ECB, 2-CBC ]: " );
	scanf( "%d", &flag );

	if ( flag == 1 && mech == 1)
		algid = SGD_DES_ECB;
	else if ( flag == 2 && mech == 1)
		algid = SGD_DES_CBC;
	else if ( flag == 1 && mech == 2)
		algid = SGD_3DES_ECB;
	else if ( flag == 2 && mech == 2)
		algid = SGD_3DES_CBC;
	else
	{
		printf( "Invalid Input, Press <Enter> Key to Continue...\n" );
		return;
	}

	plainlen = sizeof( plainbuf );
	memset( plainbuf, 0x0, plainlen );
	rv = readFile( FNAME_DESPLAINDATA, plainbuf, &plainlen );
	if ( rv )
		return;
	PrintBuf( "plain data", plainbuf, plainlen );

	if ( flag == 2 )
	{
		ivlen = sizeof( ivbuf );
		memset( ivbuf, 0x0, ivlen );
		rv = readFile( FNAME_DESCBCIV, ivbuf, &ivlen );
		if ( rv )
			return;
		ivlen = 8;
		PrintBuf( "cbc iv", ivbuf, ivlen );
	}
	
	rv = SDF_Encrypt( hSessionHandle, hKeyHandle, algid, ivbuf,
		plainbuf, plainlen, cipherbuf, (unsigned int*)&cipherlen );
	if ( rv )
	{
		if(mech == 1)
			printf( "DES Encrypt Data Failed, 0x%08X.\n", rv );
		else
			printf( "3DES Encrypt Data Failed, 0x%08X.\n", rv );
		return;
	}
	if(mech == 1)
		printf( "DES Encrypt Data OKOK.\n\n" );
	else
		printf( "3DES Encrypt Data OKOK.\n\n" );

	PrintBuf( "cipher data", cipherbuf, cipherlen );
	writeFile( FNAME_DESCIPHER, cipherbuf, cipherlen );
	
	rv = SDF_Decrypt( hSessionHandle, hKeyHandle, algid, ivbuf,
		cipherbuf, cipherlen, tmpbuf, (unsigned int*)&tmplen );
	if ( rv )
	{
		if(mech == 1)
			printf( "DES Decrypt Data Failed, 0x%08X.\n", rv );
		else
			printf( "3DES Decrypt Data Failed, 0x%08X.\n", rv );
		return;
	}

	if(mech == 1)
		printf( "DES Decrypt Data OKOK.\n\n" );
	else
		printf( "3DES Decrypt Data OKOK.\n\n" );
	PrintBuf( "data after decrypt", tmpbuf, tmplen );
	
	/*
	ivlen = sizeof( ivbuf );
	memset( ivbuf, 0x0, ivlen );

	rv = SDF_CalculateMAC(hSessionHandle, hKeyHandle, SGD_SM4_MAC, ivbuf, plainbuf, plainlen, cipherbuf, &cipherlen);
	if ( rv ) {
		printf( "SM4 SDF_CalculateMAC Data Failed, 0x%08X.\n", rv );
		return;
	}

	printf( "SM4 MAC OKOK.\n\n" );
	PrintBuf( "SM4 MAC ", cipherbuf, cipherlen );
	*/
	rv = SDF_DestoryKey( hSessionHandle, hKeyHandle);
	if ( rv ) {
		printf( "Destory Key error, 0x%08X.\n", rv );
		return;
	}

	if ( memcmp(plainbuf, tmpbuf, plainlen) )
		printf( "Compare with Plain Data Failed!\n\n" );
	else
		printf( "Compare with Plain Data OKOK!\n\n" );
	return;
}

void T_SSF33( void *hSessionHandle )
{
	int rv, algid, flag;
	int inout, index;
	unsigned char ssf33key[128], ivbuf[128];
	unsigned char plainbuf[MAX_DATA_LENGTH], cipherbuf[MAX_DATA_LENGTH], tmpbuf[MAX_DATA_LENGTH];
	int ssf33keylen, ivlen, plainlen, tmplen, cipherlen;
	void *hKeyHandle;

	printf("Please choose key location, 1: outside key; 2: internal key\n");
	scanf("%d", &inout);

	if((inout != 1) && (inout != 2))
		return;

	if(inout == 1)
	{
		ssf33keylen = sizeof( ssf33key );
		rv = readFile( FNAME_SSF33KEY, ssf33key, &ssf33keylen );
		if ( rv )
			return;

		rv = SDF_ImportKey( hSessionHandle, ssf33key, ssf33keylen, &hKeyHandle );
		if ( rv )
		{
			printf( "Import Session Key(SSF33) Failed, 0x%08X.\n", rv );
			return;
		}
		printf( "Import Session Key(SSF33) OKOK.\n\n" );
	}
	else
	{
		printf("Please input key index: ");
		scanf("%d", &index);
		hKeyHandle = &index;
	}

	printf( "Please Input Encryption-Mode[ 1-ECB, 2-CBC ]: " );
	scanf( "%d", &flag );

	if ( flag == 1)
		algid = SGD_SSF33_ECB;
	else if ( flag == 2)
		algid = SGD_SSF33_CBC;
	else
	{
		printf( "Invalid Input, Press <Enter> Key to Continue...\n" );
		return;
	}

	plainlen = sizeof( plainbuf );
	memset( plainbuf, 0x0, plainlen );
	rv = readFile( FNAME_SSF33PLAINDATA, plainbuf, &plainlen );
	if ( rv )
		return;
	PrintBuf( "plain data", plainbuf, plainlen );

	if ( flag == 2 )
	{
		ivlen = sizeof( ivbuf );
		memset( ivbuf, 0x0, ivlen );
		rv = readFile( FNAME_SSF33CBCIV, ivbuf, &ivlen );
		if ( rv )
			return;
		PrintBuf( "cbc iv", ivbuf, ivlen );
	}
	
	rv = SDF_Encrypt( hSessionHandle, hKeyHandle, algid, ivbuf,
		plainbuf, plainlen, cipherbuf, (unsigned int*)&cipherlen );
	if ( rv )
	{
		printf( "SSF33 Encrypt Data Failed, 0x%08X.\n", rv );
		return;
	}
	printf( "SSF33 Encrypt Data OKOK.\n\n" );

	PrintBuf( "cipher data", cipherbuf, cipherlen );
	writeFile( FNAME_DESCIPHER, cipherbuf, cipherlen );
	
	rv = SDF_Decrypt( hSessionHandle, hKeyHandle, algid, ivbuf,
		cipherbuf, cipherlen, tmpbuf, (unsigned int*)&tmplen );
	if ( rv )
	{
		printf( "SSF33 Decrypt Data Failed, 0x%08X.\n", rv );
		return;
	}

	printf( "SSF33 Decrypt Data OKOK.\n\n" );
	PrintBuf( "data after decrypt", tmpbuf, tmplen );
	
	
	ivlen = sizeof( ivbuf );
	memset( ivbuf, 0x0, ivlen );
	rv = readFile( FNAME_SSF33CBCIV, ivbuf, &ivlen );
	if ( rv )
		return;
	PrintBuf( "mac iv", ivbuf, ivlen );

	rv = SDF_CalculateMAC(hSessionHandle, hKeyHandle, SGD_SSF33_MAC, ivbuf, plainbuf, plainlen, cipherbuf, (unsigned int *)&cipherlen);
	if ( rv ) {
		printf( "SSF33 SDF_CalculateMAC Data Failed, 0x%08X.\n", rv );
		return;
	}

	printf( "SSF33 MAC OKOK.\n\n" );
	PrintBuf( "SSF33 MAC ", cipherbuf, cipherlen );
	
	rv = SDF_DestoryKey( hSessionHandle, hKeyHandle);
	if ( rv ) {
		printf( "Destory Key error, 0x%08X.\n", rv );
		return;
	}

	if ( memcmp(plainbuf, tmpbuf, plainlen) )
		printf( "Compare with Plain Data Failed!\n\n" );
	else
		printf( "Compare with Plain Data OKOK!\n\n" );
	return;
}

void T_Sm4( void *hSessionHandle )
{
	int rv, algid, flag;
	int inout, index;
	unsigned char sm4key[128], ivbuf[128];
	unsigned char plainbuf[2000], cipherbuf[2000], tmpbuf[2000];
	int sm4keylen, ivlen, plainlen, tmplen, cipherlen;
	void *hKeyHandle;
//	unsigned char key[] = {0xF2, 0x5C, 0x87, 0x8C, 0x99, 0x8D, 0xC6, 0x0D, 0xB8, 0x0D, 0xC9, 0x98, 0x72, 0x32, 0x51, 0xD2};

	printf("Please choose key location, 1: outside key; 2: internal key\n");
	scanf("%d", &inout);

	if((inout != 1) && (inout != 2))
		return;

	if(inout == 1)
	{
		sm4keylen = sizeof( sm4key );
		rv = readFile( FNAME_SM4KEY, sm4key, &sm4keylen );
		if ( rv )
			return;

	//	memcpy( sm4key, key, 16 );
		PrintBuf( "sm4 key", sm4key, sm4keylen );

		rv = SDF_ImportKey( hSessionHandle, sm4key, sm4keylen, &hKeyHandle );
		if ( rv )
		{
			printf( "Import Session Key(SM4) Failed, 0x%08X.\n", rv );
			return;
		}
		printf( "Import Session Key(SM4) OKOK.\n\n" );
	}
	else
	{
		printf("Please input key index: ");
		scanf("%d", &index);
		hKeyHandle = &index;
	}

	printf( "Please Input Encryption-Mode[ 1-ECB, 2-CBC ]: " );
	scanf( "%d", &flag );

	if ( flag == 1 )
		algid = SGD_SM4_ECB;
	else if ( flag == 2 )
		algid = SGD_SM4_CBC;
	else
	{
		printf( "Invalid Input, Press <Enter> Key to Continue...\n" );
		return;
	}

	plainlen = sizeof( plainbuf );
	memset( plainbuf, 0x0, plainlen );

	rv = readFile( FNAME_SM4PLAINDATA, plainbuf, &plainlen );
	if ( rv )
		return;
	PrintBuf( "plain data", plainbuf, plainlen );

	if ( flag == 2 )
	{
		ivlen = sizeof( ivbuf );
		memset( ivbuf, 0x0, ivlen );
		rv = readFile( FNAME_SM4CBCIV, ivbuf, &ivlen );
		if ( rv )
			return;
		PrintBuf( "cbc iv", ivbuf, ivlen );
	}
	
	rv = SDF_Encrypt( hSessionHandle, hKeyHandle, algid, ivbuf,
		plainbuf, plainlen, cipherbuf, (unsigned int*)&cipherlen );
	if ( rv )
	{
		printf( "SM4 Encrypt Data Failed, 0x%08X.\n", rv );
		return;
	}
	printf( "SM4 Encrypt Data OKOK.\n\n" );
	PrintBuf( "cipher data", cipherbuf, cipherlen );
	writeFile( FNAME_SM4CIPHER, cipherbuf, cipherlen );
	
	rv = SDF_Decrypt( hSessionHandle, hKeyHandle, algid, ivbuf,
		cipherbuf, cipherlen, tmpbuf, (unsigned int*)&tmplen );
	if ( rv )
	{
		printf( "SM4 Decrypt Data Failed, 0x%08X.\n", rv );
		return;
	}
	printf( "SM4 Decrypt Data OKOK.\n\n" );
	PrintBuf( "data after decrypt", tmpbuf, tmplen );
	
	ivlen = sizeof( ivbuf );
	memset( ivbuf, 0x0, ivlen );

	rv = SDF_CalculateMAC(hSessionHandle, hKeyHandle, SGD_SM4_MAC, ivbuf, plainbuf, plainlen, cipherbuf, (unsigned int *)&cipherlen);
	if ( rv ) {
		printf( "SM4 SDF_CalculateMAC Data Failed, 0x%08X.\n", rv );
		return;
	}

	printf( "SM4 MAC OKOK.\n\n" );
	PrintBuf( "SM4 MAC ", cipherbuf, cipherlen );

	rv = SDF_DestoryKey( hSessionHandle, hKeyHandle);
	if ( rv ) {
		printf( "Destory Key error, 0x%08X.\n", rv );
		return;
	}

	if ( memcmp(plainbuf, tmpbuf, plainlen) )
		printf( "Compare with Plain Data Failed!\n\n" );
	else
		printf( "Compare with Plain Data OKOK!\n\n" );
	return;
}

void T_Sm1( void *hSessionHandle )
{
	int rv, algid, flag, ofb_outlen, ofb_sel;
	int inout, index, i;
	unsigned char sm1key[128], ivbuf[128];
	unsigned char plainbuf[8192], cipherbuf[8192], tmpbuf[8192];
	int sm1keylen, ivlen, plainlen, tmplen;
	unsigned int cipherlen = 8192;
	void *hKeyHandle;

	printf("Please choose key location, 1: outside key; 2: internal key\n");
	scanf("%d", &inout);

	if((inout != 1) && (inout != 2))
		return;

	if(inout == 1)
	{
		sm1keylen = sizeof( sm1key );
		rv = readFile( FNAME_SM1KEY, sm1key, &sm1keylen);
		if ( rv )
			return;

		PrintBuf( "sm1 key", sm1key, sm1keylen );

		rv = SDF_ImportKey( hSessionHandle, sm1key, sm1keylen, &hKeyHandle );
		if ( rv )
		{
			printf( "Import Session Key(SM1) Failed, 0x%08X.\n", rv );
			return;
		}
		printf( "Import Session Key(SM1) OKOK.\n\n" );
	}
	else
	{
		printf("Please input key index: ");
		scanf("%d", &index);
		//rv = SDF_SetInternalSessionKey_Ex(hSessionHandle, (unsigned int *)&index, &hKeyHandle);
		hKeyHandle = &index;
	}

	plainlen = sizeof( plainbuf );
	memset( plainbuf, 0x0, plainlen );

	printf( "Please Input Encryption-Mode[ 1-ECB, 2-CBC, 3-OFB, 4-OFB-OX ]: " );
	scanf( "%d", &flag );

	if ( flag == 1 )
		algid = SGD_SM1_ECB;
	else if ( flag == 2 )
		algid = SGD_SM1_CBC;
	else if (flag == 3){
		algid = SGD_SM1_OFB;
		printf( "Please Input the group count of output: " );
		scanf( "%d", &ofb_outlen );

		plainlen = ofb_outlen * 16;
	}
	else if (flag == 4){
		algid = SGD_SM1_OFB_OX;
	}
	else
	{
		printf( "Invalid Input, Press <Enter> Key to Continue...\n" );
		return;
	}

	if(flag == 1 || flag == 2)
	{
		plainlen = 8192;
		rv = readFile( FNAME_SM1PLAINDATA, plainbuf, &plainlen );
		if ( rv )
			return;
		PrintBuf( "plain data", plainbuf, plainlen );
	}
	else if(flag == 4)
	{
		printf("Please choose input data: 1-From File; 2-Generate Data: ");
		scanf("%d", &ofb_sel);

		if(ofb_sel == 1)
		{
			plainlen = 8192;
			rv = readFile( FNAME_SM1PLAINDATA, plainbuf, &plainlen );
			if ( rv )
				return;
			PrintBuf( "plain data", plainbuf, plainlen );
		}
		else if(ofb_sel == 2)
		{
			printf( "Please Input the group count of output: " );
			scanf( "%d", &ofb_outlen );

			plainlen = ofb_outlen * 16;

			for(i=0; i<plainlen; i++)
				plainbuf[i] = i % 16;
		}
		else
			return;
	}

	if ( flag == 2 || flag == 3 || flag == 4)
	{
		ivlen = sizeof( ivbuf );
		memset( ivbuf, 0x0, ivlen );
		rv = readFile( FNAME_SM1CBCIV, ivbuf, &ivlen );
		if ( rv )
			return;
		PrintBuf( "iv", ivbuf, ivlen );
	}

	cipherlen = 8192;
	rv = SDF_Encrypt( hSessionHandle, hKeyHandle, algid, ivbuf,
		plainbuf, plainlen, cipherbuf, (unsigned int*)&cipherlen );
	if ( rv )
	{
		printf( "SM1 Encrypt Data Failed, 0x%08X.\n", rv );
		return;
	}
	printf( "SM1 Encrypt Data OKOK.\n\n" );
	PrintBuf( "cipher data", cipherbuf, cipherlen );

	if(flag != 3)
	{
		writeFile( FNAME_SM1CIPHER, cipherbuf, cipherlen );

		if ( flag == 2 || flag == 3 || flag == 4)
		{
			ivlen = sizeof( ivbuf );
			memset( ivbuf, 0x0, ivlen );
			rv = readFile( FNAME_SM1CBCIV, ivbuf, &ivlen );
			if ( rv )
				return;
			PrintBuf( "iv", ivbuf, ivlen );
		}
		tmplen = 8192;
		rv = SDF_Decrypt( hSessionHandle, hKeyHandle, algid, ivbuf,
			cipherbuf, cipherlen, tmpbuf, (unsigned int*)&tmplen );
		if ( rv )
		{
			printf( "SM1 Decrypt Data Failed, 0x%08X.\n", rv );
			return;
		}
		printf( "SM1 Decrypt Data OKOK.\n\n" );
		PrintBuf( "data after decrypt", tmpbuf, tmplen );
	}

	if(flag != 3 && flag != 4)
	{	
		ivlen = sizeof( ivbuf );
		memset( ivbuf, 0x0, ivlen );
		cipherlen = 8192;
		rv = SDF_CalculateMAC(hSessionHandle, hKeyHandle, SGD_SM1_MAC, ivbuf, plainbuf, plainlen, cipherbuf, &cipherlen);
		if ( rv ) {
			printf( "SM1 SDF_CalculateMAC Data Failed, 0x%08X.\n", rv );
			return;		
		}

		printf( "SM1 MAC OKOK.\n\n" );
		PrintBuf( "SM1 MAC ", cipherbuf, cipherlen );
	}

	if (flag != 3)
	{
		if (memcmp(plainbuf, tmpbuf, plainlen))
			printf("Compare with Plain Data Failed!\n\n");
		else
			printf("Compare with Plain Data OKOK!\n\n");
	}

	rv = SDF_DestoryKey( hSessionHandle, hKeyHandle);
	if ( rv ) {
		printf( "Destory Key error, 0x%08X.\n", rv );
		return;
	}
	return;
}


void T_Sm7(void *hSessionHandle)
{
	int rv, algid, flag;
	unsigned char sm7key[128], ivbuf[128];
	unsigned char plainbuf[8192], cipherbuf[8192], tmpbuf[8192];
	int sm7keylen, ivlen, plainlen, tmplen;
	unsigned int cipherlen = 8192;
	void *hKeyHandle;

	sm7keylen = sizeof(sm7key);
	rv = readFile(FNAME_SM7KEY, sm7key, &sm7keylen);
	if (rv)
		return;

	PrintBuf("sm7 key", sm7key, sm7keylen);

	rv = SDF_ImportKey(hSessionHandle, sm7key, sm7keylen, &hKeyHandle);
	if (rv)
	{
		printf("Import Session Key(SM7) Failed, 0x%08X.\n", rv);
		return;
	}
	printf("Import Session Key(SM7) OKOK.\n\n");

	plainlen = sizeof(plainbuf);
	memset(plainbuf, 0x0, plainlen);

	printf("Please Input Encryption-Mode[ 1-ECB, 2-OFB ]: ");
	scanf("%d", &flag);

	if (flag == 1)
		algid = SGD_SM7_ECB;
	else if (flag == 2) {
		algid = SGD_SM7_OFB;
		printf("Please Input the output key stream length: ");
		scanf("%d", &plainlen);
	}
	else
	{
		printf("Invalid Input, Press <Enter> Key to Continue...\n");
		return;
	}

	if (flag == 1)
	{
		plainlen = 8192;
		rv = readFile(FNAME_SM7PLAINDATA, plainbuf, &plainlen);
		if (rv)
			return;
		PrintBuf("plain data", plainbuf, plainlen);
	}
	else if (flag == 2)
	{
		ivlen = sizeof(ivbuf);
		memset(ivbuf, 0x0, ivlen);
		rv = readFile(FNAME_SM7CBCIV, ivbuf, &ivlen);
		if (rv)
			return;
		PrintBuf("iv", ivbuf, ivlen);
	}

	cipherlen = 8192;
	rv = SDF_Encrypt(hSessionHandle, hKeyHandle, algid, ivbuf,
		plainbuf, plainlen, cipherbuf, (unsigned int*)&cipherlen);
	if (rv)
	{
		printf("SM1 Encrypt Data Failed, 0x%08X.\n", rv);
		return;
	}
	printf("SM1 Encrypt Data OKOK.\n\n");
	PrintBuf("cipher data", cipherbuf, cipherlen);

	if (flag == 1)
	{
		writeFile(FNAME_SM7CIPHER, cipherbuf, cipherlen);

		if (flag == 2)
		{
			ivlen = sizeof(ivbuf);
			memset(ivbuf, 0x0, ivlen);
			rv = readFile(FNAME_SM7CBCIV, ivbuf, &ivlen);
			if (rv)
				return;
			PrintBuf("iv", ivbuf, ivlen);
		}
		tmplen = 8192;
		rv = SDF_Decrypt(hSessionHandle, hKeyHandle, algid, ivbuf,
			cipherbuf, cipherlen, tmpbuf, (unsigned int*)&tmplen);
		if (rv)
		{
			printf("SM7 Decrypt Data Failed, 0x%08X.\n", rv);
			return;
		}
		printf("SM1 Decrypt Data OKOK.\n\n");
		PrintBuf("data after decrypt", tmpbuf, tmplen);
	}

	if (flag == 1)
	{
		if (memcmp(plainbuf, tmpbuf, plainlen))
			printf("Compare with Plain Data Failed!\n\n");
		else
			printf("Compare with Plain Data OKOK!\n\n");
	}

	rv = SDF_DestoryKey(hSessionHandle, hKeyHandle);
	if (rv) {
		printf("Destory Key error, 0x%08X.\n", rv);
		return;
	}
	return;
}

void T_Random( void *hSessionHandle )
{
	int rv, randlen, fnum, i;
	unsigned char randdata[MAX_RAND_LENGTH];
	char buf[128];

	printf( "How many random file [ 1 - 1000 ]: " );
	scanf( "%d", &fnum );
	printf( "How many bytes per file[ 1 - max(128K) ]: " );
	scanf( "%s", buf );
	if ( strcmp(buf,"max") == 0 )
		randlen = MAX_RAND_LENGTH;
	else
		randlen = atoi( buf );
	if ( randlen > MAX_RAND_LENGTH )
		randlen = MAX_RAND_LENGTH;

	if ( fnum > 1000 )
		fnum = 1000;

	for ( i = 1; i <= fnum; i ++ )
	{
		rv = TestGenRandomData( hSessionHandle, randlen, randdata );
		if ( rv )
			return;

		sprintf( buf, "%d-%d", fnum, i );
		writeFile( buf, randdata, randlen );
	}

	printf( "Generate Random Data Finished.\n\n" );
	return;
}

void T_Rsa( void *hSessionHandle )
{
	int sel, rv, len, iRsaKeyLen, rsaindex;
	RSArefPublicKey rsapubkey;
	RSArefPrivateKey rsaprikey;
	unsigned char plainbuf[MAX_DATA_LENGTH], tmpbuf[MAX_DATA_LENGTH+128];
	char pwd[128];
	int plainlen, tmplen;

	for ( ; ; )
	{
		printf( "\n--------------- Test RSA Functions ---------------\n" );
		printf( "|                                                   \n" );
		printf( "|      1.  Generate RSA Key Pair.                   \n" );
		printf( "|      2.  RSA External Private Key Operation.      \n" );
		printf( "|      3.  RSA External Public Key Operation.       \n" );
		printf( "|      4.  RSA Internal Private Key Operation.      \n" );
		printf( "|      5.  RSA Internal Public Key Operation.       \n" );
		printf( "|      6.  RSA Export Sign Public Key Operation.    \n" );
		printf( "|      7.  RSA Export Encrypt Public Key Operation. \n" );
		printf( "|                                                   \n" );
		printf( "|      0.  Return.                                  \n" );
		printf( "|                                                   \n" );
		printf( "----------------------------------------------------\n" );
		printf( "\nPlease Select:" );
		scanf( "%d", &sel );

		switch( sel )
		{
		case 1:		// Generate SM2 Key Pair
			printf( "Generate RSA Key Pair Length: " );
			scanf( "%d", &iRsaKeyLen );
			if ( !((1024 == iRsaKeyLen) || (2048 == iRsaKeyLen)) ) {
				printf( "The RSA Key Pair Length[%d] invalid.\n\n", iRsaKeyLen );
				break;
			}
						
			memset(&rsapubkey, 0x0, sizeof(rsapubkey));
			memset(&rsaprikey, 0x0, sizeof(rsaprikey));
			rv = SDF_GenerateKeyPair_RSA( hSessionHandle, iRsaKeyLen, &rsapubkey, &rsaprikey);
			if ( rv ) {
				printf( "\n SDF_GenerateKeyPair_RSA error. rv = 0x%08x. \n\n", rv );
				break;
			}

			PrintBuf( "pub_m", rsapubkey.m+RSAref_MAX_LEN-iRsaKeyLen/8, iRsaKeyLen/8 );
			PrintBuf( "pub_e", rsapubkey.e+RSAref_MAX_LEN-3, 3 );
			writeFile( FNAME_RSAPUBKEY, (unsigned char*)&rsapubkey, sizeof(RSArefPublicKey) );

			PrintBuf( "pri_m", rsaprikey.m+RSAref_MAX_LEN-iRsaKeyLen/8, iRsaKeyLen/8 );
			PrintBuf( "pri_e", rsaprikey.e+RSAref_MAX_LEN-3, 3 );
			PrintBuf( "pri_d", rsaprikey.d+RSAref_MAX_LEN-iRsaKeyLen/8, iRsaKeyLen/8 );
			PrintBuf( "pri_p", rsaprikey.prime[0]+RSAref_MAX_PLEN-iRsaKeyLen/8/2, iRsaKeyLen/8/2 );
			PrintBuf( "pri_q", rsaprikey.prime[1]+RSAref_MAX_PLEN-iRsaKeyLen/8/2, iRsaKeyLen/8/2 );
			PrintBuf( "pri_dp", rsaprikey.pexp[0]+RSAref_MAX_PLEN-iRsaKeyLen/8/2, iRsaKeyLen/8/2 );
			PrintBuf( "pri_dq", rsaprikey.pexp[1]+RSAref_MAX_PLEN-iRsaKeyLen/8/2, iRsaKeyLen/8/2 );
			PrintBuf( "pri_qinv", rsaprikey.coef+RSAref_MAX_PLEN-iRsaKeyLen/8/2, iRsaKeyLen/8/2 );

			writeFile( FNAME_RSAPRIKEY, (unsigned char*)&rsaprikey, sizeof(RSArefPrivateKey) );
			printf("\n\n");
			break;
		case 2:		// RSA External Private Key Operation
			// ¶ÁÈ¡Ë½Ô¿
			len = sizeof( rsaprikey );
			memset( &rsaprikey, 0x0, len );
			rv = readFile( FNAME_RSAPRIKEY, (unsigned char*)&rsaprikey, &len );
			if ( rv )
				break;

			plainlen = sizeof( plainbuf );
			memset( plainbuf, 0x0, plainlen );
			rv = readFile( FNAME_RSAPLAIN, plainbuf, &plainlen );
			if ( rv )
				break;

			plainlen = rsaprikey.bits/8;
			PrintBuf( "plain data", plainbuf, plainlen );

			rv = SDF_ExternalPrivateKeyOperation_RSA( hSessionHandle, 
				&rsaprikey, plainbuf, plainlen, tmpbuf, (unsigned int*)&tmplen);
			if ( rv ) {
				printf( "\n SDF_ExternalPrivateKeyOperation_RSA error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nRSA Private Key Operation OKOK.\n\n" );
			PrintBuf( "cipher data", tmpbuf, tmplen );

			writeFile( FNAME_RSACIPHER, (unsigned char*)&tmpbuf, tmplen );
			printf("\n\n");

			break;
		case 3:	 // RSA External Public Key Operation.
			
			// ¶ÁÈ¡Ë½Ô¿¡£
			len = sizeof( rsaprikey );
			memset( &rsaprikey, 0x0, len );
			memset( &rsapubkey, 0x0, sizeof(rsapubkey) );
			rv = readFile( FNAME_RSAPRIKEY, (unsigned char*)&rsaprikey, &len );
			if ( rv )
				break;

			memcpy(&rsapubkey, &rsaprikey, sizeof(rsapubkey));

			plainlen = sizeof( plainbuf );
			memset( plainbuf, 0x0, plainlen );
			rv = readFile( FNAME_RSACIPHER, plainbuf, &plainlen );
			if ( rv )
				break;

			plainlen = rsapubkey.bits/8;
			PrintBuf( "cipher data", plainbuf, plainlen );

			rv = SDF_ExternalPublicKeyOperation_RSA( hSessionHandle,
				&rsapubkey, plainbuf, plainlen, tmpbuf, (unsigned int*)&tmplen);
			if ( rv ) {
				printf( "\n SDF_ExternalPublicKeyOperation_RSA error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nRSA Public Key Operation OKOK.\n\n" );
			PrintBuf( "plain data", tmpbuf, tmplen );
			printf("\n\n");

			break;

		case 4:		// RSA Internal Private Key Operation.
			printf( "Please Input Internal RSA Key Pair Index [ 1 - 64 ]: " );
			scanf( "%d", &rsaindex );
			if ( 1 > rsaindex || 64 < rsaindex ) {
				printf( "\n The RSA Key Pair Index[%d] invalid.\n\n", rsaindex );
				break;
			}

			printf( "Please Input RSA Key Pair Length [ 1024 - 2048 ]: " );
			scanf( "%d", &iRsaKeyLen );
			if ( 1024 > iRsaKeyLen || 2048 < iRsaKeyLen || iRsaKeyLen % 16 ) {
				printf( "\n The RSA Key Pair Length[%d] invalid.\n\n", iRsaKeyLen );
				break;
			}

			printf( "Please Input Internal RSA Private Key PassWord: " );
			scanf( "%s", pwd );

			plainlen = sizeof( plainbuf );
			memset( plainbuf, 0x0, plainlen );
			rv = readFile( FNAME_RSAPLAIN, plainbuf, &plainlen );
			if ( rv )
				break;

			plainlen = iRsaKeyLen/8;
			PrintBuf( "plain data", plainbuf, plainlen );
			
			rv = SDF_GetPrivateKeyAccessRight_Ex(hSessionHandle, rsaindex, 1, (unsigned char*)pwd, strlen(pwd) );
			if ( rv ) {
				printf( "\nSDF_GetPrivateKeyAccessRight error. rv = 0x%08x. \n\n", rv );
				break;
			}
		
			rv = SDF_InternalPrivateKeyOperation_RSA( hSessionHandle,
				rsaindex, plainbuf, plainlen, tmpbuf, (unsigned int*)&tmplen);
			if ( rv ) {
				printf( "\nSDF_InternalPrivateKeyOperation_RSA error. rv = 0x%08x. \n\n", rv );
				SDF_ReleasePrivateKeyAccessRight(hSessionHandle, rsaindex);
				break;
			}

			SDF_ReleasePrivateKeyAccessRight(hSessionHandle, rsaindex);

			printf( "\nRSA Private Key Operation OKOK.\n\n" );
			PrintBuf( "cipher data", tmpbuf, tmplen );


			writeFile( FNAME_RSACIPHER, (unsigned char*)&tmpbuf, tmplen );
			printf("\n\n");

			break;
		case 5:		// RSA Internal Public Key Operation.
			printf( "Please Input Internal RSA Key Pair Index [ 1 - 64 ]: " );
			scanf( "%d", &rsaindex );
			if ( 1 > rsaindex || 64 < rsaindex ) {
				printf( "\n The RSA Key Pair Index[%d] invalid.\n\n", rsaindex );
				break;
			}

			printf( "Please Input RSA Key Pair Length [ 1024 - 2048 ]: " );
			scanf( "%d", &iRsaKeyLen );
			if ( 1024 > iRsaKeyLen || 2048 < iRsaKeyLen || iRsaKeyLen % 16 ) {
				printf( "\n The RSA Key Pair Length[%d] invalid.\n\n", iRsaKeyLen );
				break;
			}

			plainlen = sizeof( plainbuf );
			memset( plainbuf, 0x0, plainlen );
			rv = readFile( FNAME_RSACIPHER, plainbuf, &plainlen );
			if ( rv )
				break;

			plainlen = iRsaKeyLen/8;
			PrintBuf( "Cipher data", plainbuf, plainlen );
			
			rv = SDF_InternalPublicKeyOperation_RSA( hSessionHandle,
				rsaindex, plainbuf, plainlen, tmpbuf, (unsigned int*)&tmplen);
			if ( rv ) {
				printf( "\n SDF_InternalPublicKeyOperation_RSA error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nRSA Public Key Operation OKOK.\n\n" );
			PrintBuf( "plain data", tmpbuf, tmplen );
			printf("\n\n");

			break;
		case 6:		// RSA Export Sign Public Key Operation.
			printf( "Please Input RSA Key Pair Index: " );
			scanf( "%d", &rsaindex );

			memset(&rsapubkey, 0x0, sizeof(rsapubkey));
			rv = SDF_ExportSignPublicKey_RSA( hSessionHandle, rsaindex, &rsapubkey);
			if ( rv ) {
				printf( "\n SDF_ExportSignPublicKey_RSA error. rv = 0x%08x. \n\n", rv );
				break;
			}
			writeFile( FNAME_RSAPRIKEY, (unsigned char*)&rsaprikey, sizeof(rsaprikey) );

			printf( "\nRSA Export Sign Public Key Operation OKOK.\n\n" );

			PrintBuf( "pri_m", rsapubkey.m+RSAref_MAX_LEN-(rsapubkey.bits+7)/8, (rsapubkey.bits+7)/8 );
			PrintBuf( "pri_e", rsapubkey.e+RSAref_MAX_LEN-3, 3 );
			printf("\n\n");

			break;
		case 7:		// RSA Export Encrypt Public Key Operation.
			printf( "Please Input RSA Key Pair Index: " );
			scanf( "%d", &rsaindex );

			memset(&rsapubkey, 0x0, sizeof(rsapubkey));
			rv = SDF_ExportEncPublicKey_RSA( hSessionHandle, rsaindex, &rsapubkey);
			if ( rv ) {
				printf( "\n SDF_ExportSignPublicKey_RSA error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nRSA Export Encrypted Public Key Operation OKOK.\n\n" );

			PrintBuf( "pri_m", rsapubkey.m+RSAref_MAX_LEN-rsapubkey.bits/8, rsapubkey.bits/8 );
			PrintBuf( "pri_e", rsapubkey.e+RSAref_MAX_LEN-3, 3 );
			printf("\n\n");

			break;
		case 0:	
			return;
		default:
			printf( "Invalid Input, Press <Enter> Key to Continue...\n" );
			break;
		}
		getchar();
		getchar();
	}
}

void T_Exchange(void *hSessionHandle )
{
	int sel, rv, rsaindex, sm2index, iKeyIndex;
	RSArefPublicKey rsapubkey;
	RSArefPrivateKey rsaprikey;
	ECCrefPublicKey sm2pubkey;
	ECCrefPrivateKey sm2prikey;
	ECCCipher sm2cipherkey, sm2cipherkey1;

	ECCrefPublicKey pucSponsorPublicKey;
	ECCrefPublicKey pucSponsorTmpPublicKey;
	ECCrefPublicKey pucResponsePublicKey;
	ECCrefPublicKey pucResponseTmpPublicKey;

	Agreement *st_agreement;

	void *hSessKey = NULL;
	unsigned char ucSessKey[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

	unsigned char selfid[] = "mxy", otherid[] = "wyf";
	unsigned int selfidlen = 3, otheridlen = 3;

	unsigned char cipherKey[256], cipherKey1[256];
	unsigned char cipherData[128], decData[128], plainData[128];
	unsigned char tmp[8192];
	unsigned int cipherlen, declen, plainlen;

	char pwd[128];
	int cipherKeyLen, cipherKeyLen1;
	void *phKeyHandle = NULL, *hkeyhandle1 = NULL, *hkeyhandle2 = NULL;

	for ( ; ; )
	{
		printf( "\n------------------------- Test Exchange Functions -----------------------\n" );
		printf( "|                                                                          \n" );
		printf( "|      1.  Generate Session Key by RSA Internal Public Key Encrypted.      \n" );
		printf( "|      2.  Generate Session Key by RSA External Public Key Encrypted.      \n" );
		printf( "|      3.  Import Session Key by RSA Internal Private  Key Decrypted.      \n" );
		printf( "|      4.  The RSA DigitEnvelope.                                          \n" );
		printf( "|                                                                          \n" );
		printf( "|      5.  Generate Session Key by SM2 Internal Public Key Encrypted.      \n" );
		printf( "|      6.  Generate Session Key by SM2 External Public Key Encrypted.      \n" );
		printf( "|      7.  Import Session Key by SM2 Internal Private  Key Decrypted.      \n" );
		printf( "|      8.  The SM2 DigitEnvelope.                                          \n" );
		printf( "|                                                                          \n" );
		printf( "|      9.  The SM2 Agreement Session Key.                                  \n" );
		printf( "|                                                                          \n" );
		printf( "|      10.  Generate Session Key by KEK.                                   \n" );
		printf( "|      11.  Import Session Key by KEK                                      \n" );
		printf( "|                                                                          \n" );
		printf( "|      12.  Generate Session Key by Session Key.                           \n" );
		printf( "|      13.  Import Session Key by Session Key.                             \n" );
		printf( "|                                                                          \n" );
		printf( "|      0.  Return.                                                         \n" );
		printf( "|                                                                          \n" );
		printf( "----------------------------------------------------------------------------\n" );
		printf( "\nPlease Select:" );
		scanf( "%d", &sel );

		switch( sel )
		{
		case 1: // Generate Session Key by RSA Internal Public Key Encrypted.
			printf( "Please Input RSA Key Pair Index [ 1 - 64 ]: " );
			scanf( "%d", &rsaindex );
			if ( 1 > rsaindex || 64 < rsaindex ) {
				printf( "\n The RSA Key Pair Index[%d] invalid.\n\n", rsaindex );
				break;
			}
			
			rv = SDF_GenerateKeyWithIPK_RSA( hSessionHandle,
				rsaindex, 128, cipherKey, (unsigned int*)&cipherKeyLen, (void**)&phKeyHandle);
			if ( rv ) {
				printf( "\nSDF_GenerateKeyWithIPK_RSA error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nGenerate Session Key by RSA Internal Public Key Encrypted OKOK.\n\n" );
			PrintBuf( "cipherKey", cipherKey, cipherKeyLen );
			writeFile( FNAME_RSACIPHERKEY, (unsigned char*)cipherKey, cipherKeyLen);
			printf("\n\n");

			break;
		case 2: // Generate Session Key by RSA External Public Key Encrypted.
			memset(&rsapubkey, 0x0, sizeof(rsapubkey));
			memset(&rsaprikey, 0x0, sizeof(rsaprikey));
			rv = SDF_GenerateKeyPair_RSA( hSessionHandle, 1024, &rsapubkey, &rsaprikey);
			if ( rv ) {
				printf( "\nSDF_GenerateKeyPair_RSA error. rv = 0x%08x. \n\n", rv );
				break;
			}

			rv = SDF_GenerateKeyWithEPK_RSA( hSessionHandle,
				128, &rsapubkey, cipherKey1, (unsigned int*)&cipherKeyLen1, (void **)&phKeyHandle);
			if ( rv ) {
				printf( "\nSDF_GenerateKeyWithEPK_RSA error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nGenerate Session Key by RSA External Public Key Encrypted OKOK.\n\n" );
			PrintBuf( "cipherKey", cipherKey1, cipherKeyLen1 );
			writeFile( FNAME_RSACIPHERKEY, (unsigned char*)cipherKey1, cipherKeyLen1);
			printf("\n\n");

			break;

		case 3: // Import Session Key by RSA Internal Private  Key Decrypted.
			printf( "Please Input RSA Key Pair Index [ 1 - 64 ]: " );
			scanf( "%d", &rsaindex );
			if ( 1 > rsaindex || 64 < rsaindex ) {
				printf( "\n The RSA Key Pair Index[%d] invalid.\n\n", rsaindex );
				break;
			}

			printf( "Please Input Internal RSA Private Key PassWord: " );
			scanf( "%s", pwd );
			
			rv = SDF_GetPrivateKeyAccessRight(hSessionHandle, rsaindex, (unsigned char*)pwd, strlen(pwd) );
			if ( rv ) {
				printf( "\nSDF_GetPrivateKeyAccessRight error. rv = 0x%08x. \n\n", rv );
				SDF_ReleasePrivateKeyAccessRight(hSessionHandle, rsaindex);
				break;
			}
			
			readFile(FNAME_RSACIPHERKEY, cipherKey, &cipherKeyLen);
			rv = SDF_ImportKeyWithISK_RSA( hSessionHandle,
				rsaindex, cipherKey, cipherKeyLen, (void**)&phKeyHandle);
			if ( rv ) {
				printf( "\nSDF_ImportKeyWithISK_RSA error. rv = 0x%08x. \n\n", rv );
				SDF_ReleasePrivateKeyAccessRight(hSessionHandle, rsaindex);
				break;
			}

			SDF_ReleasePrivateKeyAccessRight(hSessionHandle, rsaindex);

			printf( "\nImport Session Key by RSA Internal Private  Key Decrypted OKOK.\n\n" );

			break;

		case 4: // The RSA DigitEnvelope. 
			printf( "Please Input RSA Key Pair Index [ 1 - 64 ]: " );
			scanf( "%d", &rsaindex );
			if ( 1 > rsaindex || 64 < rsaindex ) {
				printf( "\n The RSA Key Pair Index[%d] invalid.\n\n", rsaindex );
				break;
			}

			memset(&rsapubkey, 0x0, sizeof(rsapubkey));
			memset(&rsaprikey, 0x0, sizeof(rsaprikey));
			rv = SDF_GenerateKeyPair_RSA( hSessionHandle, 1024, &rsapubkey, &rsaprikey);
			if ( rv ) {
				printf( "\nSDF_GenerateKeyPair_RSA error. rv = 0x%08x. \n\n", rv );
				break;
			}

			readFile(FNAME_RSACIPHERKEY, cipherKey, &cipherKeyLen);
			
			rv = SDF_ExchangeDigitEnvelopeBaseOnRSA( hSessionHandle,
				rsaindex, &rsapubkey, cipherKey, cipherKeyLen, cipherKey1, (unsigned int*)&cipherKeyLen1);
			if ( rv ) {
				printf( "\nSDF_ExchangeDigitEnvelopeBaseOnRSA error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nThe RSA DigitEnvelope OKOK.\n\n" );
			PrintBuf( "cipherKey", cipherKey1, cipherKeyLen1 );
			printf("\n\n");

			break;
		case 5: // Generate Session Key by SM2 Internal Public Key Encrypted.

			printf( "Please Input SM2 Key Pair Index [ 1 - 64 ]: " );
			scanf( "%d", &sm2index );
			if ( 1 > sm2index || 64 < sm2index ) {
				printf( "\n The SM2 Key Pair Index[%d] invalid.\n\n", sm2index );
				break;
			}

			rv = SDF_GenerateKeyWithIPK_ECC( hSessionHandle,
				sm2index, 128, &sm2cipherkey, (void**)&phKeyHandle);
			if ( rv ) {
				printf( "\nSDF_GenerateKeyWithIPK_ECC error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nGenerate Session Key by SM2 Internal Public Key Encrypted OKOK.\n\n" );

			printf("sm2cipherkey_L is %d.\n", 32);
			PrintBuf( "cipherKey", sm2cipherkey.C, 32 );

			memcpy(tmp, &sm2cipherkey.x[32], 32);
			memcpy(&tmp[32], &sm2cipherkey.y[32], 32);
			memcpy(&tmp[64], &sm2cipherkey.C, sm2cipherkey.L);
			memcpy(&tmp[64+sm2cipherkey.L], sm2cipherkey.M, 32);

			writeFile(FNAME_SM2CIPHERKEY, tmp, 96+sm2cipherkey.L);
			printf("\n\n");

			printf( "\nThe new session key Encrypt Plain.\n\n" );
			
			plainlen = 128;
			readFile(FNAME_SESSIONPLAIN, plainData, (int *)&plainlen);
			PrintBuf( "Plain:", plainData, plainlen );

			rv = SDF_Encrypt(hSessionHandle, phKeyHandle, SGD_SM4_ECB, NULL, plainData, plainlen, cipherData, &cipherlen);
			if ( rv ) {
				printf( "\nSDF_Encrypt error. rv = 0x%08x. \n\n", rv );
				break;			
			}

			PrintBuf( "Cipher data:", cipherData, cipherlen );
			writeFile(FNAME_SESSIONCIPHER, cipherData, cipherlen);

			break;
		case 6: // Generate Session Key by SM2 External Public Key Encrypted.

			rv = SDF_GenerateKeyPair_ECC( hSessionHandle,
				PARAID, 256, &sm2pubkey, &sm2prikey );
			if ( rv ) {
				printf( "\nSDF_GenerateKeyPair_ECC error. rv = 0x%08x. \n\n", rv );
				break;
			}
			
			rv = SDF_GenerateKeyWithEPK_ECC( hSessionHandle,
				128, SGD_SM2_3, &sm2pubkey, &sm2cipherkey1, (void**)&phKeyHandle);
			if ( rv ) {
				printf( "\nSDF_GenerateKeyPair_ECC error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nGenerate Session Key by SM2 External Public Key Encrypted OKOK.\n\n" );
			PrintBuf( "cipherKey: ", sm2cipherkey1.C, sm2cipherkey1.L );

			memcpy(tmp, &sm2cipherkey1.x[32], 32);
			memcpy(&tmp[32], &sm2cipherkey1.y[32], 32);
			memcpy(&tmp[64], sm2cipherkey1.C, sm2cipherkey1.L);
			memcpy(&tmp[64+sm2cipherkey1.L], sm2cipherkey1.M, 32);

			writeFile(FNAME_SM2CIPHERKEY, tmp, 96+sm2cipherkey1.L);

			printf("\n\n");
			
			break;
		case 7: // Import Session Key by SM2 Internal Private  Key Decrypted. 
			printf( "Please Input SM2 Key Pair Index [ 1 - 64 ]: " );
			scanf( "%d", &rsaindex );
			if ( 1 > rsaindex || 64 < rsaindex ) {
				printf( "\n The RSA Key Pair Index[%d] invalid.\n\n", rsaindex );
				break;
			}

			printf( "Please Input Internal SM2 Private Key PassWord: " );
			scanf( "%s", pwd );
			
			rv = SDF_GetPrivateKeyAccessRight(hSessionHandle, rsaindex, (unsigned char*)pwd, strlen(pwd) );
			if ( rv ) {
				printf( "\nSDF_GetPrivateKeyAccessRight error. rv = 0x%08x. \n\n", rv );
				break;
			}

			cipherKeyLen = 2048;
			memset(&sm2cipherkey, 0, sizeof(ECCCipher));

			readFile(FNAME_SM2CIPHERKEY, tmp, &cipherKeyLen);

			memcpy(&sm2cipherkey.x[32], tmp, 32);
			memcpy(&sm2cipherkey.y[32], &tmp[32], 32);
			memcpy(&sm2cipherkey.C, &tmp[64], cipherKeyLen-96);
			sm2cipherkey.L = cipherKeyLen-96;
			memcpy(sm2cipherkey.M, &tmp[64+sm2cipherkey.L], 32);

			rv = SDF_ImportKeyWithISK_ECC( hSessionHandle,
				rsaindex, &sm2cipherkey, (void**)&phKeyHandle);
			if ( rv ) {
				printf( "\nSDF_ImportKeyWithISK_ECC error. rv = 0x%08x. \n\n", rv );
				SDF_ReleasePrivateKeyAccessRight(hSessionHandle, rsaindex);
				break;
			}

			SDF_ReleasePrivateKeyAccessRight(hSessionHandle, rsaindex);

			cipherlen = 256;
			readFile(FNAME_SESSIONCIPHER, cipherData, (int *)&cipherlen);
			rv = SDF_Decrypt(hSessionHandle, phKeyHandle, SGD_SM4_ECB, NULL, cipherData, cipherlen, decData, &declen);
			if ( rv ) {
				printf( "\nSDF_Encrypt error. rv = 0x%08x. \n\n", rv );
				break;			
			}

			PrintBuf( "Plain data:", decData, declen );
			printf( "\nImport Session Key by SM2 Internal Private  Key Decrypted OKOK.\n\n" );

			break;
		case 8: // The SM2 DigitEnvelope. 
			rv = SDF_GenerateKeyPair_ECC( hSessionHandle,
				PARAID, 256, &sm2pubkey, &sm2prikey );
			if ( rv ) {
				printf( "\nSDF_GenerateKeyPair_ECC error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nThe Generate SM2 Key pair OKOK.\n\n" );
			PrintBuf("SM2 pubKey_X:", sm2pubkey.x, 32);
			PrintBuf("SM2 pubKey_Y:", sm2pubkey.y, 32);
			PrintBuf("SM2 priKey_D:", sm2prikey.D, 32);

			cipherKeyLen = 2048;
			readFile(FNAME_SM2CIPHERKEY, tmp, &cipherKeyLen);
			memcpy(&sm2cipherkey.x[32], tmp, 32);
			memcpy(&sm2cipherkey.y[32], &tmp[32], 32);
			memcpy(&sm2cipherkey.C, &tmp[64], cipherKeyLen-96);
			sm2cipherkey.L = cipherKeyLen-96;
			memcpy(sm2cipherkey.M, &tmp[64+sm2cipherkey.L], 32);

			rv = SDF_ExchangeDigitEnvelopeBaseOnECC( hSessionHandle,
				sm2index, SGD_SM2_3, &sm2pubkey, &sm2cipherkey, &sm2cipherkey1);
			if ( rv ) {
				printf( "\nSDF_ExchangeDigitEnvelopeBaseOnECC error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nThe sm2 DigitEnvelope OKOK.\n\n" );
			PrintBuf("sm2cipherkey1_X", sm2cipherkey1.x, 32);
			PrintBuf("sm2cipherkey1_Y", sm2cipherkey1.y, 32);
			PrintBuf("sm2cipherkey1_M", sm2cipherkey1.M, 32);
			printf("sm2cipherkey1_L is %d.\n", 32);
			PrintBuf( "cipherKey", sm2cipherkey1.C, 32 );
			printf("\n\n");

			rv = SDF_ExternalDecrypt_ECC(hSessionHandle, PARAID, &sm2prikey, &sm2cipherkey1,decData, &declen );
			if ( rv  ) {
				printf( "\nSDF_ExternalDecrypt_ECC error. rv = 0x%08x. \n\n", rv );
				break;
			}

			printf( "\nDecrypt Session Key  OKOK.\n\n" );
			PrintBuf( "Session Key plain:", decData, declen );

			rv = SDF_ImportKey( hSessionHandle, decData, declen, &phKeyHandle );
			if ( rv )
			{
				printf( "Import Session Key(SM4) Failed, 0x%08X.\n", rv );
				return;
			}
			printf( "Import Session Key(SM4) OKOK.\n\n" );

			rv = SDF_Decrypt(hSessionHandle, phKeyHandle, SGD_SM4_ECB, NULL,cipherData, cipherlen,  decData, &declen);
			if ( rv ) {
				printf( "\nSDF_Decrypt error. rv = 0x%08x. \n\n", rv );
				break;			
			}
			printf( "Decrypt cipher data OKOK.\n\n" );
			PrintBuf( "Session Decrypt plain:", decData, declen );

			break;
		case 9: //  The SM2 Agreement Session Key. 
			printf( "Please Agreement1 SM2 Key Pair Index [ 1 - 64 ]: " );
			scanf( "%d", &rsaindex );
			if ( 1 > rsaindex || 64 < rsaindex ) {
				printf( "\n The RSA Key Pair Index[%d] invalid.\n\n", rsaindex );
				break;
			}

			rv = SDF_GenerateAgreementDataWithECC(hSessionHandle, rsaindex, 128, 
				selfid, selfidlen, 
				&pucSponsorPublicKey, &pucSponsorTmpPublicKey,
				(void **)&st_agreement);
			if(rv) {
				printf("SDF_GenerateAgreementDataWithECC Failed!!! Error: %#x!\r\n", rv);
				break ;
			}

			printf( "Please Agreement2 SM2 Key Pair Index [ 1 - 64 ]: " );
			scanf( "%d", &rsaindex );
			if ( 1 > rsaindex || 64 < rsaindex ) {
				printf( "\n The RSA Key Pair Index[%d] invalid.\n\n", rsaindex );
				break;
			}

			rv = SDF_GenerateAgreementDataAndKeyWithECC(hSessionHandle, rsaindex, 128, 
				otherid, otheridlen,
				selfid,  selfidlen, 
				&pucSponsorPublicKey, &pucSponsorTmpPublicKey,
				&pucResponsePublicKey, &pucResponseTmpPublicKey,
				&hkeyhandle1);
			if(rv) {
				printf("SDF_GenerateAgreementDataAndKeyWithECC Failed!!! Error: %#x!\r\n", rv);
				break ;
			}
	
			rv = SDF_GenerateKeyWithECC(hSessionHandle, 
				otherid, otheridlen, 
				&pucResponsePublicKey, &pucResponseTmpPublicKey,
				st_agreement,
				&hkeyhandle2);
			if(rv) {
				printf("SDF_GenerateAgreementDataAndKeyWithECC Failed!!! Error: %#x!\r\n", rv);
				break ;
			}

			printf( "\nThe SM2 Agreement Session Key OKOK.\n\n" );

			break;
		case 10: // Generate Session Key by KEK.  
			printf( "Please Input KEK Index [ 1 - 128 ]: " );
			scanf( "%d", &iKeyIndex );
			if ( 1 > iKeyIndex || 2048 < iKeyIndex ) {
				printf( "\n The KEK Index[%d] invalid.\n\n", iKeyIndex );
				break;
			}

			rv = SDF_GenerateKeyWithKEK( hSessionHandle, 
				128, SGD_SM1_ECB, iKeyIndex, cipherKey, (unsigned int*)&cipherKeyLen, (void**)&phKeyHandle);
			if ( rv ) {
				printf("SDF_GenerateKeyWithKEK Failed!!! Error: %#x!\r\n", rv);
				break ;
			}

			printf( "\nGenerate Session Key by KEK OKOK.\n\n" );
			PrintBuf( "cipherKey", cipherKey, cipherKeyLen );
			printf("\n\n");

			break;
		case 11: // Import Session Key by KEK
			printf( "Please Input KEK Index [ 1 - 128 ]: " );
			scanf( "%d", &iKeyIndex );
			if ( 1 > iKeyIndex || 2048 < iKeyIndex ) {
				printf( "\n The KEK Index[%d] invalid.\n\n", iKeyIndex );
				break;
			}

			rv = SDF_ImportKeyWithKEK( hSessionHandle,
				SGD_SM1_ECB, iKeyIndex, cipherKey, cipherKeyLen, (void**)&phKeyHandle);
			if ( rv ) {
				printf("SDF_ImportKeyWithKEK Failed!!! Error: %#x!\r\n", rv);
				break ;
			}

			printf( "\nImport Session Key by KEK OKOK.\n\n" );
			printf("\n\n");

			break;
		case 12: // Generate Session Key by Session Key.  
			rv = SDF_ImportKey(hSessionHandle, ucSessKey, 16, &hSessKey);
			if ( rv ) {
				printf("SDF_ImportKey Failed!!! Error: %#x!\r\n", rv);
				break ;
			}

			rv = SDF_GenerateKeyWithSK( hSessionHandle, 
				128, SGD_SM1_ECB, hSessKey, cipherKey, (unsigned int*)&cipherKeyLen, (void**)&phKeyHandle);
			if ( rv ) {
				printf("SDF_GenerateKeyWithSK Failed!!! Error: %#x!\r\n", rv);
				SDF_DestoryKey(hSessionHandle,hSessKey);
				break ;
			}

			SDF_DestoryKey(hSessionHandle,hSessKey);
			SDF_DestoryKey(hSessionHandle,phKeyHandle);
			printf( "\nGenerate Session Key by KEK OKOK.\n\n" );
			PrintBuf( "cipherKey", cipherKey, cipherKeyLen );
			printf("\n\n");

			break;
		case 13: // Import Session Key by Session Key

			rv = SDF_ImportKey(hSessionHandle, ucSessKey, 16, &hSessKey);
			if ( rv ) {
				printf("SDF_ImportKey Failed!!! Error: %#x!\r\n", rv);
				break ;
			}

			rv = SDF_ImportKeyWithSK( hSessionHandle,
				SGD_SM1_ECB, hSessKey, cipherKey, cipherKeyLen, (void**)&phKeyHandle);
			if ( rv ) {
				printf("SDF_ImportKeyWithSK Failed!!! Error: %#x!\r\n", rv);
				SDF_DestoryKey(hSessionHandle,hSessKey);
				break ;
			}

			SDF_DestoryKey(hSessionHandle,hSessKey);
			SDF_DestoryKey(hSessionHandle,phKeyHandle);
			printf( "\nImport Session Key by KEK OKOK.\n\n" );
			printf("\n\n");

			break;
		case 0:	
			return;
		default:
			printf( "Invalid Input, Press <Enter> Key to Continue...\n" );
			break;
		}
		getchar();
		getchar();
	}

}

void T_File(void *hSessionHandle )
{

	int rv, sel;
	char filename[64], input[64];
	int	 filelen;
	int uioffset=0; 
	unsigned int uibufflen;
	char writebuff[16*1024];
	unsigned char readbuff[8192+1];
	int keyid, keytype, certtype;

	int i;
	for(i=0; i<16*1024; i++)
	{
		writebuff[i] = i % 16;
	}
	
	for ( ; ; )
	{
		printf( "\n------------- Test SM2 Functions ------------\n" );
		printf( "|                                           |\n" );
		printf( "|      1.  File Create Test.                |\n" );
		printf( "|      2.  File Write Test.                 |\n" );
		printf( "|      3.  File Read Test.                  |\n" );
		printf( "|      4.  File Delete Test.                |\n" );
		printf( "|      5.  Export Cert File.                |\n");
		printf( "|                                           |\n" );
		printf( "|      0.  Return.                          |\n" );
		printf( "|                                           |\n" );
		printf( "---------------------------------------------\n" );
		printf( "\nPlease Select:" );
		scanf( "%d", &sel );

		switch( sel ) {
		case 1:  // File Create Test.
			printf( "Please Input File Name: " );
			scanf( "%s", filename );

			printf( "Please Input File Length: ");
			scanf("%s", input);
			filelen = atoi(input);
	//		rv = SDF_DeleteFile(hSessionHandle, (unsigned char*)filename, strlen(filename));
			
			rv = SDF_CreateFile(hSessionHandle, (unsigned char*)filename, strlen(filename), filelen);
			if(rv)
			{
				printf("SDF_CreateFile Failed!!! Error: %#x!\r\n", rv);
				break ;
			}

			printf( "\nThe Create file OKOK. file name[%s]\n\n", filename);
			printf("\n\n");

			break;
		case 2:  // File Write Test.
			printf( "Please Input File Name: " );
			scanf( "%s", filename );

			printf( "Please Input Write Offset: ");
			scanf("%s", input);
			uioffset = atoi(input);

			printf( "Please Input Write Length: ");
			scanf("%s", input);
			uibufflen = atoi(input);

			rv = SDF_WriteFile(hSessionHandle, (unsigned char*)filename, strlen(filename), uioffset, uibufflen, (unsigned char*)writebuff);
			if(rv)
			{
				printf("SDF_WriteFile Failed!!! Error: %#x!\r\n", rv);
				break ;
			}
			printf( "\nThe write file OKOK. file name[%s]\n\n", filename);
			PrintBuf( "write data", (unsigned char*)writebuff, uibufflen);

			printf("\n\n");

			break;
		case 3:  // File Read Test.
			printf( "Please Input File Name: " );
			scanf( "%s", filename );

			printf( "Please Input Read Offset: ");
			scanf("%s", input);
			uioffset = atoi(input);

			printf( "Please Input Read Length: ");
			scanf("%s", input);
			uibufflen = atoi(input);

			rv = SDF_ReadFile(hSessionHandle, (unsigned char*)filename, strlen(filename), uioffset, &uibufflen, readbuff);
			if(rv)
			{
				printf("SDF_ReadFile Failed!!! Error: %#x!\r\n", rv);
				break ;
			}
			printf( "\nThe read file OKOK. file name[%s]\n\n", filename);

			PrintBuf( "read data", (unsigned char*)readbuff, uibufflen);

			break;
		case 4:  // File Delete Test.
			printf( "Please Input File Name: " );
			scanf( "%s", filename );
			rv = SDF_DeleteFile(hSessionHandle, (unsigned char*)filename, strlen(filename));
			if(rv)
			{
				printf("SDF_DeleteFile Failed!!! Error: %#x!\r\n", rv);
				break ;
			}

			printf( "\nThe delete file OKOK. file name[%s]\n\n", filename);

			break;
		case 5:  // File Read Test.
			printf("Please Input Key Id: ");
			scanf("%d", &keyid);

			printf("Please Input Key Type(1-RSA;2-SM2): ");
			scanf("%d", &keytype);

			printf("Please Input Cert Type(0-Root;1-SignCert;2-EncCert): ");
			scanf("%d", &certtype);

			uibufflen = 8192;
			rv = SDF_ExportCert_Ex(hSessionHandle, keyid, keytype, certtype, readbuff, &uibufflen);
			if (rv)
			{
				printf("SDF_ExportCert_Ex Failed!!! Error: %#x!\r\n", rv);
				break;
			}

			PrintBuf("cert data", (unsigned char*)readbuff, uibufflen);
		case 0:	
			return;
		default:
			printf( "Invalid Input, Press <Enter> Key to Continue...\n" );
			break;
		}
		getchar();
		getchar();
	}
}

void T_DevInfo(void *hSessionHandle )
{
	int rv, i;
	char DeviceSerial[32];
	DEVICEINFO definfo;
	
	memset(&definfo, 0x0, sizeof(definfo));

	rv = SDF_GetDeviceInfo( hSessionHandle, &definfo);
	if ( rv ) {
		printf("SDF_GetDeviceInfo Failed!!! Error: %#x!\r\n", rv);
		return ;
	}

	memcpy(DeviceSerial,definfo.DeviceSerial,16);
	DeviceSerial[16] = 0x0;
	printf("IssuerName: %s.\n", definfo.IssuerName);
	printf("DeviceName: %s.\n", definfo.DeviceName);
	printf("DeviceSerial: ");
	for(i=0; i<16; i++)
		printf("%02X", (unsigned char)DeviceSerial[i]);
	printf("\n");
	printf("DeviceVersion: 0x%08x \n", definfo.DeviceVersion);
	printf("StandardVersion: 0x%08x  \n", definfo.StandardVersion);
	printf("AsymAlgAbility1: 0x%08x  \n", definfo.AsymAlgAbility[0]);
	printf("AsymAlgAbility2: 0x%08x  \n", definfo.AsymAlgAbility[1]);
	printf("SymAlgAbility: 0x%08x  \n", definfo.SymAlgAbility);
	printf("HashAlgAbility: 0x%08x  \n", definfo.HashAlgAbility);
	printf("BufferSize: 0x%08x  \n", definfo.BufferSize);
}

void T_GetKeyInfo(void *hSessionHandle )
{
	int rv;
	unsigned int keyindex, keytype, cvLen;
	unsigned char cv[16] = {0};
	char tag[32];
	
	printf("Please input key index [1-128]:  ");
	scanf("%d", &keyindex);

	rv = SDF_GetSymmKeyInfo( hSessionHandle, keyindex, &keytype, cv, &cvLen, tag);
	if ( rv ) {
		printf("SDF_GetSymmKeyInfo Failed!!! Error: %#x!\r\n", rv);
		return ;
	}

	printf("The key information at index %d is:\n", keyindex);
	switch(keytype){
	case 'P':
		printf("Type is: SM1\n");
		break;
	case 'R':
		printf("Type is: SM4\n");
		break;
	case 'X':
		printf("Type is: DES\n");
		break;
	case 'Y':
		printf("Type is: DES2\n");
		break;
	case 'Z':
		printf("Type is: DES3\n");
		break;
	default:
		printf("Type is: Unknown\n");
		return;
	}
	PrintBuf("cv", cv, cvLen);

	printf("The Label of this key: %s\n", tag);

	printf("\n");
}

void PrintBuf( char *title, unsigned char *buf, int buflen ) 
{
#if 1
	int i;
	printf( "%s[%d]:\n", title, buflen);
	for(i=0; i<(int)buflen; i++) 
	{
		printf("%02x ", buf[i]);
		if ( i % 16 == 15)
			printf( "\n" );
	}
	printf("\n");
	return;
#endif
}

int Hstr2Barr(const char *src, int maxLength, unsigned char *dest)
{
	char dummy[8192+1];
	int temp, i = 0;
	strncpy(dummy, src, maxLength*2+1);
	dummy[maxLength*2] = '\0';
	while (sscanf(&(dummy[i*2]), "%02x", &temp) > 0)
	{
		dest[i] = temp;
		i++;
		if(i*2 >= maxLength)
			break;
	}
	return i;
}

int Barr2Hstr(const unsigned char *src, int minLength, char *dest)
{
	char tmp[3] = {0};
	int i = 0;
	while (sprintf(tmp, "%02X", src[i]) > 0)
	{
		dest[i*2] = tmp[0];
		dest[i*2 + 1] = tmp[1];
		i++;

		if(i >= minLength)
			break;
	}
	return i*2;	
}

int readFile(char *fname, unsigned char *readbuf, int *buflen) 
{
	FILE *fp;
	int flen;
	char filename[128];

	char buf[8192];
	int len;
	sprintf( filename, "./data/%s", fname );
	fp = fopen(filename, "rb" );
	if ( fp == NULL )
	{
		printf( "Can't Open File [ %s ].\n", fname );
		return -1;
	}

	fseek( fp, 0, SEEK_SET );
	fseek( fp, 0, SEEK_END );
	flen = ftell( fp );
	fseek( fp, 0, SEEK_SET );

	if(flen % 2) 
		flen -= 1;
	printf("flen: %d\n", flen);

	if ( flen > (*buflen)*2 )
	{
		fclose( fp );
		printf( "Buffer Length[%d] < File Length[%d].\n", *buflen, flen );
		return -2;
	}

	*buflen = fread( buf, 1, flen, fp );
	fclose( fp );
	if ( *buflen != flen )
	{
		printf( "Read File [%s] Failed.\n", fname );
		return -3;
	}
	else
	{
		len = Hstr2Barr((const char *)buf, *buflen, (unsigned char *)readbuf);
		*buflen = len;
		printf( "Read File [%s] OKOK.\n", fname );
	}

	return 0;
}

int readFileString(char *fname, unsigned char *readbuf, int *buflen) 
{
	FILE *fp;
	int flen;
	char filename[128];

	char buf[8192];
	sprintf( filename, "./data/%s", fname );
	fp = fopen(filename, "rb" );
	if ( fp == NULL )
	{
		printf( "Can't Open File [ %s ].\n", fname );
		return -1;
	}

	fseek( fp, 0, SEEK_SET );
	fseek( fp, 0, SEEK_END );
	flen = ftell( fp );
	
	if(flen % 2) 
		flen -= 1;
	printf("flen: %d\n", flen);

	fseek( fp, 0, SEEK_SET );

	if ( flen > (*buflen)*2 )
	{
		fclose( fp );
		printf( "Buffer Length[%d] < File Length[%d].\n", *buflen, flen );
		return -2;
	}

	*buflen = fread( buf, 1, flen, fp );
	fclose( fp );
	if ( *buflen != flen )
	{
		printf( "Read File [%s] Failed.\n", fname );
		return -3;
	}
	else
	{
		memcpy(readbuf, buf, *buflen);
		printf( "Read File [%s] OKOK.\n", fname );
	}

	return 0;
}

int writeFile( char *fname, unsigned char *writebuf, int buflen) 
{
	FILE *fp;
	int flen;
	char filename[128];
	int  len;
	char buf[8192*2];
	sprintf( filename, "./data/%s", fname );
	fp = fopen( filename, "wb+" );
	if ( fp == NULL )
	{
		printf( "Can't Open File [ %s ].\n", fname );
		return -1;
	}

	len = Barr2Hstr(writebuf, buflen, buf);

	flen = fwrite( buf, 1, len, fp );
	fclose( fp );
	if ( len != flen )
	{
		printf( "Write File [%s] Failed.\n", fname );
		return -3;
	}
	else
	{
		printf( "Write File [%s] OKOK.\n", fname );
	}
	return 0;
}

