
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
#include "datbase.h"
#include "processargs.h"



int main()
{  	
	const int HMILLION=100000000;                                 // Number of elements of the database
  int flag=0;                                                   // When flag equals 1, the program ends
	int nargs=0;                                                  // Number of arguments of a command
	char command[20];                                             // Command itself
	char **arguments;                                             // Arguments of the command
	double londob; double latdob;  int age;                       // Auxiliar variables for quering. Note that... 
	                                                                  
	Database base1(HMILLION,3,0);                                 //Construction of the database
	base1.populate();                                             //Population of the database
	Procargs extrac1;                                             //Extractor of commands
        base1.instructions();
        cout<<"Type 'exit' to close the program\n";
	
        while(flag==0){
		
		cout<<"Type your query\n";
		gets(command);
		
		arguments=extrac1.getcom(command);                                                                                                                    
		nargs=extrac1.count(arguments);
	
			if(strcmp(arguments[0],"exit")==0){
			flag=1;
			}
			else if(strcmp(arguments[0],"query")==0 && nargs==3){
				latdob=atof(arguments[1]); londob=atof(arguments[2]); age=atoi(arguments[3]);
				if(londob!=NULL && latdob!=NULL && age!=NULL && base1.checkval(londob,latdob)) {
					 base1.query(latdob,londob,age);					

				}
			
			}

		}
  
	return(1);   
}



