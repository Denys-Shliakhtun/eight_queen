#include "pch.h"
#include "Form1.h"
namespace CppCLRWinformsProject {
	System::Void Form1::createPictureQueen(int x, int y, int num)
	{
		System::Windows::Forms::PictureBox^ pictureBox = (gcnew System::Windows::Forms::PictureBox());
		pictureBox->Image = Image::FromFile("queen64.png");
		pictureBox->ClientSize = System::Drawing::Size(64, 64);
		pictureBox->Anchor = System::Windows::Forms::AnchorStyles::None;

		pictureBox->Location = System::Drawing::Point(64 * x, 64 * y);
		pictureBox->Margin = System::Windows::Forms::Padding(0, 0, 0, 0);
		pictureBox->Name = L"pictureBox" + num;
		
		pictureBox->TabIndex = 2;
		pictureBox->TabStop = false;

		pictureBox->BackColor = System::Drawing::Color::Transparent;
		
		this->pictureBox1->Controls->Add(pictureBox);
		//this->pictureBox1->Controls->;
		pictureBox->BringToFront();

		pictureBox->Click += gcnew System::EventHandler(this, &Form1::pictureBoxRemove);

	}
}