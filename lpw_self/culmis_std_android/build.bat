@echo off
echo vs7 Environment
set ndk=F:\android-ndk-r10d
set android_sdk=F:\Android\android-sdk\build-tools\23.0.3;F:\Android\android-sdk\platform-tools;F:\Android\android-sdk\tools
echo ndk environment is %ndk%
SET PATH=%ndk%;%android_sdk%;%PATH%
aapt package -f -m -J ./gen -S res -M AndroidManifest.xml -j D:\git\lpw_c\lpw_self\culmis_std_android\jar\android-support-v71-appcompat.jar -j D:\git\lpw_c\lpw_self\culmis_std_android\jar\android-support-v41.jar -I F:\Android\android-sdk\platforms\android-17\android.jar 
ndk-build
pause