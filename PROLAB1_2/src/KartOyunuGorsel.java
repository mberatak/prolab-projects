import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class KartOyunuGorsel extends JFrame {
    private JPanel bilgisayarKartlarPanel;
    private JPanel oyuncuKartlarPanel;
    private JPanel secilenKartlarPanel;
    private JPanel skorPanel;
    private JLabel oyuncuSkorLabel;
    private JLabel bilgisayarSkorLabel;
    private JButton savasButonu;
    private JButton sonrakiAdimButonu;
    private List<JButton> kullaniciKartButonlari;
    private List<SavasAraclari> oyuncuSecilenKartlar;
    private Oyuncu oyuncu;
    private Oyuncu bilgisayar;
    private Oyun oyun;


    public KartOyunuGorsel(Oyuncu oyuncu, Oyuncu bilgisayar,Oyun oyun) {
        this.oyuncu = oyuncu;
        this.bilgisayar = bilgisayar;
        this.oyun=oyun;
        setTitle("Kart Oyunu Görselleştirme");
        setSize(1200, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout(10, 10));

        oyuncuSecilenKartlar = new ArrayList<>();
        kullaniciKartButonlari = new ArrayList<>();


        // Bilgisayar Kartları (üst kısım)

        bilgisayarKartlarPanel = new JPanel();
        bilgisayarKartlarPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));
        bilgisayarKartlarPanel.setPreferredSize(new Dimension(1200, 150));
        bilgisayarKartlarPanel.setBorder(BorderFactory.createTitledBorder("Bilgisayar Kartları"));
        guncelleBilgisayarKartlariPanel();
        add(bilgisayarKartlarPanel, BorderLayout.NORTH);

        // Seçilen Kartlar (orta kısım)
        secilenKartlarPanel = new JPanel();
        secilenKartlarPanel.setLayout(new GridLayout(2, 3, 10, 10));
        secilenKartlarPanel.setPreferredSize(new Dimension(1200, 300));
        secilenKartlarPanel.setBorder(BorderFactory.createTitledBorder("Seçilen Kartlar"));
        add(secilenKartlarPanel, BorderLayout.CENTER);

        // Kullanıcı Kartları (alt kısım)
        oyuncuKartlarPanel = new JPanel();
        oyuncuKartlarPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));
        oyuncuKartlarPanel.setPreferredSize(new Dimension(1200, 150));
        oyuncuKartlarPanel.setBorder(BorderFactory.createTitledBorder("Kullanıcı Kartları"));
        guncelleOyuncuKartlariPanel();
        add(oyuncuKartlarPanel, BorderLayout.SOUTH);

        // Skor Paneli (sağ üst köşe)
        skorPanel = new JPanel();
        skorPanel.setLayout(new GridLayout(2, 1));
        skorPanel.setPreferredSize(new Dimension(200, 100));
        skorPanel.setBorder(BorderFactory.createTitledBorder("Skorlar"));
        oyuncuSkorLabel = new JLabel("Kullanıcı Skoru: " + oyuncu.getSkor());
        bilgisayarSkorLabel = new JLabel("Bilgisayar Skoru: " + bilgisayar.getSkor());
        skorPanel.add(oyuncuSkorLabel);
        skorPanel.add(bilgisayarSkorLabel);
        add(skorPanel, BorderLayout.NORTH);

        // Savaşı Başlat Butonu
        savasButonu = new JButton("Savaşı Başlat");
        savasButonu.setEnabled(false);
        savasButonu.addActionListener(new SavasBaslatListener());
        add(savasButonu, BorderLayout.EAST);

        // Sonraki Adım Butonu
        sonrakiAdimButonu = new JButton("Sonraki Adım");
        sonrakiAdimButonu.setEnabled(false);
        sonrakiAdimButonu.addActionListener(new SonrakiAdimListener());
        add(sonrakiAdimButonu, BorderLayout.WEST);
    }


    private class KartSecimListener implements ActionListener {
        private SavasAraclari kart;

        public KartSecimListener(SavasAraclari kart) {
            this.kart = kart;
        }

        @Override
        public void actionPerformed(ActionEvent e) {

            if (oyuncuSecilenKartlar.size() < 3) {
                if (kart.isKullanildiMi() && !oyun.tumKartlarKullanildiMi()) {
                    JOptionPane.showMessageDialog(null, "Bu kart daha önce kullanıldı! Öncelikle kullanmadığınız kartları seçiniz.", "Uyarı", JOptionPane.WARNING_MESSAGE);
                    return;
                }
                
                oyuncuSecilenKartlar.add(kart);
                JButton buton = (JButton) e.getSource();
                buton.setEnabled(false);
                buton.setBackground(new Color(200, 200, 200));  // soluk
                secilenKartlarPanel.add(new JLabel(new ImageIcon(kart.getKartGorselYolu())));
                secilenKartlarPanel.revalidate();
                secilenKartlarPanel.repaint();

                for (SavasAraclari kart : oyuncuSecilenKartlar) {
                    kart.setKullanildiMi(true);
                }
            }
            if (oyuncuSecilenKartlar.size() == 3) {
                savasButonu.setEnabled(true);
            }
        }
    }

    // Savaşı Başlatmak İçin Listener
    public class SavasBaslatListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            List<SavasAraclari> bilgisayarSecilenKartlar = oyun.kartSec(bilgisayar);

            secilenKartlarPanel.removeAll(); //orta panel siliyo
            for (int i = 0; i < 3; i++) {
                SavasAraclari oyuncuKart = oyuncuSecilenKartlar.get(i);
                SavasAraclari bilgisayarKart = bilgisayarSecilenKartlar.get(i);
                JLabel oyuncuKartLabel = new JLabel(new ImageIcon(oyuncuKart.getKartGorselYolu()));
                oyuncuKartLabel.setBorder(BorderFactory.createLineBorder(Color.BLUE, 3));
                secilenKartlarPanel.add(oyuncuKartLabel);
                JLabel bilgisayarKartLabel = new JLabel(new ImageIcon(bilgisayarKart.getKartGorselYolu()));
                bilgisayarKartLabel.setBorder(BorderFactory.createLineBorder(Color.RED, 3));
                secilenKartlarPanel.add(bilgisayarKartLabel);
                int ilk1=oyuncuKart.getDayaniklilik();
                int ilk2=bilgisayarKart.getDayaniklilik();
                // Kartların saldırı sonuçlarını güncelle
                int oyuncuHasar = oyuncuKart.SaldiriHesapla(bilgisayarKart);
                int bilgisayarHasar = bilgisayarKart.SaldiriHesapla(oyuncuKart);
                bilgisayarKart.DurumGuncelle(oyuncuHasar);
                oyuncuKart.DurumGuncelle(bilgisayarHasar);
                // Kartların durum bilgilerini yazdır
                secilenKartlarPanel.add(new JLabel(oyuncuKart.KartAdiGoster()+"Dayanıklılık: "  + ilk1 + " -> " + oyuncuKart.getDayaniklilik()));
                secilenKartlarPanel.add(new JLabel(bilgisayarKart.KartAdiGoster()+"Dayanıklılık: " + ilk2 + " -> " + bilgisayarKart.getDayaniklilik()));

                oyun.adimKaydet(oyuncu, bilgisayar, oyuncuKart, bilgisayarKart, oyuncuHasar, "Oyuncu");
                oyun.adimKaydet(oyuncu, bilgisayar, oyuncuKart, bilgisayarKart, bilgisayarHasar, "Bilgisayar");
                // Skor güncelleme
                if (bilgisayarKart.getDayaniklilik() <= 0) {
                    bilgisayar.getKartListesi().remove(bilgisayarKart);

                    if(bilgisayarKart.getSeviyePuani()<=10)
                    {
                        oyuncuKart.setSeviyePuani(oyuncuKart.getSeviyePuani()+10);
                        oyuncu.setSkor(oyuncu.getSkor() + 10);
                    }
                    else{
                        oyuncuKart.setSeviyePuani(oyuncuKart.getSeviyePuani()+bilgisayarKart.getSeviyePuani());
                        oyuncu.setSkor(oyuncu.getSkor() + bilgisayarKart.getSeviyePuani());
                    }
                }
                if (oyuncuKart.getDayaniklilik() <= 0) {
                    oyuncu.getKartListesi().remove(oyuncuKart);
                    if(oyuncuKart.getSeviyePuani()<=10)
                    {
                        bilgisayarKart.setSeviyePuani(bilgisayarKart.getSeviyePuani()+10);
                        bilgisayar.setSkor(bilgisayar.getSkor() + 10);
                    }
                    else{
                        bilgisayarKart.setSeviyePuani(bilgisayarKart.getSeviyePuani()+oyuncuKart.getSeviyePuani());
                        bilgisayar.setSkor(bilgisayar.getSkor() + oyuncuKart.getSeviyePuani());
                    }


                }
            }

            oyuncu.getKartListesi().add(oyun.rastgeleKartOlustur(oyuncu.getSkor()>=20));
            bilgisayar.getKartListesi().add(oyun.rastgeleKartOlustur(bilgisayar.getSkor()>=20));

            if (oyuncu.getKartListesi().size() < 3 && oyuncu.getKartListesi().size()!=0) {
                while (oyuncu.getKartListesi().size() < 3) {
                    oyuncu.getKartListesi().add(oyun.rastgeleKartOlustur(oyuncu.getSkor() >= 20));
                }
            }
            if (bilgisayar.getKartListesi().size() < 3 && bilgisayar.getKartListesi().size()!=0) {
                while (bilgisayar.getKartListesi().size() < 3) {
                    bilgisayar.getKartListesi().add(oyun.rastgeleKartOlustur(bilgisayar.getSkor() >= 20));
                }
            }

            secilenKartlarPanel.revalidate();
            secilenKartlarPanel.repaint();

            //
            oyuncuSkorLabel.setText("Kullanıcı Skoru: " + oyuncu.getSkor());
            bilgisayarSkorLabel.setText("Bilgisayar Skoru: " + bilgisayar.getSkor());

            savasButonu.setEnabled(false);
            sonrakiAdimButonu.setEnabled(true);

        }
    }

    private class SonrakiAdimListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            secilenKartlarPanel.removeAll();
            secilenKartlarPanel.revalidate();
            secilenKartlarPanel.repaint();



            // Panelleri güncelle
            guncelleOyuncuKartlariPanel();
            guncelleBilgisayarKartlariPanel();

            oyuncuSecilenKartlar.clear();

            oyun.mevcutHamle+=1;

            // Sonraki adım butonunu devre dışı bırak
            sonrakiAdimButonu.setEnabled(false);

            if (oyunBitti()) {
                oyunSonuEkrani();
            }
        }

    }

    private void guncelleOyuncuKartlariPanel() {
        oyuncuKartlarPanel.removeAll();
        kullaniciKartButonlari.clear();
        for (SavasAraclari kart : oyuncu.getKartListesi()) {
            JButton kartButonu = new JButton("Dayanıklılık: " + kart.getDayaniklilik(), new ImageIcon(kart.getKartGorselYolu()));
            kartButonu.setPreferredSize(new Dimension(100, 150));
            kartButonu.addActionListener(new KartSecimListener(kart));
            kartButonu.setBorder(BorderFactory.createLineBorder(Color.BLUE, 3));
            kullaniciKartButonlari.add(kartButonu);
            oyuncuKartlarPanel.add(kartButonu);
        }
        oyuncuKartlarPanel.revalidate();
        oyuncuKartlarPanel.repaint();
    }

    // Bilgisayar kartlarını güncelleme
    private void guncelleBilgisayarKartlariPanel() {
        bilgisayarKartlarPanel.removeAll();
        for (int i = 0; i < bilgisayar.getKartListesi().size(); i++) {
            JLabel kartArka = new JLabel(new ImageIcon("src/fotolar/kartarkasi.png"));
            kartArka.setPreferredSize(new Dimension(100, 150));
            kartArka.setBorder(BorderFactory.createLineBorder(Color.RED, 3));
            bilgisayarKartlarPanel.add(kartArka);
        }
        bilgisayarKartlarPanel.revalidate();
        bilgisayarKartlarPanel.repaint();
    }

    // Oyunun bitip bitmediğini kontrol et
    private boolean oyunBitti() {
        return oyuncu.getKartListesi().isEmpty() || bilgisayar.getKartListesi().isEmpty() || oyun.mevcutHamle>=oyun.toplamHamleSayisi  ;
    }

    // Oyun sonu ekranı
    private void oyunSonuEkrani() {
        String kazanan;
        if (oyuncu.getSkor() > bilgisayar.getSkor()) {
            kazanan = "Kazanan: Kullanıcı";
        } else if (bilgisayar.getSkor() > oyuncu.getSkor()) {
            kazanan = "Kazanan: Bilgisayar";
        } else {
            kazanan = "Oyun Berabere!";
        }

        // Oyun sonu mesajı ve skorları göster
        JOptionPane.showMessageDialog(this, kazanan + " Kullanıcı Skoru: " + oyuncu.getSkor() + " Bilgisayar Skoru: " + bilgisayar.getSkor(), "Oyun Bitti", JOptionPane.INFORMATION_MESSAGE);
        System.exit(0);
    }

    public void kartSeviyePuaniGuncelle(int kartSeviyePuani) {
        for (SavasAraclari kart : oyuncu.getKartListesi()) {
            kart.setSeviyePuani(kartSeviyePuani);
        }
        for (SavasAraclari kart : bilgisayar.getKartListesi()) {
            kart.setSeviyePuani(kartSeviyePuani);
        }
    }

}
