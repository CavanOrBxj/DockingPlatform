/*-----------------------------------------------------------------
|	mult_thread.c
|	SDF 接口性能测试程序，测试接口如下：
|	1. 产生随机数
|	2. RSA密钥产生。1024 & 2048
|	3. RSA密钥的私钥运算。1024 & 2048
|	4. RSA密钥的公钥运算。1024 & 2048
|	5. SM2密钥产生
|	6. SM2签名
|	7. SM2验证签名
|	8. SM2加密
|	9. SM2解密
|  10. SM4加密
------------------------------------------------------------------*/
#include <malloc.h>
#include <memory.h>
#include <string.h>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SDF.h"
#include "devdef.h"

#define  MAXWATCHTHREAD	256

size_t thread_num, repeat_num, fnc_slect, data_len;

unsigned int *hDeviceHandle = NULL;

// 函数指针

//线程池参数
static unsigned int s_thread_para[128][9];//线程参数
pthread_mutex_t s_mutex[4096];//线程锁

// 
typedef int (*FUNC_CALL)(unsigned int *session, unsigned int len);
typedef int (*FUNC_CALL_CMP)(unsigned int *session, unsigned char *input, unsigned int inlen, unsigned char *check);

FUNC_CALL fnc_ptr;
FUNC_CALL_CMP fnc_ptr_cmp;

// 线程函数
extern int task_Random_Gen	(unsigned int *session, unsigned int dataLen);
extern int task_RSA_Gen		(unsigned int *session, unsigned int modules);
extern int task_RSA_Private	(unsigned int *session, unsigned int modules);
extern int task_RSA_Public	(unsigned int *session, unsigned int modules);
extern int task_RSAIndex_Private	(unsigned int *session, unsigned int modules);
extern int task_RSAIndex_Public	(unsigned int *session, unsigned int modules);
extern int task_SM1_Encrypt(unsigned int *session, unsigned char *input, unsigned int inlen, unsigned char *check);
extern int task_SM1_OFB(unsigned int *session, unsigned char *input, unsigned int inlen, unsigned char *check);
extern int task_SM2_Gen(unsigned int *session, unsigned int dataLen);
extern int task_3DES_Encrypt(unsigned int *session, unsigned char *input, unsigned int inlen, unsigned char *check);
extern int task_SSF33_Encrypt(unsigned int *session, unsigned char *input, unsigned int inlen, unsigned char *check);
extern int task_SM1_OFB(unsigned int *session, unsigned char *input, unsigned int inlen, unsigned char *check);
extern int task_SM2_Gen		(unsigned int *session, unsigned int dataLen);
extern int task_SM2_Sign	(unsigned int *session, unsigned int dataLen);
extern int task_SM2_Verify	(unsigned int *session, unsigned int dataLen);
extern int task_SM2Index_Sign	(unsigned int *session, unsigned int dataLen);
extern int task_SM2Index_Verify	(unsigned int *session, unsigned int dataLen);
extern int task_SM2_Encrypt	(unsigned int *session, unsigned int dataLen);
extern int task_SM2_Decrypt	(unsigned int *session, unsigned int dataLen);
extern int task_SM3_Encrypt(unsigned int *session, unsigned int dataLen);
extern int task_SM4_Encrypt(unsigned int *session, unsigned char *input, unsigned int inlen, unsigned char *check);
extern int task_ZUC(unsigned int *session, unsigned char *input, unsigned int inlen, unsigned char *check);
extern int task_SM7_Encrypt(unsigned int *session, unsigned char *input, unsigned int inlen, unsigned char *check);
extern int task_SM7_OFB(unsigned int *session, unsigned char *input, unsigned int inlen, unsigned char *check);

// 数据函数
extern int task_Data_Preparation( unsigned int sel, unsigned int len );
extern int task_Data_Prepare_Cmp(unsigned int *phSessionHandle, unsigned int sel, unsigned char *input, unsigned int inlen, unsigned char *check);

int					g_encdec;  //enc dec
int					g_algmod;  //ecb cbc mac || eia eea
int					g_inoutkey; //inkey outkey
int					g_sm2_index;
int					g_rsa_index;
int					g_sym_index;
unsigned int		g_iModuls;

int getitemvalue(char *filename, char *itemname, char *itemvalue )
{

	FILE * inifile;
	char *valuehead, line[128];

	memset(line, 0x0, sizeof(line));
	inifile = fopen(filename, "r" );
	if ( inifile == NULL )
	{
		return -1;
	}

	while (!feof(inifile)) 
	{
		fgets(line, 127, inifile);
		if (strstr(line, itemname) == line)
			break;
	}

	if (feof(inifile))
	{
		fclose(inifile);
		return -2;
	}

	valuehead = strstr(line, "=");

	if (valuehead == NULL)
	{
		fclose(inifile);
		return -3;
	}

	valuehead++;
	strncpy(itemvalue, valuehead, 120);
	fclose(inifile);
	return 0;
}

int Config_Algo()
{	
	int result;
	char value[128];
	FILE *tmpfile;
	char config_fname[260];

	strcpy(config_fname, "./multsel.ini");
	tmpfile = fopen(config_fname, "r");
	if(tmpfile == NULL) 
	{
		return 0;
	}
	fclose(tmpfile);

	result = getitemvalue(config_fname, "enc", value);
	if (result)
	{
		return result;
	}
	g_encdec = atoi(value);

	result = getitemvalue(config_fname, "mod", value);
	if (result)
	{
		return result;
	}
	g_algmod = atoi(value);

	result = getitemvalue(config_fname, "out", value);
	if (result)
	{
		return result;
	}
	g_inoutkey = atoi(value);

	result = getitemvalue(config_fname, "sm2id", value);
	if (result)
	{
		return result;
	}
	g_sm2_index = atoi(value);

	result = getitemvalue(config_fname, "rsaid", value);
	if (result)
	{
		return result;
	}
	g_rsa_index = atoi(value);

	result = getitemvalue(config_fname, "symid", value);
	if (result)
	{
		return result;
	}
	g_sym_index = atoi(value);

	return 0;
}

static void * get_testfnc_ptr(int slt)
{
	switch ( slt ) 
	{
	case 1: // 随机数（128M）
		return task_Random_Gen;
	case 2: // RSA 密钥产生
		return task_RSA_Gen;
	case 3: // RSA 私钥运算
		return task_RSA_Private;
	case 4: // RSA 公钥运算
		return task_RSA_Public;
	case 5: // SM2 密钥产生
		return task_SM2_Gen;
	case 6: // SM2 签名
		return task_SM2_Sign;
	case 7: // SM2 验证签名
		return task_SM2_Verify;
	case 8: // SM2 加密
		return task_SM2_Encrypt;
	case 9: // SM2 解密
		return task_SM2_Decrypt;
	case 10: // SM4 加密
		return task_SM4_Encrypt;
	case 11:
		return task_SM1_Encrypt;
	case 12:
		return task_SM1_OFB;
	case 13:
		return task_SM3_Encrypt;
	case 14:
		return task_3DES_Encrypt;
	case 15:
		return task_ZUC;
	case 16:
		return task_SSF33_Encrypt;
	case 17:
		return task_SM7_Encrypt;
	case 18:
		return task_SM7_OFB;
	default:
		return NULL;
	}
}

#ifndef UNIX
void pthread_mutex_lock(pthread_mutex_t *t) {
	EnterCriticalSection(t);
}

void pthread_mutex_destroy(pthread_mutex_t *t)
{
	DeleteCriticalSection(t);
}

void pthread_mutex_unlock(pthread_mutex_t *t) {
	LeaveCriticalSection(t);
}

void sleep(int sec) {
	Sleep(sec * 1000);
}
#endif

void * task (unsigned int thread_para[])
{
	//临时变量
	int	pool_index;	//线程池索引
	int	test_type;
	size_t iRepeat;
	unsigned char input[16*1024], check[16 * 1024];
	unsigned int rv;
	size_t i;
	unsigned int *phSessionHandle = NULL;

		//线程脱离创建者
#ifdef UNIX
		pthread_detach(pthread_self());
#endif

	pool_index = thread_para[7];
	test_type = thread_para[1];

	if (hDeviceHandle == NULL) 
	  return NULL;

	pthread_mutex_lock(s_mutex + pool_index);//等待线程解锁

	rv = SDF_OpenSession(hDeviceHandle, (void **)&phSessionHandle);
	if ( rv ) {
		fprintf(stdout, "SDF_OpenSession error. ret=[0x%08x]. \n\n", rv );
		pthread_mutex_unlock(s_mutex + pool_index);
		return NULL;
	}

	switch(test_type)
	{
	case 10:
	case 11:
	case 12:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
		memset(input, 0, 16 * 1024);
//		srand(pool_index);
//		for(i=0; i<8192; i++)
//			input[i] = rand() % 256;

		rv = task_Data_Prepare_Cmp(phSessionHandle, test_type, input, data_len, check);
		if(rv)
		{
			printf("task_Data_Prepare_Cmp failed. %08x\n", rv);
			pthread_mutex_unlock(s_mutex + pool_index);
			break;
		}

		iRepeat = repeat_num;

		for ( i = 0; i < iRepeat; i++ ) { // 根据函数指针确定需要调用的具体函数
			rv = fnc_ptr_cmp(phSessionHandle, input, data_len, check);

			if( rv == 0xABCD1234)
				thread_para[6]++;
			else if ( rv ) 
				thread_para[8]++;
			else
				thread_para[5]++;
		}
		break;
	default:
		for ( i = 0; i < repeat_num; i++ ) { // 根据函数指针确定需要调用的具体函数
			rv = fnc_ptr(phSessionHandle, data_len );
			if( rv == 0xABCD1234)
				thread_para[6]++;
			else if ( rv )
			{	
				thread_para[8]++;
			}
			else
				thread_para[5]++;
		}
		break;
	}

	//线程结束
	thread_para[0] = 0;//设置线程占用标志为"空闲"

	SDF_CloseSession(phSessionHandle);

#ifdef UNIX
	pthread_exit(NULL);
#else
	return NULL;
#endif
}

static int init_thread_pool(void)
{
	size_t i;

#ifdef UNIX
	pthread_t	tid;
#else
	HANDLE	tid;
#endif

	size_t thCnt = thread_num<MAXWATCHTHREAD?thread_num:MAXWATCHTHREAD;

	//初始化线程池参数
	for(i = 0; i < thread_num; i++) {
		s_thread_para[i][0] = 1;//设置线程占用标志为"使用"
		s_thread_para[i][1] = 0;
		s_thread_para[i][2] = 0;
		s_thread_para[i][3] = 0;
		s_thread_para[i][4] = 0;
		s_thread_para[i][5] = 0;
		s_thread_para[i][6] = 0;
		s_thread_para[i][7] = i;//线程池索引
		s_thread_para[i][8] = 0;
#ifdef UNIX
#else
		InitializeCriticalSection(s_mutex+i);
#endif		
		pthread_mutex_lock(s_mutex + i);//线程锁
	}

	switch(fnc_slect)
	{
	case 10:
	case 11:
	case 12:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
		fnc_ptr_cmp = get_testfnc_ptr(fnc_slect);
		if ( fnc_ptr_cmp == NULL ) {
			fprintf(stderr, "Function Select[%d] error.\r\n", (int)fnc_slect);
			return (-1);
		}
		break;
	default:
		fnc_ptr = get_testfnc_ptr( fnc_slect );
		if ( fnc_ptr == NULL ) {
			fprintf(stderr, "Function Select[%d] error.\r\n", (int)fnc_slect);
			return (-1);
		}
		break;
	}

	//创建线程池
	for(i = 0; i < thCnt; i++) {
		s_thread_para[i][1] = fnc_slect;
#ifdef UNIX
		int rc = pthread_create(&tid, 0, (void *)task, (void *)(s_thread_para[i]));
		if (0 != rc) {
			fprintf(stderr, "pthred_create() failed(%d)\r\n", (int)i);
			return(-1);
		}
#else
		tid = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)task,(void *)(s_thread_para[i]),0,NULL);
		if ( tid == NULL )
		{
			fprintf(stderr, "pthred_create() failed(%d)\r\n", i);
			return(-1);
		}
		CloseHandle(tid);
#endif
	}

	return 0;
}

static int test_mult_thread()
{
	int	rc;
	size_t i;
	int	active_num = 0;
	int	connect_err = 0;
	int	send_err = 0;
	int	recv_err = 0;
	int	close_num = 0;
	float	finish_num = 0;
	int	cmp_num = 0;
	int 	yewu_err = 0;

	time_t	t1, t2;
	time_t	t3;

	rc = init_thread_pool();
	if ( 0 != rc ) 
		return rc;

	//线程解锁
	for(i = 0; i < thread_num; i++) pthread_mutex_unlock(s_mutex + i);

		//统计输出
	t1 = time(NULL);
	for( ; ; ) {
		active_num = 0;
		connect_err = 0;
		send_err = 0;
		recv_err = 0;
		close_num = 0;
		finish_num = 0;
		cmp_num = 0;
		yewu_err = 0;

		for(i = 0; i < thread_num; i++) {
			active_num += s_thread_para[i][0];
			connect_err += s_thread_para[i][1];
			send_err += s_thread_para[i][2];
			recv_err += s_thread_para[i][3];
			close_num += s_thread_para[i][4];
			finish_num += s_thread_para[i][5];
			cmp_num += s_thread_para[i][6];
			yewu_err += s_thread_para[i][8];
		}

		fprintf(stdout, "active_num = %d finish_num = %.2f cmp_num = %d yewu_err = %d\r\n",
				active_num, finish_num, cmp_num, yewu_err);

//		if(runtimes++ > 8)
//			break;

#ifdef UNIX
		sleep(2);
#else
		Sleep(2000);
#endif

		if (0 == active_num) break;
	}
	t2 = time(NULL);
	t3 = t2 - t1;
	
	if((fnc_slect == 1) || ((fnc_slect >= 8) && (fnc_slect <= 16)))
		fprintf(stdout, "Mbps is %.2fMbps/sec.\r\n", ((finish_num + thread_num * 2)*data_len * 8) / 1024 / 1024 / t3);
	else
		fprintf(stdout, "Total time is %d;\r\nAverage is %.2f/sec\r\n", (int)t3, ((finish_num+thread_num*2) / t3));

	system("pause");
	exit(0);

	return 0;
}


static int parse_arg(int argc, char *argv[])
{
	if (2 > argc) {
		printf( "----------- Function select --------------\n" );
		printf( "|                                         |\n" );
		printf( "|        1.  Random Generate.             |\n" );
		printf( "|        2.  RSA Generate.                |\n" );
		printf( "|        3.  RSA Private Key Algorithm    |\n" );
		printf( "|        4.  RSA Public Key Algorithm     |\n" );
		printf( "|        5.  SM2 Generate                 |\n" );
		printf( "|        6.  SM2 Sign                     |\n" );
		printf( "|        7.  SM2 Verify                   |\n" );
		printf( "|        8.  SM2 Encrypt                  |\n" );
		printf( "|        9.  SM2 Decrypt                  |\n" );
		printf( "|       10.  SM4 Encrypt                  |\n" );
		printf( "|       11.  SM1 ECB Encrypt              |\n" );
		printf( "|       12.  SM1 OFB Encrypt              |\n" );
		printf( "|       13.  SM3 HASH                     |\n" );
		printf( "|       14.  3DES ECB Encrypt             |\n" );
		printf( "|       15.  ZUC EEA Encrypt              |\n" );
		printf( "|       16.  SSF33 ECB Encrypt            |\n" );
		printf( "|       17.  SM1 ECB Encrypt              |\n" );
		printf( "|       18.  SM1 OFB Generate             |\n" );
		printf( "|                                         |\n" );
		printf( "------------------------------------------\n" );
		fprintf(stderr, "Usage: %s <thread_num> <repeat_num> <Function slect> <Data length OR Modules>\r\n", argv[0]);
		return(-1);
	}
	
	thread_num = atoi(argv[1]);
	if ((1 > thread_num) || (128 < thread_num)) {
		fprintf(stderr, "Error: thread_num MUST between 1 to 2048\r\n");
		return(-1);
	}

	repeat_num = atoi(argv[2]);
	if ((1 > repeat_num) || (1000000000 < repeat_num)) {
		fprintf(stderr, "Error: repeat_num MUST between 1 to 100000000\r\n");
		return(-1);
	}

	fnc_slect = atoi(argv[3]);
	if ((1 > fnc_slect) || (18 < fnc_slect)) {
		fprintf(stderr, "Error: Function select MUST between 1 to 14\r\n");
		return(-1);
	}

	data_len = atoi(argv[4]);
	if ((1 > data_len) || (65536 < data_len)) {
		fprintf(stderr, "Error: Data length OR RSA modules error.\r\n");
		return(-1);
	}
	g_iModuls = data_len;

	return(0);
}

int main(int argc, char *argv[])
{
	int rv;
	void *hSessionHandle;
	
	
	rv = SDF_OpenDevice((void **)&hDeviceHandle);
	if (rv != SDR_OK) {
		printf("设备接口初始化失败。\r\n\r\n");	
		exit(EXIT_FAILURE);
	}

	Config_Algo();
	
	SDF_OpenSession(hDeviceHandle, &hSessionHandle);

	if (0 != parse_arg(argc, argv))
	{
		printf("功能错误，请重选。\r\n");
		exit(EXIT_FAILURE);
	}
	
	if(fnc_slect != 10 && fnc_slect != 11 && fnc_slect != 12 && fnc_slect != 14 && fnc_slect != 15 && fnc_slect != 16 && fnc_slect != 17 && fnc_slect != 18)
	{
		rv = task_Data_Preparation(fnc_slect, data_len);
		if ( rv ) {
			printf("数据准备初始化失败。\r\n\r\n");	
			exit(EXIT_FAILURE);
		}
	}

	rv = test_mult_thread(repeat_num);

	SDF_CloseDevice(hDeviceHandle);
	if ( rv ) 
		return (-1);

	return 0;
}
