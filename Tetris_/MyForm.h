#pragma once

#include <cliext/vector>
#include <random>
#include <ctime>


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Tetris {
    public ref class MyForm : public Form {
    public:
        const static int width = 15;
        const static int height = 25;
        const static int k = 15;//размер клетки в пикселях

        array<int, 2>^ shape = gcnew array<int, 2>(2, 4);
        array<int, 2>^ field = gcnew array<int, 2>(width, height);
        Bitmap^ bitfield = gcnew Bitmap(k * (width + 1) + 1, k * (height + 3) + 1);
        Graphics^ gr;

        PictureBox^ FieldPictureBox;
        Timer^ TickTimer;
        Button^ button1;

        MyForm() {
            InitializeComponent();

            gr = Graphics::FromImage(bitfield);

            // Заполнение границ поля
            for (int i = 0; i < width; i++)
                field[i, height - 1] = 1;
            for (int i = 0; i < height; i++) {
                field[0, i] = 1;
                field[width - 1, i] = 1;
            }

            SetShape();
        }

    private:
        void InitializeComponent() {
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->FieldPictureBox = gcnew PictureBox();

            this->TickTimer = gcnew Timer();

            this->SuspendLayout();
            this->KeyPreview = true;

            this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(20, 425);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Left";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);



            // PictureBox
            this->FieldPictureBox->Location = System::Drawing::Point(10, 10);
            this->FieldPictureBox->Size = System::Drawing::Size(k * (width), k * (height));
            this->FieldPictureBox->TabIndex = 0;
            this->FieldPictureBox->TabStop = false;

            // Timer
            this->TickTimer->Interval = 300;
            this->TickTimer->Tick += gcnew EventHandler(this, &MyForm::TickTimer_Tick);

            // MyForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6.0F, 13.0F);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(k * (width + 2), k * (height + 5));
            this->Controls->Add(this->FieldPictureBox);
            this->Controls->Add(this->button1);
            this->Name = L"MyForm";
            this->Text = L"Little Tetris";
            this->KeyDown += gcnew KeyEventHandler(this, &MyForm::MyForm_KeyDown);

            this->ResumeLayout(false);
            this->Focus();
            // Запуск таймера
            this->TickTimer->Start();
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

            for (int i = 0; i < 4; i++) {//для новой фигуры
                gr->FillRectangle(Brushes::Red, shape[1, i] * k, shape[0, i] * k, k, k);//закрашиваем красным
                gr->DrawRectangle(Pens::Black, shape[1, i] * k, shape[0, i] * k, k, k);//рисуем её контур
            }

            FieldPictureBox->Image = bitfield;//Устанавливает изображение в поле
        }

        void TickTimer_Tick(Object^ sender, EventArgs^ e) {
            if (field[8, 3] == 1) {//если при создании новой фигуры элемент поля уже занят, то игра заканчивается
                Application::Exit();
            }

            for (int i = 0; i < 4; i++)
                shape[0, i]++;//каждый элемент фигуры опускаем вниз

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

            if (FindMistake()) {//если ошибка, то
                for (int i = 0; i < 4; i++)//проходимя по всем элемнтам фигуры
                    field[shape[1, i], --shape[0, i]]++;//поднимаем фигуру наверх и записываем, что еще 1 элемент поля занят
                SetShape();//создаем новую фигуру
            }

            FillField();//обновляет поле
        }
        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
             button1->PerformClick(); // Действие при нажатии кнопки
        }

        System::Void WinForm_KeyDown(System::Object^ sender, KeyEventArgs^ e) {
            if (e->KeyCode == Keys::A) { // Проверяем, нажата ли клавиша "A"
                button1->PerformClick(); // Программно вызываем событие нажатия кнопки
            }
        }
        void MyForm_KeyDown(Object^ sender, KeyEventArgs^ e) {//нажатие клавиш
            switch (e->KeyCode) {
            case Keys::A://если А
                for (int i = 0; i < 4; i++)
                    shape[1, i]--;//то сдвиг влево
                if (FindMistake())//если ошибка
                    for (int i = 0; i < 4; i++)
                        shape[1, i]++;//то вправо
                break;

            case Keys::D://если вправо
                for (int i = 0; i < 4; i++)
                    shape[1, i]++;
                if (FindMistake())
                    for (int i = 0; i < 4; i++)
                        shape[1, i]--;//если ошибка, то влево 
                break;

            case Keys::W://если вверх
                array<int, 2>^ shapeT = gcnew array<int, 2>(2, 4);
                Array::Copy(shape, shapeT, shape->Length);//копируем массив shape в shapeT

                int maxx = 0, maxy = 0;
                for (int i = 0; i < 4; i++) {
                    if (shape[0, i] > maxy)
                        maxy = shape[0, i];//находим максимальный y
                    if (shape[1, i] > maxx)
                        maxx = shape[1, i];//находим максимальный х
                }

                for (int i = 0; i < 4; i++) {
                    int temp = shape[0, i];//текущий элемент складываем в temp
                    shape[0, i] = maxy - (maxx - shape[1, i]) - 1;
                    shape[1, i] = maxx - (3 - (maxy - temp)) + 1;//поворачиваем фигуру
                }

                if (FindMistake())
                    Array::Copy(shapeT, shape, shape->Length);//если ошибка, то не поворачиваем
                break;
            }
        }
        void SetShape() {//создаем новую фигуру
            Random^ rand = gcnew Random(static_cast<int>(DateTime::Now.Millisecond));
            int type = rand->Next(7);//выбираем тип фигуры
            switch (type) {
                { case 0: shape = gcnew array<int, 2> {{2, 3, 4, 5}, { 8, 8, 8, 8 }}; break; }
                { case 1: shape = gcnew array<int, 2> {{2, 3, 2, 3}, { 8, 8, 9, 9 }}; break; }
                { case 2: shape = gcnew array<int, 2> {{2, 3, 4, 4}, { 8, 8, 8, 9 }}; break; }
                { case 3: shape = gcnew array<int, 2> {{2, 3, 4, 4}, { 8, 8, 8, 7 }}; break; }
                { case 4: shape = gcnew array<int, 2> {{3, 3, 4, 4}, { 7, 8, 8, 9 }}; break; }
                { case 5: shape = gcnew array<int, 2> {{3, 3, 4, 4}, { 9, 8, 8, 7 }}; break; }
                { case 6: shape = gcnew array<int, 2> {{3, 4, 4, 4}, { 8, 7, 8, 9 }}; break; }
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
}
