// 简化演示版 - 用于测试沉浸式快速翻阅概念
// 可以直接用g++编译: g++ simple_demo.cpp -o simple_demo -lmingw32

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

// 简化的页面结构
struct SimplePage {
    int number;
    std::string chapter;
    std::string content;
};

class SimpleReader {
private:
    std::vector<SimplePage> pages;
    int currentPage = 0;
    int totalPages = 100;
    bool isDragging = false;
    int mouseStartX = 0;
    double previewOffset = 0;
    
public:
    SimpleReader() {
        // 创建测试页面
        for (int i = 0; i < totalPages; i++) {
            pages.push_back({
                i,
                "Chapter " + std::to_string(i / 10 + 1),
                "这是第" + std::to_string(i + 1) + "页的内容示例。这是为了演示快速翻阅功能的测试文本。"
            });
        }
    }
    
    void printPage(int page) {
        if (page >= 0 && page < totalPages) {
            system("cls");  // 清屏
            std::cout << "═══════════════════════════════════════\n";
            std::cout << "📖 PaperFlip - 快速翻阅演示\n";
            std::cout << "═══════════════════════════════════════\n";
            std::cout << "章节: " << pages[page].chapter << "\n";
            std::cout << "页码: " << (page + 1) << "/" << totalPages << "\n";
            std::cout << "---------------------------------------\n";
            std::cout << pages[page].content << "\n";
            std::cout << "═══════════════════════════════════════\n";
            std::cout << "操作: [鼠标左键拖拽=快速翻阅] [ESC=退出]\n";
        }
    }
    
    void printPreview(int centerPage) {
        std::cout << "\n┌─快速预览─";
        for (int i = -2; i <= 2; i++) {
            int page = centerPage + i;
            if (page >= 0 && page < totalPages) {
                if (i == 0) {
                    std::cout << "[" << (page + 1) << "]";
                } else {
                    std::cout << " " << (page + 1) << " ";
                }
            }
        }
        std::cout << "─┐\n";
    }
    
    void runDemo() {
        printPage(currentPage);
        
        std::cout << "🖱️ 开始快速翻阅演示...\n";
        std::cout << "请输入页码(1-100)或0退出: ";
        
        while (true) {
            int target;
            std::cin >> target;
            
            if (target == 0) break;
            if (target < 1 || target > totalPages) {
                std::cout << "请输入1-100之间的页码\n";
                continue;
            }
            
            // 模拟快速翻阅动画
            int start = currentPage;
            int end = target - 1;
            
            std::cout << "🚀 快速翻阅中...\n";
            
            for (double t = 0; t <= 1.0; t += 0.1) {
                int current = start + (int)((end - start) * t);
                
                // 显示预览
                system("cls");
                std::cout << "🔄 正在翻阅... " << (int)(t * 100) << "%\n";
                printPreview(current);
                std::cout << "章节: " << pages[current].chapter << "\n";
                
                Sleep(50);  // Windows延时
            }
            
            currentPage = end;
            printPage(currentPage);
        }
        
        std::cout << "感谢体验PaperFlip!\n";
    }
};

int main() {
    SetConsoleOutputCP(65001);  // 设置UTF-8输出
    
    std::cout << "📚 PaperFlip 快速翻阅演示\n";
    std::cout << "一个模拟纸质书快速翻阅体验的PC端电子阅读器\n\n";
    
    SimpleReader reader;
    reader.runDemo();
    
    return 0;
}