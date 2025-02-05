#pragma once
#include "ITetrisView.h"
#include "Tetris_model.h"

namespace Tetris {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	public ref class TetrisView : public ITetrisView {
	private:
		TetrisModel^ model;
		Bitmap^ bitfield;
		Graphics^ gr;
		PictureBox^ pictureBox1;
	public:
		TetrisView(TetrisModel^ model, System::Windows::Forms::PictureBox^ pictureBox) {
			this->model = model;
			this->pictureBox1 = pictureBox1;
			Bitmap^ bitfield = gcnew Bitmap(TetrisModel::k * (TetrisModel::width + 1) + 1, TetrisModel::k * (TetrisModel::height + 3) + 1);
			gr = Graphics::FromImage(bitfield);
		}
		virtual void FillField() override {
			gr->Clear(Color::Black);
			for (int i = 0; i < TetrisModel::width; i++) {
				for (int j = 0; j < TetrisModel::height; j++) {//Проходится по всему полю
					if (model->field[i, j] == 1) {//если элемент поля занят
						gr->FillRectangle(Brushes::Green, i * TetrisModel::k, j * TetrisModel::k, TetrisModel::k, TetrisModel::k);//то закрашиваем зеленым
						gr->DrawRectangle(Pens::Black, i * TetrisModel::k, j * TetrisModel::k, TetrisModel::k, TetrisModel::k);//рисуем контур
					}
				}
			}

			pictureBox1->Image = bitfield;//Устанавливает изображение в поле
		}
	};
}
