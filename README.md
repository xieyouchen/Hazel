# Hazel
Hazel Engine Learning following Cherno

# Build

1. `git clone --recursive git@github.com:xieyouchen/Hazel.git` 

2. 创建 vendor\premake

3. 保存 [premake 的 LICENSE.txt](https://github.com/premake/premake-core/blob/master/LICENSE.txt)

4. 下载 [premake-core 的 win 版本](https://github.com/premake/premake-core/releases)

5. 最后有目录

   vendor\premake\LICENSE.txt

   vendor\premake\premake.exe

6. 点击根目录下的 GenerateProject.bat 生成 .sln 工程文件



# 修改项目操作

1. 修改完代码后保存文件
2. 到工程文件根目录，双击 GenerateProject.bat 脚本
3. 进入到 VS，会弹窗口，直接全部重新加载
4. 按 F5 即可正常运行