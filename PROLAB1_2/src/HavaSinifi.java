public abstract class HavaSinifi extends SavasAraclari {
    private boolean karaVurusAvantaji;

    // Constructor
    public HavaSinifi(int dayaniklilik, int seviyePuani, String sinif, int vurus, boolean karaVurusAvantaji) {
        super(dayaniklilik, seviyePuani, sinif, vurus);
        this.karaVurusAvantaji = karaVurusAvantaji;
    }

    // Getter and Setter methods
    public boolean isKaraVurusAvantaji() {
        return karaVurusAvantaji;
    }

    public void setKaraVurusAvantaji(boolean karaVurusAvantaji) {
        this.karaVurusAvantaji = karaVurusAvantaji;
    }
}