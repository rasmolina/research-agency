//PROJETO PRÁTICO DE APII - PARTE 2
//TEMA 15: Gerenciamento de pesquisa de opinião pública 
//NOME: Roberto Augusto Silva Molina
//PRONTUÁRIO: SC3012905

#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<string.h>
#define tam 100

// ESTRUTURAS DE DADOS ========================================================================
struct Pessoa{
	int cpfP;
	char nome[40];
	char nasc[11];
	char sexo;
	char fone[5][25];
	char escolaridade[30];
	int numTel;
};

struct Pesquisa{
	int codP;
	char descri[50];
};

struct Resposta{
	int cpfR;
	int codR;
	char data[11];
	char resp[40];
};
//===============================================================================================

int chamar_menu(){
	int op;
	printf("\n\n> > >AGÊNCIA DE PESQUISAS< < <\n\n");
	printf("***MENU PRINCIPAL***\n\n");
	printf("\t[1] Pessoas\n\t[2] Pesquisa\n\t[3] Respostas\n\t[4] Relatórios\n\t[5] Sair\n");
	printf("\n\tEscolha uma opção do menu:\n");
	scanf("%d",&op);
	fflush(stdin);
	return op;
}

int chamar_submenu(){
	int op;
	printf("\n");
	printf("\t[1] Listar tudo\n\t[2] Listar um elemento\n\t[3] Incluir\n\t[4] Alterar\n\t[5] Excluir");
	printf("\n\tEscolha uma opção:\n");
	scanf("%d",&op);
	fflush(stdin);
	return op;
}

int chamar_menu_relatorios(){
	int op;
	printf("\n");
	printf("\t[1] Telefones por CPF\n\t[2] Respostas por pesquisa\n\t[3] Pesquisas realizadas por data");
	printf("\n\tEscolha uma opção:\n");
	scanf("%d",&op);
	fflush(stdin);
	return op;
}

//Função para verificar se já existe cadastrado o CPF da pessoa
int verificar_CPF(int CPF){
	Pessoa *vet_pep;
	vet_pep=(Pessoa *)calloc(1,sizeof(Pessoa));
	FILE *arqPessoa;
	if ((arqPessoa=fopen("arq_pessoas.txt","rb"))==NULL)
		return -1;
	else
	{
		int i=0;
		fread(vet_pep,sizeof(Pessoa),1, arqPessoa); //Faço a leitura de um registro por vez
		while(!feof(arqPessoa)){
			if (CPF == vet_pep->cpfP)
			{
				return i;
			}	
			i++;
			fread(vet_pep,sizeof(struct Pessoa),1,arqPessoa);
		}
		return -1;
	}
	fclose(arqPessoa);	
}

//Função para verificar se já existe cadastrado o código da pesquisa
int verificar_codigo_pesquisa(int codigo){
	Pesquisa *vet_pesq;
	vet_pesq=(Pesquisa *)calloc(1,sizeof(Pesquisa));
	FILE *arqPesquisa;
	if ((arqPesquisa=fopen("arq_pesquisa.txt","rb"))==NULL)
		return -1;
	else{
		int i=0;
		fread(vet_pesq,sizeof(Pesquisa),1, arqPesquisa); //Faço a leitura de um registro por vez
		while(!feof(arqPesquisa)){
			if (codigo == vet_pesq->codP){
				return i;
			}	
			i++;
			fread(vet_pesq,sizeof(struct Pesquisa),1,arqPesquisa);
		}
		return -1;
	}
	fclose(arqPesquisa);	
}

//Função para verificar se já existe cadastrado o código da resposta
int verificar_resposta_especifica(int codigo){
	Resposta *vet_resp;
	vet_resp=(Resposta *)calloc(1,sizeof(Resposta));
	FILE *arqResposta;
	if ((arqResposta=fopen("arq_resposta.txt","rb"))==NULL)
		return -1;
	else{
		int i=0;
		fread(vet_resp,sizeof(Resposta),1, arqResposta); //Faço a leitura de um registro por vez
		while(!feof(arqResposta)){
			if (codigo == vet_resp->codR){
				printf("\n------------------");
				printf("\nCPF: %d",vet_resp->cpfR);
				printf("\nData da resposta: %s",vet_resp->data);
				printf("\nResposta: %s",vet_resp->resp);
				printf("\n------------------");
			}	
			i++;
			fread(vet_resp,sizeof(struct Resposta),1,arqResposta);
		}
	}
	free(vet_resp);
	fclose(arqResposta);	
}

//Função para verificar se já existe cadastrado o CPF, Código da Pesquisa e Data no banco de dados de resposta
int validar_resposta(int CPF, int cod, char *data){
	Resposta *vet_resp;
	vet_resp=(Resposta *)calloc(1,sizeof(Resposta));
	FILE *arqResposta;
	if ((arqResposta=fopen("arq_resposta.txt","rb"))==NULL)
		return -1;
	else
	{
		int i=0;
		fread(vet_resp,sizeof(Resposta),1, arqResposta); //Faço a leitura de um registro por vez
		while(!feof(arqResposta)){
			if (CPF == vet_resp->cpfR && cod == vet_resp->codR && strcmp(data,vet_resp->data)==0)
			{
				return i;
			}	
			i++;
			fread(vet_resp,sizeof(struct Resposta),1,arqResposta);
		}
		return -1;
	}
	fclose(arqResposta);	
}

//Função para cadastrar uma pessoa
void cadastrar_pessoa(int CPF){
	Pessoa *vet_pep;
	fflush(stdin);
	vet_pep->cpfP=CPF;
	fflush(stdin);
	puts("\nDigite o Nome:");
	gets(vet_pep->nome);
	puts("\nDigite a Data de Nascimento [dd/mm/aaaa]:");
	gets(vet_pep->nasc);
	puts("\nDigite o sexo(M/F):");
	scanf("%c",&vet_pep->sexo);	

	//Laço para cadastrar 1 ou mais telefones (limite de 5 telefones)
	int mais = 1, i;	
	for(i = 0; i < 5 && mais == 1; i++){ //laço para cadastrar vários telefones
		fflush(stdin);
		puts("\nDigite o telefone do cliente:\n");
		gets(vet_pep->fone[i]);
		printf("\nDeseja adicionar mais telefones? sim (1) ou não (0)\n");
		scanf("%d", &mais);
	}
	vet_pep->numTel = i;
	mais = 1;
	//--------------------------s
	fflush(stdin);
	puts("\nDigite a escolaridade:");
	gets(vet_pep->escolaridade);	
		
	//Parte que grava os dados da struct no arquivo
	puts("\nGravando no arquivo...");
	FILE *arqPessoa;
	if((arqPessoa = fopen ("arq_pessoas.txt","ab"))== NULL){
		printf("Não foi possível abrir o arquivo!");
		exit(0);
	}
	else
		fwrite(vet_pep, sizeof(Pessoa), 1, arqPessoa);
	fflush(stdin);
	fclose(arqPessoa);
	printf("\nCADASTRO EFETUADO COM SUCESSO!");
}

//Função para cadastrar uma pesquisa
void cadastrar_pesquisa(){
	int codigo, resultado;
	Pesquisa *vet_pesq;
	FILE * arqPesquisa;

	printf("Cadastrando pesquisa...\n");
	printf("\nDigite o código (apenas números):");
	scanf("%d",&codigo);
	resultado = verificar_codigo_pesquisa(codigo);
	if (resultado == -1){
		fflush(stdin);
		vet_pesq->codP = codigo;
		fflush(stdin);
		puts("\nDigite a descrição:");
		gets(vet_pesq->descri);
		
		//Parte que grava os dados da struct no arquivo
		puts("\nGravando no arquivo...");
		if((arqPesquisa = fopen ("arq_pesquisa.txt","ab"))== NULL){
			printf("Não foi possível abrir o arquivo!");
			exit(0);
		}
		else
			fwrite(vet_pesq, sizeof(Pesquisa), 1, arqPesquisa);
		fflush(stdin);
		fclose(arqPesquisa);
		printf("\nCADASTRO EFETUADO COM SUCESSO!");
	}
	else
		printf("\n\nCÓDIGO JÁ CADASTRADO!\n");
}

//Função para cadastrar uma resposta
void cadastrar_resposta(int CPF, int codigo){
	int resultado;
	Resposta *vet_resp;
	FILE * arqResposta;
	char data_resp[11];
	fflush(stdin);
	puts("\nDigite a data [dd/mm/aaaa]:");
	gets(data_resp);
	resultado = validar_resposta(CPF, codigo, data_resp);
	if (resultado == -1){
		fflush(stdin);
		vet_resp->cpfR = CPF;
		vet_resp->codR = codigo;
		strcpy(vet_resp->data, data_resp);
		fflush(stdin);
		puts("\nDigite a resposta:");
		gets(vet_resp->resp);
		
		//Parte que grava os dados da struct no arquivo
		puts("\nGravando no arquivo...");
		if((arqResposta = fopen ("arq_resposta.txt","ab"))== NULL){
			printf("Não foi possível abrir o arquivo!");
			exit(0);
		}
		else
			fwrite(vet_resp, sizeof(Resposta), 1, arqResposta);
		fflush(stdin);
		fclose(arqResposta);
		printf("\nCADASTRO EFETUADO COM SUCESSO!");
	}
	else
		printf("\nJÁ EXISTE UMA RESPOSTA DESTA PESQUISA PARA ESTE CPF CADASTRADA NESTA DATA!");
}

//Função para listar todas as pessoas cadastradas
void listar_pessoa(){
	Pessoa *vet_pep;
	vet_pep=(Pessoa *)calloc(1,sizeof(Pessoa));
	FILE *arqPessoa;
	int verificador=0;
	if ((arqPessoa=fopen("arq_pessoas.txt","rb"))==NULL){
		printf("ARQUIVO NÃO LOCALIZADO");
		verificador=1;
	}
	else{
		//Faço a leitura de um registro por vez
		fread(vet_pep,sizeof(Pessoa),1, arqPessoa);
		while(!feof(arqPessoa)){
			printf("CPF: %d\n", vet_pep->cpfP);
			printf("Nome: %s\n", vet_pep->nome);
			printf("Data de nascimento: %s\n", vet_pep->nasc);
			printf("Sexo: %c\n", vet_pep->sexo);
			printf("Escolaridade: %s\n", vet_pep->escolaridade);
		
			//Laço para listar todos os telefones cadastrados
			for(int j = 0; j < vet_pep->numTel; j++){ //percorre os telefones cadastrados
				printf("Telefone %d do cliente: %s\n", j+1, vet_pep->fone);
			}
			printf("--------------------\n");
			fread(vet_pep,sizeof(Pessoa),1, arqPessoa);
			verificador+=1;
		}
	}
	free(vet_pep);
	fclose(arqPessoa);
	if (verificador == 0)
		printf("NÃO HÁ PESSOAS CADASTRADAS!");
}

//Função para listar todas as pesquisas
//void listar_pesquisa(Pesquisa vet_pesq[], int cont){
void listar_pesquisa(){	
	int verificador = 0;
	Pesquisa *vet_pesq;
	vet_pesq=(Pesquisa *)calloc(1,sizeof(Pesquisa));
	FILE *arqPesquisa;
	if ((arqPesquisa=fopen("arq_pesquisa.txt","rb"))==NULL){
		printf("ARQUIVO NÃO LOCALIZADO!");
		verificador=1;
	}
	else{
		fread(vet_pesq,sizeof(Pesquisa),1, arqPesquisa); //Faço a leitura de um registro por vez
		while(!feof(arqPesquisa)){
			printf("Código: %d\n", vet_pesq->codP);
			printf("Descrição: %s\n", vet_pesq->descri);
			printf("--------------------\n");
			fread(vet_pesq,sizeof(struct Pesquisa),1,arqPesquisa); //Leio o próximo registro
			verificador+=1;
		}
	}
	fclose(arqPesquisa);
	if (verificador == 0)
		printf("NÃO HÁ PESQUISAS CADASTRADAS!");
}

//Função para listar todas as respostas
void listar_resposta(){
	int verificador=0;
	Resposta *vet_resp;
	vet_resp=(Resposta *)calloc(1,sizeof(Resposta));
	FILE *arqResposta;
	if ((arqResposta=fopen("arq_resposta.txt","rb"))==NULL){
		printf("ARQUIVO NÃO LOCALIZADO!");
		verificador=1;
	}
	else{
		fread(vet_resp,sizeof(Resposta),1, arqResposta); //Faço a leitura de um registro por vez
		while(!feof(arqResposta)){
			printf("Código da Pesquisa: %d\n", vet_resp->codR);
			printf("CPF: %d\n", vet_resp->cpfR);
			printf("Data: %s\n", vet_resp->data);
			printf("Resposta: %s\n", vet_resp->resp);
			printf("--------------------\n");
			fread(vet_resp,sizeof(struct Resposta),1,arqResposta); //Leio o próximo registro
			verificador+=1;
		}
	}
	fclose(arqResposta);	
	if (verificador == 0)
		printf("NÃO HÁ RESPOSTAS CADASTRADAS!");
}

//Função para listar uma resposta específica
void listar_resposta_especifica(){
	Resposta *vet_resp;
	vet_resp=(Resposta *) calloc(1, sizeof(Resposta)); //alocação dinâmica
	int pos=-1;
	int codigo;
	//Uma pesquisa pode ter várias repostas por dia e por CPF
	//Só não pode ter no mesmo dia pelo mesmo CPF
	printf("Digite o código da pesquisa para busca: ");
	scanf("%d",&codigo);
	pos=verificar_resposta_especifica(codigo);
	if(pos==-1)
		printf("\nCÓDIGO DE PESQUISA %d NÃO LOCALIZADO!", codigo);
}

//Função para alterar uma pessoa cadastrada
void alterar_pessoa(){
	Pessoa *vet_pep;
	vet_pep=(Pessoa *) calloc(1, sizeof(Pessoa));
	int pos;
	int cpf;
	fflush(stdin);
	printf("\nDigite o CPF da pessoa que deseja alterar: ");
	scanf("%d",&cpf);
	pos=verificar_CPF(cpf);
	if(pos!=-1)
	{
		FILE *arqPessoa;
		if((arqPessoa=fopen("arq_pessoas.txt", "rb+"))==NULL)
		{
			printf("NÃO FOI POSSÍVEL ABRIR OS REGISTROS!");
			//exit(1);
		}
		else
		{
			int i=0, verificador=0;
			while(!feof(arqPessoa) && verificador==0)
			{
				if(i!=pos)
				{
					i++;
					fread(vet_pep, sizeof(Pessoa), 1, arqPessoa);
				}
				else
				{
					vet_pep->cpfP=cpf;
					fflush(stdin);
					printf("\nInforme o nome atualizado:");
					gets(vet_pep->nome);
					printf("\nInforme a Data de Nascimento atualizada (dd/mm/aaaa):");
					gets(vet_pep->nasc);
					printf("\nDigite o sexo(M/F) atualizado:");
					scanf("%c",&vet_pep->sexo);	
					
					//Laço para alterar os telefones cadastrados
					int mais = 1, i;	
					for(i = 0; i < 5 && mais == 1; i++){
						fflush(stdin);
						puts("\nDigite o telefone atualizado do cliente:\n");
						gets(vet_pep->fone[i]);
						printf("\nDeseja alterar ou adicionar mais telefones? sim (1) ou não (0)\n");
						scanf("%d", &mais);
					}
					vet_pep->numTel = i;
					mais = 1;
					//--------------------------
					fflush(stdin);
					printf("\nDigite a escolaridade atualizada:");
					gets(vet_pep->escolaridade);	
					
					fseek(arqPessoa, 0, SEEK_CUR);
					fwrite(vet_pep, sizeof(Pessoa), 1, arqPessoa);
					verificador=1;
					free(vet_pep);
					fclose(arqPessoa);
					fflush(stdin);
					printf("\nCADASTRO ALTERADO COM SUCESSO!");
				}
			}
		}
	}
	else
		printf("\nCPF %d NÃO LOCALIZADO!", cpf);
}

//Função para alterar uma pesquisa cadastrada
void alterar_pesquisa(){
	Pesquisa *vet_pesq;
	vet_pesq=(Pesquisa *) calloc(1, sizeof(Pesquisa));
	int pos;
	int codigo;
	fflush(stdin);
	printf("\nDigite o código da pesquisa que deseja alterar: ");
	scanf("%d",&codigo);
	pos=verificar_codigo_pesquisa(codigo);
	if(pos!=-1)
	{
		FILE *arqPesquisa;
		if((arqPesquisa=fopen("arq_pesquisa.txt", "rb+"))==NULL)
		{
			printf("NÃO FOI POSSÍVEL ABRIR OS REGISTROS!");
		}
		else
		{
			int i=0, verificador=0;
			while(!feof(arqPesquisa) && verificador==0)
			{
				if(i!=pos)
				{
					i++;
					fread(vet_pesq, sizeof(Pesquisa), 1, arqPesquisa);
				}
				else
				{
					vet_pesq->codP=codigo;
					fflush(stdin);
					printf("\nInforme a descrição atualizada: ");
					gets(vet_pesq->descri);
					
					fseek(arqPesquisa, 0, SEEK_CUR); // localiza
					fwrite(vet_pesq, sizeof(Pesquisa), 1, arqPesquisa);
					verificador=1;
					free(vet_pesq);
					fclose(arqPesquisa);
					fflush(stdin);
					printf("\nCADASTRO ALTERADO COM SUCESSO!");
				}
			}
		}
	}
	else
		printf("\nCÓDIGO %d NÃO LOCALIZADO!", codigo);
}

//Função para alterar uma resposta cadastrada
int alterar_resposta(int posicao, int cpf, int codigo, char data[11]){
	Resposta *vet_resp;
	vet_resp=(Resposta *) calloc(1, sizeof(Resposta));
	FILE *arqResposta;
	if((arqResposta=fopen("arq_resposta.txt", "rb+"))==NULL){
		printf("NÃO FOI POSSÍVEL ABRIR OS REGISTROS!");
	}
	else{
		int i=0, verificador=0;
		while(!feof(arqResposta) && verificador==0){
			if(i!=posicao)
			{
				i++;
				fread(vet_resp, sizeof(Resposta), 1, arqResposta);
			}
			else
			{
				fflush(stdin);
				vet_resp->codR = codigo;
				vet_resp->cpfR = cpf;
				strcpy(vet_resp->data, data);
				printf("\nInforme a resposta atualizada: ");
				gets(vet_resp->resp);
				
				fseek(arqResposta, 0, SEEK_CUR); // localiza
				fwrite(vet_resp, sizeof(Resposta), 1, arqResposta);
				verificador=1;
				free(vet_resp);
				fclose(arqResposta);
				fflush(stdin);
			}
		}
	}
}

//Função para excluir uma pessoa cadastrada
void excluir_pessoa(){
	Pessoa *vet_pep;
	vet_pep=(Pessoa *) calloc(1, sizeof(Pessoa));
	int i, posicao;
	int cpf;
	printf("\nDigite o CPF da pessoa que deseja excluir: ");
	scanf("%d",&cpf);
	posicao=verificar_CPF(cpf);
	if(posicao!=-1){ //se for localizado o registro
		FILE *arqPessoa;
		if((arqPessoa=fopen("arq_pessoas.txt", "rb+"))==NULL)
		{
			printf("NÃO FOI POSSÍVEL ABRIR OS REGISTROS!");
			exit(1);
		}
		else
		{
			int i=0, verificador=0, cont;
			while(!feof(arqPessoa) && verificador==0) //percorre todos os registros
			{
				if(i!=posicao) //laço que percorre cada registro enquanto não for igual do cpf
				{
					i++;
					fread(vet_pep, sizeof(Pessoa), 1, arqPessoa);
				}
				else
				{
					//Reposiciona o indicador de posição do fluxo em função do deslocamento.
					fseek(arqPessoa, 0, SEEK_CUR); //posição atual do arquivo
					int flag=0;
					while(!feof(arqPessoa) && flag==0)
					{
						vet_pep[i]=vet_pep[i+1];
						fwrite(vet_pep+i, sizeof(Pessoa), 1, arqPessoa); //exclusão
						flag=1;
					}
					verificador=1;
					free(vet_pep); //
					fclose(arqPessoa);
					fflush(stdin);
					printf("\nPESSOA REMOVIDA COM SUCESSO!\n");				}
			}
		}
	}
	else
		printf("\nCPF %d NÃO LOCALIZADO!", cpf);
}

//Função para excluir uma pesquisa cadastrada
void excluir_pesquisa(){
	Pesquisa *vet_pesq;
	vet_pesq=(Pesquisa *) calloc(1, sizeof(Pesquisa));
	int i, posicao;
	int codigo;
	printf("\nDigite o código da pesquisa que deseja excluir: ");
	scanf("%d",&codigo);
	posicao=verificar_codigo_pesquisa(codigo);
	if(posicao!=-1){ //se for localizado o registro
		FILE *arqPesquisa;
		if((arqPesquisa=fopen("arq_pesquisa.txt", "rb+"))==NULL)
		{
			printf("NÃO FOI POSSÍVEL ABRIR OS REGISTROS!");
			exit(1);
		}
		else
		{
			int i=0, verificador=0, cont;
			while(!feof(arqPesquisa) && verificador==0) //percorre todos os registros
			{
				if(i!=posicao) //laço que percorre cada registro enquanto não for igual do codigo
				{
					i++;
					fread(vet_pesq, sizeof(Pesquisa), 1, arqPesquisa);
				}
				else
				{
					//Reposiciona o indicador de posição do fluxo em função do deslocamento.
					fseek(arqPesquisa, 0, SEEK_CUR); //posição atual do arquivo
					int flag=0;
					while(!feof(arqPesquisa) && flag==0)
					{
						vet_pesq[i]=vet_pesq[i+1];
						fwrite(vet_pesq+i, sizeof(Pesquisa), 1, arqPesquisa);
						flag=1;
					}
					verificador=1;
					free(vet_pesq);
					fclose(arqPesquisa);
					fflush(stdin);
					printf("\nPESQUISA REMOVIDA COM SUCESSO!\n");				}
			}
		}
	}
	else
		printf("\nCÓDIGO %d NÃO LOCALIZADO!", codigo);
}

//Função para excluir uma resposta cadastrada
void excluir_resposta(int posicao){
	Resposta *vet_resp;
	vet_resp=(Resposta *) calloc(1, sizeof(Resposta));
	FILE *arqResposta;
	if((arqResposta=fopen("arq_resposta.txt", "rb+"))==NULL){
		printf("NÃO FOI POSSÍVEL ABRIR OS REGISTROS!");
		exit(1);
	}
	else
	{
		int i=0, verificador=0;
		while(!feof(arqResposta) && verificador==0){ //percorre todos os registros
			if(i!=posicao) //laço que percorre cada registro enquanto não for igual do codigo
			{
				i++;
				fread(vet_resp, sizeof(Resposta), 1, arqResposta);
			}
			else{
				//Reposiciona o indicador de posição do fluxo em função do deslocamento.
				fseek(arqResposta, 0, SEEK_CUR); //posição atual do arquivo
				int flag=0;
				while(!feof(arqResposta) && flag==0)
				{
					vet_resp[i]=vet_resp[i+1];
					fwrite(vet_resp+i, sizeof(Resposta), 1, arqResposta);
					flag=1;
				}
				verificador=1;
				free(vet_resp);
				fclose(arqResposta);
				fflush(stdin);
				printf("\nRESPOSTA REMOVIDA COM SUCESSO!\n");
			}
		}
	}
}


//Função para gerar o relatório de respostas por codigo
void gerar_relatorio_resposta_por_codigo(Resposta *vet_resp, int codigo, char *data_resp, int *cont_resposta){
	int i;
	for(i=0; i<*cont_resposta; i++)
	{
		if (codigo == vet_resp[i].codR && strcmp(data_resp,vet_resp[i].data)==0)
			printf("\nCPF: %d - RESPOSTA: %s",vet_resp[i].cpfR,vet_resp[i].resp);
	}
}

//Função para gerar o relatório de respostas por data
void gerar_relatorio_pesquisa_por_data(Resposta *vet_resp, Pesquisa *vet_pesq, char *dt_ini, char *dt_fin, int *cont_resposta, int *cont_pesquisa){
	int i, posicao;
	for(i=0; i<*cont_resposta; i++)
	{
		if (strcmp(vet_resp[i].data,dt_ini)>=0 || strcmp(vet_resp[i].data,dt_fin)<=0)
			posicao = verificar_codigo_pesquisa(vet_resp[i].codR);
			printf("\nCódigo: %d - Descrição: %s",vet_resp[i].codR,vet_pesq[posicao].descri);
	}
	if (*cont_resposta == 0)
		printf("NÃO HÁ DADOS CADASTRADOS!");
}

//Função para listar uma pessoa específica de acordo com o CPF
void listar_pessoa_especifica(){
	Pessoa *vet_pep;
	vet_pep=(Pessoa *) calloc(1, sizeof(Pessoa)); //alocação dinâmica
	int pos=-1;
	int cpf;
	printf("Digite o CPF para busca: ");
	scanf("%d",&cpf);
	pos=verificar_CPF(cpf);
	if(pos!=-1)
	{
		FILE *arqPessoa;
		if((arqPessoa=fopen("arq_pessoas.txt", "rb"))==NULL)
		{
			printf("Não foi possível abrir os cadastros de pessoas!");
			exit(1);
		}
		else
		{
			int i=0, verificador=0;
			fread(vet_pep, sizeof(Pessoa), 1, arqPessoa);
			while(!feof(arqPessoa) && verificador==0)
			{
				if(i!=pos)
				{
					i++;
					fread(vet_pep, sizeof(Pessoa), 1, arqPessoa);
				}
				else
				{
					printf("Nome: %s\n", vet_pep->nome);
					printf("Data de nascimento: %s\n", vet_pep->nasc);
					printf("Sexo: %c\n", vet_pep->sexo);
					printf("Escolaridade: %s\n", vet_pep->escolaridade);
		
					//Laço para listar todos os telefones cadastrados
					for(int j = 0; j < vet_pep->numTel; j++){ //percorre os telefones cadastrados
						printf("Telefone %d do cliente: %s\n", j+1, vet_pep->fone);
					}
					printf("\n\n-------------------------------");
					verificador=1;
				}
			}
		}
		free(vet_pep);
		fclose(arqPessoa);
	}
	else
		printf("\nCPF %d NÃO LOCALIZADO!", cpf);
}

//Função para listar uma pessoa específica de acordo com o CPF
void listar_pesquisa_especifica(){
	Pesquisa *vet_pesq;
	vet_pesq=(Pesquisa *) calloc(1, sizeof(Pesquisa)); //alocação dinâmica
	int pos=-1;
	int codigo;
	printf("Digite o código da pesquisa para busca: ");
	scanf("%d",&codigo);
	pos=verificar_codigo_pesquisa(codigo);
	if(pos!=-1)
	{
		FILE *arqPesquisa;
		if((arqPesquisa=fopen("arq_pesquisa.txt", "rb"))==NULL)
		{
			printf("Não foi possível abrir os cadastros de pesqusas!");
			exit(1);
		}
		else
		{
			int i=0, verificador=0;
			fread(vet_pesq, sizeof(Pesquisa), 1, arqPesquisa);
			while(!feof(arqPesquisa) && verificador==0)
			{
				if(i!=pos) //percorro até encontrar a posição desejada
				{
					i++;
					fread(vet_pesq, sizeof(Pesquisa), 1, arqPesquisa);
				}
				else
				{
					printf("Código: %d\n", vet_pesq->codP);
					printf("Descrição: %s\n", vet_pesq->descri);
					printf("-------------------------------");
					verificador=1; //já encerra o laço para deixar mais rápido
				}
			}
		}
		free(vet_pesq);
		fclose(arqPesquisa);
	}
	else
		printf("\nCÓDIGO %d NÃO LOCALIZADO!", codigo);
}


void gerar_relatorio_telefones(){
	Pessoa *vet_pep;
	vet_pep=(Pessoa *) calloc(1, sizeof(Pessoa)); //alocação dinâmica
	int pos=-1;
	int cpf;
	printf("Digite o CPF para impressão do relatório: ");
	scanf("%d",&cpf);
	pos=verificar_CPF(cpf);
	if(pos!=-1)
	{
		FILE *arqPessoa;
		FILE *arqRELfones;
		arqRELfones=fopen("relatorio_telefones.txt", "w");
		if((arqPessoa=fopen("arq_pessoas.txt", "rb"))==NULL)
		{
			printf("Não foi possível abrir os cadastros de pessoas!");
			exit(1);
		}
		else
		{
			int i=0, verificador=0;
			fread(vet_pep, sizeof(Pessoa), 1, arqPessoa);
			while(!feof(arqPessoa) && verificador==0)
			{
				if(i!=pos)
				{
					i++;
					fread(vet_pep, sizeof(Pessoa), 1, arqPessoa);
				}
				else
				{
					fputs("---------------------------------",arqRELfones);
					fputs("\nRELATÓRIO DE TELEFONES POR PESSOA",arqRELfones);
					fputs("\n---------------------------------",arqRELfones);
					fputs("\nNome: ",arqRELfones);
					fputs(vet_pep->nome,arqRELfones);
					fputs("\nTelefones: ",arqRELfones);
					//Laço para listar todos os telefones cadastrados
					for(int j = 0; j < vet_pep->numTel; j++){ //percorre os telefones cadastrados
						fputs(vet_pep->fone[j],arqRELfones);
						fputs("\n",arqRELfones);
					}
					fputs("\n---------------------------------",arqRELfones);
					printf("RELATÓRIO GERADO COM SUCESSO!");
					verificador=1;
				}
			}
		}
		free(vet_pep);
		fclose(arqRELfones);
		fclose(arqPessoa);
	}
	else
		printf("\nCPF %d NÃO LOCALIZADO!", cpf);
}


//==========================================================================
//PROGRAMA PRINCIPAL
main (){
	setlocale(LC_ALL,"Portuguese");
//VARIÁVEIS LOCAIS=============================================================================================================
	int i, j, opGeral, opSubmenu, opMenuRel, contador=0, cont_pesquisa=0, cont_resposta=0, resultado=0, codigo, confirma, busca_pesq;
	char data_resp[11], descri[50], data_ini[11], data_fim[11];
	int CPF;

//ESTRUTURAS DE DADOS===========================================================================================================
	Pessoa pep[tam];
	Pesquisa pesq[tam];
	Resposta resp[tam];

	do {
		opGeral = chamar_menu();
		switch(opGeral)
		{
			case 1: //MENU GERAL OPÇÃO 1 - PESSOAS
				system("cls"); 	
				printf("MENU PESSOAS ===>>>\n\n");
				opSubmenu = chamar_submenu();
//SUBMENU PESSOA ========================================================================				
				switch(opSubmenu)
				{
					case 1: //SUBMENU PESSOAS OPÇÃO 1
						printf("Listando pessoas...\n");
						listar_pessoa();
						break;
					case 2: //SUBMENU OPÇÃO 2
						listar_pessoa_especifica();
						break; 
					case 3: if (contador < tam){ //SUBMENU PESSOAS OPÇÃO 3
						printf("Cadastrando pessoa...\n");
						printf("\nDigite o CPF (apenas números):");
						scanf("%d",&CPF);
						resultado = verificar_CPF(CPF);
						if (resultado == -1)
							cadastrar_pessoa(CPF);
						else
							printf("\n\nCPF JÁ CADASTRADO!");
						}
						else {
							printf("\nNÃO FOI POSSÍVEL CADASTRAR A PESSOA!");
						}
						break;
					case 4: //SUBMENU PESSOAS OPÇÃO 4
						printf("ALTERANDO OS DADOS DA PESSOA...\n");
						alterar_pessoa();
						break;	
					case 5: //SUBMENU PESSOAS OPÇÃO 5
						excluir_pessoa();
						break;
					case 6: opGeral = chamar_menu();
				}
			break;
			case 2:  //MENU GERAL OPÇÃO 2 - PESQUISA
				system("cls"); 	
				printf("MENU PESQUISA ===>>>\n\n");
				
					opSubmenu = chamar_submenu();
					switch(opSubmenu)
					{
//SUBMENU PESQUISA ========================================================================
						case 1: //SUBMENU PESQUISA OPÇÃO 1
							printf("Listando pesquisas...\n");
							listar_pesquisa();
							break;
						case 2: //SUBMENU PESQUISA OPÇÃO 2
							listar_pesquisa_especifica();
							break; 
						case 3:  //SUBMENU PESQUISA OPÇÃO 3
							cadastrar_pesquisa();
							break;
						case 4: //SUBMENU PESQUISA OPÇÃO 4
							printf("ALTERANDO OS DADOS DA PESQUISA...\n");
							alterar_pesquisa();
							break;	
						case 5: //SUBMENU PESSOAS OPÇÃO 5
							excluir_pesquisa();
							break;
					}
			break;
//SUBMENU RESPOSTA ========================================================================
			case 3:  //MENU GERAL OPÇÃO 3 - RESPOSTAS
				system("cls"); 	
				printf("MENU RESPOSTAS ===>>>\n\n");
					opSubmenu = chamar_submenu();
					switch(opSubmenu)
					{
						case 1:  //SUBMENU RESPOSTAS OPÇÃO 1
							printf("Listando respostas...\n");
							listar_resposta();
							break;
						case 2: //SUBMENU RESPOSTAS OPÇÃO 2
							listar_resposta_especifica();
							break;
						case 3: if (cont_resposta < tam){  //SUBMENU RESPOSTAS OPÇÃO 3
							printf("Cadastrando resposta...\n");
							printf("\nDigite o CPF (apenas números):");
							scanf("%d",&CPF);
							resultado = verificar_CPF(CPF); //Verifica se há o CPF no BD de pessoas
							if (resultado != -1){
								printf("\nDigite o código da pesquisa (apenas números):");
								scanf("%d",&codigo);
								resultado = verificar_codigo_pesquisa(codigo); //Verifica se há o código no BD de pesquisas
								if (resultado != -1){
									cadastrar_resposta(CPF, codigo);
								}
								else{
									printf("\nCÓDIGO NÃO ENCONTRADO NO BANCO DE DADOS DE PESQUISAS\n");
								}
							}
							else{
								printf("\nCPF NÃO ENCONTRADO NO BANCO DE DADOS DE PESSOAS!\n");
							}
						}
						else {
							printf("\nNÃO FOI POSSÍVEL CADASTRAR A RESPOSTA!\n");
						}
						break;
						case 4: //SUBMENU RESPOSTAS OPÇÃO 4
							printf("ALTERANDO OS DADOS DA RESPOSTA...\n");
							printf("\nDigite o CPF desejado:");
							scanf("%d",&CPF);
							printf("\nDigite o código da pesquisa desejado:");
							scanf("%d",&codigo);
							fflush(stdin);
							printf("\nDigite a data desejada:");
							gets(data_resp);
							resultado = validar_resposta(CPF, codigo, data_resp);
							if (resultado != -1){
								alterar_resposta(resultado, CPF, codigo, data_resp);
								printf("\nALTERAÇÃO REALIZADA COM SUCESSO!\n");}
							else
								printf("\nDADOS INFORMADOS NÃO ENCONTRADOS!\n");
							break;	
						case 5: //SUBMENU RESPOSTAS OPÇÃO 5
							printf("\nDigite o CPF que deseja excluir:");
							scanf("%d",&CPF);
							printf("\nDigite o código da pesquisa que deseja excluir:");
							scanf("%d",&codigo);
							fflush(stdin);
							printf("\nDigite a data que deseja excluir:");
							gets(data_resp);
							resultado = validar_resposta(CPF, codigo, data_resp);
							if (resultado != -1){
								printf("\nREGISTRO LOCALIZADO!");
								printf("\nCONFIRMA A EXCLUSÃO? (1-SIM/2-NÃO)");
								scanf("%d",&confirma);
								if (confirma == 1)
									excluir_resposta(resultado);
							}
							else{
								printf("DADOS NÃO ENCONTRADOS!");
							}
						break;
					}
			break;
//SUBMENU RELATÓRIOS ========================================================================
			case 4:  //MENU GERAL OPÇÃO 4 - RELATÓRIOS
				system("cls"); 	
				printf("MENU RELATÓRIOS ===>>>\n\n");
					opMenuRel = chamar_menu_relatorios();
					switch(opMenuRel)
					{
						case 1:
							gerar_relatorio_telefones();
							break; 
						case 2:
							printf("\nDigite o código da pesquisa para impressão do relatório:");
							scanf("%d",&codigo);
							fflush(stdin);
							printf("\nDigite a data da pesquisa para impressão do relatório:");
							gets(data_resp);
							resultado = validar_resposta(CPF, codigo, data_resp);
							busca_pesq = verificar_codigo_pesquisa(codigo); //procuro a descrição da pesquisa associada ao código
							if (resultado != -1){
								printf("\n***********************************************************");
								printf("\nRELATÓRIO DE RESPOSTAS POR DATA");
								printf("\n===========================================================");
								printf("\nCÓDIGO: %d",codigo);
								printf("\nDESCRIÇÃO: %s",pesq[busca_pesq].descri);
								printf("\n===========================================================");
								printf("\nR E S P O S T A S");
								printf("\n===========================================================");
								gerar_relatorio_resposta_por_codigo(resp, codigo, data_resp, &cont_resposta);
							}
							else{
								printf("NÃO FORAM ENCONTRADOS DADOS COM AS INFORMAÇÕES PASSADAS!");
							}
								
						break;
						case 3: //NÃO CONSEGUI REALIZAR A MANIPULAÇÃO DE DATAS EM C PARA EFETUAR ESSE SUBMENU
							fflush(stdin);
							printf("Digite a data inicial para gerar o relatório:");
							gets(data_ini);
							fflush(stdin);
							printf("Digite a data final para gerar o relatório:");
							gets(data_fim);
							if (strcmp(data_ini,data_fim)>0 || strcmp(data_fim,data_ini)<0)
								printf("INTERVALO DE DATAS INVÁLIDO!");
							else{
								gerar_relatorio_pesquisa_por_data(resp, pesq, data_ini, data_fim, &cont_resposta, &cont_pesquisa);
							}
						break;
				}
				break;
		}		
	}while(opGeral != 5);
}
