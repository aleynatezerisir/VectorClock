#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int head=0;
int tail=0;
struct time
{
int p1;
int p2;
int p3;
}time[5][10];

struct msg
{
int p;
int e;
}msg[5][10];
int array[10][3];
bool isdelivery;
int main()
{
    // n1,n2,n3 proseslerdeki event sayisi.init saatin baslangiç artisi.run while döngüsü için kullanilir,menü ekranini devamli ekranda tutmaya yarar.
    //ps,pr sirasiyla gönderici ve alici prosesdir.s,r gönderilen ve alýnan mesaj sayisi.flag kuyrukta proses bekleyeceði zaman 1 olur.
	int n1=0,n2=0,n3=0,i,j,d=1,init=0,run=1,choice,ps,pr,s=1,r=1,rep=1,sev=1,flag=0;
	char kuyruk[20];
	system("cls");

    int choicemenu;
    char message[20];
	printf("\nPlease enter current process: ");
	scanf("%d",&ps);

	while(run){
    printf("\n1.Send new message m.\n");
    printf("2.Receive message m from process i.\n");
    scanf("%d",&choicemenu);
    if(choicemenu==1){
        printf("Please enter message: ");
        scanf("%s",&message);//gönderilecek mesaji içerir.
        printf("%s",message);
    if(ps==1){ //ilk secenek secilmistir.
            int i,j;
        time[0][0].p1+=init+d;//gönderen prosese timestamp ekler.
        printf("Message sends P%d to all nodes timestamp is:[%d %d %d]",ps,time[0][n1].p1,time[1][n1].p2,time[2][n1].p3);
        n1++;
        }
        else if(ps==2){
        time[1][0].p2+=init+d;

        printf("Message sends P%d to all nodes timestamp is:[%d %d %d]",ps,time[0][n2].p1,	time[1][n2].p2,time[2][n2].p3);

        n2++;
        }
       else if(ps==3){
            	time[2][0].p3+=init+d;

        printf("Message sends P%d to all nodes timestamp is:[%d %d %d] ",ps,time[0][n3].p1,	time[1][n3].p2,time[2][n3].p3);
        n3++;
        }
    }

else if(choicemenu==2){
    printf("\nPlease enter message: ");
    scanf("%s",message);
    printf("\nPlease enter who sent the message: ");
    scanf("%d",&pr);
    printf("\nPlease enter timestamp(Birer bosluk ile yaziniz.(1 0 0)gibi): ");
    for(i=0;i<10;i++)
	{
    //ilk 10 event ve prosesi icini -1 ile doldurur ve alici proses oldugunda arttirarak islem yapar.
	 msg[0][i].p=-1;
	 msg[0][i].e=-1;
	 msg[1][i].p=-1;
	 msg[1][i].e=-1;
	 msg[2][i].p=-1;
	 msg[2][i].e=-1;
	}
	//girilen input lara gore gonderici ve alici prosese timestamp ekler.
	if(ps==1 && pr==2){
	time[0][0].p1=init+d;
	time[1][0].p2=init+d;
	}
	else if(ps==1 && pr==3){
    time[0][0].p1=init+d;
	time[2][0].p3=init+d;
	}
	else if(ps==2 && pr==1){
        time[0][0].p1=init+d;
	time[1][0].p2=init+d;
	}
    else if(ps==2 && pr==3){
        time[1][0].p2=init+d;
	time[2][0].p3=init+d;
	}
	else if(ps==3 && pr==1){
          time[0][0].p1=init+d;
        time[2][0].p3=init+d;
	}
	else if(ps==3 && pr==2){
          time[1][0].p2=init+d;
        time[2][0].p3=init+d;
	}
	//event sayisi kadar ilerler ve her eventa timestamp degerini atar.
	for(i=1;i<n1;i++)
	{
	time[0][i].p1=time[0][i-1].p1+d;
	time[0][i].p2=0;
	time[0][i].p3=0;
	}
	for(i=1;i<n2;i++)
	{
	time[1][i].p1=0;
	time[1][i].p2=time[1][i-1].p2+d;
	time[1][i].p3=0;
	}
	for(i=1;i<n3;i++)
	{
	time[2][i].p1=0;
	time[2][i].p2=0;
	time[2][i].p3=time[2][i-1].p3+d;
	}
    if(ps==1){ // gonderen process 1 ise
        int i,j,temp,k,l;
        s++;//gonderen proses sayısı artar
		 r++;//alıcı proses sayisi artar.
		 // pr 1 deb başliyor.msg arrayi 0 dan basliyor bunu 0 a ingirdemek icin pr den 1 cikartiyoruz.
		 msg[pr-1][r-1].p=ps-1;
		 msg[pr-1][r-1].e=s-1;
        scanf("%d %d %d",&time[0][n1].p1,&time[0][n2].p2,&time[0][n3].p3);//kullanicidan timestamp istenir.Console dan girerken bosluklu girilmesi gerekir.

        printf("%s Message receive %d to %d.timestamp is:[ %d %d %d ] ",message,pr,ps,time[0][n1].p1,time[0][n2].p2,time[0][n3].p3);//evetin timestmpi gönderildi.
        //eventin gonderilmesine ragmen gonderen notun timestampi ile vector saatini karsilastirarak delivery olup olmadigini kontrol eder.
        //eger if kosulu saglanirsa mesaj delivery olmaz ve flag bir olur.Ayni zamanda 2 boyutlu olusturulan kuyruga eklenir ve orada delivey olmasi icin
        //sirasini bekler.
        if(time[0][n1].p1>=time[pr-1][n1].p1 && time[0][n1].p2>=time[pr-1][n1].p2 && time[0][n1].p3 >=time[pr-1][n1].p1 ){
                flag=1;
                array[0][0]=time[0][n1].p1;
                array[0][1]=time[1][n1].p2;
                array[0][2]=time[2][n1].p3;
        printf("\nMessage is no delivery added queue");
        //kuyruk kendi icinde siralanir.
        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
             temp=array[i][j];
              l=j+1;

        for(k=i; k<3; k++){
            while(l<3){
                if(temp<array[k][l]){
                    temp=array[k][l];
                    array[k][l]=array[i][j];
                    array[i][j]=temp;
                }
            l++;
            }
        l=0;
        }}}

        }
        //kosula girmeyen mesaj var ise mesaj delivery olur ve buraya girer.
        else{
        printf("\n%s Message is delivered timestamp is: [%d %d %d] ",time[0][n1].p1,time[0][n2].p2,time[0][n3].p3);//delivery olan mesajin time stampi yazilir.
        //eger flag 1 ise yani kuyrukta bekleyen mesaj var ise mesajı delivery eder.
        if(flag==1){
                if(pr==2)//onceki mesajın gondereni sorulur.sonra kuyrukta bekleyen mesajin time stampi basilir.
            printf("\nBefore Message is delivered timestamp is: [%d %d %d] ",time[pr-1][n1].p2,time[2][n1].p2,array[0][2]);
            else if(pr==3)//onceki mesajın gondereni sorulur.sonra kuyrukta bekleyen mesajin time stampi basilir.
            printf("\nBefore Message is delivered timestamp is: [%d %d %d] ",time[pr-1][n1].p3,time[2][n1].p3,array[0][2]);

        }
        }
    }
    else if(ps==2){
            //yukaridaki islemler eger gonderici 2. prosese gore yapilir.
        int i,j,temp,k,l;

             s++;
		 r++;
		 msg[pr-1][r-1].p=ps-1;
		 msg[pr-1][r-1].e=s-1;
		 //kullanicidan timestamp istenir.Console dan girerken bosluklu girilmesi gerekir.
        scanf("%d %d %d",&time[1][n1].p1,&time[1][n2].p2,&time[1][n3].p3);
        printf("%s Message receive %d to %d.timestamp is:[ %d %d %d ] ",message,pr,ps,time[1][n1].p1,time[1][n2].p2,time[1][n3].p3);
        if(time[1][n1].p1>=time[pr-1][n1].p1 && time[1][n1].p2>=time[pr-1][n1].p2 && time[1][n1].p3 >=time[pr-1][n1].p1 ){
                flag=1;
                array[1][0]=time[0][n1].p1;
                array[1][1]=time[1][n1].p2;
                array[1][2]=time[2][n1].p3;
                        printf("\nMessage is no delivery added queue");

        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
             temp=array[i][j];
              l=j+1;
            }
        for(k=i; k<3; k++){
            while(l<3){
                if(temp<array[k][l]){
                    temp=array[k][l];
                    array[k][l]=array[i][j];
                    array[i][j]=temp;
                }
            l++;
            }
        l=0;
        }
        }

        }
        else{
        printf("\n%s Message is delivered timestamp is: [%d %d %d] ",message,time[1][n1].p1,time[1][n2].p2,time[1][n3].p3);
        if(flag==1){
                if(pr==1)
            printf("\nBefore Message is delivered timestamp is: [%d %d %d] ",time[pr-1][n1].p1,time[2][n1].p1,array[0][2]);
            else if(pr==3)
            printf("\nBefore Message is delivered timestamp is: [%d %d %d] ",time[pr-1][n1].p3,time[2][n1].p3,array[0][2]);

        }}
    }
    else if(ps==3){
            //yukaridaki islemler eger gonderici 2. prosese gore yapilir.
        int i,j,temp,k,l;
        s++;
		 r++;
		 msg[pr-1][r-1].p=ps-1;
		 msg[pr-1][r-1].e=s-1;
        scanf("%d %d %d",&time[2][n1].p1,&time[2][n2].p2,&time[2][n3].p3);

        printf("\n%s Message receive %d to %d.timestamp is:[ %d %d %d ] ",message,pr,ps,time[2][n1].p1,time[2][n2].p2,time[2][n3].p3);
        if(time[2][n1].p1>=time[pr-1][n1].p1 && time[2][n1].p2>=time[pr-1][n1].p2 && time[2][n1].p3 >=time[pr-1][n1].p1){
                flag=1;
                array[2][0]=time[0][n1].p1;
                array[2][1]=time[1][n1].p2;
                array[2][2]=time[2][n1].p3;
                        printf("\nMessage is no delivery added queue");

         for(i=0; i<3; i++){
            for(j=0; j<3; j++){
             temp=array[i][j];
              l=j+1;
            }
        for(k=i; k<3; k++){
            while(l<3){
                if(temp<array[k][l]){
                    temp=array[k][l];
                    array[k][l]=array[i][j];
                    array[i][j]=temp;
                }
            l++;
            }
        l=0;
        }
        }

        }

        else{
        printf("\n%s Message is delivered timestamp is: [%d %d %d] ",message,time[2][n1].p1,time[2][n2].p2,time[2][n3].p3);
        if(flag==1){
            if(pr==1)
            printf("\nBefore Message is delivered timestamp is: [%d %d %d] ",time[pr-1][n1].p1,time[2][n1].p1,array[0][2]);
            else if(pr==2)
            printf("\nBefore Message is delivered timestamp is: [%d %d %d] ",time[pr-1][n1].p2,time[2][n1].p2,array[0][2]);

        }}
        }
    }

	}
	//yukarida belirlenen degerlerin vector saatini hesaplar ve Ram'e yazar.Kullanilmak üzere hafizada kaydedilir.istenirse tüm proseslerin timestampine bakilabilir.
    RAM:
	if(sev==2)
	{
	rep=2;
	}
	for(i=0;i<n1;i++)
	{
	if((msg[0][i].p!=-1)&&(msg[0][i].e!=-1))
	{
	if((time[msg[0][i].p][msg[0][i].e].p1)>time[0][i].p1)
	  {
	  time[0][i].p1=time[msg[0][i].p][msg[0][i].e].p1;
	  for(j=i+1;j<n1;j++)
	  {
	   time[0][j].p1=time[0][j].p1+time[0][i].p1;
	  }
	  }
	if((time[msg[0][i].p][msg[0][i].e].p2)>time[0][i].p2)
	{
	  time[0][i].p2=time[msg[0][i].p][msg[0][i].e].p2;
	  for(j=i+1;j<n1;j++)
	  {
	   time[0][j].p2=time[0][j].p2+time[0][i].p2;
	  }
	}
	if((time[msg[0][i].p][msg[0][i].e].p3)>time[0][i].p3)
	{
	  time[0][i].p3=time[msg[0][i].p][msg[0][i].e].p3;
	  for(j=i+1;j<n1;j++)
	  {
	   time[0][j].p3=time[0][j].p3+time[0][i].p3;
	  }
	}
	}
	}
	for(i=0;i<n2;i++)
	{
	if((msg[1][i].p!=-1)&&(msg[1][i].e!=-1))
	{
	if((time[msg[1][i].p][msg[1][i].e].p2+d)>time[1][i].p2)
	{
	  time[1][i].p2=time[msg[1][i].p][msg[1][i].e].p2+d;
	  for(j=i+1;j<n2;j++)
	  {
	   time[1][j].p2=time[1][j].p2+time[1][i].p2;
	  }
	}
	if((time[msg[1][i].p][msg[1][i].e].p1)>time[1][i].p1)
	{
	  time[1][i].p1=time[msg[1][i].p][msg[1][i].e].p1;
	  for(j=i+1;j<n2;j++)
	  {
	   time[1][j].p1=time[1][j].p1+time[1][i].p1;
	  }
	}
	if((time[msg[1][i].p][msg[1][i].e].p3)>time[1][i].p3)
	{
	  time[1][i].p3=time[msg[1][i].p][msg[1][i].e].p3;
	  for(j=i+1;j<n2;j++)
	  {
	   time[1][j].p3=time[1][j].p3+time[1][i].p3;
	  }
	}
	}
	}
	for(i=0;i<n3;i++)
	{
	if((msg[2][i].p!=-1)&&(msg[2][i].e!=-1))
	{
	if((time[msg[2][i].p][msg[2][i].e].p1)>time[2][i].p1)
	{
	  time[2][i].p1=time[msg[2][i].p][msg[2][i].e].p1;
	  for(j=i+1;j<n3;j++)
	  {
	   time[2][j].p1=time[2][j].p1+time[2][i].p1;
	  }
	}
	if((time[msg[2][i].p][msg[2][i].e].p2)>time[2][i].p2)
	{
	  time[2][i].p2=time[msg[2][i].p][msg[2][i].e].p2;
	  for(j=i+1;j<n3;j++)
	  {
	   time[2][j].p2=time[2][j].p2+time[2][i].p2;
	  }
	}
	if((time[msg[2][i].p][msg[2][i].e].p3)>time[2][i].p3)
	{
	  time[2][i].p3=time[msg[2][i].p][msg[2][i].e].p3;
	  for(j=i+1;j<n3;j++)
	  {
	   time[2][j].p3=time[2][j].p3+time[2][i].p3;
	  }
	}
	}
	if(rep==1)
	{
	sev=2;
	goto RAM;
	}
	}

}

