#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <unistd.h>

int determinant(int koseS , int koordinat[][2]) {
    
	int det = 0;

    for (int i = 0; i < koseS; ++i) {
        int x1 = koordinat[i][0], y1 = koordinat[i][1];
        int x2 = koordinat[(i + 1) % koseS][0], y2 = koordinat[(i + 1) % koseS][1];

        det += (x1 * y2 - x2 * y1);
    }

    return abs(det) / 2;
}

int main() {
    
    const char *url = "http://bilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt";		// URL'yi belirle

    system("curl -s -o prolab1.txt http://bilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt"); 		// curl komutu ile veriyi çek

    FILE *dosya = fopen("prolab1.txt", "r"); 	// Dosyayı aç
    if (dosya == NULL) 
	{
        perror("Dosya açılamadı");
        return 1;
    }
	
	int istenenSatir;
    printf("Lutfen cizmek istediginiz satiri giriniz: ");
    scanf("%d", &istenenSatir);
    /*
    int sondajMaliyet;
    printf("Birim sondaj maliyetini giriniz: ");
    scanf("%d", &sondajMaliyet);
    
    int platformMaliyet;
    printf("Birim platform maliyetini giriniz: ");
    scanf("%d", &platformMaliyet);
	*/
	sleep(1);
	
    char satir[100];
    int satirSayisi = 1;

    // Belirtilen satıra kadar döngü
    while (fgets(satir, sizeof(satir), dosya) != NULL && satirSayisi < istenenSatir) 
	{
        satirSayisi++;
    }

    // Eğer istenen satır mevcutsa, ekrana yazdır
    if (satirSayisi == istenenSatir) 
	{
        printf("Okunan Satir %d: %s", istenenSatir, satir);
    } 
	else 
	{
        printf("Belirtilen satir bulunamadi.\n");
        return 1;
    }
    
    int koseSayisi = 0;
    char *virgulSayisi = strchr(satir, ',');
	
	while (virgulSayisi != NULL)		//Koordinat sayısını bulan döngü
	{
	    koseSayisi++;
	    virgulSayisi = strchr(virgulSayisi + 1, ','); 
	}
	
	printf("\nKose: %d\n",koseSayisi);
	
	int koordinat[koseSayisi][2]; 	// Koordinatları tutacak dizi
	
    // Satırdaki koordinatları diziye kaydet
    int i = -1;
    char *joker = strtok(satir, "()");
    while ((joker != NULL) && (i<koseSayisi)) 
	{
        sscanf(joker, "%d,%d", &koordinat[i][0], &koordinat[i][1]);
        i++;
        joker = strtok(NULL, "()");
    }
	
	int sekiller[4];
	sekiller[0] = 0;
	int sekilSayisi = 0;
	int temp = 0;
	int k = 1;
	for (i = 1 ; i <koseSayisi ; i++)
	{
		if ( (koordinat[temp][0] == koordinat[i][0]) && (koordinat[temp][1] == koordinat[i][1]))
		{
			sekilSayisi++;
			temp = i+1;
			sekiller[k] = temp;
			k++;
			i++;		
		}	
	}
	
	printf("Sekil: %d \n",sekilSayisi);
    // Koordinatları ekrana yazdır
    int j ;
    for (j = 0; j < koseSayisi; j++) 
	{
        printf("%d, %d\n", koordinat[j][0], koordinat[j][1]);
    }

    fclose(dosya);		// Dosyayı kapat
    
    int alan = determinant(koseSayisi , koordinat);
    printf("Hesaplanan kaynak rezerv degeri: %d\n", alan*10);
    
    initwindow(800,600);
	
	 
    int zoom = 10; 	// Çizimi bir oranla büyüt
 
    for (j = 0; j < i; j++) 
	{
        koordinat[j][0] *= zoom;
        koordinat[j][1] *= zoom;
    }
    setbkcolor(11);
    cleardevice();
	setcolor(0);
    
    for (i=0;i<=600;i+=10)
	{
		setlinestyle(5,0,1);
		line(0,i,800,i);
	}
	
	for (i=0;i<=800;i+=10)
	{
		setlinestyle(5,0,1);
		line(i,0,i,600);
	}
	
	
	setlinestyle(0,0,1);
    
    setcolor(4);
 	
	for ( k = 1 ; k <= sekilSayisi ; k++)
	{
		drawpoly(sekiller[k]-sekiller[k-1], koordinat[sekiller[k-1]]);
	}
		
    getch();
 	
 	setbkcolor(0);
	cleardevice();
	
    
 	setfillstyle(1,4);
 	
 	for ( k = 1 ; k <= sekilSayisi ; k++)
	{
		fillpoly(sekiller[k]-sekiller[k-1], koordinat[sekiller[k-1]]);
	}
 
 	setcolor(0);
 	
	for (i=0;i<=600;i+=10)
	{
		setlinestyle(5,0,1);
		line(0,i,800,i);
	}
	
	for (i=0;i<=800;i+=10)
	{
		setlinestyle(5,0,1);
		line(i,0,i,600);
	}
	getch();closegraph();return 0; 
//1 . satırın degerrleri: (5,5)(13,12)(8,17)(1,10)(5,5)
//2. satırın degerleri :(20,20)(30,20)(20,40)(10,40)(20,20)(40,22)(50,32)(30,32)(40,22)
}
