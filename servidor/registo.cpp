#include "servidor.h"

int escreveRegisto() {

	HKEY chave;
	DWORD queAconteceu;

	//Criar/abrir uma chave em HKEY_CURRENT_USER\Software\TP_SO2_2018_2019
	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\TP_SO2_2018_2019"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &chave, &queAconteceu) != ERROR_SUCCESS) {
		_tprintf(TEXT("Erro ao criar/abrir chave (%d)\n"), GetLastError());
		return -1;
	}
	else {
		//Se a chave foi criada, inicializar os valores
		if (queAconteceu == REG_CREATED_NEW_KEY) {
			_tprintf(TEXT("Chave: HKEY_CURRENT_USER\\Software\\TP_SO2_2018_2019 criada\n"));
			//Criar valor "Autor" = "Nuno Fidalgo e Cláudio Melo"
			RegSetValueEx(chave, TEXT("Autores"), 0, REG_SZ, (LPBYTE)TEXT("Nuno Fidalgo e Cláudio Melo"), _tcslen(TEXT("Nuno Fidalgo e Cláudio Melo")) * sizeof(TCHAR));

			RegSetValueEx(chave, TEXT("Meta"), 0, REG_SZ, (LPBYTE)TEXT("Meta 1"), _tcslen(TEXT("Meta 1")) * sizeof(TCHAR));

			RegSetValueEx(chave, TEXT("Top Ten"), 0, REG_SZ, (LPBYTE)TEXT("Nuno,Cláudio,Cláudio,Nuno,Melo,Fidalgo,21170023,21140369"), _tcslen(TEXT("Nuno,Cláudio,Cláudio,Nuno,Melo,Fidalgo,21170023,21140369")) * sizeof(TCHAR));
			RegSetValueEx(chave, TEXT("Pontuações"), 0, REG_SZ, (LPBYTE)TEXT("2931,292,198,156,145,133,132,15"), _tcslen(TEXT("2931,292,198,156,145,133,132,15")) * sizeof(TCHAR));
		}
	}
	return 0;
}

int leRegisto() {

	HKEY chave;
	DWORD queAconteceu, tamanho;
	TCHAR str[TAM], top_ten[TAM], pontuacoes[TAM];

	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\TP_SO2_2018_2019"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &chave, &queAconteceu) != ERROR_SUCCESS) {
		_tprintf(TEXT("Erro ao criar/abrir chave (%d)\n"), GetLastError());
		return -1;
	}
	else {
		//Se a chave foi aberta, ler os valores lá guardados
		if (queAconteceu == REG_OPENED_EXISTING_KEY) {
			tamanho = 200;
			RegQueryValueEx(chave, TEXT("Top Ten"), NULL, NULL, (LPBYTE)top_ten, &tamanho);
			top_ten[tamanho / sizeof(TCHAR)] = '\0';

			tamanho = 200;
			RegQueryValueEx(chave, TEXT("Pontuações"), NULL, NULL, (LPBYTE)pontuacoes, &tamanho);
			pontuacoes[tamanho / sizeof(TCHAR)] = '\0';

			_stprintf_s(str, TAM, TEXT("Top Ten: %s\nPontuação: %s\n"), top_ten, pontuacoes);
			_tprintf(TEXT("Lido do Registry:\n%s"), str);
		}
		else {
			_tprintf(TEXT("Erro ao criar/abrir chave (%d)\n"), GetLastError());
			return -1;
		}
		RegCloseKey(chave);
		return 0;
	}
}
