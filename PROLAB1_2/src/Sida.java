public class Sida extends DenizSinifi {
    private static final int DEFAULT_DAYANIKLILIK = 15; // Sabit başlangıç dayanıklılık
    private static final int KARA_VURUS_AVANTAJI = 10; // Kara vuruş avantaj çarpanı
    private static final int HAVA_VURUS_AVANTAJI=10;

    // Varsayılan seviye puanı (0) ile constructor
    public Sida() {
        super(DEFAULT_DAYANIKLILIK, 0, "Deniz", 10, true); // Vuruş gücü sabit: 10
    }

    // Kullanıcı tarafından belirtilen seviye puanı ile constructor
    public Sida(int seviyePuani) {
        super(DEFAULT_DAYANIKLILIK, seviyePuani, "Deniz", 10, true); // Dayanıklılık sabit, seviye puanı belirlenebilir
    }

    @Override
    public void DurumGuncelle(int hasar) {
        // Dayanıklılığı hasara göre azalt
        setDayaniklilik(getDayaniklilik() - hasar);
        if (getDayaniklilik() < 0) {
            setDayaniklilik(0); // Negatif değerleri sıfıra çek
        }
    }

    public void seviyePuaniEkle(int puan) {
        // Seviye puanını artır
        setSeviyePuani(getSeviyePuani() + puan);
    }

    @Override
    public void KartPuaniGoster() {
        System.out.println("Sida - Dayanıklılık: " + getDayaniklilik() +
                ", Seviye Puanı: " + getSeviyePuani());
    }

    // Vuruş gücü hesaplama (avantaj dahil)
    public int SaldiriHesapla(SavasAraclari rakip) {
        if (rakip instanceof KaraSinifi) {
            return getVurus() + KARA_VURUS_AVANTAJI;
        } else if (rakip instanceof HavaSinifi) {
            return getVurus() + HAVA_VURUS_AVANTAJI;
        }
        else {
            return getVurus();
        }
    }

    // Kartın aktif olup olmadığını kontrol et
    public boolean aktifMi() {
        return getDayaniklilik() > 0;
    }

    @Override
    public String KartAdiGoster(){
        return "Sida";
    }
    @Override
    public String getKartGorselYolu() {
        return "src/fotolar/sida.png"; // Obüs görsel dosyasının yolu
    }
}
