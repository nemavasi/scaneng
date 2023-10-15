#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "redblacktree.h"
#include "redblacktree2.h"

static void printHelp();
static void exitProgram();
static int validateChar(char c);

int main (int argc, char **argv) {
	
	int const MAX_WORD_LENGTH = 100;
	
	if (argc == 1) {		
		printHelp();
		exitProgram();		
	}

    FILE *textFile = fopen(argv[1], "rt");
    if (textFile == 0) {
		perror("Can't open file");
		exit(1);
	}        
	
	
	char ch;
	char oneWord[MAX_WORD_LENGTH];
	int currentPositionInWord = 0;
    while((ch=fgetc(textFile)) !=EOF) {
		if (validateChar(ch)) {
			oneWord[currentPositionInWord] = ch;
			currentPositionInWord++;
			if (currentPositionInWord == (MAX_WORD_LENGTH - 1)) {
				oneWord[currentPositionInWord] = 0;
				printf("Wrong word: %s...\n", oneWord);
			
	            exit(1); 
			}
		}  else {                
			oneWord[currentPositionInWord] = 0;
			if (currentPositionInWord > 1) {
				char * clonedWord = (char *) malloc(sizeof(char)*strlen(oneWord) + 1);
				strcpy(clonedWord, oneWord);
				put(clonedWord, 1);
			} 			
			currentPositionInWord = 0;
		} 
    }
    
    printf("unique words count = %d\n", size());
    //printSorted();
    transfer(&putCountForString);
    printAllOrderedByCountDesc();
    
    //    printAllOrderedByCountDesc();
    
    int fileClosingResult = fclose(textFile);
    if (fileClosingResult != 0) {
		perror("Can't close program");
		exit(1);
	}
	
	exitProgram();	
}

static int validateChar(char c) {
	if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ) {
		return 1;		
	} else {
		return 0;
	}
}

static void printHelp() {
	printf("Example: scaneng book.txt\n");
}

static void exitProgram(){
//	printf("Good bye!\n");
	exit(0); 
}
