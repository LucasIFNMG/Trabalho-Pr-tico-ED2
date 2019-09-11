#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

typedef struct
{
    char nome[40];
    int idFunc;
    int cpf;
    float comissaoTotal;
    float salarioBase;
    float salarioTotal;


}Funcionario;

typedef struct
{
    char descricao[40];
    int idMed;
    int estoque;
    int qtdeVendida;
    float precoCusto;
    float precoVenda;
    char lab[20];
    float valorTotalVendido;


}Medicamento;

typedef struct
{
    int idVenda;
    long int data;
    char hora[10];
    Funcionario Func;
    int idFunc;
    Medicamento Med;
    int idMed;
    int qtde;
    float precoTotal;
    float porcentComissao;
    int contMedVenda;
    int dia;
    int mes;
    int ano;

}Venda;

void printLinha()
{
    for(int i=0;i<30;i++)
        printf("*");

}

int buscaBinariaMedId(FILE* arq, Medicamento medicamentos[], int contMed, int alvo)
{
    arq = fopen("medicamentos.txt","rb");
    if(arq == NULL)
    {
        printf("Erro na abertura\n");
        system("pause");
        exit(1);
    }

    fread(medicamentos, sizeof(Medicamento), contMed, arq);

    int inicio = 0;
    int final = contMed - 1;
    while (inicio <= final) {
        int pivo = (inicio + final) / 2; //calcula o meio
        if (alvo == medicamentos[pivo].idMed) {
            //o elemento foi encontrado
            return pivo;
        } else {
            if (alvo > medicamentos[pivo].idMed) {
                //a busca continuará no subvetor à direira
                inicio = pivo + 1;
            } else {
                //a busca continuará no subvetor à esquerda
                final = pivo - 1;
            }
        }
    }

    fclose(arq);

    //o elemento não está no vetor
    return -1;
}

int buscaBinariaMedDescricao(FILE* arq, Medicamento medicamentos[], int *contMed, char* busca)
{
    arq = fopen("medicamentos.txt","rb");
    if(arq == NULL)
    {
        printf("Erro na abertura\n");
        system("pause");
        exit(1);
    }
    fread(medicamentos, sizeof(Medicamento), *contMed, arq);

    int inicio = 0;
    int final = *contMed - 1;
    while (inicio <= final) {
        int pivo = (inicio + final) / 2; //calcula o meio
        if (strcmp(busca,medicamentos[pivo].descricao) == 0) {
            //o elemento foi encontrado
            return pivo;
        } else {
            if (strcmp(busca,medicamentos[pivo].descricao) > 0) {
                //a busca continuará no subvetor à direira
                inicio = pivo + 1;
            } else {
                //a busca continuará no subvetor à esquerda
                final = pivo - 1;
            }
        }
    }
    fclose(arq);

    //o elemento não está no vetor
    return -1;
}

int buscaBinariaFuncId(FILE* arq, Funcionario funcionarios[], int contFunc, int alvo)
{
    arq = fopen("funcionarios.txt","rb");
    if(arq == NULL)
    {
        printf("ERRO na abertura!\n");
        system("pause");
        exit(1);
    }

    fread(funcionarios, sizeof(Funcionario), contFunc, arq);

    int inicio = 0;
    int final = contFunc - 1;
    while (inicio <= final) {
        int pivo = (inicio + final) / 2; //calcula o meio
        if (alvo == funcionarios[pivo].idFunc) {
            //o elemento foi encontrado
            return pivo;
        } else {
            if (alvo > funcionarios[pivo].idFunc) {
                //a busca continuará no subvetor à direira
                inicio = pivo + 1;
            } else {
                //a busca continuará no subvetor à esquerda
                final = pivo - 1;
            }
        }
    }
    fclose(arq);

    //o elemento não está no vetor
    return -1;
}

int buscaBinariaFuncNome(FILE* arq, Funcionario funcionarios[], int contFunc, char* busca)
{
    arq = fopen("funcionarios.txt","rb");
    if(arq == NULL)
    {
        printf("ERRO na abertura!\n");
        system("pause");
        exit(1);
    }

    fread(funcionarios, sizeof(Funcionario), contFunc, arq);

    int inicio = 0;
    int final = contFunc - 1;
    while (inicio <= final) {
        int pivo = (inicio + final) / 2; //calcula o meio
        if (strcmp(busca,funcionarios[pivo].nome) == 0) {
            //o elemento foi encontrado
            return pivo;
        } else {
            if (strcmp(busca,funcionarios[pivo].nome) > 0) {
                //a busca continuará no subvetor à direira
                inicio = pivo + 1;
            } else {
                //a busca continuará no subvetor à esquerda
                final = pivo - 1;
            }
        }
    }
    fclose(arq);

    //o elemento não está no vetor
    return -1;
}

Medicamento setMed(FILE* arq, int contMed)
{
    arq = fopen("medicamentos.txt","ab");
    if(arq == NULL)
    {
        printf("ERRO na abertura!\n");
        system("pause");
        exit(1);
    }

    Medicamento novo;
    printf("CADASTRO DE MEDICAMENTO\n");

    printf("Insira Descrição:\n");
    scanf(" %[^\n]s",novo.descricao);
    printf("Insira Preco de Custo:\n");
    scanf(" %f",&novo.precoCusto);
    printf("Insira Preco de Venda:\n");
    scanf(" %f",&novo.precoVenda);
    printf("Insira Estoque:\n");
    scanf(" %d",&novo.estoque);
    printf("Insira Laboratório:\n");
    scanf(" %[^\n]s",novo.lab);
    novo.idMed = contMed;
    printf("IDMED = %d\n",novo.idMed);

    fwrite(&novo, sizeof(Medicamento), 1, arq);


    fclose(arq);
    printf("Medicamento cadastrado com sucesso!\n");

    return novo;

}

void getMedDescricao(FILE* arq, Medicamento medicamentos[], int contMed)
{
    arq = fopen("medicamentos.txt","rb");
    if(arq == NULL)
    {
        printf("ERRO na abertura!\n");
        system("pause");
        exit(1);
    }

    fread(medicamentos, sizeof(Medicamento), contMed, arq);

    char busca[20];
    int indice;

    printf("Insira a Descrição do Medicamento:\n");
    scanf(" %[^\n]s",busca);

    indice = buscaBinariaMedDescricao(arq, medicamentos, &contMed, busca);
        if (indice != -1)
        {
            printf("ID\tDESCRIÇÃO\tESTOQUE\tPREÇO CUSTO\tPREÇO VENDA\tLABORATÓRIO\n");
            printf("%d\t%s\t\t%d\t%.2f\t\t%.2f\t\t%s\n",medicamentos[indice].idMed, medicamentos[indice].descricao, medicamentos[indice].estoque, medicamentos[indice].precoCusto, medicamentos[indice].precoVenda, medicamentos[indice].lab);
        }

   else
        printf("'%s' não encontrado!!\n",busca);

    fclose(arq);
}

void getMedID(FILE* arq, Medicamento medicamentos[], int contMed)
{
    int busca;
    int indice;

    arq = fopen("medicamentos.txt","rb");

    if(arq == NULL)
    {
        printf("Erro na abertura!\n");
        system("pause");
        exit(1);
    }

    fread(medicamentos, sizeof(Medicamento), contMed, arq);

    printf("Insira o ID do Medicamento:\n");
    scanf(" %d",&busca);

    indice = buscaBinariaMedId(arq, medicamentos, contMed, busca);

        if(indice!=-1)
        {
            printf("\nID\tDESCRIÇÃO\tESTOQUE\tPREÇO CUSTO\tPREÇO VENDA\tLABORATÓRIO\n");
            printf("%d\t%s\t\t%d\t%.2f\t\t%.2f\t\t%s\n",
                   medicamentos[indice].idMed, medicamentos[indice].descricao, medicamentos[indice].estoque,
                   medicamentos[indice].precoCusto, medicamentos[indice].precoVenda, medicamentos[indice].lab);
        }

    else
        printf("ID '%d' não encontrado!!\n",busca);

    fclose(arq);

}

void alteraMed(FILE* arq, Medicamento medicamentos[], int contMed)
{
    arq = fopen("medicamentos.txt","r+b");
    if(arq == NULL)
    {
        printf("ERRO na abertura!\n");
        system("pause");
        exit(1);
    }


    int busca_id;
    char busca_med_descricao[20];
    int opt,indice;

    Medicamento aux;

    printf("Selecione o método de Pesquisa para o Medicamento:\n");
    printf("1- ID\n2- DESCRIÇÃO\n");
    scanf(" %d",&opt);

    if(opt == 1)
    {
        printf("Insira o ID:\n");
        scanf(" %d",&busca_id);
        indice = buscaBinariaMedId(arq, medicamentos, contMed, busca_id);
        if(indice!=-1)
        {
            fseek(arq, (busca_id-1)*sizeof(Medicamento), SEEK_SET);
            fread(&aux, sizeof(Medicamento), 1, arq);


            printf("\nID\tDESCRIÇÃO\tESTOQUE\tPREÇO CUSTO\tPREÇO VENDA\tLABORATÓRIO\n");
            printf("%d\t%s\t\t%d\t%.2f\t\t%.2f\t\t%s\n",
                   aux.idMed, aux.descricao, aux.estoque,
                   aux.precoCusto, aux.precoVenda, aux.lab);


            printf("Insira nova Descrição:\n");
            scanf(" %[^\n]s",aux.descricao);
            printf("Insira novo Estoque:\n");
            scanf(" %d",&aux.estoque);
            printf("Insira novo Preço de Custo:\n");
            scanf(" %f",&aux.precoCusto);
            printf("Insira novo Preço de Venda:\n");
            scanf(" %f",&aux.precoVenda);
            printf("Insira novo Laboratório:\n");
            scanf(" %[^\n]s",aux.lab);

            fseek(arq, -1*sizeof(Medicamento), SEEK_CUR);
            fwrite(&aux, sizeof(Medicamento), 1, arq);

            fclose(arq);

            printf("Medicamento alterado com sucesso!\n");

        }
        else
            printf("ID %d não encontrado!!\n",busca_id);
    }
    if(opt == 2)
    {
        printf("Insira a Descrição:\n");
        scanf(" %[^\n]s",busca_med_descricao);

        indice = buscaBinariaMedDescricao(arq, medicamentos, &contMed, busca_med_descricao);
        if(indice!=-1)
        {
            fseek(arq, (indice)*sizeof(Medicamento), SEEK_SET);
            fread(&aux, sizeof(Medicamento), 1, arq);

            printLinha();
            printf("\nREGISTRO ANTIGO\n");
            printf("\nID\tDESCRIÇÃO\tESTOQUE\tPREÇO CUSTO\tPREÇO VENDA\tLABORATÓRIO\n");
            printf("%d\t%s\t\t%d\t%.2f\t\t%.2f\t\t%s\n",
                   aux.idMed, aux.descricao, aux.estoque,
                   aux.precoCusto, aux.precoVenda, aux.lab);
            printLinha();

            printf("\nInsira nova Descrição:\n");
            scanf(" %[^\n]s",aux.descricao);
            printf("Insira novo Estoque:\n");
            scanf(" %d",&aux.estoque);
            printf("Insira novo Preço de Custo:\n");
            scanf(" %f",&aux.precoCusto);
            printf("Insira novo Preço de Venda:\n");
            scanf(" %f",&aux.precoVenda);
            printf("Insira novo Laboratório:\n");
            scanf(" %[^\n]s",aux.lab);

            fseek(arq, -1*sizeof(Medicamento), SEEK_CUR);
            fwrite(&aux, sizeof(Medicamento), 1, arq);
            fclose(arq);

            printf("Medicamento alterado com sucesso!\n");
        }
        if(indice == -1)
            printf("'%s' não encontrado!!\n",busca_med_descricao);
    }

    fclose(arq);

}
/*
Medicamento excluiMed(FILE* arq, Medicamento medicamentos[], int contMed)
{

}
*/
Funcionario setFunc(FILE* arq, int contFunc)
{
    Funcionario novo;
    arq = fopen("funcionarios.txt","ab");
    if(arq == NULL)
    {
        printf("ERRO na abertura!\n");
        system("pause");
        exit(1);
    }
    printf("CADASTRO DE FUNCIONÁRIO\n");


    printf("Insira Nome:\n");
    scanf(" %[^\n]s",novo.nome);
    printf("Insira CPF:\n");
    scanf(" %d",&novo.cpf);
    printf("Insira Salário Base:\n");
    scanf(" %f",&novo.salarioBase);
    novo.salarioTotal = novo.salarioBase;
    novo.idFunc = contFunc;
    printf("IDFUNC = %d\n",novo.idFunc);

    fwrite(&novo, sizeof(Funcionario), 1, arq);
    fclose(arq);
    printf("Funcionário cadastrado com sucesso!\n");

    return novo;

}

void getFuncNome(FILE* arq, Funcionario funcionarios[], int contFunc)
{
    arq = fopen("funcionarios.txt","rb");
    if(arq == NULL)
    {
        printf("ERRO na abertura!\n");
        system("pause");
        exit(1);
    }
    char busca[20];
    int indice;

    printf("Insira o Nome do Funcionário:\n");
    scanf(" %[^\n]s",busca);

    indice = buscaBinariaFuncNome(arq, funcionarios, contFunc, busca);
        if (indice != -1)
        {
            printf("ID\tNOME\tCPF\tSALÁRIO BASE\tSALÁRIO TOTAL\n");
            printf("%d\t%s\t%d\t%.2f\t\t%.2f\n",funcionarios[indice].idFunc,funcionarios[indice].nome, funcionarios[indice].cpf, funcionarios[indice].salarioBase, funcionarios[indice].salarioTotal);
        }

    else
        printf("'%s' não encontrado!!\n",busca);

}

void getFuncID(FILE* arq, Funcionario funcionarios[], int contFunc)
{
    arq = fopen("funcionarios.txt","rb");
    if(arq == NULL)
    {
        printf("ERRO na abertura!\n");
        system("pause");
        exit(1);
    }
    int busca;
    int indice;

    printf("Insira o ID do Funcionário:\n");
    scanf(" %d",&busca);

    indice = buscaBinariaFuncId(arq, funcionarios, contFunc, busca);

        if (indice!=-1)
        {
            printf("\nID\tNOME\tCPF\tSALÁRIO BASE\tSALÁRIO TOTAL\n");
            printf("%d\t%s\t%d\t%.2f\t\t%.2f\n",funcionarios[indice].idFunc, funcionarios[indice].nome, funcionarios[indice].cpf, funcionarios[indice].salarioBase, funcionarios[indice].salarioTotal);
        }

    else
        printf(" ID %d não encontrado!!\n",busca);

}

void alteraFunc(FILE* arq, Funcionario funcionarios[], int contFunc)
{
    arq = fopen("funcionarios.txt","r+b");
    if(arq == NULL)
    {
        printf("ERRO na abertura!\n");
        system("pause");
        exit(1);
    }

    Funcionario aux;
    int busca_id;
    char busca_func_nome[20];
    int opt,indice;

    printf("Selecione o método de Pesquisa para o Funcionário:\n");
    printf("1- ID\n2- NOME\n");
    scanf(" %d",&opt);

    switch(opt)
    {
        case 1:
            printf("Insira o ID:\n");
            scanf(" %d",&busca_id);
            indice = buscaBinariaFuncId(arq, funcionarios, contFunc, busca_id);
            if(indice!=-1)
            {
                fseek(arq, (indice)*sizeof(Funcionario), SEEK_SET);
                fread(&aux, sizeof(Funcionario), 1, arq);

                printLinha();
                printf("\nREGISTRO ANTIGO\n");
                printf("ID\tNOME\tCPF\tSALÁRIO BASE\tSALÁRIO TOTAL\n");
                printf("%d\t%s\t%d\t%.2f\t\t%.2f\n",aux.idFunc,aux.nome, aux.cpf, aux.salarioBase, aux.salarioTotal);
                printLinha();

                printf("\nInsira novo Nome:\n");
                scanf(" %[^\n]s",aux.nome);
                printf("Insira novo CPF:\n");
                scanf(" %d",&aux.cpf);
                printf("Insira novo Salário Base:\n");
                scanf(" %f",&aux.salarioBase);
                aux.salarioTotal = aux.salarioBase;

                fseek(arq, -1*sizeof(Funcionario), SEEK_CUR);
                fwrite(&aux, sizeof(Funcionario), 1, arq);
                fclose(arq);
                printf("Registro alterado com sucesso!\n");
            }
            else
                printf("ID %d não encontrado!!\n",busca_id);
            break;
        case 2:
            printf("Insira o NOME:\n");
            scanf(" %[^\n]s",busca_func_nome);
            indice = buscaBinariaFuncNome(arq, funcionarios, contFunc, busca_func_nome);
            if(indice!=-1)
            {
                fseek(arq, (indice)*sizeof(Funcionario), SEEK_SET);
                fread(&aux, sizeof(Funcionario), 1, arq);

                printLinha();
                printf("\nREGISTRO ANTIGO\n");
                printf("ID\tNOME\tCPF\tSALÁRIO BASE\tSALÁRIO TOTAL\n");
                printf("%d\t%s\t%d\t%.2f\t\t%.2f\n",aux.idFunc,aux.nome, aux.cpf, aux.salarioBase, aux.salarioTotal);
                printLinha();

                printf("\nInsira novo Nome:\n");
                scanf(" %[^\n]s",aux.nome);
                printf("Insira novo CPF:\n");
                scanf(" %d",&aux.cpf);
                printf("Insira novo Salário Base:\n");
                scanf(" %f",&aux.salarioBase);
                aux.salarioTotal = aux.salarioBase;

                fseek(arq, -1*sizeof(Funcionario), SEEK_CUR);
                fwrite(&aux, sizeof(Funcionario), 1, arq);
                fclose(arq);
                printf("Registro alterado com sucesso!\n");

            }
            else
                printf("'%s' não encontrado!!\n",busca_func_nome);
            break;

        default:
            printf("Opção Inválida!\n");
            break;

    }
    fclose(arq);

}
/*
Funcionario excluiFunc(FILE* arq, Funcionario funcionarios[], int contFunc)
{

}
*/
Venda setVenda(FILE* arqMeds, FILE* arqFuncs, FILE* arqVendas, Venda vendas[], Medicamento medicamentos[], Funcionario funcionarios[], int contVendas, int contMed, int contFunc)
{
    arqVendas = fopen("vendas.txt","ab");
    if(arqVendas == NULL)
    {
        printf("ERRO na abertura do Arquivo Vendas!\n");
        system("pause");
        exit(1);
    }

    arqMeds = fopen("medicamentos.txt","r+b");
    if(arqMeds == NULL)
    {
        printf("ERRO na abertura do Arquivo Medicamentos!\n");
        system("pause");
        exit(1);
    }

    arqFuncs = fopen("funcionarios.txt","r+b");
    if(arqMeds == NULL)
    {
        printf("ERRO na abertura do Arquivo Funcionários!\n");
        system("pause");
        exit(1);
    }

    Venda nova;
    nova.precoTotal = 0;

    int encontrou = 0;
    int optFunc,optMed;
    char pesquisa_nome_func[20];
    char pesquisa_descricao_med[20];
    int indiceFuncionario;
    int pesquisa_id_func;
    int pesquisa_id_med;
    int indiceBusca;
    int indiceMed;
    

    long int amd;
    char data[9] = {'\0'};

    /*
    printf("Dia = %d\n", dia);
    printf("Mes = %d\n", mes);
    printf("Ano = %d\n", ano);
    printf("AAAAMMDD = %ld\n", amd);
    */

    printf("CADASTRO DE VENDA\n\n");

    printf("Insira a data (DD/MM/AAAA): ");
    scanf("%d/%d/%d", &nova.dia, &nova.mes, &nova.ano);
    sprintf(data, "%d%02d%02d", nova.ano, nova.mes, nova.dia);
    amd = atol(data);
    nova.data = amd;

    printLinha();
    printf("\nPESQUISA PELO FUNCIONÁRIO\n\n");
    printf("Insira uma Opção:\n1 - ID\n2 - Nome\n");
    printLinha();
    scanf(" %d",&optFunc);

    encontrou = 0;

    Funcionario auxFunc;


    if(optFunc == 1)
    {
        do
        {
            encontrou = 0;
            printf("\nInsira o ID do Funcionário:\n");
            scanf(" %d",&pesquisa_id_func);

            //PESQUISA BUSCA BINÁRIA ID_FUNC
            indiceBusca = buscaBinariaFuncId(arqFuncs, funcionarios, contFunc, pesquisa_id_func);

            if(indiceBusca == -1)
            {
                printf("ID %d NÃO encontrado!\n",pesquisa_id_func);
                encontrou = 0;
            }
            else
            {
                encontrou = 1;
                fseek(arqFuncs, (indiceBusca)*sizeof(Funcionario), SEEK_SET);
                fread(&auxFunc, sizeof(Funcionario), 1, arqFuncs);
                indiceFuncionario = indiceBusca;
                nova.idFunc = indiceFuncionario;
                printf("Funcionário %d - %s\n",auxFunc.idFunc,auxFunc.nome);
            }
        }while(!encontrou);

    }
    
    if(optFunc == 2)
    {
        do
        {
            printf("Insira o Nome do Funcionário:\n");
            scanf(" %[^\n]s",pesquisa_nome_func);

            encontrou = 0;

            //PESQUISA BUSCA BINÁRIA NOME_FUNC
            indiceBusca = buscaBinariaFuncNome(arqFuncs, funcionarios, contFunc, pesquisa_nome_func);
            if(indiceBusca == -1)
            {
                printf("Funcionário '%s' não encontrado!!",pesquisa_nome_func);
                encontrou = 0;
            }
            else
                {
                    fseek(arqFuncs, (indiceBusca)*sizeof(Funcionario), SEEK_SET);
                    fread(&auxFunc, sizeof(Funcionario), 1, arqFuncs);
                    encontrou=1;
                    indiceFuncionario = indiceBusca;
                    printf("Funcionário %d - %s\n",auxFunc.idFunc, auxFunc .nome);
                }
        }while(!encontrou);
  
    }

    Medicamento auxMed;
    printLinha();
    printLinha();
    printf("\nPESQUISA PELO MEDICAMENTO\n\n");
    printf("Insira uma Opção:\n1 - ID\n2 - Descrição\n");
    printLinha();
    printLinha();
    scanf(" %d",&optMed);

    if(optMed == 1)
    {
            //PESQUISA BUSCA BINÁRIA ID_MED
        do{
            printf("\nInsira o ID do Medicamento:\n");
            scanf(" %d",&pesquisa_id_med);
            if(pesquisa_id_med == -1)
                break;
            


            encontrou = 0;

            indiceBusca = buscaBinariaMedId(arqMeds, medicamentos, contMed, pesquisa_id_med);
            if(indiceBusca != -1)
            {
                indiceMed = indiceBusca;
                encontrou=1;

                fseek(arqMeds, (indiceBusca)*sizeof(Medicamento), SEEK_SET);
                fread(&auxMed, sizeof(Medicamento), 1, arqMeds);

                printLinha();
                printf("\nID\tDESCRIÇÃO\tESTOQUE\tPREÇO CUSTO\tPREÇO VENDA\tLABORATÓRIO\n");
                printf("%d\t%s\t\t%d\t%.2f\t\t%.2f\t\t%s\n",
                       auxMed.idMed, auxMed.descricao, auxMed.estoque,
                       auxMed.precoCusto, auxMed.precoVenda, auxMed.lab);
                printLinha();
            }
            else
            {
                printf("ID %d não encontrado!\n",pesquisa_id_med);
                encontrou = 0;
            }
        }while(!encontrou);

        do{
            printf("\nInsira a Quantidade:\n");
            scanf(" %d",&nova.qtde);
            if(nova.qtde > auxMed.estoque)
                printf("ATENÇÃO! Estoque insuficiente!\n");
        }while(nova.qtde > auxMed.estoque);

        if(nova.qtde <= auxMed.estoque)
            contVendas++;

        nova.idMed = auxMed.idMed;
        nova.precoTotal += nova.qtde * auxMed.precoVenda;
        auxFunc.comissaoTotal += (0.1*nova.precoTotal);
        auxFunc.salarioTotal = auxFunc.salarioBase + auxFunc.comissaoTotal;
        medicamentos[indiceMed].estoque-= nova.qtde;

        //TESTE
        printLinha();
        printf("TESTE\n");
        printf("\nID\tDESCRIÇÃO\tESTOQUE\tPREÇO CUSTO\tPREÇO VENDA\tLABORATÓRIO\n");
        printf("%d\t%s\t\t%d\t%.2f\t\t%.2f\t\t%s\n",
               auxMed.idMed, auxMed.descricao, auxMed.estoque,
               auxMed.precoCusto, auxMed.precoVenda, auxMed.lab);
        printLinha();

    }

    if(optMed == 2)
    {
            //PESQUISA BUSCA BINÁRIA DESCRIÇÃO_MED
        do{
            encontrou = 0;
            printf("Insira a Descrição do Medicamento ('sair' para Encerrar a venda):\n");
            scanf(" %[^\n]s",pesquisa_descricao_med);

            indiceBusca = buscaBinariaMedDescricao(arqMeds, medicamentos, &contMed, pesquisa_descricao_med);

            if( strcmp(pesquisa_descricao_med,"sair") == 0 )
                break;
            

            if (indiceBusca != -1)
            {
                fseek(arqMeds, indiceBusca*sizeof(Medicamento), SEEK_SET);
                fread(&auxMed, sizeof(Medicamento), 1, arqMeds);

                printLinha();
                printf("\nID\tDESCRIÇÃO\tESTOQUE\tPREÇO CUSTO\tPREÇO VENDA\tLABORATÓRIO\n");
                printf("%d\t%s\t\t%d\t%.2f\t\t%.2f\t\t%s\n",
                       auxMed.idMed, auxMed.descricao, auxMed.estoque,
                       auxMed.precoCusto, auxMed.precoVenda, auxMed.lab);
                printLinha();

                indiceMed = indiceBusca;
                encontrou = 1;
            }
            else
            {
                printf("'%s' não encontrado!\n",pesquisa_descricao_med);
                encontrou = 0;
            }
        }while(!encontrou);

        do{
            printf("\nInsira a Quantidade:\n");
            scanf(" %d",&nova.qtde);

            //TESTE
            printf("NOVA.QTDE = %d",nova.qtde);
            printf("AUXMED.ESTOQUE = %d",auxMed.estoque);

            if(nova.qtde > auxMed.estoque)
                printf("ATENÇÃO! Estoque insuficiente!\n");

        }while(nova.qtde > auxMed.estoque);

        if(nova.qtde <= auxMed.estoque)
            contVendas++;


        nova.precoTotal += nova.qtde * auxMed.precoVenda;
        nova.idMed = auxMed.idMed;

        auxFunc.comissaoTotal = auxFunc.comissaoTotal + (0.1*nova.precoTotal);
        auxFunc.salarioTotal = auxFunc.salarioBase + auxFunc.comissaoTotal;

        auxMed.estoque-= nova.qtde;
        auxMed.qtdeVendida = nova.qtde;
        auxMed.valorTotalVendido = nova.precoTotal;

        //TESTE
        printLinha();
        printf("TESTE\n");
        printf("\nID\tDESCRIÇÃO\tESTOQUE\tPREÇO CUSTO\tPREÇO VENDA\tLABORATÓRIO\n");
        printf("%d\t%s\t\t%d\t%.2f\t\t%.2f\t\t%s\n",
               auxMed.idMed, auxMed.descricao, auxMed.estoque,
               auxMed.precoCusto, auxMed.precoVenda, auxMed.lab);
        printLinha();


    }

    if (indiceBusca == -1)
    {
        encontrou = 0;
        printf("Medicamento '%s' não encontrado!!",pesquisa_descricao_med);
    }


    nova.idVenda = contVendas;
    printLinha();
    printLinha();
    printf("\nRESUMO DA VENDA #%d\n\n",contVendas-1);
    printf("DESCRIÇÃO\tQUANTIDADE\tPREÇO UNITÁRIO\tPREÇO TOTAL\n");
    printf("%s\t\t%d\t\t%.2f\t\t%.2f\n",auxMed.descricao, nova.qtde, auxMed.precoVenda, nova.qtde * auxMed.precoVenda);

    printf("\n\nTOTAL: %.2f\n",nova.precoTotal);

    printf("OBRIGADO!\n\n");
    printLinha();
    printLinha();

    fwrite(&nova, sizeof(Venda), 1, arqVendas);

    fseek(arqMeds, -1*sizeof(Medicamento), SEEK_CUR);
    fwrite(&auxMed, sizeof(Medicamento), 1, arqMeds);

    fseek(arqFuncs, -1*sizeof(Funcionario), SEEK_CUR);
    fwrite(&auxFunc, sizeof(Funcionario), 1, arqFuncs);


    fclose(arqMeds);
    fclose(arqFuncs);
    fclose(arqVendas);

    return nova;

}
/*
//Funções QUICKSORT

void troca (int i, int j, Venda vendas[])
{
    int k = vendas[i].data;
    vendas[i] = vendas[j];
    vendas[j].data = k;
}

int particao (int inicio, int fim, Venda vendas[])
{
    int i = inicio;

    for (int j = inicio; j < fim; j++) {

        // Elemento atual menor ou igual ao pivô?
        if (vendas[j].data <= vendas[fim].data) {
            troca(i++, j, vendas);
        }
    }
    troca(i, fim, vendas);

    return i;
}

void quicksortVendas (int inicio, int fim, Venda vendas[])
{
    if (inicio >= fim)
        return;

    int pivo = particao(inicio, fim, vendas);

    quicksortVendas(inicio, pivo - 1, vendas);
    quicksortVendas(pivo + 1, fim, vendas);
}

*/

void relatorioMedGeral(FILE* arq, Medicamento medicamentos[], int contMed)
{
    Medicamento auxMed[contMed];

    arq = fopen("medicamentos.txt","rb");
    if(arq == NULL)
    {
        printf("ERRO na abertura!\n");
        system("pause");
        exit(1);
    }

    fread(auxMed, sizeof(Medicamento), contMed, arq);

    printLinha();
    printLinha();
    printLinha();
    printf("\nID\tDESCRIÇÃO\tESTOQUE\tPREÇO CUSTO\tPREÇO VENDA\tLABORATÓRIO\n");

    for(int i=0; i<contMed; i++)
    {
        printf("%d\t%s\t\t%d\t%.2f\t\t%.2f\t\t%s\n",
               auxMed[i].idMed, auxMed[i].descricao, auxMed[i].estoque,
               auxMed[i].precoCusto, auxMed[i].precoVenda, auxMed[i].lab);

    }
    printLinha();
    printLinha();


    fclose(arq);

}

void relatorioFuncGeral(FILE* arq, Funcionario funcionarios[], int contFunc)
{
    Funcionario auxFunc[contFunc];

    arq = fopen("funcionarios.txt","rb");
    if(arq == NULL)
    {
        printf("ERRO na abertura!\n");
        system("pause");
        exit(1);
    }

    fread(auxFunc, sizeof(Funcionario), contFunc, arq);


    printLinha();
    printf("\nID\tNOME\tCPF\tSALÁRIO BASE\tSALÁRIO TOTAL\n");



    for(int i=0; i<contFunc; i++)
       printf("%d\t%s\t%d\t%.2f\t\t%.2f\n", auxFunc[i].idFunc, auxFunc[i].nome, auxFunc[i].cpf, auxFunc[i].salarioBase, auxFunc[i].salarioTotal);


    printLinha();


    fclose(arq);
}

void relatorioVendasGeral(FILE* arqVendas, FILE* arqMeds, Venda vendas[], Medicamento medicamentos[], int contVendas, int contMed)
{
    Venda auxVendas[contVendas];
    Medicamento auxMed[contMed];

    arqVendas = fopen("vendas.txt","rb");
    if(arqVendas == NULL)
    {
        printf("ERRO na abertura do arquivo Vendas!\n");
        system("pause");
        exit(1);
    }

    arqMeds = fopen("medicamentos.txt","rb");
    if(arqMeds == NULL)
    {
        printf("ERRO na abertura do arquivo Medicamentos!\n");
        system("pause");
        exit(1);
    }

    fread(auxVendas, sizeof(Venda), contVendas, arqVendas);
    fread(auxMed, sizeof(Medicamento), contMed, arqMeds);


    printLinha();
    printLinha();
    printf("\nID\tDATA\tDESCRIÇÃO MED\tQUANTIDADE\tPREÇO UNITÁRIO\tPREÇO TOTAL\n");
    for(int i=0; i<contVendas; i++)
        for(int j=0; j<contMed; j++)
            if(auxVendas[i].idMed == auxMed[j].idMed)
            {
                printf("%d\t%d/%d/%d\t%s\t\t%d\t\t%.2f\t\t%.2f\n",auxVendas[i].idVenda , auxVendas[i].dia ,auxVendas[i].mes ,auxVendas[i].ano ,auxMed[j].descricao,
                        auxVendas[i].qtde, auxMed[j].precoVenda, auxVendas[i].precoTotal);
                break;
            }


    printLinha();


    fclose(arqVendas);
    fclose(arqMeds);




}

void troca (int i, int j, int vetor[])
{
    int k = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = k;
}

int particao (int inicio, int fim, int vetor[])
{
    int i = inicio;

    for (int j = inicio; j < fim; j++) {

        /* Elemento atual menor ou igual ao pivô? */
        if (vetor[j] <= vetor[fim]) {
            troca(i++, j, vetor);
        }
    }
    troca(i, fim, vetor);

    return i;
}

void quickSortMed (int inicio, int fim, int vetor[])
{
    if (inicio >= fim)
        return;

    int pivo = particao(inicio, fim, vetor);

    quickSortMed(inicio, pivo - 1, vetor);
    quickSortMed(pivo + 1, fim, vetor);
}


void relatorioVendasOrdenado(FILE* arq, Venda vendas[], Medicamento medicamentos[], int contVendas)
{
    //Relatório Vendas Ordenado pela DATA - QUICKSORT
    //quicksortVendas(0, contVendas-1, vendas);
    Venda aux[100];

    arq = fopen("vendas.txt","rb");
    if(arq == NULL)
    {
        printf("ERRO na abertura do Arquivo Vendas!\n");
        system("pause");
        exit(1);
    }

    fread(aux,sizeof(Venda),contVendas,arq);
    printf("\nRELATÓRIO DE VENDAS\n");
    printf("ID\tDATA\tID MED\tID FUNCIONÁRIO\t\tQTDE\tVALOR TOTAL\n");
    for(int i=0;i<contVendas;i++)
    {
        printf("%d\t%d/%d/%d\t%d\t%d\t%d\t%.2f\n",vendas[i].idVenda, vendas[i].dia, vendas[i].mes, vendas[i].ano, medicamentos[i].idMed, vendas[i].idFunc, vendas[i].qtde, vendas[i].precoTotal);
        // VENDAS (CREATE)
        // ID, DATA, HORA, ID_FUNCIONÁRIO, ID_MEDICAMENTO, QTDE, PREÇO_TOTAL
    }

    fclose(arq);
}

void relatorioMedOrdenado(FILE* arqMeds, FILE* arqVendas, Venda vendas[], Medicamento medicamentos[], int contMed)
{
    arqMeds = fopen("medicamentos.txt","rb");
     if(arqMeds == NULL)
    {
        printf("ERRO na abertura do Arquivo Medicamentos!\n");
        system("pause");
        exit(1);
    }

    arqVendas = fopen("vendas.txt","rb");
     if(arqVendas == NULL)
    {
        printf("ERRO na abertura do Arquivo Vendas!\n");
        system("pause");
        exit(1);
    }

    int vetorAux[contMed];

    Medicamento vetMedAux[contMed];
    for(int i=0;i<contMed;i++)
        vetMedAux[i] = medicamentos[i];

    //Mais Vendidos
    //ID, Descrição, Qtde Vendida e Valor Total Vendido
    //Ordenado de forma Decrescente pela Qtde Total Vendida
    for(int i=0;i<contMed;i++)
    {
        vetorAux[i] = medicamentos[i].qtdeVendida;
    }
    quickSortMed(0, contMed, vetorAux);

    for(int i=0;i<contMed;i++)
    {
        {
            for(int j=0;j<contMed;j++)
                if( medicamentos[i].qtdeVendida == vetorAux[j])
                    vetMedAux [j] = medicamentos[i];

        }
    }

    Medicamento auxMed[100];
    fread(auxMed, sizeof(Medicamento), contMed, arqMeds);

    for(int i=0;i<contMed;i++)
    {
        printf("\nMEDICAMENTOS MAIS VENDIDOS\n");
        printf("ID\tDESCRIÇÃO\tQuantidade Vendida\tValor Total\n");
        printf("%d\t%s\t\t%d\t%.2f\n",vetMedAux[i].idMed, vetMedAux[i].descricao, vetMedAux[i].qtdeVendida, vetMedAux[i].valorTotalVendido);

    }
    fclose(arqMeds);
    fclose(arqVendas);
}

int contadorMed(FILE* arq)
{
    Medicamento aux[100];
    int contAux;

    arq = fopen("medicamentos.txt","rb");
    if(arq == NULL)
    {
        printf("Erro na abertura!\n");
        system("pause");
        exit(1);
    }

    contAux = fread(aux, sizeof(Medicamento), 100, arq);

    fclose(arq);
    printf("CONTMED = %d\n",contAux);

    return contAux;
}

int contadorFunc(FILE* arq)
{
    Funcionario aux[100];
    int contAux;

    arq = fopen("funcionarios.txt","rb");
    if(arq == NULL)
    {
        printf("Erro na abertura!\n");
        system("pause");
        exit(1);
    }

    //fread(v, sizeof(int), 5, arq);


    contAux = fread(aux, sizeof(Funcionario), 100, arq);

    fclose(arq);
    printf("CONTFUNC = %d\n",contAux);

    return contAux;
}

int contadorVendas(FILE* arq)
{
    Venda aux[100];
    int contAux;

    arq = fopen("vendas.txt","rb");
    if(arq == NULL)
    {
        printf("Erro na abertura!\n");
        system("pause");
        exit(1);
    }

    contAux = fread(aux, sizeof(Venda), 100, arq);

    fclose(arq);
    printf("CONTVENDAS = %d\n",contAux);

    return contAux;
}

int main()

{

    setlocale(LC_ALL, "Portuguese");
    int opt1,optMed,optFunc,optRelat;

    Medicamento medicamentos[100];
    Funcionario funcionarios[100];
    Venda vendas[100];

    FILE* arqMeds;
    arqMeds = fopen("medicamentos.txt","ab");

    FILE* arqFuncs;
    arqFuncs = fopen("funcionarios.txt","ab");

    FILE* arqVendas;
    arqVendas = fopen("vendas.txt","ab");

    int contVendas = contadorVendas(arqVendas);
    int contMed = contadorMed(arqMeds);
    int contFunc = contadorFunc(arqFuncs);

    if(arqMeds == NULL || arqFuncs == NULL || arqVendas == NULL)
    {
        printf("ERRO na abertura dos arquivos!!\n");
        system("pause");
        exit(1);
    }

    do
    {
        printLinha();
        printf("\nInforme o MENU de acesso:\n1- Medicamentos\n2- Funcionários\n3- Cadastrar Vendas\n4- Relatórios\n0- Encerrar\n");
        printLinha();
        scanf(" %d",&opt1);
        switch(opt1)
        {
            case 1:
                printLinha();
                printf("\nMENU MEDICAMENTOS\n\n"
                "1- Cadastrar Medicamento\n2- Consultar Medicamento(Descrição)\n3- Consultar Medicamento(ID)\n4- Alterar Medicamento\n5- Excluir Medicamento\n0- Menu Principal\n");
                printLinha();
                scanf(" %d",&optMed);

                switch(optMed)
                {
                    case 1:
                        medicamentos[contMed++] = setMed(arqMeds, contMed);
                        break;
                    case 2:
                        getMedDescricao(arqMeds, medicamentos,contMed);
                        break;
                    case 3:
                        getMedID(arqMeds, medicamentos,contMed);
                        break;
                    case 4:
                        alteraMed(arqMeds, medicamentos, contMed);
                        break;
                    case 5:
						break;
                    case 6:
                        break;

                    default:
                        printf("Favor inserir uma opção válida!!\n");
                        break;

                    case 0:
                        break;

                }
                break;

            case 2:
                printLinha();
                printf("\nMENU FUNCIONÁRIOS\n\n"
                "1- Cadastrar Funcionário\n2- Consultar Funcionário(Nome)\n3- Consultar Funcionário (ID)\n4- Alterar Funcionário\n5- Excluir Funcionário\n0- Menu Principal\n");
                printLinha();
                scanf(" %d",&optFunc);

                switch(optFunc)
                {
                    case 1:
                        funcionarios[contFunc++] = setFunc(arqFuncs, contFunc);
                        break;
                    case 2:
                        getFuncNome(arqFuncs, funcionarios,contFunc);
                        break;
                    case 3:
                        getFuncID(arqFuncs, funcionarios,contFunc);
                        break;
                    case 4:
                        alteraFunc(arqFuncs, funcionarios, contFunc);
                        break;
                    case 5:
                        break;
                    default:
                        printf("Favor inserir uma opção válida!!\n");
                        break;

                    case 0:
                        break;
                }
                break;

            case 3:
                vendas[contVendas++] = setVenda(arqMeds, arqFuncs, arqVendas, vendas,medicamentos,funcionarios,contVendas,contMed,contFunc);
                break;

            case 4:
                printLinha();
                printf("\nMENU RELATÓRIOS\n\n"
                "1- GERAL: Medicamentos\n2- GERAL: Funcionários\n3- GERAL: Vendas\n4- Medicamentos Mais Vendidos\n5- Vendas Ordenadas por Data\n0- Menu Principal\n");
                printLinha();
                scanf(" %d",&optRelat);
                switch(optRelat)
                {
                    case 1:
                        relatorioMedGeral(arqMeds, medicamentos, contMed);
                        break;
                    case 2:
                        relatorioFuncGeral(arqFuncs, funcionarios, contFunc);
                        break;
                    case 3:
                        relatorioVendasGeral(arqVendas, arqMeds, vendas, medicamentos, contVendas, contMed);
                        break;
                    case 4:
                     //   relatorioMedOrdenado(arqMeds, arqVendas, vendas, medicamentos, contVendas);
                        break;
                    case 5:
                     //   relatorioVendasOrdenado(arqVendas, vendas, medicamentos, contVendas);
                        break;
                    default:
                        printf("Favor inserir uma opção válida!!\n");
                        break;
                    case 0:
                        break;
                }

        }

    }while(opt1!=0);

    fclose(arqFuncs);
    fclose(arqMeds);
    fclose(arqVendas);
    exit(0);
}
