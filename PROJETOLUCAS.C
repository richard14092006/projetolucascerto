#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_PRODUTOS 100
#define MAX_ITENS 50
#define MAX_VENDAS 100

// Structs
typedef struct {
    int id;
    char nome[50];
    char cpf[15];
} Cliente;

typedef struct {
    int id;
    char nome[50];
    float preco;
    int estoque;
} Produto;

typedef struct {
    int idProduto;
    int quantidade;
    float valorUnitario;
} ItemVenda;

typedef struct {
    int idVenda;
    int idCliente;
    char data[11];
    ItemVenda itens[MAX_ITENS];
    int qtdItens;
    float total;
} Venda;

Cliente clientes[MAX_CLIENTES];
Produto produtos[MAX_PRODUTOS];
Venda vendas[MAX_VENDAS];

int qtdClientes = 0, qtdProdutos = 0, qtdVendas = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void cadastrarCliente() {
    Cliente c;
    memset(&c, 0, sizeof(Cliente));

    printf("ID do cliente: ");
    scanf("%d", &c.id);
    limparBuffer();

    printf("Nome: ");
    scanf(" %[^\n]", c.nome);
    limparBuffer();

    printf("CPF: ");
    scanf("%s", c.cpf);
    limparBuffer();

    clientes[qtdClientes++] = c;
    printf("Cliente cadastrado com sucesso!\n\n");
}

void cadastrarProduto() {
    Produto p;
    memset(&p, 0, sizeof(Produto));

    printf("ID do produto: ");
    scanf("%d", &p.id);
    limparBuffer();

    printf("Nome: ");
    scanf(" %[^\n]", p.nome);
    limparBuffer();

    printf("Preco unitario: ");
    scanf("%f", &p.preco);
    limparBuffer();

    printf("Estoque disponivel: ");
    scanf("%d", &p.estoque);
    limparBuffer();

    produtos[qtdProdutos++] = p;
    printf("Produto cadastrado com sucesso!\n\n");
}

Produto* buscarProduto(int id) {
    for (int i = 0; i < qtdProdutos; i++) {
        if (produtos[i].id == id)
            return &produtos[i];
    }
    return NULL;
}

void cadastrarVenda() {
    Venda v;
    memset(&v, 0, sizeof(Venda));

    printf("ID da venda: ");
    scanf("%d", &v.idVenda);
    limparBuffer();

    printf("ID do cliente comprador: ");
    scanf("%d", &v.idCliente);
    limparBuffer();

    printf("Data (dd/mm/aaaa): ");
    scanf("%s", v.data);
    limparBuffer();

    v.qtdItens = 0;
    v.total = 0.0;

    int continuar = 1;
    while (continuar) {
        ItemVenda item;
        memset(&item, 0, sizeof(ItemVenda));

        printf("ID do produto: ");
        scanf("%d", &item.idProduto);
        limparBuffer();

        Produto* prod = buscarProduto(item.idProduto);
        if (prod == NULL) {
            printf("Produto nao encontrado!\n");
            continue;
        }

        printf("Quantidade: ");
        scanf("%d", &item.quantidade);
        limparBuffer();

        if (item.quantidade > prod->estoque) {
            printf("Estoque insuficiente! Disponivel: %d\n", prod->estoque);
            continue;
        }

        item.valorUnitario = prod->preco;
        v.itens[v.qtdItens++] = item;

        prod->estoque -= item.quantidade;

        v.total += item.quantidade * item.valorUnitario;

        printf("Adicionar outro item? (1-Sim / 0-Nao): ");
        scanf("%d", &continuar);
        limparBuffer();
    }

    vendas[qtdVendas++] = v;

    printf("\nVenda cadastrada com sucesso!\nTotal da venda: R$ %.2f\n\n", v.total);
}

void listarClientes() {
    printf("=== Clientes Cadastrados ===\n");
    for (int i = 0; i < qtdClientes; i++) {
        printf("ID: %d | Nome: %s | CPF: %s\n", clientes[i].id, clientes[i].nome, clientes[i].cpf);
    }
    printf("\n");
}

void listarProdutos() {
    printf("=== Produtos Cadastrados ===\n");
    for (int i = 0; i < qtdProdutos; i++) {
        printf("ID: %d | Nome: %s | Preco: R$ %.2f | Estoque: %d\n",
            produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
    printf("\n");
}

void listarVendas() {
    printf("=== Vendas Realizadas ===\n");
    for (int i = 0; i < qtdVendas; i++) {
        Venda v = vendas[i];
        printf("Venda ID: %d | Cliente ID: %d | Data: %s\n", v.idVenda, v.idCliente, v.data);
        printf("Itens:\n");
        for (int j = 0; j < v.qtdItens; j++) {
            ItemVenda item = v.itens[j];
            printf(" - Produto ID: %d | Quantidade: %d | Valor Unitario: R$ %.2f\n",
                item.idProduto, item.quantidade, item.valorUnitario);
        }
        printf("Total: R$ %.2f\n\n", v.total);
    }
}

int main() {
    int opcao;

    do {
        printf("=== MENU ===\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Produto\n");
        printf("3. Cadastrar Venda\n");
        printf("4. Listar Clientes\n");
        printf("5. Listar Produtos\n");
        printf("6. Listar Vendas\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1: cadastrarCliente(); break;
            case 2: cadastrarProduto(); break;
            case 3: cadastrarVenda(); break;
            case 4: listarClientes(); break;
            case 5: listarProdutos(); break;
            case 6: listarVendas(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
