    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define Mesafe 7430.0
    #define hiz_sinir 70
    #define BIR_GUN_SANIYE 86400

    typedef struct {
        int saat;
        int dakika;
        int saniye;
    } zaman;

    typedef struct {
        char plaka[10];
        zaman Giriszamani;
    } arac;

    int total(zaman z) {
        return (z.saat * 3600) + (z.dakika * 60) + z.saniye;
    }

    int main(void) {
        char cikisplaka[10];
        zaman cikiszamani;
        FILE *fankara, *fgolbasi, *fceza;

        fankara = fopen("ankara.txt", "r");
        if (fankara == NULL) {
            printf("Ankara.txt bulunamadi\n");
            exit(1);
        }

        fgolbasi = fopen("golbasi.txt", "r");
        if (fgolbasi == NULL) {
            printf("Golbasi.txt bulunamadi\n");
            exit(1);
        }

        fceza = fopen("ceza.txt", "w");
        if (fceza == NULL) {
            printf("Ceza.txt olusturulamadi\n");
            exit(1);
        }

        arac araclar[100];
        int i = 0;

        while (i < 100 && fscanf(fankara, "%s %d %d %d", araclar[i].plaka,
                                 &araclar[i].Giriszamani.saat,
                                 &araclar[i].Giriszamani.dakika,
                                 &araclar[i].Giriszamani.saniye) != EOF) {
            i++;
        }
        int aracsayisi = i;
        fclose(fankara);

        while (fscanf(fgolbasi, "%s %d %d %d", cikisplaka,
                      &cikiszamani.saat,
                      &cikiszamani.dakika,
                      &cikiszamani.saniye) != EOF) {

            for (int j = 0; j < aracsayisi; j++) {
                if (strcmp(cikisplaka, araclar[j].plaka) == 0) {

                    int giris_toplam_sn = total(araclar[j].Giriszamani);
                    int cikis_toplam_sn = total(cikiszamani);
                    int fark_saniye = cikis_toplam_sn - giris_toplam_sn;


                    if (fark_saniye < 0) {
                        fark_saniye += BIR_GUN_SANIYE;
                    }

                    float hizli = (Mesafe / fark_saniye) * 3.6;

                    if (hizli > hiz_sinir) {
                        fprintf(fceza, "%-10s %.2f km/h\n", araclar[j].plaka, hizli);
                    }
                }
            }
        }

        fclose(fgolbasi);
        fclose(fceza);
        printf("Islem basariyla tamamlandi. Ceza yiyenler ceza.txt dosyasina yazildi.\n");

        return 0;
    }
