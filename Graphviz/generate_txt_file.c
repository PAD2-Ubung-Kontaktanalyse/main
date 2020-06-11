//	Header für PAD2-Kontaktanalyse
//
//	Arbeitsablauf der Funktion 
//	
//	Öffnen der Angegebenen Quellatei
//	Es wird eine Neue Datei "Code_Graphviz.txt" erstellt. 
//	Die Quelldatei wird Zeile für Zeile eingelesen und 
//	Daten entsprechend in die neue .txt Datei geschrieben
//	Das Format der .txt Datei kann in Graphviz online eingegeben werden. 
//
//	http://www.webgraphviz.com/
//
//	Hierzu bitte das vorhande Skript mit dem Inhalt der .txt Datei ersetzen. 
//
///////////////////////////////////////////////////////////////////////
  
#ifndef scriptwriter_h
#define scriptwriter_h 
 
/**
 *  @brief Reads generated List and converts it into Graphviz script 
 *  @details Format of output file: .txt with script
 *  @param input_path Path + file name of the full list of names
 *  @param output_path Path + file name where to output should be saved
 *  @return Returns 0
 */
 
int create_txt(FILE *myfile, FILE *newfile){

   FILE *myfile;
    char Dateiname[81];
   FILE *newfile;
    char Nametxt[81]
	int Interaktion_ID;                                                   // Fortlaufende Nummerrierung des einlesens                 
	int ID_Person_1;                                                      // Identifikationsnummer von Person 1 
	int ID_Person_2;					              // Identifikationsnummer von Person 2
	int Start_Zeit;								
	int End_Zeit;

    printf("Geben Sie die Bezeichnung der Datei ein:\n Achtung! 80 Zeichen Maximum!\n");		      // Dateiname abfragen
    scanf("%s", Dateiname);
    myfile = fopen(Dateiname, "r");                                 	      // Datei zum schreiben öffnen 
    
    printf("Geben Sie die Bezeichnung der Datei ein:\n Achtung! 80 Zeichen Maximum!\n");		      // Dateiname abfragen
    scanf("%s", Nametxt);
    newfile = fopen("Code_Graphviz %d .txt", Nametxt, "w");				      // Datei neu erzeugen bzw. ueberschreiben, wenn es sie schon gibt	
    
        if(myfile == NULL) {                                        	      // Fehlerbehandlung 
            printf("could not oben %s", Dateiname);
            return 0;
        }
	if(newfile == NULL) {                                        	      // Fehlerbehandlung 
            printf("could not oben Code_Graphviz %s", Nametxt);
            return 0;
        }
   	fprintf(newfile,"digraph G { \n\n"); 
	
        while(fscanf(myfile, " %d,%d,%d,%d,%d,%d", 
			&Interaktion_ID, 
			&ID_Person_1, 
			&ID_Person_2,
			&Start_Zeit, 
			&End_Zeit,
			&Infektionsstatus,
		     ) != EOF) {    					      // Einlesen der Zeilen bis End Of File
	 

	 
	 
	 if(Infektionsstatus == 0) {
	 fprintf(newfile,"	%d -> %d;\n", &ID_Person1, &ID_Person2); 
	 fprintf(newfile,"\n}"};
	 }   else {
	 	 fprintf(newfile,"	%d  -> %d\n [color="0.002 0.999 0.999"];\n", &ID_Person1, &ID_Person2); 
		 fprintf(newfile,"	%d [color="0.000 1.000 1.000"];\n", &ID_Person1);
		 fprintf(newfile,"	%d [color="0.000 1.000 1.000"];\n", &ID_Person2);  
	    }
        }
fprintf(newfile,"\n}"};	
fclose(myfile);
fclose(newfile);

}

#endif /* scriptwriter_h */