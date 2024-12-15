public class Firkateyn extends DenizSinifi {
    private static final int DEFAULT_DAYANIKLILIK = 25; // Sabit başlangıç dayanıklılık
    private static final int HAVA_VURUS_AVANTAJI = 5; // Hava birimlerine karşı vuruş avantaj çarpanı

    // Varsayılan seviye puanı (0) ile constructor
    public Firkateyn() {
        super(DEFAULT_DAYANIKLILIK, 0, "Deniz", 10, true); // Vuruş gücü sabit: 15
    }

    // Kullanıcı tarafından belirtilen seviye puanı ile constructor
    public Firkateyn(int seviyePuani) {
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
        System.out.println("Firkateyn - Dayanıklılık: " + getDayaniklilik() +
                ", Seviye Puanı: " + getSeviyePuani());
    }

    // Vuruş gücü hesaplama (avantaj duruma göre dahil edilecek)
    public int SaldiriHesapla(SavasAraclari rakip) {
        if (rakip instanceof HavaSinifi) {
            return getVurus() + HAVA_VURUS_AVANTAJI;
        } else {
            return getVurus();
        }
    }

    @Override
    public String KartAdiGoster(){
        return "Fırkateyn";
    }

    // Kartın aktif olup olmadığını kontrol et
    public boolean aktifMi() {
        return getDayaniklilik() > 0;
    }

    @Override
    public String getKartGorselYolu() {
        return "src/fotolar/firkateyn.png";
    }
}
