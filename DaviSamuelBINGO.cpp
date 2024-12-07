#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

class cartela {
    public:
    string espacos[5][5];
    string nome;
    int numeracao = 1;
}; 

// Função para criar as cartelas de bingo
void criarCARTELA(vector<cartela> &cartelas, string dono, int contador, int num) {
    for(int qnt=0;qnt<contador;++qnt){
        cartela c;
        c.nome = dono;
        c.numeracao = num;
        
        // Preenche as cartelas com números aleatórios
        for (int y = 0; y < 5; ++y) {
            vector<int> numeros;
            int min = y * 15 +1;
            int max = y * 15 + 15;
            
            for (int i = min; i <= max; ++i){
                numeros.push_back(i);
            }
            
            random_shuffle(numeros.begin(), numeros.end());
            
            for (int x=1;x<5;++x){
                c.espacos[x][y] = to_string(numeros.back());
                numeros.pop_back();
            }
        }
        
        // Cabeçalho da cartela
        c.espacos[0][0] = "B ";
        c.espacos[0][1] = "I ";
        c.espacos[0][2] = "N ";
        c.espacos[0][3] = "G ";
        c.espacos[0][4] = "O ";
        
        // Marca o espaço central como livre (X)
        c.espacos[2][2] = "X";
        cartelas.push_back(c);
        num++;
    }
}

// Função para exibir as cartelas de um jogador
void exibirCARTELA(const vector<cartela> &cartelas, const string &nome) {
    bool nomeado = false;
    for (const cartela &c : cartelas) {
        if (c.nome  == nome){
            nomeado = true;
            cout << "Cartela de " << c.nome << ":\n";
            
            // Exibe a cartela
            for (int x = 0; x < 5; ++x) {
                for (int y = 0; y < 5; ++y) {
                    cout << c.espacos[x][ y] << " |";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    
    // Caso o nome não seja encontrado
    if (!nomeado){
        cout << "OPS! acho que esse nome não foi registrado... Tente novamente!";
    }
}

// Função para iniciar o jogo de BINGO
void iniciarBINGO(vector<cartela> &cartelas, const string &nome) {
    bool nomeado = false;
    vector<cartela> cartelasJOGO;  // Vetor para armazenar as cartelas selecionadas para o jogo
    int numeroCARTELA;
    int qntCARTELA;
    int numSELECIONADO;
    
    // Verifica se o nome fornecido existe nas cartelas registradas
    for (const cartela &c: cartelas) {
        if (c.nome == nome){
            nomeado = true;
        }
    }
    
    if (!nomeado) {
        cout << "OPS! Acho que esse nome não foi registrado... Tente novamente!";
    }

    // Solicita a quantidade de cartelas para o jogo
    cout << "Digite a quantidade de cartelas que deseja usar no BINGO \n";
    cin >> qntCARTELA;
    
    // Exibe as cartelas disponíveis para o jogador
    for (int i = 0; i < qntCARTELA; ++i) {
        // Loop de seleção de cartela
    }

    // Exibe as cartelas do jogador com o nome informado
    for (const cartela &c : cartelas) {
        if (c.nome == nome) {
            nomeado = true;
            cout << "Cartela Nº " << c.numeracao << ":\n";
            for (int x = 0; x < 5; ++x) {
                for (int y = 0; y < 5; ++y) {
                    cout << c.espacos[x][y] << " |";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    // Solicita ao jogador a escolha das cartelas para o jogo
    for (int i = 0; i < qntCARTELA; ++i) {
        cout << "Digite o número da cartela que deseja usar (" << i+1 << " de " << qntCARTELA << "): ";
        cin >> numSELECIONADO;

        bool encontrada = false;
        for (const cartela &c : cartelas) {
            if (c.nome == nome && c.numeracao == numSELECIONADO) {
                cartelasJOGO.push_back(c);
                encontrada = true;
                break;
            }
        }
    }
    
    // Exibe as cartelas selecionadas para o BINGO
    cout << "Cartelas selecionadas para o BINGO:\n";
    for (const cartela &c : cartelasJOGO) {
        cout << "Cartela Nº " << c.numeracao << " de " << c.nome << ":\n";
        for (int x = 0; x < 5; ++x) {
            for (int y = 0; y < 5; ++y) {
                cout << c.espacos[x][y] << " |";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Inicializa variáveis para o loop do jogo
    int rodadas = 0;
    int opJOGO;
    int numeroCHAMADO;
    vector<int> sorteados;

    do {
        // Sorteia um número aleatório
        do {
            numeroCHAMADO = rand() % 75 + 1;
        } while (find(sorteados.begin(), sorteados.end(), numeroCHAMADO) != sorteados.end());

        sorteados.push_back(numeroCHAMADO); // Armazena o número sorteado

        cout << "Número sorteado: " << numeroCHAMADO << " \n";

        // Exibe as cartelas para o jogador verificar
        for (const cartela &c : cartelasJOGO) {
            cout << "Confira sua(s) cartela(s) "  << c.nome << ":\n";
            for (int x = 0; x < 5; ++x) {
                for (int y = 0; y < 5; ++y) {
                    cout << c.espacos[x][y] << " |";
                }
                cout << endl;
            }
            cout << endl;
        }

        // Menu de opções durante o jogo
        cout <<"      JOGO-MENU        \n";
        cout <<"_______________________\n";
        cout <<"  [1] - Marcar Cartela \n";
        cout <<"  [2] - Próximo número \n";
        cout <<"  [3] - Desistir       \n";
        cout <<"_______________________\n";
        cout <<"Escolha uma opção:     \n";
        cin >> opJOGO;

        // Opções do menu
        switch(opJOGO){
            case 1:{
                // Exibe as cartelas para marcar o número sorteado
                for (const cartela &c : cartelasJOGO) {
                    cout << "Cartela Nº " << c.numeracao << "\n";
                    for (int x = 0; x < 5; ++x) {
                        for (int y = 0; y < 5; ++y) {
                            cout << c.espacos[x][y] << " |";
                        }
                        cout << endl;
                    }
                    cout << endl;
                }

                bool numeroCHECADO = false;
                string numeroDIGITADO;
                string numeroSORTEADO = to_string(numeroCHAMADO);
                bool check = false;
                
                // Solicita ao jogador digitar o número sorteado para marcar
                do {
                    cout <<"Digite o número sorteado " << numeroSORTEADO << " para marcar suas Cartelas: ";
                    cin >> numeroDIGITADO;
                    if (numeroDIGITADO != numeroSORTEADO) {
                        cout <<"Esse não é o número sorteado... Tente novamente \n";
                    }
                } while(numeroDIGITADO != numeroSORTEADO);
                
                // Marca o número sorteado nas cartelas
                for (cartela &c: cartelasJOGO) {
                    for (int x = 0; x < 5; ++x) {
                        for (int y = 0; y < 5; ++y) {
                            if (c.espacos[x][y] == numeroDIGITADO) {
                                c.espacos[x][y] = 'X';
                                check = true;
                                numeroCHECADO = true;
                            }
                        }
                    }
                }

                // Verifica se o jogador fez BINGO ou uma linha/coluna
                for (cartela &c: cartelasJOGO) {
                    if (numeroCHECADO) {
                        bool LINHA = false;
                        bool COLUNA = false;
                        bool BINGO = false;
                        bool olhaBOA = false;

                        // Verifica linha
                        for (int x = 0; x < 5; ++x) {
                            int contLINHA = 0;
                            for (int y = 0; y < 5; ++y) {
                                if (c.espacos[x][y] == "X") contLINHA++;
                            }
                            if (contLINHA == 5) LINHA = true;
                            if (contLINHA == 4) olhaBOA = true; // Quase preenchida
                        }

                        // Verifica coluna
                        for (int y = 0; y < 5; ++y) {
                            int contCOLUNA = 0;
                            for (int x = 0; x < 5; ++x) {
                                if (c.espacos[x][y] == "X") contCOLUNA++;
                            }
                            if (contCOLUNA == 5) COLUNA = true;
                            if (contCOLUNA == 4) olhaBOA = true;
                        }

                        // Verifica BINGO
                        for (int x = 0; x < 5; ++x) {
                            for (int y = 0; y < 5; ++y) {
                                if (c.espacos[x][y] != "X") {
                                    BINGO = false;
                                }
                            }
                        }

                        // Exibe as mensagens de BINGO ou progresso
                        if (BINGO) {
                            cout << "BINGO! Cartela " << c.numeracao << " está cheia!\n";
                            rodadas = 90;
                        } else if (LINHA) {
                            cout << "LINHA! Uma linha foi preenchida na cartela " << c.numeracao << ".\n";
                            rodadas = 90;
                        } else if (COLUNA) {
                            cout << "COLUNA! Uma coluna foi preenchida na cartela " << c.numeracao << ".\n";
                            rodadas = 90;
                        } else if (olhaBOA) {
                            cout << "Olha a boa! Falta apenas um número para marcar na cartela " << c.numeracao << ".\n";
                        }
                    }
                }
               }break;
            
            case 2:{
                // Opção para passar para o próximo número
                }break;
            
            case 3:{
                cout << "XIIIII, até a próxima então \n ";
                rodadas = 90;
                }break;
            
            default:
                cout <<"OPS! Acho que essa opção não existe, tente novamente \n";
        }

    } while (rodadas < 90);

    // Agradecimento ao final do jogo
    cout << "Obrigado por Jogar :D \n";
}

// Função principal para o menu do jogo de Bingo
int main() {
    vector<cartela> cartelas;  // Vetor que armazena as cartelas dos jogadores
    string nomeJOGADOR;        // Nome do jogador que cria a cartela ou participa do jogo
    string nomeBUSCAR;         // Nome do jogador para buscar suas cartelas ou iniciar o jogo
    int quantidade;            // Quantidade de cartelas a serem criadas
    int proximaNUMERACAO;      // Numeração da próxima cartela
    int op;                     // Opção escolhida pelo jogador no menu
    int vezes = 0;             // Variável para controlar o número de iterações do loop

    // Loop do menu principal do jogo
    do {
        cout << "      BINGO-MENU       \n";
        cout << "_______________________\n";
        cout << "  [1] - Criar Cartela  \n";
        cout << "  [2] - Ver cartelas   \n";
        cout << "  [3] - Iniciar Jogo   \n";
        cout << "  [4] - Sair           \n";
        cout << "_______________________\n";
        cout << "Escolha uma opção:     \n";
        cin >> op;

        // Switch para escolher a opção do menu
        switch(op) {
            case 1:  // Caso para criar cartelas
                cout << "Digite o nome do jogador: \n";
                cin.ignore();
                getline(cin, nomeJOGADOR);

                cout << "Digite a quantidade de cartelas a gerar: \n";
                cin >> quantidade;

                criarCARTELA(cartelas, nomeJOGADOR, quantidade, cartelas.size() + 1);  // Chama a função para criar as cartelas
                cout << "Cartelas criadas com sucesso! \n"; 
                break;

            case 2:  // Caso para visualizar as cartelas de um jogador
                cout << "Digite o nome do jogador para exibir as cartelas: \n";
                cin.ignore();
                getline(cin, nomeBUSCAR);
                
                exibirCARTELA(cartelas, nomeBUSCAR);  // Chama a função para exibir as cartelas do jogador
                break;

            case 3:  // Caso para iniciar o jogo de Bingo
                cout << "Digite o nome do jogador que irá jogar: \n";
                cin.ignore();
                getline(cin, nomeBUSCAR);
                
                iniciarBINGO(cartelas, nomeBUSCAR);  // Chama a função para iniciar o jogo
                break;
            
            case 4:  // Caso para sair do jogo
                cout << "Saindo do Bingo... \n";
                vezes = 30;  // Finaliza o loop ao definir vezes como 30
                break;

            default:  // Caso para uma opção inválida
                cout << "OPS! Acho que essa opção não existe, tente novamente \n";
        }
        
        vezes++;  // Incrementa o número de iterações do loop
    } while(vezes < 30);  // Continua até que o jogador escolha sair

    cout << "Obrigado e até a próxima! :) \n";  // Mensagem final após sair do loop

    return 0;  // Retorno da função principal
}
