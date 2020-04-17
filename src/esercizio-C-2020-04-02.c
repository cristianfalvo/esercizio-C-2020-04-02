#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_CHARS 80

char char_array[NUM_CHARS];

void forkthis(); //int per ritornare l'output di fork?
void analyze_string();

int main(int argc, char ** argv){
	int child_counter = 0;

	//gestione dell'input
	int ch;
	char * current = char_array;
	char * end = &char_array[NUM_CHARS - 1];
	while ((ch = getchar()) != EOF) {

		*current = ch; //casting implicito, *current è char, ch è int

		if (current == end){

			forkthis(); // ritorno l'output di fork?

			//qui processo padre
			child_counter++; //aggiungo 1 al counter di child process
			current = char_array; //torno all'inizio di char_array
			memset(char_array, 0, NUM_CHARS * sizeof(char)); //svuoto char_array (necessario?)
		}
		else{
			current++;
		}
	}
	printf("Ho eseguito %d processi figlio.\n", child_counter);
	return (0);

}

void forkthis(){
	int a = fork();
	switch(a){
		case 0:
			//child
			analyze_string();
			exit(EXIT_SUCCESS);
			break;
		case -1:
			//errore
			perror("Fork error");
			exit(EXIT_FAILURE);
			break;
		default:
			//parent
			break;
	}
	//return a;
}

//# define DEBUG
void analyze_string(){
	int min_char = 256; //qualunque char sarà minore all'inizio
	int max_char = -1; //qualunque char sarà maggiore all'inizio
	int ch;

	char most_frequent_char, least_frequent_char;
	int char_freqs[256] = {0}; //tengo conto di ogni comparsa di ogni char
	int most_frequent_char_freq = -1; //qualunque char avrà frequenza maggiore
	int least_frequent_char_freq = 81; //qualunque char avrà frequenza minore (array è lungo 80)

#ifdef DEBUG
	for (int i =0; i < NUM_CHARS; i++){
		printf("%c", char_array[i]);
	}
	printf("\n");
	for (int i =0; i < NUM_CHARS; i++){
			printf("%d ", (int)char_array[i]);
		}
#endif

	for (int i = 0; i < NUM_CHARS; i++){
		ch = (int)char_array[i];
		char_freqs[ch]++;

		if (ch < min_char) min_char = ch;
		if (ch > max_char) max_char = ch;
	}

	for (int i = 0; i < NUM_CHARS; i++){
		if (char_freqs[i] > most_frequent_char_freq){
			most_frequent_char_freq = char_freqs[i];
			most_frequent_char = i;

		}
		if (char_freqs[i] < least_frequent_char_freq){
			least_frequent_char_freq = char_freqs[i];
			least_frequent_char = i;
		}
	}

	printf("carattere minimo: %u \n",min_char);
	printf("carattere massimo: %u \n",max_char);
	printf("carattere con più occorrenze: %u freq=%d\n",
			most_frequent_char,
			most_frequent_char_freq);
	printf("carattere con meno occorrenze: %u freq=%d\n\n",
			least_frequent_char,
			least_frequent_char_freq);
}
