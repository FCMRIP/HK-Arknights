#include "hook.h"

void *(*old_HGSDK_HGSDK__CallIdentityVerifyService_c__AnonStoreyA____m__0)(void *_this, void *response);
void *(*old_HGSDK_HGSDK__CallLoginService_c__AnonStorey3____m__0)(void *_this, void *response);
void *(*old_HGSDK_HGSDK__CallAuthService_c__AnonStorey4____m__0)(void *_this, void *response);
void *(*old_HGSDK_HGSDK__CallSmsCodeLoginService_c__AnonStorey7____m__0)(void *_this, void *response);
void *(*old_Torappu_UI_UIPopupWindow___Alert)(void *_this, void *content, void *onConfirm);
void *(*old_HGSDK_HGSDK_PingManager__FirstPing_c__AnonStorey1____m__0)(void *_this, void *response);
void *(*old_HGSDK_HGSDK_PingManager____DoPeriodicPing_m__0)(void *_this, void *response);

void *HGSDK_HGSDK_PingManager____DoPeriodicPing_m__0(void *_this, void *response){
	unsigned char *p =(unsigned char *)response;
	//int result=*(int *)(p+0x8);
	//LOGW("result:%d",result);
	*(int *)(p+0x8)=0;
	*(int *)(p+0xC)=5400; //抓包后发现一直无意义的ping，这里改一下ping间隙。
	//result=*(int *)(p+0x8);
	//LOGW("result2:%d",result);
	//int interval=*(int *)(p+0xC);
	//LOGW("interval:%d",interval);
	//CString *message=(CString *)(*(int *)(p+0x10));
	//CString_Print(message);

	return old_HGSDK_HGSDK_PingManager____DoPeriodicPing_m__0(_this,response);
}

void *HGSDK_HGSDK_PingManager__FirstPing_c__AnonStorey1____m__0(void *_this, void *response){
	unsigned char *p =(unsigned char *)response;
	//int result=*(int *)(p+0x8);
	//LOGW("result:%d",result);
	*(int *)(p+0x8)=0;
	*(int *)(p+0xC)=5400; //抓包后发现一直无意义的ping，这里改一下ping间隙。
	//result=*(int *)(p+0x8);
	//LOGW("result2:%d",result);
	//int interval=*(int *)(p+0xC);
	//LOGW("interval:%d",interval);
	//CString *message=(CString *)(*(int *)(p+0x10));
	//CString_Print(message);
	return old_HGSDK_HGSDK_PingManager__FirstPing_c__AnonStorey1____m__0(_this,response);
}
/*
void *Torappu_UI_UIPopupWindow___Alert(void *_this, void *content, void *onConfirm){
	CString_Print((CString *)content);
	return old_Torappu_UI_UIPopupWindow___Alert(_this,content,onConfirm);
}

void *HGSDK_HGSDK__CallSmsCodeLoginService_c__AnonStorey7____m__0(void *_this, void *response){
	unsigned char *p =(unsigned char *)response;
	*(p+0x18)=1;
	unsigned char isAuthenticate=*(p+0x18);
	*(p+0x19)=0;
	unsigned char isMinor=*(p+0x19);
	LOGW("isAuthenticate:%d",isAuthenticate);
	LOGW("isMinor:%d",isMinor);
	return old_HGSDK_HGSDK__CallSmsCodeLoginService_c__AnonStorey7____m__0(_this,response);
}

void *HGSDK_HGSDK__CallAuthService_c__AnonStorey4____m__0(void *_this, void *response){
	unsigned char *p =(unsigned char *)response;
	unsigned char *isAuthenticate=(p+0xC);
	unsigned char *isMinor=(p+0xD);
	unsigned char *needAuthenticate=(p+0xE);
	
	*(p+0xC)=0;
	*(p+0xD)=0;
	*(p+0xE)=0;
	
	LOGW("isAuthenticate:%d",*isAuthenticate);
	LOGW("isMinor:%d",*isMinor);
	LOGW("needAuthenticate:%d",*needAuthenticate);
	
	return old_HGSDK_HGSDK__CallAuthService_c__AnonStorey4____m__0(_this,response);
}

void *HGSDK_HGSDK__CallLoginService_c__AnonStorey3____m__0(void *_this, void *response){
	unsigned char *p =(unsigned char *)response;
	*(p+0x18)=1;
	unsigned char isAuthenticate=*(p+0x18);
	*(p+0x19)=0;
	unsigned char isMinor=*(p+0x19);
	int result=*(int *)(p+0x8);
	LOGW("isAuthenticate:%d",isAuthenticate);
	LOGW("isMinor:%d",isMinor);
	//LOGW("result:%d",result);
	return old_HGSDK_HGSDK__CallLoginService_c__AnonStorey3____m__0(_this,response);
}

void *HGSDK_HGSDK__CallIdentityVerifyService_c__AnonStoreyA____m__0(void *_this, void *response){
	unsigned char *p =(unsigned char *)response;
	*(int *)(p+0xC)=0;
	unsigned char isMinor=*(int *)(p+0xC);
	LOGW("isMinor:%d",isMinor);
	CString *message=(CString *)(*(int *)(p+0x10));
	CString_Print(message);
	*(int *)(p+0x8)=0;
	int result=*(int *)(p+0x8);
	LOGW("result:%d",result);
	return old_HGSDK_HGSDK__CallIdentityVerifyService_c__AnonStoreyA____m__0(_this,response);
}
*/
__attribute__((constructor))
void libhook_main() {
    while(libBase == 0) { 
        libBase = get_libBase(libName); 
        sleep(1); 
    }   
    // old_Elements_Battle_BattleManager__GetEnemyCtrlLength = reinterpret_cast<int32_t (*)(void *)>(getRealOffset(0x9B5704));
    /*MSHookFunction((void *) getRealOffset(0x1188268),
                   (void *) HGSDK_HGSDK__CallIdentityVerifyService_c__AnonStoreyA____m__0,
                   (void **) &old_HGSDK_HGSDK__CallIdentityVerifyService_c__AnonStoreyA____m__0);*/
	/*MSHookFunction((void *) getRealOffset(0x1188850),
                   (void *) HGSDK_HGSDK__CallLoginService_c__AnonStorey3____m__0,
                   (void **) &old_HGSDK_HGSDK__CallLoginService_c__AnonStorey3____m__0);	
	MSHookFunction((void *) getRealOffset(0x1187A34),
                   (void *) HGSDK_HGSDK__CallAuthService_c__AnonStorey4____m__0,
                   (void **) &old_HGSDK_HGSDK__CallAuthService_c__AnonStorey4____m__0);		
	MSHookFunction((void *) getRealOffset(0x1188DAC),
                   (void *) HGSDK_HGSDK__CallSmsCodeLoginService_c__AnonStorey7____m__0,
                   (void **) &old_HGSDK_HGSDK__CallSmsCodeLoginService_c__AnonStorey7____m__0);*/
	/*MSHookFunction((void *) getRealOffset(0x108E534),
                   (void *) Torappu_UI_UIPopupWindow___Alert,
                   (void **) &old_Torappu_UI_UIPopupWindow___Alert);*/
	MSHookFunction((void *) getRealOffset(0x36A2800), // x86:0x36A2800 arm:0x395ADF0
                   (void *) HGSDK_HGSDK_PingManager__FirstPing_c__AnonStorey1____m__0,
                   (void **) &old_HGSDK_HGSDK_PingManager__FirstPing_c__AnonStorey1____m__0);
	MSHookFunction((void *) getRealOffset(0x36A2326), // x86:0x36A2326 arm:0x395A814
                   (void *) HGSDK_HGSDK_PingManager____DoPeriodicPing_m__0,
                   (void **) &old_HGSDK_HGSDK_PingManager____DoPeriodicPing_m__0);
}
