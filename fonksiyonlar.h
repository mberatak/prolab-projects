#ifndef FONKSIYONLAR_H
#define FONKSIYONLAR_H
#include  <stdio.h>
#include <string.h>
#include <stdlib.h>


 typedef struct // unit_types.json icin
{
     int saldiri;
    int savunma;
    int saglik;
    int kritik_sans;
} birim;

typedef struct // insan imp unit_types.json icin
{
    birim piyadeler;
    birim okcular;
    birim suvariler;
    birim kusatma_makineleri;
} insanimp_birim;

typedef struct // orklar unit_types.json icin
{
    birim ork_dovusculeri;
    birim mizrakcilar;
    birim varg_binicileri;
    birim troller;
} orklar_birim;

typedef struct // unit_types genel
{
    insanimp_birim insanlar;
    orklar_birim orklar;
} birim_genel;


void degerayir(char* satir, char* neyindegeri, char* deger)
{
     if (satir[0] == '{' || satir[0] == '}') return; // eger bos bir kumeyse atla

   
    char* start = strchr(satir, '\"'); // " icin
    if (start) {
        start++; 
        char* end = strchr(start, '\"');
        if (end) {
            strncpy(neyindegeri, start, end - start);
            neyindegeri[end - start] = '\0'; 
        }
    }

   
    char* value_start = strchr(satir, ':'); // : key olarak almak icin
    if (value_start) {
        value_start++; 
        while (*value_start == ' ') value_start++; 

        
        if (*value_start == '{' || *value_start == '"') value_start++;

        
        char* value_end = value_start; 
        while (*value_end != '\0' && *value_end != '}' && *value_end != '\"') {
            value_end++;
        }
        if (value_end > value_start) {
            strncpy(deger, value_start, value_end - value_start);
            deger[value_end - value_start] = '\0'; // sona null karakter ekle
        }
    }



}

typedef struct // research.json icin
{
   int deger;
   char aciklama[200];
}research;

typedef struct // research.json seviye
{
   research seviye_1;
   research seviye_2;
   research seviye_3;
}research_seviye;

typedef struct // research.json arastirma turleri
{
   research_seviye savunma_ustaligi;
   research_seviye saldiri_gelistirmesi;
   research_seviye elit_egitim;
   research_seviye kusatma_ustaligi;
}research_turleri;



typedef struct // heroes.json icin
{
   char bonus_turu[100];
   int bonus_degeri;
   char aciklama[200];
}heroes;

typedef struct // insanimp kahramanlar heroes.json icin
{
   heroes Alparslan;
   heroes Fatih_Sultan_Mehmet;
   heroes Mete_Han;
   heroes Yavuz_Sultan_Selim;
   heroes Tugrul_Bey;
}heroes_insanlar;

typedef struct //orklar kahrhamanlar  icin heroes.jsondaki
{
   heroes Goruk_Vahsi;
   heroes Thruk_Kemikkiran;
   heroes Vrog_Kafakiran;
   heroes Ugur_Zalim;
}heroes_orklar;

typedef struct // kahramanlar genel
{
   heroes_insanlar insanlar;
   heroes_orklar orklar;
   }heroes_genel;

typedef struct // creatures.json icin
{
   char isim[100];
   int etki_degeri;
   char etki_turu[100];
   char aciklama[200];
}creatures;

typedef struct  //insanimp creatures.json icin
{
   creatures Ejderha;
   creatures Agri_Dagi_Devleri;
   creatures Tepegoz;
   creatures Karakurt;
   creatures Samur;

}insanimp_creatures;

typedef struct // orklar creatures.json icin
{
   creatures Kara_Troll;
   creatures Golge_Kurtlari;
   creatures Camur_Devleri;
   creatures Ates_Iblisi;
   creatures Makrog_Savas_Beyi;
   creatures Buz_Devleri;
}orklar_creatures;

typedef struct // creatures genenl
{
   insanimp_creatures insanlar;
   orklar_creatures orklar;}
   creatures_genel;

void deger_ata_research(research* research, FILE* dosya)
{
   char satir[300];
   char neyindegeri[100], deger[100];
   fseek(dosya, 0, SEEK_SET);
   while(fgets(satir,sizeof(satir),dosya))
   {

      degerayir(satir,neyindegeri,deger);
      if(strcmp(neyindegeri,"deger")==0)
      {
         research->deger=atoi(deger);

      }
      else if(strcmp(neyindegeri,"aciklama")==0)
      {
         strcpy(research->aciklama,deger);
      }

   }
}

void deger_ata_heroes(heroes* kahramanlar, FILE* dosya) // kahramanlarin degerini atama
{
   char satir[300];
   char neyindegeri[100], deger[100];
   fseek(dosya, 0, SEEK_SET);
   while(fgets(satir,sizeof(satir),dosya))
   {
      degerayir(satir,neyindegeri,deger);
      if(strcmp(neyindegeri,"bonus_turu")==0)
      {
          printf("deneme");
         strcpy(kahramanlar->bonus_turu,deger);
      }
      else if(strcmp(neyindegeri,"bonus_degeri")==0)
      {
         kahramanlar->bonus_degeri=atoi(deger);
      }
      else if(strcmp(neyindegeri,"aciklama")==0)
      {
         strcpy(kahramanlar->aciklama,deger);
      }
}
   }

typedef struct 

{
   int birimSayisi;
   int saldiriGucu;
   int savunmaGucu;
   int saglik;
   float kritikSans;

}unit;


void deger_ata_creatures(creatures* creatures, FILE* dosya) // creatures deger atama
{
   char satir[300];
   char neyindegeri[100], deger[100];
   fseek(dosya,0,SEEK_SET);
   while(fgets(satir,sizeof(satir),dosya))
   {
      degerayir(satir,neyindegeri,deger);
      if(strcmp(neyindegeri,"etki_degeri")==0)
      {
         creatures->etki_degeri=atoi(deger);

      }
      else if(strcmp(neyindegeri,"etki_turu")==0)
      {
         strcpy(creatures->etki_turu,deger);
      }
      else if(strcmp(neyindegeri,"aciklama")==0)
      {
         strcpy(creatures->aciklama,deger);
      }
}
}



        void deger_ata_unit_types(birim *birim, FILE* dosya)
{
   char satir[300];
   char neyindegeri[100], deger[100];
   fseek(dosya, 0, SEEK_SET);
   while(fgets(satir,sizeof(satir),dosya))
   {
      degerayir(satir,neyindegeri,deger);
      if(strcmp(neyindegeri,"saldiri")==0)
      {

         birim->saldiri=atoi(deger);

      }
      else if(strcmp(neyindegeri,"savunma")==0)
      {

         birim->savunma=atoi(deger);
      }
      else if(strcmp(neyindegeri,"saglik")==0)
      {
         birim->saglik=atoi(deger);
      }
      else if(strcmp(neyindegeri,"kritik_sans")==0)
      {
         birim->kritik_sans=atoi(deger);
      }
}
}


void bosluk_sil(char* dizi)
{
    int i = 0, j = 0;
    int tirnak_acik = 0; 

    while (dizi[i] != '\0')
    {
        if (dizi[i] == '"')  
        {
            tirnak_acik = !tirnak_acik; 
            dizi[j++] = dizi[i]; 
        }
        else if (tirnak_acik || dizi[i] != ' ')
        {
            
            dizi[j++] = dizi[i];
        }
        i++;
    }
    dizi[j] = '\0';  
}

#endif // FONKSIYONLAR_H