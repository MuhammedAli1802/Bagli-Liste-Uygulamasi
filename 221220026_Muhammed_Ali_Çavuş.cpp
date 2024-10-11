
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Kayit{
	char isim[10],soyisim[10];
	int num;
	struct Kayit *sonraki;
}kayit;

kayit *ilk=NULL,*sonraki=NULL,*son=NULL,*gecici=NULL;

int number,x,y,kayitsayisi=0;
char adal[10],soyadal[10];

void ekle(char *a,char *b,int c);
void listele();
void arama();
void silme();
void tasima(int a,int b);
void okuma();
void yazdirma();

void tersyaz(kayit *gecici) // recursive �rne�i
{
if(gecici->sonraki!=NULL) tersyaz(gecici->sonraki);
printf("%d ",gecici->num);
}

void okuma(){
	FILE *read;
	if((read=fopen("dosya.txt","r"))==NULL){
		printf("Dosya ac�lamad�.");
	}
	
	while( !feof(read) ){
		fscanf(read,"%d#%9[^#]#%9[^\n]",&number,adal,soyadal); //ald���m�z char max 10 byte oldugu i�in # ler aras�na 9 yazd�k.
		ekle(adal,soyadal,number);
	}
	fclose(read);
}

void yazdirma(){
	FILE *write;
	if((write=fopen("dosya.txt","w"))==NULL){
		printf("Dosya ac�lamad�.");
	}
	kayit *yaz=ilk;
	while(yaz->sonraki!=NULL){
		fprintf(write,"%d#%s#%s\n",yaz->num,yaz->isim,yaz->soyisim);
		yaz=yaz->sonraki;
	}
	fprintf(write,"%d#%s#%s",yaz->num,yaz->isim,yaz->soyisim);
	fclose(write);
}

void anamenu(){
	int menusecim;
	printf("------ A N A  M E N U ------\n");
	printf("1. Listeleme\n2. Ekle\n3. Arama\n4. Silme\n5. Tasima\n6. Cikis\n");
	scanf("%d",&menusecim);
	switch (menusecim){
		case 1: listele(); break;
		case 2: 
				system("cls");
				printf("Kisinin ismi: "); scanf("%s",&adal);
				printf("Kisinin soyismi: "); scanf("%s",&soyadal);
				printf("Kisinin numarasi: "); scanf("%d",&number);
				ekle(adal,soyadal,number); anamenu(); break;
			
		case 3: arama(); break;
		case 4: silme(); break;
		case 5: printf("Tasimak istediginiz kaydin numarasini ve tasimak istediginiz sirayi giriniz\n"); scanf("%d%d",&x,&y); tasima(x,y); break;
		case 6: yazdirma(); exit(0);
		case 7: tersyaz(ilk);
	}
}

void ekle(char *a,char *b,int c){
		if(ilk==NULL){
			ilk=(kayit*) malloc(sizeof(kayit));
			strcpy(ilk->isim,a);
			strcpy(ilk->soyisim,b);
			ilk->num=c;
			ilk->sonraki=NULL;
			son=ilk;
		}
		else{
			son->sonraki=(kayit*) malloc(sizeof(kayit));
			son=son->sonraki;
			strcpy(son->isim,a);
			strcpy(son->soyisim,b);
			son->num=c;
			son->sonraki=NULL;
		}
		kayitsayisi++;
}

void listele(){
	int n=1;
	system("cls");
	gecici=ilk;
	while(gecici!=NULL){
		printf("%d. Kisinin Ismi: %s\n%d. Kisinin Soyismi: %s\n%d. Kisinin Numarasi: %d\n\n",n,gecici->isim,n,gecici->soyisim,n,gecici->num);
		gecici=gecici->sonraki;
		n++;
	}
	anamenu();
}

void arama(){
	char aranansoyad[10];
	kayit *bulundu=NULL;
	char b = 'h';
	int sayac=0;
	printf("Aranan kisinin soyismi: "); scanf("%s",aranansoyad);
	gecici=ilk;
	while(gecici!=NULL && b =='h'){
		if(strcmp(gecici->soyisim,aranansoyad)==0){
			printf("Kisinin Ismi: %s\nKisinin Soyismi: %s\n%Kisinin Numarasi: %d\n\n",gecici->isim,gecici->soyisim,gecici->num);
			printf("Aranan kisi bulundu mu? (e/h)\n"); scanf("%s",&b);
			if(b=='e'){
				bulundu=gecici;
			}
		}
		gecici=gecici->sonraki;
		sayac++;
	}
	if(b=='h'){
		printf("Aranan kisi bulunamadi.\n");
	}
	else if(b=='e'){
		printf("Kisinin Ismi: %s\nKisinin Soyismi: %s\n%Kisinin Numarasi: %d\nKayit Listenin %d. Sirasindadir.\n\n",bulundu->isim,bulundu->soyisim,bulundu->num,sayac);
	}
	anamenu();
}

void silme(){
	int silnum;
	kayit *bironceki=NULL;
	printf("Silmek Istediginiz kaydin numarasi: "); scanf("%d",&silnum);
	gecici=ilk;
	while(gecici!=NULL){
		if(gecici->num == silnum) break;
		bironceki=gecici;
		gecici=gecici->sonraki;
	}
	if(gecici!=NULL){
			if(gecici==ilk){ //silinecek kay�t ilk kay�tsa
				if(ilk==son){
					ilk=NULL;
					son=NULL;
				}
				else{
					ilk=ilk->sonraki;
				}
		}
		else{
			if(gecici==son){ //silinecek kay�t son kay�tsa
				bironceki->sonraki=NULL;
				son=bironceki;
			}
			else{ //silinecek kay�t aradaki kay�tsa
				bironceki->sonraki=gecici->sonraki;
			}
		}
		free(gecici);
		kayitsayisi--;
		printf("Kayit Basariyla Silindi.\n");
	}
	else{
		printf("Aranan Kayit Bulunamadi.\n");
	}
	anamenu();
}

void tasima(int a,int b){
	kayit *bironceki=NULL,*gecici2=NULL,*bironceki2=NULL;
	gecici=ilk;
	gecici2=ilk; 
	while(gecici!=NULL){
		if(gecici->num==a) break;
		bironceki=gecici;
		gecici=gecici->sonraki;
	}
	if(gecici!=NULL){
		if(gecici==ilk){ //ta��ancak kay�t ilk kay�tsa
			if(gecici==son){
				printf("Tek Kayit Yer Degistiremez.\n");
			}
			else{
				if(b!=kayitsayisi){ //ta��nacak yer son s�re de�ilse
					for(int i=0;i<b;i++){
					bironceki2=gecici2;
					gecici2=gecici2->sonraki;
					}
					ilk=ilk->sonraki;
					bironceki2->sonraki=gecici;
					gecici->sonraki=gecici2;
				}
				else{ //ta��nacak yer son s�ra ise
					ilk=ilk->sonraki;
					son->sonraki=gecici;
					son=gecici;
					son->sonraki=NULL;
				}
			}
		}
		else{
			if(gecici==son){ //ta��nacak kay�t son kay�tsa
				if(b==1){ //ta��nacak yer 1. s�ra ise
					gecici->sonraki=ilk;
					ilk=gecici;
				}
				else{
					for(int i=0;i<b-1;i++){
					bironceki2=gecici2;
					gecici2=gecici2->sonraki;
					}
					bironceki2->sonraki=gecici;
					gecici->sonraki=gecici2;
				}
				bironceki->sonraki=NULL; //geciciyi sondan kald�rma
				son=bironceki;
			}
			else{ //ta��nacak kay�t aradaki kay�tsa
				if(b==1){ //ta��nacak yer 1. s�ra ise
					bironceki->sonraki=gecici->sonraki; //geciciyi aradan kald�rma
					gecici->sonraki=ilk;
					ilk=gecici;
				}
				else if(b==kayitsayisi){ //ta��nacak yer son s�ra ise
					bironceki->sonraki=gecici->sonraki; //geciciyi aradan kald�rma
					//geciciyi sona ekleme
					son->sonraki=gecici;
					son=gecici;
					son->sonraki=NULL;
				}
				else{	// ta��nacak yer arada ise
					bironceki->sonraki=gecici->sonraki; //geciciyi aradan kald�rma
				
					for(int i=0;i<b-1;i++){
					bironceki2=gecici2;
					gecici2=gecici2->sonraki;
					}
					//geciciyi istenilen s�raya koyma
					bironceki2->sonraki=gecici;
					gecici->sonraki=gecici2;
				}
			}
		}
	}
	anamenu();
}

int main(){
	okuma();
	anamenu();
}
