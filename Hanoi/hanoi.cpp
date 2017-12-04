#include <iostream>
#include <vector>
#include <string>

using namespace std;

int numDiscos, numTorres, medio;

void imprimirPinos(vector<vector<int>> pinos)
{
	for (int i = numDiscos - 1; i >= 0; i--) {
		for (int j = 0; j < numTorres; j++) {
			int tamanho = pinos[j].size() - 1;
			if (tamanho >= i)
				cout << pinos[j][i] << " ";
			else
				cout << "0" << " ";
		}
		cout << endl;
	}
}

int jogar(int origem, int destino, vector<int> &topo, vector<vector<int>> &pino)
{
	if (origem > numTorres || destino < 0 || destino > numTorres)
		return -1;


	if ( ((topo[destino] < topo[origem]) && topo[destino] > 0) || (topo[origem] == 0) || origem == destino)
		return - 2;

	topo[destino] = topo[origem];
	pino[destino].push_back(topo[destino]);

	pino[origem].pop_back();
	if (pino[origem].empty() == false)
		topo[origem] = pino[origem].back();
	else
		topo[origem] = 0;

	if (pino[medio].size() == numDiscos)
		return 1;

	return 0;
}

int main() {
	cin >> numTorres >> numDiscos;

	vector<int> topo(numTorres, 0);

	vector<vector<int>> pinos (numTorres, vector<int>(0));

	medio = numTorres / 2;

	for (int i = 0; i < numDiscos; i++)
	{
		int temp;
		cin >> temp;
		pinos[temp-1].push_back(numDiscos - i);

		// inicializar topo
		if (topo[temp - 1] < pinos[temp - 1].back())
			topo[temp - 1] = pinos[temp - 1].back();
	}

	int qtdJogadas, destino, origem;
	cin >> qtdJogadas;

	imprimirPinos(pinos);
	bool win = false;
	for (int i = 0; i < qtdJogadas; i++)
	{
		cout << endl;
		cin >> origem >> destino;

		switch (jogar(origem-1, destino-1, topo, pinos))
		{
		case -1:
			cout << "Tanto o pino de origem como o pino de destino devem ser valores de 1 a " << numTorres << endl;
			i--;
			break;
		case -2:
			cout << "Jogada nao permetida" << endl;
			i--;
			break;
		case 1:
			cout << "Movendo o disco da torre " << origem << " para torre " << destino << endl;
			win = true;
			break;
		default:
			cout << "Movendo o disco da torre " << origem << " para torre " << destino << endl;
			break;
		}

		cout << endl;
		imprimirPinos(pinos);

		if (win) {
			cout << endl;
			cout << "Voce ganhou com " << i+1 << " jogada(s)" << endl;
			exit(0);
		}
	}

	cout << endl;
	cout << "Jogadas esgotadas" << endl;
	
	return 0;
}
