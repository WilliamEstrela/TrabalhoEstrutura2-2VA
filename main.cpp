#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

typedef struct{
    int matricula;
    char nome[24];
    char curso[24];
}Info;

typedef struct tree
{
    Info* info;
    struct tree* esq;
    struct tree* dir;
} Tree;

Tree* createTree(){
    return NULL;
}

int treeIsEmpty(Tree* t){
    return t == NULL;
}

void showTree(Tree* t){
    if(t != NULL){
        showTree(t->dir);
        printf("\n%s", t->info->nome);
        printf("\n%i", t->info->matricula);
        printf("\n%s", t->info->curso);
        showTree(t->esq);
    }
}


void insereOrdenadoMatricula(Tree** t, Info* usuario){

    if(*t == NULL){
        *t = (Tree*)malloc(sizeof(Tree));
        (*t)->dir = NULL;
        (*t)->esq = NULL;
        (*t)->info = usuario;
    } else {
        if(usuario->matricula < (*t)->info->matricula){
            insereOrdenadoMatricula(&(*t)->dir, usuario);
        }
        if(usuario->matricula > (*t)->info->matricula){
            insereOrdenadoMatricula(&(*t)->esq, usuario);
        }
    }
}

void insereOrdenadoNome(Tree** t, Info* usuario){
    if(*t == NULL){
        *t = (Tree*)malloc(sizeof(Tree));
        (*t)->dir = NULL;
        (*t)->esq = NULL;
        (*t)->info = usuario;
    } else {
        if(strcmp(usuario->nome, (*t)->info->nome) < 0){
            insereOrdenadoNome(&(*t)->dir, usuario);
        }else{
            insereOrdenadoNome(&(*t)->esq, usuario);
        }
    }
}


int isInTree(Tree* t, int matricula) {

    if(treeIsEmpty(t)) {
        return 0;
    }
    return t->info->matricula == matricula || isInTree(t->dir, matricula) || isInTree(t->esq, matricula);
}

int buscaPorMatricula(Tree * t, Info * entrada){ // faz a busca na �rvore por matr�cula

    if(t != NULL){
        buscaPorMatricula(t->esq, entrada);

        if(t->info->matricula == entrada->matricula){
            printf("\nBusca por Matr�cula: ");
            printf("Nome: %s | Matr�cula:%d | Curso:%s \n\n", t->info->nome, t->info->matricula, t->info->curso);
            return 1;
        }
        buscaPorMatricula(t->dir, entrada);
    }
    else{
        return 0;
    }

}
Tree * remove_atual(Tree * atual){
    Tree* no1;
    Tree* no2;
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }

    no1= atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }

    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }

    no2->dir = atual->dir;
    free(atual);
    return no2;
}

Tree* removeRaiz(Tree* r){

    Tree *p, *q;
    if(r->esq == NULL)//raiz n�o possui filho a esquerda
        q = r->dir;//filho a direita passa a ser a raiz
    else{
        p = r; q = r->esq;
        while(q->dir != NULL){//busca maior valor da direita
            p = q; q = q->dir;
        }
        if(p != r){
            q->esq = r->esq;//atualiza nova esquerda de q (raiz)
            p->dir = NULL;//atualiza nova direita de p
        }
        q->dir = r->dir;//conecta a direita da �rvore na nova raiz
    }

    free(r);
    return q;

}

int removerPorNome(Tree **t, Info* entrada, Tree **t_mat, int cont);
int removerPorMatricula(Tree **t, int matricula, Tree **t_nom, int cont){ // remove o noh por matr�cula

    if(t == NULL) return 0;
    Tree* ant= NULL;
    Tree* atual= *t;
    while(atual != NULL){
        if(matricula == atual->info->matricula){
            cont++;
            if(cont==1)
                removerPorNome(&(*t_nom),atual->info,&(*t), cont);
            if(atual == *t){
                *t = removeRaiz(atual);
            } else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(matricula > atual->info->matricula)
            atual = atual->dir;
        else
            atual = atual->esq;
    }

}
int removerPorNome(Tree **t, Info* entrada, Tree **t_mat, int cont){ // remove o noh por matr�cula

    if(*t == NULL) return 0;
    Tree* ant= NULL;
    Tree* atual= *t;
    while(atual != NULL){
        if(strcmp(entrada->nome,atual->info->nome) == 0){
            cont++;
            if(cont==1)
                removerPorMatricula(&(*t_mat),atual->info->matricula,&(*t), cont);

            if(atual == *t){
                *t = removeRaiz(atual);
            } else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }

            return 1;
        }
        ant = atual;
        if(strcmp(entrada->nome, atual->info->nome) > 1)
            atual = atual->dir;
        else
            atual = atual->esq;
    }

}
int buscaPorNome(Tree *t, Info *entrada){ // faz uma busca na �rvore por nome

    if(t != NULL){
        buscaPorNome(t->esq, entrada);

        if(strcmp(t->info->nome,entrada->nome)==0){
            printf("\nBusca por Nome: ");
            printf("Nome:%s | Matricula:%d | Curso:%s \n\n", t->info->nome, t->info->matricula, t->info->curso);
            return 1;
        }

        buscaPorNome(t->dir, entrada);
    }
    else{
        return 0;
    }
}

int opcao;
Tree* arvoreMatricula = createTree();
Tree* arvoreNome = createTree();
char flag;
char curso[100];
char nome[100];
int  matricula;
int matriculaBusca;
char nomeBusca[100];
Info* entrada = (Info*) malloc(sizeof(Info));

int menu(){


    cout << "Trabalho de Estrutura de dados" <<endl;
    cout << "1 - Inserir" <<endl;
    cout << "2 - Buscar" <<endl;
    cout << "3 - Imprimir" <<endl;
    cout << "4 - Remover" <<endl;
    cin >> opcao;

    switch (opcao){
        case 1:
            do{
                char pergunta;

                Info* usuario1 = (Info*) malloc(sizeof(Info));

                cout << "Matricula" <<endl;
                cin >> usuario1->matricula;

                cout << "Curso" <<endl;
                scanf("%s", &curso );

                cout << "Nome" <<endl;
                scanf("%s", &nome );

                strcpy(usuario1->curso,curso);
                strcpy(usuario1->nome,nome);

                insereOrdenadoMatricula(&arvoreMatricula, usuario1);
                insereOrdenadoNome(&arvoreNome, usuario1);

                showTree(arvoreMatricula);
                showTree(arvoreNome);

                cout << "Deseja terminar de inserir?  (s/n)" <<endl;
                cin >> flag;
            }while (flag == 'n');
            menu();
            break;
        case 4:
            char opcao2;
            cout << "Você deseja remover por nome ou matricula (n/m)" <<endl;
            cin >> opcao2;


            if(opcao2 == 'n' || opcao2 == 'N'){
                cout << "Digite o nome" <<endl;
                scanf("%s", &nome);

                strcpy(entrada->nome,nome);

                if(removerPorNome(&arvoreNome,entrada, &arvoreMatricula, 0)){
                    printf("\nAluno removido\n");
                }else{
                    printf("Nome n�o encontrado!\n");
                }
            }
            else{
                if(opcao2 == 'm' || opcao2 == 'm'){
                    cout << "Digite a matricula" <<endl;
                    scanf("%d", &matricula);
                    entrada->matricula = matricula;
                    if(removerPorMatricula(&arvoreMatricula,entrada->matricula, &arvoreNome, 0)){
                        printf("\nAluno removido!\n");
                    }else {
                        printf("Matricula n�o encontrada!\n");
                    }
                }
            }
            printf("\n\nArvore ordenada por matricula: \n");
            showTree(arvoreMatricula); printf("\n\n");
            printf("Arvore ordenada por Nome: \n");
            showTree(arvoreNome); printf("\n\n");
            menu();
            break;
        case 2:
            char busca;
            cout << "Buscando por nome ou matricula ? (n/m)"  <<endl;
            Info* usuarioBusca = (Info*) malloc(sizeof(Info));
            cin >> busca;

            if ( busca == 'n'){
                cout << "Nome" <<endl;
                scanf("%s", &nomeBusca );
                strcpy(usuarioBusca->nome,nome);

                buscaPorMatricula(arvoreNome, usuarioBusca);
            }else{
                if ( busca == 'm'){
                    cout << "Matricula" <<endl;
                    cin >> usuarioBusca->matricula;
                    if(!buscaPorMatricula(arvoreMatricula, usuarioBusca)){
                        printf("Matricula n encontrado\n");
                    }

                }else{
                    cout << "escolha errada"<<endl;
                    menu();
                }
            }
            break;
    }




    showTree(arvoreMatricula);

    free(arvoreMatricula);

    return 0;
}

int main() {
    menu();
}