#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura Sala
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função para criar uma nova sala
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// Função para explorar as salas
void explorarSalas(Sala* salaAtual) {
    if (salaAtual == NULL) {
        return;
    }
    
    printf("\n--- Você está na: %s ---\n", salaAtual->nome);
    
    // Verifica se é uma sala final (folha)
    if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
        printf(">>> Esta é uma sala final! Não há mais caminhos a explorar.\n");
        printf("Fim da exploração nesta direção.\n");
        return;
    }
    
    // Mostra opções disponíveis
    printf("Opções de caminho:\n");
    if (salaAtual->esquerda != NULL) {
        printf("- [e] Ir para ESQUERDA (%s)\n", salaAtual->esquerda->nome);
    }
    if (salaAtual->direita != NULL) {
        printf("- [d] Ir para DIREITA (%s)\n", salaAtual->direita->nome);
    }
    printf("- [s] Sair do jogo\n");
    
    // Loop para obter uma escolha válida
    char escolha;
    int escolhaValida = 0;
    
    while (!escolhaValida) {
        printf("\nPara onde deseja ir? ");
        scanf(" %c", &escolha);
        
        switch (escolha) {
            case 'e':
            case 'E':
                if (salaAtual->esquerda != NULL) {
                    explorarSalas(salaAtual->esquerda);
                    escolhaValida = 1;
                } else {
                    printf("Não há caminho à esquerda!\n");
                }
                break;
                
            case 'd':
            case 'D':
                if (salaAtual->direita != NULL) {
                    explorarSalas(salaAtual->direita);
                    escolhaValida = 1;
                } else {
                    printf("Não há caminho à direita!\n");
                }
                break;
                
            case 's':
            case 'S':
                printf("Saindo do jogo...\n");
                return;
                
            default:
                printf("Opção inválida! Use 'e' para esquerda, 'd' para direita ou 's' para sair.\n");
                break;
        }
    }
}

// Função para liberar a memória da árvore
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

// Função principal
int main() {
    printf("=== DETECTIVE QUEST ===\n");
    printf("Bem-vindo à mansão misteriosa!\n");
    printf("Explore os cômodos para encontrar pistas...\n\n");
    
    // Montagem do mapa da mansão (árvore binária)
    printf("Criando mapa da mansão...\n");
    
    // Criando todas as salas
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");
    Sala* escritorio = criarSala("Escritório");
    Sala* quarto = criarSala("Quarto Principal");
    Sala* porao = criarSala("Porão");
    
    // Montando a estrutura da árvore
    // Hall de Entrada -> Sala de Estar (esquerda) e Cozinha (direita)
    hallEntrada->esquerda = salaEstar;
    hallEntrada->direita = cozinha;
    
    // Sala de Estar -> Biblioteca (esquerda) e Jardim (direita)
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    
    // Cozinha -> Escritório (esquerda) e Quarto Principal (direita)
    cozinha->esquerda = escritorio;
    cozinha->direita = quarto;
    
    // Biblioteca -> Porão (esquerda) apenas
    biblioteca->esquerda = porao;
    
    // Iniciar exploração a partir do Hall de Entrada
    explorarSalas(hallEntrada);
    
    // Liberar memória alocada
    liberarArvore(hallEntrada);
    
    printf("\nObrigado por jogar Detective Quest!\n");
    printf("Esperamos que tenha encontrado boas pistas!\n");
    
    return 0;
}