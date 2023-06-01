#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

class cursa
{
protected:
    string locatie_cursa;
    string tip;
    double durata;
public:
    cursa (string, string, double);
    cursa (cursa&);
    virtual ~cursa();

    virtual void citire (istream &in);
    virtual void afisare(ostream &out);


    cursa& operator=(cursa &p);
    friend istream& operator>>(istream&, cursa&);
    friend ostream& operator<<(ostream&, cursa&);
    friend class persoane;
};
cursa::cursa (string num="", string tip="", double minute=0)
{
    locatie_cursa=num;
    tip=tip;
    try
    {
        if (minute<0)
            throw minute;
    }
    catch (double x)
    {
        cout<<"Eroare in constructor, minutele nu pot fi negative.\n";
        exit(EXIT_FAILURE);
    }
    durata=minute;
}
void cursa::citire(istream &in)
{
    string x;
    cout<<"Locatia cursei:";
    in>>x;
    locatie_cursa=x;
    cout<<"Tipul cursei:";
    in>>x;
    tip=x;
    cout<<"Durata cursei:";
    string p;
    in>>p;
    double d;
    char *q=new char [p.length()+1];
    strcpy(q,p.c_str());
    d=atof(q);
    try
    {
        if (d<0)
            throw 1;
    }
    catch (int x)
    {
        cout<<"Eroare in setarea duratei, minutele nu pot fi negative.\n";
        exit(EXIT_FAILURE);
    }
    durata=d;
}
void cursa::afisare(ostream &out)
{
    out<<"Locatia cursei: "<<locatie_cursa<<"\n";
    out<<"Tipul cursei: "<<tip<<"\n";
    out<<"Durata cursei: "<<durata<<"\n";
}
cursa::cursa (cursa &p)
{
    locatie_cursa=p.locatie_cursa;
    tip=p.tip;
    durata=p.durata;
}
cursa::~cursa()
{

}
cursa& cursa :: operator= (cursa &x)
{
    if (this!=&x)
    {
        locatie_cursa=x.locatie_cursa;
        tip=x.tip;
        durata=x.durata;
    }
    return *this;
}
istream& operator>>(istream& in,cursa& f)
{
    f.citire(in);
    return in;
}

ostream& operator<<(ostream& out, cursa& f)
{
    f.afisare(out);
    return out;
}
///------------------------------------------------------

class persoane
{
protected:
    string cnp;
    string nume_persoana;
    cursa *curse;
    int nr;
public:
    persoane (string, string, cursa*,int);
    persoane (persoane&);
    virtual ~persoane();

    int get_numar()
    {
        return nr;
    }
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    persoane& operator=(persoane &p);
    friend istream& operator>>(istream&, persoane&);
    friend ostream& operator<<(ostream&, persoane&);

    friend ifstream& operator>>(ifstream&, persoane&);

};

persoane::persoane (string c="",string numep="",cursa *f=NULL,int nr=0)
{
    try
    {
        for (unsigned int i=0; i<c.length(); i++)
            if (c[i]<'0'||c[i]>'9')
                throw 1;
    }
    catch(int i)
    {
        cout<<"Eroare constructor, CNP-ul persoanei poate contine doar cifre.\n";
        exit(EXIT_FAILURE);
    }
    cnp=c;
    nume_persoana=numep;
    curse=new cursa[nr];
    for(int i=0; i<nr; i++)
        curse[i]=f[i];

}
persoane::persoane(persoane &p)
{
    cnp=p.cnp;
    nume_persoana=p.nume_persoana;
    nr=p.nr;
    curse=new cursa[nr];
    for(int i=0; i<nr; i++)
        curse[i]=p.curse[i];

}
persoane::~persoane()
{

}
void persoane::citire(istream &in)
{
    string x;
    cout<<"CNP:";
    in>>x;
    cnp=x;
    cout<<"Nume:";
    in>>x;
    nume_persoana=x;
    cout<<"Numarul de curse: ";
    in>>nr;
    curse=new cursa[nr];
    for(int i=0; i<nr; i++)
        in>>curse[i];
}
void persoane::afisare(ostream &out)
{
    out<<"CNP: "<<cnp<<"\n";
    out<<"Nume: "<<nume_persoana<<"\n";
    out<<"Cele "<<nr<<" curse sunt: "<<"\n";
    int i;
    for(i=0; i<nr-1; i++)
        out<<curse[i]<<"\n";
    if (nr!=0)
        out<<curse[i];
}
persoane& persoane :: operator= (persoane &x)
{
    if (this!=&x)
    {
        cnp=x.cnp;
        nume_persoana=x.nume_persoana;
        nr=x.nr;
        curse=new cursa[nr];
        for(int i=0; i<nr; i++)
            curse[i]=x.curse[i];
    }
    return *this;
}
istream& operator>>(istream& in,persoane& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, persoane& p)
{
    p.afisare(out);
    return out;
}
///-------------------------------------------------
class personal:public persoane
{
protected:
    double* procent_incasari;
public:
    personal(string, string, cursa*,int, double*);
    personal(personal&);
    ~personal();

    void citire(istream &in);
    void afisare(ostream &out);

    personal& operator=(personal &p);
    friend istream& operator>>(istream&, personal&);
    friend ostream& operator<<(ostream&, personal&);

    friend ifstream& operator>>(ifstream&, personal&);
};
personal::personal(string c="",string numep="",cursa* f=NULL,int n=0,double procent[]=0):persoane(c,numep,f,n)
{
    if (f)
    {
        procent_incasari=new double[nr];
        for (int i=0; i<nr; i++)
            procent_incasari[i]=procent[i];

    }
}
personal::personal(personal &p):persoane(p)
{
    procent_incasari=new double[p.nr];
    for (int i=0; i<p.nr; i++)
        procent_incasari[i]=p.procent_incasari[i];
}
personal::~personal()
{

}
void personal::citire(istream &in)
{
    persoane::citire(in);
    procent_incasari=new double[nr];
    for (int i=0; i<nr; i++)
    {
        cout<<"Introduceti procentul castigat "<<i+1<<": ";
        string p1;
        in>>p1;
        double d;
        char *q=new char [p1.length()+1];
        strcpy(q,p1.c_str());
        d=atof(q);
        try
        {
            if (d<0||d>100)
                throw 1;
        }
        catch (int i)
        {
            cout<<"Eroare la setarea procentului din incasari. Valoarea procentului trebuie sa fie intre 0% si 100%.\n";
            exit(EXIT_FAILURE);
        }
        procent_incasari[i]=d;
    }
}
void personal::afisare(ostream &out)
{
    persoane::afisare(out);
    int i;
    for (i=0; i<nr-1; i++)
        out<<"Procent incasari "<<i+1<<": "<<procent_incasari[i]<<"\n";
    if (nr!=0)
        out<<"Procent incasari "<<i+1<<": "<<procent_incasari[i]<<"\n";
}
personal& personal :: operator=(personal &x)
{
    if(this!=&x)
    {
        persoane::operator=(x);
        for (int i=0; i<x.nr; i++)
            procent_incasari[i]=x.procent_incasari[i];
    }
    return *this;
}
istream& operator>>(istream& in,personal& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, personal& p)
{
    p.afisare(out);
    return out;
}

///-------------------------------------------------
class instructor_pilot:public personal
{
    double* suma_fixa;
public:
    instructor_pilot(string, string, cursa*,int, double*, double*);
    instructor_pilot(instructor_pilot&);
    ~instructor_pilot();

    void citire(istream &in);
    void afisare(ostream &out);

    instructor_pilot& operator=(instructor_pilot &p);
    friend istream& operator>>(istream&, instructor_pilot&);
    friend ostream& operator<<(ostream&, instructor_pilot&);
};
instructor_pilot::instructor_pilot(string c="",string numep="",cursa* f=NULL,int n=0,double procent[]=0,double suma[]=0):personal(c,numep,f,n,procent)
{
    if (f)
    {
        suma_fixa=new double[nr];
        for (int i=0; i<nr; i++)
            suma_fixa[i]=suma[i];
    }
}
instructor_pilot::instructor_pilot(instructor_pilot &p):personal(p)
{
    suma_fixa=new double[p.nr];
    for (int i=0; i<p.nr; i++)
        suma_fixa[i]=p.suma_fixa[i];
}
instructor_pilot::~instructor_pilot()
{

}
void instructor_pilot::citire(istream &in)
{
    personal::citire(in);
    suma_fixa=new double[nr];
    for (int i=0; i<nr; i++)
    {
        cout<<"Introduceti suma fixa castigata "<<i+1<<": ";
        string p1;
        in>>p1;
        double d;
        char *q=new char [p1.length()+1];
        strcpy(q,p1.c_str());
        d=atof(q);
        suma_fixa[i]=d;
    }
}
void instructor_pilot::afisare(ostream &out)
{
    personal::afisare(out);
    int i;
    for (i=0; i<nr-1; i++)
        out<<"Suma fixa "<<i+1<<": "<<suma_fixa[i]<<"\n";
    if (nr!=0)
        out<<"Suma fixa "<<i+1<<": "<<suma_fixa[i]<<"\n";
}
instructor_pilot& instructor_pilot :: operator=(instructor_pilot &x)
{
    if(this!=&x)
    {
        personal::operator=(x);
        for (int i=0; i<x.nr; i++)
            suma_fixa[i]=x.suma_fixa[i];
    }
    return *this;
}

istream& operator>>(istream& in,instructor_pilot& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, instructor_pilot& p)
{
    p.afisare(out);
    return out;
}
///-------------------------------------------------
class pilot:public personal
{
    bool* titular;
public:
    pilot(string, string, cursa*,int, double*,bool*);
    pilot(pilot&);
    ~pilot();

    bool get_titular(int i)
    {
        return titular[i];
    }
    void citire(istream &in);
    void afisare(ostream &out);

    pilot& operator=(pilot &p);
    friend istream& operator>>(istream&, pilot&);
    friend ostream& operator<<(ostream&, pilot&);
};
pilot::pilot(string c="",string numep="",cursa* f=NULL,int n=0,double procent[]=0,bool princ[]=0):personal(c,numep,f,n,procent)
{
    if (f)
    {
        titular=new bool[nr];
        for (int i=0; i<nr; i++)
            titular[i]=princ[i];
        for (int i=0; i<nr; i++)
            if (titular[i]==1)
                procent_incasari[i]=procent_incasari[i]+10;
    }
}
pilot::pilot(pilot &p):personal(p)
{
    titular=new bool[p.nr];
    for (int i=0; i<p.nr; i++)
        titular[i]=p.titular[i];
}
pilot::~pilot()
{

}
void pilot::citire(istream &in)
{
    personal::citire(in);
    titular=new bool[nr];
    for (int i=0; i<nr; i++)
    {
        cout<<"Pilot pentru cursa "<<i+1<<": ";
        bool d;
        in>>d;
        titular[i]=d;
        if (d!=0)
            procent_incasari[i]+=10;
    }
}
void pilot::afisare(ostream &out)
{
    personal::afisare(out);
    int i;
    for (i=0; i<nr-1; i++)
        out<<"Pilotul titular pentru cursa "<<i+1<<": "<<titular[i]<<"\n";
    if (nr!=0)
        out<<"Pilotul titular pentru cursa "<<i+1<<": "<<titular[i];
    out<<"\n";
}
pilot& pilot :: operator=(pilot &x)
{
    if(this!=&x)
    {
        personal::operator=(x);
        for (int i=0; i<x.nr; i++)
            titular[i]=x.titular[i];
    }
    return *this;
}

istream& operator>>(istream& in,pilot& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, pilot& p)
{
    p.afisare(out);
    return out;
}

///-------------------------------------------------
class mecanic_auto:public personal
{
    string* specializare;
public:
    mecanic_auto(string, string, cursa*,int, double*,string*);
    mecanic_auto(mecanic_auto&);
    ~mecanic_auto();

    void citire(istream &in);
    void afisare(ostream &out);

    mecanic_auto& operator=(mecanic_auto &p);
    friend istream& operator>>(istream&, mecanic_auto&);
    friend ostream& operator<<(ostream&, mecanic_auto&);
};
mecanic_auto::mecanic_auto(string c="",string numep="",cursa* f=NULL,int n=0,double procent[]=0,string spec[]=0):personal(c,numep,f,n,procent)
{
    if (f)
    {
        specializare=new string[nr];
        for (int i=0; i<nr; i++)
            specializare[i]=spec[i];
    }
}
mecanic_auto::mecanic_auto(mecanic_auto &p):personal(p)
{
    specializare=new string[nr];
    for (int i=0; i<p.nr; i++)
        specializare[i]=p.specializare[i];
}
mecanic_auto::~mecanic_auto()
{

}
void mecanic_auto::citire(istream &in)
{
    personal::citire(in);
    specializare=new string[nr];
    for (int i=0; i<nr; i++)
    {
        cout<<"Specializare pentru cursa "<<i+1<<": ";
        string d;
        in>>d;
        specializare[i]=d;
    }
}
void mecanic_auto::afisare(ostream &out)
{
    personal::afisare(out);
    int i;
    for (i=0; i<nr-1; i++)
        out<<"Specializare pentru cursa "<<i+1<<": "<<specializare[i]<<"\n";
    if (nr!=0)
        out<<"Specializare pentru cursa "<<i+1<<": "<<specializare[i];
    out<<"\n";
}
mecanic_auto& mecanic_auto :: operator=(mecanic_auto &x)
{
    if(this!=&x)
    {
        personal::operator=(x);
        for (int i=0; i<x.nr; i++)
            specializare[i]=x.specializare[i];
    }
    return *this;
}

istream& operator>>(istream& in,mecanic_auto& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, mecanic_auto& p)
{
    p.afisare(out);
    return out;
}

template <class t> class EchipaCurse
{
    t *v;
    int nr;
public:
    EchipaCurse(t *p=NULL, int n=0)
    {
        nr=n;
        if (n!=0)
        {
            v=new t[n];
            for(int i=0; i<n; i++)
            {
                v[i]=p[i];
            }
        }
    }
    EchipaCurse(EchipaCurse &a)
    {
        nr=a.nr;
        v=new t[nr];
        for(int i=0; i<nr; i++)
        {
            v[i]=a.v[i];
        }
    }
    ~EchipaCurse()
    {
        delete [] v;
    }

    int get_nr();
    t get_v(int i)
    {
        return v[i];
    }
    friend istream& operator >>(istream &in, EchipaCurse <t> &g)
    {
        cout<<"Introduceti numarul de persoane implicate: ";
        in>>g.nr;
        g.v=new t[g.nr];
        cout<<"Introduceti obiectele: \n";
        for(int i=0; i<g.nr; i++)
        {
            in>>g.v[i];
            cout<<"\n";
        }
        return in;
    }
    friend ostream& operator <<(ostream &out, EchipaCurse<t> &g)
    {
        out<<"In EchipaCurse se gasesc urmatoarele "<<g.nr<<" persoane implicate:"<<"\n";
        for(int i=0; i<g.nr; i++)
            out<<g.v[i]<<"\n";
        return out;
    }
};

template <class t> int EchipaCurse<t>::get_nr()
{
    return nr;
}

template <> class EchipaCurse <pilot>
{
    pilot* v;
    int nr;
    int nr_piloti_titulari;
public:
    EchipaCurse(pilot *p=NULL, int n=0)
    {
        nr_piloti_titulari=0;
        nr=n;
        v=new pilot[n];
        for(int i=0; i<n; i++)
        {
            v[i]=p[i];
            for (int j=0; j<v[i].get_numar(); j++)
                if (v[i].get_titular(j)==1)
                {
                    nr_piloti_titulari+=1;
                    break;
                }
        }
    }
    EchipaCurse(EchipaCurse &a)
    {
        nr=a.nr;
        nr_piloti_titulari=0;
        v=new pilot[nr];
        for(int i=0; i<nr; i++)
        {
            v[i]=a.v[i];
            for (int j=0; j<v[i].get_numar(); j++)
                if (v[i].get_titular(j)==1)
                    nr_piloti_titulari+=1;
        }
    }
    ~EchipaCurse()
    {
        delete [] v;
    }

    int get_nr()
    {
        return nr;
    }
    pilot get_v(int i)
    {
        return v[i];
    }
    friend istream& operator >>(istream &in, EchipaCurse <pilot> &g)
    {
        cout<<"Introduceti numarul de piloti implicati: ";
        in>>g.nr;
        g.v=new pilot[g.nr];
        cout<<"Introduceti obiectele\n";
        for(int i=0; i<g.nr; i++)
        {
            in>>g.v[i];
            for (int j=0; j<g.v[i].get_numar(); j++)
                if (g.v[i].get_titular(j)==1)
                {
                    g.nr_piloti_titulari+=1;
                    break;
                }
            cout<<"\n";
        }
        return in;
    }
    friend ostream& operator <<(ostream &out, EchipaCurse<pilot> &g)
    {
        out<<"In EchipaCurse sunt "<<g.nr<<" piloti implicati.\n";
        for(int i=0; i<g.nr; i++)
            out<<g.v[i]<<"\n";
        out<<"Dintre acestia, "<<g.nr_piloti_titulari<<" sunt piloti titulari.\n";
        return out;
    }
};


void tip(personal *&p, int &i)
{
    string s;
    cout<<"\n";
    cout<<"Introduceti tipul personalului "<<i+1<<": ";
    cin>>s;
    try
    {
        if(s=="instructor_pilot")
        {
            p=new instructor_pilot;
            cin>>*p;
            i++;
        }
        else if(s=="pilot")
        {
            p=new pilot;
            cin>>*p;
            i++;
        }
        else if(s=="mecanic_auto")
        {
            p=new mecanic_auto;
            cin>>*p;
            i++;
        }
        else
            throw 10;
    }
    catch (bad_alloc var)
    {
        cout << "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int j)
    {
        cout<<"Nu ati introdus un tip valid. Incercati instructor_pilot, pilot sau mecanic_auto.\n ";
    }
}
void menu_output()
{
    cout<<"\nCURSE FORMULA1\n";
    cout<<"\n\t\tMENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citeste informatii despre persoanele implicate.";
    cout<<"\n";
    cout<<"2. EchipaCurse --- TEMPLATE (instructor_pilot).";
    cout<<"\n";
    cout<<"3. EchipaCurse --- TEMPLATE (mecanic_auto).";
    cout<<"\n";
    cout<<"4. EchipaCurse --- TEMPLATE (pilot).";
    cout<<"\n";
    cout<<"5. Contorizare personal.";
    cout<<"\n";
    cout<<"0. Iesire.";
    cout<<"\n";
}
void menu()
{
    int option;///optiunea aleasa din meniu
    option=0;
    int n=0;
    personal **v;
    do
    {
        menu_output();
        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;
        if (option==1)
        {
            cout<<"Introduceti numarul de obiecte citite: ";
            cin>>n;
            v=new personal*[n];
            if (n>0)
            {
                for(int i=0; i<n;)
                    tip(v[i],i);
                cout<<"\nAfisam personalul citit anterior:\n";
                for(int i=0; i<n; i++)
                {
                    cout<<"\n"<<*v[i];
                    cout<<"--------------------------\n";
                }
            }
            else
                cout<<"Numarul introdus trebuie sa fie pozitiv.\n";
        }
        if (option==2)
        {
            EchipaCurse <instructor_pilot> x;
            cin>>x;
            cout<<x;
        }
        if (option==3)
        {
            EchipaCurse <mecanic_auto> x;
            cin>>x;
            cout<<x;
        }
        if (option==4)
        {
            EchipaCurse <pilot> x;
            cin>>x;
            cout<<x;
        }
        if (option==5)
        {
            int N_reg,N_act,N_teh;
            N_reg=N_act=N_teh=0;
            if (n>0)
            {
                for(int i=0; i<n; i++)
                {
                    instructor_pilot *p1=dynamic_cast<instructor_pilot*>(v[i]);
                    pilot *p2=dynamic_cast<pilot*>(v[i]);
                    mecanic_auto *p3=dynamic_cast<mecanic_auto*>(v[i]);
                    if (p1)
                        N_reg++;
                    if (p2)
                        N_act++;
                    if (p3)
                        N_teh++;
                }
                cout<<"Numarul de instructor_piloti: "<<N_reg<<"\n";
                cout<<"Numarul de piloti: "<<N_act<<"\n";
                cout<<"Numarul de mecanic_auto: "<<N_teh<<"\n";
            }
            else
            {
                cout<<"Nu s-au citit persoane. Reveniti la actiunea 1.\n";
            }
        }
        if (option==0)
        {
            cout<<"\nEXIT\n\n";
        }
        if (option<0||option>5)
        {
            cout<<"\nSelectie invalida\n";
        }
        cout<<"\n";
        system("pause");
        system("cls");
    }
    while(option!=0);
}
int main()
{
    menu();
    return 0;
}
