#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct{
    int matricula;
    char *nome;
    char *curso;
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


void insertTree(Tree** t, Info* usuario){

    if(*t == NULL){
        *t = (Tree*)malloc(sizeof(Tree));
        (*t)->dir = NULL;
        (*t)->esq = NULL;
        (*t)->info = usuario;
    } else {
        if(usuario->matricula < (*t)->info->matricula){
            insertTree(&(*t)->dir, usuario);
        }
        if(usuario->matricula > (*t)->info->matricula){
            insertTree(&(*t)->esq, usuario);
        }
    }
}

int isInTree(Tree* t, int matricula) {

    if(treeIsEmpty(t)) {
        return 0;
    }
    return t->info->matricula == matricula || isInTree(t->dir, matricula) || isInTree(t->esq, matricula);
}



int main()
{
    Tree* t = createTree();
    char flag;
    char curso[100];
    char nome[100];
    do{
        Info* usuario1 = (Info*) malloc(sizeof(Info));

        cout << "Matricula" <<endl;
        cin >> usuario1->matricula;

        cout << "Curso" <<endl;
        scanf("%s", &curso );

        cout << "Nome" <<endl;
        scanf("%s", &nome );

        cout << "Deseja terminar ?  s/n" <<endl;
        cin >> flag;

        usuario1->curso = curso;
        usuario1->nome = nome;

        insertTree(&t, usuario1);
    }while (flag == 'n');

    showTree(t);

    free(t);

    return 0;
}