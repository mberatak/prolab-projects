import java.util.List;
import java.util.ArrayList;

public class Oyuncu {
    private int oyuncuID;
    private String oyuncuAdi;
    private int skor;
    private List<SavasAraclari> kartListesi;


    public Oyuncu(int oyuncuID, String oyuncuAdi) {
        this.oyuncuID = oyuncuID;
        this.oyuncuAdi = oyuncuAdi;
        this.skor = 0;
        this.kartListesi = new ArrayList<>();
    }


    public int getOyuncuID() {
        return oyuncuID;
    }

    public void setOyuncuID(int oyuncuID) {
        this.oyuncuID = oyuncuID;
    }

    public String getOyuncuAdi() {
        return oyuncuAdi;
    }

    public void setOyuncuAdi(String oyuncuAdi) {
        this.oyuncuAdi = oyuncuAdi;
    }

    public int getSkor() {
        return skor;
    }

    public void setSkor(int skor) {
        this.skor = skor;
    }

    public List<SavasAraclari> getKartListesi() {
        return kartListesi;
    }

    public void setKartListesi(List<SavasAraclari> kartListesi) {
        this.kartListesi = kartListesi;
    }


    public void kartEkle(SavasAraclari kart) {
        this.kartListesi.add(kart);
    }

    public void SkorGoster() {
        System.out.println(oyuncuAdi + " - Skor: " + skor);
    }

    public void kartSec(SavasAraclari kart) {
    }
}
