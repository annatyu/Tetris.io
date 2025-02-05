//#pragma once
//#include "Tetris_model.h"
//#include "Tetris_interface.h"

//namespace Tetris {
//	using namespace System;
//	using namespace System::Windows::Forms;
//
//	ref class TetrisController {
//	private:
//		TetrisModel^ model;
//		IInterface^ view;
//		System::Windows::Forms::Timer^ timer;
//
//	public:
//		TetrisController(IInterface^ viewInstance) {
//			model = gcnew TetrisModel();
//			view = viewInstance;
//			timer = gcnew System::Windows::Forms::Timer();
//			timer->Interval = 300;
//			timer->Tick += gcnew EventHandler(this, &TetrisController::TimerTick);
//			timer->Start();
//		}
//
//		void KeyPressed(Object^ sender, KeyEventArgs^ e) {
//			switch (e->KeyCode) {
//			case Keys::A: model->MoveLeft();
//				break;
//			case Keys::D: model->MoveRight();
//				break;
//			case Keys::W: model->Rotate();
//				break;
//			}
//			view->UpdateView();
//		}
//
//		void TimerTick(Object^ sender, EventArgs^ e) {
//			model->Update();
//			view->UpdateView();
//		}
//	};
//}
//
