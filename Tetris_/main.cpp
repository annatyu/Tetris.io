//#include "MyForm.h"
#include "Tetris_model.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

void Main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Tetris::TetrisModel form;
	Application::Run(% form);
}