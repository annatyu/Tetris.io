#pragma once
namespace Tetris{
	public interface class ITetrisView {
	public:
		virtual void FillField() = 0;
		virtual void FillShape() = 0;
	};
}

