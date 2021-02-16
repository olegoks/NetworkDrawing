#pragma once

#include <algorithm>
#include "Form.hpp"

using Color = Pixel;

EXPIMP class Canvas final : protected Form{

private:

	Pixel* buffer_;
	int width_;
	int height_;
	int pixels_number_;

public:

	EXPIMP explicit Canvas(const HINSTANCE hInstance, const int width, const int height, const Color& color = Color{ 255, 255, 255 })noexcept(true) :
		Form::Form{ hInstance },
		buffer_{ nullptr },
		width_{ width },
		height_{ height },
		pixels_number_{ width_ * height_ }{

		Form::Size(width, height);

		try {
		
			buffer_ = new Pixel[pixels_number_];

			std::for_each(buffer_, buffer_ + pixels_number_, [&color](Pixel& pixel)noexcept->void {

				pixel = color;

				});
		
		} catch (const std::bad_alloc&) {  }

	}

	EXPIMP void SetPixel(int x, int y, const Pixel& pixel)noexcept(false) {

		if (buffer_ == nullptr) throw FormExcep{ u8"Bad allocation exception." };

		int index = y * width_ + x;

		if (index > 0 && index < pixels_number_) {

			buffer_[index] = pixel;
			ShowFrame(buffer_, pixels_number_);

		}

	}

	EXPIMP void Create(const HWND parent_hWnd)noexcept(false) {

		Form::Style(WS_EX_DLGMODALFRAME, WS_CHILD | WS_BORDER);
		Form::Create(L"Canvas", parent_hWnd);

	}

	EXPIMP void Show(int nCmdShow)noexcept(false) {

		Form::Show(SW_SHOW);
			
	}

	EXPIMP void InitCanvasProc(FormProc process_canvas)noexcept(true) {

		Form::InitFormProc(process_canvas);

	}

};