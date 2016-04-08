#include <iostream>
#include<fstream>
#include<sstream>
#include <vector>
#include<stdlib.h>
#include<iomanip>
#include<string>

using namespace std;
int first=0;
int last=0;
int flag=0;

void print();
void pdb(int first,int last, int fileno );
int helix_New(int minimum, int maximum);
void extractData(string sequence, ofstream & outfile);

void finalize();
void sheet(int difference,string filename);
std::vector<string> fetchAlphaGroup(int start, int end);

struct helixinfo
{
    string helix_1,helix_2,helix_Final;
    int sequenceNumber,terminal;

};

struct sheetinfo
{
    string hltt,re2,sheete;
    int terminal,sequenceNumber;
};


struct atominfo
{
    string atomic;
    int atoms,atoms_1,atoms_2,atoms_3;

};

std::vector<helixinfo> sequence;

std::vector<sheetinfo> sheet;

std::vector<atominfo> atom;







void pdb(int first,int last, int fileno,string filename )
{
     ifstream inFile;
     ofstream oute,outfile,outa;

     string sudo,word_1,word_2,tempfilename,temp,newone;
     int number=0;
outa.open("brandnew.pdb",ios::app);
    


     inFile.open(filename.c_str());
  
    outfile.open("Output.pdb",ios::app);

    while(inFile && flag==0)
    {
        getline(inFile,sudo);
        if(!sudo.empty())
        {
            word_1=sudo.substr(0,4);
            word_2=sudo.substr(0,6);


            


              if(word_1=="ATOM")
             {
                temp=sudo.substr(22,4);
                number=atoi(temp.c_str());
				newone=sudo.substr(13,2);
                   if(number >=first && number <=last)
                       {
                          oute<<sudo<<endl;
                          outfile<<sudo<<endl;
						  if(newone.compare("CA") == 0)
						  outa<<sudo<<endl;
						  

                       }
             }

        }
        else
        {
        outfile<<endl<<sudo;
        }
    }




}


void finalize()
{
    int i=0;
    int new_Record=0;
    int count;
    int difference;
    string filename[5000];
    int file;
    string sheet_New;
    ifstream inFile;
	ofstream outFile;
  
    int size=0;



    cout<<"TASK 2\n";

   cout << "Enter files : ";
    cin >> file;


cout<<endl<<" Enter the number for difference :";
cin>>difference;

     cout<<"processing..........\n";
     while(size<file){

     size++;
    cout<<"Enter the name of the PDB file: ";
	cin>>filename[1];
    inFile.open(filename[1].c_str());


    if (!inFile){
        cout<<"invalid type";
    }

      while(inFile)
    {
        getline(inFile,sheet_New);
        extractData(sheet_New, outFile);

    }


    

    sheet(difference,filename[1]);

    inFile.close();
     }

}



int main()
{
    finalize();
  
    return 0;
}



void sheet(int difference,string filename)
{
    int i=0;
    int new_Record=0;
    int count;
	int array_1[900],array_2[900];
	int temporary=0;
	ofstream opaque;
	
	int setStart[500], setEnd[500];
	int numCalphas = 0;
    while(i<sheet.size())
    {
        i++;
        new_Record=(sheet[i+1].sequenceNumber-sheet[i].terminal-1);

        if(new_Record==difference)
        {
            cout<<endl<<" similarity found :"<<sheet[i].terminal<<"   "<<sheet[i+1].sequenceNumber;
            count=helix_New(sheet[i].terminal,sheet[i+1].sequenceNumber);
			array_1[temporary]=sheet[i].terminal;
			array_2[temporary]=sheet[i+1].sequenceNumber;
			
            if(count==1)
            {
                first=sheet[i].sequenceNumber;
                last=sheet[i+1].terminal;

                pdb(first,last,i,filename);

                cout<<" sheet range : "<< first<<" "<<last;
				setStart[temporary] = first;
				setEnd[temporary] = last;
            }
			temporary++;
			numCalphas++;
        }
    }
	
	int initial=array_1[0];
	int initial_1;
	string xco,yco,zco;
	string xs,ys,zs;
	double axis_1, axis_2, axis_3;
	string se;
	string sequel;
	string fast1,fast2;
	
	std::vector<string> set;
	
	cout<<endl<<"Processing............ "<<endl;
	opaque.open("final.pdb");
	for(int i = 0; i < numCalphas; i++)
	{
		initial_1 = array_1[i];
		
		set = fetchAlphaGroup(setStart[i], setEnd[i]);
		
		int setCnt = set.size();
		for(int j = 0; j < setCnt; j++)
		{
			se = set[j];
			if(!se.empty())
			{
				sequel=se.substr(22,4);
				
			xs = se.substr(30,8); 
			ys = se.substr(38,8);
			zs = se.substr(46,8);
				
				if(i == 0)
				{
					if (atoi(sequel.c_str())== initial )
					{
				xco = xs;
				yco = ys;
			    zco = zs;
						
						break;
					}
				}
				else
				{
					if (atoi(sequel.c_str())== initial_1 )
					{
				axis_1 = atof(xs.c_str()) - atof(xco.c_str());
				axis_2 = atof(ys.c_str()) - atof(yco.c_str());
				axis_3 = atof(zs.c_str()) - atof(zco.c_str());
						
						break;
			}
			}
		}
		}
		cout<<"break"<<endl;
	
		float xsf,ysf,zsf;
		for(int j = 0; j < setCnt; j++)
		{
			se = set[j];
			if(!se.empty())
		{
				sequel=se.substr(22,4);
				
				fast1=se.substr(0,30);
				xsf = atof(se.substr(30,8).c_str()); 
				ysf = atof(se.substr(38,8).c_str());
				zsf = atof(se.substr(46,8).c_str());
				fast2=se.substr(54,25);
				
				if(i > 0)
				{
					
					
					xsf = xsf - axis_1;
					ysf = ysf - axis_2;
					zsf = zsf - axis_3;
				}				
				
				opaque<<fixed<<setprecision(3)<<fast1<<setw(8)<<xsf<<setw(8)<<ysf<<setw(8)<<zsf<<fast2<<endl;
		}
		}
	}
	opaque.close();
}


vector<string> fetchAlphaGroup(int start, int end)
{
	ifstream input;
	input.open("brandnew.pdb");
	int intSequel;
	string sequel;
	string set[500]; 
	string se;
	int i = 0;
	while(!input.eof())
	{
	   getline(input,se);
	   	   
	   if(!se.empty())
	   {
		   sequel = se.substr(22,4);
		   intSequel = atoi(sequel.c_str());
		   if (intSequel >= start && intSequel <= end){
				
				set[i++] = se;			
				cout<<endl<<se<<endl;
		   }
		}
	}	
	input.close();
	
	std::vector<string> vectorSet (set, set + sizeof(set) / sizeof(*set) );
	
	return vectorSet;
}





int helix_New(int minimum, int maximum)
{
    int i=0;
    while(i<sequence.size())
{
        i++;
        if(sequence[i].sequenceNumber>=minimum&&sequence[i].terminal<=maximum)
        print();

}

    return 1;

}
void print()
{


cout<<endl<<" Conflict with helix ";
             flag=1;


}


///sorting helix data


void Helixcheck()
{
    int i=0,j,value=0,tempNumber=0;
    string helistr;

    while(i<sequence.size())
    {
        i++;
        value=sequence[i].sequenceNumber;

           for(j=0;j<sequence.size()-1;j++)
             {
                   if(sequence[j+1].sequenceNumber<sequence[j].sequenceNumber)
                        {



                            helistr=sequence[j].helix_2;
                            sequence[j].helix_2=sequence[j+1].helix_2;
                            sequence[j+1].helix_2=helistr;

                            tempNumber=sequence[j].sequenceNumber;
                            sequence[j].sequenceNumber=sequence[j+1].sequenceNumber;
                            sequence[j+1].sequenceNumber=tempNumber;


                            helistr=sequence[j].helix_Final;
                            sequence[j].helix_Final=sequence[j+1].helix_Final;
                            sequence[j+1].helix_Final=helistr;

                            tempNumber=sequence[j].terminal;
                            sequence[j].terminal=sequence[j+1].terminal;
                            sequence[j+1].terminal=tempNumber;
                        }
         }


    }
}
///Sorting sheetdata

void sheetcheck()
{

    int i=0,j,value=0,tempNumber=0;
    string tempString;


    while(i<sheet.size())
    {
        i++;
        value=sheet[i].sequenceNumber;
         for(j=0;j<sheet.size()-1;j++)
         {
        if(sheet[j+1].sequenceNumber<sheet[j].sequenceNumber)
        {



            tempString=sheet[j].re2;
            sheet[j].re2=sheet[j+1].re2;
            sheet[j+1].re2=tempString;

            tempNumber=sheet[j].sequenceNumber;
            sheet[j].sequenceNumber=sheet[j+1].sequenceNumber;
            sheet[j+1].sequenceNumber=tempNumber;


            tempString=sheet[j].sheete;
            sheet[j].sheete=sheet[j+1].sheete;
            sheet[j+1].sheete=tempString;

            tempNumber=sheet[j].terminal;
            sheet[j].terminal=sheet[j+1].terminal;
            sheet[j+1].terminal=tempNumber;
        }
         }


    }

}





void extractData(string sequence, ofstream & outfile)
{
    string all;
    helixinfo xdat;
    sheetinfo sdat;
    atominfo adat;
    all=sequence.substr(0,5);
                  if(all=="HELIX")
                        {
                               xdat.helix_1=all;
                               outfile<<all<<" ";

                               all=sequence.substr(15,3);
                               outfile<<all<<" ";

                               xdat.helix_2=all;
                               all=sequence.substr(21,4);
                               outfile<<all<<" ";

                               xdat.sequenceNumber=atoi(all.c_str());

                               all=sequence.substr(27,3);
                               outfile<<all<<" ";

                               xdat.helix_Final=all;
                               all=sequence.substr(33,4);

                               outfile<<all<<" ";
                               xdat.terminal=atoi(all.c_str());

                               sequence.push_back(xdat);

                        }
                   if(all=="SHEET")
                        {

                               sdat.hltt=all;
                               outfile<<all<<" ";

                               all=sequence.substr(17,3);
                               outfile<<all<<" ";

                               sdat.re2=all;
                               all=sequence.substr(22,4);
                               outfile<<all<<" ";

                               sdat.sequenceNumber=atoi(all.c_str());

                               all=sequence.substr(28,3);
                               outfile<<all<<" ";

                               sdat.sheete=all;
                               all=sequence.substr(33,4);

                               outfile<<all<<" ";
                               sdat.terminal=atoi(all.c_str());

                               sheet.push_back(sdat);

                        }

     all=sequence.substr(0,4);
                     if(all=="ATOM")
                        {

                               adat.atomic=all;
                               outfile<<all<<" ";

                               all=sequence.substr(22,4);
                               adat.atoms=atoi(all.c_str());
                               outfile<<all<<" ";

                               all=sequence.substr(30,8);
                               adat.atoms_1=atoi(all.c_str());
                               outfile<<all<<" ";

                               all=sequence.substr(38,8);
                               adat.atoms_2=atoi(all.c_str());
                               outfile<<all<<" ";
                               all=sequence.substr(46,8);

                               adat.atoms_3=atoi(all.c_str());
                               outfile<<all<<" ";

                               atom.push_back(adat);



                         }

                                Helixcheck();


                                sheetcheck();




}












