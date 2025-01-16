//#include "MyForm.h"
#include "TetrisMainForm.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

void Main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Tetris::WinForm form;
	Application::Run(% form);
}