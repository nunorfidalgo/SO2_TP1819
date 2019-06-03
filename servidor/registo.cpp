#include "servidor.h"

#define CHAVE_REG  TEXT("Software\\TP_SO2_2018_2019")

extern SECURITY_ATTRIBUTES sa;

int escreveRegisto(TOPTEN &topten) {

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
		_tprintf(TEXT("%s: Erro ao criar chave no registo! (%d)\n"), SERVIDOR, GetLastError());
		return -1;
	}
	else {
		if (queAconteceu == REG_CREATED_NEW_KEY) {
			_tprintf(TEXT("%s: Chave criada com sucesso no registo!\n"), SERVIDOR);
			RegSetValueEx(chave, TEXT("Autores"), 0, REG_SZ, (LPBYTE)autores, _tcslen(autores) * sizeof(TCHAR));
			RegSetValueEx(chave, TEXT("Meta"), 0, REG_SZ, (LPBYTE)meta, _tcslen(meta) * sizeof(TCHAR));
			RegSetValueEx(chave, TEXT("Top Ten"), 0, REG_SZ, (LPBYTE)top_ten, _tcslen(top_ten) * sizeof(TCHAR));
			_tprintf(TEXT("%s: Dados guardados no registo!\n"), SERVIDOR);
			RegCloseKey(chave);
			return 1;
		}
	}
	return 0;
}

int leRegisto(TOPTEN &topten) {

	HKEY chave;
	DWORD queAconteceu, tamanho = MAX;

	TCHAR autores[MAX];
	TCHAR meta[MAX];
	TCHAR top_ten[MAX];

	TCHAR seps[] = TEXT("=\n");
	//TCHAR teste[] = TEXT("Nuno=1000\nClaudio=20\nNuno2=10002\nClaudio2=202\n");
	TCHAR *token1 = NULL;
	TCHAR *next_token1 = NULL;

	if (RegCreateKeyEx(HKEY_CURRENT_USER, CHAVE_REG, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &sa, &chave, &queAconteceu) != ERROR_SUCCESS) {
		_tprintf(TEXT("%s: Erro ao abrir chave do registo! (%d)\n"), SERVIDOR, GetLastError());
		return -1;
	}
	else {
		if (queAconteceu == REG_OPENED_EXISTING_KEY) {

			RegQueryValueEx(chave, TEXT("Autores"), NULL, NULL, (LPBYTE)autores, &tamanho);
			autores[tamanho / sizeof(TCHAR)] = '\0';

			RegQueryValueEx(chave, TEXT("Meta"), NULL, NULL, (LPBYTE)meta, &tamanho);
			meta[tamanho / sizeof(TCHAR)] = '\0';

			RegQueryValueEx(chave, TEXT("Top Ten"), NULL, NULL, (LPBYTE)top_ten, &tamanho);
			top_ten[tamanho / sizeof(TCHAR)] = '\0';

			_tprintf(TEXT("%s: Ler do Registry:\n"), SERVIDOR);
			_tprintf(TEXT("%s: Autores: %s\n"), SERVIDOR, autores);
			_tprintf(TEXT("%s: Meta: %s\n"), SERVIDOR, meta);
			_tprintf(TEXT("%s: Topten: %s\n"), SERVIDOR, top_ten);

			token1 = _tcstok_s(top_ten, seps, &next_token1);
			int i = 0, num = 0;
			while (token1 != NULL || i < TOP_TEN)
			{
				if (token1 != NULL)
				{
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
	}
	return 0;
}

//
//TCHAR seps[] = TEXT("=\n");
//TCHAR teste[] = TEXT("Nuno=1000\nClaudio=20\nNuno2=10002\nClaudio2=202\n");
//TCHAR *token1 = NULL;
//TCHAR *next_token1 = NULL;
//
//token1 = _tcstok_s(teste, seps, &next_token1);
//int i = 0, num = 0;
//while (token1 != NULL || i < TOP_TEN)
//{
//	if (token1 != NULL)
//	{
//		//_tprintf(TEXT("[%d] token1: %s\n"), i, token1);
//		if (num % 2 == 0) {
//			/*_tprintf(TEXT("[%d] par\n"), i);*/
//			_tcscpy_s(topten.pontuacoes[i].nome, token1);
//			_tprintf(TEXT("[%d] par: %s\n"), i, topten.pontuacoes[i].nome);
//		}
//		else {
//			//_tprintf(TEXT("[%d] impar\n"), i);
//			topten.pontuacoes[i].pontos = _tstoi(token1);
//			_tprintf(TEXT("[%d] impar: %d\n"), i, topten.pontuacoes[i].pontos);
//			i++;
//		}
//		token1 = _tcstok_s(NULL, seps, &next_token1);
//		//_tprintf(TEXT("[%d] next_token1: %s\n"), i, next_token1);
//		num++;
//	}
//	else {
//		_tcscpy_s(topten.pontuacoes[i].nome, TEXT(""));
//		topten.pontuacoes[i].pontos = 0;
//		i++;
//	}
//}
