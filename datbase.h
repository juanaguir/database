class Database
{
public:
	
	Database();                                                        //Constructs a data base with no slots that can be built dynamically.                         
	Database(int columns,int intvals, int dobvals);                    //Constructs and empty data base with reserved memory for "number of subject"=columns and "number of integer properties"=nint (i.e age) and "number of double properties"=ndobs (i.e heigh)                                              
    void put(int i, int j, int val);                                   //Inserts an int value in the database
	void put(int i, int j, double val);                                //Inserts a double value in the database
    int get(int i, int j);                                             //Sorry but it works only in "integer" sites of the data base. Ongoing work  
	
	// Here beging the "Ad hoc methods" i.e they can be clearly improved by generalization, leading to better integration with the class structure
    // they are more friend functions than actual methods
	void query(double querylat, double querylon,int querage);          //Ad hoc version of ther searching algorithm for the purpose of the exam. Further work must generalize the definition linked with the structure of the database
	void populate(void);                                               //An ad-hoc method to populate the data base with the requests of the exercise
	void instructions(void);                                           //Instructions to query the database
	bool checkval(double querlon, double querlat);                     //Checks that the queried values have sense
   
private:                                                              
            
	 int **ielements; double **delements;                     //dynamic arrays, for the sake of speed in the searching algorithm                               
     int *key;                                                //Array used to take care of the size of the datbase
	 int Basedouble(double val);                              //Multiplies a double by 100, rounds it and cast it int. This format is the way that the database stores longitud and latitud. It is like a double, with two decimals digits precision, occupy the memory size of an int. 
     double Bdouble2double(int val);                          //Changes from "base double" to actual double
   
};
//The implementation of the class usually goes in another archive, but since the code is short I left them here
Database::Database(){}
Database::Database(int columns, int nints, int ndobs){
    
	const int KEY_SIZE=3;  //
	//const int ncolumns=nints+ndobs;
	key = (int *)malloc(KEY_SIZE*sizeof(int));
	key[0]=nints; key[1]=ndobs; key[2]=columns;
  
	if(key==NULL) cout<<"Error: Out of memory;\n";
	
                        
	if(nints>0)
	{                                   
	    ielements = (int **)malloc(key[0]*sizeof(int *));
		if(ielements == NULL) cout<<"Error:Out of memory\n";
		for(int i = 0; i < key[0]; i++)
		{
		ielements[i] =(int *)malloc(key[2]*sizeof(int));
		if(ielements[i] == NULL){
			cout<<"Error:Out of memory\n";
		}
	    }
	}
	if(ndobs>0)
	{                                   
	    delements = (double **)malloc(key[0] * sizeof(double *));
		if(delements == NULL) cout<<"Error:Out of memory";
		for(int i = 0; i < key[0]; i++)
		{
		delements[i] =(double *)malloc(key[2] * sizeof(double));
		if(delements[i] == NULL)cout<<"Error:Out of memory";
	    }
	}
	



}
int Database::get(int i, int j){
     if(j<key[2]&& i<key[0]) return ielements[i][j];
	 
	 else if(j<key[2]&& i>=key[0]&& i<key[0]+key[1])cout<<delements[i-key[0]][j]<<"it is a double element, can be printed but not returned\n";
	 else cout<<"Incorrect selection\n";
	 
	 return 0;
	 
}

void Database::put(int i, int j, int val){
    if(j<key[2] &&  i<key[0]){
		ielements[i][j]=val;
	}
	else{
	cout<<"incorrect selection\n";
	}
	

}
void Database::put(int i, int j, double val){  
	
	if(j<key[2] && i>=key[0] && i<(key[0]+key[1])){
		delements[i-key[0]][j]=val;
	}
	else{
	cout<<"incorrect selection\n";
	}
	


}

                                                                   
                                                           //Ad hoc methods
void Database::populate(void){

int nsubjects=key[2];
const int nsubjectsmin=100000000;
const int nsubjectsmax=10000000;

int rowage=0;
int rowlat=1;
int rowlon=2;

if(nsubjects>nsubjectsmin || nsubjectsmax<100000000) nsubjects=nsubjectsmax;
int lonmin=4800;  //Minimum longitud value in germany. The units are 100*DD (decimal degrees). 0.01 DD is the maximum resolution of the queries
int lonmax=5300;  //Maximum longitud value in germany. The units are 100*DD
int latmin=700;   //Minimum latitud value in germany. The units are 100*DD
int latmax=1300;  //Maximum latitud value in germany. The units are 100*DD
int agemin=18;    //Minimal legal age in germany to participate in the database
int agemax=80;    //Maximum age of the participant
int nname=10;

srand (time(NULL)); 
 cout<<"Populating database\n";
	for(int i=0;  i<nsubjects; i++){
		put(rowage, i, agemin+(rand() % (agemax-agemin)));
		put(rowlat, i, latmin+(rand() % (latmax-latmin)));
		put(rowlon, i, lonmin+(rand() % (lonmax-lonmin)));
		}	
	cout<<"Data base built\n\n\n";
}


void Database::query(double querylat, double querylon,int querage){
 //The data base is populated assuming that citizens are distributed randomly in the whole germany. The results of the query 
//should be evaluated accordingly
 
 const int n=10000000;                                  //Number of random access to the data base
 const int tolage=4;                                    //Tolerance i.e resolution of the query
 const int tolpos=20;                                   //Tolerance i.e resolution of the query
 int rowage=0;
 int rowlat=1;
 int rowlon=2;
 
 int m;                                                 //Helper variable for the loop of the search algorithm
 int mm;                                                //Helper variable for the loop of the search algorithm
 int i=0;                                               //Helper variable for the loop of the search algorithm
 int counter=0;                                         //Counts how many targeted subjects have been found
 int ranpoint;                                          //Random column of the database
 
 std::vector<int> selection;                            //Vector used to get the positive results after each random query. I used to this format since it simplifies the syntax for dynamic memory allocation
 int querlon=Basedouble(querylon);
 int querlat=Basedouble(querylat);
 
 cout<<"Quering data base \n";
 //clock_t start = clock();
 mm=0;
 srand (time(NULL)); 
//begins the searching algorithm
 while(i<n && counter <10)
	{
	ranpoint =rand() %  n;                             //since the data base is populated randomly, this line could go out of the loop and the do something like
                                                       //for(int i =randpoint; i<ranpoint+n; i++) and make the algorithm faster...
                                                       //however in this way it is already fast and it is valid also for ordered databases...
                                                       //for ordered data bases more deterministran algorithms can be much faster and get finer results.
	
		if(get(rowage,ranpoint)>querage-tolage && get(rowage,ranpoint)<querage+tolage && get(rowlat,ranpoint)<querlat+tolpos && get(rowlat,ranpoint)>querlat-tolpos && get(rowlon,ranpoint)<querlon+tolpos && get(rowlon,ranpoint)>querlon-tolpos )
	   {
		m=0;
		selection.push_back(ranpoint);
	   
			while(m<(selection.size()-1) && mm==0)
			{
				if(selection[m]==ranpoint) mm=1;
				m=m+1;
			}
					if(mm==0){ 
						cout<< " Age "<<get(rowage,ranpoint)<<"  Longitud "<<Bdouble2double(get(rowlon,ranpoint))<<"  Latitud "<<Bdouble2double(get(rowlat,ranpoint))<<"\n";
						counter++;
						}
		mm=0;

		
		}
	 i++;
	}
 //end of the searching algorithm
 //clock_t end = clock();
 //float seconds = (float)(end - start) / CLOCKS_PER_SEC;
 cout<<"Finished quering data base\n";
};
int Database::Basedouble(double val){
    double dobval;
	int intval;
    dobval=val*100;
	dobval=floor(dobval);
	intval=int(dobval);
	return intval;
} 
double Database::Bdouble2double(int val){
double doblval;
doblval=double(val);
doblval=doblval/100;
return doblval;


} 

void Database::instructions(void){

	int lonmin=4800;  //Minimum longitud value in germany. The units are 100*DD (decimal degrees). 0.01 DD is the maximum resolution of the queries
int lonmax=5300;  //Maximum longitud value in germany. The units are 100*DD
int latmin=700;   //Minimum latitud value in germany. The units are 100*DD
int latmax=1300;  //Maximum latitud value in germany. The units are 100*DD
int agemin=18;    //Minimal legal age in germany to participate in the database
int agemax=80;    //Maximum age of the participant
    cout<<"Instructions\n\n";
	cout<<"Type: 'query latitud longitud age'\n";
	cout<<"Example: query 20.39 10.15 40\n";
	cout<<"It is a german national database \n";
	cout<<"therefore 7.00<latitud<13.00 and  48.00<longitud< 53.00 \n";
    cout<<"The members of the database have ages between 18 and 80 \n";

}

bool Database::checkval(double querlon, double querlat){
	
	if(querlon>48.00 && querlon<53.00 && querlat>7.00 && querlat<13.00)
	{
	    return true;
	}
	else
	{
		return false;
	}}
