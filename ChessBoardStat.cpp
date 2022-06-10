#include "pch.h"
#include "ChessBoardStat.h"

void ChessBoardStat::messageBoxShow()
{
	System::Windows::Forms::MessageBox::Show(
		"Statistics:"
		+ "\nThe number of all created nodes: " + count
		+ "\nMax number of nodes that existed at the same time: " + max
		+ "\nThe depth of the tree: " + depth,
		"Completed!",
		System::Windows::Forms::MessageBoxButtons::OK,
		System::Windows::Forms::MessageBoxIcon::Information
	);
}

void ChessBoardStat::fileOutput(std::ofstream& fileOut)
{
	ChessBoard::fileOutput(fileOut);
	fileOut << "\nStatistics:"
		<< "\nThe number of all created nodes: " << count
		<< "\nMax number of nodes that existed at the same time: " << max
		<< "\nThe depth of the tree: " << depth << "\n\n\n";
};