#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "YingJiGuangBoSignatureDLL/TassYJGBCmd_SJJ.h"

#ifdef _MSC_VER
    #pragma comment(lib, ".\\libTassYJGBCmd_SJJ1313.lib")    //根据设备加载不同的库
    //#pragma comment(lib, ".\libTassYJGBCmd_SJJ1507.lib")
    #pragma warning(disable:4996)
#endif

int main(void)
{
    void *hDevHandle = NULL;
    int rt, count, len;
    FILE *pf;
    unsigned char buf[1024] = { 0 };
    //SetCfgPathName("./tacipher.ini"); //设备为SJJ1507且运行使用平台为linux时此接口有效
    rt = OpenDevice(&hDevHandle);
    if (rt)
    {
        printf("OpenDevice Failed, Error Code: %04X", rt);
        getchar();
        return;
    }
    printf("OpenDevice Success\n");
    len = 1024;
    rt = Platform_CalculateSignature(
        hDevHandle,
        0,
        "\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB\xCC\xDD\xEE\xFF",
        16,
        buf,
        &len);
    if (rt)
    {
        printf("Sign Failed\n");
        getchar();
        return;
    }
    printf("Singature%s\n", buf);
    rt = Platform_VerifySignature(
        hDevHandle,
        0,
        "\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB\xCC\xDD\xEE\xFF",
        16,
        buf);
    printf("Verify %s\n", rt ? "Failed" : "Success");
    CloseDevice(hDevHandle);
    getchar();
    return;
}