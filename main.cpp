#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>

#define BUF_SIZE 256

using namespace std;

TCHAR* lpName=new TCHAR[256];
TCHAR* szMsg=new TCHAR[256];

int _tmain()
{
    cout << "Enter shared memory name:\n";
    cin >>  szMsg;
    std::cout<<"\n";

    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = OpenFileMapping(
               FILE_MAP_ALL_ACCESS,
               FALSE,
               lpName);


    if (hMapFile == NULL){
      cout << hMapFile << ", Last Error: " << GetLastError() << endl << endl;

      cout << "Create File Mapping" << endl;

      hMapFile = CreateFileMapping(
             INVALID_HANDLE_VALUE,
             NULL,
             PAGE_READWRITE,
             0,
             BUF_SIZE,
             lpName);
    }


    if (hMapFile == NULL){
      cout << hMapFile << ", Last Error: " << GetLastError() << endl;
      return 1;
    }

    pBuf = (LPTSTR) MapViewOfFile(hMapFile, // handle to map object
               FILE_MAP_ALL_ACCESS,         // read/write permission
               0,
               0,
               BUF_SIZE);

    if (pBuf == NULL)
       {
          cout << "Could not map view of file, Last Error: " << GetLastError() << endl;
          CloseHandle(hMapFile);
          return 1;
       }


    int nfact;

    while (hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,lpName))
    {
        std::cout<<"\nPlease choose an action to do:\n\n"<<"1. Read message from shared memory;\n"<<"2. Write message to shared memory;\n"<<"3. Quit.\n\n";
        std::cin>>nfact;

        if (nfact==1)
        {
            std::cout<<"The message says:  "<<pBuf<<std::endl;
        }
        else {
            if (nfact==2)
                {
                    memset((void*)pBuf,0,BUF_SIZE);
                    std::cout<<"Enter message text:  ";
                    std::cin >> szMsg;
                    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
                }
            else {
                if (nfact==3){
                        exit(1);
                }
                else if ((nfact!=1)&&(nfact!=2)&&(nfact!=3))
                    { std::cout<<"Uncorrect number\n\n";
                    }}}
        }

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
