import javax.swing.*;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Oyun {
    private Oyuncu oyuncu;
    private Oyuncu bilgisayar;
    public int toplamHamleSayisi;
    public int mevcutHamle;
    private Random rand;
    public int baslangicpuan;
    private BufferedWriter logWriter;


    public Oyun(Oyuncu oyuncu, Oyuncu bilgisayar,int toplamHamleSayisi,int baslangicpuan) {
        this.oyuncu = oyuncu;
        this.bilgisayar = bilgisayar;
        this.toplamHamleSayisi = toplamHamleSayisi;
        this.mevcutHamle = 0;
        this.rand = new Random();
        this.baslangicpuan=baslangicpuan;
        baslangicKartDagitimi();

        try {
            logWriter = new BufferedWriter(new FileWriter("oyun_log.txt"));
            logWriter.write("Oyun basladi\n");
        } catch (IOException e) {
            System.out.println("Dosya olusturulamadi: " + e.getMessage());
        }
    }

    public void baslangicKartDagitimi() {
        for (int i = 0; i < 6; i++) {
            oyuncu.getKartListesi().add(rastgeleKartOlustur(false));
            bilgisayar.getKartListesi().add(rastgeleKartOlustur(false));
        }
    }

    public SavasAraclari rastgeleKartOlustur(boolean yirmiPuanaUlasildi) {
        int kartTipi = rand.nextInt(yirmiPuanaUlasildi ? 6 : 3);
        switch (kartTipi) {
            case 0:
                return new Ucak(baslangicpuan);
            case 1:
                return new Obus(baslangicpuan);
            case 2:
                return new Firkateyn(baslangicpuan);
            case 3:
                return new Siha(baslangicpuan);
            case 4:
                return new Sida(baslangicpuan);
            case 5:
                return new KFS(baslangicpuan);
            default:
                throw new IllegalStateException("Beklenmeyen kart tipi: " + kartTipi);
        }
    }

    public void kartSeviyePuaniAta(int a){

    }

    public void adimKaydet(Oyuncu saldiran, Oyuncu savunan, SavasAraclari saldiranKart, SavasAraclari savunanKart, int vurulanHasar, String saldiriYapan) {
        try {
            logWriter.write(saldiriYapan + " " + saldiran.getOyuncuAdi() + " kartı: " + saldiranKart.KartAdiGoster() + " - Verilen Hasar: " + vurulanHasar +
                    " - " + savunan.getOyuncuAdi() + " kartı: " + savunanKart.KartAdiGoster() + " (Kalan Dayanıklılık: " + savunanKart.getDayaniklilik() + ")\n");

            logWriter.flush();

        } catch (IOException e) {
            System.out.println("Adım kaydedilemedi: " + e.getMessage());
        }
    }

    private boolean oyunBitti() {

        return oyuncu.getKartListesi().isEmpty() || bilgisayar.getKartListesi().isEmpty() || mevcutHamle==toplamHamleSayisi;
    }



    public List<SavasAraclari> kartSec(Oyuncu oyuncu) {
        List<SavasAraclari> secilenKartlar = new ArrayList<>();
        List<SavasAraclari> kartListesi = new ArrayList<>(oyuncu.getKartListesi());
        if (secilenKartlar.size() == oyuncu.getKartListesi().size()) {
            // Eğer eldeki tüm kartlar seçildiyse, seçimler sıfırlanır ve tekrar seçilebilir hale gelir
            secilenKartlar.clear();
        }
        Collections.shuffle(kartListesi);
        for (int i = 0; i < 3 && i < kartListesi.size(); i++) {
            secilenKartlar.add(kartListesi.get(i));
        }
        return secilenKartlar;
    }

    private List<SavasAraclari> oyuncuKartSec() {
        List<SavasAraclari> secilenKartlar = new ArrayList<>();
        System.out.println("Mevcut Kartlar: ");
        for (int i = 0; i < oyuncu.getKartListesi().size(); i++) {
            System.out.println((i + 1) + ". " + oyuncu.getKartListesi().get(i).KartAdiGoster());
        }
        Scanner scanner = new Scanner(System.in);
        while (secilenKartlar.size() < 3) {
            System.out.print("Lütfen seçmek istediğiniz kart numarasını girin (1-" + oyuncu.getKartListesi().size() + "): ");
            int secim = scanner.nextInt() - 1;
            if (secim >= 0 && secim < oyuncu.getKartListesi().size()) {
                SavasAraclari secilenKart = oyuncu.getKartListesi().get(secim);
                if (!secilenKartlar.contains(secilenKart) && !oyuncu.getKartListesi().isEmpty()) {
                    secilenKartlar.add(secilenKart);
                } else {
                    System.out.println("Bu kartı zaten seçtiniz, başka bir kart seçin.");
                }
            } else {
                System.out.println("Geçersiz seçim, lütfen tekrar deneyin.");
            }
        }
        return secilenKartlar;
    }

    public boolean tumKartlarKullanildiMi() {
        for (SavasAraclari kart : oyuncu.getKartListesi()) {

            if (!kart.isKullanildiMi()) {
                return false;
            }
        }
        return true;
    }

    private void oyunuSonlandir() {
        try {
            logWriter.write("Oyun sona erdi.\n");
            oyuncu.SkorGoster();
            bilgisayar.SkorGoster();
            if (oyuncu.getSkor() > bilgisayar.getSkor()) {
                logWriter.write(oyuncu.getOyuncuAdi() + " kazandı!\n");
            } else if (bilgisayar.getSkor() > oyuncu.getSkor()) {
                logWriter.write(bilgisayar.getOyuncuAdi() + " kazandı!\n");
            } else {
                logWriter.write("Oyun berabere!\n");
            }
            logWriter.flush();
            logWriter.close();
        } catch (IOException e) {
            System.out.println("Oyun sonlandirilamadi: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {

            JTextField maxRoundField = new JTextField();
            JTextField kartSeviyePuaniField = new JTextField();
            Object[] message = {
                    "Max Round Sayısı:", maxRoundField,
                    "Kart Seviye Puanı:", kartSeviyePuaniField
            };
            int option = JOptionPane.showConfirmDialog(null, message, "Oyun Ayarları", JOptionPane.OK_CANCEL_OPTION);
            if (option != JOptionPane.OK_OPTION) {
                System.exit(0);
            }

            int maxRound;
            int kartSeviyePuani;
            try {
                maxRound = Integer.parseInt(maxRoundField.getText());
                kartSeviyePuani = Integer.parseInt(kartSeviyePuaniField.getText());
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(null, "Lütfen geçerli bir sayı girin!", "Hata", JOptionPane.ERROR_MESSAGE);
                System.exit(0);
                return;
            }

            Oyuncu oyuncu = new Oyuncu(1, "Kullanıcı");
            Oyuncu bilgisayar = new Oyuncu(2, "Bilgisayar");
            // Başlangıç kartları Oyun sınıfındaki dağıtım yöntemi ile verilecek

            Oyun oyun = new Oyun(oyuncu, bilgisayar, maxRound,kartSeviyePuani);




            KartOyunuGorsel oyunGorsel = new KartOyunuGorsel(oyuncu, bilgisayar,oyun);
            oyunGorsel.setVisible(true);
        });
    }

}



