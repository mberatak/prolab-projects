#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>



    typedef struct // unit_types.json icin
{
     int saldiri;
    int savunma;
    int saglik;
    float kritik_sans;
    int genel_can;

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


    char* start = strchr(satir, '\"');
    if (start) {
        start++;
        char* end = strchr(start, '\"');
        if (end) {
            strncpy(neyindegeri, start, end - start);
            neyindegeri[end - start] = '\0';
        }
    }
    char* basla = strchr(satir, ':');
    if (basla) {
        basla++;
        while (*basla == ' ') basla++;


        if (*basla == '{' || *basla == '"') basla++;


        char* bitis = basla;
        while (*bitis != '\0' && *bitis != '}' && *bitis != '\"') {
            bitis++;
        }
        if (bitis > basla) {
            strncpy(deger, basla, bitis - basla);
            deger[bitis - basla] = '\0';
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
   heroes Ugar_Zalim;
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

typedef struct
{
   research_turleri research_turleri;
   heroes_genel heroes_genel;
   creatures_genel creatures_genel;

}bonuslar;


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



void deger_ata_heroes(heroes_genel* kahramanlar, FILE* dosya) // kahramanlarin degerini atama
{
   char satir[300];
   char neyindegeri[100], deger[100];

   while(fgets(satir,sizeof(satir),dosya))
   {

      bosluk_sil(satir);
      if(strstr(satir,"Alparslan")){

         while(fgets(satir,sizeof(satir),dosya))
         {

            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"bonus_turu")==0)
            {
               strcpy(kahramanlar->insanlar.Alparslan.bonus_turu,deger);
            }
            else if(strcmp(neyindegeri,"bonus_degeri")==0)
            {
               kahramanlar->insanlar.Alparslan.bonus_degeri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"aciklama")==0)
            {
               strcpy(kahramanlar->insanlar.Alparslan.aciklama,deger);
               break;
            }
         }
      }
        else if(strstr(satir,"\"Fatih_Sultan_Mehmet\"")){
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"bonus_turu")==0)
            {
               strcpy(kahramanlar->insanlar.Fatih_Sultan_Mehmet.bonus_turu,deger);
            }
            else if(strcmp(neyindegeri,"bonus_degeri")==0)
            {
               kahramanlar->insanlar.Fatih_Sultan_Mehmet.bonus_degeri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"aciklama")==0)
            {
               strcpy(kahramanlar->insanlar.Fatih_Sultan_Mehmet.aciklama,deger);
               break;
            }
         }
        }
         else if(strstr(satir,"\"Mete_Han\"")){
          while(fgets(satir,sizeof(satir),dosya))
          {
               bosluk_sil(satir);
               degerayir(satir,neyindegeri,deger);
               if(strcmp(neyindegeri,"bonus_turu")==0)
               {
                strcpy(kahramanlar->insanlar.Mete_Han.bonus_turu,deger);
               }
               else if(strcmp(neyindegeri,"bonus_degeri")==0)
               {
                kahramanlar->insanlar.Mete_Han.bonus_degeri=atoi(deger);
               }
               else if(strcmp(neyindegeri,"aciklama")==0)
               {
                strcpy(kahramanlar->insanlar.Mete_Han.aciklama,deger);
                break;
               }
          }
         }
         else if(strstr(satir,"\"Yavuz_Sultan_Selim\"")){
          while(fgets(satir,sizeof(satir),dosya))
          {
               bosluk_sil(satir);
               degerayir(satir,neyindegeri,deger);
               if(strcmp(neyindegeri,"bonus_turu")==0)
               {
                strcpy(kahramanlar->insanlar.Yavuz_Sultan_Selim.bonus_turu,deger);
               }
               else if(strcmp(neyindegeri,"bonus_degeri")==0)
               {
                kahramanlar->insanlar.Yavuz_Sultan_Selim.bonus_degeri=atoi(deger);
               }
               else if(strcmp(neyindegeri,"aciklama")==0)
               {
                strcpy(kahramanlar->insanlar.Yavuz_Sultan_Selim.aciklama,deger);
                break;
               }
          }
         }
         else if(strstr(satir,"\"Tugrul_Bey\"")){
          while(fgets(satir,sizeof(satir),dosya))
          {
               bosluk_sil(satir);
               degerayir(satir,neyindegeri,deger);
               if(strcmp(neyindegeri,"bonus_turu")==0)
               {
                strcpy(kahramanlar->insanlar.Tugrul_Bey.bonus_turu,deger);
               }
               else if(strcmp(neyindegeri,"bonus_degeri")==0)
               {
                kahramanlar->insanlar.Tugrul_Bey.bonus_degeri=atoi(deger);
               }
               else if(strcmp(neyindegeri,"aciklama")==0)
               {
                strcpy(kahramanlar->insanlar.Tugrul_Bey.aciklama,deger);
                break;
               }
          }
         }
         else if(strstr(satir,"\"Goruk_Vahsi\"")){
          while(fgets(satir,sizeof(satir),dosya))
          {
               bosluk_sil(satir);
               degerayir(satir,neyindegeri,deger);
               if(strcmp(neyindegeri,"bonus_turu")==0)
               {
                strcpy(kahramanlar->orklar.Goruk_Vahsi.bonus_turu,deger);
               }
               else if(strcmp(neyindegeri,"bonus_degeri")==0)
               {
                kahramanlar->orklar.Goruk_Vahsi.bonus_degeri=atoi(deger);
               }
               else if(strcmp(neyindegeri,"aciklama")==0)
               {
                strcpy(kahramanlar->orklar.Goruk_Vahsi.aciklama,deger);
                break;
               }
          }
         }
         else if(strstr(satir,"\"Thruk_Kemikkiran\"")){
          while(fgets(satir,sizeof(satir),dosya))
          {
               bosluk_sil(satir);
               degerayir(satir,neyindegeri,deger);
               if(strcmp(neyindegeri,"bonus_turu")==0)
               {
                strcpy(kahramanlar->orklar.Thruk_Kemikkiran.bonus_turu,deger);
               }
               else if(strcmp(neyindegeri,"bonus_degeri")==0)
               {
                kahramanlar->orklar.Thruk_Kemikkiran.bonus_degeri=atoi(deger);
               }
               else if(strcmp(neyindegeri,"aciklama")==0)
               {
                strcpy(kahramanlar->orklar.Thruk_Kemikkiran.aciklama,deger);
                break;
               }
          }
         }
         else if(strstr(satir,"\"Vrog_Kafakiran\"")){
          while(fgets(satir,sizeof(satir),dosya))
          {
               bosluk_sil(satir);
               degerayir(satir,neyindegeri,deger);
               if(strcmp(neyindegeri,"bonus_turu")==0)
               {
                strcpy(kahramanlar->orklar.Vrog_Kafakiran.bonus_turu,deger);
               }
               else if(strcmp(neyindegeri,"bonus_degeri")==0)
               {
                kahramanlar->orklar.Vrog_Kafakiran.bonus_degeri=atoi(deger);
               }
               else if(strcmp(neyindegeri,"aciklama")==0)
               {
                strcpy(kahramanlar->orklar.Vrog_Kafakiran.aciklama,deger);
                break;
               }
          }
         }
         else if(strstr(satir,"\"Ugar_Zalim\"")){
          while(fgets(satir,sizeof(satir),dosya))
          {
               bosluk_sil(satir);
               degerayir(satir,neyindegeri,deger);
               if(strcmp(neyindegeri,"bonus_turu")==0)
               {
                strcpy(kahramanlar->orklar.Ugar_Zalim.bonus_turu,deger);
               }
               else if(strcmp(neyindegeri,"bonus_degeri")==0)
               {
                kahramanlar->orklar.Ugar_Zalim.bonus_degeri=atoi(deger);
               }
               else if(strcmp(neyindegeri,"aciklama")==0)
               {
                strcpy(kahramanlar->orklar.Ugar_Zalim.aciklama,deger);
                break;
               }
          }
         }




   }
   }



void deger_ata_creatures(creatures_genel* creatures, FILE* dosya) {
    char satir[300];
    char neyindegeri[100], deger[100];


    while (fgets(satir, sizeof(satir), dosya)) {
        bosluk_sil(satir);


        if (strstr(satir, "\"Ejderha\"")) {

            while (fgets(satir, sizeof(satir), dosya)) {
                bosluk_sil(satir);
                degerayir(satir, neyindegeri, deger);
                if (strcmp(neyindegeri, "etki_degeri") == 0) {
                    creatures->insanlar.Ejderha.etki_degeri = atoi(deger);
                } else if (strcmp(neyindegeri, "etki_turu") == 0) {
                    strcpy(creatures->insanlar.Ejderha.etki_turu, deger);
                } else if (strcmp(neyindegeri, "aciklama") == 0) {
                    strcpy(creatures->insanlar.Ejderha.aciklama, deger);
                    break;
                }
            }
        }


        else if (strstr(satir, "\"Agri_Dagi_Devleri\"")) {
            while (fgets(satir, sizeof(satir), dosya)) {
                bosluk_sil(satir);
                degerayir(satir, neyindegeri, deger);
                if (strcmp(neyindegeri, "etki_degeri") == 0) {
                    creatures->insanlar.Agri_Dagi_Devleri.etki_degeri = atoi(deger);
                } else if (strcmp(neyindegeri, "etki_turu") == 0) {
                    strcpy(creatures->insanlar.Agri_Dagi_Devleri.etki_turu, deger);
                } else if (strcmp(neyindegeri, "aciklama") == 0) {
                    strcpy(creatures->insanlar.Agri_Dagi_Devleri.aciklama, deger);
                    break;
                }
            }
        }
       else if(strstr(satir,"\"Tepegoz\"")){
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"etki_degeri")==0)
            {
               creatures->insanlar.Tepegoz.etki_degeri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"etki_turu")==0)
            {
               strcpy(creatures->insanlar.Tepegoz.etki_turu,deger);
            }
            else if(strcmp(neyindegeri,"aciklama")==0)
            {
               strcpy(creatures->insanlar.Tepegoz.aciklama,deger);
               break;
            }
         }
       }
       else if(strstr(satir,"\"Karakurt\"")){
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"etki_degeri")==0)
            {
               creatures->insanlar.Karakurt.etki_degeri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"etki_turu")==0)
            {
               strcpy(creatures->insanlar.Karakurt.etki_turu,deger);
            }
            else if(strcmp(neyindegeri,"aciklama")==0)
            {
               strcpy(creatures->insanlar.Karakurt.aciklama,deger);
               break;
            }
         }
       }
       else if(strstr(satir,"\"Samur\"")){

         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"etki_degeri")==0)
            {
               creatures->insanlar.Samur.etki_degeri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"etki_turu")==0)
            {
               strcpy(creatures->insanlar.Samur.etki_turu,deger);
            }
            else if(strcmp(neyindegeri,"aciklama")==0)
            {
               strcpy(creatures->insanlar.Samur.aciklama,deger);
               break;
            }
         }
       }

       else if(strstr(satir,"\"Kara_Troll\"")){
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"etki_degeri")==0)
            {
               creatures->orklar.Kara_Troll.etki_degeri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"etki_turu")==0)
            {
               strcpy(creatures->orklar.Kara_Troll.etki_turu,deger);
            }
            else if(strcmp(neyindegeri,"aciklama")==0)
            {
               strcpy(creatures->orklar.Kara_Troll.aciklama,deger);
               break;
            }
         }
       }
       else if(strstr(satir,"\"Golge_Kurtlari\"")){
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"etki_degeri")==0)
            {
               creatures->orklar.Golge_Kurtlari.etki_degeri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"etki_turu")==0)
            {
               strcpy(creatures->orklar.Golge_Kurtlari.etki_turu,deger);
            }
            else if(strcmp(neyindegeri,"aciklama")==0)
            {
               strcpy(creatures->orklar.Golge_Kurtlari.aciklama,deger);
               break;
            }
         }
       }
       else if(strstr(satir,"\"Camur_Devleri\"")){
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"etki_degeri")==0)
            {
               creatures->orklar.Camur_Devleri.etki_degeri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"etki_turu")==0)
            {
               strcpy(creatures->orklar.Camur_Devleri.etki_turu,deger);
            }
            else if(strcmp(neyindegeri,"aciklama")==0)
            {
               strcpy(creatures->orklar.Camur_Devleri.aciklama,deger);
               break;
            }
         }
       }
       else if(strstr(satir,"\"Ates_Iblisi\"")){
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"etki_degeri")==0)
            {
               creatures->orklar.Ates_Iblisi.etki_degeri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"etki_turu")==0)
            {
               strcpy(creatures->orklar.Ates_Iblisi.etki_turu,deger);
            }
            else if(strcmp(neyindegeri,"aciklama")==0)
            {
               strcpy(creatures->orklar.Ates_Iblisi.aciklama,deger);
               break;
            }
         }
       }
       else if(strstr(satir,"Makrog_Savas_Beyi")){
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"etki_degeri")==0)
            {
               creatures->orklar.Makrog_Savas_Beyi.etki_degeri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"etki_turu")==0)
            {
               strcpy(creatures->orklar.Makrog_Savas_Beyi.etki_turu,deger);
            }
            else if(strcmp(neyindegeri,"aciklama")==0)
            {
               strcpy(creatures->orklar.Makrog_Savas_Beyi.aciklama,deger);
               break;
            }
         }
       }
       else if(strstr(satir,"Buz_Devleri")){
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"etki_degeri")==0)
            {
               creatures->orklar.Buz_Devleri.etki_degeri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"etki_turu")==0)
            {
               strcpy(creatures->orklar.Buz_Devleri.etki_turu,deger);
            }
            else if(strcmp(neyindegeri,"aciklama")==0)
            {
               strcpy(creatures->orklar.Buz_Devleri.aciklama,deger);
               break;
            }
         }
       }

    }
}




void deger_ata_unit_types(birim_genel *birim, FILE* dosya){
   char satir[300];
   char neyindegeri[100], deger[100];
   while(fgets(satir,sizeof(satir),dosya))
   {
      bosluk_sil(satir);

      if(strstr(satir,"\"piyadeler\"")){
      while(fgets(satir,sizeof(satir),dosya)){
         bosluk_sil(satir);
         degerayir(satir,neyindegeri,deger);
         if(strcmp(neyindegeri,"saldiri")==0){
            birim->insanlar.piyadeler.saldiri=atoi(deger);
         }
         else if(strcmp(neyindegeri,"savunma")==0){
            birim->insanlar.piyadeler.savunma=atoi(deger);
         }
         else if(strcmp(neyindegeri,"saglik")==0){
            birim->insanlar.piyadeler.saglik=atoi(deger);
            birim->insanlar.piyadeler.genel_can=atoi(deger);
         }
         else if(strcmp(neyindegeri,"kritik_sans")==0){
            birim->insanlar.piyadeler.kritik_sans=atof(deger);
            break;
         }
      }
      }
      else if(strstr(satir,"\"okcular\"")){
      while(fgets(satir,sizeof(satir),dosya)){
         bosluk_sil(satir);
         degerayir(satir,neyindegeri,deger);
         if(strcmp(neyindegeri,"saldiri")==0){
            birim->insanlar.okcular.saldiri=atoi(deger);
         }
         else if(strcmp(neyindegeri,"savunma")==0){
            birim->insanlar.okcular.savunma=atoi(deger);
         }
         else if(strcmp(neyindegeri,"saglik")==0){
            birim->insanlar.okcular.saglik=atoi(deger);
            birim->insanlar.okcular.genel_can=atoi(deger);
         }
         else if(strcmp(neyindegeri,"kritik_sans")==0){
            birim->insanlar.okcular.kritik_sans=atof(deger);
            break;
         }
      }
      }
      else if(strstr(satir,"\"suvariler\"")){
      while(fgets(satir,sizeof(satir),dosya)){
         bosluk_sil(satir);
         degerayir(satir,neyindegeri,deger);
         if(strcmp(neyindegeri,"saldiri")==0){
            birim->insanlar.suvariler.saldiri=atoi(deger);
         }
         else if(strcmp(neyindegeri,"savunma")==0){
            birim->insanlar.suvariler.savunma=atoi(deger);
         }
         else if(strcmp(neyindegeri,"saglik")==0){
            birim->insanlar.suvariler.saglik=atoi(deger);
            birim->insanlar.suvariler.genel_can=atoi(deger);
         }
         else if(strcmp(neyindegeri,"kritik_sans")==0){
            birim->insanlar.suvariler.kritik_sans=atof(deger);
            break;
         }
      }
      }
      else if(strstr(satir,"\"kusatma_makineleri\"")){
      while(fgets(satir,sizeof(satir),dosya)){
         bosluk_sil(satir);
         degerayir(satir,neyindegeri,deger);
         if(strcmp(neyindegeri,"saldiri")==0){
            birim->insanlar.kusatma_makineleri.saldiri=atoi(deger);
         }
         else if(strcmp(neyindegeri,"savunma")==0){
            birim->insanlar.kusatma_makineleri.savunma=atoi(deger);
         }
         else if(strcmp(neyindegeri,"saglik")==0){
            birim->insanlar.kusatma_makineleri.saglik=atoi(deger);
            birim->insanlar.kusatma_makineleri.genel_can=atoi(deger);
         }
         else if(strcmp(neyindegeri,"kritik_sans")==0){
            birim->insanlar.kusatma_makineleri.kritik_sans=atof(deger);
            break;
         }
      }
      }
      else if(strstr(satir,"\"ork_dovusculeri\""))
      {
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"saldiri")==0)
            {
               birim->orklar.ork_dovusculeri.saldiri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"savunma")==0)
            {
               birim->orklar.ork_dovusculeri.savunma=atoi(deger);
            }
            else if(strcmp(neyindegeri,"saglik")==0)
            {
               birim->orklar.ork_dovusculeri.saglik=atoi(deger);
               birim->orklar.ork_dovusculeri.genel_can=atoi(deger);
            }
            else if(strcmp(neyindegeri,"kritik_sans")==0)
            {
               birim->orklar.ork_dovusculeri.kritik_sans=atof(deger);
               break;
            }
         }
      }
      else if(strstr(satir,"\"mizrakcilar\""))
      {
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"saldiri")==0)
            {
               birim->orklar.mizrakcilar.saldiri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"savunma")==0)
            {
               birim->orklar.mizrakcilar.savunma=atoi(deger);
            }
            else if(strcmp(neyindegeri,"saglik")==0)
            {
               birim->orklar.mizrakcilar.saglik=atoi(deger);
               birim->orklar.mizrakcilar.genel_can=atoi(deger);
            }
            else if(strcmp(neyindegeri,"kritik_sans")==0)
            {
               birim->orklar.mizrakcilar.kritik_sans=atof(deger);
               break;
            }
         }
      }
      else if(strstr(satir,"\"varg_binicileri\""))
      {
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"saldiri")==0)
            {
               birim->orklar.varg_binicileri.saldiri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"savunma")==0)
            {
               birim->orklar.varg_binicileri.savunma=atoi(deger);
            }
            else if(strcmp(neyindegeri,"saglik")==0)
            {
               birim->orklar.varg_binicileri.saglik=atoi(deger);
               birim->orklar.varg_binicileri.genel_can=atoi(deger);
            }
            else if(strcmp(neyindegeri,"kritik_sans")==0)
            {
               birim->orklar.varg_binicileri.kritik_sans=atof(deger);
               break;
            }
         }
      }
      else if(strstr(satir,"\"troller\""))
      {
         while(fgets(satir,sizeof(satir),dosya))
         {
            bosluk_sil(satir);
            degerayir(satir,neyindegeri,deger);
            if(strcmp(neyindegeri,"saldiri")==0)
            {
               birim->orklar.troller.saldiri=atoi(deger);
            }
            else if(strcmp(neyindegeri,"savunma")==0)
            {
               birim->orklar.troller.savunma=atoi(deger);
            }
            else if(strcmp(neyindegeri,"saglik")==0)
            {
               birim->orklar.troller.saglik=atoi(deger);
               birim->orklar.troller.genel_can=atoi(deger);
            }
            else if(strcmp(neyindegeri,"kritik_sans")==0)
            {
               birim->orklar.troller.kritik_sans=atof(deger);
               break;
            }
         }
      }



}
}





void deger_ata_research(research_turleri* research, FILE* dosya) {
    char satir[300];
    char neyindegeri[100], deger[100];

    while (fgets(satir, sizeof(satir), dosya)) {
        bosluk_sil(satir);


        if (strstr(satir, "\"savunma_ustaligi\"")) {
            while (fgets(satir, sizeof(satir), dosya)) {
                bosluk_sil(satir);
                degerayir(satir, neyindegeri, deger);

                if (strcmp(neyindegeri, "seviye_1") == 0) {
                    while (fgets(satir, sizeof(satir), dosya)) {
                        bosluk_sil(satir);
                        degerayir(satir, neyindegeri, deger);
                        if (strcmp(neyindegeri, "deger") == 0) {
                            research->savunma_ustaligi.seviye_1.deger = atoi(deger);
                        } else if (strcmp(neyindegeri, "aciklama") == 0) {
                            strcpy(research->savunma_ustaligi.seviye_1.aciklama, deger);
                            break;
                        }
                    }
                } else if (strcmp(neyindegeri, "seviye_2") == 0) {
                    while (fgets(satir, sizeof(satir), dosya)) {
                        bosluk_sil(satir);
                        degerayir(satir, neyindegeri, deger);
                        if (strcmp(neyindegeri, "deger") == 0) {
                            research->savunma_ustaligi.seviye_2.deger = atoi(deger);
                        } else if (strcmp(neyindegeri, "aciklama") == 0) {
                            strcpy(research->savunma_ustaligi.seviye_2.aciklama, deger);
                            break;
                        }
                    }
                } else if (strcmp(neyindegeri, "seviye_3") == 0) {
                    while (fgets(satir, sizeof(satir), dosya)) {
                        bosluk_sil(satir);
                        degerayir(satir, neyindegeri, deger);
                        if (strcmp(neyindegeri, "deger") == 0) {
                            research->savunma_ustaligi.seviye_3.deger = atoi(deger);
                        } else if (strcmp(neyindegeri, "aciklama") == 0) {
                            strcpy(research->savunma_ustaligi.seviye_3.aciklama, deger);
                            break;
                        }
                    }
                }

                if (strstr(satir, "\"saldiri_gelistirmesi\"")) {
                    break;
                }
            }
        }

        if (strstr(satir, "\"saldiri_gelistirmesi\"")) {
            while (fgets(satir, sizeof(satir), dosya)) {
                bosluk_sil(satir);
                degerayir(satir, neyindegeri, deger);

                if (strcmp(neyindegeri, "seviye_1") == 0) {
                    while (fgets(satir, sizeof(satir), dosya)) {
                        bosluk_sil(satir);
                        degerayir(satir, neyindegeri, deger);
                        if (strcmp(neyindegeri, "deger") == 0) {
                            research->saldiri_gelistirmesi.seviye_1.deger = atoi(deger);
                        } else if (strcmp(neyindegeri, "aciklama") == 0) {
                            strcpy(research->saldiri_gelistirmesi.seviye_1.aciklama, deger);
                            break;
                        }
                    }
                } else if (strcmp(neyindegeri, "seviye_2") == 0) {
                    while (fgets(satir, sizeof(satir), dosya)) {
                        bosluk_sil(satir);
                        degerayir(satir, neyindegeri, deger);
                        if (strcmp(neyindegeri, "deger") == 0) {
                            research->saldiri_gelistirmesi.seviye_2.deger = atoi(deger);
                        } else if (strcmp(neyindegeri, "aciklama") == 0) {
                            strcpy(research->saldiri_gelistirmesi.seviye_2.aciklama, deger);
                            break;
                        }
                    }
                } else if (strcmp(neyindegeri, "seviye_3") == 0) {
                    while (fgets(satir, sizeof(satir), dosya)) {
                        bosluk_sil(satir);
                        degerayir(satir, neyindegeri, deger);
                        if (strcmp(neyindegeri, "deger") == 0) {
                            research->saldiri_gelistirmesi.seviye_3.deger = atoi(deger);
                        } else if (strcmp(neyindegeri, "aciklama") == 0) {
                            strcpy(research->saldiri_gelistirmesi.seviye_3.aciklama, deger);
                            break;
                        }
                    }
                }
                if(strstr(satir,"\"elit_egitim\"")){
                    break;
                }
            }
        }
        if(strstr(satir,"\"elit_egitim\""))
         {
               while(fgets(satir,sizeof(satir),dosya))
               {
                  bosluk_sil(satir);
                  degerayir(satir,neyindegeri,deger);
                  if(strcmp(neyindegeri,"seviye_1")==0)
                  {
                     while(fgets(satir,sizeof(satir),dosya))
                     {
                           bosluk_sil(satir);
                           degerayir(satir,neyindegeri,deger);
                           if(strcmp(neyindegeri,"deger")==0)
                           {
                              research->elit_egitim.seviye_1.deger=atoi(deger);
                           }
                           else if(strcmp(neyindegeri,"aciklama")==0)
                           {
                              strcpy(research->elit_egitim.seviye_1.aciklama,deger);
                              break;
                           }
                     }
                  }
                  else if(strcmp(neyindegeri,"seviye_2")==0)
                  {
                     while(fgets(satir,sizeof(satir),dosya))
                     {
                           bosluk_sil(satir);
                           degerayir(satir,neyindegeri,deger);
                           if(strcmp(neyindegeri,"deger")==0)
                           {
                              research->elit_egitim.seviye_2.deger=atoi(deger);
                           }
                           else if(strcmp(neyindegeri,"aciklama")==0)
                           {
                              strcpy(research->elit_egitim.seviye_2.aciklama,deger);
                              break;
                           }
                     }
                  }
                  else if(strcmp(neyindegeri,"seviye_3")==0)
                  {
                     while(fgets(satir,sizeof(satir),dosya))
                     {
                           bosluk_sil(satir);
                           degerayir(satir,neyindegeri,deger);
                           if(strcmp(neyindegeri,"deger")==0)
                           {
                              research->elit_egitim.seviye_3.deger=atoi(deger);
                           }
                           else if(strcmp(neyindegeri,"aciklama")==0)
                           {
                              strcpy(research->elit_egitim.seviye_3.aciklama,deger);
                              break;
                           }
                     }
                  }
                  if(strstr(satir,"\"kusatma_ustaligi\""))
                  {
                     break;
                  }
               }
         }
         if(strstr(satir,"\"kusatma_ustaligi\""))
         {
               while(fgets(satir,sizeof(satir),dosya))
               {
                  bosluk_sil(satir);
                  degerayir(satir,neyindegeri,deger);
                  if(strcmp(neyindegeri,"seviye_1")==0)
                  {
                     while(fgets(satir,sizeof(satir),dosya))
                     {
                           bosluk_sil(satir);
                           degerayir(satir,neyindegeri,deger);
                           if(strcmp(neyindegeri,"deger")==0)
                           {
                              research->kusatma_ustaligi.seviye_1.deger=atoi(deger);
                           }
                           else if(strcmp(neyindegeri,"aciklama")==0)
                           {
                              strcpy(research->kusatma_ustaligi.seviye_1.aciklama,deger);
                              break;
                           }
                     }
                  }
                  else if(strcmp(neyindegeri,"seviye_2")==0)
                  {
                     while(fgets(satir,sizeof(satir),dosya))
                     {
                           bosluk_sil(satir);
                           degerayir(satir,neyindegeri,deger);
                           if(strcmp(neyindegeri,"deger")==0)
                           {
                              research->kusatma_ustaligi.seviye_2.deger=atoi(deger);
                           }
                           else if(strcmp(neyindegeri,"aciklama")==0)
                           {
                              strcpy(research->kusatma_ustaligi.seviye_2.aciklama,deger);
                              break;
                           }
                     }
                  }
                  else if(strcmp(neyindegeri,"seviye_3")==0)
                  {
                     while(fgets(satir,sizeof(satir),dosya))
                     {
                           bosluk_sil(satir);
                           degerayir(satir,neyindegeri,deger);
                           if(strcmp(neyindegeri,"deger")==0)
                           {
                              research->kusatma_ustaligi.seviye_3.deger=atoi(deger);
                           }
                           else if(strcmp(neyindegeri,"aciklama")==0)
                           {
                              strcpy(research->kusatma_ustaligi.seviye_3.aciklama,deger);
                              break;
                           }
                     }
                  }
               }
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
int piyadelers_b;
int okculars;
int okculars_b;
int suvarilers;
int suvarilers_b;
int kusatma_makineleris;
int kusatma_makineleris_b;
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
  int ork_dovusculeris_b;
  int varg_binicileris;
   int varg_binicileris_b;
  int trollers;
   int trollers_b;
  int  mizrakcilars;
   int mizrakcilars_b;
  int goruk_vahsis;
  int  thruk_kemikkirans;
  int vrog_kafa_kirans;
  int ugar_zalims;
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
    g->orklar.ugar_zalims = 0;
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
         sayi->insanlar.piyadelers_b=atoi(deger);
      }
      if(strstr(satir,"okcu")!=NULL)
      {
         sayi->insanlar.okculars=atoi(deger);
         sayi->insanlar.okculars_b=atoi(deger);
      }
      if(strstr(satir,"suvariler")!=NULL)
      {
         sayi->insanlar.suvarilers=atoi(deger);
         sayi->insanlar.suvarilers_b=atoi(deger);
      }
      if(strstr(satir,"kusatma_makineleri")!=NULL)
      {
         sayi->insanlar.kusatma_makineleris=atoi(deger);
         sayi->insanlar.kusatma_makineleris_b=atoi(deger);

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
         sayi->orklar.ork_dovusculeris_b=atoi(deger);
      }
      if(strstr(satir,"varg_binicileri")!=NULL)
      {
         sayi->orklar.varg_binicileris=atoi(deger);
         sayi->orklar.varg_binicileris_b=atoi(deger);
      }
      if(strstr(satir,"troller")!=NULL)
      {
         sayi->orklar.trollers=atoi(deger);
         sayi->orklar.trollers_b=atoi(deger);
      }
      if(strstr(satir,"mizrakcilar")!=NULL)
      {
         sayi->orklar.mizrakcilars=atoi(deger);
         sayi->orklar.mizrakcilars_b=atoi(deger);
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
      if(strstr(satir,"Ugar_Zalim")!=NULL)
      {
         sayi->orklar.ugar_zalims=1;
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
   bir->insanlar.piyadeler.kritik_sans = 0;
   bir->insanlar.okcular.kritik_sans = 0;
   bir->insanlar.suvariler.kritik_sans = 0;
   bir->insanlar.kusatma_makineleri.kritik_sans = 0;
   bir->orklar.ork_dovusculeri.kritik_sans = 0;
   bir->orklar.mizrakcilar.kritik_sans = 0;
   bir->orklar.varg_binicileri.kritik_sans = 0;
   bir->orklar.troller.kritik_sans = 0;
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

      if(g->orklar.ugar_zalims==1)
      {
        if(g->orklar.ork_dovusculeris>0){
         b->orklar.ork_dovusculeri.savunma+=b->orklar.ork_dovusculeri.savunma*((h->orklar.Ugar_Zalim.bonus_degeri)/100.0);}

        if(g->orklar.mizrakcilars>0){
         b->orklar.mizrakcilar.savunma+=b->orklar.mizrakcilar.savunma*((h->orklar.Ugar_Zalim.bonus_degeri)/100.0);
        }

        if(g->orklar.trollers>0){
         b->orklar.troller.savunma+=b->orklar.troller.savunma*((h->orklar.Ugar_Zalim.bonus_degeri)/100.0);
        }

         if(g->orklar.varg_binicileris>0){
          b->orklar.varg_binicileri.savunma+=b->orklar.varg_binicileri.savunma*((h->orklar.Ugar_Zalim.bonus_degeri)/100.0);
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


int saldiri_hesapla_insan(birim_genel* b, genel_sayi* sayi) {
    int toplam_saldiri = 0;


    srand(time(NULL));

    if (sayi->insanlar.piyadelers > 0) {


            int kritik = rand() % 100;
            if (kritik < b->insanlar.piyadeler.kritik_sans) {
                toplam_saldiri += b->insanlar.piyadeler.saldiri * 1.5* sayi->insanlar.piyadelers;
            } else {
                toplam_saldiri += b->insanlar.piyadeler.saldiri* sayi->insanlar.piyadelers;
            }

    }

    if (sayi->insanlar.okculars > 0) {
            int kritik = rand() % 100;
            if (kritik < b->insanlar.okcular.kritik_sans) {

                toplam_saldiri += b->insanlar.okcular.saldiri * 1.5* sayi->insanlar.okculars;
            } else {
                toplam_saldiri += b->insanlar.okcular.saldiri* sayi->insanlar.okculars;

            }

    }

    if (sayi->insanlar.suvarilers > 0) {

            int kritik = rand() % 100;
            if (kritik < b->insanlar.suvariler.kritik_sans) {
                toplam_saldiri += b->insanlar.suvariler.saldiri * 1.5* sayi->insanlar.suvarilers;
            } else {
                toplam_saldiri += b->insanlar.suvariler.saldiri* sayi->insanlar.suvarilers;
            }

    }

    if (sayi->insanlar.kusatma_makineleris > 0) {

            int kritik = rand() % 100;
            if (kritik < b->insanlar.kusatma_makineleri.kritik_sans) {
                toplam_saldiri += b->insanlar.kusatma_makineleri.saldiri * 1.5* sayi->insanlar.kusatma_makineleris;
            } else {
                toplam_saldiri += b->insanlar.kusatma_makineleri.saldiri* sayi->insanlar.kusatma_makineleris;
            }

    }

    return toplam_saldiri;
}

int saldiri_hesapla_ork(birim_genel* b, genel_sayi* sayi) {
    int toplam_saldiri = 0;

    srand(time(NULL));

    if (sayi->orklar.ork_dovusculeris > 0) {
        int kritik = rand() % 100;
        if (kritik < b->orklar.ork_dovusculeri.kritik_sans) {
            toplam_saldiri += b->orklar.ork_dovusculeri.saldiri * 1.5 * sayi->orklar.ork_dovusculeris;
        } else {
            toplam_saldiri += b->orklar.ork_dovusculeri.saldiri * sayi->orklar.ork_dovusculeris;
        }
    }

    if (sayi->orklar.mizrakcilars > 0) {
        int kritik = rand() % 100;
        if (kritik < b->orklar.mizrakcilar.kritik_sans) {
            toplam_saldiri += b->orklar.mizrakcilar.saldiri * 1.5 * sayi->orklar.mizrakcilars;
        } else {
            toplam_saldiri += b->orklar.mizrakcilar.saldiri * sayi->orklar.mizrakcilars;
        }
    }

    if (sayi->orklar.varg_binicileris > 0) {
        int kritik = rand() % 100;
        if (kritik < b->orklar.varg_binicileri.kritik_sans) {
            toplam_saldiri += b->orklar.varg_binicileri.saldiri * 1.5 * sayi->orklar.varg_binicileris;
        } else {
            toplam_saldiri += b->orklar.varg_binicileri.saldiri * sayi->orklar.varg_binicileris;
        }
    }

    if (sayi->orklar.trollers > 0) {
        int kritik = rand() % 100;
        if (kritik < b->orklar.troller.kritik_sans) {
            toplam_saldiri += b->orklar.troller.saldiri * 1.5 * sayi->orklar.trollers;
        } else {
            toplam_saldiri += b->orklar.troller.saldiri * sayi->orklar.trollers;
        }
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



int netHasarHesapla(float saldiri, float savunma) {
    float netHasar = saldiri*(1-(savunma/saldiri));
    if (netHasar < 0) {
        netHasar = 0;
    }
    return netHasar;
}


int savasSonuKontrol(genel_sayi* insanlar, genel_sayi* orklar) {

    if (insanlar->insanlar.piyadelers == 0 && insanlar->insanlar.okculars == 0 && insanlar->insanlar.suvarilers == 0 && insanlar->insanlar.kusatma_makineleris == 0 && orklar->orklar.ork_dovusculeris == 0 && orklar->orklar.mizrakcilars == 0 && orklar->orklar.varg_binicileris == 0 && orklar->orklar.trollers == 0) {
        return 3;
    }
    if (insanlar->insanlar.piyadelers == 0 && insanlar->insanlar.okculars == 0 && insanlar->insanlar.suvarilers == 0 && insanlar->insanlar.kusatma_makineleris == 0) {

        return 1;
    }
    if (orklar->orklar.ork_dovusculeris == 0 && orklar->orklar.mizrakcilars == 0 && orklar->orklar.varg_binicileris == 0 && orklar->orklar.trollers == 0) {
        return 2;
    }

    return 0;
}


void yorgunluk(int turSayisi,int toplamSaldiri,int toplamSavunma)
{
   int yorgunluk = 1;
   int nerf= yorgunluk*(0.1);

   if(turSayisi%5==0)
   {
      toplamSaldiri-=toplamSaldiri*nerf;
      toplamSavunma-=toplamSavunma*nerf;
         yorgunluk++;
   }


}

void adimKaydet(FILE *dosya, int adimNumarasi, genel_sayi *insanlar, genel_sayi *orklar) {

    fprintf(dosya, "Adim %d:\n", adimNumarasi);
    fprintf(dosya, "Insan Imparatorlugu - Piyadeler: %d, Okcular: %d Suvariler: %d, Kusatma makineleri: %d\n", insanlar->insanlar.piyadelers, insanlar->insanlar.okculars, insanlar->insanlar.suvarilers, insanlar->insanlar.kusatma_makineleris);
    fprintf(dosya, "Ork Lejyonu - Dovusculer: %d, Mizrakcilar: %d, Varg Binicileri: %d, Troller: %d\n", orklar->orklar.ork_dovusculeris, orklar->orklar.mizrakcilars, orklar->orklar.varg_binicileris, orklar->orklar.trollers);
    fprintf(dosya, "------------------------\n");
}

void savasSonuKaydet(FILE *dosya, int kazanan) {
    if (kazanan == 1) {
        fprintf(dosya, "SavaS sona erdi. Ork Lejyonu kazandi!\n");
    } else if (kazanan == 2) {
        fprintf(dosya, "Savas sona erdi. insan imparatorlugu kazandi!\n");
    }
}



  void birimGuncelle(int* birimSayisi, birim* birlik, int netHasar, int toplamSavunma) {
    if (*birimSayisi > 0) {


        birlik->saglik -= (netHasar/ *birimSayisi);
        *birimSayisi=*birimSayisi*(birlik->saglik)/(birlik->genel_can);

        if (birlik->saglik < 0) {
            birlik->saglik = 0;
        }


        if (*birimSayisi < 0) {
            *birimSayisi = 0;
        }
    }
}

void savasRaporuYaz(FILE* dosya,int tur, int insanMevcutBirim,int insankaybedilen, int orkMevcutBirim,int orkkaybedilen) {



    fprintf(dosya, "Tur: %d\n", tur);
    fprintf(dosya, "Ýnsan Mevcut Birim Sayýsý: %d\n", insanMevcutBirim);
    fprintf(dosya,"Insan Kaybedilen Birim Sayýsý: %d\n", insankaybedilen);
    fprintf(dosya, "Ork Mevcut Birim Sayýsý: %d\n", orkMevcutBirim);
      fprintf(dosya,"Ork Kaybedilen Birim Sayýsý: %d\n", orkkaybedilen);
    fprintf(dosya, "----------------------------\n");



}

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {

        printf("bellek yetersiz (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void savas_alani_gorsellestir(int piyade_sayisi, int okcu_sayisi, int suvari_sayisi, int kusatma_makineleri_sayisi, int ork_dovusculeri_sayisi, int mizrakcilar_sayisi, int troller_sayisi, int varg_binicisi_sayisi,birim_genel* birlik,genel_sayi* sayi,int kazanan)
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Baslatilamadi!! SDL_Error: %s\n", SDL_GetError());
        return;
    }


    SDL_Window* pencere = SDL_CreateWindow("Savaþ Alaný", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 800, SDL_WINDOW_SHOWN);
    if (pencere == NULL)
    {
        printf("Pencere olusturulamadi! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }


    SDL_Renderer* renderer = SDL_CreateRenderer(pencere, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer olusturulamadi! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(pencere);
        SDL_Quit();
        return;
    }


    SDL_Surface* arkaplan_surface = SDL_LoadBMP("arkaplan.bmp");
    if (arkaplan_surface == NULL)
    {
        printf("Arkaplan goruntusu yuklenemedi! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(pencere);
        SDL_Quit();
        return;
    }
    SDL_Texture* arkaplan_texture = SDL_CreateTextureFromSurface(renderer, arkaplan_surface);
    SDL_FreeSurface(arkaplan_surface);
    if (arkaplan_texture == NULL)
    {
        printf("Arkaplan texture olusturulamadi! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(pencere);
        SDL_Quit();
        return;
    }


    SDL_RenderCopy(renderer, arkaplan_texture, NULL, NULL);


{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL baslatilamadi! SDL_Error: %s\n", SDL_GetError());
        return;
    }


    SDL_Window* pencere = SDL_CreateWindow("Savas Alani", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 800, SDL_WINDOW_SHOWN);
    if (pencere == NULL)
    {
        printf("Pencere olusturulamadi! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }


    SDL_Renderer* renderer = SDL_CreateRenderer(pencere, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer olusturulamadi! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(pencere);
        SDL_Quit();
        return;
    }


    SDL_Surface* arkaplan_surface = SDL_LoadBMP("arkaplan.bmp");
    if (arkaplan_surface == NULL)
    {
        printf("Arkaplan goruntusu yuklenemedi! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(pencere);
        SDL_Quit();
        return;
    }
    SDL_Texture* arkaplan_texture = SDL_CreateTextureFromSurface(renderer, arkaplan_surface);
    SDL_FreeSurface(arkaplan_surface);
    if (arkaplan_texture == NULL)
    {
        printf("Arkaplan texture olusturulamadi! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(pencere);
        SDL_Quit();
        return;
    }


    SDL_RenderCopy(renderer, arkaplan_texture, NULL, NULL);


    int hucre_boyutu = 40;
    int baslangic_x = 180;
    int baslangic_y = 100;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i <= 20; i++)
    {

        SDL_RenderDrawLine(renderer, baslangic_x + i * hucre_boyutu, baslangic_y, baslangic_x + i * hucre_boyutu, baslangic_y + 20 * hucre_boyutu);

        SDL_RenderDrawLine(renderer, baslangic_x, baslangic_y + i * hucre_boyutu, baslangic_x + 20 * hucre_boyutu, baslangic_y + i * hucre_boyutu);
    }


    SDL_Surface* piyade_surface = SDL_LoadBMP("piyadeler.bmp");
    SDL_Surface* okcu_surface = SDL_LoadBMP("okcu.bmp");
    SDL_Surface* suvari_surface = SDL_LoadBMP("suvari.bmp");
    SDL_Surface* kusatma_makineleri_surface = SDL_LoadBMP("kusatma_makinesi.bmp");
    SDL_Surface* ork_dovusculeri_surface = SDL_LoadBMP("ork_dovusculeri.bmp");
    SDL_Surface* mizrakcilar_surface = SDL_LoadBMP("mizrakcilar.bmp");
    SDL_Surface* troller_surface = SDL_LoadBMP("troller.bmp");
    SDL_Surface* varg_binicisi_surface = SDL_LoadBMP("varg_binicileri.bmp");

    if (piyade_surface == NULL || okcu_surface == NULL || suvari_surface == NULL || kusatma_makineleri_surface == NULL || ork_dovusculeri_surface == NULL || mizrakcilar_surface == NULL || troller_surface == NULL || varg_binicisi_surface == NULL)
    {
        printf("Goruntu yuklenemedi! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(arkaplan_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(pencere);
        SDL_Quit();
        return;
    }

    SDL_Texture* piyade_texture = SDL_CreateTextureFromSurface(renderer, piyade_surface);
    SDL_Texture* okcu_texture = SDL_CreateTextureFromSurface(renderer, okcu_surface);
    SDL_Texture* suvari_texture = SDL_CreateTextureFromSurface(renderer, suvari_surface);
    SDL_Texture* kusatma_makineleri_texture = SDL_CreateTextureFromSurface(renderer, kusatma_makineleri_surface);
    SDL_Texture* ork_dovusculeri_texture = SDL_CreateTextureFromSurface(renderer, ork_dovusculeri_surface);
    SDL_Texture* mizrakcilar_texture = SDL_CreateTextureFromSurface(renderer, mizrakcilar_surface);
    SDL_Texture* troller_texture = SDL_CreateTextureFromSurface(renderer, troller_surface);
    SDL_Texture* varg_binicisi_texture = SDL_CreateTextureFromSurface(renderer, varg_binicisi_surface);

    SDL_FreeSurface(piyade_surface);
    SDL_FreeSurface(okcu_surface);
    SDL_FreeSurface(suvari_surface);
    SDL_FreeSurface(kusatma_makineleri_surface);
    SDL_FreeSurface(ork_dovusculeri_surface);
    SDL_FreeSurface(mizrakcilar_surface);
    SDL_FreeSurface(troller_surface);
    SDL_FreeSurface(varg_binicisi_surface);

    if (piyade_texture == NULL || okcu_texture == NULL || suvari_texture == NULL || kusatma_makineleri_texture == NULL || ork_dovusculeri_texture == NULL || mizrakcilar_texture == NULL || troller_texture == NULL || varg_binicisi_texture == NULL)
    {
        printf("Texture olusturulamadi! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(arkaplan_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(pencere);
        SDL_Quit();
        return;
    }



    SDL_Rect hucre;
    hucre.w = hucre_boyutu - 12;
    hucre.h = hucre_boyutu - 8;
    int hucre_index = 0;



    while (piyade_sayisi > 0)
    {
        int birlik_sayisi = (piyade_sayisi > 100) ? 100 : piyade_sayisi;
        piyade_sayisi -= birlik_sayisi;


        hucre.x = baslangic_x + (hucre_index / 10) * hucre_boyutu + 2;
        hucre.y = baslangic_y + (hucre_index % 10) * hucre_boyutu + 2;


        SDL_RenderCopy(renderer, piyade_texture, NULL, &hucre);


        float saglik_yuzdesi = ((float)birlik->insanlar.piyadeler.saglik / (float)birlik->insanlar.piyadeler.genel_can) * 100.0;
SDL_Rect dolu_saglik_bari;
SDL_Rect eksilen_saglik_bari;

dolu_saglik_bari.x = hucre.x;
dolu_saglik_bari.y = hucre.y + hucre.h + 2;
dolu_saglik_bari.w = (hucre.w * (saglik_yuzdesi / 100));
dolu_saglik_bari.h = 5;

eksilen_saglik_bari.x = hucre.x + dolu_saglik_bari.w;
eksilen_saglik_bari.y = hucre.y + hucre.h + 2;
eksilen_saglik_bari.w = hucre.w - dolu_saglik_bari.w;
eksilen_saglik_bari.h = 5;

SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
SDL_RenderFillRect(renderer, &dolu_saglik_bari);

SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &eksilen_saglik_bari);

        hucre_index++;
    }


    hucre_index = 10;
    while (okcu_sayisi > 0)
    {
        int birlik_sayisi = (okcu_sayisi > 100) ? 100 : okcu_sayisi;
        okcu_sayisi -= birlik_sayisi;


        hucre.x = baslangic_x + (hucre_index / 10) * hucre_boyutu + 2;
        hucre.y = baslangic_y + (hucre_index % 10) * hucre_boyutu + 2;


        SDL_RenderCopy(renderer, okcu_texture, NULL, &hucre);
            float saglik_yuzdesi = ((float)birlik->insanlar.piyadeler.saglik / (float)birlik->insanlar.piyadeler.genel_can) * 100.0;
SDL_Rect dolu_saglik_bari;
SDL_Rect eksilen_saglik_bari;

dolu_saglik_bari.x = hucre.x;
dolu_saglik_bari.y = hucre.y + hucre.h + 2;
dolu_saglik_bari.w = (hucre.w * (saglik_yuzdesi / 100));
dolu_saglik_bari.h = 5;

eksilen_saglik_bari.x = hucre.x + dolu_saglik_bari.w;
eksilen_saglik_bari.y = hucre.y + hucre.h + 2;
eksilen_saglik_bari.w = hucre.w - dolu_saglik_bari.w;
eksilen_saglik_bari.h = 5;

SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
SDL_RenderFillRect(renderer, &dolu_saglik_bari);

SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &eksilen_saglik_bari);

        hucre_index++;
    }


    hucre_index = 20;
    while (suvari_sayisi > 0)
    {
        int birlik_sayisi = (suvari_sayisi > 100) ? 100 : suvari_sayisi;
        suvari_sayisi -= birlik_sayisi;


        hucre.x = baslangic_x + (hucre_index / 10) * hucre_boyutu + 2;
        hucre.y = baslangic_y + (hucre_index % 10) * hucre_boyutu + 2;


        SDL_RenderCopy(renderer, suvari_texture, NULL, &hucre);
            float saglik_yuzdesi = ((float)birlik->insanlar.piyadeler.saglik / (float)birlik->insanlar.piyadeler.genel_can) * 100.0;
SDL_Rect dolu_saglik_bari;
SDL_Rect eksilen_saglik_bari;

dolu_saglik_bari.x = hucre.x;
dolu_saglik_bari.y = hucre.y + hucre.h + 2;
dolu_saglik_bari.w = (hucre.w * (saglik_yuzdesi / 100));
dolu_saglik_bari.h = 5;

eksilen_saglik_bari.x = hucre.x + dolu_saglik_bari.w;
eksilen_saglik_bari.y = hucre.y + hucre.h + 2;
eksilen_saglik_bari.w = hucre.w - dolu_saglik_bari.w;
eksilen_saglik_bari.h = 5;

SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
SDL_RenderFillRect(renderer, &dolu_saglik_bari);

SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &eksilen_saglik_bari);

        hucre_index++;
    }


    hucre_index = 30;
    while (kusatma_makineleri_sayisi > 0)
    {
        int birlik_sayisi = (kusatma_makineleri_sayisi > 100) ? 100 : kusatma_makineleri_sayisi;
        kusatma_makineleri_sayisi -= birlik_sayisi;


        hucre.x = baslangic_x + (hucre_index / 10) * hucre_boyutu + 2;
        hucre.y = baslangic_y + (hucre_index % 10) * hucre_boyutu + 2;


        SDL_RenderCopy(renderer, kusatma_makineleri_texture, NULL, &hucre);
            float saglik_yuzdesi = ((float)birlik->insanlar.piyadeler.saglik / (float)birlik->insanlar.piyadeler.genel_can) * 100.0;
SDL_Rect dolu_saglik_bari;
SDL_Rect eksilen_saglik_bari;

dolu_saglik_bari.x = hucre.x;
dolu_saglik_bari.y = hucre.y + hucre.h + 2;
dolu_saglik_bari.w = (hucre.w * (saglik_yuzdesi / 100));
dolu_saglik_bari.h = 5;

eksilen_saglik_bari.x = hucre.x + dolu_saglik_bari.w;
eksilen_saglik_bari.y = hucre.y + hucre.h + 2;
eksilen_saglik_bari.w = hucre.w - dolu_saglik_bari.w;
eksilen_saglik_bari.h = 5;

SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
SDL_RenderFillRect(renderer, &dolu_saglik_bari);

SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &eksilen_saglik_bari);

        hucre_index++;
    }


    int ork_baslangic_x = baslangic_x + 400;


    hucre_index = 0;
    while (ork_dovusculeri_sayisi > 0)
    {
        int birlik_sayisi = (ork_dovusculeri_sayisi > 100) ? 100 : ork_dovusculeri_sayisi;
        ork_dovusculeri_sayisi -= birlik_sayisi;


        hucre.x = ork_baslangic_x + (hucre_index / 10) * hucre_boyutu + 5;
        hucre.y = baslangic_y + (hucre_index % 10) * hucre_boyutu + 5;


        SDL_RenderCopy(renderer, ork_dovusculeri_texture, NULL, &hucre);
            float saglik_yuzdesi = ((float)birlik->insanlar.piyadeler.saglik / (float)birlik->insanlar.piyadeler.genel_can) * 100.0;
SDL_Rect dolu_saglik_bari;
SDL_Rect eksilen_saglik_bari;

dolu_saglik_bari.x = hucre.x;
dolu_saglik_bari.y = hucre.y + hucre.h + 2;
dolu_saglik_bari.w = (hucre.w * (saglik_yuzdesi / 100));
dolu_saglik_bari.h = 5;

eksilen_saglik_bari.x = hucre.x + dolu_saglik_bari.w;
eksilen_saglik_bari.y = hucre.y + hucre.h + 2;
eksilen_saglik_bari.w = hucre.w - dolu_saglik_bari.w;
eksilen_saglik_bari.h = 5;

SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
SDL_RenderFillRect(renderer, &dolu_saglik_bari);

SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &eksilen_saglik_bari);

        hucre_index++;
    }


    hucre_index = 10;
    while (mizrakcilar_sayisi > 0)
    {
        int birlik_sayisi = (mizrakcilar_sayisi > 100) ? 100 : mizrakcilar_sayisi;
        mizrakcilar_sayisi -= birlik_sayisi;


        hucre.x = ork_baslangic_x + (hucre_index / 10) * hucre_boyutu + 5;
        hucre.y = baslangic_y + (hucre_index % 10) * hucre_boyutu + 5;


        SDL_RenderCopy(renderer, mizrakcilar_texture, NULL, &hucre);
            float saglik_yuzdesi = ((float)birlik->insanlar.piyadeler.saglik / (float)birlik->insanlar.piyadeler.genel_can) * 100.0;
SDL_Rect dolu_saglik_bari;
SDL_Rect eksilen_saglik_bari;

dolu_saglik_bari.x = hucre.x;
dolu_saglik_bari.y = hucre.y + hucre.h + 2;
dolu_saglik_bari.w = (hucre.w * (saglik_yuzdesi / 100));
dolu_saglik_bari.h = 5;

eksilen_saglik_bari.x = hucre.x + dolu_saglik_bari.w;
eksilen_saglik_bari.y = hucre.y + hucre.h + 2;
eksilen_saglik_bari.w = hucre.w - dolu_saglik_bari.w;
eksilen_saglik_bari.h = 5;

SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
SDL_RenderFillRect(renderer, &dolu_saglik_bari);

SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &eksilen_saglik_bari);
        hucre_index++;
    }


    hucre_index = 20;
    while (troller_sayisi > 0)
    {
        int birlik_sayisi = (troller_sayisi > 100) ? 100 : troller_sayisi;
        troller_sayisi -= birlik_sayisi;


        hucre.x = ork_baslangic_x + (hucre_index / 10) * hucre_boyutu + 5;
        hucre.y = baslangic_y + (hucre_index % 10) * hucre_boyutu + 5;


        SDL_RenderCopy(renderer, troller_texture, NULL, &hucre);
            float saglik_yuzdesi = ((float)birlik->insanlar.piyadeler.saglik / (float)birlik->insanlar.piyadeler.genel_can) * 100.0;
SDL_Rect dolu_saglik_bari;
SDL_Rect eksilen_saglik_bari;

dolu_saglik_bari.x = hucre.x;
dolu_saglik_bari.y = hucre.y + hucre.h + 2;
dolu_saglik_bari.w = (hucre.w * (saglik_yuzdesi / 100));
dolu_saglik_bari.h = 5;

eksilen_saglik_bari.x = hucre.x + dolu_saglik_bari.w;
eksilen_saglik_bari.y = hucre.y + hucre.h + 2;
eksilen_saglik_bari.w = hucre.w - dolu_saglik_bari.w;
eksilen_saglik_bari.h = 5;

SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
SDL_RenderFillRect(renderer, &dolu_saglik_bari);

SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &eksilen_saglik_bari);
        hucre_index++;
    }


    hucre_index = 30;
    while (varg_binicisi_sayisi > 0)
    {
        int birlik_sayisi = (varg_binicisi_sayisi > 100) ? 100 : varg_binicisi_sayisi;
        varg_binicisi_sayisi -= birlik_sayisi;


        hucre.x = ork_baslangic_x + (hucre_index / 10) * hucre_boyutu + 5;
        hucre.y = baslangic_y + (hucre_index % 10) * hucre_boyutu + 5;


        SDL_RenderCopy(renderer, varg_binicisi_texture, NULL, &hucre);
            float saglik_yuzdesi = ((float)birlik->insanlar.piyadeler.saglik / (float)birlik->insanlar.piyadeler.genel_can) * 100.0;
SDL_Rect dolu_saglik_bari;
SDL_Rect eksilen_saglik_bari;

dolu_saglik_bari.x = hucre.x;
dolu_saglik_bari.y = hucre.y + hucre.h + 2;
dolu_saglik_bari.w = (hucre.w * (saglik_yuzdesi / 100));
dolu_saglik_bari.h = 5;

eksilen_saglik_bari.x = hucre.x + dolu_saglik_bari.w;
eksilen_saglik_bari.y = hucre.y + hucre.h + 2;
eksilen_saglik_bari.w = hucre.w - dolu_saglik_bari.w;
eksilen_saglik_bari.h = 5;

SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
SDL_RenderFillRect(renderer, &dolu_saglik_bari);

SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &eksilen_saglik_bari);

        hucre_index++;
    }


    SDL_Surface* kahraman_surface = NULL;
    SDL_Texture* kahraman_texture = NULL;
    SDL_Rect kahraman_rect;


    kahraman_rect.x = 50;
    kahraman_rect.y = 150;
    kahraman_rect.w = 100;
    kahraman_rect.h = 100;

    if (sayi->insanlar.alparslans == 1) {
        kahraman_surface = SDL_LoadBMP("Alparslan.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if (sayi->insanlar.fatih_sultan_mehmets == 1) {
        kahraman_surface = SDL_LoadBMP("Fatih_Sultan_Mehmet.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if (sayi->insanlar.mete_hans == 1) {
        kahraman_surface = SDL_LoadBMP("Mete_Han.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if (sayi->insanlar.yavuz_sultan_selims == 1) {
        kahraman_surface = SDL_LoadBMP("Yavuz_Sultan_Selim.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if (sayi->insanlar.tugrul_beys == 1) {
        kahraman_surface = SDL_LoadBMP("Tugrul_Bey.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if(sayi->insanlar.ejderhas == 1) {
        kahraman_surface = SDL_LoadBMP("ejderha.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if(sayi->insanlar.agri_dagi_devleris == 1) {
        kahraman_surface = SDL_LoadBMP("agri_dagi_devleri.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if(sayi->insanlar.tepegozs == 1) {
        kahraman_surface = SDL_LoadBMP("tepegoz.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if(sayi->insanlar.karakurts == 1) {
        kahraman_surface = SDL_LoadBMP("karakurt.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if(sayi->insanlar.samurs == 1) {
        kahraman_surface = SDL_LoadBMP("samur.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }



    kahraman_rect.x = 1000;
    kahraman_rect.y = 150;

    if (sayi->orklar.goruk_vahsis == 1) {
        kahraman_surface = SDL_LoadBMP("Goruk_Vahsi.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if (sayi->orklar.thruk_kemikkirans == 1) {
        kahraman_surface = SDL_LoadBMP("Thruk_Kemikkiran.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if (sayi->orklar.vrog_kafa_kirans == 1) {
        kahraman_surface = SDL_LoadBMP("Vrog_Kafakiran.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if (sayi->orklar.ugar_zalims == 1) {
        kahraman_surface = SDL_LoadBMP("Ugar_Zalim.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if (sayi->orklar.kara_trolls == 1) {
        kahraman_surface = SDL_LoadBMP("Kara_Troll.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if(sayi->orklar.golge_kurtlaris == 1) {
        kahraman_surface = SDL_LoadBMP("golge_kurtlari.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if(sayi->orklar.camur_devleris == 1) {
        kahraman_surface = SDL_LoadBMP("camur_devi.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if(sayi->orklar.ates_iblisis == 1) {
        kahraman_surface = SDL_LoadBMP("ates_iblisi.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if(sayi->orklar.makrog_savas_beyis == 1) {
        kahraman_surface = SDL_LoadBMP("makrog_savas_beyi.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }
    if(sayi->orklar.buz_devleris == 1) {
        kahraman_surface = SDL_LoadBMP("buz_devleri.bmp");
        kahraman_texture = SDL_CreateTextureFromSurface(renderer, kahraman_surface);
        SDL_FreeSurface(kahraman_surface);
        SDL_RenderCopy(renderer, kahraman_texture, NULL, &kahraman_rect);
        SDL_DestroyTexture(kahraman_texture);
        kahraman_rect.y += 120;
    }


SDL_Surface* kazanan_surface = NULL;
SDL_Texture* kazanan_texture = NULL;
if (kazanan==3)
{
    kazanan_surface = SDL_LoadBMP("berabere.bmp");
}
if (kazanan == 2) {
    kazanan_surface = SDL_LoadBMP("kazan_insan.bmp");
} else if (kazanan == 1) {
    kazanan_surface = SDL_LoadBMP("kazan_ork.bmp");
}

if (kazanan_surface != NULL) {
    kazanan_texture = SDL_CreateTextureFromSurface(renderer, kazanan_surface);
    SDL_FreeSurface(kazanan_surface);
    SDL_Rect kazanan_rect = {450, 30, 300, 100};
    SDL_RenderCopy(renderer, kazanan_texture, NULL, &kazanan_rect);
    SDL_DestroyTexture(kazanan_texture);
    SDL_RenderPresent(renderer);
}


    SDL_RenderPresent(renderer);




    SDL_Delay(5000);


    SDL_DestroyTexture(piyade_texture);
    SDL_DestroyTexture(okcu_texture);
    SDL_DestroyTexture(suvari_texture);
    SDL_DestroyTexture(kusatma_makineleri_texture);
    SDL_DestroyTexture(ork_dovusculeri_texture);
    SDL_DestroyTexture(mizrakcilar_texture);
    SDL_DestroyTexture(troller_texture);
    SDL_DestroyTexture(varg_binicisi_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(pencere);
    SDL_Quit();
}
}



int main(int argc, char* argv[]) {





 char url[256];
    const char *dosya_adi = "indirilen_dosya.json";

    printf("Lütfen indirmek istediginiz JSON dosyasinin URL'sini girin: ");
    fgets(url, sizeof(url), stdin);

    url[strcspn(url, "\n")] = 0;

    char komut[512];
    snprintf(komut, sizeof(komut), "curl -o %s %s", dosya_adi, url);

    int sonuc = system(komut);

    if (sonuc != 0) {
        printf("Dosya indirilemedi.\n");
        return 1;
    }

    FILE *senaryolar_dosya = fopen(dosya_adi, "r");
    if (senaryolar_dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return 1;
    }


    FILE* heroes_dosya = fopen("heroes.json", "r");
    FILE* research_dosya = fopen("research.json", "r");
    FILE* unit_types_dosya = fopen("unit_types.json", "r");
    FILE* creatures_dosya = fopen("creatures.json", "r");
    FILE* savas_sim_dosya = fopen("savas_sim.txt", "w");


      if (heroes_dosya == NULL || research_dosya == NULL || unit_types_dosya == NULL || creatures_dosya == NULL || senaryolar_dosya == NULL) {
         printf("Dosya acilamadi\n");
         return 1;
        }else printf("Dosyalar acildi\n");

        bonuslar bonuslar;
       arastirma_tarafi arastirmat;
      genel_sayi sayilarim;
       birim_genel bir;
        heroes_genel kahramanlar;
        research_turleri arastirma;
        birim_genel birimlerG;

         creatures_genel creaturesG;




         varsayilan_deger(&birimlerG);


         deger_ata_research(&arastirma, research_dosya);


         deger_ata_heroes(&kahramanlar, heroes_dosya);
         deger_ata_creatures(&creaturesG, creatures_dosya);

        deger_ata_unit_types(&birimlerG, unit_types_dosya);


         sifirla(&sayilarim,&arastirma);
        senaryo_oku(senaryolar_dosya,&sayilarim,&arastirmat);

int turSayisi = 0;
   int kazanan = 0;

    savas_alani_gorsellestir(sayilarim.insanlar.piyadelers, sayilarim.insanlar.okculars, sayilarim.insanlar.suvarilers, sayilarim.insanlar.kusatma_makineleris, sayilarim.orklar.ork_dovusculeris, sayilarim.orklar.mizrakcilars, sayilarim.orklar.trollers, sayilarim.orklar.varg_binicileris,&birimlerG,&sayilarim,kazanan);

     creatures_bonus(&sayilarim, &birimlerG,&creaturesG);

      heroes_bonus(&sayilarim, &birimlerG, &kahramanlar);

     kusatma_ustaligi(&arastirmat, &sayilarim, &birimlerG, &arastirma);


      saldiri_gelistirmesi(&arastirmat, &sayilarim, &arastirma,&birimlerG);


      savunma_ustaligi(&arastirmat, &arastirma, &sayilarim, &birimlerG);


     elit_egitim(&arastirmat, &sayilarim, &birimlerG);

   int insan_kaybedilen_birim_sayisi = 0;
   int ork_kaybedilen_birim_sayisi = 0;
    int insan_toplam_birim_sayisi = sayilarim.insanlar.piyadelers + sayilarim.insanlar.okculars + sayilarim.insanlar.suvarilers + sayilarim.insanlar.kusatma_makineleris;
      int ork_toplam_birim_sayisi = sayilarim.orklar.ork_dovusculeris + sayilarim.orklar.mizrakcilars + sayilarim.orklar.varg_binicileris + sayilarim.orklar.trollers;


  while(kazanan==0){







  savasRaporuYaz(savas_sim_dosya, turSayisi,insan_toplam_birim_sayisi,insan_kaybedilen_birim_sayisi,ork_toplam_birim_sayisi,ork_kaybedilen_birim_sayisi);



     insan_toplam_birim_sayisi = sayilarim.insanlar.piyadelers + sayilarim.insanlar.okculars + sayilarim.insanlar.suvarilers + sayilarim.insanlar.kusatma_makineleris;
     ork_toplam_birim_sayisi = sayilarim.orklar.ork_dovusculeris + sayilarim.orklar.mizrakcilars + sayilarim.orklar.varg_binicileris + sayilarim.orklar.trollers;

      turSayisi++;





       int insanSaldiri = saldiri_hesapla_insan(&birimlerG, &sayilarim);
      int orkSaldiri = saldiri_hesapla_ork(&birimlerG, &sayilarim);
      int insanSavunma = savunma_hesapla_insan(&birimlerG, &sayilarim);
      int orkSavunma = savunma_hesapla_ork(&birimlerG, &sayilarim);



      yorgunluk(turSayisi,insanSaldiri,insanSavunma);


      int orkNetHasar = netHasarHesapla(orkSaldiri, insanSavunma);

      int insanNetHasar = netHasarHesapla(insanSaldiri, orkSavunma);









if (sayilarim.insanlar.piyadelers > 0) {
    birimGuncelle(&sayilarim.insanlar.piyadelers, &birimlerG.insanlar.piyadeler, orkNetHasar, insanSavunma);

}

if (sayilarim.insanlar.okculars > 0) {
    birimGuncelle(&sayilarim.insanlar.okculars, &birimlerG.insanlar.okcular, orkNetHasar, insanSavunma);
}


if (sayilarim.insanlar.suvarilers > 0) {
    birimGuncelle(&sayilarim.insanlar.suvarilers, &birimlerG.insanlar.suvariler, orkNetHasar, insanSavunma);
}


if (sayilarim.insanlar.kusatma_makineleris > 0) {
    birimGuncelle(&sayilarim.insanlar.kusatma_makineleris, &birimlerG.insanlar.kusatma_makineleri, orkNetHasar, insanSavunma);
}


if (sayilarim.orklar.ork_dovusculeris > 0) {
    birimGuncelle(&sayilarim.orklar.ork_dovusculeris, &birimlerG.orklar.ork_dovusculeri, insanNetHasar, orkSavunma);
}


if (sayilarim.orklar.mizrakcilars > 0) {
    birimGuncelle(&sayilarim.orklar.mizrakcilars, &birimlerG.orklar.mizrakcilar, insanNetHasar, orkSavunma);
}


if (sayilarim.orklar.varg_binicileris > 0) {
    birimGuncelle(&sayilarim.orklar.varg_binicileris, &birimlerG.orklar.varg_binicileri, insanNetHasar, orkSavunma);
}


if (sayilarim.orklar.trollers > 0) {
    birimGuncelle(&sayilarim.orklar.trollers, &birimlerG.orklar.troller, insanNetHasar, orkSavunma);
}
     insan_kaybedilen_birim_sayisi=insan_toplam_birim_sayisi-sayilarim.insanlar.piyadelers-sayilarim.insanlar.okculars-sayilarim.insanlar.suvarilers-sayilarim.insanlar.kusatma_makineleris;
     ork_kaybedilen_birim_sayisi=ork_toplam_birim_sayisi-sayilarim.orklar.ork_dovusculeris-sayilarim.orklar.mizrakcilars-sayilarim.orklar.varg_binicileris-sayilarim.orklar.trollers;


      kazanan = savasSonuKontrol(&sayilarim, &sayilarim);
      if(kazanan==3)
      {
          savasRaporuYaz(savas_sim_dosya, turSayisi,insan_toplam_birim_sayisi,insan_kaybedilen_birim_sayisi,ork_toplam_birim_sayisi,ork_kaybedilen_birim_sayisi);
        savas_alani_gorsellestir(sayilarim.insanlar.piyadelers, sayilarim.insanlar.okculars, sayilarim.insanlar.suvarilers, sayilarim.insanlar.kusatma_makineleris, sayilarim.orklar.ork_dovusculeris, sayilarim.orklar.mizrakcilars, sayilarim.orklar.trollers, sayilarim.orklar.varg_binicileris,&birimlerG,&sayilarim,kazanan);
         printf("Berabere\n");

         fclose(heroes_dosya);
         fclose(research_dosya);
         fclose(unit_types_dosya);
         fclose(creatures_dosya);
         fclose(senaryolar_dosya);
         fclose(savas_sim_dosya);
         break;
      }
      if(kazanan==1)
      {
          savasRaporuYaz(savas_sim_dosya, turSayisi,insan_toplam_birim_sayisi,insan_kaybedilen_birim_sayisi,ork_toplam_birim_sayisi,ork_kaybedilen_birim_sayisi);
    savas_alani_gorsellestir(sayilarim.insanlar.piyadelers, sayilarim.insanlar.okculars, sayilarim.insanlar.suvarilers, sayilarim.insanlar.kusatma_makineleris, sayilarim.orklar.ork_dovusculeris, sayilarim.orklar.mizrakcilars, sayilarim.orklar.trollers, sayilarim.orklar.varg_binicileris,&birimlerG,&sayilarim,kazanan);
         printf("Orklar kazandi\n");


         fclose(heroes_dosya);
         fclose(research_dosya);
         fclose(unit_types_dosya);
         fclose(creatures_dosya);
         fclose(senaryolar_dosya);
         fclose(savas_sim_dosya);

         break;
      }
      if(kazanan==2)
      {
savasRaporuYaz(savas_sim_dosya, turSayisi,insan_toplam_birim_sayisi,insan_kaybedilen_birim_sayisi,ork_toplam_birim_sayisi,ork_kaybedilen_birim_sayisi);
    savas_alani_gorsellestir(sayilarim.insanlar.piyadelers, sayilarim.insanlar.okculars, sayilarim.insanlar.suvarilers, sayilarim.insanlar.kusatma_makineleris, sayilarim.orklar.ork_dovusculeris, sayilarim.orklar.mizrakcilars, sayilarim.orklar.trollers, sayilarim.orklar.varg_binicileris,&birimlerG,&sayilarim,kazanan);
         printf("Insanlar kazandi\n %d",turSayisi);

         fclose(heroes_dosya);
         fclose(research_dosya);
         fclose(unit_types_dosya);
         fclose(creatures_dosya);
         fclose(senaryolar_dosya);
         fclose(savas_sim_dosya);
         break;
      }

      if(turSayisi==500)
      {
    savas_alani_gorsellestir(sayilarim.insanlar.piyadelers, sayilarim.insanlar.okculars, sayilarim.insanlar.suvarilers, sayilarim.insanlar.kusatma_makineleris, sayilarim.orklar.ork_dovusculeris, sayilarim.orklar.mizrakcilars, sayilarim.orklar.trollers, sayilarim.orklar.varg_binicileris,&birimlerG,&sayilarim,kazanan);
         printf("Berabere\n");

         fclose(heroes_dosya);
         fclose(research_dosya);
         fclose(unit_types_dosya);
         fclose(creatures_dosya);
         fclose(senaryolar_dosya);
         fclose(savas_sim_dosya);
         break;
      }
  }

















     return 0;
    }
