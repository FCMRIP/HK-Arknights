# ArkN未成年版 更新至1.5.81
## 下载
Ofb
链接：https://honoka-my.sharepoint.com/:f:/g/personal/msm8940_honoka_onmicrosoft_com/Eh_6Y1YgwJ9DhxCbYyePwXQBV0en6-P99dz6eWXQykm7vw?e=RTY3gv

本项目源于 MengLuwa/ArkNightsForMinor 原作者 MengLuwa 已经注销，原仓库已被删除

同时支持arm v7和x86
没有修改包名
## 如何延续这个项目
~~如果我死了的话~~

需要以下工具

* Android NDK 16b (梯子)<br>https://developer.android.com/ndk/downloads/older_releases

* Android-Hooking-Template-master

* Il2CppDumper

* APK Easy Tool

* GameGuardian

* 明日方舟安装包

* JDK
* MengLuwa/ArkNightsForMinor

* 一个安卓armeabi-v7a模拟器

* 一个安卓x86模拟器

整合包 :https://wwa.lanzoui.com/ipJr2lbre0d


### 准备工作：

1-11可参考 [BV1Ui4y1V7Pi](https://www.bilibili.com/video/BV1Ui4y1V7Pi)
- 在模拟器中安装 GameGuardian(安装后名为Game) 打开并授予ROOT权限
- 这里模拟器选择是会影响结果的(参考工具时的说明)
- 点击 GameGuardian 右下角的开始
- 打开ArkN
- 点击左上角的 GameGuardian 图标，再点击左上角的应用图标，并选择明日方舟(最大的那个)
- 点击右上角从关闭图标开始的倒数第三个图标，再点击倒数第二个图标，下翻，找到导出内存
- 点击 “从:0000000” 右边的倒三角，下翻，找到末尾为 libil2cpp.so 的地址，记录开始的地址
- 下翻，找到 libil2cpp.so 最后一次出现的地址，记录结束的地址
- 路径选择模拟器的共享文件夹，保存
- 找到明日方舟安装包，右键打开方式为解压软件打开
- 找到压缩包下 assets/bin/Data/Managed/Metadata/global-metadata.dat ，并复制出来
- 打开 Il2CppDumper ，选择导出的bin文件和 global-metadata.dat ，并输入刚才记录下了的 libil2cpp.so 的开始地址，等待工具反编译
- 打开 dump.cs (最好用记事本，vs之内的会卡死的) 按下 ctrl+f 进行搜索
- 安装JDK以提供反编译时的运行环境

`HGSDK.PingManager.<FirstPing>c__AnonStorey1`
`<_DoPeriodicPing>m__0`
- 找到类似于下面的内容

```csharp
private sealed class HGSDK.PingManager.<FirstPing>c__AnonStorey1 // TypeDefIndex: 14827
{
                   // Fields
                   internal Action onSuc; // 0x8
                   internal Action onFail; // 0xC
                   internal HGSDK.PingManager $this; // 0x10
                   // Methods
                   // RVA: 0x36A18CF Offset: 0x36A18CF VA: 0x9A9288CF
                   public void .ctor() { }
                   // RVA: 0x36A2800 Offset: 0x36A2800 VA: 0x9A929800
                   internal void <>m__0(PingResponse response) { }
                   // RVA: 0x36A296C Offset: 0x36A296C VA: 0x9A92996C
                   internal void <>m__1(ResponseError error) { }

}
```
```csharp
// RVA: 0x36A2326 Offset: 0x36A2326 VA: 0x9A929326
private void <_DoPeriodicPing>m__0(PingResponse response) { }
```

- 记录m__0的 offset，例如这里是 0x36A2800 和0x36A2326 （x86和armeabi-v7a下地址是不一样的）

- 编辑 MengLuwa/ArkNightsForMinor 的  hook.cpp 中getRealOffset参数 <br>这里的原理和上一项目是一样的，只不过作手脚的地方改了。

```cpp
MSHookFunction((void *) getRealOffset(0x36A2800), // x86:0x36A2800 arm:0x395ADF0
                   (void *) HGSDK_HGSDK_PingManager__FirstPing_c__AnonStorey1____m__0,
                   (void **) &old_HGSDK_HGSDK_PingManager__FirstPing_c__AnonStorey1____m__0);
MSHookFunction((void *) getRealOffset(0x36A2326),  // x86:0x36A2326 arm:0x395A814
                   (void *) HGSDK_HGSDK_PingManager____DoPeriodicPing_m__0,
                   (void **) &old_HGSDK_HGSDK_PingManager____DoPeriodicPing_m__0);
```
```cpp
void *HGSDK_HGSDK_PingManager____DoPeriodicPing_m__0(void *_this, void *response){
                   unsigned char *p =(unsigned char *)response;
                   *(int *)(p+0x8)=0;
                   *(int *)(p+0xC)=5400; //抓包后发现一直无意义的ping，这里改一下ping间隙。
                   return old_HGSDK_HGSDK_PingManager____DoPeriodicPing_m__0(_this,response);
}
```
```cpp
void *HGSDK_HGSDK_PingManager__FirstPing_c__AnonStorey1____m__0(void *_this, void *response){
                   unsigned char *p =(unsigned char *)response;
                   *(int *)(p+0x8)=0;
                   *(int *)(p+0xC)=5400; //抓包后发现一直无意义的ping，这里改一下ping间隙。
                   return old_HGSDK_HGSDK_PingManager__FirstPing_c__AnonStorey1____m__0(_this,response);
}
```

- 保存 hook.cpp

### 编译：

- 解压 Android-Hooking-Template 和 android-ndk-r16b
- 修改 Android-Hooking-Template 下 compile.bat 的第一行，“ndk-build”前修改为解压后android-ndk-r16b的目录
- 将刚才保存的 hook.cpp 和 hook.h 复制到 Android-Hooking-Template 下的 jni 文件夹中
- 运行 Android-Hooking-Template 下的 compile.bat  并等待编译
- 打开 APK Easy Tool 在 APK/Decompiled folder 右第一个按钮下选择ArkN最新安装包
- 点击下方的 Decompile ，之后同目录下会生成一些文件夹(1-Decompiled APKs)。
- 为了避免于原版冲突，修改以下文件<br>AndroidManifest.xml 第一行 package="com.hypergryph.arknights" 改为自己喜欢的名字(全小写字母)<br>res\values-zh\strings.xml 中 `<string name="app_name">明  %日   %方%   舟</string>`改为自己喜欢的名字
- 将刚刚生成的 Android-Hooking-master\libs 中的 libhook.so 复制到1-Decompiled APKs 对应的lib文件夹下去(这里要区分armeabi-v7a和x86框架) 或许你在两种模拟器中都重复上面操作一次~~（我全都要~~，将对应的 libhook.so 复制到 lib 文件夹

- 在反编译文件夹中 smali\com 下新建一个文件夹，名为 loadLib ，将刚刚生成的 Android-Hooking-master\Smali Files 中的 smali 文件复制到 smali\com\loadLib 中
- 打开反编译文件夹中 smali\com\unity3d\player\UnityPlayerActivity ，ctrl+f 找到 onCreate 并加入一句 `invoke-static {}, Lcom/loadLib/libLoader;->loadLib()V` ，之后保存

```
.method protected onCreate(Landroid/os/Bundle;)V

        .locals 1

        invoke-static {}, Lcom/loadLib/libLoader;->loadLib()V

        const/4 v0, 0x1

        invoke-virtual {p0, v0}, Lcom/unity3d/player/UnityPlayerActivity;->requestWindowFeature(I)Z

        ........
```
- 再次打开 APK Easy Tool 在 APK/Decompiled folder 右第二个按钮下选择1-Decompiled APKs(反编译文件夹)
- 点击下方Compile，完成。
