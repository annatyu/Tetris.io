#pragma once

#include <vector>
#include <ctime>

namespace Tetris {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// Размеры игрового поля
	const int FIELD_WIDTH = 10;
	const int FIELD_HEIGHT = 15;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			InitializeGame();
			this->DoubleBuffered = true;
			this->KeyDown += gcnew KeyEventHandler(this, &MyForm::OnKeyDown);
			Application::Idle += gcnew EventHandler(this, &MyForm::GameLoop);
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:

		cli::array<cli::array<int>^>^ gameField;
		cli::array<cli::array<int>^>^ tetrominoes;
		Point currentPiecePos;
		int currentPiece;
		int currentRotation;
		bool gameOver;
		DateTime lastMoveTime;
		int score;
		bool gameStarted;
		int moveDelay;


	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ btn_main;
	private: System::Windows::Forms::Label^ label2;

		  

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btn_main = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Ravie", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->label1->Location = System::Drawing::Point(341, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(129, 40);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Score";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// btn_main
			// 
			this->btn_main->Font = (gcnew System::Drawing::Font(L"Matura MT Script Capitals", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_main->Location = System::Drawing::Point(187, 227);
			this->btn_main->Name = L"btn_main";
			this->btn_main->Size = System::Drawing::Size(114, 60);
			this->btn_main->TabIndex = 1;
			this->btn_main->Text = L"Start";
			this->btn_main->UseVisualStyleBackColor = true;
			this->btn_main->Click += gcnew System::EventHandler(this, &MyForm::btn_main_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label2->Location = System::Drawing::Point(374, 62);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(64, 25);
			this->label2->TabIndex = 2;
			this->label2->Text = L"label2";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(482, 553);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->btn_main);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"Tetris";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void InitializeGame()
		{
			// Инициализация игрового поля
			gameField = gcnew cli::array<cli::array<int>^>(FIELD_HEIGHT);
			for (int y = 0; y < FIELD_HEIGHT; y++)
			{
				gameField[y] = gcnew cli::array<int>(FIELD_WIDTH);
				for (int x = 0; x < FIELD_WIDTH; x++)
				{
					gameField[y][x] = 0;
				}
			}

			// Инициализация фигур Тетриса
			tetrominoes = gcnew cli::array<cli::array<int>^>(7) {
				gcnew cli::array<int>{0x0F00, 0x2222, 0x00F0, 0x4444},
					gcnew cli::array<int>{0x44C0, 0x8E00, 0x6440, 0x0E20},
					gcnew cli::array<int>{0x4460, 0x0E80, 0xC440, 0x2E00},
					gcnew cli::array<int>{0x44C0, 0x8E00, 0x6440, 0x0E20},
					gcnew cli::array<int>{0x4E00, 0x8C40, 0x4E00, 0x8C40},
					gcnew cli::array<int>{0x8E00, 0x44C0, 0xE800, 0xC440},
					gcnew cli::array<int>{0xCC00, 0xCC00, 0xCC00, 0xCC00}
			};

			currentPiece = 0;
			currentRotation = 0;
			currentPiecePos = Point(FIELD_WIDTH / 2 - 2, 0);
			gameOver = false;
			moveDelay = 500; // миллисекунд
			lastMoveTime = DateTime::Now;
		}

		void StartGame() {
			// Логика для инициализации игры
			gameStarted = true;
			InitializeGame(); // Если у вас есть метод для инициализации игрового состояния
			Application::Idle += gcnew EventHandler(this, &MyForm::GameLoop); // Запуск игрового цикла
		}

		void GameLoop(Object^ sender, EventArgs^ e)
		{
			DateTime now = DateTime::Now;
			if ((now - lastMoveTime).TotalMilliseconds > moveDelay)
			{
				UpdateGame();
				this->Invalidate();
				lastMoveTime = now;
			}
		}

		void UpdateGame()
		{
			if (!gameOver)
			{
				// Опускаем текущую фигуру вниз
				currentPiecePos.Y++;

				// Проверяем столкновение
				if (CheckCollision())
				{
					currentPiecePos.Y--;
					PlacePiece();
					ClearLines();
					SpawnNewPiece();
				}
			}
			else
			{
				// Логика завершения игры
				MessageBox::Show(L"Game Over", L"Tetris", MessageBoxButtons::OK, MessageBoxIcon::Information);
				InitializeGame();
			}
		}

		bool CheckCollision()
		{
			// Проверка столкновений текущей фигуры с границами или другими фигурами
			for (int py = 0; py < 4; py++)
			{
				for (int px = 0; px < 4; px++)
				{
					if ((tetrominoes[currentPiece][currentRotation] & (0x8000 >> (py * 4 + px))) != 0)
					{
						int x = currentPiecePos.X + px;
						int y = currentPiecePos.Y + py;

						if (x < 0 || x >= FIELD_WIDTH || y >= FIELD_HEIGHT || (y >= 0 && gameField[y][x] != 0))
							return true;
					}
				}
			}
			return false;
		}

		void PlacePiece()
		{
			// Помещаем текущую фигуру на игровое поле
			for (int py = 0; py < 4; py++)
			{
				for (int px = 0; px < 4; px++)
				{
					if ((tetrominoes[currentPiece][currentRotation] & (0x8000 >> (py * 4 + px))) != 0)
					{
						int x = currentPiecePos.X + px;
						int y = currentPiecePos.Y + py;
						if (y >= 0)
							gameField[y][x] = currentPiece + 1;
					}
				}
			}
		}

		void ClearLines()
		{
			int Score = 0;
			// Удаление заполненных линий
			for (int y = 0; y < FIELD_HEIGHT; y++)
			{
				bool lineFull = true;
				Score += 100;
				for (int x = 0; x < FIELD_WIDTH; x++)
				{
					if (gameField[y][x] == 0)
					{
						lineFull = false;
						break;
					}
				}
				if (lineFull)
				{
					for (int ny = y; ny > 0; ny--)
						for (int nx = 0; nx < FIELD_WIDTH; nx++)
							gameField[ny][nx] = gameField[ny - 1][nx];
					for (int nx = 0; nx < FIELD_WIDTH; nx++)
						gameField[0][nx] = 0;
				}
			}
		}

		void SpawnNewPiece()
		{
			// Создаем новую фигуру
			currentPiece = rand() % 7;
			currentRotation = 0;
			currentPiecePos = Point(FIELD_WIDTH / 2 - 2, 0);

			// Если новая фигура сразу сталкивается, игра окончена
			if (CheckCollision())
			{
				gameOver = true;
			}
		}

	protected:
		virtual void OnPaint(PaintEventArgs^ e) override
		{
			Graphics^ g = e->Graphics;

			// Рисуем игровое поле
			for (int y = 0; y < FIELD_HEIGHT; y++)
			{
				for (int x = 0; x < FIELD_WIDTH; x++)
				{
					if (gameField[y][x] != 0)
					{
						g->FillRectangle(Brushes::Blue, x * 30, y * 30, 30, 30);
						g->DrawRectangle(Pens::Black, x * 30, y * 30, 30, 30);
					}
				}
			}

			// Рисуем текущую фигуру
			for (int py = 0; py < 4; py++)
			{
				for (int px = 0; px < 4; px++)
				{
					if ((tetrominoes[currentPiece][currentRotation] & (0x8000 >> (py * 4 + px))) != 0)
					{
						int x = currentPiecePos.X + px;
						int y = currentPiecePos.Y + py;
						if (y >= 0)
						{
							g->FillRectangle(Brushes::Red, x * 30, y * 30, 30, 30);
							g->DrawRectangle(Pens::Black, x * 30, y * 30, 30, 30);
						}
					}
				}
			}
		}

		void OnKeyDown(Object^ sender, KeyEventArgs^ e)
		{
			if (gameOver)
				return;

			switch (e->KeyCode)
			{
			case Keys::Left:
				currentPiecePos.X--;
				if (CheckCollision())
					currentPiecePos.X++;
				break;
			case Keys::Right:
				currentPiecePos.X++;
				if (CheckCollision())
					currentPiecePos.X--;
				break;
			case Keys::Down:
				currentPiecePos.Y++;
				if (CheckCollision())
					currentPiecePos.Y--;
				break;
			case Keys::Up:
				currentRotation = (currentRotation + 1) % 4;
				if (CheckCollision())
					currentRotation = (currentRotation + 3) % 4; // отмена вращения
				break;
			}

			this->Invalidate();
		}

private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void btn_main_Click(System::Object^ sender, System::EventArgs^ e) {
	this->label2->Text = "Score_result";
	this->btn_main->Visible = false;
	StartGame();
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}

