public abstract class SavasAraclari {
    private int dayaniklilik;
    private int seviyePuani;
    private String sinif;
    private int vurus;


    // yapici
    public SavasAraclari(int dayaniklilik, int seviyePuani, String sinif, int vurus) {
        this.dayaniklilik = dayaniklilik;
        this.seviyePuani = seviyePuani;
        this.sinif = sinif;
        this.vurus = vurus;
    }


    public int getDayaniklilik() {
        return dayaniklilik;
    }

    public void setDayaniklilik(int dayaniklilik) {
        this.dayaniklilik = dayaniklilik;
    }

    public int getSeviyePuani() {
        return seviyePuani;
    }

    public void setSeviyePuani(int seviyePuani) {
        this.seviyePuani = seviyePuani;
    }

    public String getSinif() {
        return sinif;
    }

    public void setSinif(String sinif) {
        this.sinif = sinif;
    }

    public int getVurus() {
        return vurus;
    }

    public void setVurus(int vurus) {
        this.vurus = vurus;
    }

    public abstract int SaldiriHesapla(SavasAraclari rakip);
    public void DurumGuncelle(int hasar) {
        this.dayaniklilik -= hasar;
        if (dayaniklilik < 0) {
            dayaniklilik = 0;
        }
    }

    private boolean kullanildiMi = false; // kartın kullanılıp kullanılmadığı


    public boolean isKullanildiMi() {
        return kullanildiMi;
    }

    public void setKullanildiMi(boolean kullanildiMi) {
        this.kullanildiMi = kullanildiMi;
    }

    public abstract String KartAdiGoster();
    public abstract void KartPuaniGoster();
    public abstract String getKartGorselYolu();

}
