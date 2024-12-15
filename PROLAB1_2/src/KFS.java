public class KFS extends KaraSinifi {
    private static final int DEFAULT_DAYANIKLILIK = 10; // Sabit başlangıç dayanıklılık
    private static final int DENIZ_VURUS_AVANTAJI = 10; // Deniz birimlerine karşı vuruş avantaj çarpanı
    private static final int HAVA_VURUS_AVANTAJI = 20; // Hava birimlerine karşı vuruş avantaj çarpanı

    // Varsayılan seviye puanı (0) ile constructor
    public KFS() {
        super(DEFAULT_DAYANIKLILIK, 0, "Kara", 10, true); // Vuruş gücü sabit: 10
    }

    // Kullanıcı tarafından belirtilen seviye puanı ile constructor
    public KFS(int seviyePuani) {
        super(DEFAULT_DAYANIKLILIK, seviyePuani, "Kara", 10, true); // Dayanıklılık sabit, seviye puanı belirlenebilir
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
        System.out.println("KFS - Dayanıklılık: " + getDayaniklilik() +
                ", Seviye Puanı: " + getSeviyePuani());
    }

    // Vuruş gücü hesaplama (avantaj duruma göre dahil edilecek)
    public int SaldiriHesapla(SavasAraclari rakip) {
        if (rakip instanceof DenizSinifi) {
            return getVurus() + DENIZ_VURUS_AVANTAJI;
        } else if (rakip instanceof HavaSinifi) {
            return getVurus() + HAVA_VURUS_AVANTAJI;
        } else {
            return getVurus();
        }
    }

    @Override
    public String KartAdiGoster(){
        return "KFS";
    }

    // Kartın aktif olup olmadığını kontrol et
    public boolean aktifMi() {
        return getDayaniklilik() > 0;
    }

    @Override
    public String getKartGorselYolu() {
        return "src/fotolar/kfs.png";
    }
}
