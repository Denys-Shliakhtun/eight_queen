#include "pch.h"
#include "Form1.h"
namespace CppCLRWinformsProject {
	System::Void Form1::deletePictureQueen(System::Object^ sender, System::EventArgs^ e)
	{
		System::Drawing::Point pos = this->PointToClient(Cursor->Position);
		this->board->removeQueen((pos.Y - 10) / 64, (pos.X - 10) / 64);
		displayResult(this->board);
	}
	
	System::Void Form1::createPictureQueen(int x, int y, int num)
	{
		System::Windows::Forms::PictureBox^ pictureBox = (gcnew System::Windows::Forms::PictureBox());
		pictureBox->Image = this->queenImage;
		pictureBox->ClientSize = System::Drawing::Size(64, 64);
		pictureBox->Anchor = System::Windows::Forms::AnchorStyles::None;
		pictureBox->Location = System::Drawing::Point(64 * x, 64 * y);
		pictureBox->Margin = System::Windows::Forms::Padding(0, 0, 0, 0);
		pictureBox->Name = L"pictureBox" + num;		
		pictureBox->TabStop = false;
		pictureBox->BackColor = System::Drawing::Color::Transparent;
		
		this->pictureBox1->Controls->Add(pictureBox);
		pictureBox->BringToFront();
		pictureBox->Click += gcnew System::EventHandler(this, &Form1::deletePictureQueen);
	}

	System::Void Form1::displayResult(ChessBoard* board)
	{
		if (graphics)
			this->Invalidate();

		std::vector<std::vector<int>> queenPos = board->getQueenPos();

		int i = 0;
		while (this->pictureBox1->Controls->ContainsKey((L"pictureBox" + i)))
		{
			Control^ ctrl = this->pictureBox1->Controls->Find(L"pictureBox" + i, false)[0];
			delete ctrl;
			this->pictureBox1->Controls->RemoveByKey((L"pictureBox" + i));			
			i++;
		}

		for (int i = 0; i < queenPos.size(); i++)
			createPictureQueen(queenPos[i][1], queenPos[i][0], i);
		
		this->pictureBox1->Refresh();
	}

	System::Void Form1::displayResult(ChessBoard* board, ChessBoard* prev)
	{
		displayResult(board);
		displayArrows(prev, board);
	}

	System::Void Form1::button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		//if (stressTest())
		//	MessageBox::Show("Stress test is completed!", "Completed!");
		if (this->board->queenFirstCheck())
		{
			std::ofstream fileOutput("output.txt");
			fileOutput << "Input:\n";
			this->board->fileOutput(fileOutput);
			if (!this->board->queenCheck())
			{
				MessageBox::Show("The position of figures is right. No method is applied!", "Completed!");
				fileOutput << "\nThe position of figures is right. No method is applied!";
				fileOutput.close();
				return;
			}
			int choice = this->comboBox1->SelectedIndex;
			ChessBoard* result = NULL;
			switch (choice)
			{
			case 0:
				result = LDFS(this->board);
				if (result == NULL)
					MessageBox::Show("The method cannot solve the task! The stack is overflowed!", "Error!");
				else
					fileOutput << "\nLDFS method:\n";
				break;
			case 1:
				result = BFS(this->board);
				fileOutput << "\nBFS method:\n";
				break;
			case 2:
				result = IDS(new ChessBoard(this->board), 100);
				if (result == NULL)
					MessageBox::Show("The method cannot solve the task! The depth is not enough!", "Error!");
				else
					fileOutput << "\nIDS method:\n";
				break;
			default:
				MessageBox::Show("Method is not selected!", "Error!");
				fileOutput << "\nError! No method was selected!";
			}

			if (result != NULL)
			{

				displayResult(result, this->board);
				MessageBox::Show("The task is solved!", "Completed!");
				result->fileOutput(fileOutput);

				delete this->board;
				this->board = result;
			}
			fileOutput.close();
		}
		else
			MessageBox::Show("Wrong placement!", "Error!");

	}


	bool Form1::stressTest()
	{
		bool flag;
		ChessBoard* temp, * temp2;
		int k, l, d1, d2;
		for (int i = 11111111; i < 88888888; i++)
		{
			flag = true;
			k = 10000000;
			while (k > 1 && flag)
			{
				d1 = i % (k * 10) / k;
				l = k / 10;
				while (l > 0 && flag)
				{
					d2 = i % (l * 10) / l;
					if (d1 == d2 || (d1 > 8 || d1 < 1) || (d2 > 8 || d2 < 1))
					{
						flag = false;
					}
					l /= 10;
				}
				k /= 10;
			}
			if (flag)
			{
				temp = new ChessBoard();
				for (int j = 0; j < 8; j++)
				{
					temp->insertQueen(i % (int)pow(10, j + 1) / (int)pow(10, j) - 1, j);
				}
				temp2 = BFS(temp);
				if (temp2 == NULL || temp2->queenCheck())
					return false;
				displayResult(temp2);
				delete board;
				board = new ChessBoard(temp2);
				delete temp, temp2;
			}
		}
		return true;
	}

	System::Void Form1::displayArrows(ChessBoard* first, ChessBoard* second) 
	{
		std::vector<std::vector<int>> posFirst = first->getQueenPos();
		std::vector<std::vector<int>> posSecond = second->getQueenPos();

		Point a, b;
		Pen^ p = gcnew Pen(Color::Red);
		p->Width = 6.0F;
		//p->DashStyle = Pen::DashStyle::DashPattern::
		//p->LineJoin = System::Drawing::Drawing2D::LineJoin::Bevel;
		p->EndCap = Drawing::Drawing2D::LineCap::ArrowAnchor;
		for (int i = 0; i < posFirst.size(); i++)
		{
			a.X = posFirst[i][1] * 64 + 32;
			a.Y = posFirst[i][0] * 64 + 32;
			b.X = posSecond[i][1] * 64 + 32;
			b.Y = posSecond[i][0] * 64 + 32;
			graphics->DrawLine(p, a, b);
		}
	}

	System::Void Form1::pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		System::Drawing::Point pos = this->PointToClient(Cursor->Position);
		this->board->insertQueen((pos.Y - 10) / 64, (pos.X - 10) / 64);
		displayResult(board);
	}
}