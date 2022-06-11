#include "pch.h"
#include "Form1.h"
namespace CppCLRWinformsProject {
	System::Void Form1::deletePictureQueen(System::Object^ sender, System::EventArgs^ e)
	{
		System::Drawing::Point pos = this->pictureBox1->PointToClient(Cursor->Position);
		this->board->removeQueen((pos.Y) / 64, (pos.X) / 64);
		displayBoard(this->board);
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

	System::Void Form1::displayBoard(ChessBoard* board)
	{
		std::vector<std::vector<int>> queenPos = board->getQueenPos();

		int i = 0;
		while (FormPointer->pictureBox1->Controls->ContainsKey((L"pictureBox" + i)))
		{
			Control^ ctrl = FormPointer->pictureBox1->Controls->Find(L"pictureBox" + i, false)[0];
			delete ctrl;
			FormPointer->pictureBox1->Controls->RemoveByKey((L"pictureBox" + i));
			i++;
		}

		for (int i = 0; i < queenPos.size(); i++)
			FormPointer->createPictureQueen(queenPos[i][1], queenPos[i][0], i);
		
		FormPointer->pictureBox1->Refresh();
	}

	System::Void Form1::button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		//if (stressTest())
		//	MessageBox::Show("Stress test is completed!", "Completed!");
		if (this->board->queenFirstCheck())
		{
			std::ofstream fileOutput("output.txt", std::ios::app);
			time_t current_time = time(0);
			fileOutput << "------------------------\n" << ctime(&current_time) << "\nInput:\n";
			this->board->fileOutput(fileOutput);
			if (!this->board->queenCheck())
			{
				MessageBox::Show("The position of figures is right. No method is applied!", "Completed!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				fileOutput << "\nThe position of figures is right. No method is applied!\n\n\n";
				fileOutput.close();
				return;
			}
			int choice = this->comboBox1->SelectedIndex;
			ChessBoard* result = NULL;
			switch (choice)
			{
			case 0:
				result = LDFS(this->board);
				fileOutput << "\nLDFS method:\n";
				break;
			case 1:
				result = BFS(this->board);
				fileOutput << "\nBFS method:\n";
				break;
			case 2:
				result = IDS(new ChessBoard(this->board), 100);
				if (result == NULL)
					MessageBox::Show("The method cannot solve the task! The depth is not enough!", "Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				else
					fileOutput << "\nIDS method:\n";
				break;
			default:
				MessageBox::Show("Method is not selected!", "Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				fileOutput << "\nError! No method was selected!\n\n\n";
			}

			if (result != NULL)
			{

				displayBoard(result);

				displayArrows(board, result);
				MessageBox::Show("The task is solved!", "Completed!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				result->messageBoxShow();
				result->fileOutput(fileOutput);

				delete this->board;
				this->board = new ChessBoard(result);
				delete result;
			}
			fileOutput.close();
		}
		else
			MessageBox::Show("Wrong placement!", "Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);

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
				temp2 = IDS(temp, 10); //choose method here
				if (temp2 == NULL || temp2->queenCheck())
					return false;
				displayBoard(temp2);
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
		System::Drawing::Point pos = this->pictureBox1->PointToClient(Cursor->Position);
		this->board->insertQueen((pos.Y) / 64, (pos.X) / 64);
		displayBoard(board);
	}
}