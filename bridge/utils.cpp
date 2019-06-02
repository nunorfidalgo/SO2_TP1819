#include "bridge.h"
#include "sinc.h"
#include <strsafe.h>
#include <aclapi.h>

extern "C" {

	void gotoxy(int x, int y) {
		static HANDLE hStdout = NULL;
		COORD coord;
		coord.X = x;
		coord.Y = y;
		if (!hStdout)
			hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hStdout, coord);
	}

	void closeSincControl(SincControl &sincControl) {
		CloseHandle(sincControl.hMutexMensagem);
		CloseHandle(sincControl.hEventoMensagem);
		CloseHandle(sincControl.hMutexJogo);
		CloseHandle(sincControl.hEventoJogo);
		UnmapViewOfFile(sincControl.mensagem);
		UnmapViewOfFile(sincControl.jogo);
		CloseHandle(sincControl.hMemMensagem);
		CloseHandle(sincControl.hMemJogo);
	}

	// Buffer clean up routine
	void Cleanup(PSID pEveryoneSID, PSID pAdminSID, PACL pACL, PSECURITY_DESCRIPTOR pSD)
	{
		if (pEveryoneSID)
			FreeSid(pEveryoneSID);
		if (pAdminSID)
			FreeSid(pAdminSID);
		if (pACL)
			LocalFree(pACL);
		if (pSD)
			LocalFree(pSD);
	}

	void Seguranca(SECURITY_ATTRIBUTES * sa)
	{
		PSECURITY_DESCRIPTOR pSD;
		PACL pAcl;
		EXPLICIT_ACCESS ea;
		PSID pEveryoneSID = NULL, pAdminSID = NULL;
		SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
		TCHAR str[256];

		pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR,
			SECURITY_DESCRIPTOR_MIN_LENGTH);
		if (pSD == NULL) {
			_tprintf(TEXT("Erro LocalAlloc!!!\n"));
			return;
		}
		if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION)) {
			_tprintf(TEXT("Erro IniSec!!!\n"));
			return;
		}

		// Create a well-known SID for the Everyone group.
		if (!AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID,
			0, 0, 0, 0, 0, 0, 0, &pEveryoneSID))
		{
			_stprintf_s(str, 256, TEXT("AllocateAndInitializeSid() error %u\n"), GetLastError());
			_tprintf(str);
			Cleanup(pEveryoneSID, pAdminSID, NULL, pSD);
		}
		else
			_tprintf(TEXT("AllocateAndInitializeSid() for the Everyone group is OK\n"));

		ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));

		ea.grfAccessPermissions = GENERIC_READ | GENERIC_WRITE;
		ea.grfAccessMode = SET_ACCESS;
		ea.grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
		ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
		ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
		ea.Trustee.ptstrName = (LPTSTR)pEveryoneSID;

		if (SetEntriesInAcl(1, &ea, NULL, &pAcl) != ERROR_SUCCESS) {
			_tprintf(TEXT("Erro SetAcl!!!\n"));
			return;
		}

		if (!SetSecurityDescriptorDacl(pSD, TRUE, pAcl, FALSE)) {
			_tprintf(TEXT("Erro IniSec!!!\n"));
			return;
		}

		sa->nLength = sizeof(*sa);
		sa->lpSecurityDescriptor = pSD;
		sa->bInheritHandle = TRUE;
	}

}