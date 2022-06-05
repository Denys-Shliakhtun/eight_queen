#pragma once
#include "methods.h"

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
			queenImage = Image::FromFile("queen64.png");
			boardImage = Image::FromFile("board.jpg");
			this->pictureBox1->Image = boardImage;
			this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
			this->board = new ChessBoard();			
			graphics = pictureBox1->CreateGraphics();
			
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		/// 
		
		//~Form1()
		//{
		//	/*
		//	if (components)
		//	{
		//		delete components;
		//	}
		//	*/
		//}
		
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::ComboBox^ comboBox1;	
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: ChessBoard* board;
	private: PictureBox^ picturebox;
	private: Graphics^ graphics;
	private: Image^ queenImage;
	private: Image^ boardImage;




		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
	//private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			//System::Windows::Forms::GroupBox^ groupBox1;
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
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
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Location = System::Drawing::Point(10, 10);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox1->Name = L"PictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(512, 512);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
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
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->Text = L"Queens Puzzle";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e);

	public:  System::Void displayResult(ChessBoard* board);

	private: System::Void displayResult(ChessBoard* board, ChessBoard* prev);

	private: System::Void displayArrows(ChessBoard* first, ChessBoard* second);

	private: System::Void createPictureQueen(int x, int y, int num);

	private: System::Void deletePictureQueen(System::Object^ sender, System::EventArgs^ e);	
	
	private:  bool stressTest();
	};
}
