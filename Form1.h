#pragma once
#include "Header.h"

namespace CppCLRWinformsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			this->pictureBox1->Image = Image::FromFile("board.jpg");
			this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
			this->board = new ChessBoard();
			//func1();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: ChessBoard* board;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;

	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->button1->Location = System::Drawing::Point(589, 435);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(96, 59);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Start program";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"LDFS", L"BFS", L"IDS" });
			this->comboBox1->Location = System::Drawing::Point(568, 260);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(140, 21);
			this->comboBox1->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Location = System::Drawing::Point(10, 10);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(512, 512);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(586, 235);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(99, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Choose the method";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->label2->Location = System::Drawing::Point(537, 46);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(189, 25);
			this->label2->TabIndex = 4;
			this->label2->Text = L"QUEENS PUZZLE";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(740, 535);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"Form1";
			this->Text = L"Queens Puzzle";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void pictureBoxRemove(System::Object^ sender, System::EventArgs^ e)
	{
		delete sender;
		System::Drawing::Point pos = this->PointToClient(Cursor->Position);
		this->board->removeQueen(pos.Y / 64, pos.X / 64);
	}

	private: System::Void createPictureQueen(int x, int y, int num)
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

	private: System::Void displayResult(ChessBoard* board)
	{
		this->pictureBox1->Controls->Clear();
		std::vector<std::vector<int>> queenPos = board->getQueenPos();
		for(int i = 0; i < queenPos.size(); i++)
		{
			createPictureQueen(queenPos[i][1], queenPos[i][0], i);
		}

	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if(this->board->queenFirstCheck())
		{
			int choice = this->comboBox1->SelectedIndex;		
			ChessBoard* result = this->board;
			switch (choice)
			{
			case 1:
				result = BFS(this->board);
				displayResult(result);
				MessageBox::Show("The task is solved!", "Completed!");
				break;
			case 2:
				result = IDS(new ChessBoard(this->board), 100);
				if (result != NULL)
				{
					displayResult(result);
					MessageBox::Show("The task is solved!", "Completed!");
				}
				else
					MessageBox::Show("The method cannot solve the task!", "Error!"); 
				break;
			default:
				MessageBox::Show("Method is not selected!", "Error!");
			}
			if (result != NULL && result != board)
			{
				delete this->board;
				this->board = result;
			}
		}
		else
			MessageBox::Show("Wrong placement!", "Error!");
		
	}

private: System::Void pictureBox1_LoadCompleted(System::Object^ sender, System::ComponentModel::AsyncCompletedEventArgs^ e) {
	this->pictureBox1->Image = Image::FromFile("board.jpg");
}
private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Drawing::Point pos = this->PointToClient(Cursor->Position); //pos.PointToClient()
	//pos.X; pos.Y;
	createPictureQueen((pos.X)/64, (pos.Y)/64, 0);
	this->board->insertQueen(pos.Y / 64, pos.X / 64);
	displayResult(board);
}

};
}
