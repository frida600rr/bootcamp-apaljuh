#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void stanje(int &budget,int &chipovi);

void uplata(int &budget,int &chipovi);

void izbornik();

void isplata(int &budget, int &chipovi);

void slot_m(int &budget, int &chipovi);

void igre(int &budget,int &chipovi);

void kockanje(int &budget,int &chipovi);

void kartanje(int &budget,int &chipovi);

void score();

int main(){

    string ime;
    int budget=0, izbor, chipovi=0;
    cout<<"Unesi ime: ";
    cin>>ime;
    cout<<"Unesi svoj budget u kunama: ";
    cin>>budget;


    izbornik();


    do{
        cin>>izbor;
          switch(izbor){
        case 1:
            uplata(budget,chipovi);
            break;
        case 2:
           isplata(budget,chipovi);
            break;
        case 3:
           igre(budget,chipovi);
            break;
        case 4:
           score();
            break;
        case 5:
            return 0;
            break;
        default:
            cout<<"Unijeli ste krivi izbor, birajte ponovo!" <<endl;

          }

        izbornik();
    }while(izbor!=0);


    return 0;
}

void stanje(int &budget,int &chipovi){
    cout<<endl<<"****Vase stanje: "<<budget<<" kuna i "<<chipovi<<" chipova****"<<endl;
};

void uplata(int &budget,int &chipovi){

    system("cls");
    int kolicina,ostatak=0;
    cout<<"Dobro dosli na blagajnu, ovdje mjenjate kune u chipove - 5kn za 1 chip"<<endl;
    stanje(budget,chipovi);
    cout<<"Koliko kuna zelite mjenjati? ";
    cin>>kolicina;
    if(kolicina%5==0){
        if(kolicina<=budget){
    chipovi=chipovi+kolicina/5;
    budget=budget-kolicina;
        }
    }else if(kolicina%5!=0){
        if(kolicina<=budget){
            chipovi=chipovi+kolicina/5;
            ostatak=int(kolicina%5);
            budget=(budget-kolicina) + ostatak;

        }
    }
    cout<<"Hvala i vidimo se uskoro"<<endl;
    system("pause");

};

void izbornik(){
    system("cls");
    cout<<"////////////////////////////////////"<<endl;
    cout<<"Unesi 1 za uplatu/zamjenu za chipove"<<endl;
    cout<<"Unesi 2 za isplatu, chipovi u kune"<<endl;
    cout<<"Unesi 3 za igre"<<endl;
    cout<<"Unesi 4 za pogledati najbolje rezultate"<<endl;
    cout<<"Unesi 5 za izlaz iz programa"<<endl;
    cout<<"////////////////////////////////////"<<endl;

}

void isplata(int &budget, int &chipovi){
    system("cls");
    int iznos=chipovi*5;
    cout<<"Dobrodosli na blagajnu, 1 chip je 5 kuna, vi imate "<< chipovi<<" chipova i mozete dobiti "<< iznos<<" kuna"<<endl;
    cout<<"Jeste li sigurni za isplatu ako da, biraj 1, ako ne biraj 0 za povratak u izbornik ";
    int odgovor;
    cin>>odgovor;
    if (odgovor==1){
        budget = budget+ iznos;
        chipovi=0;
    }
    stanje(budget,chipovi);
    system("pause");
    ofstream fout;
    fout.open("log_igre.txt", ios::app);

        fout<<iznos<<endl;
    fout.close();
}

void slot_m(int &budget, int &chipovi){
    system("cls");

    srand(time(0));
    cout<<"**Dobrodosli u jednoruki jack, slot machine**, biraj 1 da zavrtis, 0 za izlaz iz igre, dobitak je ulog x 6"<<endl;
    int izbor,ulog;
    cout<<"U svaki pokusaj, koliko chipova zelite uloziti?"<<endl;
    cin>>ulog;
    cout<<"U redu, mogu vrtit?"<<endl;
    cin>>izbor;
    char polje[4];

    while(izbor!=0){
        chipovi=chipovi-ulog;
        stanje(budget,chipovi);
       for(int i=0;i<4;i++){
            int x=rand()%4;
            if (x==0){
                polje[i]='+';
            }else if(x==1){
                polje[i]='X';
            }else if(x==2){
                polje[i]='O';
            }else if(x==3){
                polje[i]='*';
            }

            cout<<polje[i];
       }

       if(polje[0]==polje[1]&&polje[1]==polje[2]&&polje[2]==polje[3]){
        cout<<endl<<"*******DOBITAK!!!!*******"<<endl;
        chipovi=chipovi+ulog*10;
        stanje(budget,chipovi);

        ofstream fout;
        fout.open("slot_m.txt",ios::app);
            fout<<ulog*10<<endl;
        fout.close();
       }


       cout<<endl;
       cin>>izbor;

    }

}


void kockanje(int &budget,int &chipovi){
    system("cls");

    srand(time(0));
    cout<<"**Dobrodosli u kockanje**, biraj 1 da bacis kockicu, 0 za izlaz iz igre, dobitak je ulog x 2, upisi koliki je ulog"<<endl;
    int izbor;
    int ulog;
    cin>>ulog;
    cout<<"Uredu, mogu vrtit?"<<endl;
    cin>>izbor;



    while(izbor!=0){
        chipovi=chipovi-ulog;
        stanje(budget,chipovi);
        int korisnik=0,pc=0,zbr1=0,zbr2=0;

        for(int i=0;i<2;i++){
                korisnik=rand()%6;
                pc=rand()%6;
            cout<<"Korisnik baca... "<<korisnik<<endl;
            cout<<"Racunalo baca... "<<pc<<endl;
                zbr1+=korisnik;
                zbr2+=pc;
        }
        cout<<"Zbroj 1.igraca "<<zbr1<<endl;
        cout<<"Zbroj 2.igraca "<<zbr2<<endl;

       if(zbr1>zbr2){
            cout<<endl<<"*******DOBITAK!!!!*******"<<endl;
            cout<<"Osvojili ste "<<ulog*2<<"chipova!"<<endl;

            chipovi=chipovi+ ulog*2;
            stanje(budget,chipovi);

            ofstream fout;
            fout.open("kockanje.txt",ios::app);
                fout<<ulog*2<<endl;
            fout.close();

       }else if(zbr1==zbr2){
            cout<<"Vracam ulog, zbroj bacanja jednak!"<<endl;
            chipovi=chipovi+ulog;
       }

       cout<<endl;
       cin>>izbor;

    }

}

void kartanje(int &budget,int &chipovi){
    system("cls");
    srand(time(0));
    cout<<"Dobrodosli u ***kartanje***, biraj pocetni ulog"<<endl;
    int ulog,izbor;
    cin>>ulog;
    cout<<"Zelis zapoceti?"<<endl;
    cin>>izbor;
    int polje[4][13];
    for (int i=0;i<4;i++){
        for(int j=0;j<13;j++){
            polje[i][j]=j+1;
        }
    }

    int redak,stupac,redak1,stupac1;
    while(izbor!=0){

        do{
            redak = rand()%4;
            stupac = rand()%13;
            redak1 =rand()%4;
            stupac1=rand()%13;
        }while(polje[redak][stupac]==0 && polje[redak1][stupac1]==0);


        cout<<"Igrac je izvukao: "<<polje[redak][stupac]<<endl;
        cout<<"Racunalo je izvuklo: "<<polje[redak1][stupac1]<<endl;

        if(polje[redak][stupac]>polje[redak1][stupac1]){
            cout<<"Igrac dobio, zelite li igrati za duplo 1-da, 0-ne"<<endl;
            int izbory;
            cin>>izbory;
            if(izbory==1){

                polje[redak][stupac]=0;
                polje[redak1][stupac1]=0;
               do{
                    redak = rand()%4;
                    stupac = rand()%13;
                    redak1 =rand()%4;
                    stupac1=rand()%13;
               }while(polje[redak][stupac]==0 && polje[redak1][stupac1]==0);

                cout<<"Igrac je izvukao: "<<polje[redak][stupac]<<endl;
                cout<<"Racunalo je izvuklo: "<<polje[redak1][stupac1]<<endl;
                if(polje[redak][stupac]>polje[redak1][stupac1]){
                    cout<<"****DOBITAK!!!****"<<endl;
                    chipovi=chipovi+ulog*2*2;
                    stanje(budget,chipovi);
                    ofstream fout;
                    fout.open("duplo.txt",ios::app);
                        fout<<ulog*2*2<<endl;
                    fout.close();

                }else if(polje[redak][stupac]<polje[redak1][stupac1]){
                    cout<<"Izgubili ste!"<<endl;
                    chipovi=chipovi-ulog*2;
                    stanje(budget,chipovi);
                }


            }else{
                chipovi=chipovi+ulog*2;
                stanje(budget,chipovi);

            }
        }else if(polje[redak][stupac]<polje[redak1][stupac1]){
            cout<<"Racunalo je dobilo, zelite li igrati za dupli ulog 1-da,0-ne?"<<endl;
            int duplo=0;
            cin>>duplo;

            if(duplo==1){
                    polje[redak][stupac]=0;
                    polje[redak1][stupac1]=0;
                do{
                    redak = rand()%4;
                    stupac = rand()%13;
                    redak1 =rand()%4;
                    stupac1=rand()%13;
                }while(polje[redak][stupac]==0 && polje[redak1][stupac1]==0);

                cout<<"Igrac je izvukao: "<<polje[redak][stupac]<<endl;
                cout<<"Racunalo je izvuklo: "<<polje[redak1][stupac1]<<endl;
                if(polje[redak][stupac]>polje[redak1][stupac1]){
                    cout<<"****DOBITAK!!!****"<<endl;
                    chipovi=chipovi+ulog*2*2;
                    stanje(budget,chipovi);
                    ofstream fout;
                    fout.open("duplo.txt",ios::app);
                        fout<<ulog*2*2<<endl;
                    fout.close();
                }else if(polje[redak][stupac]<polje[redak1][stupac1]){
                    cout<<"Izgubili ste!"<<endl;
                    chipovi=chipovi-ulog*2;
                    stanje(budget,chipovi);
                }
            }else{
                chipovi=chipovi-ulog;
                stanje(budget,chipovi);
            }
        }
        cout<<"Zelite li ponovo igrati? biraj 1"<<endl;
        cin>>izbor;
    }
}

void score(){
    ifstream fin;
    fin.open("slot_m.txt");
        vector<int>vektor;
        int tmp=0;
        while(fin){
           fin>>tmp;
           vektor.push_back(tmp);
        }
        sort(vektor.begin(),vektor.end());
        vektor.pop_back();
        cout<<"Slot machine najbolji rezultati dobitka chipova"<<endl;
        int brojac=1;
        for(int i=vektor.size();i>vektor.size()-3;i--){
        cout<<brojac<<". "<<vektor[i]<<endl;
        brojac++;
        }
    fin.close();

    ifstream fin2;
    fin2.open("kockanje.txt");
        vector<int>vektor2;
        tmp=0;
        while(fin2){
           fin2>>tmp;
           vektor2.push_back(tmp);
        }
        sort(vektor2.begin(),vektor2.end());
        vektor2.pop_back();
        cout<<"Kockanje najbolji rezultati dobitka chipova"<<endl;
        brojac=1;
        for(int i=vektor2.size();i>vektor2.size()-3;i--){
        cout<<brojac<<". "<<vektor2[i]<<endl;
        brojac++;
        }
    fin2.close();

    ifstream fin3;
    fin3.open("duplo.txt");
        vector<int>vektor3;
        tmp=0;
        while(fin3){
           fin3>>tmp;
           vektor3.push_back(tmp);
        }
        sort(vektor3.begin(),vektor3.end());
        vektor3.pop_back();
        cout<<"Kartanje - najbolji rezultati dobitka chipova"<<endl;
        brojac=1;
        for(int i=vektor3.size();i>vektor3.size()-3;i--){
        cout<<brojac<<". "<<vektor3[i]<<endl;
        brojac++;
        }
    fin2.close();


    ifstream fin4;
    fin4.open("log_igre.txt");
        vector<int>vektor4;
        tmp=0;
        while(fin4){
           fin4>>tmp;
           vektor4.push_back(tmp);
        }
        sort(vektor4.begin(),vektor4.end());
        vektor4.pop_back();
        cout<<"Najveci osvojeni iznosi (isplata chipovi u kune)"<<endl;
        brojac=1;
        for(int i=vektor4.size();i>vektor4.size()-3;i--){
        cout<<brojac<<". "<<vektor4[i]<<endl;
        brojac++;
        }
    fin4.close();
    system("pause");
}

void igre(int &budget,int &chipovi){


    int izbor=0;
    do{
            system("cls");
            cout<<"***Dobrodosli u igre***"<<endl;
            cout<<"Biraj 1 za *Slot machine* \nBiraj 2 za *Kockanje* \nBiraj 3 za *Duplo ili nista*"<<endl;

        cin>>izbor;
        switch(izbor){
        case 1:
            slot_m(budget,chipovi);
            break;
        case 2:
           kockanje(budget,chipovi);
            break;
        case 3:
           kartanje(budget,chipovi);
            break;
        default:
            cout<<"Nemam tu igru, biraj ponovo"<<endl;
            break;

        }
    }while(izbor!=0);

}
