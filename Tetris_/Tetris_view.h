//#pragma once
//#include "Tetris_controller.h"
//#include "Tetris_interface.h"

//namespace Tetris {
	/*using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class TetrisView :public Form, public IInterface {
	private:
		TetrisController^ controller;
		PictureBox^ puctureBox;
		Bitmap^ bitmap;
		Graphics^ graphics;
	public:
		TetrisView() {
			controller = gcnew TetrisController(this);
			pictureBox = gcnew PictureBox();
			bitmap = gcnew Bitmap(300, 500);
			graphics = Graphics::FromImage(bitmap);
			this->Controls->Add(pictureBox);
			this->KeyDown += gcnew KeyEventHandler(this, &TetrisView::OnKeyDown);
		}

		virtual void UpdateView() override {
			graphics->Clear(Color::Black);

		}
	};

}*/
