@echo off
echo java Environment
set GRADLE_HOME="D:\git\lpw_java\gradle-2.5"
set JAVA_HOME="D:\git\lpw_java\jdk1.8.0_74"
set ANDROID_HOME=F:\Android\android-sdk\build-tools\23.0.3;F:\Android\android-sdk\platform-tools;F:\Android\android-sdk\tools
echo git environment is %GRADLE_HOME%
SET PATH=%GRADLE_HOME%\bin;%ANDROID_HOME%;%PATH%