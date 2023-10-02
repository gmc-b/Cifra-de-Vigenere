/* **** Arquivo: 	header.h
  ***** Autor:     	Guilherme Mattos Camargo
  ***** Matrícula: 	170104508 
  ***** Disciplina:	Segurança computacional
*/

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <string.h>


typedef struct stc_link_list{
	void* first;
	int size;
}link_list;


typedef struct stc_combination{
	int freq;
	char* comb_string;
	int comb_last_position;
	struct stc_combination* next;
}comb_item;


typedef struct stc_spacing{
	struct stc_spacing* next;
	int spacing;
}spacing_item;

typedef struct func_cba_return{
	link_list* comb_list;
	link_list* spacing_list;
}cba_return;

typedef struct func_psg_return{
	int   guess_size[2] ;
	float mean_x2[2];
	char*  pass[2];
}psg_return;

int memory_check(void* ptr);    

void delay(int number_of_seconds);

comb_item* create_comb_item(char*string, int last_pos);

void insert_spacing( link_list* spacing_list_ptr, int spacing);

link_list* create_list();

void insert_spacing(link_list* spacing_list_ptr, int spacing);

void insert_comb(link_list* list,char* string, int pos, link_list* spacing_list_ptr);

int freq_counter(comb_item** comb,char* string, int pos);

void show_comb_list(link_list* list);

void show_spacing_list(link_list* list);

void clear_comb_list(link_list* list);

void clear_spacing_list(link_list* list);


#endif
