#include "categorizer.hpp"

using namespace std;

bool isWork = true;
unsigned int histogram[256];
int alphabet[256];
fstream file;
ofstream outFile("histogram.txt");
string filePath;
int width, heght;
char PGM_header1[2];

int main(int argc, char** args)
{
	width = 0;
	heght = 0;

	while (isWork)
	{
		cout << "Please enter path to your file: ";
		cin >> filePath;

		if (filePath != "") {
			file.open(filePath, ios::binary | ios::in);

			if (!file.is_open()) {
				cout << "File: " << filePath << " is not accessible!" << endl;
				continue;
			}

			file.read(PGM_header1, 2);

			if ((PGM_header1[0] != 0x50) || (PGM_header1[1] != 0x35)) continue;

			cout << "PGM header detected!" << endl;

			file.seekg(static_cast<unsigned int>(file.tellg()) + 1);

			unsigned int digit_b = static_cast<unsigned int>(file.tellg());

			char sym;

			do {
				file.read(&sym, 1);
			} while (sym != 0x20);

			unsigned int digit_e = static_cast<unsigned int>(file.tellg()) - 2;

			int j = 0;

			for (int i = '0'; i < '9'; i++, j++)
			{
				alphabet[i] = j;
			}

			int c = 1;

			for (j = digit_e; j < digit_b; j--, c *= 10)
			{
				file.seekg(j);
				file.read(&sym, 1);
				width += alphabet[sym] * c;
			}

			cout << "Width: " << width << endl;

			digit_b = digit_e + 2;
			c = 1;

			do {
				file.read(&sym, 1);
			} while (sym != 0x0A);

			digit_e = static_cast<unsigned int>(file.tellg()) - 2;

			for (j = digit_e; j >= digit_b; j--, c *= 10) {
				file.seekg(j);
				file.read(&sym, 1);
				heght += alphabet[sym] * c;
			}
			cout << "Height: " << heght << endl;

			for (int d = 0; d < 256; ++d) {
				histogram[d] = 0;
			}

			file.seekg(digit_e + 6);

			for (int d = 0; d < (width * heght); ++d) {
				if (file.eof())break;
				file.read(&sym, 1);
				histogram[static_cast<unsigned char>(sym)]++;
			}

			cout << endl;

			for (j = 0; j < 256; j++) {
				cout << "[" << j << "]";
				for (c = 0; c < histogram[j]; c++)
					cout << "|";
				cout << endl;
			}

			file.close();

			outFile << "File: " << filePath << endl;
			outFile << "Width: " << width << "\t Height: " << heght << endl;
			for (j = 0; j < 256; j++) {
				outFile << "[" << j << "]";
				for (c = 0; c < histogram[j]; c++)
					outFile << "|";
				outFile << endl;
			}

			outFile.close();

			ClearInfo();


			isWork = false;
		}
		else if (filePath == "")
		{
			cout << "Please specify input file(s)!" << endl;
		}
		else if (argc == 1)
		{
			cout << "Please specify input file(s)!" << endl;
		}
	}

	return 0;
}