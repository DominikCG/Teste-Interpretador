#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <fstream>
using namespace std;


int main() {
	string text;
	string name;
	string value;
	string s_aux;
	string aux_flag = "representa";
	string valem_aux = "valem";
	bool qnt = false, qnts = false, vl = false, crd = false, au = false, ag = false, fe = false, perg = false,valem = false;//
	list<string> names, values, flags, lines;
	list<int> uni,aux_cred;
	bool isNumber = false, check = false,calc = false;
	int aux = 0;
	float vau = 0, vag = 0, vfe = 0;
	float a=0, b=0, c=0;
	stringstream ss;
	ifstream txtOpen("Text.txt", std::ofstream::out);

	if (!txtOpen.is_open()) {
		cout << "erro ao procurar o arquivo de texto" << endl;
		return 1;
	}
	while (getline(txtOpen, text))
	{
		ss.str("");
		//lista de linhas
		lines.push_back(text);
		//teste de linhas para numeros
		if (aux < 7) {
			for (int j = text.size() - 1; j >= 0; j--)
			{

				//teste para ver se é elegivem a linha como parametro para valores
				if (text[j] == 'I' || text[j] == 'V' || text[j] == 'X' || text[j] == 'L' || text[j] == 'C' || text[j] == 'D' || text[j] == 'M') {

					value = text[j];

					isNumber = true;
					break;
				}
			}

			for (int i = 0; i < text.size(); i++) {

				if (text[i] != ' ')
					ss << text[i];

				if (text[i] == ' ' && check) {
					s_aux = ss.str();

					ss.str("");
					check = false;

				}
				if (text[i] == ' ' && isNumber) {
					name = ss.str();

					//cout << name << " " << value << endl;
					isNumber = false;
					ss.str("");
					check = true;

				}

			}
			if (s_aux == aux_flag) {
				values.push_back(value);
				names.push_back(name);
				flags.push_back(s_aux);
			}
			aux++;
			name.clear();
			value.clear();
			s_aux.clear();
		}

	}
	txtOpen.close();


	//fazer uma leitura procuranto "quanto " "vale" "quantos" "creditos" "nome do metal" "?" ...
	for (int i = 0; i < lines.size(); i++)
	{
		//reset de variaveis e listas para cada linha
		ss.clear();
		ss.str("");
		std::list<string>::iterator l = lines.begin();
		advance(l, i);
		s_aux.clear();
		uni.clear();
		aux_cred.clear();
		s_aux = *l;
		for (int j = 0; j < s_aux.size(); j++)
		{

			if (s_aux[j] != ' ') {
				ss << s_aux[j];
			}
			if (s_aux[j] == ' ' || s_aux[j] == '?') {
				//testa e salva o numero de creditos para conversao de valores em galactico
				if (isNumber && valem) {
					int x;
					string testnumber;
					ss >> testnumber;
					bool n = (testnumber.find_first_not_of("0123456789") == std::string::npos);
					if (n) {
						x = atoi(ss.str().c_str());
						aux_cred.push_back(x);
						calc = true;
					}
				}
				//testa palavra com nomes de valores e cria uma lista ordenada para conversao posterior
				for (int k = 0; k < names.size(); k++)
				{
					std::list<string>::iterator n = names.begin();
					advance(n, k);
					std::list<string>::iterator v = values.begin();
					if (ss.str() == *n) {
						advance(v, k);
						if (*v == "I")
							uni.push_back(1);
						if (*v == "V")
							uni.push_back(5);
						if (*v == "X")
							uni.push_back(10);
						if (*v == "L")
							uni.push_back(50);
						if (*v == "C")
							uni.push_back(100);
						if (*v == "D")
							uni.push_back(500);
						if (*v == "M")
							uni.push_back(1000);
						isNumber = true;
					}
				}
				//teste de palavras chave
				if (ss.str() == "valem" && au||ag||fe)
					valem = true;
				if (ss.str() == "quanto" && !qnts)
					qnt = true;
				if (ss.str() == "quantos" && !qnt)
					qnts = true;
				if (ss.str() == "vale" && qnt)
					vl = true;
				if (ss.str() == "creditos" || ss.str() == "créditos" )
					crd = true;
				if (ss.str() == "Ouro" || ss.str() == "Gold"  && !ag && !fe)
					au = true;
				if (ss.str() == "Prata" || ss.str() == "Silver"  && !au && !fe)
					ag = true;
				if (ss.str() == "Ferro" || ss.str() == "Iron"  && !au && !ag)
					fe = true;
				if (s_aux[j] == '?')
					perg = true;

				ss.clear();
				ss.str("");
			}



		}
		ss.clear();
		ss.str("");
		//tratamento para perguntas

		if (isNumber)
		{

			for (int l = 0; l < uni.size(); l++)//faz calculo de conversao de galactico para decimal
			{
				std::list<int>::iterator u = uni.begin();
				advance(u, l);
				if (l == 0) {
					a = *u;
				}
				else {
					b = *u;
					if (a < b) {
						c = b - a;
						a = b;
					}
					else {
						//tratamento para metais
						if (au || ag || fe) {
							c = a+b;
						}
						else //tratamento para numeros , implementar teste de validação para fazer calculos corretos de numeros apropriadamente
						{
							c += b;
						}
							a = b;
					}
				}


			}
			if (isNumber && valem && !perg)
			{//identifica a quantidade de metais e retorna a quantidade em creditos
				if (au) {
					std::list<int>::iterator aux_au = aux_cred.begin();
					a = *aux_au;
					vau = a/c;
				}
				else if (ag) {
					std::list<int>::iterator aux_ag = aux_cred.begin();
					a = *aux_ag;
					vag = a/c;
				}
				else if (fe) {
					std::list<int>::iterator aux_fe = aux_cred.begin();
					a = *aux_fe;
					vfe = a/c;
				}
			}
		}
		if (perg) {


			//respostas para perguntas
				if (qnts && crd && au) {

					b = c * vau ;
					cout << "o valor de " << c << "unidades de ouro e " << b << " creditos" << endl;
				}
				else if (qnts && crd && ag) {

					b = c * vag;
					cout << "o valor de " << c << "unidades de prata e " << b << " creditos" << endl;
				}
				else if (qnts && crd && fe) {

					b = c * vfe;
					cout << "o valor de "<<c<<"unidades de ferro e " << b << " creditos" << endl;
				}
				else if(qnt && vl && isNumber) {
					cout << "a quantidade da conversao e " << c << endl;
				}
				else {
					cout << "nao entendi a pergunta." << endl;
				}


		}

		isNumber = false, valem = false,calc = false;
		qnt = false, qnts = false, vl = false, crd = false, au = false, ag = false, fe = false, perg = false;
		
	}

	return 0;
}
