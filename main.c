/* **** Arquivo:    main.c
  ***** Autor:      Guilherme Mattos Camargo
  ***** Matrícula:  170104508 
  ***** Disciplina: Segurança Computacional
*/

#include "header.h"

#define ALPHABET_SIZE 26

#define PASS_SIZE_LIMIT 25



void mensagem_inst(){
    printf("\n");
    printf(" Erro na utilização dos argumentos\n\n");
    printf(" 1º Modo de funcionamento:\n");
    printf("   - \"c\": Criptografa um arquivo de texto\n");
    printf("   - \"d\": Descriptografa um arquivo de texto\n");
    printf("   - \"q\": Quebra a criptografia de um arquivo de texto em um determinado idioma\n");
    printf(" 2º Nome do arquivo de entrada\n");
    printf(" 3º Nome do arquivo de saída\n");
    printf(" 4º Chave utilizada para criptografia (modos \"c\" e \"d\") || Idioma ( \"en\" ou \"pt\"modo \"q\")  \n\n");
    
}

void lower_string(char* str){
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
}

}

int is_letter(char letter){             
    if ((letter>='a')&&(letter<='z')){
        return 1;
    }
    return 0;
}

void factors(int num, int* factor_frequency_array){
    int i;
    int stop = sqrt(num);

    if (stop>PASS_SIZE_LIMIT){
        stop = PASS_SIZE_LIMIT;
    }

    for(i = 2; i<=stop;i++){
        if (num%i == 0){
            factor_frequency_array[i]++;
        }

    } 

}

void vigenere_cypher(char* plain_text, char* pass){
    char new_char;
    int str_pos = 0;
    int pass_pos = 0;
    int loop_pass = strlen(pass);
    int offset = 'a'; 
    int value_text;
    int value_pass;

    do{

        if (is_letter(plain_text[str_pos])){
            value_text = plain_text[str_pos]    - offset;
            value_pass = pass[pass_pos%loop_pass]- offset;

            new_char = (value_text + value_pass)% ALPHABET_SIZE;

            plain_text[str_pos] = new_char+offset;         
            pass_pos++;                                    
        }
        str_pos++;
    }while(plain_text[str_pos] != '\0');

    return ;
}


void vigenere_decypher(char* cypher_text, char* pass){ 
    int i = 0;
    char new_char;
    int offset = 'a'; 

    do{
        pass[i] = ALPHABET_SIZE - (pass[i]-offset) + offset; // gera uma senha "negativa". range em minúsculas [100,123]
        i++;
    }while(pass[i] != '\0');

    vigenere_cypher(cypher_text,pass);
    return ; 
}



int file_size(FILE* file_ptr){
    long int file_size;

    fseek(file_ptr, 0L, SEEK_END);  // Percorre todo o arquivo com ponteiro
    file_size = ftell(file_ptr);    // Retorna em qual byte do arquivo está o pnteiro (no último)
    rewind(file_ptr);               // Retorna o ponteiro ao começo do arquivo
    return file_size;
}


char* file_to_string(char* input_file_name){
	FILE* file_ptr  = fopen(input_file_name, "r");
    long int string_size;
    char* string;

	if(file_ptr== NULL){
		printf("O arquivo %s, ou não teve sua leitura permitida\n",input_file_name);
        return NULL;
	}

    string_size = file_size(file_ptr) ;

    string = malloc(string_size+1);     // Aloca memória do tamanho do arquivo para guardar o texto na variável string
    string[string_size] = '\0';

    if (string){
        fread(string,1,string_size,file_ptr);
        lower_string(string);
    }
    else{
        printf("Erro na alocação de memória");
        return NULL;
    }

	fclose(file_ptr);
	return string;
}


int string_to_file(char* output_file_name, char*cypher_text){

    FILE* out_file = fopen(output_file_name, "w");

	if(out_file== NULL){
		printf("Não foi possível salvar no arquivo\n");
        return 0;
	}

    fputs(cypher_text, out_file);

	fclose(out_file);
	return 0;
}


int letter_frequency_analiser(char* text, int* letter_freq_array, int shift){ 
    int pos = 0;
    int valid_size = 0;
    int offset = 'a';
    int index;
    int letter;

    

    do{

        if (is_letter(text[pos])){
            index = (text[pos] - offset + shift)%ALPHABET_SIZE;   // Indice corresponde aos valores das letras na cifra de vigenere 'a'=0, 'b'=1 ....
            letter_freq_array[index]++;                           // O shift é utilizado para análise da frequencia de subsets deslocados 
            valid_size++;
        }
        pos++;
    }while(text[pos] != '\0');

    //for(int i=0;i<ALPHABET_SIZE;i++){
    //    letter = i+offset;
    //    letter_freq_array[i] = (float) letter_freq_array[i]/total;
    //    printf("%c: %.4f%% \n",letter,letter_freq_array[i]*100);
    //}

    return valid_size;

}

cba_return combination_frequency_analiser(char* text, int comb_size){ // uma vez que estamos tratando de char, uma posição de memória de char = 1 byte
    int text_pos       = 0;
    int text_valid_pos = 0;
    int comb_pos       = 0;
    int freq_array_pos = 0;
    int first_pos_comb = 0;
    int offset         ='a';
    
    char* comb_item_string;
    char* comb;

    link_list* comb_freq_array_ptr = create_list();
    link_list* spacing_array_ptr   = create_list();

    cba_return list_group;

    comb = malloc(comb_size+1);

    comb[comb_size] = '\0'; // Último caracter sempre é o finalizador de string

    while(text[text_pos] != '\0'){
        if (is_letter(text[text_pos])){ 
            
            comb[comb_pos] = text[text_pos];
            comb_pos++;

            if (comb_pos>=comb_size){

                first_pos_comb = text_valid_pos - (comb_size-1);
                insert_comb(comb_freq_array_ptr, comb, first_pos_comb, spacing_array_ptr);
                text_pos       = text_pos       - (comb_size-1);
                text_valid_pos = text_valid_pos - (comb_size-1);

                freq_array_pos++;
                comb_pos = 0;
            }
            
            text_valid_pos++;

        }else{
            comb_pos = 0; // Reseta a combinação em caso de espaços virgulas etc
        }
        text_pos++;
    }


   
    //show_comb_list(comb_freq_array_ptr); 
    //show_spacing_list(spacing_array_ptr);  

    
    free(comb);
    
    list_group.comb_list     = comb_freq_array_ptr;
    list_group.spacing_list  = spacing_array_ptr;

    return list_group; 
}



void factor_frequency_counter(int* factor_frequency_array,link_list* spacing_array_ptr){
    spacing_item* spacing_item = spacing_array_ptr->first;
    int num = 0;

    while(spacing_item){
        num = spacing_item->spacing;
        factors(num,factor_frequency_array);
        spacing_item = spacing_item->next;
    }
}

psg_return pass_size_guesser(int* factor_frequency_array, int min_initial_pass_size){
    
    psg_return psg;

    int first  = PASS_SIZE_LIMIT-1;
    int second = PASS_SIZE_LIMIT-1;

    float current_factor;
    float best_factor;
    for (int i = PASS_SIZE_LIMIT -1; i >= min_initial_pass_size; i--){
        
        current_factor = factor_frequency_array[i]*sqrt(i);
        best_factor    = factor_frequency_array[first]*sqrt(first);
        
        if (current_factor>=best_factor){  // Os valores são multiplicados pela raiz quadrada de seu fator para valorizar multiplos maiores
            second = first;
            first = i;
        }
    }
    
    psg.guess_size[0] = first;
    psg.guess_size[1] = second;
    return psg;
}




float chi_squared(int* letter_freq_array, int size, float* std_letter_freq_array){
    float x2             = 0.0;
    float float_freq     = 0.0;
    float float_std_freq = 0.0;

    for (int i=0; i<ALPHABET_SIZE; i++){
        float_freq = (float)letter_freq_array[i]/ (float)size;
        float_std_freq = std_letter_freq_array[i] ;

        x2 += ((( float_freq - float_std_freq )*( float_freq - float_std_freq)) / float_std_freq );
    }

    return x2;
}


void subset_selector(int start,char* text, char* text_subset,int step){

    int pos = 0;
    int subset_pos = 0;
    int step_pos = step - start; 

    do{
        if (is_letter(text[pos])){

            if(step_pos%step == 0){
                text_subset[subset_pos] = text[pos];
                subset_pos++;
            }

            step_pos++;
        }
        pos++;
    }while(text[pos] != '\0');

    text_subset[subset_pos] = '\0'; 

}




void doubled_pass_check(char* pass){ // Corta senhas que estão repetidas. EX: abcabc -> abc
    int size = strlen(pass);
    int mid = size/2;
    
    if (size%2==0){
        for (int i =0; i<mid ; i++){
            if(pass[i] != pass[i+mid]){
                printf("i:%d",i);
                return;
            }
        }
        pass[mid] = '\0';
    }
    return ;
}
















int main(int argc, char *argv[]){
    clock_t start_time = clock();

    char* plain_text;
    char* cypher_text;
    char* pass;
    char* language;
    char* text_subset;
    char* guess_pass;
    char final_pass[25];

    int factor_frequency_array          [PASS_SIZE_LIMIT] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 ,0,0,0,0,0 ,0,0,0,0,0,  };
    int letter_freq_array_text          [ALPHABET_SIZE]   = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0};
    int letter_freq_array_subset        [ALPHABET_SIZE]   = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0};

    
    float letter_freq_array_pt  [ALPHABET_SIZE]   = {0.1463, 0.0104, 0.0388, 0.0499, 0.1257, 0.0102, 0.0130, 0.0128, 0.0618, 0.0040, 0.0002, 0.0278, 0.0474, 0.0505, 0.1073, 0.0252, 0.0120, 0.0653, 0.0781, 0.0434, 0.0463, 0.0167, 0.0001, 0.0021, 0.0001, 0.0047};
    float letter_freq_array_eng [ALPHABET_SIZE]   = {0.0815, 0.0144, 0.0276, 0.0379, 0.1311, 0.0292, 0.0199, 0.0526, 0.0635, 0.0013, 0.0042, 0.0339, 0.0254, 0.0710, 0.0800, 0.0198, 0.0012, 0.0683, 0.0610, 0.1047, 0.0246, 0.0092, 0.0154	,0.0017, 0.0198, 0.0008};
    float chosen_letter_freq_array[ALPHABET_SIZE];
    //float eng_ic = 0.068601;
    //float pt_ic  = 0.078138;

    link_list* comb_freq_array_ptr;
    link_list* spacing_array_ptr;

    cba_return list_group;
    psg_return psg_pass;

    int pass_guess_size;
    int text_valid_size;
    int subset_valid_size;
    int text_subset_size;
    int offset = 'a';
    int min_initial_pass_size = 4;

    int current_pass_pos;
    float x2;
    float best_x2;
    float mean_x2 = 0;

    if ( argc<4){    
        mensagem_inst();
        return 0;
    }

    int   mode             = argv[1][0]; 
    char* input_file_name  = argv[2]; 
    char* output_file_name = argv[3];

    switch (mode){
        case 'c':
            pass = argv[4];
            lower_string(pass);

            plain_text = file_to_string(input_file_name);
            vigenere_cypher(plain_text, pass);
            cypher_text = plain_text;
            string_to_file(output_file_name,cypher_text);
            free(cypher_text);
            break;

        case 'd':
            pass = argv[4]; 
            lower_string(pass);
            
            cypher_text = file_to_string(input_file_name);
            vigenere_decypher(cypher_text, pass);
            plain_text = cypher_text;
            string_to_file(output_file_name,plain_text);
            free(plain_text);
            break;

        case 'q':
                language = argv[4];

                if (strcmp(language,"en")==0){
                    memcpy(chosen_letter_freq_array,letter_freq_array_eng,sizeof (letter_freq_array_eng) );
                }
                else{
                    memcpy(chosen_letter_freq_array,letter_freq_array_pt,sizeof (letter_freq_array_eng) );
                }

                cypher_text = file_to_string(input_file_name);

                text_valid_size = letter_frequency_analiser(cypher_text, letter_freq_array_text, 0);
                
                ///////////////////////////// Estimativa de tamanho de chave ///////////////////////////// 
                list_group = combination_frequency_analiser(cypher_text,3);
                comb_freq_array_ptr = list_group.comb_list;
                spacing_array_ptr   = list_group.spacing_list;


                factor_frequency_counter(factor_frequency_array, spacing_array_ptr); 
                //for(int i = 2;i<PASS_SIZE_LIMIT;i++){
                //    printf("fator:%d    frequência:%d\n",i,factor_frequency_array[i]); 
                //}


                // Selecionar maior freq maior que 3
                psg_pass = pass_size_guesser(factor_frequency_array, min_initial_pass_size);





                ///////////////////////////// Estimativa de chave ///////////////////////////// 

                for(int a = 0; a<2; a++){
                    
                    pass_guess_size = psg_pass.guess_size[a];
                    guess_pass = malloc(pass_guess_size*sizeof(char)+1);
                    guess_pass[pass_guess_size] = '\0';
                    
                    text_subset_size = (text_valid_size/pass_guess_size) + 1; // Trunca no menor inteiro e adciona 1 para garantir o possível espaço
                    text_subset = malloc(  text_subset_size*sizeof(char)+1);  // +1 posição para o /0


                    best_x2 = 1000; // Valor maior do que qualquer erro possível

                    for(int i = 0; i<pass_guess_size; i++){
                        subset_selector(i, cypher_text, text_subset, pass_guess_size);
                        
                        for(int j = 0; j<ALPHABET_SIZE; j++){
                            memset(letter_freq_array_subset, 0, sizeof(letter_freq_array_subset)); // "Reseta" o array para 0
                            subset_valid_size = letter_frequency_analiser(text_subset, letter_freq_array_subset, j);


                            x2 = chi_squared(letter_freq_array_subset, subset_valid_size, chosen_letter_freq_array);


                            if(best_x2 > x2){
                                best_x2 = x2;
                                current_pass_pos = j;
                            }
                        }
                        mean_x2 += best_x2;
                        best_x2 = 1000;
                        guess_pass[i] =  offset + (ALPHABET_SIZE - current_pass_pos)%ALPHABET_SIZE;
                    }


                    psg_pass.mean_x2[a] = mean_x2/pass_guess_size;
                    psg_pass.pass[a]    = guess_pass;
                    mean_x2 =0;
                    free(text_subset);
                }
                ///////////////////////////////////////////////////////////////////

                if(psg_pass.mean_x2[0]<=psg_pass.mean_x2[1]){

                    doubled_pass_check(psg_pass.pass[0]);
                    strcpy(final_pass,psg_pass.pass[0]);
                }
                else{
                    doubled_pass_check(psg_pass.pass[1]);
                    strcpy(final_pass, psg_pass.pass[0]);
                }

                printf("Key: %s\n", final_pass);

                vigenere_decypher(cypher_text, final_pass);
                plain_text = cypher_text;
                string_to_file(output_file_name,plain_text);

                clear_comb_list(comb_freq_array_ptr);
                clear_spacing_list(spacing_array_ptr);

                
                free(cypher_text); 
                
                free(psg_pass.pass[0]);
                free(psg_pass.pass[1]);
                break;
            }

   
    
    clock_t stop_time = clock();
    double time_spent = (double)(stop_time - start_time) / CLOCKS_PER_SEC;
    printf("Execução: %f ms\n", time_spent*1000);
	return 0;
}
