#pragma once

#include <cliext/vector>
#include <random>
#include <ctime>

namespace Tetris {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for WinForm
	/// </summary>
	public ref class WinForm : public System::Windows::Forms::Form
	{
	public:
		const static int width = 15;
		const static int height = 25;
		const static int k = 15;//размер клетки в пикселях
		array<int, 2>^ shape = gcnew array<int, 2>(2, 4);
		array<int, 2>^ field = gcnew array<int, 2>(width, height);
		WinForm(void)
		{
			InitializeComponent();
			//
			// Заполнение границ поля
			for (int i = 0; i < width; i++)
				field[i, height - 1] = 1;
			for (int i = 0; i < height; i++) {
				field[0, i] = 1;
				field[width - 1, i] = 1;
			}

			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~WinForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(28, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(318, 460);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &WinForm::pictureBox1_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &WinForm::timer1_Tick);
			// 
			// WinForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(367, 493);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"WinForm";
			this->Text = L"WinForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
