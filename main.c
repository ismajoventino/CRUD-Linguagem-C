#include <stdio.h>
#include <string.h>
#include <locale.h>

# define MAX 10000

// Estrutura para representar um Produto
typedef struct {	
	int id;
	char nomeProduto[50];
	float preco;
	int quantidade;
	char dataValidade[20];
	char categoria[20];
	char fornecedor[50];
} Produto;

// Função para cadastrar um novo produto
void cadastrarProduto(Produto produtos[], int* contador) {
    if (*contador >= MAX) {
        printf("ERRO: Quantidade de produtos em estoque excedida!\n");
        return;
    }

    Produto novoProduto;

    printf("------------------------------ \n");
    printf("ID do Produto: \n");
    scanf("%d", &novoProduto.id);
    getchar();

    printf("Nome do Produto: \n");
    scanf("%[^\n]", novoProduto.nomeProduto);
    getchar();

    printf("Quantidade: \n");
    scanf("%d", &novoProduto.quantidade);
    getchar();

    printf("Preço do Produto: \n");
    scanf("%f", &novoProduto.preco);
    getchar();

    printf("Fornecedor do Produto: \n");
    scanf("%[^\n]", novoProduto.fornecedor);
    getchar();

    printf("Validade do Produto (se aplicável, senão deixe em branco): \n");
    scanf("%[^\n]", novoProduto.dataValidade);
    getchar();

    printf("Categoria: \n");
    scanf("%[^\n]", novoProduto.categoria);
    getchar();

    produtos[*contador] = novoProduto;
    (*contador)++;
    printf("Produto cadastrado com sucesso!\n");
    printf("------------------------------ \n");
}

// Função para consultar produtos por categoria
void consultarPorCategoria(Produto produtos[], int contador) {
    if (contador == 0) {
        printf("---------------------\n");
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    char categoriaDesejada[20];
    printf("---------------------\n");
    printf("Digite a categoria que deseja consultar: ");
    scanf("%[^\n]", categoriaDesejada);
    getchar();
    printf("---------------------\n");

    int produtosEncontrados = 0;
    int i;
    for (i = 0; i < contador; i++) {
        if (strcmp(produtos[i].categoria, categoriaDesejada) == 0) {
            printf("ID: %d\n", produtos[i].id);
            printf("Nome: %s\n", produtos[i].nomeProduto);
            printf("Preço: %.2f\n", produtos[i].preco);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Validade: %s\n\n", produtos[i].dataValidade);
            printf("Categoria: %s\n", produtos[i].categoria);
            printf("Fornecedor: %s\n", produtos[i].fornecedor);
            printf("---------------------\n");
            produtosEncontrados++;
        }
    }

    if (produtosEncontrados == 0) {
        printf("Nenhum produto encontrado na categoria '%s'.\n", categoriaDesejada);
        printf("---------------------\n");
    }
}

// Função para consultar todos os produtos ou por categoria
void consultarProdutos(Produto produtos[], int contador) {
    int escolhaConsulta;
    printf("---------------------\n");
    printf("1. Consultar todos os produtos\n");
    printf("2. Consultar por categoria\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolhaConsulta);
    getchar();
    printf("---------------------\n");

    switch(escolhaConsulta) {
        case 1:
            // Código para listar todos os produtos
            break;
        case 2:
            consultarPorCategoria(produtos, contador);
            break;
        default:
            printf("Opção inválida.\n");
            printf("---------------------\n");
            break;
    }
}

// Função para alterar os dados de um produto
void alterarProduto(Produto produtos[], int contador) {
    if (contador == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    int idAlteracao;
    printf("---------------------\n");
    printf("Digite o ID do produto que deseja alterar: \n");
    scanf("%d", &idAlteracao);
    getchar();

    int encontrado = 0;
    int i;
    for (i = 0; i < contador; i++) {
        if (produtos[i].id == idAlteracao) {
            encontrado = 1;

            printf("Dados atuais do produto:\n");
            printf("ID: %d\n", produtos[i].id);
            printf("Nome: %s\n", produtos[i].nomeProduto);
            printf("Preço: %.2f\n", produtos[i].preco);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Validade: %s\n", produtos[i].dataValidade);
            printf("Categoria: %s\n", produtos[i].categoria);
            printf("Fornecedor: %s\n", produtos[i].fornecedor);

            printf("\nDigite o novo nome (ou mantenha o mesmo): ");
            scanf("%[^\n]", produtos[i].nomeProduto);
            getchar();

            printf("Digite a nova quantidade (ou mantenha a mesma): ");
            scanf("%d", &produtos[i].quantidade);
            getchar();

            printf("Digite o novo preço (ou mantenha o mesmo): ");
            scanf("%f", &produtos[i].preco);
            getchar();

            printf("Digite a nova validade (ou mantenha a mesma): ");
            scanf("%[^\n]", produtos[i].dataValidade);
            getchar();

            printf("Digite a nova categoria (ou mantenha a mesma): ");
            scanf("%[^\n]", produtos[i].categoria);
            getchar();

            printf("Digite o novo fornecedor (ou mantenha o mesmo): ");
            scanf("%[^\n]", produtos[i].fornecedor);
            getchar();

            printf("Dados do produto atualizados com sucesso!\n");
            printf("---------------------\n");

            break;
        }
    }

    if (!encontrado) {
        printf("Produto com ID %d não encontrado.\n", idAlteracao);
        printf("---------------------\n");
    }
}

// Função para deletar um produto
void deletarProduto(Produto produtos[], int* contador) {
    if (*contador == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    int idDelecao;
    printf("---------------------\n");
    printf("Digite o ID do produto que deseja deletar: \n");
    scanf("%d", &idDelecao);
    getchar();

    int index = -1;
    int i;
    for (i = 0; i < *contador; i++) {
        if (produtos[i].id == idDelecao) {
            index = i;
            break;
        }
    }

    if (index != -1) {
    	int j;
        for (j = index; j < (*contador) - 1; j++) {
            produtos[j] = produtos[j + 1];
        }
        (*contador)--;
        printf("Produto com ID %d excluído com sucesso!\n", idDelecao);
        printf("---------------------\n");
    } else {
        printf("Produto com ID %d não encontrado.\n", idDelecao);
        printf("---------------------\n");
    }
}

// Função para salvar os produtos em um arquivo
void salvarProdutos(Produto produtos[], int contador) {
    FILE *fp = fopen("produtos.txt", "w");

    if (!fp) {
        printf("Erro ao abrir o arquivo para gravação.\n");
        return;
    }
    int i = 0;
    for (i = 0; i < contador; i++) {
        fprintf(fp, "%d,%s,%f,%d,%s,%s,%s\n", 
            produtos[i].id, produtos[i].nomeProduto, produtos[i].preco,
            produtos[i].quantidade, produtos[i].dataValidade, produtos[i].categoria, produtos[i].fornecedor);
    }

    fclose(fp);
}

// Função para carregar os produtos de um arquivo
int carregarProdutos(Produto produtos[]) {
    FILE *fp = fopen("produtos.txt", "r");

    if (!fp) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }

    int contador = 0;
    while (fscanf(fp, "%d,%49[^,],%f,%d,%19[^,],%19[^,],%49[^\n]", 
            &produtos[contador].id, produtos[contador].nomeProduto, &produtos[contador].preco,
            &produtos[contador].quantidade, produtos[contador].dataValidade, produtos[contador].categoria, produtos[contador].fornecedor) != EOF) {
        contador++;
    }

    fclose(fp);
    return contador;
}

// Função principal
int main() {
	setlocale(LC_ALL, "Portuguese");

	Produto produtos[MAX];
	int numeroProdutos = 0;
	int escolha;

	numeroProdutos = carregarProdutos(produtos);

	do {
    	printf("MENU \n");
    	printf("\n");
	    printf("1. Cadastrar Produto \n");
	    printf("2. Consultar Produto \n");
    	printf("3. Alterar Produto \n");
    	printf("4. Deletar Produto \n");
    	printf("0. Sair \n");
    	scanf("%d", &escolha);
    	getchar();

    	switch (escolha) {
            case 1:
               cadastrarProduto(produtos, &numeroProdutos);
               break;
            case 2:
               consultarProdutos(produtos, numeroProdutos);
               break;
            case 3:
               alterarProduto(produtos, numeroProdutos);
               break;
            case 4:
               deletarProduto(produtos, &numeroProdutos);
               break;
        }
    } while (escolha != 0);
    salvarProdutos(produtos, numeroProdutos);
	return 0;
}

