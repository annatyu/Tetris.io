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
		Bitmap^ bitfield = gcnew Bitmap(k * (width + 1) + 1, k * (height + 3) + 1);
		Graphics^ gr;
		PictureBox^ pictureBox1;
		System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	public:


		WinForm()
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
			SetShape();
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
		void InitializeComponent()
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(10, 10);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(301, 462);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 300;
			this->timer1->Tick += gcnew System::EventHandler(this, &WinForm::timer1_Tick);
			// 
			// WinForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(340, 513);
			this->Controls->Add(this->pictureBox1);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"WinForm";
			this->Text = L"Tetris";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}

		void FillField() {
			gr->Clear(Color::Black);//Очищает поле

			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {//Проходится по всему полю
					if (field[i, j] == 1) {//если элемент поля занят
						gr->FillRectangle(Brushes::Green, i * k, j * k, k, k);//то закрашиваем зеленым
						gr->DrawRectangle(Pens::Black, i * k, j * k, k, k);//рисуем контур
					}
				}
			}

			//for (int i = 0; i < 4; i++) {//для новой фигуры
			//	gr->FillRectangle(Brushes::Red, shape[1, i] * k, shape[0, i] * k, k, k);//закрашиваем красным
			//	gr->DrawRectangle(Pens::Black, shape[1, i] * k, shape[0, i] * k, k, k);//рисуем её контур
			//}

			pictureBox1->Image = bitfield;//Устанавливает изображение в поле
		}
		void FillShape() {
			for (int i = 0; i < 4; i++) {//для новой фигуры
				gr->FillRectangle(Brushes::Red, shape[1, i] * k, shape[0, i] * k, k, k);//закрашиваем красным
				gr->DrawRectangle(Pens::Black, shape[1, i] * k, shape[0, i] * k, k, k);//рисуем её контур
			}

			pictureBox1->Image = bitfield;//Устанавливает изображение в поле
		}

		void PutDownShape() {
			for (int i = 0; i < 4; i++)
				shape[0, i]++;//каждый элемент фигуры опускаем вниз
		}

		System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
			if (field[8, 3] == 1) {//если при создании новой фигуры элемент поля уже занят, то игра заканчивается
				Application::Exit();
			}

			PutDownShape();

			for (int i = height - 2; i > 2; i--) {//проходимся по строкам
				int cross = 0;
				for (int j = 0; j < width; j++) {//проходимся по столбцам
					if (field[j, i] == 1)//если элемент в строке занят
						cross++;//то прибавляем к счетчику 1
				}
				if (cross == width) {//если вся строка занята
					for (int k = i; k > 1; k--) {//проходимя по всем столбцам где полностью они заняты
						for (int l = 1; l < width - 1; l++) {//проходимся по всей строке
							field[l, k] = field[l, k - 1];//теперь присваеваем полностью заполненой строке верхнюю строку
						}
					}
				}
			}

			FillField();//обновляет поле
			FillShape();
		}
		void SetShape() {
			Random^ rand = gcnew Random(static_cast<int>(DateTime::Now.Millisecond));
			int type = rand->Next(0);
			switch (type) {
				{ case 0: shape = gcnew array<int, 2>{{2, 3, 4, 5}, { 8,8,8,8 }}; break;  }
			}
		}
		bool FindMistake() {
			for (int i = 0; i < 4; i++) {// проходимся по всем элементам фигуры
				if (shape[1, i] >= width || shape[0, i] >= height ||//если элемент вышел за границы поля
					shape[1, i] <= 0 || shape[0, i] <= 0 ||
					field[shape[1, i], shape[0, i]] == 1)//если поле уже заполнено
					return true;//то это ошибка
			}
			return false;
		}
	};
};

