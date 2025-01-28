# Hazel
Hazel Engine Learning following Cherno

# Build

1. `git clone --recursive git@github.com:xieyouchen/Hazel.git` 

2. 修改 \Hazel\vendor\imgui\imgui.cpp 文件中 3839 行代码为 

   ```c++
       if (window) {
           for (int i = 0; i < window->DC.Layouts.Data.Size; i++)
           {
               ImGuiLayout* layout = (ImGuiLayout*)window->DC.Layouts.Data[i].val_p;
               IM_DELETE(layout);
           }
       }
   ```

3. 添加指令到 \Hazel\vendor\imgui\premake.lua 文件(比如在24行)中

   ```lua
   defines 
	{
        "IMGUI_API=__declspec(dllexport)"
	}
   ```

4. 点击根目录下的 GenerateProject.bat 生成 .sln 工程文件



# 修改项目操作

1. 修改完代码后保存文件
2. 到工程文件根目录，双击 GenerateProject.bat 脚本
3. 进入到 VS，会弹窗口，直接全部重新加载
4. 按 F5 即可正常运行

