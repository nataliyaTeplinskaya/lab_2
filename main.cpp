#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <Lmcons.h>
#include <cstdlib>
#include <tchar.h>
#define WINVER 0x0502
#define BUFSIZE MAX_PATH
#define FILESYSNAMEBUFSIZE MAX_PATH
#define MAX_KEY_LENGTH 255
#pragma warning(disable : 4996)
#define BUFFER_SIZE 32767;
using namespace std;


int _tmain()
{
    DWORD nHigh = 0;
	DWORD szMsg = 32767;
    HANDLE hMapFile = INVALID_HANDLE_VALUE;
    LPVOID memory;
    char lpName[MAX_PATH]

    wcout << "Enter shared memory name: ";
	cin >> lpName;
	cout << endl;


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
		/*4*/
		int nfact;
		int a = 0;
		do
		{
		    std::cout<<"\nPlease choose an action to do:\n\n"<<"1. Read message from shared memory;\n"<<"2. Write message to shared memory;\n"<<"3. Quit.\n\n";
            std::cin>>nfact;
            if (nfact==1)
        {
            std::cout<<"The message says:  "<<memory<<std::endl;
        }
            else {
                if (nfact==2)
                    {
                        memset((void*)memory,0,BUF_SIZE);
                        std::cout<<"Enter message text:  ";
                        std::cin >> szMsg;
                        CopyMemory((PVOID)memory, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
                }
                else {
                    if (nfact==3){
                            exit(1);
                }
                    else if ((nfact!=1)&&(nfact!=2)&&(nfact!=3))
                    { std::cout<<"Uncorrect number\n\n";
                    }}}
		}
    UnmapViewOfFile(memory);
	CloseHandle(hMapFile);
}

