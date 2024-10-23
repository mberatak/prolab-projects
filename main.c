#include <stdio.h>
#include <string.h>
#include <stdlib.h>




    typedef struct // unit_types.json icin
{
     int saldiri;
    int savunma;
    int saglik;
    float kritik_sans;
 }birim;

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
     if (satir[0] == '{' || satir[0] == '}') return;

    // { veya " karakterleri arasında kalan değerleri al
    char* start = strchr(satir, '\"');
    if (start) {
        start++; // İlk " karakterinden sonrası
        char* end = strchr(start, '\"');
        if (end) {
            strncpy(neyindegeri, start, end - start);
            neyindegeri[end - start] = '\0'; // Null terminator ekle
        }
    }
    char* value_start = strchr(satir, ':');
    if (value_start) {
        value_start++; // ":" karakterinden sonrası
        while (*value_start == ' ') value_start++; // Boşlukları atla

        // Değerin başındaki { veya " karakterlerini atla
        if (*value_start == '{' || *value_start == '"') value_start++;

        // Değerin sonundaki } veya " karakterlerini temizle
        char* value_end = value_start;
        while (*value_end != '\0' && *value_end != '}' && *value_end != '\"') {
            value_end++;
        }
        if (value_end > value_start) {
            strncpy(deger, value_start, value_end - value_start);
            deger[value_end - value_start] = '\0'; // Null terminator ekle
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
   creatures Agri_Dagi_Devleri; // 
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

typedef struct
{
   research_turleri research_turleri;
   heroes_genel heroes_genel;
   creatures_genel creatures_genel;

}bonuslar;


void bosluk_sil(char* dizi)
{
    int i = 0, j = 0;
    int tirnak_acik = 0; // Çift tırnakların açık olup olmadığını takip eden bayrak

    while (dizi[i] != '\0')
    {
        if (dizi[i] == '"')  // Eğer çift tırnaksa durumu değiştir
        {
            tirnak_acik = !tirnak_acik;  // tirnak_acik bayrağını tersine çevir (1->0, 0->1)
            dizi[j++] = dizi[i]; // Çift tırnağı kaydedelim
        }
        else if (tirnak_acik || dizi[i] != ' ')
        {
            // Eğer tırnakların içindeysek ya da boşluk değilse karakteri kopyala
            dizi[j++] = dizi[i];
        }
        i++;
    }
    dizi[j] = '\0';  // Sonuna null karakter ekleyelim
}



void deger_ata_heroes(heroes* kahramanlar, FILE* dosya) // kahramanlarin degerini atama
{
   char satir[300];
   char neyindegeri[100], deger[100];
 
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


void deger_ata_creatures(creatures* creatures, FILE* dosya) // creatures deger atama
{
   char satir[300];
   char neyindegeri[100], deger[100];

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



void deger_ata_unit_types(birim *birim, FILE* dosya){
   char satir[300];
   char neyindegeri[100], deger[100];
   while(fgets(satir,sizeof(satir),dosya))
   {
      
      degerayir(satir,neyindegeri,deger);
      if(strcmp(neyindegeri,"saldiri")==0)
      {
         printf("%s  %d ",neyindegeri,atoi(deger));

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





void deger_ata_research(research* research, FILE* dosya)
{
   char satir[300];
   char neyindegeri[100], deger[100];

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

typedef struct{
int savunma_ustaligi1;
int savunma_ustaligi2;
int savunma_ustaligi3;
int saldiri_gelistirmesi1;
int saldiri_gelistirmesi2;
int saldiri_gelistirmesi3;
int elit_egitim1;
int elit_egitim2;
int elit_egitim3;
int kusatma_ustaligi1;
int kusatma_ustaligi2;
int kusatma_ustaligi3;
   
}arastirma_sayi;

typedef struct{
   arastirma_sayi insanlar;
   arastirma_sayi orklar;
}arastirma_tarafi;


typedef struct {
int piyadelers;
int okculars;
int suvarilers;
int kusatma_makineleris;
int fatih_sultan_mehmets;
int alparslans;
int mete_hans;
int yavuz_sultan_selims;
int tugrul_beys;
int ejderhas;
int agri_dagi_devleris;
int tepegozs;
int karakurts;
int samurs;


}insanlar_sayi;

typedef struct{
  int ork_dovusculeris;
  int varg_binicileris;
  int trollers;
  int  mizrakcilars;
  int goruk_vahsis;
  int  thruk_kemikkirans;
  int vrog_kafa_kirans;
  int ugur_zalims;
  int kara_trolls;
  int golge_kurtlaris;
  int camur_devleris;
  int ates_iblisis;
  int makrog_savas_beyis;
  int buz_devleris;
}orklar_sayi;

typedef struct{
   insanlar_sayi insanlar;
   orklar_sayi orklar;
   }genel_sayi;

void sifirla(genel_sayi *g,arastirma_tarafi *a) {
    g->insanlar.piyadelers = 0;
    g->insanlar.okculars = 0;
    g->insanlar.suvarilers = 0;
    g->insanlar.kusatma_makineleris = 0;
    g->insanlar.fatih_sultan_mehmets = 0;
    g->insanlar.alparslans = 0;
    g->insanlar.mete_hans = 0;
    g->insanlar.yavuz_sultan_selims = 0;
    g->insanlar.tugrul_beys = 0;
    g->insanlar.ejderhas = 0;
    g->insanlar.agri_dagi_devleris = 0;
    g->insanlar.tepegozs = 0;
    g->insanlar.karakurts = 0;
    g->insanlar.samurs = 0;
    a->insanlar.saldiri_gelistirmesi1 = 0;
   a->insanlar.saldiri_gelistirmesi2 = 0;
   a->insanlar.saldiri_gelistirmesi3 = 0;
   a->insanlar.savunma_ustaligi1 = 0;
   a->insanlar.savunma_ustaligi2 = 0;
   a->insanlar.savunma_ustaligi3 = 0;
   a->insanlar.elit_egitim1 = 0;
   a->insanlar.elit_egitim2 = 0;
   a->insanlar.elit_egitim3 = 0;
   a->insanlar.kusatma_ustaligi1 = 0;
   a->insanlar.kusatma_ustaligi2 = 0;
   a->insanlar.kusatma_ustaligi3 = 0;

 
    g->orklar.ork_dovusculeris = 0;
    g->orklar.varg_binicileris = 0;
    g->orklar.trollers = 0;
    g->orklar.mizrakcilars = 0;
    g->orklar.goruk_vahsis = 0;
    g->orklar.thruk_kemikkirans = 0;
    g->orklar.vrog_kafa_kirans = 0;
    g->orklar.ugur_zalims = 0;
    g->orklar.kara_trolls = 0;
    g->orklar.golge_kurtlaris = 0;
    g->orklar.camur_devleris = 0;
    g->orklar.ates_iblisis = 0;
    g->orklar.makrog_savas_beyis = 0;
    g->orklar.buz_devleris = 0;
      a->orklar.saldiri_gelistirmesi1 = 0;
   a->orklar.saldiri_gelistirmesi2 = 0;
   a->orklar.saldiri_gelistirmesi3 = 0;
   a->orklar.savunma_ustaligi1 = 0;
   a->orklar.savunma_ustaligi2 = 0;
   a->orklar.savunma_ustaligi3 = 0;
   a->orklar.elit_egitim1 = 0;
   a->orklar.elit_egitim2 = 0;
   a->orklar.elit_egitim3 = 0;
   a->orklar.kusatma_ustaligi1 = 0;
   a->orklar.kusatma_ustaligi2 = 0;
   a->orklar.kusatma_ustaligi3 = 0;
   
}

void senaryo_oku(FILE* dosya,genel_sayi* sayi,arastirma_tarafi* arastirma)
{
   char satir[300];
   char neyindegeri[100], deger[100];
   int orkMu = 0;
   int insanMi = 0;
   while(fgets(satir,sizeof(satir),dosya))
   {
      if (strstr(satir, "ork_legi") != NULL) {
            orkMu = 1; 
            insanMi = 0;
        } else if (strstr(satir, "insan_imparatorlugu") != NULL) {
            insanMi = 1;
            orkMu = 0;
        }
       
      degerayir(satir,neyindegeri,deger);

      if(strstr(satir,"saldiri_gelistirmesi")!=NULL)
      {
         if(atoi(deger)==1){
         if(insanMi)
         {
            arastirma->insanlar.saldiri_gelistirmesi1=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.saldiri_gelistirmesi1=1;
            }
         }
         if(atoi(deger)==2){
         if(insanMi)
         {
            arastirma->insanlar.saldiri_gelistirmesi2=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.saldiri_gelistirmesi2=1;
            }
         }
         if(atoi(deger)==3){
         if(insanMi)
         {
            arastirma->insanlar.saldiri_gelistirmesi3=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.saldiri_gelistirmesi3=1;
            }
         }
      }
      if(strstr(satir,"savunma_ustaligi")!=NULL)
      {
         if(atoi(deger)==1){
         if(insanMi)
         {
            arastirma->insanlar.savunma_ustaligi1=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.savunma_ustaligi1=1;
            }
         }
         if(atoi(deger)==2){
         if(insanMi)
         {
            arastirma->insanlar.savunma_ustaligi2=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.savunma_ustaligi2=1;
            }
         }
         if(atoi(deger)==3){
         if(insanMi)
         {
            printf("deneme");
            arastirma->insanlar.savunma_ustaligi3=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.savunma_ustaligi3=1;
            }
         }
      }
      if(strstr(satir,"elit_egitim")!=NULL)
      {
         
         if(atoi(deger)==1){
         if(insanMi)
         {
            arastirma->insanlar.elit_egitim1=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.elit_egitim1=1;
            }
         }
         if(atoi(deger)==2){
         if(insanMi)
         {
            arastirma->insanlar.elit_egitim2=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.elit_egitim2=1;
            }
         }
         if(atoi(deger)==3){
         if(insanMi)
         {
            arastirma->insanlar.elit_egitim3=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.elit_egitim3=1;
            }
         }
      }
      if(strstr(satir,"kusatma_ustaligi")!=NULL)
      {
         if(atoi(deger)==1){
         if(insanMi)
         {
            arastirma->insanlar.kusatma_ustaligi1=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.kusatma_ustaligi1=1;
            }
         }
         if(atoi(deger)==2){
         if(insanMi)
         {
            arastirma->insanlar.kusatma_ustaligi2=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.kusatma_ustaligi2=1;
            }
         }
         if(atoi(deger)==3){
         if(insanMi)
         {
            arastirma->insanlar.kusatma_ustaligi3=1;
          }
            else if(orkMu)
            {
               arastirma->orklar.kusatma_ustaligi3=1;
            }
         }
      }
         
      if(strstr(satir,"piyade")!=NULL)
      {
         sayi->insanlar.piyadelers=atoi(deger);
      }
      if(strstr(satir,"okcu")!=NULL)
      {
         sayi->insanlar.okculars=atoi(deger);
      }
      if(strstr(satir,"suvariler")!=NULL)
      {
         sayi->insanlar.suvarilers=atoi(deger);
      }
      if(strstr(satir,"kusatma_makineleri")!=NULL)
      {
         sayi->insanlar.kusatma_makineleris=atoi(deger);
      }
      if(strstr(satir,"Fatih_Sultan_Mehmet")!=NULL)
      {
         sayi->insanlar.fatih_sultan_mehmets=1;
      }
      if(strstr(satir,"Alparslan")!=NULL)
      {
         sayi->insanlar.alparslans=1;
      }
      if(strstr(satir,"Mete_Han")!=NULL)
      {
         sayi->insanlar.mete_hans=1;
      }
      if(strstr(satir,"Yavuz_Sultan_Selim")!=NULL)
      {
         sayi->insanlar.yavuz_sultan_selims=1;
      }
      if(strstr(satir,"Tugrul_Bey")!=NULL)
      {
         sayi->insanlar.tugrul_beys=1;
      }
      if(strstr(satir,"Ejderha")!=NULL)
      {
         sayi->insanlar.ejderhas=1;
      }
      if(strstr(satir,"Agri_Dagi_Devi")!=NULL)
      {
         sayi->insanlar.agri_dagi_devleris=1;
      }
      if(strstr(satir,"Tepegoz")!=NULL)
      {
         sayi->insanlar.tepegozs=1;
      }
      if(strstr(satir,"Karakurt")!=NULL)
      {
         sayi->insanlar.karakurts=1;
      }
      if(strstr(satir,"Samur")!=NULL)
      {
         sayi->insanlar.samurs=1;
      }
      if(strstr(satir,"ork_dovusculeri")!=NULL)
      {
         sayi->orklar.ork_dovusculeris=atoi(deger);
      }
      if(strstr(satir,"varg_binicileri")!=NULL)
      {
         sayi->orklar.varg_binicileris=atoi(deger);
      }
      if(strstr(satir,"troller")!=NULL)
      {
         sayi->orklar.trollers=atoi(deger);
      }
      if(strstr(satir,"mizrakcilar")!=NULL)
      {
         sayi->orklar.mizrakcilars=atoi(deger);
      }
      if(strstr(satir,"Goruk_Vahsi")!=NULL)
      {
         sayi->orklar.goruk_vahsis=1;
      }
      if(strstr(satir,"Thruk_Kemikkiran")!=NULL)
      {
         sayi->orklar.thruk_kemikkirans=1;
      }
      if(strstr(satir,"Vrog_Kafakiran")!=NULL)
      {
         sayi->orklar.vrog_kafa_kirans=1;
      }
      if(strstr(satir,"Ugur_Zalim")!=NULL)
      {
         sayi->orklar.ugur_zalims=1;
      }
      if(strstr(satir,"Kara_Troll")!=NULL)
      {
         sayi->orklar.kara_trolls=1;
      }
      if(strstr(satir,"Golge_Kurtlari")!=NULL)
      {
         sayi->orklar.golge_kurtlaris=1;
      }
      if(strstr(satir,"Camur_Devleri")!=NULL)
      {
         sayi->orklar.camur_devleris=1;
      }
      if(strstr(satir,"Ates_Iblisi")!=NULL)
      {
         sayi->orklar.ates_iblisis=1;
      }
      if(strstr(satir,"Makrog_Savas_Beyi")!=NULL)
      {
         sayi->orklar.makrog_savas_beyis=1;
      }
      if(strstr(satir,"Buz_Devleri")!=NULL)
      {
         sayi->orklar.buz_devleris=1;
      }
      
      
   }

}



void varsayilan_deger(birim_genel* bir)
{
   bir->insanlar.piyadeler.kritik_sans = 5;
   bir->insanlar.okcular.kritik_sans = 5;
   bir->insanlar.suvariler.kritik_sans = 5;
   bir->insanlar.kusatma_makineleri.kritik_sans = 5;
   bir->orklar.ork_dovusculeri.kritik_sans = 5;
   bir->orklar.mizrakcilar.kritik_sans = 5;
   bir->orklar.varg_binicileri.kritik_sans = 5;
   bir->orklar.troller.kritik_sans = 5;
}
void creatures_bonus(genel_sayi* g,birim_genel*b,creatures_genel*c)
{
  if(g->insanlar.ejderhas==1)
  {
     if(g->insanlar.piyadelers>0)
     {
      
      b->insanlar.piyadeler.saldiri+=(b->insanlar.piyadeler.saldiri)*((c->insanlar.Ejderha.etki_degeri)/100.0);
     }
  }
  if(g->insanlar.agri_dagi_devleris==1)
  {
   
     if(g->insanlar.suvarilers>0)
     {
        b->insanlar.suvariler.savunma+=b->insanlar.suvariler.savunma*((c->insanlar.Agri_Dagi_Devleri.etki_degeri)/100.0);
     }
  }
  if(g->insanlar.tepegozs==1)
  {
     if(g->insanlar.okculars>0)
     {
        b->insanlar.okcular.saldiri+=b->insanlar.okcular.saldiri*((c->insanlar.Tepegoz.etki_degeri)/100.0);
     }
  }
  if(g->insanlar.karakurts==1)
  {
     if(g->insanlar.okculars>0)
     {
      
        b->insanlar.okcular.kritik_sans+=(b->insanlar.okcular.kritik_sans)*((c->insanlar.Karakurt.etki_degeri)/100.0);
     }
  }
  if(g->insanlar.samurs==1)
  {
     if(g->insanlar.piyadelers>0)
     {
        b->insanlar.piyadeler.savunma+=b->insanlar.piyadeler.savunma*((c->insanlar.Samur.etki_degeri)/100.0);
     }
  }
   if(g->orklar.kara_trolls==1)
   {
       if(g->orklar.ork_dovusculeris>0)
       {
         b->orklar.troller.saldiri+=b->orklar.troller.saldiri*((c->orklar.Kara_Troll.etki_degeri)/100.0);
       }
   }
   if(g->orklar.golge_kurtlaris==1)
   {
       if(g->orklar.ork_dovusculeris>0)
       {
         b->orklar.varg_binicileri.savunma+=b->orklar.varg_binicileri.savunma*((c->orklar.Golge_Kurtlari.etki_degeri)/100.0);
       }
   }
   if(g->orklar.camur_devleris==1)
   {
       if(g->orklar.trollers>0)
       {
         b->orklar.ork_dovusculeri.savunma+=b->orklar.ork_dovusculeri.savunma*((c->orklar.Camur_Devleri.etki_degeri)/100.0);
       }
   }
   if(g->orklar.ates_iblisis==1)
   {
       if(g->orklar.mizrakcilars>0)
       {
         b->orklar.varg_binicileri.saldiri+=b->orklar.varg_binicileri.saldiri*((c->orklar.Ates_Iblisi.etki_degeri)/100.0);
       }
   }
   if(g->orklar.makrog_savas_beyis==1)
   {
       if(g->orklar.ork_dovusculeris>0)
       {
         b->orklar.troller.savunma+=b->orklar.troller.savunma*((c->orklar.Makrog_Savas_Beyi.etki_degeri)/100.0);
       }
   }
   if(g->orklar.buz_devleris==1)
   {
       if(g->orklar.ork_dovusculeris>0)
       {
         b->orklar.mizrakcilar.savunma+=b->orklar.mizrakcilar.savunma*((c->orklar.Buz_Devleri.etki_degeri)/100.0);
       }
   }


}
void heroes_bonus(genel_sayi* g,birim_genel* b,heroes_genel* h)
{
   if(g->insanlar.alparslans==1)
    {
      if(g->insanlar.piyadelers>0){
      b->insanlar.piyadeler.savunma+=b->insanlar.piyadeler.savunma*((h->insanlar.Alparslan.bonus_degeri)/100.0);}
    }
    if(g->insanlar.fatih_sultan_mehmets==1)
    { if(g->insanlar.kusatma_makineleris>0){
      b->insanlar.kusatma_makineleri.saldiri+=b->insanlar.kusatma_makineleri.saldiri*((h->insanlar.Fatih_Sultan_Mehmet.bonus_degeri)/100.0);
    }
    }
      if(g->insanlar.mete_hans==1)
      { if(g->insanlar.okculars>0){
         b->insanlar.okcular.savunma+=b->insanlar.okcular.savunma*((h->insanlar.Mete_Han.bonus_degeri)/100.0);}
      }
      if(g->insanlar.yavuz_sultan_selims==1)
      {  if(g->insanlar.suvarilers>0){
         b->insanlar.suvariler.kritik_sans+=b->insanlar.suvariler.kritik_sans*((h->insanlar.Yavuz_Sultan_Selim.bonus_degeri)/100.0);
      }
      }
      if(g->insanlar.tugrul_beys==1)
      { if(g->insanlar.okculars>0){
         b->insanlar.okcular.saldiri+=b->insanlar.okcular.saldiri*((h->insanlar.Tugrul_Bey.bonus_degeri)/100.0);
      }
      }
      if(g->orklar.goruk_vahsis==1)
      { if(g->orklar.ork_dovusculeris>0){
         b->orklar.ork_dovusculeri.saldiri+=b->orklar.ork_dovusculeri.saldiri*((h->orklar.Goruk_Vahsi.bonus_degeri)/100.0);
      }}
      if(g->orklar.thruk_kemikkirans==1)
      { if(g->orklar.trollers>0){
         b->orklar.troller.savunma+=b->orklar.troller.savunma*((h->orklar.Thruk_Kemikkiran.bonus_degeri)/100.0);
      }}
      if(g->orklar.vrog_kafa_kirans==1)
      {
         if(g->orklar.varg_binicileris>0){
         b->orklar.varg_binicileri.kritik_sans+=b->orklar.varg_binicileri.kritik_sans*((h->orklar.Vrog_Kafakiran.bonus_degeri)/100.0);
      }}

      if(g->orklar.ugur_zalims==1)
      {
        if(g->orklar.ork_dovusculeris>0){
         b->orklar.ork_dovusculeri.savunma+=b->orklar.ork_dovusculeri.savunma*((h->orklar.Ugur_Zalim.bonus_degeri)/100.0);}
        
        if(g->orklar.mizrakcilars>0){
         b->orklar.mizrakcilar.savunma+=b->orklar.mizrakcilar.savunma*((h->orklar.Ugur_Zalim.bonus_degeri)/100.0);
        }
        
        if(g->orklar.trollers>0){
         b->orklar.troller.savunma+=b->orklar.troller.savunma*((h->orklar.Ugur_Zalim.bonus_degeri)/100.0);
        }
         
         if(g->orklar.varg_binicileris>0){
          b->orklar.varg_binicileri.savunma+=b->orklar.varg_binicileri.savunma*((h->orklar.Ugur_Zalim.bonus_degeri)/100.0);
         }


      }

   
}
void kusatma_ustaligi(arastirma_tarafi* a,genel_sayi*g,birim_genel* bir,research_turleri* research)
{
   if(a->insanlar.kusatma_ustaligi1==1)
   {
      if(g->insanlar.kusatma_makineleris>0)
      {
         bir->insanlar.kusatma_makineleri.saldiri+=bir->insanlar.kusatma_makineleri.saldiri*((research->kusatma_ustaligi.seviye_2.deger)/100.0);
      }
   }
   else if(a->insanlar.kusatma_ustaligi2==1)
   {
      if(g->insanlar.kusatma_makineleris>0)
      {
         bir->insanlar.kusatma_makineleri.saldiri+=bir->insanlar.kusatma_makineleri.saldiri*((research->kusatma_ustaligi.seviye_2.deger)/100.0);
      }
   }
   else if(a->insanlar.kusatma_ustaligi3==1)
   {
      if(g->insanlar.kusatma_makineleris>0)
      {
         bir->insanlar.kusatma_makineleri.saldiri+=bir->insanlar.kusatma_makineleri.saldiri*((research->kusatma_ustaligi.seviye_3.deger)/100.0);
      }
   }
   
}

void saldiri_gelistirmesi (arastirma_tarafi* a, genel_sayi* g, research_turleri* research,birim_genel* bir)
{
  if(a->insanlar.saldiri_gelistirmesi1==1)
  {
   if(g->insanlar.piyadelers>0)
   {
      bir->insanlar.piyadeler.saldiri+=bir->insanlar.piyadeler.saldiri*((research->saldiri_gelistirmesi.seviye_1.deger)/100.0);
   }
   if(g->insanlar.okculars>0)
   {
      bir->insanlar.okcular.saldiri+=bir->insanlar.okcular.saldiri*((research->saldiri_gelistirmesi.seviye_1.deger)/100.0);
   }
   if(g->insanlar.suvarilers>0)
   {
      bir->insanlar.suvariler.saldiri+=bir->insanlar.suvariler.saldiri*((research->saldiri_gelistirmesi.seviye_1.deger)/100.0);
   }
   if(g->insanlar.kusatma_makineleris>0)
   {
      bir->insanlar.kusatma_makineleri.saldiri+=bir->insanlar.kusatma_makineleri.saldiri*((research->saldiri_gelistirmesi.seviye_1.deger)/100.0);
   }
  }
  else if(a->insanlar.saldiri_gelistirmesi2==1)
  {
   if(g->insanlar.piyadelers>0)
   {
      bir->insanlar.piyadeler.saldiri+=bir->insanlar.piyadeler.saldiri*((research->saldiri_gelistirmesi.seviye_2.deger)/100.0);
   }
   if(g->insanlar.okculars>0)
   {
      bir->insanlar.okcular.saldiri+=bir->insanlar.okcular.saldiri*((research->saldiri_gelistirmesi.seviye_2.deger)/100.0);
   }
   if(g->insanlar.suvarilers>0)
   {
      bir->insanlar.suvariler.saldiri+=bir->insanlar.suvariler.saldiri*((research->saldiri_gelistirmesi.seviye_2.deger)/100.0);
   }
   if(g->insanlar.kusatma_makineleris>0)
   {
      bir->insanlar.kusatma_makineleri.saldiri+=bir->insanlar.kusatma_makineleri.saldiri*((research->saldiri_gelistirmesi.seviye_2.deger)/100.0);
   }
  }
  else if(a->insanlar.saldiri_gelistirmesi3==1)
  {
   if(g->insanlar.piyadelers>0)
   {
      bir->insanlar.piyadeler.saldiri+=bir->insanlar.piyadeler.saldiri*((research->saldiri_gelistirmesi.seviye_3.deger)/100.0);
   }
   if(g->insanlar.okculars>0)
   {
      bir->insanlar.okcular.saldiri+=bir->insanlar.okcular.saldiri*((research->saldiri_gelistirmesi.seviye_3.deger)/100.0);
   }
   if(g->insanlar.suvarilers>0)
   {
      bir->insanlar.suvariler.saldiri+=bir->insanlar.suvariler.saldiri*((research->saldiri_gelistirmesi.seviye_3.deger)/100.0);
   }
   if(g->insanlar.kusatma_makineleris>0)
   {
      bir->insanlar.kusatma_makineleri.saldiri+=bir->insanlar.kusatma_makineleri.saldiri*((research->saldiri_gelistirmesi.seviye_3.deger)/100.0);
   }
  }

if(a->orklar.saldiri_gelistirmesi1==1)
{
   if(g->orklar.ork_dovusculeris>0)
   {
      bir->orklar.ork_dovusculeri.saldiri+=bir->orklar.ork_dovusculeri.saldiri*((research->saldiri_gelistirmesi.seviye_1.deger)/100.0);
   }
   if(g->orklar.mizrakcilars>0)
   {
      bir->orklar.mizrakcilar.saldiri+=bir->orklar.mizrakcilar.saldiri*((research->saldiri_gelistirmesi.seviye_1.deger)/100.0);
   }
   if(g->orklar.varg_binicileris>0)
   {
      bir->orklar.varg_binicileri.saldiri+=bir->orklar.varg_binicileri.saldiri*((research->saldiri_gelistirmesi.seviye_1.deger)/100.0);
   }
   if(g->orklar.trollers>0)
   {
      bir->orklar.troller.saldiri+=bir->orklar.troller.saldiri*((research->saldiri_gelistirmesi.seviye_1.deger)/100.0);
   }
}
else if(a->orklar.saldiri_gelistirmesi2==1)
{
   if(g->orklar.ork_dovusculeris>0)
   {
      bir->orklar.ork_dovusculeri.saldiri+=bir->orklar.ork_dovusculeri.saldiri*((research->saldiri_gelistirmesi.seviye_2.deger)/100.0);
   }
   if(g->orklar.mizrakcilars>0)
   {
      bir->orklar.mizrakcilar.saldiri+=bir->orklar.mizrakcilar.saldiri*((research->saldiri_gelistirmesi.seviye_2.deger)/100.0);
   }
   if(g->orklar.varg_binicileris>0)
   {
      bir->orklar.varg_binicileri.saldiri+=bir->orklar.varg_binicileri.saldiri*((research->saldiri_gelistirmesi.seviye_2.deger)/100.0);
   }
   if(g->orklar.trollers>0)
   {
      bir->orklar.troller.saldiri+=bir->orklar.troller.saldiri*((research->saldiri_gelistirmesi.seviye_2.deger)/100.0);
   }
}
else if(a->orklar.saldiri_gelistirmesi3==1)
{
   if(g->orklar.ork_dovusculeris>0)
   {
      bir->orklar.ork_dovusculeri.saldiri+=bir->orklar.ork_dovusculeri.saldiri*((research->saldiri_gelistirmesi.seviye_3.deger)/100.0);
   }
   if(g->orklar.mizrakcilars>0)
   {
      bir->orklar.mizrakcilar.saldiri+=bir->orklar.mizrakcilar.saldiri*((research->saldiri_gelistirmesi.seviye_3.deger)/100.0);
   }
   if(g->orklar.varg_binicileris>0)
   {
      bir->orklar.varg_binicileri.saldiri+=bir->orklar.varg_binicileri.saldiri*((research->saldiri_gelistirmesi.seviye_3.deger)/100.0);
   }
   if(g->orklar.trollers>0)
   {
      bir->orklar.troller.saldiri+=bir->orklar.troller.saldiri*((research->saldiri_gelistirmesi.seviye_3.deger)/100.0);
   }

}
}


void savunma_ustaligi (arastirma_tarafi* a,research_turleri* research,genel_sayi* g,birim_genel* bir)
{ 
   if(a->insanlar.savunma_ustaligi1==1)
   {
      if(g->insanlar.piyadelers>0)
      {
         bir->insanlar.piyadeler.savunma+=bir->insanlar.piyadeler.savunma*((research->savunma_ustaligi.seviye_1.deger)/100.0);
      }
      if (g->insanlar.okculars>0)
      {
         bir->insanlar.okcular.savunma+=bir->insanlar.okcular.savunma*((research->savunma_ustaligi.seviye_1.deger)/100.0);
      }
      if(g->insanlar.suvarilers>0)
      {
         bir->insanlar.suvariler.savunma+=bir->insanlar.suvariler.savunma*((research->savunma_ustaligi.seviye_1.deger)/100.0);
      }
      if(g->insanlar.kusatma_makineleris>0)
      {
         bir->insanlar.kusatma_makineleri.savunma+=bir->insanlar.kusatma_makineleri.savunma*((research->savunma_ustaligi.seviye_1.deger)/100.0);
      }
   }
   else if(a->insanlar.savunma_ustaligi2==1)
   {
      if(g->insanlar.piyadelers>0)
      {
         bir->insanlar.piyadeler.savunma+=bir->insanlar.piyadeler.savunma*((research->savunma_ustaligi.seviye_2.deger)/100.0);
      }
      if(g->insanlar.okculars>0)
      {
         bir->insanlar.okcular.savunma+=bir->insanlar.okcular.savunma*((research->savunma_ustaligi.seviye_2.deger)/100.0);
      }
      if(g->insanlar.suvarilers>0)
      {
         bir->insanlar.suvariler.savunma+=bir->insanlar.suvariler.savunma*((research->savunma_ustaligi.seviye_2.deger)/100.0);
      }
      if(g->insanlar.kusatma_makineleris>0)
      {
         bir->insanlar.kusatma_makineleri.savunma+=bir->insanlar.kusatma_makineleri.savunma*((research->savunma_ustaligi.seviye_2.deger)/100.0);
      }
   }
   else if(a->insanlar.savunma_ustaligi3==1)
   {
      if(g->insanlar.piyadelers>0)
      {
         bir->insanlar.piyadeler.savunma+=bir->insanlar.piyadeler.savunma*((research->savunma_ustaligi.seviye_3.deger)/100.0);
      }
      if(g->insanlar.okculars>0)
      {
         bir->insanlar.okcular.savunma+=bir->insanlar.okcular.savunma*((research->savunma_ustaligi.seviye_3.deger)/100.0);
      }
      if(g->insanlar.suvarilers>0)
      {
         bir->insanlar.suvariler.savunma+=bir->insanlar.suvariler.savunma*((research->savunma_ustaligi.seviye_3.deger)/100.0);
      }
      if(g->insanlar.kusatma_makineleris>0)
      {
         bir->insanlar.kusatma_makineleri.savunma+=bir->insanlar.kusatma_makineleri.savunma*((research->savunma_ustaligi.seviye_3.deger)/100.0);
      }
   }

   if(a->orklar.savunma_ustaligi1==1)
   {
      if(g->orklar.ork_dovusculeris>0)
      {
         bir->orklar.ork_dovusculeri.savunma+=bir->orklar.ork_dovusculeri.savunma*((research->savunma_ustaligi.seviye_1.deger)/100.0);
      }
      if(g->orklar.mizrakcilars>0)
      {
         bir->orklar.mizrakcilar.savunma+=bir->orklar.mizrakcilar.savunma*((research->savunma_ustaligi.seviye_1.deger)/100.0);
      }
      if(g->orklar.varg_binicileris>0)
      {
         bir->orklar.varg_binicileri.savunma+=bir->orklar.varg_binicileri.savunma*((research->savunma_ustaligi.seviye_1.deger)/100.0);
      }
      if(g->orklar.trollers>0)
      {
         bir->orklar.troller.savunma+=bir->orklar.troller.savunma*((research->savunma_ustaligi.seviye_1.deger)/100.0);
      }
   }
   else if(a->orklar.savunma_ustaligi2==1)
   {
      if(g->orklar.ork_dovusculeris>0)
      {
         bir->orklar.ork_dovusculeri.savunma+=bir->orklar.ork_dovusculeri.savunma*((research->savunma_ustaligi.seviye_2.deger)/100.0);
      }
      if(g->orklar.mizrakcilars>0)
      {
         bir->orklar.mizrakcilar.savunma+=bir->orklar.mizrakcilar.savunma*((research->savunma_ustaligi.seviye_2.deger)/100.0);
      }
      if(g->orklar.varg_binicileris>0)
      {
         bir->orklar.varg_binicileri.savunma+=bir->orklar.varg_binicileri.savunma*((research->savunma_ustaligi.seviye_2.deger)/100.0);
      }
      if(g->orklar.trollers>0)
      {
         bir->orklar.troller.savunma+=bir->orklar.troller.savunma*((research->savunma_ustaligi.seviye_2.deger)/100.0);
      }
   }
   else if(a->orklar.savunma_ustaligi3==1)
   {
      if(g->orklar.ork_dovusculeris>0)
      {
         bir->orklar.ork_dovusculeri.savunma+=bir->orklar.ork_dovusculeri.savunma*((research->savunma_ustaligi.seviye_3.deger)/100.0);
      }
      if(g->orklar.mizrakcilars>0)
      {
         bir->orklar.mizrakcilar.savunma+=bir->orklar.mizrakcilar.savunma*((research->savunma_ustaligi.seviye_3.deger)/100.0);
      }
      if(g->orklar.varg_binicileris>0)
      {
         bir->orklar.varg_binicileri.savunma+=bir->orklar.varg_binicileri.savunma*((research->savunma_ustaligi.seviye_3.deger)/100.0);
      }
      if(g->orklar.trollers>0)
      {
         bir->orklar.troller.savunma+=bir->orklar.troller.savunma*((research->savunma_ustaligi.seviye_3.deger)/100.0);
      }
   }
}

void elit_egitim (arastirma_tarafi* a,genel_sayi* g, birim_genel* bir)
{
if (a->insanlar.elit_egitim1 == 1) {
   if(g->insanlar.piyadelers>0)
   {
      bir->insanlar.piyadeler.kritik_sans += 5;
   }
   if(g->insanlar.piyadelers>0)
   {
      bir->insanlar.okcular.kritik_sans += 5;
   }
   if(g->insanlar.suvarilers>0)
   {
      bir->insanlar.suvariler.kritik_sans += 5;
   }
   if(g->insanlar.kusatma_makineleris>0)
   {
      bir->insanlar.kusatma_makineleri.kritik_sans += 5;
   }
} 
 else if (a->insanlar.elit_egitim2 == 1) {
   if(g->insanlar.piyadelers>0)
   {
      bir->insanlar.piyadeler.kritik_sans += 10;
   }
   if(g->insanlar.okculars>0)
   {
      bir->insanlar.okcular.kritik_sans += 10;
   }
   if(g->insanlar.suvarilers>0)
   {
      bir->insanlar.suvariler.kritik_sans += 10;
   }
   if(g->insanlar.kusatma_makineleris>0)
   {
      bir->insanlar.kusatma_makineleri.kritik_sans += 10;
   }
}
   
else if (a->insanlar.elit_egitim3 == 1) {
   if(g->insanlar.piyadelers>0)
   {
      bir->insanlar.piyadeler.kritik_sans += 15;
   }
   if(g->insanlar.okculars>0)
   {
      bir->insanlar.okcular.kritik_sans += 15;
   }
   if(g->insanlar.suvarilers>0)
   {
      bir->insanlar.suvariler.kritik_sans += 15;
   }
   if(g->insanlar.kusatma_makineleris>0)
   {
      bir->insanlar.kusatma_makineleri.kritik_sans += 15;
   }
}

if(a->orklar.elit_egitim1==1){

   if(g->orklar.ork_dovusculeris>0)
   {
      bir->orklar.ork_dovusculeri.kritik_sans += 5;
   }
   if(g->orklar.mizrakcilars>0)
   {
      bir->orklar.mizrakcilar.kritik_sans += 5;
   }
   if(g->orklar.varg_binicileris>0)
   {
      bir->orklar.varg_binicileri.kritik_sans += 5;
   }
   if(g->orklar.trollers>0)
   {
      bir->orklar.troller.kritik_sans += 5;
   }
}
else if(a->orklar.elit_egitim2==1)
{
   if(g->orklar.ork_dovusculeris>0)
   {
      bir->orklar.ork_dovusculeri.kritik_sans += 10;
   }
   if(g->orklar.mizrakcilars>0)
   {
      bir->orklar.mizrakcilar.kritik_sans += 10;
   }
   if(g->orklar.varg_binicileris>0)
   {
      bir->orklar.varg_binicileri.kritik_sans += 10;
   }
   if(g->orklar.trollers>0)
   {
      bir->orklar.troller.kritik_sans += 10;
   }
}
else if(a->orklar.elit_egitim3==1)
{
   if(g->orklar.ork_dovusculeris>0)
   {
      bir->orklar.ork_dovusculeri.kritik_sans += 15;
   }
   if(g->orklar.mizrakcilars>0)
   {
      bir->orklar.mizrakcilar.kritik_sans += 15;
   }
   if(g->orklar.varg_binicileris>0)
   {
      bir->orklar.varg_binicileri.kritik_sans += 15;
   }
   if(g->orklar.trollers>0)
   {
      bir->orklar.troller.kritik_sans += 15;
   }
}
}


int saldiri_hesapla_insan(birim_genel* b,genel_sayi* sayi)
{

   int toplam_saldiri=0;
   if(sayi->insanlar.piyadelers>0){
      toplam_saldiri+=b->insanlar.piyadeler.saldiri*sayi->insanlar.piyadelers;
   }
   if(sayi->insanlar.okculars>0){
      toplam_saldiri+=b->insanlar.okcular.saldiri*sayi->insanlar.okculars;
   }
   if(sayi->insanlar.suvarilers>0){
      toplam_saldiri+=b->insanlar.suvariler.saldiri*sayi->insanlar.suvarilers;
   }
   if(sayi->insanlar.kusatma_makineleris>0){
      toplam_saldiri+=b->insanlar.kusatma_makineleri.saldiri*sayi->insanlar.kusatma_makineleris;
   }
   return toplam_saldiri;
}

int saldiri_hesapla_ork(birim_genel* b,genel_sayi* sayi)
{
   int toplam_saldiri=0;
  if(sayi->orklar.ork_dovusculeris>0){
     toplam_saldiri+=b->orklar.ork_dovusculeri.saldiri*sayi->orklar.ork_dovusculeris;
   }
   if(sayi->orklar.mizrakcilars>0){
      toplam_saldiri+=b->orklar.mizrakcilar.saldiri*sayi->orklar.mizrakcilars;
   }
   if(sayi->orklar.varg_binicileris>0){
      toplam_saldiri+=b->orklar.varg_binicileri.saldiri*sayi->orklar.varg_binicileris;
   }
   if(sayi->orklar.trollers>0){
      toplam_saldiri+=b->orklar.troller.saldiri*sayi->orklar.trollers;
   }
    
   return toplam_saldiri;
}

int savunma_hesapla_insan(birim_genel* b,genel_sayi* sayi)
{
   int toplam_savunma=0;
   if(sayi->insanlar.piyadelers>0){
      toplam_savunma+=b->insanlar.piyadeler.savunma*sayi->insanlar.piyadelers;
   }
   if(sayi->insanlar.okculars>0){
      toplam_savunma+=b->insanlar.okcular.savunma*sayi->insanlar.okculars;
   }
   if(sayi->insanlar.suvarilers>0){
      toplam_savunma+=b->insanlar.suvariler.savunma*sayi->insanlar.suvarilers;
   }
   if(sayi->insanlar.kusatma_makineleris>0){
      toplam_savunma+=b->insanlar.kusatma_makineleri.savunma*sayi->insanlar.kusatma_makineleris;
   }
   return toplam_savunma;
}

int savunma_hesapla_ork(birim_genel* b,genel_sayi* sayi)
{
   int toplam_savunma=0;
   if(sayi->orklar.ork_dovusculeris>0){
      toplam_savunma+=b->orklar.ork_dovusculeri.savunma*sayi->orklar.ork_dovusculeris;
   }
   if(sayi->orklar.mizrakcilars>0){
      toplam_savunma+=b->orklar.mizrakcilar.savunma*sayi->orklar.mizrakcilars;
   }
   if(sayi->orklar.varg_binicileris>0){
      toplam_savunma+=b->orklar.varg_binicileri.savunma*sayi->orklar.varg_binicileris;
   }
   if(sayi->orklar.trollers>0){
      toplam_savunma+=b->orklar.troller.savunma*sayi->orklar.trollers;
   }
   return toplam_savunma;
}



int netHasarHesapla(int saldiri, int savunma) {
    int netHasar = saldiri - savunma;
    if (netHasar < 0) {
        netHasar = 0;
    }
    return netHasar;
}

int savasSonuKontrol(genel_sayi* insanlar, genel_sayi* orklar) {
    if (insanlar->insanlar.piyadelers == 0 && insanlar->insanlar.okculars == 0 && insanlar->insanlar.suvarilers == 0 && insanlar->insanlar.kusatma_makineleris == 0) {
        return 1; //orklar kazanır
    }
    if (orklar->orklar.ork_dovusculeris == 0 && orklar->orklar.mizrakcilars == 0 && orklar->orklar.varg_binicileris == 0 && orklar->orklar.trollers == 0) {
        return 2; // insanlar kazanır
    }
    return 0;
}


int yorgunluk(int turSayisi,int toplamSaldiri,int toplamSavunma)
{
   int yorgunluk = 1;
   int nerf= yorgunluk*(0.1);
  
   if(turSayisi%5==0)
   {
        toplamSaldiri-=toplamSaldiri*nerf;
         toplamSavunma-=toplamSavunma*nerf;
         
         yorgunluk++;
   }
   return toplamSaldiri,toplamSavunma;

}

void adimKaydet(FILE *dosya, int adimNumarasi, genel_sayi *insanlar, genel_sayi *orklar) {
    printf("DenemeAAA");
    fprintf(dosya, "Adim %d:\n", adimNumarasi);
    fprintf(dosya, "İnsan İmparatorlugu - Piyadeler: %d, Okcular: %d Suvariler: %d, Kusatma makineleri: %d\n", insanlar->insanlar.piyadelers, insanlar->insanlar.okculars, insanlar->insanlar.suvarilers, insanlar->insanlar.kusatma_makineleris);
    fprintf(dosya, "Ork Lejyonu - Dövüşçüler: %d, Mizrakcilar: %d, Varg Binicileri: %d, Troller: %d\n", orklar->orklar.ork_dovusculeris, orklar->orklar.mizrakcilars, orklar->orklar.varg_binicileris, orklar->orklar.trollers);
    fprintf(dosya, "------------------------\n");
}

void savasSonuKaydet(FILE *dosya, int kazanan) {
    if (kazanan == 1) {
        fprintf(dosya, "Savaş sona erdi. Ork Lejyonu kazandi!\n");
    } else if (kazanan == 2) {
        fprintf(dosya, "Savaş sona erdi. İnsan İmparatorluğu kazandi!\n");
    }
}

void savas_simulasyonu(genel_sayi* insanlar, genel_sayi* orklar, birim_genel* birimler,bonuslar*  bonuslar,arastirma_tarafi* arastirma)
{
   FILE *adimDosya = fopen("savas_adimlari.txt", "w");
   if (adimDosya == NULL) {
      printf("Adim dosyasi acilamadi\n");
      return;
   }

   int turSayisi = 0;
   int kazanan = 0;

// Bonusları uygula
      varsayilan_deger(birimler);
      creatures_bonus(insanlar, birimler,&bonuslar->creatures_genel);
      heroes_bonus(insanlar, birimler, &bonuslar->heroes_genel);
      kusatma_ustaligi(arastirma, insanlar, birimler, &bonuslar->research_turleri);
      
      saldiri_gelistirmesi(arastirma, insanlar, &arastirma, birimler);
      
      savunma_ustaligi(arastirma, &arastirma, insanlar, birimler);
      savunma_ustaligi(arastirma, &arastirma, orklar, birimler);
      elit_egitim(arastirma, insanlar, birimler);
      elit_egitim(arastirma, orklar, birimler);


   while (kazanan == 0) {
      turSayisi++;

      

      // Saldırı ve savunma hesapla
      int insanSaldiri = saldiri_hesapla_insan(birimler, insanlar);
      int orkSaldiri = saldiri_hesapla_ork(birimler, orklar);
      int insanSavunma = savunma_hesapla_insan(birimler, insanlar);
      int orkSavunma = savunma_hesapla_ork(birimler, orklar);

      // Yorgunluk hesapla
      insanSaldiri, insanSavunma = yorgunluk(turSayisi, insanSaldiri, insanSavunma);
      orkSaldiri, orkSavunma = yorgunluk(turSayisi, orkSaldiri, orkSavunma);

      // Net hasar hesapla
      int insanNetHasar = netHasarHesapla(orkSaldiri, insanSavunma);
      int orkNetHasar = netHasarHesapla(insanSaldiri, orkSavunma);

      // Birim sayısını güncelle
      insanlar->insanlar.piyadelers -= insanNetHasar / birimler->insanlar.piyadeler.saglik;
      orklar->orklar.ork_dovusculeris -= orkNetHasar / birimler->orklar.ork_dovusculeri.saglik;

      // Adımı kaydet
      adimKaydet(adimDosya, turSayisi, insanlar, orklar);

      // Savaş sonu kontrol
      kazanan = savasSonuKontrol(insanlar, orklar);
   }

   // Savaş sonu kaydet
   savasSonuKaydet(adimDosya, kazanan);

   fclose(adimDosya);
}
  
    





int main() {

srand(time(NULL));

    FILE* heroes_dosya = fopen("C:\\projefiles\\unit_types.json", "r");
    FILE* research_dosya = fopen("C:\\projefiles\\research.json", "r");
    FILE* unit_types_dosya = fopen("C:\\projefiles\\unit_types.json", "r");
    FILE* creatures_dosya = fopen("C:\\projefiles\\creatures.json", "r");
    FILE* senaryolar_dosya= fopen("C:\\projefiles\\3.json", "r");
 
      if (heroes_dosya == NULL || research_dosya == NULL || unit_types_dosya == NULL || creatures_dosya == NULL || senaryolar_dosya == NULL) {
         printf("Dosya acilamadi\n");
         return 1;
        }else printf("Dosyalar acildi\n");
      
        bonuslar bonuslar;
       arastirma_tarafi arastirmaTarafi;
      genel_sayi sayilarim;
       birim_genel bir;
        heroes_genel kahramanlar;
        heroes_genel orklar;
        research_turleri arastirma;
        birim_genel insan_birimleri;
        birim_genel ork_birimleri;
         creatures_genel insanimp_creatures;
         creatures_genel orklar_creatures;
         
         
         deger_ata_heroes(&kahramanlar.insanlar.Alparslan, heroes_dosya); fseek(heroes_dosya, 0, SEEK_SET);
         deger_ata_heroes(&kahramanlar.insanlar.Fatih_Sultan_Mehmet, heroes_dosya); fseek(heroes_dosya, 0, SEEK_SET);
         deger_ata_heroes(&kahramanlar.insanlar.Mete_Han, heroes_dosya); fseek(heroes_dosya, 0, SEEK_SET);
         deger_ata_heroes(&kahramanlar.insanlar.Tugrul_Bey, heroes_dosya); fseek(heroes_dosya, 0, SEEK_SET);
         deger_ata_heroes(&kahramanlar.insanlar.Yavuz_Sultan_Selim, heroes_dosya); fseek(heroes_dosya, 0, SEEK_SET);
 

         deger_ata_heroes(&orklar.orklar.Goruk_Vahsi, heroes_dosya); fseek(heroes_dosya, 0, SEEK_SET);
         deger_ata_heroes(&orklar.orklar.Thruk_Kemikkiran, heroes_dosya); fseek(heroes_dosya, 0, SEEK_SET);
         deger_ata_heroes(&orklar.orklar.Ugur_Zalim, heroes_dosya); fseek(heroes_dosya, 0, SEEK_SET);
         deger_ata_heroes(&orklar.orklar.Vrog_Kafakiran, heroes_dosya); fseek(heroes_dosya, 0, SEEK_SET);


         deger_ata_research(&arastirma.elit_egitim.seviye_1, research_dosya); fseek(research_dosya, 0, SEEK_SET);
         deger_ata_research(&arastirma.elit_egitim.seviye_2, research_dosya); fseek(research_dosya, 0, SEEK_SET);
         deger_ata_research(&arastirma.elit_egitim.seviye_3, research_dosya); fseek(research_dosya, 0, SEEK_SET);
         deger_ata_research(&arastirma.kusatma_ustaligi.seviye_1, research_dosya); fseek(research_dosya, 0, SEEK_SET);
         deger_ata_research(&arastirma.kusatma_ustaligi.seviye_2, research_dosya); fseek(research_dosya, 0, SEEK_SET);
         deger_ata_research(&arastirma.kusatma_ustaligi.seviye_3, research_dosya); fseek(research_dosya, 0, SEEK_SET);
         deger_ata_research(&arastirma.saldiri_gelistirmesi.seviye_1, research_dosya); fseek(research_dosya, 0, SEEK_SET);
         deger_ata_research(&arastirma.saldiri_gelistirmesi.seviye_2, research_dosya); fseek(research_dosya, 0, SEEK_SET);
         deger_ata_research(&arastirma.saldiri_gelistirmesi.seviye_3, research_dosya); fseek(research_dosya, 0, SEEK_SET);
         deger_ata_research(&arastirma.savunma_ustaligi.seviye_1, research_dosya); fseek(research_dosya, 0, SEEK_SET);
         deger_ata_research(&arastirma.savunma_ustaligi.seviye_2, research_dosya); fseek(research_dosya, 0, SEEK_SET);
         deger_ata_research(&arastirma.savunma_ustaligi.seviye_3, research_dosya); fseek(research_dosya, 0, SEEK_SET);

         
         deger_ata_creatures(&insanimp_creatures.insanlar.Agri_Dagi_Devleri, creatures_dosya); fseek(creatures_dosya, 0, SEEK_SET);
         deger_ata_creatures(&insanimp_creatures.insanlar.Ejderha, creatures_dosya); fseek(creatures_dosya, 0, SEEK_SET);
         deger_ata_creatures(&insanimp_creatures.insanlar.Karakurt, creatures_dosya); fseek(creatures_dosya, 0, SEEK_SET); 
         deger_ata_creatures(&insanimp_creatures.insanlar.Samur, creatures_dosya); fseek(creatures_dosya, 0, SEEK_SET);
         deger_ata_creatures(&insanimp_creatures.insanlar.Tepegoz, creatures_dosya); fseek(creatures_dosya, 0, SEEK_SET);

         fseek(creatures_dosya, 0, SEEK_SET);
         deger_ata_creatures(&orklar_creatures.orklar.Ates_Iblisi, creatures_dosya);
         fseek(creatures_dosya, 0, SEEK_SET);
         deger_ata_creatures(&orklar_creatures.orklar.Buz_Devleri, creatures_dosya);
         fseek(creatures_dosya, 0, SEEK_SET);
         deger_ata_creatures(&orklar_creatures.orklar.Camur_Devleri, creatures_dosya);
         fseek(creatures_dosya, 0, SEEK_SET);
         deger_ata_creatures(&orklar_creatures.orklar.Golge_Kurtlari, creatures_dosya);
         fseek(creatures_dosya, 0, SEEK_SET);
         deger_ata_creatures(&orklar_creatures.orklar.Kara_Troll, creatures_dosya);
         fseek(creatures_dosya, 0, SEEK_SET);
         deger_ata_creatures(&orklar_creatures.orklar.Makrog_Savas_Beyi, creatures_dosya); fseek(creatures_dosya, 0, SEEK_SET);
         fseek(unit_types_dosya,0,SEEK_SET);
        deger_ata_unit_types(&insan_birimleri.insanlar.kusatma_makineleri, unit_types_dosya); fseek(unit_types_dosya, 0, SEEK_SET);
         deger_ata_unit_types(&insan_birimleri.insanlar.okcular, unit_types_dosya); fseek(unit_types_dosya, 0, SEEK_SET);
         deger_ata_unit_types(&insan_birimleri.insanlar.piyadeler, unit_types_dosya); fseek(unit_types_dosya, 0, SEEK_SET);
         deger_ata_unit_types(&insan_birimleri.insanlar.suvariler, unit_types_dosya); fseek(unit_types_dosya, 0, SEEK_SET);

         deger_ata_unit_types(&ork_birimleri.orklar.mizrakcilar, unit_types_dosya);  fseek(unit_types_dosya, 0, SEEK_SET);
         deger_ata_unit_types(&ork_birimleri.orklar.ork_dovusculeri, unit_types_dosya);  fseek(unit_types_dosya, 0, SEEK_SET);
         deger_ata_unit_types(&ork_birimleri.orklar.troller, unit_types_dosya);  fseek(unit_types_dosya, 0, SEEK_SET);
         deger_ata_unit_types(&ork_birimleri.orklar.varg_binicileri, unit_types_dosya);  fseek(unit_types_dosya, 0, SEEK_SET);
         void varsayilan_deger();
         sifirla(&sayilarim,&arastirmaTarafi);
        senaryo_oku(senaryolar_dosya,&sayilarim,&arastirmaTarafi);
     /* printf("Insanlar:\n");
      printf("Piyadeler: %d\n", sayilarim.insanlar.piyadelers);
      printf("Okcular: %d\n", sayilarim.insanlar.okculars);
      printf("Suvariler: %d\n", sayilarim.insanlar.suvarilers);
      printf("Kusatma Makineleri: %d\n", sayilarim.insanlar.kusatma_makineleris);
      printf("Orklar:\n");
      printf("Ork Dovusculeri: %d\n", sayilarim.orklar.ork_dovusculeris);
      printf("Mizrakcilar: %d\n", sayilarim.orklar.mizrakcilars);
      printf("Troller: %d\n", sayilarim.orklar.trollers);
      printf("Varg Binicileri: %d\n", sayilarim.orklar.varg_binicileris);
      printf("Arastirmalar:\n");
   
      printf(" %d", arastirmaTarafi.insanlar.savunma_ustaligi2); */
      printf("%d",bir.insanlar.piyadeler.saldiri);
      
      
      
     
         
         fclose(heroes_dosya);
         fclose(research_dosya);
         fclose(unit_types_dosya);
         fclose(creatures_dosya);
         fclose(senaryolar_dosya);
         


     return 0;
    }
