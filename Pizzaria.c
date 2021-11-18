#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <conio.h>
/////////////////////////////////////////////////////////
/////////DEFINICAO DOS STRUCTS///////////////////////////
/////////////////////////////////////////////////////////
typedef struct s_end
{
char rua[50];
int num;
char bairro[50];
} end;

typedef struct s_pessoa
{
    char telefone[15];
    char nome[50];
    end endereco;
}t_pessoa;

typedef struct s_cli
{
    t_pessoa pessoa;
}cli;

typedef struct s_mot
{
    t_pessoa pessoa;
    int cod;
}mot;

typedef struct s_pizza
{
    int cod;
    char nome[50];
    float preco;
}pizza;

typedef struct s_pedido
{
    int cod_ped;
    char telefone[15];
    int cod_pizza;
    int cod_mot;
    int situacao;
}pedidos;
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//////////////////////DECLARAÇÃO DAS FUNÇÕES///////////////////////
///////////////////////////////////////////////////////////////////

////////////CADASTRO///////////////////////////////////////////////
int cadastro_cli(cli *c, int *pos);
int cadastro_mot(mot *mot, int *pos);
int cadastro_pizza(pizza *p, int *pos);
//////////////////////////////PEDIDOS//////////////////////////////
int cadastro_pedido(pedidos *ped, int *pos, cli *c, int pos2, pizza *p, int pos3);
int despacha_pizza(pedidos *ped, int pos, mot *mot, int qnt_mot);
void entrega_pizza(pedidos *ped, int pos);
/////////////////////////////LISTAS////////////////////////////////
int pedidos_situacao(pedidos *ped, int cont_ped, int sit);
int pedidos_cliente(pedidos *ped, int cont_ped, char *tel);
int pedidos_m(pedidos *ped, int cont_ped, int cod_m);
////////////////////////////BUSCADORAS/////////////////////////////
int busca_mot(mot *mot, int cod, int pos);
int busca_ped(pedidos *ped, int cod, int pos);
int busca_cli(cli *c, char *tel, int pos);
int busca_pizza(pizza *p, int cod, int pos);
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

int main()
{
    const int c_cli = 5;
    const int c_pizza = 3;
    const int c_ped = 6;
    const int c_mot = 2;

    int cont_c=0,cont_m=0,cont_p=0,cont_ped=0;

    cli c[c_cli];
    mot mot[c_mot];
    pizza p[c_pizza];
    pedidos ped[c_ped];

    char aux_s[50];
    int op,ret,aux;

    do
    {
  /*printf("1: Cadastrar como cliente\n");
    printf("2: Cadastrar como motoboy\n");
    printf("3: Cadastrar pizza\n");
    printf("4: Cadastrar pedido\n");
    printf("5: Despacho da pizza\n");
    printf("6: Recebimento da pizza\n");
    printf("7: Listar pedidos por situação\n");
    printf("8: Listar pedidos de um cliente\n");
    printf("9: Listar pedidos por motoqueiro\n");
    printf("0: Sair\n");*/

    //printf("Opção: ");
    scanf("%d",&op);
    //fflush(stdin);

    
        switch(op)
        {
            case 1:
                {
                    if(cont_c < c_cli)
                    {
                        ret = cadastro_cli(c,&cont_c);

                        if(ret == 0)
                        {
                         printf("Cliente ja cadastrado\n");
                        }
                        else 
                            {                                
                             printf("Cliente cadastrado com sucesso\n");  
                            }

                    } else printf("Numero maximo de clientes cadastrados\n");
                    break;
                }
            case 2:
                {
                    if(cont_m < c_mot)
                    {
                        ret = cadastro_mot(mot,&cont_m);

                        if(ret==0)
                        {
                            printf("Motoqueiro ja cadastrado\n");
                        } 
                        else
                            {
                                printf("Motoqueiro cadastrado com sucesso\n");
                            }
                        
                    } else printf("Numero maximo de motoqueiros cadastrados\n");
                    break;
                }
            case 3:
                {
                    if(cont_p < c_pizza)
                    {
                        ret = cadastro_pizza(p,&cont_p);

                        if(ret == 0)
                        {
                            printf("Pizza ja cadastrada\n");
                        } else
                            {
                                printf("Pizza cadastrada com sucesso\n");
                            }
                    } else printf("Numero maximo de pizzas cadastrados\n");
                    break;
                }
            case 4:
                {
                    ret = cadastro_pedido(ped,&cont_ped, c, cont_c, p, cont_p);
             
                    if (ret == 1)
                    {
                        if(cont_ped < c_ped)
                        {
                            
                            printf("Pedido cadastrado\n");
                            break;
                        } 
                        else {
                            printf("Numero maximo de pedidos realizados\n");
                            break;
                        }
                    }

                    if(ret == 2)
                    {
                        printf("Cliente nao encontrado\n");
                    }
                    if(ret == 3)
                    {
                        printf("Pizza nao cadastrada\n");
                    }
                    break;
                }
            case 5:
                {
                    //printf("Código do pedido: ");
                    scanf("%d",&aux);
                    //fflush(stdin);

                    ret = busca_ped(ped,aux,c_ped);

                    if(ret == 1)
                    {
                        printf("Pedido nao encontrado\n");
                        break;
                    } else {

                        ret = despacha_pizza(ped,aux,mot,c_mot);

                        if(ret == 2)
                        {
                        printf("Motoqueiro nao encontrado\n");
                        break;
                        } else {
                                if(ret == 1)
                                {
                                    printf("Despachando pedido\n");
                                    break;
                                }
                                if(ret == 3)
                                {
                                    printf("Pedido ja despachado\n");
                                    break;
                                }
                                if(ret == 4)
                                {
                                    printf("Pedido ja entregue\n");
                                    break;
                                }                 
                        }      
                    }
                }
            case 6:
                {
                    //printf("Código do pedido: ");
                    scanf("%d",&aux);
                    //fflush(stdin);

                    ret = busca_ped(ped,aux,c_ped);
                    if(ret == 0)
                    {
                        if(ped[aux].situacao == 2)
                        {
                        entrega_pizza(ped,aux);
                        printf("Pedido entregue\n");
                        break;  
                        }

                        if(ped[aux].situacao == 3)
                        {
                        printf("Entrega ja realizada\n");
                        break;
                        }

                    } else {
                        if(ret == 1 || ped[aux].situacao == 1)
                        printf("Pedido nao encontrado\n");
                        break;
                    }
                }
            case 7:
                {
                    //printf("Situação: ");
                    scanf("%d",&aux);
                    //fflush(stdin);

                    if(aux != 1 && aux != 2 && aux != 3)
                    {
                    printf("Opcao invalida\n");
                    break;
                    }
                    else {
                        ret = pedidos_situacao(ped,cont_ped,aux);
                        if(ret == 1)
                        {
                            printf("Sem itens nessa situacao\n");
                            break;
                        }
                        break;
                    }
                }
            case 8:
                {
                    //printf("Telefone: ");
                    scanf(" %[^\n]",aux_s);
                    //fflush(stdin);

                    ret = busca_cli(c,aux_s,c_cli);
                    
                    if(ret == 0)
                    {
                        ret = pedidos_cliente(ped,cont_ped,aux_s);
                        if(ret == 1)
                        {
                            printf("Cliente sem pedidos\n");
                            break;
                        } 
                     break;
                    } else {
                        printf("Cliente nao encontrado\n");
                        break;
                    }
                }
            case 9:
                {
                    //printf("Código do motoqueiro: ");
                    scanf("%d",&aux);
                    //fflush(stdin);

                    ret = busca_mot(mot,aux,c_mot);

                    if(ret==0)
                    {
                        ret = pedidos_m(ped,cont_ped,aux);
                        if(ret==1)
                        {
                            printf("Motoqueiro sem pedidos\n");
                            break;
                        }
                        break;
                    } else {
                        printf("Motoqueiro nao encontrado\n");
                        break;
                    }
                }
            case 0:
                {
                    printf("Encerrando sistema\n");
                    break;
                }
            default: printf("Opcao invalida\n");
                    break;
        }
        
    } while (op != 0);


  return 0;  
}

//////////CADASTROS/////////////////////////////////////////////////


int cadastro_cli(cli *c, int *pos)
{
    int i,j;
    i = *pos;
    //printf("Telefone: ");
    scanf(" %[^\n]",c[i].pessoa.telefone);   
    //fflush(stdin);
    
    for(j=0; j < *pos; j++)
    {
        if(strcmp(c[i].pessoa.telefone,c[j].pessoa.telefone)==0)
        return 0;
    }

    //printf("\nNome: ");
    scanf(" %[^\n]",c[i].pessoa.nome);
    //fflush(stdin);

    //printf("Endereço:\n");

    //printf("\nRua: ");
    scanf(" %[^\n]",c[i].pessoa.endereco.rua);
    //fflush(stdin);

    //printf("\nNumero");
    scanf("%d",&c[i].pessoa.endereco.num);
    //fflush(stdin);

    //printf("\nBairro");
    scanf(" %[^\n]",c[i].pessoa.endereco.bairro);
    //fflush(stdin);

    *pos = *pos + 1;
    return 1;
}

int cadastro_mot(mot *mot, int *pos)
{
    int i = *pos,j;

    //printf("Codigo: ");
    scanf("%d",&mot[i].cod);
    //fflush(stdin);

    for(j=0;j<*pos;j++)
    {
        if(mot[i].cod == mot[j].cod)
        return 0;
    }

    //printf("Telefone: ");
    scanf(" %[^\n]",mot[i].pessoa.telefone);
    //fflush(stdin);

    //printf("\nNome: ");
    scanf(" %[^\n]",mot[i].pessoa.nome);
    //fflush(stdin);

    //printf("Endereço:\n");

    //printf("\nRua: ");
    scanf(" %[^\n]",mot[i].pessoa.endereco.rua);
    //fflush(stdin);

    //printf("\nNumero");
    scanf("%d",&mot[i].pessoa.endereco.num);
    //fflush(stdin);

    //printf("\nBairro");
    scanf(" %[^\n]",mot[i].pessoa.endereco.bairro);
    //fflush(stdin);

    *pos = *pos + 1;
    return 1;
}

int cadastro_pizza(pizza *p, int *pos)
{
    int i = *pos,j;

    //printf("Código: ");
    scanf("%d",&p[i].cod);
    //fflush(stdin);

    for(j=0;j<*pos;j++)
    {
       if(p[i].cod == p[j].cod)
       return 0; 
    }

    //printf("Nome: ");
    scanf(" %[^\n]",p[i].nome);
    //fflush(stdin);

    //printf("Preço: ");
    scanf("%f",&p[i].preco);
    //fflush(stdin);

    *pos = *pos + 1;
    return 1;
}

//////////////////PEDIDOS/////////////////////////////////////////////
int cadastro_pedido(pedidos *ped, int *pos, cli *c, int pos2, pizza *p, int pos3)
{
    int i,ret;
    i = *pos;

    ped[i].cod_ped = i;
    ped[i].situacao = 1;
    ped[i].cod_mot = 0;

    //printf("Telefone do cliente: ");
    scanf(" %[^\n]",ped[i].telefone);
    //fflush(stdin);

    ret = busca_cli(c,ped[i].telefone,pos2);

    if(ret==1)
    return 2;

    //printf("Código da pizza: ");
    scanf("%d",&ped[i].cod_pizza);

    ret = busca_pizza(p,ped[i].cod_pizza,pos3);

    if(ret)
    return 3;

    *pos = *pos + 1;
    return 1;
}

int despacha_pizza(pedidos *ped, int pos, mot *mot, int qnt_mot)
{
    int ret;

     if(ped[pos].situacao == 2)
    return 3;

    if(ped[pos].situacao == 3)
    return 4;
    //printf("Código do motoqueiro: ");
    scanf("%d",&ped[pos].cod_mot);
    //fflush(stdin);

    ret = busca_mot(mot,ped[pos].cod_mot,qnt_mot);
    if(ret == 1)
    return 2;

    ped[pos].situacao = 2;
    return 1;
}

void entrega_pizza(pedidos *ped, int pos)
{
    ped[pos].situacao = 3;
}

////////////////LISTAS/////////////////////////////////////////////
int pedidos_situacao(pedidos *ped, int cont_ped, int sit)
{
    int i,cont=0;

    for(i=0;i<cont_ped;i++)
    {
        if(ped[i].situacao == sit)
        {
            printf("Pedido: %d\n",ped[i].cod_ped);
            printf("Cliente: %s\n",ped[i].telefone);
            printf("Pizza: %d\n",ped[i].cod_pizza);
            printf("Motoq: %d\n",ped[i].cod_mot);
            cont++;
        }
    }
    if(cont == 0)
    return 1;
    else
    return 0;
}

int pedidos_cliente(pedidos *ped, int cont_ped, char *tel)
{
    int i,cont=0;

    for(i=0;i<cont_ped;i++)
    {
        if(strcmp(ped[i].telefone,tel) == 0)
        {
            printf("Pedido: %d\n",ped[i].cod_ped);
            printf("Situacao: %d\n",ped[i].situacao);
            printf("Pizza: %d\n",ped[i].cod_pizza);
            printf("Motoq: %d\n",ped[i].cod_mot);
            cont++;
        }
    }
    if(cont == 0)
    return 1;
    else
    return 0;
}

int pedidos_m(pedidos *ped, int cont_ped, int cod_m)
{
    int i,cont=0;

    for(i=0;i<cont_ped;i++)
    {
        if(ped[i].cod_mot == cod_m)
        {
            printf("Pedido: %d\n",ped[i].cod_ped);
            printf("Situacao: %d\n",ped[i].situacao);
            cont++;
        }
    }
    if(cont == 0)
    return 1;
    
    return 0;
}

int busca_mot(mot *mot, int cod, int qnt)
{
    int i;

    for(i=0;i<qnt;i++)
    {
        if(cod == mot[i].cod)
        return 0;
    }
    return 1;

}
int busca_ped(pedidos *ped, int pos, int qnt)
{
    int i;

    for(i=0;i<qnt;i++)
    {
        if(ped[i].cod_ped == pos)
        return 0;
    }

    return 1;
}

int busca_cli(cli *c, char *tel, int pos)
{
    int i;

    for(i=0;i<pos;i++)
    {
        if(strcmp(tel,c[i].pessoa.telefone) == 0)
        return 0;
    }
    return 1;
}

int busca_pizza(pizza *p, int cod, int qnt)
{
    int i;
    for(i=0;i<qnt;i++)
    {
        if(cod == p[i].cod)
        return 0;
    }
    return 1;
}