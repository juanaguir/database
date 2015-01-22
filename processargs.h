class Procargs                       //This class contains methods to process the commands of the command line and their arguments
{
public:
    
	Procargs();                      //Empty constructor
	char ** getcom(char *command);   //Get the arguments of the command
    int count(char **arguments);     //Count the number of arguments

};
Procargs::Procargs(){};
char ** Procargs::getcom(char *command){
	char **arguments; 
	int nargs=0;
	arguments=(char**)malloc(sizeof(char*));
    arguments[nargs] = strtok(command," ");
	if(arguments[0]==NULL){
	arguments[0]="a";                       //Could be whatever 
	}
	else{
	while (arguments[nargs] != NULL){ 
           arguments=(char **) realloc((void*)arguments,sizeof(char*)*((++nargs)+1));
           arguments[nargs]=strtok(NULL," ");
        }
	}
	
return arguments;
}
int Procargs::count(char **arguments){
	int nargs=0;
	while(arguments[nargs]!=NULL){
    nargs++;
	}
    nargs=nargs-1;
  return nargs;
}
