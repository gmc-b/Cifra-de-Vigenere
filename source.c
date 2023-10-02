/* **** Arquivo:   	source.c
  ***** Autor:     	Guilherme Mattos Camargo
  ***** Matrícula: 	170104508 
  ***** Disciplina:	Segurança computacional
*/

#include "header.h"


int memory_check(void* ptr){
	if (ptr == NULL)
	{
		printf("Não foi possível alocar a memória\n");
		return 0;
	}
	return 1;
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}


comb_item* create_comb_item(char* string, int last_pos){

	comb_item* comb = malloc(sizeof(comb_item));
	char* comb_string_ptr  = malloc(strlen(string)+1);
	
	strcpy(comb_string_ptr,string);

	if (memory_check(comb)){

		comb->comb_string 	     = comb_string_ptr;
		comb->comb_last_position = last_pos;
		comb->next 		  		 = NULL;
		comb->freq 		  		 = 1;

		return comb;
	}

	return NULL;
}

spacing_item* create_spacing_item(int new_spacing,spacing_item* next_spacing_item){

	spacing_item* spacing_ptr = malloc(sizeof(spacing_item));
	
	if (memory_check(spacing_ptr)){

		spacing_ptr->next 		  		 = next_spacing_item;
		spacing_ptr->spacing 		   	 = new_spacing;

		return spacing_ptr;
	}

	return NULL;
}

link_list* create_list(){
	link_list* list = malloc(sizeof(link_list));
	if (memory_check(list)){
		list->first = NULL;
        list->size  = 0;
		return list;
	}

	return NULL;


}


void insert_spacing( link_list* spacing_list_ptr, int spacing){ //insere em ordem diferente da insert comb
	spacing_item* aux = spacing_list_ptr->first;

	spacing_list_ptr->first = create_spacing_item(spacing,aux);

}



								// Versão recursiva //
//void insert_comb(link_list* comb_list_ptr,char* string,int pos, link_list* spacing_list_ptr){
//	int spacing = 0;
//    spacing = freq_counter((comb_item**) &comb_list_ptr->first, string, pos); // Se houver inserção retorna 0, se uma string se repetir, retorna a distância da entre a duas ultimas repetções
//
//	if (spacing){
//		insert_spacing(spacing_list_ptr,spacing);
//		spacing_list_ptr->size++; 
//	}
//	else{
//		comb_list_ptr->size++; 
//	}
//}
//
//
//int freq_counter(comb_item** comb,char* string,int pos){ // Recursivo
//	int spacing = 0;
//
//	if((*comb) == NULL){                                       // Primeiro item da lista
//		comb_item* new_comb = create_comb_item(string,pos); 
//		*comb = new_comb;
//
//		return 0;
//	}
//
//	if(strcmp((*comb)->comb_string,string) == 0){				// Item repetido
//		(*comb)->freq++;
//		spacing = pos- (*comb)->comb_last_position; 
//		
//		(*comb)->comb_last_position = pos;
//		return spacing;
//	}
//	
//	if((*comb)->next==NULL){									// Novo item
//		comb_item* new_comb = create_comb_item(string,pos);
//		(*comb)->next		 	= new_comb;
//		return 0;
//	}
//
//	return freq_counter(&(*comb)->next,string,pos);
//	
//
//}


void insert_comb(link_list* comb_list_ptr,char* string,int pos, link_list* spacing_list_ptr){
	
	comb_item* aux = comb_list_ptr->first;

	int spacing = 0;

	if(aux == NULL){                                       // Primeiro item da lista
		comb_item* new_comb = create_comb_item(string,pos); 
		comb_list_ptr->first = new_comb;
		comb_list_ptr->size++; 

		return ; 

	}

	while(aux){

		if(strcmp(aux->comb_string,string) == 0){				// Item repetido
			spacing = pos - aux->comb_last_position; 
			insert_spacing(spacing_list_ptr,spacing);
			
			aux->comb_last_position = pos;
			aux->freq++;
			spacing_list_ptr->size++; 
			return ;
		}
		
		if(aux->next==NULL){									// Novo item
			comb_item* new_comb = create_comb_item(string,pos);
			aux->next		 	= new_comb;
			comb_list_ptr->size++; 
			return ;
		}
		
		aux = aux->next;
	}
}


void show_comb_list(link_list* list){
	comb_item* aux = list->first;
	int i = 0;
	printf("tamanho lista: %d\n",list->size);
    if (memory_check(list)){
        
		while(aux){
            printf("lista[%4d]: \"%s\" , frequência: %4d última posição válida: %d  \n",i, aux->comb_string, aux->freq,aux->comb_last_position );
            aux = aux->next;
			i++;
        }
    }
}

void show_spacing_list(link_list* list){
	spacing_item* aux = list->first;
	int i = 0;
	printf("tamanho lista: %d\n",list->size);

    if (memory_check(list)){
        
		while(aux){
            printf("spacing[%d]: %d \n",i,aux->spacing );
            aux = aux->next;
			i++;
        }
    }
}	





void clear_comb_list(link_list* list){
	comb_item* aux = list->first;

	while(aux != NULL){
		list->first = aux->next;
		free(aux->comb_string);
		free(aux);
		aux=list->first;
	}
	free(list);
}


void clear_spacing_list(link_list* list){ 
	spacing_item* aux = list->first;

	while(aux != NULL){
		list->first = aux->next;
		free(aux);
		aux=list->first;
	}
	free(list);
}


