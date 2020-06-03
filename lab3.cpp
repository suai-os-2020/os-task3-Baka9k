#include <windows.h>
#include <iostream>
#include "lab3.h"

using namespace std;

#define THREAD__COUNT 10

DWORD ThreadID;
HANDLE ghThread[THREAD__COUNT];
HANDLE ghMutex;
HANDLE sem_e, sem_h, sem_i, semInterval, semContinue;

unsigned int lab3_thread_graph_id()
{
    return 16;
}

const char* lab3_unsynchronized_threads()
{
    return "bcef";
}

const char* lab3_sequential_threads()
{
    return "ehi";
}

DWORD WINAPI thread_a(LPVOID);
DWORD WINAPI thread_b(LPVOID);
DWORD WINAPI thread_c(LPVOID);
DWORD WINAPI thread_e(LPVOID);
DWORD WINAPI thread_f(LPVOID);
DWORD WINAPI thread_d(LPVOID);
DWORD WINAPI thread_g(LPVOID);
DWORD WINAPI thread_h(LPVOID);
DWORD WINAPI thread_i(LPVOID);
DWORD WINAPI thread_k(LPVOID);



DWORD WINAPI thread_a(LPVOID lpParam) {
    // ---- 1 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "a" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }

    // thread_e
    ghThread[3] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
    if (ghThread[3] == NULL) {
        return GetLastError();
    }

    // WaitE
    WaitForSingleObject(ghThread[3], INFINITE);
    return 0;

}

DWORD WINAPI thread_e(LPVOID lpParam) {
    // ---- 2 ----
    // thread_b
    ghThread[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &ThreadID);
    if (ghThread[1] == NULL) {
        return GetLastError();
    }

    // thread_c
    ghThread[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &ThreadID);
    if (ghThread[2] == NULL) {
        return GetLastError();
    }

    // thread_f
    ghThread[4] = CreateThread(NULL, 0, thread_f, NULL, 0, &ThreadID);
    if (ghThread[4] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }

    // WaitC
    WaitForSingleObject(ghThread[2], INFINITE);
    // interval - b
    WaitForSingleObject(semInterval, INFINITE);
    // interval - f
    WaitForSingleObject(semInterval, INFINITE);

    // ---- 3 ----
    // continue - b
    ReleaseSemaphore(semContinue, 1, NULL); 
    // continue - f
    ReleaseSemaphore(semContinue, 1, NULL);
    // thread_d
    ghThread[5] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
    if (ghThread[5] == NULL) {
        return GetLastError();
    }

    // thread_g
    ghThread[6] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
    if (ghThread[6] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }

    // WaitB
    WaitForSingleObject(ghThread[1], INFINITE);
    // WaitD
    WaitForSingleObject(ghThread[5], INFINITE);
    // interval - g
    WaitForSingleObject(semInterval, INFINITE);
    // interval - f
    WaitForSingleObject(semInterval, INFINITE);

    // ---- 4 ----
    // continue - g
    ReleaseSemaphore(semContinue, 1, NULL);
    // continue - f
    ReleaseSemaphore(semContinue, 1, NULL);
    // thread_h
    ghThread[7] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
    if (ghThread[7] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }

    // WaitG
    WaitForSingleObject(ghThread[6], INFINITE);
    // WaitF
    WaitForSingleObject(ghThread[4], INFINITE);
    // interval - h
    WaitForSingleObject(semInterval, INFINITE);

    // ---- 5 ----
    // continue - h
    ReleaseSemaphore(semContinue, 1, NULL);
    // thread_i
    ghThread[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &ThreadID);
    if (ghThread[8] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(sem_e, INFINITE);
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(ghMutex);
        ReleaseSemaphore(sem_h, 1, NULL);
    }

    // WaitH
    WaitForSingleObject(ghThread[7], INFINITE);
    // interval - i
    WaitForSingleObject(semInterval, INFINITE);

    // ---- 6 ----
    // continue - i
    ReleaseSemaphore(semContinue, 1, NULL);
    // thread_k
    ghThread[9] = CreateThread(NULL, 0, thread_k, NULL, 0, &ThreadID);
    if (ghThread[9] == NULL) {
        return GetLastError();
    }

    // WaitI
    WaitForSingleObject(ghThread[8], INFINITE);
    // WaitK
    WaitForSingleObject(ghThread[9], INFINITE);
    return 0;
}

DWORD WINAPI thread_b(LPVOID lpParam) {
    // ---- 2 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "b" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }

    ReleaseSemaphore(semInterval, 1, NULL);
    // ----
    WaitForSingleObject(semContinue, INFINITE);

    // ---- 3 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "b" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }
    return 0;
}

DWORD WINAPI thread_c(LPVOID lpParam) {
    // ---- 2 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "c" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }
    return 0;
}

DWORD WINAPI thread_f(LPVOID lpParam) {
    // ---- 2 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "f" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }

    ReleaseSemaphore(semInterval, 1, NULL);
    // ----
    WaitForSingleObject(semContinue, INFINITE);

    // ---- 3 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "f" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }

    ReleaseSemaphore(semInterval, 1, NULL);
    // ----
    WaitForSingleObject(semContinue, INFINITE);

    // ---- 4 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "f" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }
    return 0;
}

DWORD WINAPI thread_g(LPVOID lpParam) {
    // ---- 3 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "g" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }

    ReleaseSemaphore(semInterval, 1, NULL);
    // ----
    WaitForSingleObject(semContinue, INFINITE);

    // ---- 4 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "g" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }
    return 0;
}

DWORD WINAPI thread_d(LPVOID lpParam) {
    // ---- 3 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "d" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }
    return 0;
}

DWORD WINAPI thread_h(LPVOID lpParam) {
    // ---- 4 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "h" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }

    ReleaseSemaphore(semInterval, 1, NULL);
    // ----
    WaitForSingleObject(semContinue, INFINITE);

    // ---- 5 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(sem_h, INFINITE);
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "h" << flush;
        computation();
        ReleaseMutex(ghMutex);
        ReleaseSemaphore(sem_i, 1, NULL);
    }
    return 0;
}

DWORD WINAPI thread_i(LPVOID lpParam) {
    // ---- 5 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(sem_i, INFINITE);
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "i" << flush;
        computation();
        ReleaseMutex(ghMutex);
        ReleaseSemaphore(sem_e, 1, NULL);
    }

    ReleaseSemaphore(semInterval, 1, NULL);
    // ----
    WaitForSingleObject(semContinue, INFINITE);
    // ---- 6 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "i" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }
    return 0;
}

DWORD WINAPI thread_k(LPVOID lpParam) {
    // ---- 6 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(ghMutex, INFINITE);
        cout << "k" << flush;
        computation();
        ReleaseMutex(ghMutex);
    }
    return 0;
}

int lab3_init()
{

    ghMutex = CreateMutex(NULL, 0, NULL);
    if (ghMutex == NULL) {
        cout << "CreateMutex error: " << GetLastError();
        return 1;
    }

    sem_e = CreateSemaphore(NULL, 1, 1, NULL);
    if (sem_e == NULL)
    {
        std::cout << "CreateSemaphore_e error: " << GetLastError();
        return 1;
    }
    sem_h = CreateSemaphore(NULL, 0, 1, NULL);
    if (sem_h == NULL)
    {
        std::cout << "CreateSemaphore_h error: " << GetLastError();
        return 1;
    }
    sem_i = CreateSemaphore(NULL, 0, 1, NULL);
    if (sem_i == NULL)
    {
        std::cout << "CreateSemaphore_i error: " << GetLastError();
        return 1;
    }

    semInterval = CreateSemaphore(NULL, 0, 3, NULL);
    if (semInterval == NULL)
    {
        std::cout << "Interval error: " << GetLastError();
        return 1;
    }

    semContinue = CreateSemaphore(NULL, 0, 3, NULL);
    if (semInterval == NULL)
    {
        std::cout << "Error: " << GetLastError();
        return 1;
    }

    ghThread[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);
    if (ghThread[0] == NULL) {
        return GetLastError();
    }

    // WaitD
    WaitForSingleObject(ghThread[0], INFINITE);
   
    CloseHandle(ghThread[0]);
    // mutex close
    CloseHandle(ghMutex);
    // sem_e close
    CloseHandle(sem_e);
    // sem_h close
    CloseHandle(sem_h);
    // sem_i close
    CloseHandle(sem_i);

    // semContinue close
    CloseHandle(semContinue);
    // semInterval close
    CloseHandle(semInterval);
    return 0;
}

