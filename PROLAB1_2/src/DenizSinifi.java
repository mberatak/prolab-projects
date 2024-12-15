public abstract class DenizSinifi extends SavasAraclari {
    private boolean havaVurusAvantaji;

    // Constructor
    public DenizSinifi(int dayaniklilik, int seviyePuani, String sinif, int vurus, boolean havaVurusAvantaji) {
        super(dayaniklilik, seviyePuani, sinif, vurus);
        this.havaVurusAvantaji = havaVurusAvantaji;
    }

    // Getter and Setter methods
    public boolean isHavaVurusAvantaji() {
        return havaVurusAvantaji;
    }

    public void setHavaVurusAvantaji(boolean havaVurusAvantaji) {
        this.havaVurusAvantaji = havaVurusAvantaji;
    }
}