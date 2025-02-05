#pragma once
#include <cliext/vector>
#include <random>
#include <ctime>
#include "ITetrisView.h"
namespace Tetris {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class TetrisModel : public System::Windows::Forms::Form {

	public:
		const static int width = 15;
		const static int height = 25;
		const static int k = 15;
		array<int, 2>^ shape = gcnew array<int, 2>(2, 4);
		array<int, 2>^ field = gcnew array<int, 2>(width, height);
		Bitmap^ bitfield = gcnew Bitmap(k * (width + 1) + 1, k * (height + 3) + 1);
		Graphics^ gr;
		PictureBox^ pictureBox1;
		System::Windows::Forms::Timer^ timer1;
		ITetrisView^ view;

	private: System::ComponentModel::IContainer^ components;

	public:
		TetrisModel()
		{
			InitializeComponent();

			gr = Graphics::FromImage(bitfield);

			//
			// Заполнение границ поля
			for (int i = 0; i < width; i++)
				field[i, height - 1] = 1;
			for (int i = 0; i < height; i++) {
				field[0, i] = 1;
				field[width - 1, i] = 1;
			}
		}
	protected:
		~TetrisModel() {
			if (components) {
				delete components;
			}
		}
#pragma region Windows Form Designer generated code

		void InitializeComponent()
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();

		}

	};
}