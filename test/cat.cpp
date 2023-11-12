#include <iostream>
#include <fstream>
#include <string>

int main()
{
    // 打开文件
    std::ifstream inputFile("1.docx");

    // 检查文件是否成功打开
    if (!inputFile.is_open())
    {
        std::cerr << "无法打开文件" << std::endl;
        return 1; // 返回错误码
    }

    // 逐行读取文件内容并输出到控制台
    std::string line;
    while (std::getline(inputFile, line))
    {
        std::cout << line << std::endl;
    }

    // 关闭文件
    inputFile.close();

    return 0; // 返回成功码
}
