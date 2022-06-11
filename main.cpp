// файл за замовчуванням
#include "pch.h"
#include "Form1.h"

using namespace System::Windows::Forms;

[System::STAThread]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CppCLRWinformsProject::Form1()); 
	return 0;
}