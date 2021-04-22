
#include <stdio.h>

#include "moduleloader.h"

#define gle GetLastError

void usage();

typedef INT (*DOSOMETHING)();


int main(int argc, char ** argv)
{
    DWORD le = NOERROR;
    if (argc < 2 || lstrcmpA(argv[1], "/?") == 0)
    {
        usage();
    }
    else
    {
        HANDLE hFile = CreateFileA(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (INVALID_HANDLE_VALUE != hFile)
        {
            const DWORD dwSizeLow = GetFileSize(hFile, NULL);
            PBYTE pbFile = (PBYTE)malloc(dwSizeLow);
            if (NULL != pbFile)
            {
                DWORD dwRead = 0;
                if (ReadFile(hFile, pbFile, dwSizeLow, &dwRead, NULL) && dwSizeLow == dwRead)
                {
                    PLOADEDMODULE pModule = LoadModuleFromMemory(pbFile, dwRead);
                    if (NULL != pModule)
                    {
                        DOSOMETHING DoSomething = (DOSOMETHING)_GetProcAddress(pModule, "DoSomething");
                        if (NULL != DoSomething)
                        {
                            DoSomething();
                        }
                        else
                        {
                            le = gle();
                        }

                        FreeLibraryResources(pModule);
                    }
                    else
                    {
                        le = gle();
                    }
                }
                else
                {
                    le = gle();
                }

                free(pbFile);
            }
            else
            {
                le = ERROR_OUTOFMEMORY;
            }

            CloseHandle(hFile);
        }
        else
        {
            le = gle();
        }

        if (NOERROR != le)
        {
            printf("Unable to load library or execute function. GLE=%d\n", le);
        }
    }

    return le;
}

void usage()
{
    printf("Loads a DLL into memory, and then invokes a function in it.\n"
           "\n"
           "SAMPLE-EXE dllpath\n"
           "\n"
           "dllpath    Specifies the file path to the sample-dll.\n"
           "\n"
           "Example:\n"
           "\n"
           "    SAMPLE-EXE .\\SAMPLE-DLL.DLL\n"
           "\n");
}
