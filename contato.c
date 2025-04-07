#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 50
#define MAX_NOME 128
#define MAX_TELEFONE 15
#define ARQUIVO "agenda.csv"

typedef struct {
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];
} Contato;

Contato agenda[MAX_CONTATOS];
int totalContatos =0;
int alterado =0;

void carregarContatos(){
    FILE *file=fopen(ARQUIVO,"r");
    if (!file) return;

    while (fscanf(file, " %127[^,],%14[^\n]\n", agenda[totalContatos].nome, agenda[totalContatos].telefone) == 2) {
        totalContatos++;
        if (totalContatos>=MAX_CONTATOS) 
        break;
    }
    fclose(file);
}

void salvarContatos(){
    FILE *file=fopen(ARQUIVO,"w");
    if (!file){
        printf("erro ao salvar\n");
        return;
    }
    for (int i=0; i<totalContatos;i++){
        fprintf(file,"%s,%s\n", agenda[i].nome, agenda[i].telefone);
    }
    fclose(file);
    alterado=0;
    printf("Seus contatos foram salvos\n");
}

void adicionarContato(){
    if (totalContatos>=MAX_CONTATOS){
        printf("Agenda cheia\n");
        return;
    }
    printf("Nome: ");
    scanf(" %[^\n]", agenda[totalContatos].nome);  
    printf("Telefone (ex: 63 99999-9999): ");
    scanf(" %[^\n]", agenda[totalContatos].telefone);
    totalContatos++;
    alterado=1;
}

void imprimirAgenda(){
    if (totalContatos==0){
        printf("Agenda vazia\n");
        return;
    }
    printf("Contatos na Agenda:\n");
    for (int i=0; i<totalContatos;i++){
        printf("%d %s - %s\n\n", i+1, agenda[i].nome, agenda[i].telefone);
    }
}

void deletarContato(){
    char nome[MAX_NOME];
    printf("Nome a deletar: ");
    scanf(" %[^\n]", nome);
    for (int i=0; i<totalContatos;i++) {
        if (strcmp(agenda[i].nome, nome)==0){
            for (int j=i; j<totalContatos-1; j++){
                agenda[j]=agenda[j+1];
            }
            totalContatos--;
            alterado = 1;
            printf("Contato removido\n");
            return;
        }
    }
    printf("Contato nao encontrado\n");
}

int main(){
    int opcao;
    carregarContatos();

    do {
        printf("1 - adicionar novo contato\n");
        printf("2 - imprimir agenda\n");
        printf("3 - deletar contato\n");
        printf("4 - salvar contatos\n");
        printf("5 - sair\n");
        scanf("%d",&opcao);

        switch (opcao){
            case 1:
                adicionarContato();
                break;
            case 2:
                imprimirAgenda();
                break;
            case 3:
                deletarContato();
                break;
            case 4:
                salvarContatos();
                break;
            case 5:
                if (alterado){
                    printf("deseja salvar suas alterações? (s/n): ");
                    char resposta;
                    scanf(" %c",&resposta);
                    if(resposta=='s'){
                        salvarContatos();
                    }
                }
                printf("Saindo\n");
                break;
        }
    } while (opcao!=5);
    return 0;
}
