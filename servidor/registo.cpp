#include "servidor.h"
#include <strsafe.h>

#define CHAVE_REG  TEXT("Software\\TP_SO2_2018_2019")
#define APAGA_REG TEXT("HKEY_CURRENT_USER\\Software\\TP_SO2_2018_2019")

extern SECURITY_ATTRIBUTES sa;

int escreveRegisto(TOPTEN& topten) {

	HKEY chave;
	DWORD queAconteceu;

	TCHAR autores[] = TEXT("Nuno Fidalgo e Cláudio Melo");
	TCHAR meta[] = TEXT("Meta 2 (entrega final)");
	TCHAR top_ten[MAX] = TEXT("");
	TCHAR pontos[TEXTO];

	for (int i = 0; i < TOP_TEN; i++) {
		//_tprintf(TEXT("[%d] %s = %d\n"), i, topten.pontuacoes[i].nome, topten.pontuacoes[i].pontos);
		_stprintf_s(pontos, TEXTO, TEXT("%s = %d\n"), topten.pontuacoes[i].nome, topten.pontuacoes[i].pontos);
		//_tprintf(TEXT("[%d] strlen: %d, "), i, _tcslen(aux));
		//_tprintf(TEXT("[%d] %s"), i, aux);
		if (_tcscmp(pontos, TEXT(" = 0\n")) != 0)
			_tcsncat_s(top_ten, pontos, _tcslen(pontos));
	}
	//_tprintf(TEXT("top ten:\n%s"), pontuacoes);

	if (RegCreateKeyEx(HKEY_CURRENT_USER, CHAVE_REG, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &sa, &chave, &queAconteceu) != ERROR_SUCCESS) {
		_tprintf(TEXT("%s: Erro ao criar chave ou chave já existe no registo! (%d)\n"), SERVIDOR, GetLastError());
		return -1;
	}
	else {
		_tprintf(TEXT("%s: Chave criada com sucesso no registo!\n"), SERVIDOR);
		if (queAconteceu == REG_CREATED_NEW_KEY || queAconteceu == REG_OPENED_EXISTING_KEY) {
			RegSetValueEx(chave, TEXT("Autores"), 0, REG_SZ, (LPBYTE)autores, _tcslen(autores) * sizeof(TCHAR));
			RegSetValueEx(chave, TEXT("Meta"), 0, REG_SZ, (LPBYTE)meta, _tcslen(meta) * sizeof(TCHAR));
			RegSetValueEx(chave, TEXT("Top Ten"), 0, REG_SZ, (LPBYTE)top_ten, _tcslen(top_ten) * sizeof(TCHAR));
			_tprintf(TEXT("%s: Dados guardados no registo!\n"), SERVIDOR);
		}

		RegCloseKey(chave);

		return 1;
	}
	_tprintf(TEXT("%s: Dados já existem no registo!\n"), SERVIDOR);
	return 0;
}

int leRegisto(TOPTEN& topten) {

	HKEY chave;
	DWORD tamanho = MAX;

	TCHAR autores[MAX];
	TCHAR meta[MAX];
	TCHAR top_ten[MAX];

	TCHAR seps[] = TEXT("=\n");
	//TCHAR teste[] = TEXT("Nuno=1000\nClaudio=20\nNuno2=10002\nClaudio2=202\n");
	TCHAR* token1 = NULL;
	TCHAR* next_token1 = NULL;

	if (RegOpenKey(HKEY_CURRENT_USER, CHAVE_REG, &chave) != ERROR_SUCCESS) {
		_tprintf(TEXT("%s:  Erro ao aceder ao registo / Servidor sem dados! (%d)\n"), SERVIDOR, GetLastError());
		return -1;
	}

	else {
		//	if (queAconteceu == REG_OPENED_EXISTING_KEY) {
		//_tprintf(TEXT("%s:  Erro ao criar chave ou chave já existe no registo! (%d)\n"), SERVIDOR, GetLastError());
		RegQueryValueEx(chave, TEXT("Autores"), NULL, NULL, (LPBYTE)autores, &tamanho);
		autores[tamanho / sizeof(TCHAR)] = '\0';

		RegQueryValueEx(chave, TEXT("Meta"), NULL, NULL, (LPBYTE)meta, &tamanho);
		meta[tamanho / sizeof(TCHAR)] = '\0';

		RegQueryValueEx(chave, TEXT("Top Ten"), NULL, NULL, (LPBYTE)top_ten, &tamanho);
		top_ten[tamanho / sizeof(TCHAR)] = '\0';

		_tprintf(TEXT("%s: A Ler do Registo:\n"), SERVIDOR);
		_tprintf(TEXT("%s: Autores: %s\n"), SERVIDOR, autores);
		_tprintf(TEXT("%s: Meta: %s\n"), SERVIDOR, meta);
		_tprintf(TEXT("%s: Topten: %s\n"), SERVIDOR, top_ten);

		token1 = _tcstok_s(top_ten, seps, &next_token1);
		int i = 0, num = 0;
		while (token1 != NULL || i < TOP_TEN) {
			if (token1 != NULL) {
				//_tprintf(TEXT("[%d] token1: %s\n"), i, token1);
				if (num % 2 == 0) {
					/*_tprintf(TEXT("[%d] par\n"), i);*/
					_tcscpy_s(topten.pontuacoes[i].nome, token1);
					_tprintf(TEXT("[%d] par: %s\n"), i, topten.pontuacoes[i].nome);
				}
				else {
					//_tprintf(TEXT("[%d] impar\n"), i);
					topten.pontuacoes[i].pontos = _tstoi(token1);
					_tprintf(TEXT("[%d] impar: %d\n"), i, topten.pontuacoes[i].pontos);
					i++;
				}
				token1 = _tcstok_s(NULL, seps, &next_token1);
				//_tprintf(TEXT("[%d] next_token1: %s\n"), i, next_token1);
				num++;
			}
			else {
				_tcscpy_s(topten.pontuacoes[i].nome, TEXT(""));
				topten.pontuacoes[i].pontos = 0;
				i++;
			}
		}
		RegCloseKey(chave);
		return 1;
	}
	//}
	return 0;
}

BOOL RegDelnodeRecurse(HKEY hKeyRoot, LPTSTR lpSubKey) {
	LPTSTR lpEnd;
	LONG lResult;
	DWORD dwSize;
	TCHAR szName[MAX_PATH];
	HKEY hKey;
	FILETIME ftWrite;

	// First, see if we can delete the key without having
	// to recurse.

	lResult = RegDeleteKey(hKeyRoot, lpSubKey);

	if (lResult == ERROR_SUCCESS)
		return TRUE;

	lResult = RegOpenKeyEx(hKeyRoot, lpSubKey, 0, KEY_READ, &hKey);

	if (lResult != ERROR_SUCCESS) {
		if (lResult == ERROR_FILE_NOT_FOUND) {
			printf("Key not found.\n");
			return TRUE;
		}
		else {
			printf("Error opening key.\n");
			return FALSE;
		}
	}

	// Check for an ending slash and add one if it is missing.

	lpEnd = lpSubKey + lstrlen(lpSubKey);

	if (*(lpEnd - 1) != TEXT('\\')) {
		*lpEnd = TEXT('\\');
		lpEnd++;
		*lpEnd = TEXT('\0');
	}

	// Enumerate the keys

	dwSize = MAX_PATH;
	lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL,
		NULL, NULL, &ftWrite);

	if (lResult == ERROR_SUCCESS) {
		do {

			*lpEnd = TEXT('\0');
			StringCchCat(lpSubKey, MAX_PATH * 2, szName);

			if (!RegDelnodeRecurse(hKeyRoot, lpSubKey)) {
				break;
			}

			dwSize = MAX_PATH;

			lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL,
				NULL, NULL, &ftWrite);

		} while (lResult == ERROR_SUCCESS);
	}

	lpEnd--;
	*lpEnd = TEXT('\0');

	RegCloseKey(hKey);

	// Try again to delete the key.

	lResult = RegDeleteKey(hKeyRoot, lpSubKey);

	if (lResult == ERROR_SUCCESS)
		return TRUE;

	return FALSE;
}

BOOL apagaChaveRegisto(HKEY hKeyRoot, LPCTSTR lpSubKey) {
	TCHAR szDelKey[MAX_PATH * 2];

	StringCchCopy(szDelKey, MAX_PATH * 2, lpSubKey);
	return RegDelnodeRecurse(hKeyRoot, szDelKey);

}

int apagaRegisto() {
	BOOL bSuccess;
	//HKEY chave;

	//RegOpenKey(HKEY_CURRENT_USER, CHAVE_REG, &chave);
	bSuccess = apagaChaveRegisto(HKEY_CURRENT_USER, CHAVE_REG);

	//	bSuccess = RegDeleteKeyW(chave, CHAVE_REG);

	if (bSuccess)
		_tprintf(TEXT("Chave eliminada do registo...\n"));
	else _tprintf(TEXT("Não consegui eliminar chave do registo...\n"));

	return 0;
}