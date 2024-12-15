public abstract class KaraSinifi extends SavasAraclari {
    private boolean denizVurusAvantaji;

    // Constructor
    public KaraSinifi(int dayaniklilik, int seviyePuani, String sinif, int vurus, boolean denizVurusAvantaji) {
        super(dayaniklilik, seviyePuani, sinif, vurus);
        this.denizVurusAvantaji = denizVurusAvantaji;
    }

    // Getter and Setter methods
    public boolean isDenizVurusAvantaji() {
        return denizVurusAvantaji;
    }

    public void setDenizVurusAvantaji(boolean denizVurusAvantaji) {
        this.denizVurusAvantaji = denizVurusAvantaji;
    }
}
