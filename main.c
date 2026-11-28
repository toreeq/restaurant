#include <stdio.h>
#include <string.h>

#define MAKS_USER 50
#define MAKS_MENU 30
#define MAKS_DISKON 10
#define MAKS_TRANSAKSI 1000
#define MAKS_KERANJANG 30

char namaPengguna[MAKS_USER][20];
char kataSandi[MAKS_USER][20];
int statusAdmin[MAKS_USER];
int salahLogin[MAKS_USER];
int statusBan[MAKS_USER];
int jumlahPengguna = 0;

char namaMenu[MAKS_MENU][40];
int hargaMenu[MAKS_MENU];
int jenisMenu[MAKS_MENU];
int statusMenu[MAKS_MENU];
int jumlahMenu = 0;

char kodeDiskon[MAKS_DISKON][20];
int persenDiskon[MAKS_DISKON];
int batasDiskon[MAKS_DISKON];
int terpakaiDiskon[MAKS_DISKON];
int aktifDiskon[MAKS_DISKON];
int jumlahDiskon = 0;

int nilaiRating[100];
int jumlahRating = 0;

char transaksiPengguna[MAKS_TRANSAKSI][20];
int transaksiJenis[MAKS_TRANSAKSI];
int transaksiMetode[MAKS_TRANSAKSI];
int transaksiSubtotal[MAKS_TRANSAKSI];
int transaksiDiskon[MAKS_TRANSAKSI];
int transaksiTotal[MAKS_TRANSAKSI];
int transaksiJumlahItem[MAKS_TRANSAKSI][MAKS_MENU];
int jumlahTransaksi = 0;

int keranjangMenu[MAKS_KERANJANG];
int keranjangJumlah[MAKS_KERANJANG];
int jumlahKeranjang = 0;

int jenisPesanan = 0;
int persenTerpilih = 0;
char kodeTerpilih[20] = "";
int penggunaLogin = -1;

void garisHalaman() {
    printf("======================================================================\n");
}

void garisBiasa() {
    printf("----------------------------------------------------------------------\n");
}

void tungguEnter() {
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar();
}

int inputAngka(int minimum, int maksimum) {
    int angka;
    while (1) {
        if (scanf("%d", &angka) == 1) {
            while (getchar() != '\n') {}
            if (angka >= minimum && angka <= maksimum) return angka;
        } else {
            while (getchar() != '\n') {}
        }
        printf("Input salah. Masukkan angka %d sampai %d: ", minimum, maksimum);
    }
}

int inputHarga() {
    char teks[40];
    int harga;
    int i;
    int valid;

    while (1) {
        scanf("%39s", teks);
        harga = 0;
        valid = 1;

        for (i = 0; teks[i] != '\0'; i++) {
            if (teks[i] >= '0' && teks[i] <= '9') {
                harga = harga * 10 + (teks[i] - '0');
            } else if (teks[i] != '.') {
                valid = 0;
            }
        }

        if (valid == 1 && harga > 0) {
            return harga;
        }

        printf("Harga tidak valid. Masukkan angka: Rp");
    }
}

void formatRupiah(int angka, char hasil[40]) {
    char sementara[40];
    char dibalik[40];
    int panjang;
    int i;
    int j = 0;
    int hitung = 0;

    if (angka == 0) {
        strcpy(hasil, "0");
        return;
    }

    sprintf(sementara, "%d", angka);
    panjang = (int)strlen(sementara);

    for (i = panjang - 1; i >= 0; i--) {
        dibalik[j++] = sementara[i];
        hitung++;
        if (hitung == 3 && i != 0) {
            dibalik[j++] = '.';
            hitung = 0;
        }
    }

    dibalik[j] = '\0';
    for (i = 0; i < j; i++) {
        hasil[i] = dibalik[j - i - 1];
    }
    hasil[j] = '\0';
}

void tampilHarga(int harga) {
    char hasil[40];
    formatRupiah(harga, hasil);
    printf("Rp%s", hasil);
}

const char *namaJenisMenu(int jenis) {
    if (jenis == 1) return "Makanan";
    if (jenis == 2) return "Minuman";
    return "Cemilan";
}

const char *namaJenisPesanan(int jenis) {
    if (jenis == 1) return "Makan di tempat";
    return "Dibawa pulang";
}

const char *namaMetode(int metode) {
    if (metode == 1) return "Tunai";
    return "Transfer DANA";
}

int indeksMenu(int jenis, int nomor) {
    int i;
    int hitung = 0;

    for (i = 0; i < jumlahMenu; i++) {
        if (jenisMenu[i] == jenis) {
            hitung++;
            if (hitung == nomor) return i;
        }
    }

    return -1;
}

void tambahMenuAwal(int posisi, const char *nama, int harga, int jenis) {
    strcpy(namaMenu[posisi], nama);
    hargaMenu[posisi] = harga;
    jenisMenu[posisi] = jenis;
    statusMenu[posisi] = 1;
}

void dataAwal() {
    strcpy(namaPengguna[0], "admin");
    strcpy(kataSandi[0], "admin123");
    statusAdmin[0] = 1;
    salahLogin[0] = 0;
    statusBan[0] = 0;
    jumlahPengguna = 1;

    tambahMenuAwal(0, "Nasi Goreng Spesial", 25000, 1);
    tambahMenuAwal(1, "Ayam Geprek", 22000, 1);
    tambahMenuAwal(2, "Mie Goreng", 18000, 1);
    tambahMenuAwal(3, "Soto Ayam", 20000, 1);
    tambahMenuAwal(4, "Nasi Ayam Bakar", 28000, 1);
    tambahMenuAwal(5, "Nasi Ayam Crispy", 25000, 1);
    tambahMenuAwal(6, "Bakso Kuah", 20000, 1);
    tambahMenuAwal(7, "Seblak", 18000, 1);
    tambahMenuAwal(8, "Kwetiau Goreng", 22000, 1);
    tambahMenuAwal(9, "Nasi Rendang", 30000, 1);

    tambahMenuAwal(10, "Es Teh Manis", 5000, 2);
    tambahMenuAwal(11, "Teh Hangat", 5000, 2);
    tambahMenuAwal(12, "Jus Jeruk", 10000, 2);
    tambahMenuAwal(13, "Jus Alpukat", 15000, 2);
    tambahMenuAwal(14, "Es Kopi Susu", 15000, 2);
    tambahMenuAwal(15, "Kopi Hitam", 8000, 2);
    tambahMenuAwal(16, "Cokelat Dingin", 12000, 2);
    tambahMenuAwal(17, "Matcha Latte", 16000, 2);
    tambahMenuAwal(18, "Air Mineral", 4000, 2);
    tambahMenuAwal(19, "Es Lemon Tea", 9000, 2);

    tambahMenuAwal(20, "Kentang Goreng", 15000, 3);
    tambahMenuAwal(21, "Pisang Goreng", 12000, 3);
    tambahMenuAwal(22, "Tahu Crispy", 10000, 3);
    tambahMenuAwal(23, "Tempe Mendoan", 10000, 3);
    tambahMenuAwal(24, "Cireng", 10000, 3);
    tambahMenuAwal(25, "Risoles", 12000, 3);
    tambahMenuAwal(26, "Roti Bakar", 15000, 3);
    tambahMenuAwal(27, "Sosis Bakar", 13000, 3);
    tambahMenuAwal(28, "Nugget Ayam", 14000, 3);
    tambahMenuAwal(29, "Dimsum", 18000, 3);
    jumlahMenu = 30;

    strcpy(kodeDiskon[0], "HEMAT10");
    persenDiskon[0] = 10;
    batasDiskon[0] = 20;
    terpakaiDiskon[0] = 0;
    aktifDiskon[0] = 1;

    strcpy(kodeDiskon[1], "MAKAN20");
    persenDiskon[1] = 20;
    batasDiskon[1] = 10;
    terpakaiDiskon[1] = 0;
    aktifDiskon[1] = 1;
    jumlahDiskon = 2;
}

int cariPengguna(const char *nama) {
    int i;
    for (i = 0; i < jumlahPengguna; i++) {
        if (strcmp(namaPengguna[i], nama) == 0) return i;
    }
    return -1;
}

void tampilBintang(int rating) {
    int penuh;
    int sisa;
    int i;

    penuh = rating / 10;
    sisa = rating % 10;

    if (sisa >= 8) {
        penuh++;
        sisa = 0;
    }

    for (i = 0; i < penuh && i < 5; i++) {
        printf("*");
    }

    if (sisa >= 5 && penuh < 5) {
        printf("+");
    }
}


int inputRating() {
    char teks[20];
    int nilai = 0;
    int angkaSetelahTitik = 0;
    int adaTitik = 0;
    int valid = 1;
    int i;

    while (1) {
        scanf("%19s", teks);
        nilai = 0;
        angkaSetelahTitik = 0;
        adaTitik = 0;
        valid = 1;

        for (i = 0; teks[i] != '\0'; i++) {
            if (teks[i] >= '0' && teks[i] <= '9') {
                if (adaTitik == 0) {
                    nilai = nilai * 10 + (teks[i] - '0');
                } else {
                    if (angkaSetelahTitik == 0) {
                        if (teks[i] >= '0' && teks[i] <= '9') {
                            nilai = nilai * 10 + (teks[i] - '0');
                            angkaSetelahTitik = 1;
                        }
                    } else {
                        valid = 0;
                    }
                }
            } else if (teks[i] == '.' && adaTitik == 0) {
                adaTitik = 1;
            } else {
                valid = 0;
            }
        }

        if (valid == 1) {
            if (adaTitik == 0) {
                nilai = nilai * 10;
            }
            if (nilai >= 10 && nilai <= 50) {
                return nilai;
            }
        }

        printf("Rating tidak valid. Masukkan rating 1.0 sampai 5.0: ");
    }
}

int halamanUtama() {
    int totalRating = 0;
    float rataRating = 0;
    int i;

    garisHalaman();
    printf("                 RESTORAN NUSANTARA\n");
    printf("               Sistem Pemesanan Makanan\n");
    garisBiasa();

    for (i = 0; i < jumlahRating; i++) {
        totalRating = totalRating + nilaiRating[i];
    }

    if (jumlahRating > 0) {
        rataRating = (float)totalRating / jumlahRating / 10;
        printf("Rating restoran : %.1f/5 (", rataRating);
        tampilBintang((int)(rataRating * 10 + 0.5));
        printf(") dari %d penilaian\n", jumlahRating);
    } else {
        printf("Rating restoran : Belum ada penilaian\n");
    }

    garisBiasa();
    printf("1. Login\n");
    printf("2. Register\n");
    printf("0. Keluar\n");
    garisHalaman();
    printf("Pilih menu: ");

    return inputAngka(0, 2);
}

int login() {
    char nama[20];
    char sandi[20];
    int indeks;

    garisHalaman();
    printf("|                              LOGIN                               |\n");
    garisHalaman();
    printf("Username (0 untuk kembali): ");
    scanf("%19s", nama);

    if (strcmp(nama, "0") == 0) return 0;

    indeks = cariPengguna(nama);
    if (indeks == -1) {
        printf("Username tidak ditemukan.\n");
        return 0;
    }

    if (statusBan[indeks]) {
        printf("Akun sedang diblokir. Hubungi admin untuk unban.\n");
        return 0;
    }

    printf("Password: ");
    scanf("%19s", sandi);

    if (strcmp(sandi, kataSandi[indeks]) == 0) {
        salahLogin[indeks] = 0;
        penggunaLogin = indeks;
        printf("Login berhasil. Selamat datang, %s!\n", namaPengguna[indeks]);
        return 1;
    }

    salahLogin[indeks]++;
    if (salahLogin[indeks] >= 3) {
        statusBan[indeks] = 1;
        printf("Password salah 3 kali. Akun otomatis diblokir.\n");
    } else {
        printf("Password salah. Percobaan %d dari 3.\n", salahLogin[indeks]);
    }
    return 0;
}

void registerUser() {
    char nama[20];
    char sandi[20];

    garisHalaman();
    printf("|                             REGISTER                             |\n");
    garisHalaman();

    if (jumlahPengguna >= MAKS_USER) {
        printf("Data pengguna sudah penuh.\n");
        return;
    }

    printf("Username baru: ");
    scanf("%19s", nama);
    while (cariPengguna(nama) != -1) {
        printf("Username sudah digunakan. Masukkan yang lain: ");
        scanf("%19s", nama);
    }

    printf("Password baru: ");
    scanf("%19s", sandi);

    strcpy(namaPengguna[jumlahPengguna], nama);
    strcpy(kataSandi[jumlahPengguna], sandi);
    statusAdmin[jumlahPengguna] = 0;
    salahLogin[jumlahPengguna] = 0;
    statusBan[jumlahPengguna] = 0;
    jumlahPengguna++;

    printf("Register berhasil. Silakan login.\n");
}

void tampilSatuJenisMenu(int jenis, int modePesan) {
    int i;
    int nomor = 0;
    char harga[40];

    printf("\n%s\n", namaJenisMenu(jenis));
    garisBiasa();
    printf("%-3s %-24s %-12s %-10s\n", "ID", "Nama", "Harga", "Status");
    garisBiasa();

    for (i = 0; i < jumlahMenu; i++) {
        if (jenisMenu[i] == jenis) {
            nomor++;
            formatRupiah(hargaMenu[i], harga);
            printf("%-3d %-24s Rp%-9s ", nomor, namaMenu[i], harga);
            if (statusMenu[i] == 1) {
                printf("Tersedia\n");
            } else {
                printf("Habis\n");
            }
        }
    }

    if (modePesan == 0) {
        garisBiasa();
    }
}

void tampilSemuaMenu() {
    garisHalaman();
    printf("|                           DAFTAR MENU                            |\n");
    garisHalaman();
    tampilSatuJenisMenu(1, 0);
    tampilSatuJenisMenu(2, 0);
    tampilSatuJenisMenu(3, 0);
    garisHalaman();
}

void pilihJenisPesanan() {
    garisHalaman();
    printf("|                         JENIS PESANAN                            |\n");
    garisHalaman();
    printf("1. Makan di tempat\n");
    printf("2. Dibawa pulang\n");
    garisBiasa();
    printf("Pilih jenis pesanan: ");
    jenisPesanan = inputAngka(1, 2);
}

void tambahMenuKeKeranjang(int jenis) {
    int nomor;
    int jumlah;
    int indeks;
    int i;

    tampilSatuJenisMenu(jenis, 1);
    printf("\nMasukkan ID %s (0 = lanjut): ", namaJenisMenu(jenis));

    while (1) {
        nomor = inputAngka(0, 10);
        if (nomor == 0) return;

        indeks = indeksMenu(jenis, nomor);
        if (indeks == -1) {
            printf("ID menu tidak ditemukan. Pilih 1-10 atau 0: ");
            continue;
        }

        if (!statusMenu[indeks]) {
            printf("Menu tersebut sedang habis. Pilih menu lain: ");
            continue;
        }

        printf("Jumlah %s: ", namaMenu[indeks]);
        jumlah = inputAngka(1, 99);

        for (i = 0; i < jumlahKeranjang; i++) {
            if (keranjangMenu[i] == indeks) break;
        }

        if (i < jumlahKeranjang) {
            keranjangJumlah[i] += jumlah;
        } else {
            if (jumlahKeranjang >= MAKS_KERANJANG) {
                printf("Keranjang sudah penuh.\n");
                return;
            }
            keranjangMenu[jumlahKeranjang] = indeks;
            keranjangJumlah[jumlahKeranjang] = jumlah;
            jumlahKeranjang++;
        }

        printf("%s x%d masuk ke pesanan.\n", namaMenu[indeks], jumlah);
        printf("Tambah %s lagi (0 = lanjut): ", namaJenisMenu(jenis));
    }
}

void pesanMenuBerurutan() {
    garisHalaman();
    printf("|                       PEMILIHAN MENU                            |\n");
    garisHalaman();
    printf("Urutan: Makanan -> ENTER -> Minuman -> ENTER -> Cemilan -> ENTER\n");
    garisBiasa();

    tambahMenuKeKeranjang(1);
    printf("\nMakanan selesai. Tekan ENTER untuk masuk ke Minuman...");
    getchar();

    tambahMenuKeKeranjang(2);
    printf("\nMinuman selesai. Tekan ENTER untuk masuk ke Cemilan...");
    getchar();

    tambahMenuKeKeranjang(3);
    printf("\nCemilan selesai. Tekan ENTER untuk menyelesaikan pesanan...");
    getchar();
}

int hitungSubtotal() {
    int subtotal = 0;
    int i;
    for (i = 0; i < jumlahKeranjang; i++) {
        subtotal += (int)hargaMenu[keranjangMenu[i]] * keranjangJumlah[i];
    }
    return subtotal;
}

void tampilKeranjang() {
    int i;
    char harga[40];
    char totalHarga[40];

    printf("\n");
    garisBiasa();
    printf("%-4s %-28s %-8s %-14s %-14s\n", "No", "Menu", "Jumlah", "Harga", "Total");
    garisBiasa();

    for (i = 0; i < jumlahKeranjang; i++) {
        formatRupiah(hargaMenu[keranjangMenu[i]], harga);
        formatRupiah((int)hargaMenu[keranjangMenu[i]] * keranjangJumlah[i], totalHarga);
        printf("%-4d %-28s %-8d Rp%-12s Rp%-12s\n", i + 1, namaMenu[keranjangMenu[i]], keranjangJumlah[i], harga, totalHarga);
    }
    garisBiasa();
}

void batalkanMenu() {
    int nomor;
    int jumlah;
    int i;

    if (jumlahKeranjang == 0) {
        printf("Keranjang kosong.\n");
        return;
    }

    tampilKeranjang();
    printf("Nomor menu yang dibatalkan (0 = kembali): ");
    nomor = inputAngka(0, jumlahKeranjang);
    if (nomor == 0) return;

    printf("Jumlah yang dibatalkan: ");
    jumlah = inputAngka(1, keranjangJumlah[nomor - 1]);
    keranjangJumlah[nomor - 1] -= jumlah;

    if (keranjangJumlah[nomor - 1] == 0) {
        for (i = nomor - 1; i < jumlahKeranjang - 1; i++) {
            keranjangMenu[i] = keranjangMenu[i + 1];
            keranjangJumlah[i] = keranjangJumlah[i + 1];
        }
        jumlahKeranjang--;
    }

    printf("Pesanan berhasil diperbarui.\n");
}

void tampilDiskon() {
    int i;

    printf("\n");
    garisBiasa();
    printf("%-4s %-14s %-8s %-8s %-10s %s\n", "No", "Kode", "Diskon", "Batas", "Terpakai", "Status");
    garisBiasa();

    for (i = 0; i < jumlahDiskon; i++) {
        printf("%-4d %-14s %d%%       %-8d %-10d ", i + 1, kodeDiskon[i], persenDiskon[i], batasDiskon[i], terpakaiDiskon[i]);
        if (!aktifDiskon[i]) printf("Nonaktif\n");
        else if (terpakaiDiskon[i] >= batasDiskon[i]) printf("Batas habis\n");
        else printf("Aktif\n");
    }
    garisBiasa();
}

void pilihDiskon() {
    char masukan[20];
    int i;
    int ditemukan;

    persenTerpilih = 0;
    strcpy(kodeTerpilih, "");

    printf("\nKODE DISKON\n");
    tampilDiskon();
    printf("Ketik 0 jika tidak memakai diskon.\n");

    while (1) {
        printf("Kode diskon: ");
        scanf("%19s", masukan);
        if (strcmp(masukan, "0") == 0) return;

        ditemukan = 0;
        for (i = 0; i < jumlahDiskon; i++) {
            if (strcmp(masukan, kodeDiskon[i]) == 0) {
                ditemukan = 1;
                if (!aktifDiskon[i]) printf("Kode diskon sedang nonaktif.\n");
                else if (terpakaiDiskon[i] >= batasDiskon[i]) printf("Batas pemakaian kode diskon sudah habis.\n");
                else {
                    persenTerpilih = persenDiskon[i];
                    strcpy(kodeTerpilih, kodeDiskon[i]);
                    printf("Diskon %d%% berhasil dipilih.\n", persenTerpilih);
                    return;
                }
                break;
            }
        }
        if (!ditemukan) printf("Kode diskon tidak ditemukan.\n");
    }
}

int konfirmasiPesanan() {
    int pilihan;
    int subtotal;
    int diskon;
    int total;

    while (1) {
        subtotal = hitungSubtotal();
        diskon = subtotal * persenTerpilih / 100;
        total = subtotal - diskon;

            garisHalaman();
        printf("|                       KONFIRMASI PESANAN                       |\n");
        garisHalaman();
        printf("Jenis pesanan : %s\n", namaJenisPesanan(jenisPesanan));
        printf("Kode diskon   : %s", persenTerpilih > 0 ? kodeTerpilih : "Tidak ada");
        if (persenTerpilih > 0) printf(" (%d%%)", persenTerpilih);
        printf("\n");
        tampilKeranjang();
        printf("Subtotal : "); tampilHarga(subtotal); printf("\n");
        printf("Diskon   : "); tampilHarga(diskon); printf("\n");
        printf("Total    : "); tampilHarga(total); printf("\n");
        garisBiasa();
        printf("[1] Lanjut pembayaran\n");
        printf("[2] Batalkan sebagian menu\n");
        printf("[3] Tambah menu\n");
        printf("[0] Batalkan semua\n");
        printf("Pilih: ");
        pilihan = inputAngka(0, 3);

        if (pilihan == 1) return 1;
        if (pilihan == 2) batalkanMenu();
        else if (pilihan == 3) pesanMenuBerurutan();
        else return 0;

        if (jumlahKeranjang == 0) return 0;
    }
}

void tampilDana() {
    garisHalaman();
    printf("|                       TRANSFER DANA                           |\n");
    garisHalaman();
    printf("Penerima : RESTORAN NUSANTARA\n");
    printf("DANA     : 082142816496\n");
    printf("Silakan transfer sesuai total pembayaran.\n");
    garisHalaman();
}

void tampilStruk(int subtotal, int diskon, int total, int metode, int uangBayar, int kembalian) {
    int i;
    char harga[40];
    char jumlahHarga[40];

    garisHalaman();
    printf("|                         STRUK PEMBAYARAN                       |\n");
    garisHalaman();
    printf("Pelanggan : %s\n", namaPengguna[penggunaLogin]);
    printf("Jenis     : %s\n", namaJenisPesanan(jenisPesanan));
    printf("Metode    : %s\n", namaMetode(metode));
    if (metode == 2) printf("DANA      : 082142816496\n");
    garisBiasa();

    for (i = 0; i < jumlahKeranjang; i++) {
        formatRupiah(hargaMenu[keranjangMenu[i]], harga);
        formatRupiah((int)hargaMenu[keranjangMenu[i]] * keranjangJumlah[i], jumlahHarga);
        printf("%-25s %2dx Rp%-9s = Rp%s\n", namaMenu[keranjangMenu[i]], keranjangJumlah[i], harga, jumlahHarga);
    }

    garisBiasa();
    printf("Subtotal : "); tampilHarga(subtotal); printf("\n");
    printf("Diskon   : "); tampilHarga(diskon);
    if (persenTerpilih > 0) printf(" (%s %d%%)", kodeTerpilih, persenTerpilih);
    printf("\n");
    printf("TOTAL    : "); tampilHarga(total); printf("\n");

    if (metode == 1) {
        printf("Dibayar  : "); tampilHarga(uangBayar); printf("\n");
        printf("Kembali  : "); tampilHarga(kembalian); printf("\n");
    }

    garisHalaman();
    printf("|             TERIMA KASIH TELAH MEMESAN!                       |\n");
    garisHalaman();
}

void pembayaran() {
    int metode;
    int i;
    int subtotal = hitungSubtotal();
    int diskon = subtotal * persenTerpilih / 100;
    int total = subtotal - diskon;
    int uangBayar = 0;
    int kembalian = 0;

    garisHalaman();
    printf("|                         PEMBAYARAN                            |\n");
    garisHalaman();
    printf("Total pembayaran: "); tampilHarga(total); printf("\n\n");
    printf("[1] Tunai\n");
    printf("[2] Transfer DANA\n");
    garisBiasa();
    printf("Pilih metode pembayaran: ");
    metode = inputAngka(1, 2);

    if (metode == 1) {
        printf("Uang dibayarkan: Rp");
        while (1) {
            uangBayar = inputHarga();
            if (uangBayar >= total) break;
            printf("Uang kurang. Masukkan minimal Rp");
        }
        kembalian = uangBayar - total;
    } else {
        tampilDana();
        printf("\nTekan ENTER setelah transfer selesai...");
        getchar();
    }

    if (jumlahTransaksi < MAKS_TRANSAKSI) {
        strcpy(transaksiPengguna[jumlahTransaksi], namaPengguna[penggunaLogin]);
        transaksiJenis[jumlahTransaksi] = jenisPesanan;
        transaksiMetode[jumlahTransaksi] = metode;
        transaksiSubtotal[jumlahTransaksi] = subtotal;
        transaksiDiskon[jumlahTransaksi] = diskon;
        transaksiTotal[jumlahTransaksi] = total;

        for (i = 0; i < jumlahKeranjang; i++) {
            transaksiJumlahItem[jumlahTransaksi][keranjangMenu[i]] += keranjangJumlah[i];
        }
        jumlahTransaksi++;
    }

    if (persenTerpilih > 0) {
        for (i = 0; i < jumlahDiskon; i++) {
            if (strcmp(kodeTerpilih, kodeDiskon[i]) == 0) {
                terpakaiDiskon[i]++;
                break;
            }
        }
    }

    tampilStruk(subtotal, diskon, total, metode, uangBayar, kembalian);
}

void beriRating() {
    if (jumlahRating >= 100) return;
    printf("\nBeri rating restoran (1.0-5.0): ");
    nilaiRating[jumlahRating] = inputRating();
    printf("Rating kamu: %.1f/5 (", (float)nilaiRating[jumlahRating] / 10);
    tampilBintang(nilaiRating[jumlahRating]);
    printf(")\n");
    jumlahRating++;
    printf("Terima kasih atas ratingnya.\n");
}

void halamanUser() {
    int pilihan;
    int pesanLagi = 1;

    while (pesanLagi) {
        jumlahKeranjang = 0;
        persenTerpilih = 0;
        strcpy(kodeTerpilih, "");

            garisHalaman();
        printf("|                    PEMESANAN PELANGGAN                         |\n");
        garisHalaman();
        printf("Pengguna : %s\n", namaPengguna[penggunaLogin]);
        garisBiasa();
        printf("[1] Mulai pesan\n");
        printf("[2] Lihat menu\n");
        printf("[0] Logout\n");
        garisHalaman();
        printf("Pilih: ");
        pilihan = inputAngka(0, 2);

        if (pilihan == 0) return;
        if (pilihan == 2) {
            tampilSemuaMenu();
            tungguEnter();
            continue;
        }

        pilihJenisPesanan();
        pesanMenuBerurutan();

        if (jumlahKeranjang == 0) {
            printf("Tidak ada menu yang dipilih.\n");
            tungguEnter();
            continue;
        }

        pilihDiskon();

        if (!konfirmasiPesanan()) {
            printf("Pesanan dibatalkan.\n");
            tungguEnter();
            continue;
        }

        pembayaran();
        beriRating();

        printf("\n[1] Pesan lagi\n");
        printf("[2] Kembali ke menu pengguna\n");
        printf("Pilih: ");
        if (inputAngka(1, 2) == 2) pesanLagi = 0;
    }
}

void ubahMenu() {
    int jenis;
    int nomor;
    int indeks;
    int pilihan;
    int jenisBaru;
    char namaBaru[40];

    tampilSemuaMenu();
    printf("\nJenis menu: 1. Makanan  2. Minuman  3. Cemilan\n");
    printf("Pilih jenis: ");
    jenis = inputAngka(1, 3);
    printf("ID menu (1-10): ");
    nomor = inputAngka(1, 10);
    indeks = indeksMenu(jenis, nomor);

    if (indeks == -1) {
        printf("Menu tidak ditemukan.\n");
        return;
    }

    garisBiasa();
    printf("Menu   : %s\n", namaMenu[indeks]);
    printf("Harga  : "); tampilHarga(hargaMenu[indeks]); printf("\n");
    printf("Jenis  : %s\n", namaJenisMenu(jenisMenu[indeks]));
    printf("Status : %s\n", statusMenu[indeks] ? "Tersedia" : "Habis");
    garisBiasa();
    printf("[1] Ubah nama\n");
    printf("[2] Ubah harga\n");
    printf("[3] Ubah jenis\n");
    printf("[4] Ubah status\n");
    printf("[0] Batal\n");
    printf("Pilih: ");
    pilihan = inputAngka(0, 4);

    if (pilihan == 1) {
        printf("Nama baru: ");
        scanf(" %39[^\n]", namaBaru);
        strcpy(namaMenu[indeks], namaBaru);
    } else if (pilihan == 2) {
        printf("Harga baru: Rp");
        hargaMenu[indeks] = (int)inputHarga();
    } else if (pilihan == 3) {
        printf("1. Makanan\n2. Minuman\n3. Cemilan\nPilih jenis baru: ");
        jenisBaru = inputAngka(1, 3);
        jenisMenu[indeks] = jenisBaru;
    } else if (pilihan == 4) {
        statusMenu[indeks] = !statusMenu[indeks];
    } else {
        return;
    }

    printf("Menu berhasil diperbarui.\n");
}

void banUser() {
    int i;
    int nomor = 0;
    int pilihan;

    garisHalaman();
    printf("|                            BAN USER                              |\n");
    garisHalaman();

    for (i = 0; i < jumlahPengguna; i++) {
        if (!statusAdmin[i] && !statusBan[i]) {
            nomor++;
            printf("[%d] %s\n", nomor, namaPengguna[i]);
        }
    }

    if (nomor == 0) {
        printf("Tidak ada user yang dapat di-ban.\n");
        return;
    }

    printf("Pilih user (0 = kembali): ");
    pilihan = inputAngka(0, nomor);
    if (pilihan == 0) return;

    nomor = 0;
    for (i = 0; i < jumlahPengguna; i++) {
        if (!statusAdmin[i] && !statusBan[i]) {
            nomor++;
            if (nomor == pilihan) {
                statusBan[i] = 1;
                printf("User %s berhasil di-ban.\n", namaPengguna[i]);
                return;
            }
        }
    }
}

void unbanUser() {
    int i;
    int nomor = 0;
    int pilihan;

    garisHalaman();
    printf("|                           UNBAN USER                             |\n");
    garisHalaman();

    for (i = 0; i < jumlahPengguna; i++) {
        if (statusBan[i]) {
            nomor++;
            printf("[%d] %s\n", nomor, namaPengguna[i]);
        }
    }

    if (nomor == 0) {
        printf("Tidak ada user yang sedang di-ban.\n");
        return;
    }

    printf("Pilih user (0 = kembali): ");
    pilihan = inputAngka(0, nomor);
    if (pilihan == 0) return;

    nomor = 0;
    for (i = 0; i < jumlahPengguna; i++) {
        if (statusBan[i]) {
            nomor++;
            if (nomor == pilihan) {
                statusBan[i] = 0;
                salahLogin[i] = 0;
                printf("User %s berhasil di-unban.\n", namaPengguna[i]);
                return;
            }
        }
    }
}

void kelolaDiskon() {
    int pilihan;
    int i;
    int nomor;
    char kodeBaru[20];
    int persenBaru;
    int batasBaru;
    int statusBaru;

    garisHalaman();
    printf("|                       KELOLA KODE DISKON                       |\n");
    garisHalaman();
    printf("%-4s %-14s %-8s %-8s %-10s %s\n", "No", "Kode", "Diskon", "Batas", "Terpakai", "Status");
    garisBiasa();
    for (i = 0; i < jumlahDiskon; i++) {
        printf("%-4d %-14s %d%%       %-8d %-10d %s\n", i + 1, kodeDiskon[i], persenDiskon[i], batasDiskon[i], terpakaiDiskon[i], aktifDiskon[i] ? "Aktif" : "Nonaktif");
    }
    garisBiasa();
    printf("[1] Tambah kode\n");
    printf("[2] Ubah kode, persen, atau batas\n");
    printf("[3] Aktifkan/nonaktifkan\n");
    printf("[0] Kembali\n");
    printf("Pilih: ");
    pilihan = inputAngka(0, 3);

    if (pilihan == 0) return;

    if (pilihan == 1) {
        if (jumlahDiskon >= MAKS_DISKON) {
            printf("Jumlah kode diskon sudah penuh.\n");
            return;
        }
        printf("Kode baru: ");
        scanf("%19s", kodeBaru);
        for (i = 0; i < jumlahDiskon; i++) {
            if (strcmp(kodeBaru, kodeDiskon[i]) == 0) {
                printf("Kode sudah ada.\n");
                return;
            }
        }
        printf("Persen diskon: ");
        persenBaru = inputAngka(1, 90);
        printf("Batas pemakaian: ");
        batasBaru = inputAngka(1, 9999);
        strcpy(kodeDiskon[jumlahDiskon], kodeBaru);
        persenDiskon[jumlahDiskon] = persenBaru;
        batasDiskon[jumlahDiskon] = batasBaru;
        terpakaiDiskon[jumlahDiskon] = 0;
        aktifDiskon[jumlahDiskon] = 1;
        jumlahDiskon++;
        printf("Kode diskon berhasil ditambahkan.\n");
    } else if (pilihan == 2) {
        if (jumlahDiskon == 0) return;
        printf("Nomor kode yang diubah: ");
        nomor = inputAngka(1, jumlahDiskon) - 1;
        printf("Kode baru: ");
        scanf("%19s", kodeBaru);
        printf("Persen baru: ");
        persenBaru = inputAngka(1, 90);
        printf("Batas baru: ");
        batasBaru = inputAngka(1, 9999);
        printf("Aktif? 1=ya, 0=tidak: ");
        statusBaru = inputAngka(0, 1);
        strcpy(kodeDiskon[nomor], kodeBaru);
        persenDiskon[nomor] = persenBaru;
        batasDiskon[nomor] = batasBaru;
        aktifDiskon[nomor] = statusBaru;
        printf("Kode diskon berhasil diubah.\n");
    } else {
        if (jumlahDiskon == 0) return;
        printf("Nomor kode: ");
        nomor = inputAngka(1, jumlahDiskon) - 1;
        aktifDiskon[nomor] = !aktifDiskon[nomor];
        printf("Status %s: %s\n", kodeDiskon[nomor], aktifDiskon[nomor] ? "Aktif" : "Nonaktif");
    }
}

void laporanTransaksi() {
    int i;
    int j;
    int pendapatanKotor = 0;
    int totalDiskon = 0;
    int pendapatanBersih = 0;
    int totalItemTerjual = 0;
    char harga[40];

    garisHalaman();
    printf("|                       LAPORAN TRANSAKSI                        |\n");
    garisHalaman();

    for (i = 0; i < jumlahTransaksi; i++) {
        pendapatanKotor += transaksiSubtotal[i];
        totalDiskon += transaksiDiskon[i];
        pendapatanBersih += transaksiTotal[i];
        for (j = 0; j < jumlahMenu; j++) totalItemTerjual += transaksiJumlahItem[i][j];
    }

    printf("Jumlah transaksi  : %d\n", jumlahTransaksi);
    printf("Total item terjual: %d\n", totalItemTerjual);
    printf("Pendapatan kotor  : "); tampilHarga(pendapatanKotor); printf("\n");
    printf("Total diskon      : "); tampilHarga(totalDiskon); printf("\n");
    printf("Pendapatan bersih : "); tampilHarga(pendapatanBersih); printf("\n");

    garisBiasa();
    printf("JUMLAH TERJUAL PER ITEM\n");
    garisBiasa();
    printf("%-4s %-30s %-12s %-10s\n", "ID", "Nama Item", "Kategori", "Terjual");
    garisBiasa();

    for (j = 1; j <= 3; j++) {
        int nomor = 0;
        for (i = 0; i < jumlahMenu; i++) {
            int jumlahTerjual = 0;
            int transaksi;
            if (jenisMenu[i] != j) continue;
            nomor++;
            for (transaksi = 0; transaksi < jumlahTransaksi; transaksi++) jumlahTerjual += transaksiJumlahItem[transaksi][i];
            printf("%-4d %-30s %-12s %-10d\n", nomor, namaMenu[i], namaJenisMenu(j), jumlahTerjual);
        }
        if (j < 3) garisBiasa();
    }

    garisBiasa();
    printf("DETAIL TRANSAKSI\n");
    garisBiasa();
    printf("%-4s %-15s %-20s %-15s %-15s\n", "No", "Pelanggan", "Jenis", "Kotor", "Bersih");
    garisBiasa();

    for (i = 0; i < jumlahTransaksi; i++) {
        formatRupiah(transaksiSubtotal[i], harga);
        printf("%-4d %-15s %-20s Rp%-12s ", i + 1, transaksiPengguna[i], namaJenisPesanan(transaksiJenis[i]), harga);
        formatRupiah(transaksiTotal[i], harga);
        printf("Rp%-12s\n", harga);
    }
    garisHalaman();
}

void halamanAdmin() {
    int pilihan;

    while (1) {
            garisHalaman();
        printf("|                 ADMINISTRATOR RESTORAN NUSANTARA              |\n");
        garisHalaman();
        printf("[1] Kelola menu\n");
        printf("[2] Ban user\n");
        printf("[3] Unban user\n");
        printf("[4] Kelola kode diskon\n");
        printf("[5] Laporan transaksi\n");
        printf("[6] Lihat semua menu\n");
        printf("[0] Logout\n");
        garisHalaman();
        printf("Pilih: ");
        pilihan = inputAngka(0, 6);

        if (pilihan == 0) return;
        if (pilihan == 1) ubahMenu();
        else if (pilihan == 2) banUser();
        else if (pilihan == 3) unbanUser();
        else if (pilihan == 4) kelolaDiskon();
        else if (pilihan == 5) laporanTransaksi();
        else if (pilihan == 6) tampilSemuaMenu();
        tungguEnter();
    }
}

int main() {
    int pilihan;

    dataAwal();

    while (1) {
        pilihan = halamanUtama();
        if (pilihan == 0) break;

        if (pilihan == 1) {
            if (login()) {
                if (statusAdmin[penggunaLogin]) halamanAdmin();
                else halamanUser();
                penggunaLogin = -1;
            }
            tungguEnter();
        } else if (pilihan == 2) {
            registerUser();
            tungguEnter();
        }
    }

    garisHalaman();
    printf("|                 TERIMA KASIH TELAH BERKUNJUNG                  |\n");
    garisHalaman();
    return 0;
}