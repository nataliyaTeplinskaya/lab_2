#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#define BUFFER_SIZE 32767;

using namespace std;

TCHAR* lpName=new TCHAR[256];

int _tmain()
{
    DWORD nHigh = 0;
    DWORD szMsg = 32767;
    HANDLE hMapFile = INVALID_HANDLE_VALUE;
	LPVOID memory;
	cout << "Enter shared memory name: ";
    cin >>  lpName;
    std::cout<<"\n";


    DWORD error = GetLastError();
	cout << endl;

	if (error != ERROR_FILE_EXISTS)
	{
		hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, szMsg, &lpName[0]);
	}
	else
	{
		hMapFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, &lpName[0]);
	}


	if (hMapFile != NULL)

	{
		memory = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, szMsg);
		int nfact;
		int i = 0;
		do
		{
		    std::cout<<"\nPlease choose an action to do:\n\n"<<"1. Read message from shared memory;\n"<<"2. Write message to shared memory;\n"<<"3. Quit.\n\n";
            std::cin>>nfact;

			if (nfact == 1)
			{
				printf("Message from shared memory: %s\n", memory);
				cout << endl;
			}
			else if (nfact == 2)
			{
				{
                    auto message = reinterpret_cast<char*>(memory);
                    cout << "Enter the message: ";
                    char input[128];
                    cin >> input;
                    strcpy(message, input);
                }
			}
			else if (nfact == 3)
			{
				std::cout<<"Uncorrect number\n\n";
				i = 1;
			}
			else
			{
				cout << "Uncorrect number\n\n" << endl;
				i = 1;
			}
		} while (i == 0);
		UnmapViewOfFile(memory);
		CloseHandle(hMapFile);
		return(0);
	}
	else
	{
		printf("Could not create file mapping object (%d).\n"),
			GetLastError();
		return 1;
	}
	UnmapViewOfFile(memory);
	CloseHandle(hMapFile);
}




