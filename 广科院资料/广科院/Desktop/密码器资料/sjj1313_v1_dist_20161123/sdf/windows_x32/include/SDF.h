/*----------------------------------------------------------------------|
|	SDF.h - Header file 												|
|	Version :	2.0														|												|
|	Copyright : 北京江南天安科技有限公司.	|
|----------------------------------------------------------------------*/

#ifndef _SDF_H
#define _SDF_H

#define MAX_SESSIONS 2560   /*最大打开会话数*/
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
名称： 设备信息结构体
成员：
		名称		数据长度（字节）	含义
	IssuerName			40				设备生产厂商名称
	DeviceName			16				设备型号
	DeviceSerial		16				设备编号，包含：日期（8字符）、批次号（3字符）、流水号（5字符）
	DeviceVersion		4				密码设备内部软件的版本号
	StandardVersion		4				密码设备支持的接口规范版本号
	AsymAlgAbility		8				前4字节表示支持的算法,表示方法为非对称算法标识按位或的结果；后4字节表示算法的最大模长，表示方法为支持的模长按位或的结果
	SymAlgAbility		4				所有支持的对称算法，表示方法为对称算法标识按位或运算结果
	HashAlgAbility		4				所有支持的杂凑算法，表示方法为杂凑算法标识按位或运算结果
	BufferSize			4				支持的最大文件存储空间（单位字节）
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
名称： RSA公钥结构体
成员：
	名称			数据长度（字节）	含义
	bits				4				模长
	M				RSAref_MAX_LEN		模N
	E				RSAref_MAX_LEN		指数
*/
typedef struct RSArefPublicKey_st
{
	unsigned int  bits;
	unsigned char m[RSAref_MAX_LEN];
	unsigned char e[RSAref_MAX_LEN];
} RSArefPublicKey;


/*
名称： RSA私钥结构体
成员：
	名称			数据长度（字节）			含义
	bits				4						模长
	M				RSAref_MAX_LEN				模N
	E				RSAref_MAX_LEN				指数
	D				RSAref_MAX_LEN				模D
	prime[2]		RSAref_MAX_PLEN * 2			素数p和q
	pexp[2]			RSAref_MAX_PLEN * 2			Dp 和Dq
	coef			RSAref_MAX_PLEN				系数i
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
名称： ECC公钥结构体
成员：
	名称			数据长度（字节）	含义
	bits				4				模长
	x					ECCref_MAX_LEN	公钥x坐标
	y					ECCref_MAX_LEN	公钥y坐标
*/
typedef struct ECCrefPublicKey_st
{
	unsigned int  bits;
	unsigned char x[ECCref_MAX_LEN]; 
	unsigned char y[ECCref_MAX_LEN]; 
}ECCrefPublicKey;

/*
名称： ECC私钥结构体
成员：
	名称			数据长度（字节）	含义
	bits				4				模长
	D				ECCref_MAX_LEN		私钥
*/
typedef struct ECCrefPrivateKey_st
{
    unsigned int  bits;
    unsigned char D[ECCref_MAX_LEN];
} ECCrefPrivateKey;

/*
名称： ECC加密数据结构体
成员：
	名称			数据长度（字节）	含义
	x				ECCref_MAX_LEN		与y组成椭圆曲线上的点（x，y）
	y				ECCref_MAX_LEN		与x组成椭圆曲线上的点（x，y）
	M				ECCref_MAX_LEN		明文的SM3杂凑值
	L				4					密文数据长度
	C				136				密文数据,最长支持136字节
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
名称： ECC签名数据结构体
成员：
	名称			数据长度（字节）	含义
	r				ECCref_MAX_LEN		签名的r部分
	s				ECCref_MAX_LEN		签名的s部分
*/
typedef struct ECCSignature_st
{
	unsigned char r[ECCref_MAX_LEN];	
	unsigned char s[ECCref_MAX_LEN];	
} ECCSignature;


/* ECC曲线类型 */
//NIST标准
#define NIST_FP_160           1

//NIST标准
#define NIST_FP_192           2
#define NIST_FP_224           3
#define NIST_FP_256           4

//国密局标准
#define OSCCA_FP_192          5
#define OSCCA_FP_256          6
#define OSCCA_NEWFP_256       7

#define PARAID       OSCCA_NEWFP_256

/*非对称算法机制：*/
#define SGD_RSA                  0x00010000 /* RSA算法机制 */
/*外加机制*/
#define SGD_RSA_SIGN_EX			 0x00010001  //导入或导出RSA签名或验证密钥时使用
#define SGD_RSA_ENC_EX			 0x00010002  //导入或导出RSA加密或解密密钥时使用

#define SGD_SM2				     0x00020100  /* sm2算法 */
#define SGD_SM2_1	             0x00020200  //椭圆曲线签名算法
#define SGD_SM2_2	             0x00020400  //椭圆曲线密钥交换协议
#define SGD_SM2_3	             0x00020800  //椭圆曲线加密算法

/*对称算法机制：*/
#define SGD_SM1_ECB             0x00000101 /* SCB2 ECB加密机制 */
#define SGD_SM1_CBC             0x00000102 /* SCB2 CBC加密机制 */
#define SGD_SM1_CFB             0x00000104 /* SCB2 CFB加密机制 */
#define SGD_SM1_OFB             0x00000108 /* SCB2 OFB加密机制 */
#define SGD_SM1_MAC             0x00000110 /* SCB2 MAC加密机制 */
#define SGD_SM1_OFB_OX          0x00000112 /* SCB2 OFB加密机制 扩展异或*/

#define SGD_SSF33_ECB           0x00000201 /* SSF33 ECB加密机制 */
#define SGD_SSF33_CBC           0x00000202 /* SSF33 CBC加密机制 */
#define SGD_SSF33_CFB           0x00000204 /* SSF33 CFB加密机制 */
#define SGD_SSF33_OFB           0x00000208 /* SSF33 OFB加密机制 */
#define SGD_SSF33_MAC           0x00000210 /* SSF33 MAC加密机制 */

#define SGD_SM4_ECB             0x00000401 /* SM4 ECB加密机制 */
#define SGD_SM4_CBC             0x00000402 /* SM4 CBC加密机制 */
#define SGD_SM4_CFB             0x00000404 /* SM4 CFB加密机制 */
#define SGD_SM4_OFB             0x00000408 /* SM4 OFB加密机制 */
#define SGD_SM4_MAC             0x00000410 /* SM4 MAC加密机制 */

#define SGD_DES_ECB             0x00000501 /* DES ECB加密机制 */
#define SGD_DES_CBC             0x00000502 /* DES CBC加密机制 */
#define SGD_3DES_ECB            0x00000504 /* 3DES ECB加密机制 */
#define SGD_3DES_CBC            0x00000508 /* 3DES CBC加密机制 */

#define SGD_SM7_ECB				0x00000601 /* SM7 ECB加密机制 */
#define SGD_SM7_OFB				0x00000608 /* SM4 OFB加密机制 */

/*HASH算法机制 */
#define SGD_SM3                 0x00000001  /*SM3算法机制 */
#define SGD_SHA1                0x00000002 /* SHA-1算法机制 */
#define SGD_SHA256	            0x00000004	/*SHA256杂凑算法 */

/*ZUC算法机制 */
#define SGD_ZUC_STREAM            0x00000011  /*ZUC产生密钥流 */
#define SGD_ZUC_EEA             0x00000012 /* ZUC EEA加解密 */
#define SGD_ZUC_EIA	            0x00000014	/*ZUC EIA MAC   */

//内部会话句柄
#define NULLKEYID 0xFFFFFFFF

typedef struct Handle_struct{
	unsigned int uiHandlemark;
	unsigned int uiHandlecode;
	unsigned int uiKeynumber; //获取的私钥权限个数
	unsigned int uiKeyindex[32];//获取的私钥权限索引
	//unsigned int uiHashalg;//hash 算法标识
	unsigned int uiContextlen;
	unsigned char ucHashContext[512];//计算hash所需要的上下文
}Handlestruct;                /* 句柄结构 */

//内部设备结构体
typedef struct Device_struct{
	unsigned int uiDevicemark;
	unsigned int uiDevicecode;
}Devicestruct;


//密钥协商的自身数据
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
描述：		打开密码设备
参数：		phDeviceHandle[out]	返回设备句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		phDeviceHandle由函数初始化并填写内容
 */
DLL int WINAPI SDF_OpenDevice(void **phDeviceHandle);


/* 
描述：		关闭密码设备，并释放相关资源
参数：		hDeviceHandle[in]	已打开的设备句柄
返回值：	0	成功
			非0	失败，返回错误代码
 */
DLL int WINAPI SDF_CloseDevice(void *hDeviceHandle);


/*
描述：		创建与密码设备的会话
参数：		hDeviceHandle[in]	已打开的设备句柄
			phSessionHandle[out]	返回与密码设备建立的新会话句柄
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_OpenSession(void *hDeviceHandle, void **phSessionHandle);

/* 
描述：		关闭与密码设备已建立的会话，并释放相关资源
参数：		hSessionHandle [in]	与密码设备已建立的会话句柄
返回值：	0	成功
			非0	失败，返回错误代码
 */
DLL int WINAPI SDF_CloseSession(void *hSessionHandle);

/* 
描述：	获取密码设备能力描述
参数：	hSessionHandle[in]	与设备建立的会话句柄
		pstDeviceInfo [out]	设备能力描述信息，内容及格式见设备信息定义
返回值：	0	成功
	非0	失败，返回错误代码
 */
DLL int WINAPI SDF_GetDeviceInfo(void *hSessionHandle,DEVICEINFO *pstDeviceInfo);

/* 
描述：		获取指定长度的随机数
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiLength[in]	欲获取的随机数长度
			pucRandom[out]	缓冲区指针，用于存放获取的随机数
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_GenerateRandom(void *hSessionHandle, 
					       unsigned int  uiLength,
					       unsigned char *pucRandom);

/* 
描述：		获取密码设备内部存储的指定索引私钥的使用权
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	密码设备存储私钥的索引值
			pucPassword[in]	使用私钥权限的标识码
			uiPwdLength[in]	私钥权限标识码长度，不少于8字节
返回值：	0	成功
			非0	失败，返回错误代码
备注：		本规范涉及密码设备存储的密钥对索引值的的起始索引值为1，最大为n，密码设备的实际存储容量决定n值， 
 */
DLL int WINAPI SDF_GetPrivateKeyAccessRight(void *hSessionHandle, 
                                     unsigned int  uiKeyIndex,
                                     unsigned char *pucPassword,
                                     unsigned int  uiPwdLength);

/*
描述：		获取密码设备内部存储的指定索引私钥的使用权
参数：		hSessionHandle[in]	与设备建立的会话句柄
uiKeyIndex[in]	密码设备存储私钥的索引值
uiKeyType[in]	密码设备存储私钥的类型, 1-rsa, 2-sm2
pucPassword[in]	使用私钥权限的标识码
uiPwdLength[in]	私钥权限标识码长度，不少于8字节
返回值：	0	成功
非0	失败，返回错误代码
备注：		本规范涉及密码设备存储的密钥对索引值的的起始索引值为1，最大为n，密码设备的实际存储容量决定n值，
*/
DLL int WINAPI SDF_GetPrivateKeyAccessRight_Ex(void *hSessionHandle,
	unsigned int  uiKeyIndex,
	unsigned int  uiKeyType,
	unsigned char *pucPassword,
	unsigned int  uiPwdLength);

/* 
描述：		释放密码设备存储的指定索引私钥的使用授权
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	密码设备存储私钥索引值
返回值：	0	成功
			非0	失败，返回错误代码
 */
DLL int WINAPI SDF_ReleasePrivateKeyAccessRight(void *hSessionHandle, 
                                         unsigned int  uiKeyIndex);

 /* 
描述：		导出密码设备内部存储的指定索引位置的对称密钥，需管理员授权导出
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]		密码设备存储的对称密钥对索引值，用于导出。
			pucInternalKey[out]	对称密钥明文
			uiKeyLen			对称密钥长度
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_ExportSymmKey_Ex(void *hSessionHandle, 
								unsigned int  uiKeyIndex,
                                unsigned char *pucInternalKey,
								unsigned int  *uiKeyLen);

 /* 
描述：		导出密码设备内部存储的指定索引位置的签名公钥
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	密码设备存储的RSA密钥对索引值
			pucPublicKey[out]	RSA公钥结构
返回值：	0	成功
			非0	失败，返回错误代码
*/                              
DLL int WINAPI SDF_ExportSignPublicKey_RSA(void *hSessionHandle, 
                                    unsigned int  uiKeyIndex,
                                    RSArefPublicKey *pucPublicKey);

/*

描述：		导出密码设备内部存储的指定索引位置的签名公钥
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	密码设备存储的ECC密钥对索引值
			pucPublicKey[out]	ECC公钥结构
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_ExportSignPublicKey_ECC(void *hSessionHandle, 
                                 unsigned int  uiKeyIndex,
                                 ECCrefPublicKey *pucPublicKey);

/* 
描述：		导出密码设备内部存储的指定索引位置的加密公钥
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	密码设备存储的ECC密钥对索引值
			pucPublicKey[out]	ECC公钥结构
返回值：	0	成功
			非0	失败，返回错误代码
 */
DLL int WINAPI SDF_ExportEncPublicKey_ECC(void *hSessionHandle, 
								unsigned int  uiKeyId,
								ECCrefPublicKey *pucPublicKey);

/* 
描述：		导出密码设备内部存储的指定索引位置的加密公钥
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	密码设备存储的RSA密钥对索引值
			pucPublicKey[out]	RSA公钥结构
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_ExportEncPublicKey_RSA(void *hSessionHandle, 
                                 unsigned int  uiKeyIndex,
                                 RSArefPublicKey *pucPublicKey);

/*从外部导入RSA或ECC密钥对*/
/* 
描述：		从外部导入RSA或ECC密钥对
参数：		hSessionHandle[in]	与设备建立的会话句柄
			Mechanism[in]	算法标识
			KeyId[in]	    密钥存放的id号
			KeyType[in]		密钥类型
			pucRsaKey[in]	私钥结构体指针
			pucEccPubKey[in]	私钥长度
			pucEccPriKey[in]	公钥结构体指针
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_ImportKeyPair_Ex(void             *hSessionHandle, 
						  unsigned  int    Mechanism,		   
						  unsigned  int    KeyId,
						  unsigned	int	   KeyType,
						  RSArefPrivateKey *pucRsaKey,
						  ECCrefPublicKey *pucEccPubKey,
						  ECCrefPrivateKey *pucEccPriKey);


/*从外部导入对称密钥到密码设备*/
/* 
描述：		从外部导入对称密钥到密码设备
参数：		hSessionHandle[in]	与设备建立的会话句柄
			KeyId[in]	    密钥存放的id号
			KeyType[in]		对称密钥用法类型
			pKey [in]		对称密钥指针
			KeyLen [in]		对称密钥长度, 按字节算(8, 16, 24, 32)
			pTag [in]		对称密钥标签
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_ImportKey_Ex(void             *hSessionHandle, 	   
						  unsigned  int    KeyId,
						  unsigned	int	   KeyType, //'P'=SM1 'R'=SM4 'Z'=8-DES 'X/U'=24-DES 'Y/T'=16-DES
						  unsigned  char   *pKey,
						  unsigned  int	   KeyLen,
						  char			  *pTag);

/*从外部导入对称密钥加密的加密密钥，此对称密钥被签名公钥保护*/
/* 
描述：		从外部导入RSA或ECC密钥对
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiISKIndex[in]	    密钥存放的id号
			uiALGID [in]		算法标识
			cipher [in]			被加密的对称密钥
			pubEncData [in]		被对称密钥加密的加密密钥对，必须为96字节 x|y|d均为32字节
			uiEncDataLength [in] 被对称密钥加密的加密密钥对长度，必须为96
			uiPubKeyEncFlag [in] 指定是否公钥也被加密了，1为密文公钥; 0为明文公钥
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI S_ImportEncKeyPair_ECC(void *hSessionHandle, 
	unsigned int uiISKIndex, 
	unsigned int uiALGID, 
	ECCCipher *cipher, 
	unsigned char *pubEncData,
	unsigned int uiEncDataLength,
	unsigned int uiPubKeyEncFlag);

/* 
描述：		使用内部ECC私钥解密
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiISKIndex [in]	密码设备内部存储的ECC签名私钥的索引值
			KeyType [in] 表明用签名私钥解密还是加密私钥解密
			pucEncData[in]	缓冲区指针，用于存放输入的数据密文
			pucData[out]	缓冲区指针，用于存放输出的数据明文
			puiDataLength[out]	输出的数据明文长度
返回值：	0	成功
			非0	失败，返回错误代码

*/
DLL int WINAPI SDF_InternalDecryptEx_ECC(void *hSessionHandle,
						     unsigned int  uiISKIndex,
							 unsigned	int	   KeyType,
							 ECCCipher *pucEncData,
						     unsigned char *pucData,
						     unsigned int  *uiDataLength);

/* 
描述：		获取对称密钥信息
参数：	hSessionHandle[in]	  与设备建立的会话句柄
			uiISKIndex [in]	      密码设备内部存储的对称密钥的索引值
			uikeytype[out]	      用于存放输出的密钥类型
			puckeycv[out]	        缓冲区指针，用于存放输出的密钥校验值
			uikeycvlen[out]	      用于存放输出的密钥校验值长度
			pcTag[out]            输出密钥标签(<32字节)
返回值：	0	成功
			非0	失败，返回错误代码

*/
DLL int WINAPI SDF_GetSymmKeyInfo(void *hSessionHandle,
						   unsigned int  uiISKIndex,
						   unsigned int *uikeytype,
						   unsigned char *puckeycv,
						   unsigned int *uikeycvlen,
						   char			*pcTag);

/* 
描述：		请求密码设备产生指定类型和模长的ECC密钥对
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiAlgID[in]	指定算法标识
			uiKeyBits [in]	指定密钥长度
			pucPublicKey[out]	ECC公钥结构
			pucPrivateKey[out]	ECC私钥结构
返回值：	0	成功
			非0	失败，返回错误代码
 */
DLL int WINAPI SDF_GenerateKeyPair_ECC(void *hSessionHandle, 
								unsigned int  uiAlgID,
								unsigned int  uiKeyBits,
								ECCrefPublicKey *pucPublicKey,
								ECCrefPrivateKey *pucPrivateKey);


/* 
描述：		使用内部ECC私钥对数据进行签名运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiISKIndex [in]	密码设备内部存储的ECC签名私钥的索引值
			pucData[in]	缓冲区指针，用于存放外部输入的数据
			uiDataLength[in]	输入的数据长度
			pucSignature [out]	缓冲区指针，用于存放输出的签名值数据
返回值：	0	成功
			非0	失败，返回错误代码
备注：		对原文的杂凑运算，在函数外部完成。
*/
DLL int WINAPI SDF_InternalSign_ECC(void *hSessionHandle,
						     unsigned int  uiISKIndex,
						     unsigned char *pucData,
						     unsigned int  uiDataLength,
						     ECCSignature *pucSignature);

/* 
描述：		使用外部ECC私钥对数据进行签名运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiAlgID[in]	算法标识，指定使用的ECC算法
			pucPrivateKey[in]	外部ECC私钥结构
			pucData[in]	缓冲区指针，用于存放外部输入的数据
			uiDataLength[in]	输入的数据长度
			pucSignature[out]	缓冲区指针，用于存放输出的签名值数据
返回值：	0	成功
			非0	失败，返回错误代码
 */
DLL int WINAPI SDF_ExternalSign_ECC(void *hSessionHandle,
					    unsigned int uiAlgID,
						ECCrefPrivateKey *pucPrivateKey,
						unsigned char *pucData,
						unsigned int  uiDataLength,
						ECCSignature *pucSignature);

/* 
描述：		使用内部ECC公钥对ECC签名值进行验证运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiISKIndex [in]	密码设备内部存储的ECC签名公钥的索引值
			pucData[in]	缓冲区指针，用于存放外部输入的数据
			uiDataLength[in]	输入的数据长度
			pucSignature[in]	缓冲区指针，用于存放输入的签名值数据
返回值：	0	成功
			非0	失败，返回错误代码
备注：		对原文的杂凑运算，在函数外部完成。
*/
DLL int WINAPI SDF_InternalVerify_ECC(void *hSessionHandle,
							unsigned int  uiISKIndex,
							unsigned char *pucData,
							unsigned int  uiDataLength,
							ECCSignature *pucSignature);

/* 
描述：		使用外部ECC公钥对ECC签名值进行验证运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiAlgID[in]	算法标识，指定使用的ECC算法
			pucPublicKey[in]	外部ECC公钥结构
			pucData[in]	缓冲区指针，用于存放外部输入的数据
			uiDataLength[in]	输入的数据长度
			pucSignature[in]	缓冲区指针，用于存放输入的签名值数据
返回值：	0	成功
			非0	失败，返回错误代码
备注：		对原文的杂凑运算，在函数外部完成。
*/
DLL int WINAPI SDF_ExternalVerify_ECC(	void *hSessionHandle,
							unsigned int uiAlgID,
							ECCrefPublicKey *pucPublicKey,
							unsigned char *pucDataInput,
							unsigned int  uiInputLength,
							ECCSignature *pucSignature);

/*
描述：		使用外部ECC公钥对数据进行加密运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiAlgID[in]	算法标识，指定使用的ECC算法
			pucPublicKey[in]	外部ECC公钥结构
			pucData[in]	缓冲区指针，用于存放外部输入的数据
			uiDataLength[in]	输入的数据长度
			pucEncData[out]	缓冲区指针，用于存放输出的数据密文
返回值：	0	成功
			非0	失败，返回错误代码
备注：		输入的数据长度uiDataLength不大于ECCref_MAX_LEN。
*/
DLL int WINAPI SDF_ExternalEncrypt_ECC(void *hSessionHandle,
							unsigned int uiAlgID,
							ECCrefPublicKey *pucPublicKey,
							unsigned char *pucData,
							unsigned int  uiDataLength,
							ECCCipher *pucEncData);

/* 
描述：		使用外部ECC私钥进行解密运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiAlgID[in]	算法标识，指定使用的ECC算法
			pucPrivateKey[in]	外部ECC私钥结构
			pucEncData[in]	缓冲区指针，用于存放输入的数据密文
			pucData[out]	缓冲区指针，用于存放输出的数据明文
			puiDataLength[out]	输出的数据明文长度
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_ExternalDecrypt_ECC(void *hSessionHandle,
							unsigned int uiAlgID,
							ECCrefPrivateKey *pucPrivateKey,
							ECCCipher *pucEncData,
							unsigned char *pucData,
							unsigned int  *puiDataLength);


/*
描述：		请求密码设备产生指定模长的RSA密钥对
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyBits [in]	指定密钥模长
			pucPublicKey[out]	RSA公钥结构
			pucPrivateKey[out]	RSA私钥结构
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_GenerateKeyPair_RSA( void *hSessionHandle, 
                                 unsigned int  uiKeyBits,
                                 RSArefPublicKey *pucPublicKey,
                                 RSArefPrivateKey *pucPrivateKey);


/*
描述：		生成会话密钥并用指定索引的内部加密公钥加密输出，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiIPKIndex[in]	密码设备内部存储公钥的索引值
			uiKeyBits[in]	指定产生的会话密钥长度
			pucKey[out]	缓冲区指针，用于存放返回的密钥密文
			puiKeyLength[out]	返回的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		公钥加密数据时填充方式按照PKCS#1 v1.5的要求进行；返回的密钥不包含IV部分。
*/
DLL int WINAPI SDF_GenerateKeyWithIPK_RSA(void *hSessionHandle,
								   unsigned int uiIPKIndex, 
								   unsigned int uiKeyBits,
								   unsigned char *pucKey,						
								   unsigned int *puiKeyLength, 
								   void **phKeyHandle);

/*
描述：		生成会话密钥并用指定索引的内部ECC加密公钥加密输出，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiIPKIndex[in]	密码设备内部存储公钥的索引值
			uiKeyBits[in]	指定产生的会话密钥长度
			pucKey[out]	缓冲区指针，用于存放返回的密钥密文
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		返回的密钥不包含IV部分。
*/
DLL int WINAPI SDF_GenerateKeyWithIPK_ECC(void *hSessionHandle, 
									unsigned int uiIPKIndex,
									unsigned int uiKeyBits,
									ECCCipher *pucKey,
									void **phKeyHandle);

/*
描述：		导入会话密钥并用内部ECC加密私钥解密，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiISKIndex[in]	密码设备内部存储加密私钥的索引值，对应于加密时的公钥
			pucKey[in]	缓冲区指针，用于存放输入的密钥密文
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_ImportKeyWithISK_ECC(void *hSessionHandle,
						   	     unsigned int uiISKIndex,
							     ECCCipher *pucKey,
							     void **phKeyHandle);
/*
描述：		生成会话密钥并用外部ECC公钥加密输出，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyBits[in]	指定产生的会话密钥长度
			uiAlgID[in]	外部ECC公钥的算法标识
			pucPublicKey[in]	输入的外部ECC公钥结构
			pucKey[out]	缓冲区指针，用于存放返回的密钥密文
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		返回的密钥不包含IV部分。
*/
DLL int WINAPI SDF_GenerateKeyWithEPK_ECC(void *hSessionHandle, 
								  unsigned int uiKeyBits,
								  unsigned int uiAlgID,
								  ECCrefPublicKey *pucPublicKey,
								  ECCCipher *pucKey,
								  void **phKeyHandle);
/*
描述：		生成会话密钥并用外部公钥加密输出，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyBits[in]	指定产生的会话密钥长度
			pucPublicKey[in]	输入的外部RSA公钥结构
			pucKey[out]	缓冲区指针，用于存放返回的密钥密文
			puiKeyLength[out]	返回的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		公钥加密数据时填充方式按照PKCS#1 v1.5的要求进行；返回的密钥不包含IV部分。
*/
DLL int WINAPI SDF_GenerateKeyWithEPK_RSA(void *hSessionHandle, 
								   unsigned int uiKeyBits,
								   RSArefPublicKey *pucPublicKey,
                                   unsigned char *pucKey, 
                                   unsigned int *puiKeyLength, 
                                   void **phKeyHandle);

/*
描述：		生成会话密钥并用密钥加密密钥加密输出，同时返回密钥句柄。
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyBits[in]	指定产生的会话密钥长度
			uiAlgID[in]	算法标识，指定对称加密算法
			uiKEKIndex[in]	密码设备内部存储密钥加密密钥的索引值
			pucKey[out]	缓冲区指针，用于存放返回的密钥密文
			puiKeyLength[out]	返回的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		加密模式使用ECB模式。
*/
DLL int WINAPI SDF_GenerateKeyWithKEK(void *hSessionHandle, 
							   unsigned int uiKeyBits,
                               unsigned int  uiAlgID,
                               unsigned int uiKEKIndex, 
                               unsigned char *pucKey, 
                               unsigned int *puiKeyLength,
                               void **phKeyHandle);

/*
描述：		生成会话密钥并用会话密钥加密输出，同时返回密钥句柄。
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyBits[in]	指定产生的会话密钥长度
			uiAlgID[in]	算法标识，指定对称加密算法
			phSessKey[in]	已经存在的一个会话密钥句柄
			pucKey[out]	缓冲区指针，用于存放返回的密钥密文
			puiKeyLength[out]	返回的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		加密模式使用ECB模式。
*/
DLL int WINAPI SDF_GenerateKeyWithSK(void		*hSessionHandle, 
							   unsigned int		uiKeyBits,
                               unsigned int		uiAlgID,
                               void				*phSessKey, 
                               unsigned char	*pucKey, 
                               unsigned int		*puiKeyLength,
                               void				**phKeyHandle);

/*
描述：		导入会话密钥并用内部私钥解密，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiISKIndex[in]	密码设备内部存储加密私钥的索引值，对应于加密时的公钥
			pucKey[in]	缓冲区指针，用于存放输入的密钥密文
			puiKeyLength[in]	输入的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		填充方式与公钥加密时相同。
*/
DLL int WINAPI SDF_ImportKeyWithISK_RSA(void *hSessionHandle, 
                                 unsigned int uiISKIndex, 
                                 unsigned char *pucKey, 
                                 unsigned int uiKeyLength, 
                                 void **phKeyHandle);

/*
描述：		导入会话密钥并用密钥加密密钥解密，同时返回会话密钥句柄。
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiAlgID[in]	算法标识，指定对称加密算法
			uiKEKIndex[in]	密码设备内部存储密钥加密密钥的索引值
			pucKey[in]	缓冲区指针，用于存放输入的密钥密文
			puiKeyLength[in]	输入的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		加密模式使用ECB模式。
*/
DLL int WINAPI SDF_ImportKeyWithKEK(void *hSessionHandle, 
                             unsigned int  uiAlgID,
                             unsigned int uiKEKIndex, 
                             unsigned char *pucKey, 
                             unsigned int uiKeyLength, 
                             void **phKeyHandle);

/*
描述：		导入会话密钥并用会话密钥解密，同时返回会话密钥句柄。
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiAlgID[in]	算法标识，指定对称加密算法
			phSessKey[in]	已经存在的一个会话密钥句柄
			pucKey[in]	缓冲区指针，用于存放输入的密钥密文
			puiKeyLength[in]	输入的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		加密模式使用ECB模式。
*/
DLL int WINAPI SDF_ImportKeyWithSK(void			*hSessionHandle, 
                             unsigned int		uiAlgID,
                             void				*phSessKey, 
                             unsigned char		*pucKey, 
                             unsigned int		uiKeyLength, 
                             void				**phKeyHandle);

/*
描述：		导入明文会话密钥，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			pucKey[in]	缓冲区指针，用于存放输入的密钥明文
			puiKeyLength[in]	输入的密钥明文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_ImportKey(void *hSessionHandle, 
                      unsigned char *pucKey, 
                      unsigned int uiKeyLength, 
                      void **phKeyHandle);

/*
描述：		销毁会话密钥，并释放为密钥句柄分配的内存等资源。
参数：		hSessionHandle[in]	与设备建立的会话句柄
			hKeyHandle[in]	输入的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		在对称算法运算完成后，应调用本函数销毁会话密钥。
*/
DLL int WINAPI SDF_DestoryKey(void *hSessionHandle, 
					   void *hKeyHandle);

/*
描述：		指定使用外部公钥对数据进行运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			pucPublicKey [in]	外部RSA公钥结构
			pucDataInput [in]	缓冲区指针，用于存放输入的数据
			uiInputLength[in]	输入的数据长度
			pucDataOutput[out]	缓冲区指针，用于存放输出的数据
			puiOutputLength[out]	输出的数据长度
返回值：	0	成功
			非0	失败，返回错误代码
备注：		数据格式由应用层封装
*/
DLL int WINAPI SDF_ExternalPublicKeyOperation_RSA(void *hSessionHandle, 
										   RSArefPublicKey *pucPublicKey,
										   unsigned char *pucDataInput,
										   unsigned int  uiInputLength,
										   unsigned char *pucDataOutput,
										   unsigned int  *puiOutputLength);


/*
描述：		指定使用外部私钥对数据进行运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			pucPrivateKey [in]	外部RSA私钥结构
			pucDataInput [in]	缓冲区指针，用于存放输入的数据
			uiInputLength [in]	输入的数据长度
			pucDataOutput [out]	缓冲区指针，用于存放输出的数据
			puiOutputLength [out]	输出的数据长度
返回值：	0	成功
			非0	失败，返回错误代码
备注：		数据格式由应用层封装
*/
DLL int WINAPI SDF_ExternalPrivateKeyOperation_RSA( void *hSessionHandle, 
											 RSArefPrivateKey *pucPirvateKey,
											 unsigned char *pucDataInput,
											 unsigned int  uiInputLength,
											 unsigned char *pucDataOutput,
											 unsigned int  *puiOutputLength);


/*
描述：		使用内部指定索引的公钥对数据进行运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	密码设备内部存储公钥的索引值
			pucDataInput[in]	缓冲区指针，用于存放外部输入的数据
			uiInputLength[in]	输入的数据长度
			pucDataOutput[out]	缓冲区指针，用于存放输出的数据
			puiOutputLength[out]	输出的数据长度
返回值：	0	成功
			非0	失败，返回错误代码
备注：		索引范围仅限于内部签名密钥对，数据格式由应用层封装
*/
DLL int WINAPI SDF_InternalPublicKeyOperation_RSA(void *hSessionHandle,
										   unsigned int  uiKeyIndex,
										   unsigned char *pucDataInput,
										   unsigned int  uiInputLength,
										   unsigned char *pucDataOutput,
										   unsigned int  *puiOutputLength);


/*
描述：		使用内部指定索引的私钥对数据进行运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	密码设备内部存储私钥的索引值
			pucDataInput[in]	缓冲区指针，用于存放外部输入的数据
			uiInputLength[in]	输入的数据长度
			pucDataOutput[out]	缓冲区指针，用于存放输出的数据
			puiOutputLength[out]	输出的数据长度
返回值：	0	成功
			非0	失败，返回错误代码
备注：		索引范围仅限于内部签名密钥对，数据格式由应用层封装
*/
DLL int WINAPI SDF_InternalPrivateKeyOperation_RSA( void *hSessionHandle,
											 unsigned int  uiKeyIndex,
											 unsigned char *pucDataInput,
											 unsigned int  uiInputLength,
											 unsigned char *pucDataOutput,
											 unsigned int  *puiOutputLength);


/* 
描述：		将由内部加密公钥加密的会话密钥转换为由外部指定的公钥加密，可用于数字信封转换。
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	密码设备存储的内部RSA密钥对索引值
			pucPublicKey [in]	外部RSA公钥结构
			pucDEInput [in]	缓冲区指针，用于存放输入的会话密钥密文
			uiDELength[in]	输入的会话密钥密文长度
			pucDEOutput[out]	缓冲区指针，用于存放输出的会话密钥密文
			puiDELength[out]	输出的会话密钥密文长度
返回值：	0	成功
			非0	失败，返回错误代码
 */
DLL int WINAPI SDF_ExchangeDigitEnvelopeBaseOnRSA(void *hSessionHandle, 
										   unsigned int  uiKeyIndex,
										   RSArefPublicKey *pucPublicKey,
										   unsigned char *pucDEInput,
										   unsigned int  uiDELength,
										   unsigned char *pucDEOutput,
										   unsigned int  *puiDELength);


/*
描述：		将由内部加密公钥加密的会话密钥转换为由外部指定的公钥加密，可用于数字信封转换。
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	密码设备存储的ECC密钥对索引值
			uiAlgID[in]	外部ECC公钥的算法标识
			pucPublicKey [in]	外部ECC公钥结构
			pucEncDataIn[in]	缓冲区指针，用于存放输入的会话密钥密文
			pucEncDataOut[out]	缓冲区指针，用于存放输出的会话密钥密文
返回值：	0	成功
			非0	失败，返回错误代码
 */
DLL int WINAPI SDF_ExchangeDigitEnvelopeBaseOnECC(void *hSessionHandle, 
										   unsigned int  uiKeyIndex,
										   unsigned int  uiAlgID,
										   ECCrefPublicKey *pucPublicKey,
										   ECCCipher *pucEncDataIn,
										   ECCCipher *pucEncDataOut);


/*
描述：		使用指定的密钥句柄和IV对数据进行对称加密运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			hKeyHandle[in]	指定的密钥句柄
			uiAlgID[in]	算法标识，指定对称加密算法
			pucIV[in|out]	缓冲区指针，用于存放输入和返回的IV数据
			pucData[in]	缓冲区指针，用于存放输入的数据明文
			uiDataLength[in]	输入的数据明文长度
			pucEncData[out]	缓冲区指针，用于存放输出的数据密文
			puiEncDataLength[out]	输出的数据密文长度
返回值：	0	成功
			非0	失败，返回错误代码
备注：		此函数不对数据进行填充处理，输入的数据必须是指定算法分组长度的整数倍。
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
描述:		使用指定的密钥句柄和IV对数据进行对称解密运算
参数:		hSessionHandle[in]	与设备建立的会话句柄
			hKeyHandle[in]	指定的密钥句柄
			uiAlgID[in]	算法标识，指定对称加密算法
			pucIV[in|out]	缓冲区指针，用于存放输入和返回的IV数据
			pucEncData[in]	缓冲区指针，用于存放输入的数据密文
			uiEncDataLength[in]	输入的数据密文长度
			pucData[out]	缓冲区指针，用于存放输出的数据明文
			puiDataLength[out]	输出的数据明文长度
返回值：	0	成功
			非0	失败，返回错误代码
备注：		此函数不对数据进行填充处理，输入的数据必须是指定算法分组长度的整数倍。
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
描述：			使用指定的密钥句柄和IV对数据进行MAC运算
参数：			hSessionHandle[in]	与设备建立的会话句柄
				hKeyHandle[in]	指定的密钥句柄
				uiAlgID[in]	算法标识，指定MAC加密算法
				pucIV[in|out]	缓冲区指针，用于存放输入和返回的IV数据
				pucData[in]	缓冲区指针，用于存放输出的数据明文
				uiDataLength[in]	输出的数据明文长度
				pucMAC[out]	缓冲区指针，用于存放输出的MAC值
				puiMACLength[out]	输出的MAC值长度
返回值：		0	成功
				非0	失败，返回错误代码
备注：			此函数不对数据进行分包处理，多包数据MAC运算由IV控制最后的MAC值。
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
描述：			三步式数据杂凑运算第一步。
参数：			hSessionHandle[in]	与设备建立的会话句柄
				uiAlgID[in]	指定杂凑算法标识
				pucPublicKey[in]	签名者的ECC公钥，产生用于ECC签名的杂凑值时有效
				pucID[in]	签名者的ID值，产生用于ECC签名的杂凑值时有效
				uiIDLength[in]	签名者的ID长度
返回值：		0	成功
				非0	失败，返回错误代码
备注：			如果在具体的应用中，协商双方没有统一分配的ID，可以将ID设定为常量。
*/
DLL int WINAPI SDF_HashInit(void *hSessionHandle,
					 unsigned int uiAlgID,
					 ECCrefPublicKey *pucPublicKey,//当uiAlgID为带ID的SCH算法机制时该参数才有效
					 unsigned char *pucID,//当uiAlgID为带ID的SCH算法机制时该参数才有效
				     unsigned int uiIDLength);//当uiAlgID为带ID的SCH算法机制时该参数才有效

/*
描述：			三步式数据杂凑运算第二步，对输入的明文进行杂凑运算
参数：			hSessionHandle[in]	与设备建立的会话句柄
				pucData[in]	缓冲区指针，用于存放输入的数据明文
				uiDataLength[in]	输入的数据明文长度
返回值：		0	成功
				非0	失败，返回错误代码
*/
DLL int WINAPI SDF_HashUpdate(void *hSessionHandle,
                       unsigned char *pucData,
                       unsigned int  uiDataLength);

/*
描述：			三步式数据杂凑运算第三步，杂凑运算结束返回杂凑数据并清除中间数据
参数：			hSessionHandle[in]	与设备建立的会话句柄
				pucHash[out]	缓冲区指针，用于存放输出的杂凑数据
				puiHashLength[out]	返回的杂凑数据长度
返回值：		0	成功
				非0	失败，返回错误代码
*/
DLL int WINAPI SDF_HashFinal(void *hSessionHandle,
                      unsigned char *pucHash,
                      unsigned int  *puiHashLength);

/*
描述：			三步式ZUC运算第一步。
参数：			hSessionHandle[in]	与设备建立的会话句柄
				uiAlgID[in]	指定杂凑算法标识
返回值：		0	成功
				非0	失败，返回错误代码
备注：			如果在具体的应用中，协商双方没有统一分配的ID，可以将ID设定为常量。
*/
DLL int WINAPI SDF_ZucInit(void *hSessionHandle,
					 unsigned int uiAlgID,
					 void *hKeyHandle,
					 unsigned char *pucIV,
                       unsigned char *pucData,
                       unsigned int  uiDataLength,
					   unsigned char *pucOut);

/*
描述：			三步式ZUC运算第二步，对输入的明文进行杂凑运算
参数：			hSessionHandle[in]	与设备建立的会话句柄
				pucData[in]	缓冲区指针，用于存放输入的数据明文
				uiDataLength[in]	输入的数据明文长度
返回值：		0	成功
				非0	失败，返回错误代码
*/
DLL int WINAPI SDF_ZucUpdate(void *hSessionHandle,
                       unsigned char *pucData,
                       unsigned int  uiDataLength,
					   unsigned char *pucOut);

/*
描述：			三步式ZUC运算第三步，杂凑运算结束返回杂凑数据并清除中间数据
参数：			hSessionHandle[in]	与设备建立的会话句柄
				pucHash[out]	缓冲区指针，用于存放输出的杂凑数据
				puiHashLength[out]	返回的杂凑数据长度
返回值：		0	成功
				非0	失败，返回错误代码
*/
DLL int WINAPI SDF_ZucFinal(void *hSessionHandle);

/*
描述：			在密码设备内部创建用于存储用户数据的文件
参数：			hSessionHandle[in]	与设备建立的会话句柄
				pucFileName[in]	缓冲区指针，用于存放输入的文件名，最大长度128字节
				uiNameLen[in]	文件名长度
				uiFileSize[in]	文件所占存储空间的长度
返回值：		0	成功
				非0	失败，返回错误代码
*/
DLL int WINAPI SDF_CreateFile( void *hSessionHandle,
                        unsigned char *pucFileName,
						unsigned int uiNameLen,
                        unsigned int uiFileSize);

/*
描述：		读取在密码设备内部存储用户数据的文件的内容
参数：		hSessionHandle[in]	与设备建立的会话句柄
			pucFileName[in]	缓冲区指针，用于存放输入的文件名，最大长度128字节
			uiNameLen[in]	文件名长度
			uiOffset[in]	指定读取文件时的偏移值
			puiFileLength[in|out]	入参时指定读取文件内容的长度；出参时返回实际读取文件内容的长度
			pucBuffer[out]	缓冲区指针，用于存放读取的文件数据
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL int WINAPI SDF_ReadFile(void *hSessionHandle,
                     unsigned char *pucFileName,
					 unsigned int uiNameLen,
                     unsigned int uiOffset,
                     unsigned int  *puiFileLength,
                     unsigned char *pucBuffer);


/*
描述：			向密码设备内部存储用户数据的文件中写入内容
参数：			hSessionHandle[in]	与设备建立的会话句柄
				pucFileName[in]	缓冲区指针，用于存放输入的文件名，最大长度128字节
				uiNameLen[in]	文件名长度
				uiOffset[in]	指定写入文件时的偏移值
				uiFileLength[in]	指定写入文件内容的长度
				pucBuffer[in]	缓冲区指针，用于存放输入的写文件数据
返回值：		0	成功
				非0	失败，返回错误代码
*/
DLL int WINAPI SDF_WriteFile(void *hSessionHandle,
                     unsigned char *pucFileName,
					 unsigned int uiNameLen,
                     unsigned int uiOffset,
                     unsigned int  uiFileLength,
                     unsigned char *pucBuffer);


/* 删除文件 */
DLL int WINAPI SDF_DeleteFile(void *hSessionHandle, unsigned char *pucFileName,unsigned int uiNameLen);


/* 生成密钥协商参数并输出 */
int DLL WINAPI SDF_GenerateAgreementDataWithECC (void *hSessionHandle,
				unsigned int uiISKIndex,
				unsigned int uiKeyBits,
				unsigned char *pucSponsorID,
				unsigned int uiSponsorIDLength,
				ECCrefPublicKey  *pucSponsorPublicKey,
				ECCrefPublicKey  *pucSponsorTmpPublicKey,
				void **phAgreementHandle);



/* 计算会话密钥 */
int DLL WINAPI SDF_GenerateKeyWithECC (void *hSessionHandle, 
				unsigned char *pucResponseID,
				unsigned int uiResponseIDLength,
				ECCrefPublicKey *pucResponsePublicKey,
				ECCrefPublicKey *pucResponseTmpPublicKey,
				void *phAgreementHandle,
				void **phKeyHandle);


/* 产生协商参数并计算会话密钥 */
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
描述：		导出设备内带索引号的数字证书
参数：		hSessionHandle[in]	与设备建立的会话句柄
uiKeyIndex[in]	密码设备存储的证书索引值
uiKeyType[in]	密码设备存储的证书索引值 1-RSA 2-SM2
uiCertType[in]  证书类型，0-根证书 1-签名证书 2-加密证书
CertBuf [out]	证书存储区大小，必须足够在，
CertLen[out]	返回证书长度
返回值：	0	成功 非0	失败，返回错误代码
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

#define SDR_OK								0x0	//操作成功
#define SDR_BASE							0x01000000	//错误码基础值
#define SDR_UNKNOWERR						SDR_BASE + 0x00000001	//未知错误
#define SDR_CONFIGFILE						SDR_BASE + 0x00000002	//配置文件找不到或错误(未启用，下一版本启用)
#define SDR_RESULT_FORMAT					SDR_BASE + 0x00000003   //返回数据格式错误
#define SDR_RESULT_STATUS					SDR_BASE + 0x00000004   //返回数据状态字错误
#define SDR_OPENDEVICE						SDR_BASE + 0x00000005	//打开设备失败(连不到服务)
#define SDR_OPENSESSION						SDR_BASE + 0x00000006	//创建会话失败(连不到服务或服务拒绝接受)
#define SDR_KEYNOTEXIST						SDR_BASE + 0x00000007	//不存在的密钥调用
#define SDR_ALGNOTSUPPORT					SDR_BASE + 0x00000008	//不支持的算法调用
#define SDR_ALGMODNOTSUPPORT				SDR_BASE + 0x00000009	//不支持的算法模式调用
#define SDR_RESULT_CHECK					SDR_BASE + 0x0000000A   //返回数据校验失败
#define SDR_SM2_ENCDATAERR					SDR_BASE + 0x0000000E	//SM2加密数据错误
#define SDR_FILESIZEERR						SDR_BASE + 0x00000017	//文件长度超出限制
#define SDR_FILENOEXIST						SDR_BASE + 0x00000018	//指定的文件不存在
#define SDR_FILEOFSERR						SDR_BASE + 0x00000019	//文件起始位置错误
#define SDR_KEYTYPEERR						SDR_BASE + 0x0000001E	//密钥类型错误
#define SDR_KEYERR							SDR_BASE + 0x0000001F	//密钥错误

#define SDR_HANDLE_CLOSED					SDR_BASE + 0x00000020   //函数执行过程中，该会话已经关闭。
#define SDR_HANDLE_COUNT					SDR_BASE + 0x00000021   //打开的会话太多。
#define SDR_HANDLE_INVALID           		SDR_BASE + 0x00000022   //指定的会话句柄无效。
#define SDR_NOT_LOGIN       	    		SDR_BASE + 0x00000025   //私钥使用权限未获取。
#define SDR_INPUT_LEN_ERROR           		SDR_BASE + 0x00000026   //输入参数长度错误。
#define SDR_KEYID_INVALID           		SDR_BASE + 0x00000027   //含义：指定的密钥号非法。
#define SDR_MECHANISM_INVALID				SDR_BASE + 0x00000028   //含义：机制无效。
#define SDR_NOT_INITIALIZED         		SDR_BASE + 0x00000029   //含义：未调用初始化。
#define SDR_ALREADY_INITIALIZED      		SDR_BASE + 0x0000002A   //含义：初始化已调用。
#define SDR_DEVICEHANDLE_INVALID			SDR_BASE + 0x0000002B   //设备句柄无效
#define SDR_OUTPUT_LEN_ERROR				SDR_BASE + 0x0000002C   //输出长度不正确
#define SDR_OUTPUT_BUFFER_IVVALID			SDR_BASE + 0x0000002D	//输出存储区无效

#define SDR_KEY_MEM_FULL					SDR_BASE + 0x0000002E
#define SDR_SESSION_INIT					SDR_BASE + 0x00000031   // 创建会话失败
#define SDR_KEYPAIR_LENGTH					SDR_BASE + 0x00000032   // 非对称密钥的指数长度
#define SDR_PADDING_RSA						SDR_BASE + 0x00000033   // RSA padding 错误
#define SDR_UNPADDING_RSA					SDR_BASE + 0x00000034   // RSA unpadding 错误
#define SDR_HANDLE_SYMKEY_INVALID			SDR_BASE + 0x00000035   // 会话密钥句柄无效

#define SDR_PARAMETER_ERR					SDR_BASE + 0x00000037	//接口参数错误或不能识别

#define ERROR_COMMAND_FORMAT				0xF0000001 //报文不能被解析(错误报文)
#define ERROR_DEVICE_OPEN					0xF0000002 //打开USB设备失败(密码器掉线或故障)
#define ERROR_USB_WRITE						0xF0000003 //USB设备写失败
#define ERROR_USB_READ						0xF0000004 //USB设备读失败
#define ERROR_USB_READ_TIMEOUT				0xF0000040 //USB任务超时
#define ERROR_LINK_MAX						0xF0000005 //客户端连接数量超出上限
#define ERROR_USB_MALFUNCTION				0xF0000006 //USB设备故障

#define PCIAPIERR_SOCK_CONNECT				0xF0000007 //Socket连接服务错误
#define PCIAPIERR_SOCK_SELECT_INSEND		0xF0000008 //socket select调用错误,在发送时
#define PCIAPIERR_SOCK_SELECT_INRECV		0xF0000009 //socket select调用错误,在接收时
#define PCIAPIERR_SOCK_SEND					0xF000000A //socket send错误
#define PCIAPIERR_SOCK_RECV					0xF000000B //socket recv错误
#define PCIAPIERR_SOCK_INVALID				0xF000000C //socket无效
#define PCIAPIERR_SOCK_CLOSE				0xF000000D //socket被对方关闭
#define PCIAPIERR_SOCK_TIMEOUT_SEND			0xF000000E //socket发送超时
#define PCIAPIERR_SOCK_TIMEOUT_RECV			0xF000000F //接收超时

#endif

