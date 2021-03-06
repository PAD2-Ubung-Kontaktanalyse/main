//
//  generator.c
//  PAD2-Kontaktanalyse
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generator.h"

#define NAME_LEN 61

int generate_persons(char * input_path, char * output_path, int n, float infection_rate){
    int name_count = 0;
    
    //open input file
    FILE *input_file = fopen(input_path, "r");
    if(input_file == NULL) {
        return -1;
    }
    
    //open output file
    FILE *output_file = fopen(output_path, "w");
    if(output_file == NULL) {
        return -2;
    }
    
    //count names
    name_count = line_count(input_file);
    
    //handle file read errors
    if (ferror(input_file)) {
        return -1;
    }
    
    //write random names to output file
    for(int i = 0; i < n; i++){
        char name[NAME_LEN] = "";
        int status = 0;
        
        //pick random line from input file
        int line = rand() % name_count; //random number within [0; name_count)
        
        //begin from the top of the input file
        rewind(input_file);
        
        //jump to line
        for(int j = 0; j < line; j++){
            char c;
            while((c = fgetc(input_file)) != '\n');
        }
        
        //read name
        fscanf(input_file, " %s", name);
        
        //generate infection status
        int seed = rand() % 10001;
        if(seed > infection_rate * 10000){
            status = 0;
        }else{
            status = 1;
        }
        
        //write line to output file
        fprintf(output_file, "%d; %s; %d\n", i, name, status); //Format: id, name, infection-status (1=infected, 0=healthy)
    }
    
    //release files
    fclose(input_file);
    fclose(output_file);
    
    //returns 0 for successful execution
    return 0;
}

int generate_interactions(char * input_path, char * output_path, int n, int start_time, int end_time, int min_time, int max_time){
    
    int person_count = 0;
    
    //open input file
    FILE *input_file = fopen(input_path, "r");
    if(input_file == NULL) {
        return -1;
    }
    
    //open output file
    FILE *output_file = fopen(output_path, "w");
    if(output_file == NULL) {
        return -2;
    }
    
    //count persons
    person_count = line_count(input_file);
    
    //generate n interactions
    for(int i = 0; i < n; i++){
        int person_id[2] = {0};
        int time[2] = {0};
        
        //pick 2 random persons
        for(int j = 0; j <= 1; j++){
            //begin from the top of the input file
            rewind(input_file);
            
            //pick random id
            person_id[j] = rand() % person_count;
        }
        
        //generate start time
        time[0] = start_time + (rand() % (end_time - start_time + 1));
        
        //generate end time
        time[1] = time[0] + min_time + (rand() % (max_time - min_time + 1));
        
        //write line to output file
        fprintf(output_file, "%d; %d; %d; %d; %d\n", i, person_id[0], person_id[1], time[0], time[1]); //Format: interaction-id, person-1-id, person-2-id, start-time, end-time
    }
    
    //release files
    fclose(input_file);
    fclose(output_file);
    
    //returns 0 for successful execution
    return 0;
}

int line_count(FILE *input_file){
    int result = 0;
    char c = getc(input_file);
    
    //iterate result for every new line character
    while(c != EOF){
        if (c == '\n') {
            result++;
        }
        c = getc(input_file);
    }
    return result;
}
