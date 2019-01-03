/*----------------------------------------------------------------------|
|	SDF.h - Header file 												|
|	Version :	2.0														|												|
|	Copyright : ���������찲�Ƽ����޹�˾.	|
|----------------------------------------------------------------------*/

#ifndef _SDF_H
#define _SDF_H

#define MAX_SESSIONS 2560   /*���򿪻Ự��*/
#ifndef NULL 
#define NULL 0
#endif

#include <stdio.h>

#ifdef UNIX
	#define DLL
	#define WINAPI 
#else
	#include <Windows.h>
	#define DLL _declspec (dllexport)
#endif

/*
���ƣ� �豸��Ϣ�ṹ��
��Ա��
		����		���ݳ��ȣ��ֽڣ�	����
	IssuerName			40				�豸������������
	DeviceName			16				�豸�ͺ�
	DeviceSerial		16				�豸��ţ����������ڣ�8�ַ��������κţ�3�ַ�������ˮ�ţ�5�ַ���
	DeviceVersion		4				�����豸�ڲ�����İ汾��
	StandardVersion		4				�����豸֧�ֵĽӿڹ淶�汾��
	AsymAlgAbility		8				ǰ4�ֽڱ�ʾ֧�ֵ��㷨,��ʾ����Ϊ�ǶԳ��㷨��ʶ��λ��Ľ������4�ֽڱ�ʾ�㷨�����ģ������ʾ����Ϊ֧�ֵ�ģ����λ��Ľ��
	SymAlgAbility		4				����֧�ֵĶԳ��㷨����ʾ����Ϊ�Գ��㷨��ʶ��λ��������
	HashAlgAbility		4				����֧�ֵ��Ӵ��㷨����ʾ����Ϊ�Ӵ��㷨��ʶ��λ��������
	BufferSize			4				֧�ֵ�����ļ��洢�ռ䣨��λ�ֽڣ�
*/
typedef struct DeviceInfo_st{
       unsigned char IssuerName[40];
       unsigned char DeviceName[16];
       unsigned char DeviceSerial[16];
       unsigned int  DeviceVersion;
       unsigned int  StandardVersion;
       unsigned int  AsymAlgAbility[2];
       unsigned int  SymAlgAbility;
       unsigned int  HashAlgAbility;
       unsigned int  BufferSize;
}DEVICEINFO;


#define RSAref_MAX_BITS    2048
#define RSAref_MAX_LEN     ((RSAref_MAX_BITS + 7) / 8)
#define RSAref_MAX_PBITS   ((RSAref_MAX_BITS + 1) / 2)
#define RSAref_MAX_PLEN    ((RSAref_MAX_PBITS + 7)/ 8)

/*
���ƣ� RSA��Կ�ṹ��
��Ա��
	����			���ݳ��ȣ��ֽڣ�	����
	bits				4				ģ��
	M				RSAref_MAX_LEN		ģN
	E				RSAref_MAX_LEN		ָ��
*/
typedef struct RSArefPublicKey_st
{
	unsigned int  bits;
	unsigned char m[RSAref_MAX_LEN];
	unsigned char e[RSAref_MAX_LEN];
} RSArefPublicKey;


/*
���ƣ� RSA˽Կ�ṹ��
��Ա��
	����			���ݳ��ȣ��ֽڣ�			����
	bits				4						ģ��
	M				RSAref_MAX_LEN				ģN
	E				RSAref_MAX_LEN				ָ��
	D				RSAref_MAX_LEN				ģD
	prime[2]		RSAref_MAX_PLEN * 2			����p��q
	pexp[2]			RSAref_MAX_PLEN * 2			Dp ��Dq
	coef			RSAref_MAX_PLEN				ϵ��i
*/

typedef struct RSArefPrivateKey_st
{
	unsigned int  bits;
	unsigned char m[RSAref_MAX_LEN];
	unsigned char e[RSAref_MAX_LEN];
	unsigned char d[RSAref_MAX_LEN];
	unsigned char prime[2][RSAref_MAX_PLEN];
	unsigned char pexp[2][RSAref_MAX_PLEN];
	unsigned char coef[RSAref_MAX_PLEN];
} RSArefPrivateKey;

#define ECCref_MAX_BITS			512 
#define ECCref_MAX_LEN			((ECCref_MAX_BITS+7) / 8)

/*
���ƣ� ECC��Կ�ṹ��
��Ա��
	����			���ݳ��ȣ��ֽڣ�	����
	bits				4				ģ��
	x					ECCref_MAX_LEN	��Կx����
	y					ECCref_MAX_LEN	��Կy����
*/
typedef struct ECCrefPublicKey_st
{
	unsigned int  bits;
	unsigned char x[ECCref_MAX_LEN]; 
	unsigned char y[ECCref_MAX_LEN]; 
}ECCrefPublicKey;

/*
���ƣ� ECC˽Կ�ṹ��
��Ա��
	����			���ݳ��ȣ��ֽڣ�	����
	bits				4				ģ��
	D				ECCref_MAX_LEN		˽Կ
*/
typedef struct ECCrefPrivateKey_st
{
    unsigned int  bits;
    unsigned char D[ECCref_MAX_LEN];
} ECCrefPrivateKey;

/*
���ƣ� ECC�������ݽṹ��
��Ա��
	����			���ݳ��ȣ��ֽڣ�	����
	x				ECCref_MAX_LEN		��y�����Բ�����ϵĵ㣨x��y��
	y				ECCref_MAX_LEN		��x�����Բ�����ϵĵ㣨x��y��
	M				ECCref_MAX_LEN		���ĵ�SM3�Ӵ�ֵ
	L				4					�������ݳ���
	C				136				��������,�֧��136�ֽ�
*/
typedef struct ECCCipher_st
{
	unsigned char x[ECCref_MAX_LEN];
	unsigned char y[ECCref_MAX_LEN];
	unsigned char M[32];
	unsigned int  L;
	unsigned char C[136];
}ECCCipher;

/*
���ƣ� ECCǩ�����ݽṹ��
��Ա��
	����			���ݳ��ȣ��ֽڣ�	����
	r				ECCref_MAX_LEN		ǩ����r����
	s				ECCref_MAX_LEN		ǩ����s����
*/
typedef struct ECCSignature_st
{
	unsigned char r[ECCref_MAX_LEN];	
	unsigned char s[ECCref_MAX_LEN];	
} ECCSignature;


/* ECC�������� */
//NIST��׼
#define NIST_FP_160           1

//NIST��׼
#define NIST_FP_192           2
#define NIST_FP_224           3
#define NIST_FP_256           4

//���ֱܾ�׼
#define OSCCA_FP_192          5
#define OSCCA_FP_256          6
#define OSCCA_NEWFP_256       7

#define PARAID       OSCCA_NEWFP_256

/*�ǶԳ��㷨���ƣ�*/
#define SGD_RSA                  0x00010000 /* RSA�㷨���� */
/*��ӻ���*/
#define SGD_RSA_SIGN_EX			 0x00010001  //����򵼳�RSAǩ������֤��Կʱʹ��
#define SGD_RSA_ENC_EX			 0x00010002  //����򵼳�RSA���ܻ������Կʱʹ��

#define SGD_SM2				     0x00020100  /* sm2�㷨 */
#define SGD_SM2_1	             0x00020200  //��Բ����ǩ���㷨
#define SGD_SM2_2	             0x00020400  //��Բ������Կ����Э��
#define SGD_SM2_3	             0x00020800  //��Բ���߼����㷨

/*�Գ��㷨���ƣ�*/
#define SGD_SM1_ECB             0x00000101 /* SCB2 ECB���ܻ��� */
#define SGD_SM1_CBC             0x00000102 /* SCB2 CBC���ܻ��� */
#define SGD_SM1_CFB             0x00000104 /* SCB2 CFB���ܻ��� */
#define SGD_SM1_OFB             0x00000108 /* SCB2 OFB���ܻ��� */
#define SGD_SM1_MAC             0x00000110 /* SCB2 MAC���ܻ��� */
#define SGD_SM1_OFB_OX          0x00000112 /* SCB2 OFB���ܻ��� ��չ���*/

#define SGD_SSF33_ECB           0x00000201 /* SSF33 ECB���ܻ��� */
#define SGD_SSF33_CBC           0x00000202 /* SSF33 CBC���ܻ��� */
#define SGD_SSF33_CFB           0x00000204 /* SSF33 CFB���ܻ��� */
#define SGD_SSF33_OFB           0x00000208 /* SSF33 OFB���ܻ��� */
#define SGD_SSF33_MAC           0x00000210 /* SSF33 MAC���ܻ��� */

#define SGD_SM4_ECB             0x00000401 /* SM4 ECB���ܻ��� */
#define SGD_SM4_CBC             0x00000402 /* SM4 CBC���ܻ��� */
#define SGD_SM4_CFB             0x00000404 /* SM4 CFB���ܻ��� */
#define SGD_SM4_OFB             0x00000408 /* SM4 OFB���ܻ��� */
#define SGD_SM4_MAC             0x00000410 /* SM4 MAC���ܻ��� */

#define SGD_DES_ECB             0x00000501 /* DES ECB���ܻ��� */
#define SGD_DES_CBC             0x00000502 /* DES CBC���ܻ��� */
#define SGD_3DES_ECB            0x00000504 /* 3DES ECB���ܻ��� */
#define SGD_3DES_CBC            0x00000508 /* 3DES CBC���ܻ��� */

#define SGD_SM7_ECB				0x00000601 /* SM7 ECB���ܻ��� */
#define SGD_SM7_OFB				0x00000608 /* SM4 OFB���ܻ��� */

/*HASH�㷨���� */
#define SGD_SM3                 0x00000001  /*SM3�㷨���� */
#define SGD_SHA1                0x00000002 /* SHA-1�㷨���� */
#define SGD_SHA256	            0x00000004	/*SHA256�Ӵ��㷨 */

/*ZUC�㷨���� */
#define SGD_ZUC_STREAM            0x00000011  /*ZUC������Կ�� */
#define SGD_ZUC_EEA             0x00000012 /* ZUC EEA�ӽ��� */
#define SGD_ZUC_EIA	            0x00000014	/*ZUC EIA MAC   */

//�ڲ��Ự���
#define NULLKEYID 0xFFFFFFFF

typedef struct Handle_struct{
	unsigned int uiHandlemark;
	unsigned int uiHandlecode;
	unsigned int uiKeynumber; //��ȡ��˽ԿȨ�޸���
	unsigned int uiKeyindex[32];//��ȡ��˽ԿȨ������
	//unsigned int uiHashalg;//hash �㷨��ʶ
	unsigned int uiContextlen;
	unsigned char ucHashContext[512];//����hash����Ҫ��������
}Handlestruct;                /* ����ṹ */

//�ڲ��豸�ṹ��
typedef struct Device_struct{
	unsigned int uiDevicemark;
	unsigned int uiDevicecode;
}Devicestruct;


//��ԿЭ�̵���������
typedef struct Agreement_st
{
	unsigned int uiAgreementcode;
	unsigned int uiISKIndex;
	unsigned int uiKeyBits;
	unsigned int uiSponsorIDLength;
	unsigned char pucSelfID[ECCref_MAX_LEN * 2];
	ECCrefPublicKey  pucSelfTmpPublicKey;
	ECCrefPrivateKey pucSelfTmpPrivateKey;
} Agreement;

#define MAXCMDLEN		4096
#define MAXREVLEN		4096


/*---functions---*/
#ifdef __cplusplus
extern "C" {
#endif

/* 
������		�������豸
������		phDeviceHandle[out]	�����豸���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		phDeviceHandle�ɺ�����ʼ������д����
 */
DLL int WINAPI SDF_OpenDevice(void **phDeviceHandle);


/* 
������		�ر������豸�����ͷ������Դ
������		hDeviceHandle[in]	�Ѵ򿪵��豸���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
 */
DLL int WINAPI SDF_CloseDevice(void *hDeviceHandle);


/*
������		�����������豸�ĻỰ
������		hDeviceHandle[in]	�Ѵ򿪵��豸���
			phSessionHandle[out]	�����������豸�������»Ự���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_OpenSession(void *hDeviceHandle, void **phSessionHandle);

/* 
������		�ر��������豸�ѽ����ĻỰ�����ͷ������Դ
������		hSessionHandle [in]	�������豸�ѽ����ĻỰ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
 */
DLL int WINAPI SDF_CloseSession(void *hSessionHandle);

/* 
������	��ȡ�����豸��������
������	hSessionHandle[in]	���豸�����ĻỰ���
		pstDeviceInfo [out]	�豸����������Ϣ�����ݼ���ʽ���豸��Ϣ����
����ֵ��	0	�ɹ�
	��0	ʧ�ܣ����ش������
 */
DLL int WINAPI SDF_GetDeviceInfo(void *hSessionHandle,DEVICEINFO *pstDeviceInfo);

/* 
������		��ȡָ�����ȵ������
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiLength[in]	����ȡ�����������
			pucRandom[out]	������ָ�룬���ڴ�Ż�ȡ�������
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_GenerateRandom(void *hSessionHandle, 
					       unsigned int  uiLength,
					       unsigned char *pucRandom);

/* 
������		��ȡ�����豸�ڲ��洢��ָ������˽Կ��ʹ��Ȩ
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyIndex[in]	�����豸�洢˽Կ������ֵ
			pucPassword[in]	ʹ��˽ԿȨ�޵ı�ʶ��
			uiPwdLength[in]	˽ԿȨ�ޱ�ʶ�볤�ȣ�������8�ֽ�
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		���淶�漰�����豸�洢����Կ������ֵ�ĵ���ʼ����ֵΪ1�����Ϊn�������豸��ʵ�ʴ洢��������nֵ�� 
 */
DLL int WINAPI SDF_GetPrivateKeyAccessRight(void *hSessionHandle, 
                                     unsigned int  uiKeyIndex,
                                     unsigned char *pucPassword,
                                     unsigned int  uiPwdLength);

/*
������		��ȡ�����豸�ڲ��洢��ָ������˽Կ��ʹ��Ȩ
������		hSessionHandle[in]	���豸�����ĻỰ���
uiKeyIndex[in]	�����豸�洢˽Կ������ֵ
uiKeyType[in]	�����豸�洢˽Կ������, 1-rsa, 2-sm2
pucPassword[in]	ʹ��˽ԿȨ�޵ı�ʶ��
uiPwdLength[in]	˽ԿȨ�ޱ�ʶ�볤�ȣ�������8�ֽ�
����ֵ��	0	�ɹ�
��0	ʧ�ܣ����ش������
��ע��		���淶�漰�����豸�洢����Կ������ֵ�ĵ���ʼ����ֵΪ1�����Ϊn�������豸��ʵ�ʴ洢��������nֵ��
*/
DLL int WINAPI SDF_GetPrivateKeyAccessRight_Ex(void *hSessionHandle,
	unsigned int  uiKeyIndex,
	unsigned int  uiKeyType,
	unsigned char *pucPassword,
	unsigned int  uiPwdLength);

/* 
������		�ͷ������豸�洢��ָ������˽Կ��ʹ����Ȩ
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyIndex[in]	�����豸�洢˽Կ����ֵ
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
 */
DLL int WINAPI SDF_ReleasePrivateKeyAccessRight(void *hSessionHandle, 
                                         unsigned int  uiKeyIndex);

 /* 
������		���������豸�ڲ��洢��ָ������λ�õĶԳ���Կ�������Ա��Ȩ����
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyIndex[in]		�����豸�洢�ĶԳ���Կ������ֵ�����ڵ�����
			pucInternalKey[out]	�Գ���Կ����
			uiKeyLen			�Գ���Կ����
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ExportSymmKey_Ex(void *hSessionHandle, 
								unsigned int  uiKeyIndex,
                                unsigned char *pucInternalKey,
								unsigned int  *uiKeyLen);

 /* 
������		���������豸�ڲ��洢��ָ������λ�õ�ǩ����Կ
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyIndex[in]	�����豸�洢��RSA��Կ������ֵ
			pucPublicKey[out]	RSA��Կ�ṹ
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/                              
DLL int WINAPI SDF_ExportSignPublicKey_RSA(void *hSessionHandle, 
                                    unsigned int  uiKeyIndex,
                                    RSArefPublicKey *pucPublicKey);

/*

������		���������豸�ڲ��洢��ָ������λ�õ�ǩ����Կ
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyIndex[in]	�����豸�洢��ECC��Կ������ֵ
			pucPublicKey[out]	ECC��Կ�ṹ
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ExportSignPublicKey_ECC(void *hSessionHandle, 
                                 unsigned int  uiKeyIndex,
                                 ECCrefPublicKey *pucPublicKey);

/* 
������		���������豸�ڲ��洢��ָ������λ�õļ��ܹ�Կ
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyIndex[in]	�����豸�洢��ECC��Կ������ֵ
			pucPublicKey[out]	ECC��Կ�ṹ
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
 */
DLL int WINAPI SDF_ExportEncPublicKey_ECC(void *hSessionHandle, 
								unsigned int  uiKeyId,
								ECCrefPublicKey *pucPublicKey);

/* 
������		���������豸�ڲ��洢��ָ������λ�õļ��ܹ�Կ
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyIndex[in]	�����豸�洢��RSA��Կ������ֵ
			pucPublicKey[out]	RSA��Կ�ṹ
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ExportEncPublicKey_RSA(void *hSessionHandle, 
                                 unsigned int  uiKeyIndex,
                                 RSArefPublicKey *pucPublicKey);

/*���ⲿ����RSA��ECC��Կ��*/
/* 
������		���ⲿ����RSA��ECC��Կ��
������		hSessionHandle[in]	���豸�����ĻỰ���
			Mechanism[in]	�㷨��ʶ
			KeyId[in]	    ��Կ��ŵ�id��
			KeyType[in]		��Կ����
			pucRsaKey[in]	˽Կ�ṹ��ָ��
			pucEccPubKey[in]	˽Կ����
			pucEccPriKey[in]	��Կ�ṹ��ָ��
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ImportKeyPair_Ex(void             *hSessionHandle, 
						  unsigned  int    Mechanism,		   
						  unsigned  int    KeyId,
						  unsigned	int	   KeyType,
						  RSArefPrivateKey *pucRsaKey,
						  ECCrefPublicKey *pucEccPubKey,
						  ECCrefPrivateKey *pucEccPriKey);


/*���ⲿ����Գ���Կ�������豸*/
/* 
������		���ⲿ����Գ���Կ�������豸
������		hSessionHandle[in]	���豸�����ĻỰ���
			KeyId[in]	    ��Կ��ŵ�id��
			KeyType[in]		�Գ���Կ�÷�����
			pKey [in]		�Գ���Կָ��
			KeyLen [in]		�Գ���Կ����, ���ֽ���(8, 16, 24, 32)
			pTag [in]		�Գ���Կ��ǩ
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ImportKey_Ex(void             *hSessionHandle, 	   
						  unsigned  int    KeyId,
						  unsigned	int	   KeyType, //'P'=SM1 'R'=SM4 'Z'=8-DES 'X/U'=24-DES 'Y/T'=16-DES
						  unsigned  char   *pKey,
						  unsigned  int	   KeyLen,
						  char			  *pTag);

/*���ⲿ����Գ���Կ���ܵļ�����Կ���˶Գ���Կ��ǩ����Կ����*/
/* 
������		���ⲿ����RSA��ECC��Կ��
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiISKIndex[in]	    ��Կ��ŵ�id��
			uiALGID [in]		�㷨��ʶ
			cipher [in]			�����ܵĶԳ���Կ
			pubEncData [in]		���Գ���Կ���ܵļ�����Կ�ԣ�����Ϊ96�ֽ� x|y|d��Ϊ32�ֽ�
			uiEncDataLength [in] ���Գ���Կ���ܵļ�����Կ�Գ��ȣ�����Ϊ96
			uiPubKeyEncFlag [in] ָ���Ƿ�ԿҲ�������ˣ�1Ϊ���Ĺ�Կ; 0Ϊ���Ĺ�Կ
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI S_ImportEncKeyPair_ECC(void *hSessionHandle, 
	unsigned int uiISKIndex, 
	unsigned int uiALGID, 
	ECCCipher *cipher, 
	unsigned char *pubEncData,
	unsigned int uiEncDataLength,
	unsigned int uiPubKeyEncFlag);

/* 
������		ʹ���ڲ�ECC˽Կ����
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiISKIndex [in]	�����豸�ڲ��洢��ECCǩ��˽Կ������ֵ
			KeyType [in] ������ǩ��˽Կ���ܻ��Ǽ���˽Կ����
			pucEncData[in]	������ָ�룬���ڴ���������������
			pucData[out]	������ָ�룬���ڴ���������������
			puiDataLength[out]	������������ĳ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������

*/
DLL int WINAPI SDF_InternalDecryptEx_ECC(void *hSessionHandle,
						     unsigned int  uiISKIndex,
							 unsigned	int	   KeyType,
							 ECCCipher *pucEncData,
						     unsigned char *pucData,
						     unsigned int  *uiDataLength);

/* 
������		��ȡ�Գ���Կ��Ϣ
������	hSessionHandle[in]	  ���豸�����ĻỰ���
			uiISKIndex [in]	      �����豸�ڲ��洢�ĶԳ���Կ������ֵ
			uikeytype[out]	      ���ڴ���������Կ����
			puckeycv[out]	        ������ָ�룬���ڴ���������ԿУ��ֵ
			uikeycvlen[out]	      ���ڴ���������ԿУ��ֵ����
			pcTag[out]            �����Կ��ǩ(<32�ֽ�)
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������

*/
DLL int WINAPI SDF_GetSymmKeyInfo(void *hSessionHandle,
						   unsigned int  uiISKIndex,
						   unsigned int *uikeytype,
						   unsigned char *puckeycv,
						   unsigned int *uikeycvlen,
						   char			*pcTag);

/* 
������		���������豸����ָ�����ͺ�ģ����ECC��Կ��
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiAlgID[in]	ָ���㷨��ʶ
			uiKeyBits [in]	ָ����Կ����
			pucPublicKey[out]	ECC��Կ�ṹ
			pucPrivateKey[out]	ECC˽Կ�ṹ
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
 */
DLL int WINAPI SDF_GenerateKeyPair_ECC(void *hSessionHandle, 
								unsigned int  uiAlgID,
								unsigned int  uiKeyBits,
								ECCrefPublicKey *pucPublicKey,
								ECCrefPrivateKey *pucPrivateKey);


/* 
������		ʹ���ڲ�ECC˽Կ�����ݽ���ǩ������
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiISKIndex [in]	�����豸�ڲ��洢��ECCǩ��˽Կ������ֵ
			pucData[in]	������ָ�룬���ڴ���ⲿ���������
			uiDataLength[in]	��������ݳ���
			pucSignature [out]	������ָ�룬���ڴ�������ǩ��ֵ����
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		��ԭ�ĵ��Ӵ����㣬�ں����ⲿ��ɡ�
*/
DLL int WINAPI SDF_InternalSign_ECC(void *hSessionHandle,
						     unsigned int  uiISKIndex,
						     unsigned char *pucData,
						     unsigned int  uiDataLength,
						     ECCSignature *pucSignature);

/* 
������		ʹ���ⲿECC˽Կ�����ݽ���ǩ������
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiAlgID[in]	�㷨��ʶ��ָ��ʹ�õ�ECC�㷨
			pucPrivateKey[in]	�ⲿECC˽Կ�ṹ
			pucData[in]	������ָ�룬���ڴ���ⲿ���������
			uiDataLength[in]	��������ݳ���
			pucSignature[out]	������ָ�룬���ڴ�������ǩ��ֵ����
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
 */
DLL int WINAPI SDF_ExternalSign_ECC(void *hSessionHandle,
					    unsigned int uiAlgID,
						ECCrefPrivateKey *pucPrivateKey,
						unsigned char *pucData,
						unsigned int  uiDataLength,
						ECCSignature *pucSignature);

/* 
������		ʹ���ڲ�ECC��Կ��ECCǩ��ֵ������֤����
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiISKIndex [in]	�����豸�ڲ��洢��ECCǩ����Կ������ֵ
			pucData[in]	������ָ�룬���ڴ���ⲿ���������
			uiDataLength[in]	��������ݳ���
			pucSignature[in]	������ָ�룬���ڴ�������ǩ��ֵ����
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		��ԭ�ĵ��Ӵ����㣬�ں����ⲿ��ɡ�
*/
DLL int WINAPI SDF_InternalVerify_ECC(void *hSessionHandle,
							unsigned int  uiISKIndex,
							unsigned char *pucData,
							unsigned int  uiDataLength,
							ECCSignature *pucSignature);

/* 
������		ʹ���ⲿECC��Կ��ECCǩ��ֵ������֤����
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiAlgID[in]	�㷨��ʶ��ָ��ʹ�õ�ECC�㷨
			pucPublicKey[in]	�ⲿECC��Կ�ṹ
			pucData[in]	������ָ�룬���ڴ���ⲿ���������
			uiDataLength[in]	��������ݳ���
			pucSignature[in]	������ָ�룬���ڴ�������ǩ��ֵ����
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		��ԭ�ĵ��Ӵ����㣬�ں����ⲿ��ɡ�
*/
DLL int WINAPI SDF_ExternalVerify_ECC(	void *hSessionHandle,
							unsigned int uiAlgID,
							ECCrefPublicKey *pucPublicKey,
							unsigned char *pucDataInput,
							unsigned int  uiInputLength,
							ECCSignature *pucSignature);

/*
������		ʹ���ⲿECC��Կ�����ݽ��м�������
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiAlgID[in]	�㷨��ʶ��ָ��ʹ�õ�ECC�㷨
			pucPublicKey[in]	�ⲿECC��Կ�ṹ
			pucData[in]	������ָ�룬���ڴ���ⲿ���������
			uiDataLength[in]	��������ݳ���
			pucEncData[out]	������ָ�룬���ڴ���������������
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		��������ݳ���uiDataLength������ECCref_MAX_LEN��
*/
DLL int WINAPI SDF_ExternalEncrypt_ECC(void *hSessionHandle,
							unsigned int uiAlgID,
							ECCrefPublicKey *pucPublicKey,
							unsigned char *pucData,
							unsigned int  uiDataLength,
							ECCCipher *pucEncData);

/* 
������		ʹ���ⲿECC˽Կ���н�������
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiAlgID[in]	�㷨��ʶ��ָ��ʹ�õ�ECC�㷨
			pucPrivateKey[in]	�ⲿECC˽Կ�ṹ
			pucEncData[in]	������ָ�룬���ڴ���������������
			pucData[out]	������ָ�룬���ڴ���������������
			puiDataLength[out]	������������ĳ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ExternalDecrypt_ECC(void *hSessionHandle,
							unsigned int uiAlgID,
							ECCrefPrivateKey *pucPrivateKey,
							ECCCipher *pucEncData,
							unsigned char *pucData,
							unsigned int  *puiDataLength);


/*
������		���������豸����ָ��ģ����RSA��Կ��
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyBits [in]	ָ����Կģ��
			pucPublicKey[out]	RSA��Կ�ṹ
			pucPrivateKey[out]	RSA˽Կ�ṹ
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_GenerateKeyPair_RSA( void *hSessionHandle, 
                                 unsigned int  uiKeyBits,
                                 RSArefPublicKey *pucPublicKey,
                                 RSArefPrivateKey *pucPrivateKey);


/*
������		���ɻỰ��Կ����ָ���������ڲ����ܹ�Կ���������ͬʱ������Կ���
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiIPKIndex[in]	�����豸�ڲ��洢��Կ������ֵ
			uiKeyBits[in]	ָ�������ĻỰ��Կ����
			pucKey[out]	������ָ�룬���ڴ�ŷ��ص���Կ����
			puiKeyLength[out]	���ص���Կ���ĳ���
			phKeyHandle[out]	���ص���Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		��Կ��������ʱ��䷽ʽ����PKCS#1 v1.5��Ҫ����У����ص���Կ������IV���֡�
*/
DLL int WINAPI SDF_GenerateKeyWithIPK_RSA(void *hSessionHandle,
								   unsigned int uiIPKIndex, 
								   unsigned int uiKeyBits,
								   unsigned char *pucKey,						
								   unsigned int *puiKeyLength, 
								   void **phKeyHandle);

/*
������		���ɻỰ��Կ����ָ���������ڲ�ECC���ܹ�Կ���������ͬʱ������Կ���
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiIPKIndex[in]	�����豸�ڲ��洢��Կ������ֵ
			uiKeyBits[in]	ָ�������ĻỰ��Կ����
			pucKey[out]	������ָ�룬���ڴ�ŷ��ص���Կ����
			phKeyHandle[out]	���ص���Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		���ص���Կ������IV���֡�
*/
DLL int WINAPI SDF_GenerateKeyWithIPK_ECC(void *hSessionHandle, 
									unsigned int uiIPKIndex,
									unsigned int uiKeyBits,
									ECCCipher *pucKey,
									void **phKeyHandle);

/*
������		����Ự��Կ�����ڲ�ECC����˽Կ���ܣ�ͬʱ������Կ���
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiISKIndex[in]	�����豸�ڲ��洢����˽Կ������ֵ����Ӧ�ڼ���ʱ�Ĺ�Կ
			pucKey[in]	������ָ�룬���ڴ���������Կ����
			phKeyHandle[out]	���ص���Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ImportKeyWithISK_ECC(void *hSessionHandle,
						   	     unsigned int uiISKIndex,
							     ECCCipher *pucKey,
							     void **phKeyHandle);
/*
������		���ɻỰ��Կ�����ⲿECC��Կ���������ͬʱ������Կ���
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyBits[in]	ָ�������ĻỰ��Կ����
			uiAlgID[in]	�ⲿECC��Կ���㷨��ʶ
			pucPublicKey[in]	������ⲿECC��Կ�ṹ
			pucKey[out]	������ָ�룬���ڴ�ŷ��ص���Կ����
			phKeyHandle[out]	���ص���Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		���ص���Կ������IV���֡�
*/
DLL int WINAPI SDF_GenerateKeyWithEPK_ECC(void *hSessionHandle, 
								  unsigned int uiKeyBits,
								  unsigned int uiAlgID,
								  ECCrefPublicKey *pucPublicKey,
								  ECCCipher *pucKey,
								  void **phKeyHandle);
/*
������		���ɻỰ��Կ�����ⲿ��Կ���������ͬʱ������Կ���
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyBits[in]	ָ�������ĻỰ��Կ����
			pucPublicKey[in]	������ⲿRSA��Կ�ṹ
			pucKey[out]	������ָ�룬���ڴ�ŷ��ص���Կ����
			puiKeyLength[out]	���ص���Կ���ĳ���
			phKeyHandle[out]	���ص���Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		��Կ��������ʱ��䷽ʽ����PKCS#1 v1.5��Ҫ����У����ص���Կ������IV���֡�
*/
DLL int WINAPI SDF_GenerateKeyWithEPK_RSA(void *hSessionHandle, 
								   unsigned int uiKeyBits,
								   RSArefPublicKey *pucPublicKey,
                                   unsigned char *pucKey, 
                                   unsigned int *puiKeyLength, 
                                   void **phKeyHandle);

/*
������		���ɻỰ��Կ������Կ������Կ���������ͬʱ������Կ�����
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyBits[in]	ָ�������ĻỰ��Կ����
			uiAlgID[in]	�㷨��ʶ��ָ���ԳƼ����㷨
			uiKEKIndex[in]	�����豸�ڲ��洢��Կ������Կ������ֵ
			pucKey[out]	������ָ�룬���ڴ�ŷ��ص���Կ����
			puiKeyLength[out]	���ص���Կ���ĳ���
			phKeyHandle[out]	���ص���Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		����ģʽʹ��ECBģʽ��
*/
DLL int WINAPI SDF_GenerateKeyWithKEK(void *hSessionHandle, 
							   unsigned int uiKeyBits,
                               unsigned int  uiAlgID,
                               unsigned int uiKEKIndex, 
                               unsigned char *pucKey, 
                               unsigned int *puiKeyLength,
                               void **phKeyHandle);

/*
������		���ɻỰ��Կ���ûỰ��Կ���������ͬʱ������Կ�����
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyBits[in]	ָ�������ĻỰ��Կ����
			uiAlgID[in]	�㷨��ʶ��ָ���ԳƼ����㷨
			phSessKey[in]	�Ѿ����ڵ�һ���Ự��Կ���
			pucKey[out]	������ָ�룬���ڴ�ŷ��ص���Կ����
			puiKeyLength[out]	���ص���Կ���ĳ���
			phKeyHandle[out]	���ص���Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		����ģʽʹ��ECBģʽ��
*/
DLL int WINAPI SDF_GenerateKeyWithSK(void		*hSessionHandle, 
							   unsigned int		uiKeyBits,
                               unsigned int		uiAlgID,
                               void				*phSessKey, 
                               unsigned char	*pucKey, 
                               unsigned int		*puiKeyLength,
                               void				**phKeyHandle);

/*
������		����Ự��Կ�����ڲ�˽Կ���ܣ�ͬʱ������Կ���
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiISKIndex[in]	�����豸�ڲ��洢����˽Կ������ֵ����Ӧ�ڼ���ʱ�Ĺ�Կ
			pucKey[in]	������ָ�룬���ڴ���������Կ����
			puiKeyLength[in]	�������Կ���ĳ���
			phKeyHandle[out]	���ص���Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		��䷽ʽ�빫Կ����ʱ��ͬ��
*/
DLL int WINAPI SDF_ImportKeyWithISK_RSA(void *hSessionHandle, 
                                 unsigned int uiISKIndex, 
                                 unsigned char *pucKey, 
                                 unsigned int uiKeyLength, 
                                 void **phKeyHandle);

/*
������		����Ự��Կ������Կ������Կ���ܣ�ͬʱ���ػỰ��Կ�����
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiAlgID[in]	�㷨��ʶ��ָ���ԳƼ����㷨
			uiKEKIndex[in]	�����豸�ڲ��洢��Կ������Կ������ֵ
			pucKey[in]	������ָ�룬���ڴ���������Կ����
			puiKeyLength[in]	�������Կ���ĳ���
			phKeyHandle[out]	���ص���Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		����ģʽʹ��ECBģʽ��
*/
DLL int WINAPI SDF_ImportKeyWithKEK(void *hSessionHandle, 
                             unsigned int  uiAlgID,
                             unsigned int uiKEKIndex, 
                             unsigned char *pucKey, 
                             unsigned int uiKeyLength, 
                             void **phKeyHandle);

/*
������		����Ự��Կ���ûỰ��Կ���ܣ�ͬʱ���ػỰ��Կ�����
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiAlgID[in]	�㷨��ʶ��ָ���ԳƼ����㷨
			phSessKey[in]	�Ѿ����ڵ�һ���Ự��Կ���
			pucKey[in]	������ָ�룬���ڴ���������Կ����
			puiKeyLength[in]	�������Կ���ĳ���
			phKeyHandle[out]	���ص���Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		����ģʽʹ��ECBģʽ��
*/
DLL int WINAPI SDF_ImportKeyWithSK(void			*hSessionHandle, 
                             unsigned int		uiAlgID,
                             void				*phSessKey, 
                             unsigned char		*pucKey, 
                             unsigned int		uiKeyLength, 
                             void				**phKeyHandle);

/*
������		�������ĻỰ��Կ��ͬʱ������Կ���
������		hSessionHandle[in]	���豸�����ĻỰ���
			pucKey[in]	������ָ�룬���ڴ���������Կ����
			puiKeyLength[in]	�������Կ���ĳ���
			phKeyHandle[out]	���ص���Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ImportKey(void *hSessionHandle, 
                      unsigned char *pucKey, 
                      unsigned int uiKeyLength, 
                      void **phKeyHandle);

/*
������		���ٻỰ��Կ�����ͷ�Ϊ��Կ���������ڴ����Դ��
������		hSessionHandle[in]	���豸�����ĻỰ���
			hKeyHandle[in]	�������Կ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		�ڶԳ��㷨������ɺ�Ӧ���ñ��������ٻỰ��Կ��
*/
DLL int WINAPI SDF_DestoryKey(void *hSessionHandle, 
					   void *hKeyHandle);

/*
������		ָ��ʹ���ⲿ��Կ�����ݽ�������
������		hSessionHandle[in]	���豸�����ĻỰ���
			pucPublicKey [in]	�ⲿRSA��Կ�ṹ
			pucDataInput [in]	������ָ�룬���ڴ�����������
			uiInputLength[in]	��������ݳ���
			pucDataOutput[out]	������ָ�룬���ڴ�����������
			puiOutputLength[out]	��������ݳ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		���ݸ�ʽ��Ӧ�ò��װ
*/
DLL int WINAPI SDF_ExternalPublicKeyOperation_RSA(void *hSessionHandle, 
										   RSArefPublicKey *pucPublicKey,
										   unsigned char *pucDataInput,
										   unsigned int  uiInputLength,
										   unsigned char *pucDataOutput,
										   unsigned int  *puiOutputLength);


/*
������		ָ��ʹ���ⲿ˽Կ�����ݽ�������
������		hSessionHandle[in]	���豸�����ĻỰ���
			pucPrivateKey [in]	�ⲿRSA˽Կ�ṹ
			pucDataInput [in]	������ָ�룬���ڴ�����������
			uiInputLength [in]	��������ݳ���
			pucDataOutput [out]	������ָ�룬���ڴ�����������
			puiOutputLength [out]	��������ݳ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		���ݸ�ʽ��Ӧ�ò��װ
*/
DLL int WINAPI SDF_ExternalPrivateKeyOperation_RSA( void *hSessionHandle, 
											 RSArefPrivateKey *pucPirvateKey,
											 unsigned char *pucDataInput,
											 unsigned int  uiInputLength,
											 unsigned char *pucDataOutput,
											 unsigned int  *puiOutputLength);


/*
������		ʹ���ڲ�ָ�������Ĺ�Կ�����ݽ�������
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyIndex[in]	�����豸�ڲ��洢��Կ������ֵ
			pucDataInput[in]	������ָ�룬���ڴ���ⲿ���������
			uiInputLength[in]	��������ݳ���
			pucDataOutput[out]	������ָ�룬���ڴ�����������
			puiOutputLength[out]	��������ݳ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		������Χ�������ڲ�ǩ����Կ�ԣ����ݸ�ʽ��Ӧ�ò��װ
*/
DLL int WINAPI SDF_InternalPublicKeyOperation_RSA(void *hSessionHandle,
										   unsigned int  uiKeyIndex,
										   unsigned char *pucDataInput,
										   unsigned int  uiInputLength,
										   unsigned char *pucDataOutput,
										   unsigned int  *puiOutputLength);


/*
������		ʹ���ڲ�ָ��������˽Կ�����ݽ�������
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyIndex[in]	�����豸�ڲ��洢˽Կ������ֵ
			pucDataInput[in]	������ָ�룬���ڴ���ⲿ���������
			uiInputLength[in]	��������ݳ���
			pucDataOutput[out]	������ָ�룬���ڴ�����������
			puiOutputLength[out]	��������ݳ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		������Χ�������ڲ�ǩ����Կ�ԣ����ݸ�ʽ��Ӧ�ò��װ
*/
DLL int WINAPI SDF_InternalPrivateKeyOperation_RSA( void *hSessionHandle,
											 unsigned int  uiKeyIndex,
											 unsigned char *pucDataInput,
											 unsigned int  uiInputLength,
											 unsigned char *pucDataOutput,
											 unsigned int  *puiOutputLength);


/* 
������		�����ڲ����ܹ�Կ���ܵĻỰ��Կת��Ϊ���ⲿָ���Ĺ�Կ���ܣ������������ŷ�ת����
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyIndex[in]	�����豸�洢���ڲ�RSA��Կ������ֵ
			pucPublicKey [in]	�ⲿRSA��Կ�ṹ
			pucDEInput [in]	������ָ�룬���ڴ������ĻỰ��Կ����
			uiDELength[in]	����ĻỰ��Կ���ĳ���
			pucDEOutput[out]	������ָ�룬���ڴ������ĻỰ��Կ����
			puiDELength[out]	����ĻỰ��Կ���ĳ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
 */
DLL int WINAPI SDF_ExchangeDigitEnvelopeBaseOnRSA(void *hSessionHandle, 
										   unsigned int  uiKeyIndex,
										   RSArefPublicKey *pucPublicKey,
										   unsigned char *pucDEInput,
										   unsigned int  uiDELength,
										   unsigned char *pucDEOutput,
										   unsigned int  *puiDELength);


/*
������		�����ڲ����ܹ�Կ���ܵĻỰ��Կת��Ϊ���ⲿָ���Ĺ�Կ���ܣ������������ŷ�ת����
������		hSessionHandle[in]	���豸�����ĻỰ���
			uiKeyIndex[in]	�����豸�洢��ECC��Կ������ֵ
			uiAlgID[in]	�ⲿECC��Կ���㷨��ʶ
			pucPublicKey [in]	�ⲿECC��Կ�ṹ
			pucEncDataIn[in]	������ָ�룬���ڴ������ĻỰ��Կ����
			pucEncDataOut[out]	������ָ�룬���ڴ������ĻỰ��Կ����
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
 */
DLL int WINAPI SDF_ExchangeDigitEnvelopeBaseOnECC(void *hSessionHandle, 
										   unsigned int  uiKeyIndex,
										   unsigned int  uiAlgID,
										   ECCrefPublicKey *pucPublicKey,
										   ECCCipher *pucEncDataIn,
										   ECCCipher *pucEncDataOut);


/*
������		ʹ��ָ������Կ�����IV�����ݽ��жԳƼ�������
������		hSessionHandle[in]	���豸�����ĻỰ���
			hKeyHandle[in]	ָ������Կ���
			uiAlgID[in]	�㷨��ʶ��ָ���ԳƼ����㷨
			pucIV[in|out]	������ָ�룬���ڴ������ͷ��ص�IV����
			pucData[in]	������ָ�룬���ڴ���������������
			uiDataLength[in]	������������ĳ���
			pucEncData[out]	������ָ�룬���ڴ���������������
			puiEncDataLength[out]	������������ĳ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		�˺����������ݽ�����䴦����������ݱ�����ָ���㷨���鳤�ȵ���������
*/
DLL int WINAPI SDF_Encrypt(void *hSessionHandle,
                    void *hKeyHandle,
                    unsigned int uiAlgID,
                    unsigned char *pucIV,
                    unsigned char *pucData,
                    unsigned int uiDataLength,
                    unsigned char *pucEncData,
                    unsigned int  *puiEncDataLength);


/*
����:		ʹ��ָ������Կ�����IV�����ݽ��жԳƽ�������
����:		hSessionHandle[in]	���豸�����ĻỰ���
			hKeyHandle[in]	ָ������Կ���
			uiAlgID[in]	�㷨��ʶ��ָ���ԳƼ����㷨
			pucIV[in|out]	������ָ�룬���ڴ������ͷ��ص�IV����
			pucEncData[in]	������ָ�룬���ڴ���������������
			uiEncDataLength[in]	������������ĳ���
			pucData[out]	������ָ�룬���ڴ���������������
			puiDataLength[out]	������������ĳ���
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
��ע��		�˺����������ݽ�����䴦����������ݱ�����ָ���㷨���鳤�ȵ���������
*/
DLL int WINAPI SDF_Decrypt (void *hSessionHandle,
                     void *hKeyHandle,
                     unsigned int uiAlgID,
                     unsigned char *pucIV,
                     unsigned char *pucEncData,
                     unsigned int uiEncDataLength,
                     unsigned char *pucData,
                     unsigned int  *puiDataLength);

/*	
������			ʹ��ָ������Կ�����IV�����ݽ���MAC����
������			hSessionHandle[in]	���豸�����ĻỰ���
				hKeyHandle[in]	ָ������Կ���
				uiAlgID[in]	�㷨��ʶ��ָ��MAC�����㷨
				pucIV[in|out]	������ָ�룬���ڴ������ͷ��ص�IV����
				pucData[in]	������ָ�룬���ڴ���������������
				uiDataLength[in]	������������ĳ���
				pucMAC[out]	������ָ�룬���ڴ�������MACֵ
				puiMACLength[out]	�����MACֵ����
����ֵ��		0	�ɹ�
				��0	ʧ�ܣ����ش������
��ע��			�˺����������ݽ��зְ������������MAC������IV��������MACֵ��
*/
DLL int WINAPI SDF_CalculateMAC(void *hSessionHandle,
                         void *hKeyHandle,
                         unsigned int uiAlgID,
                         unsigned char *pucIV,
                         unsigned char *pucData,
                         unsigned int uiDataLength,
                         unsigned char *pucMAC,
                         unsigned int  *puiMACLength);

/*
������			����ʽ�����Ӵ������һ����
������			hSessionHandle[in]	���豸�����ĻỰ���
				uiAlgID[in]	ָ���Ӵ��㷨��ʶ
				pucPublicKey[in]	ǩ���ߵ�ECC��Կ����������ECCǩ�����Ӵ�ֵʱ��Ч
				pucID[in]	ǩ���ߵ�IDֵ����������ECCǩ�����Ӵ�ֵʱ��Ч
				uiIDLength[in]	ǩ���ߵ�ID����
����ֵ��		0	�ɹ�
				��0	ʧ�ܣ����ش������
��ע��			����ھ����Ӧ���У�Э��˫��û��ͳһ�����ID�����Խ�ID�趨Ϊ������
*/
DLL int WINAPI SDF_HashInit(void *hSessionHandle,
					 unsigned int uiAlgID,
					 ECCrefPublicKey *pucPublicKey,//��uiAlgIDΪ��ID��SCH�㷨����ʱ�ò�������Ч
					 unsigned char *pucID,//��uiAlgIDΪ��ID��SCH�㷨����ʱ�ò�������Ч
				     unsigned int uiIDLength);//��uiAlgIDΪ��ID��SCH�㷨����ʱ�ò�������Ч

/*
������			����ʽ�����Ӵ�����ڶ���������������Ľ����Ӵ�����
������			hSessionHandle[in]	���豸�����ĻỰ���
				pucData[in]	������ָ�룬���ڴ���������������
				uiDataLength[in]	������������ĳ���
����ֵ��		0	�ɹ�
				��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_HashUpdate(void *hSessionHandle,
                       unsigned char *pucData,
                       unsigned int  uiDataLength);

/*
������			����ʽ�����Ӵ�������������Ӵ�������������Ӵ����ݲ�����м�����
������			hSessionHandle[in]	���豸�����ĻỰ���
				pucHash[out]	������ָ�룬���ڴ��������Ӵ�����
				puiHashLength[out]	���ص��Ӵ����ݳ���
����ֵ��		0	�ɹ�
				��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_HashFinal(void *hSessionHandle,
                      unsigned char *pucHash,
                      unsigned int  *puiHashLength);

/*
������			����ʽZUC�����һ����
������			hSessionHandle[in]	���豸�����ĻỰ���
				uiAlgID[in]	ָ���Ӵ��㷨��ʶ
����ֵ��		0	�ɹ�
				��0	ʧ�ܣ����ش������
��ע��			����ھ����Ӧ���У�Э��˫��û��ͳһ�����ID�����Խ�ID�趨Ϊ������
*/
DLL int WINAPI SDF_ZucInit(void *hSessionHandle,
					 unsigned int uiAlgID,
					 void *hKeyHandle,
					 unsigned char *pucIV,
                       unsigned char *pucData,
                       unsigned int  uiDataLength,
					   unsigned char *pucOut);

/*
������			����ʽZUC����ڶ���������������Ľ����Ӵ�����
������			hSessionHandle[in]	���豸�����ĻỰ���
				pucData[in]	������ָ�룬���ڴ���������������
				uiDataLength[in]	������������ĳ���
����ֵ��		0	�ɹ�
				��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ZucUpdate(void *hSessionHandle,
                       unsigned char *pucData,
                       unsigned int  uiDataLength,
					   unsigned char *pucOut);

/*
������			����ʽZUC������������Ӵ�������������Ӵ����ݲ�����м�����
������			hSessionHandle[in]	���豸�����ĻỰ���
				pucHash[out]	������ָ�룬���ڴ��������Ӵ�����
				puiHashLength[out]	���ص��Ӵ����ݳ���
����ֵ��		0	�ɹ�
				��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ZucFinal(void *hSessionHandle);

/*
������			�������豸�ڲ��������ڴ洢�û����ݵ��ļ�
������			hSessionHandle[in]	���豸�����ĻỰ���
				pucFileName[in]	������ָ�룬���ڴ��������ļ�������󳤶�128�ֽ�
				uiNameLen[in]	�ļ�������
				uiFileSize[in]	�ļ���ռ�洢�ռ�ĳ���
����ֵ��		0	�ɹ�
				��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_CreateFile( void *hSessionHandle,
                        unsigned char *pucFileName,
						unsigned int uiNameLen,
                        unsigned int uiFileSize);

/*
������		��ȡ�������豸�ڲ��洢�û����ݵ��ļ�������
������		hSessionHandle[in]	���豸�����ĻỰ���
			pucFileName[in]	������ָ�룬���ڴ��������ļ�������󳤶�128�ֽ�
			uiNameLen[in]	�ļ�������
			uiOffset[in]	ָ����ȡ�ļ�ʱ��ƫ��ֵ
			puiFileLength[in|out]	���ʱָ����ȡ�ļ����ݵĳ��ȣ�����ʱ����ʵ�ʶ�ȡ�ļ����ݵĳ���
			pucBuffer[out]	������ָ�룬���ڴ�Ŷ�ȡ���ļ�����
����ֵ��	0	�ɹ�
			��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ReadFile(void *hSessionHandle,
                     unsigned char *pucFileName,
					 unsigned int uiNameLen,
                     unsigned int uiOffset,
                     unsigned int  *puiFileLength,
                     unsigned char *pucBuffer);


/*
������			�������豸�ڲ��洢�û����ݵ��ļ���д������
������			hSessionHandle[in]	���豸�����ĻỰ���
				pucFileName[in]	������ָ�룬���ڴ��������ļ�������󳤶�128�ֽ�
				uiNameLen[in]	�ļ�������
				uiOffset[in]	ָ��д���ļ�ʱ��ƫ��ֵ
				uiFileLength[in]	ָ��д���ļ����ݵĳ���
				pucBuffer[in]	������ָ�룬���ڴ�������д�ļ�����
����ֵ��		0	�ɹ�
				��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_WriteFile(void *hSessionHandle,
                     unsigned char *pucFileName,
					 unsigned int uiNameLen,
                     unsigned int uiOffset,
                     unsigned int  uiFileLength,
                     unsigned char *pucBuffer);


/* ɾ���ļ� */
DLL int WINAPI SDF_DeleteFile(void *hSessionHandle, unsigned char *pucFileName,unsigned int uiNameLen);


/* ������ԿЭ�̲�������� */
int DLL WINAPI SDF_GenerateAgreementDataWithECC (void *hSessionHandle,
				unsigned int uiISKIndex,
				unsigned int uiKeyBits,
				unsigned char *pucSponsorID,
				unsigned int uiSponsorIDLength,
				ECCrefPublicKey  *pucSponsorPublicKey,
				ECCrefPublicKey  *pucSponsorTmpPublicKey,
				void **phAgreementHandle);



/* ����Ự��Կ */
int DLL WINAPI SDF_GenerateKeyWithECC (void *hSessionHandle, 
				unsigned char *pucResponseID,
				unsigned int uiResponseIDLength,
				ECCrefPublicKey *pucResponsePublicKey,
				ECCrefPublicKey *pucResponseTmpPublicKey,
				void *phAgreementHandle,
				void **phKeyHandle);


/* ����Э�̲���������Ự��Կ */
int DLL WINAPI SDF_GenerateAgreementDataAndKeyWithECC (void *hSessionHandle, 
				unsigned int uiISKIndex,
				unsigned int uiKeyBits,
				unsigned char *pucResponseID,
				unsigned int uiResponseIDLength,
				unsigned char *pucSponsorID,
				unsigned int uiSponsorIDLength,
				ECCrefPublicKey *pucSponsorPublicKey,
				ECCrefPublicKey *pucSponsorTmpPublicKey,
				ECCrefPublicKey  *pucResponsePublicKey,
				ECCrefPublicKey  *pucResponseTmpPublicKey,
				void **phKeyHandle);

/*
������		�����豸�ڴ������ŵ�����֤��
������		hSessionHandle[in]	���豸�����ĻỰ���
uiKeyIndex[in]	�����豸�洢��֤������ֵ
uiKeyType[in]	�����豸�洢��֤������ֵ 1-RSA 2-SM2
uiCertType[in]  ֤�����ͣ�0-��֤�� 1-ǩ��֤�� 2-����֤��
CertBuf [out]	֤��洢����С�������㹻�ڣ�
CertLen[out]	����֤�鳤��
����ֵ��	0	�ɹ� ��0	ʧ�ܣ����ش������
*/
DLL int WINAPI SDF_ExportCert_Ex(void *hSessionHandle,
				unsigned int  uiKeyIndex,
				unsigned int  uiKeyType,
				unsigned int  uiCertType,
				unsigned char *pucCertBuf,
				unsigned int  *puiCertLen);

#ifdef __cplusplus
}
#endif

#define SDR_OK								0x0	//�����ɹ�
#define SDR_BASE							0x01000000	//���������ֵ
#define SDR_UNKNOWERR						SDR_BASE + 0x00000001	//δ֪����
#define SDR_CONFIGFILE						SDR_BASE + 0x00000002	//�����ļ��Ҳ��������(δ���ã���һ�汾����)
#define SDR_RESULT_FORMAT					SDR_BASE + 0x00000003   //�������ݸ�ʽ����
#define SDR_RESULT_STATUS					SDR_BASE + 0x00000004   //��������״̬�ִ���
#define SDR_OPENDEVICE						SDR_BASE + 0x00000005	//���豸ʧ��(����������)
#define SDR_OPENSESSION						SDR_BASE + 0x00000006	//�����Ựʧ��(��������������ܾ�����)
#define SDR_KEYNOTEXIST						SDR_BASE + 0x00000007	//�����ڵ���Կ����
#define SDR_ALGNOTSUPPORT					SDR_BASE + 0x00000008	//��֧�ֵ��㷨����
#define SDR_ALGMODNOTSUPPORT				SDR_BASE + 0x00000009	//��֧�ֵ��㷨ģʽ����
#define SDR_RESULT_CHECK					SDR_BASE + 0x0000000A   //��������У��ʧ��
#define SDR_SM2_ENCDATAERR					SDR_BASE + 0x0000000E	//SM2�������ݴ���
#define SDR_FILESIZEERR						SDR_BASE + 0x00000017	//�ļ����ȳ�������
#define SDR_FILENOEXIST						SDR_BASE + 0x00000018	//ָ�����ļ�������
#define SDR_FILEOFSERR						SDR_BASE + 0x00000019	//�ļ���ʼλ�ô���
#define SDR_KEYTYPEERR						SDR_BASE + 0x0000001E	//��Կ���ʹ���
#define SDR_KEYERR							SDR_BASE + 0x0000001F	//��Կ����

#define SDR_HANDLE_CLOSED					SDR_BASE + 0x00000020   //����ִ�й����У��ûỰ�Ѿ��رա�
#define SDR_HANDLE_COUNT					SDR_BASE + 0x00000021   //�򿪵ĻỰ̫�ࡣ
#define SDR_HANDLE_INVALID           		SDR_BASE + 0x00000022   //ָ���ĻỰ�����Ч��
#define SDR_NOT_LOGIN       	    		SDR_BASE + 0x00000025   //˽Կʹ��Ȩ��δ��ȡ��
#define SDR_INPUT_LEN_ERROR           		SDR_BASE + 0x00000026   //����������ȴ���
#define SDR_KEYID_INVALID           		SDR_BASE + 0x00000027   //���壺ָ������Կ�ŷǷ���
#define SDR_MECHANISM_INVALID				SDR_BASE + 0x00000028   //���壺������Ч��
#define SDR_NOT_INITIALIZED         		SDR_BASE + 0x00000029   //���壺δ���ó�ʼ����
#define SDR_ALREADY_INITIALIZED      		SDR_BASE + 0x0000002A   //���壺��ʼ���ѵ��á�
#define SDR_DEVICEHANDLE_INVALID			SDR_BASE + 0x0000002B   //�豸�����Ч
#define SDR_OUTPUT_LEN_ERROR				SDR_BASE + 0x0000002C   //������Ȳ���ȷ
#define SDR_OUTPUT_BUFFER_IVVALID			SDR_BASE + 0x0000002D	//����洢����Ч

#define SDR_KEY_MEM_FULL					SDR_BASE + 0x0000002E
#define SDR_SESSION_INIT					SDR_BASE + 0x00000031   // �����Ựʧ��
#define SDR_KEYPAIR_LENGTH					SDR_BASE + 0x00000032   // �ǶԳ���Կ��ָ������
#define SDR_PADDING_RSA						SDR_BASE + 0x00000033   // RSA padding ����
#define SDR_UNPADDING_RSA					SDR_BASE + 0x00000034   // RSA unpadding ����
#define SDR_HANDLE_SYMKEY_INVALID			SDR_BASE + 0x00000035   // �Ự��Կ�����Ч

#define SDR_PARAMETER_ERR					SDR_BASE + 0x00000037	//�ӿڲ����������ʶ��

#define ERROR_COMMAND_FORMAT				0xF0000001 //���Ĳ��ܱ�����(������)
#define ERROR_DEVICE_OPEN					0xF0000002 //��USB�豸ʧ��(���������߻����)
#define ERROR_USB_WRITE						0xF0000003 //USB�豸дʧ��
#define ERROR_USB_READ						0xF0000004 //USB�豸��ʧ��
#define ERROR_USB_READ_TIMEOUT				0xF0000040 //USB����ʱ
#define ERROR_LINK_MAX						0xF0000005 //�ͻ�������������������
#define ERROR_USB_MALFUNCTION				0xF0000006 //USB�豸����

#define PCIAPIERR_SOCK_CONNECT				0xF0000007 //Socket���ӷ������
#define PCIAPIERR_SOCK_SELECT_INSEND		0xF0000008 //socket select���ô���,�ڷ���ʱ
#define PCIAPIERR_SOCK_SELECT_INRECV		0xF0000009 //socket select���ô���,�ڽ���ʱ
#define PCIAPIERR_SOCK_SEND					0xF000000A //socket send����
#define PCIAPIERR_SOCK_RECV					0xF000000B //socket recv����
#define PCIAPIERR_SOCK_INVALID				0xF000000C //socket��Ч
#define PCIAPIERR_SOCK_CLOSE				0xF000000D //socket���Է��ر�
#define PCIAPIERR_SOCK_TIMEOUT_SEND			0xF000000E //socket���ͳ�ʱ
#define PCIAPIERR_SOCK_TIMEOUT_RECV			0xF000000F //���ճ�ʱ

#endif

