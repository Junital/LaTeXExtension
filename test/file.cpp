#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// 获取当前时间的字符串表示
string getCurrentTime()
{
    time_t now = time(0);
    struct tm timeinfo;
    char buffer[80];

    localtime_s(&timeinfo, &now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &timeinfo);

    return buffer;
}

// 写入文本到文件
void writeTextToFile(const string &fileName, const string &content)
{
    ofstream file(fileName.c_str());

    if (file.is_open())
    {
        file << content;
        file.close();
    }
    else
    {
        cout << "Unable to open file: " << fileName << endl;
    }
}

// 打开文件
void openFile(const string &fileName)
{
#ifdef _WIN32
    // 使用ShellExecute打开文件，默认关联的程序会打开
    ShellExecuteA(NULL, "open", fileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
#else
    // 在Linux上，你可能需要使用其他方法打开文件，比如使用系统调用
    cout << "Opening file: " << fileName << " - You may need to open it manually." << endl;
#endif
}

int main()
{
    string fileName = "Document_" + getCurrentTime() + ".docx";
    string content = "<math xmlns=\"http://www.w3.org/1998/Math/MathML\" display=\"block\">  <mfrac>    <mi>a</mi>    <mi>b</mi>  </mfrac></math>";

    writeTextToFile(fileName, content);

    cout << "File created: " << fileName << endl;

    openFile(fileName);

    return 0;
}
