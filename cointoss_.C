#include<iostream>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<iomanip>
using namespace std;

double A_ (double B, double* y, int N/*=dimreg*/) {
	double A = (1-exp(-2*B))/(1-exp(-2*B*(N+1)));
	double t = 0;
	for (int i=0;i<N;++i) {
		t+= y[i]*exp(-B*i);
	}
	A*=t;
	return A;
}

double chi (double B, double*y, int N) {
	double t =0;
	for (int i=0;i<N;++i) {
		t+= pow(y[i] - A_(B,y,N)*exp(-B*i),2);
	}
	return t;
}



double AB (double a) {return a>-a?a:-a;}



int main () {
	/* caro me del futuro: questo programma conteggia il numero di teste o croci consecutive in un totale di totalcointoss lanci.
	i risultati sono interessanti
	*/
	
	int dimreg = 50;
	double* reg = new double [dimreg];
	double r = rand();
	r /= RAND_MAX;
	double aux;
	double t;
	double totalcointoss = pow(10,8);
	
	int cont = 0;
	
	for (long long unsigned int i=0;i<totalcointoss;++i) {
		
		if (i-cont == 3000) {
			cout <<'\r'<< (int)  (100*((double)i) / totalcointoss) <<'%';
			cont = i;
		}
		
		aux = r;
		r = rand();
		r/=RAND_MAX;
		
		if (r < .5) r = 0;
		else r=1;
		if (aux <.5) aux = 0;
		else aux = 1;
		
		if (r == aux) {
			t++;
		}
		else {
		if (t<dimreg){
				reg[(int)t] ++;
				t=0;
			}
			else {
				cout << "\n Fatal Core Error\n"; return 0;
			}
		}
		
	}
	
	cout<<endl<<endl;
	double pcheck= 0;
	double pcheck2 = 0;
	
	for (int i=0;i<dimreg;++i) {
		pcheck+=reg [i];
	}
	
	for (int i=0;i<dimreg;++i) {
		reg[i] /= pcheck;
		reg[i] *= 100;
		pcheck2 += reg[i];
		if (reg[i]>0)cout << i<<setprecision(8)<<fixed<<" - "<< reg [i] <<"%,\t\t"<<"p(<"<<i+1<<") = "<<pcheck2<<"%,\t\t"<<"p(>"<<i<<") = "<<100 - pcheck2<<'%'<<endl;
		reg[i] /=100.;
	}
	
	double B = rand();
	B/=RAND_MAX;
	int cc=0;
	//double t;
	aux=0;
	double oldt = chi(B,reg,dimreg);
	
	while (true) {cc++;
	//if (true) cout << "\n"<<cc<<") best fit : "<<A_(B,reg,dimreg)<<"*exp(-"<<B<<"n)\n";
		r = rand();
		r/=RAND_MAX;
		r*=2;
		r-=1;
		r/=100;
		
		t = chi(B, reg, dimreg);
		
		B+=r;
		
		if (chi(B,reg,dimreg) > t) {
			B-=r;
		}
		
		
		if (cc-aux > 9) {
			//cout << "\n CONVTEST best fit : "<<A_(B,reg,dimreg)<<"*exp(-"<<B<<"n)\n";
			if (AB (chi(B,reg,dimreg) - oldt)/10 < 0.00001) {/*cout<<"\nCONVERGENCE\n";*/break;}
			else {
				aux = cc;
				oldt = chi(B,reg,dimreg);
			}
		}
	}
	
	cout << "\n best fit : "<<A_(B,reg,dimreg)<<"*exp(-"<<B<<"n)\n\n";
	
	pcheck = 0;
	
	for (int i=0;i<dimreg;++i) {
		pcheck+=reg [i];
	}
	
	for (int i=0;i<dimreg;++i) {
		reg[i] /= pcheck;
		//pcheck2 += reg[i];
		if (reg[i]>0)cout <<i<<setprecision(14)<<fixed<<") data: "<< reg [i] <<"\t expected from fit: "<<A_(B,reg,dimreg)*exp(-B*i)<<
		"\t analytical:"<<.5*exp(-i*log(2))
		<< "\n_____________________________________________________________________________________________________\n" <<
		endl;
		
	}
	
	fstream ff ("coin.txt");
	//ff.open();
	
	for (int i=0;i<dimreg;++i) {
		reg[i] /= pcheck;
		//pcheck2 += reg[i];
		if (reg[i]>0) ff <<i<<setprecision(8)<<fixed<<" & "<< reg [i] <<" & "<<A_(B,reg,dimreg)*exp(-B*i)<<
		" & "<<.5*exp(-i*log(2))
		<< " \\\\ \n";
		
	}
	
	ff.close();
	/*è stato bello finchè è durato*/
	
}
