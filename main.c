#include <stdio.h>
#include <string.h>

char username[50][20], password[50][20];
int isAdmin[50], salah[50], diban[50];
int jmlUser = 0;

char namaMenu[20][30];
char namaMakanan[20][30];
char namaMinuman[20][30];
int hargaMenu[20], adaMenu[20];
int jmlMenu = 0;

char kodeDiskon[10][20];
int persenDiskon[10], aktifDiskon[10];
int jmlDiskon = 0;

int rating[100];
int jmlRating = 0;

char trNama[100][20];
int trJenis[100], trMetode[100];
long long trSubtotal[100], trDiskon[100], trTotal[100];
int jmlTransaksi = 0;

int cartMenu[20], cartQty[20];
int jmlCart = 0;
int jenis = 0;
int persen = 0;
char kode[20] = "";

int userLogin = -1;

void garis()
{
    printf("------------------------------------------------------------\n");
}

int inputAngka(int min, int max)
{
    int x;
    while (1)
    {
        if (scanf("%d", &x) != 1)
        {
            while (getchar() != '\n')
                ;
        }
        else if (x >= min && x <= max)
        {
            return x;
        }
        printf("Input salah, masukkan angka %d sampai %d: ", min, max);
    }
}

int cariUser(char *nama)
{
    int i;
    for (i = 0; i < jmlUser; i++)
    {
        if (strcmp(username[i], nama) == 0)
        {
            return i;
        }
    }
    return -1;
}

void dataAwal()
{
    strcpy(username[0], "admin");
    strcpy(password[0], "admin123");
    isAdmin[0] = 1;
    jmlUser = 1;

    strcpy(namaMenu[0], "Ayam Malay");
    hargaMenu[0] = 25000;
    strcpy(namaMenu[1], "Ayam Geprek Cibus");
    hargaMenu[1] = 22000;
    strcpy(namaMenu[2], "Pecel Ayam");
    hargaMenu[2] = 18000;
    strcpy(namaMenu[3], "Soto Ayam");
    hargaMenu[3] = 20000;
    strcpy(namaMenu[4], "Nais Krawu");
    hargaMenu[4] = 15000;
    strcpy(namaMenu[5], "Es Teh");
    hargaMenu[5] = 5000;
    strcpy(namaMenu[6], "Jus Jeruk");
    hargaMenu[6] = 10000;
    strcpy(namaMenu[7], "Air Mineral");
    hargaMenu[7] = 4000;
    jmlMenu = 8;
    int i;
    for (i = 0; i < jmlMenu; i++)
    {
        adaMenu[i] = 1;
    }

    strcpy(kodeDiskon[0], "HEMAT10");
    persenDiskon[0] = 10;
    aktifDiskon[0] = 1;
    strcpy(kodeDiskon[1], "MAKAN20");
    persenDiskon[1] = 20;
    aktifDiskon[1] = 1;
    jmlDiskon = 2;
}

int dashboard()
{
    int i, total = 0;
    float rata = 0;

    for (i = 0; i < jmlRating; i++)
    {
        total = total + rating[i];
    }
    if (jmlRating > 0)
    {
        rata = (float)total / jmlRating;
    }

    garis();
    printf("                 RESTORAN NUSANTARA\n");
    garis();
    if (jmlRating > 0)
    {
        printf("Rating restoran: %.1f/5 (%d penilaian)\n", rata, jmlRating);
    }
    else
    {
        printf("Belum ada rating.\n");
    }
    garis();
    printf("1. Login\n");
    printf("2. Register\n");
    printf("0. Keluar\n");
    printf("Pilih: ");
    return inputAngka(0, 2);
}

int login()
{
    char nama[20], pass[20];
    int idx;

    garis();
    printf("                         LOGIN\n");
    garis();
    printf("Username (0 untuk kembali): ");
    scanf("%19s", nama);
    if (strcmp(nama, "0") == 0)
    {
        return 0;
    }

    idx = cariUser(nama);
    if (idx == -1)
    {
        printf("Username tidak ditemukan!\n");
        return 0;
    }
    if (diban[idx] == 1)
    {
        printf("Akun kamu diblokir. Hubungi admin untuk unban.\n");
        return 0;
    }

    printf("Password: ");
    scanf("%19s", pass);
    if (strcmp(pass, password[idx]) == 0)
    {
        salah[idx] = 0;
        userLogin = idx;
        printf("Login berhasil, selamat datang %s!\n", username[idx]);
        return 1;
    }

    salah[idx]++;
    if (salah[idx] > 3)
    {
        diban[idx] = 1;
        printf("Password salah lagi. Akun kamu diblokir!\n");
    }
    else
    {
        printf("Password salah! Percobaan %d dari 3\n", salah[idx]);
        if (salah[idx] == 3)
        {
            printf("Kalau salah lagi, akun akan diblokir.\n");
        }
    }
    return 0;
}

void registerUser()
{
    char nama[20], pass[20];

    garis();
    printf("                        REGISTER\n");
    garis();
    if (jmlUser >= 50)
    {
        printf("Data user penuh.\n");
        return;
    }

    printf("Username baru: ");
    scanf("%19s", nama);
    while (cariUser(nama) != -1)
    {
        printf("Username sudah dipakai, coba yang lain: ");
        scanf("%19s", nama);
    }
    printf("Password: ");
    scanf("%19s", pass);

    strcpy(username[jmlUser], nama);
    strcpy(password[jmlUser], pass);
    isAdmin[jmlUser] = 0;
    salah[jmlUser] = 0;
    diban[jmlUser] = 0;
    jmlUser++;
    printf("Register berhasil, silakan login.\n");
}

void logout()
{
    garis();
    printf("Kamu sudah logout.\n");
    printf("Kembali ke dashboard...\n");
    garis();
    userLogin = -1;
}

void tampilMenu()
{
    int i;
    garis();
    printf("                         DAFTAR MENU\n");
    garis();
    printf("%-4s %-25s %-12s %s\n", "ID", "Nama", "Harga", "Status");
    garis();
    for (i = 0; i < jmlMenu; i++)
    {
        printf("%-4d %-25s Rp%-10d ", i + 1, namaMenu[i], hargaMenu[i]);
        if (adaMenu[i] == 1)
        {
            printf("Tersedia\n");
        }
        else
        {
            printf("Habis\n");
        }
    }
    garis();
}

void pilihMenu()
{
    int id, qty, i;

    while (1)
    {
        tampilMenu();
        printf("Masukkan ID menu (0 jika selesai): ");
        id = inputAngka(0, 100);
        if (id == 0)
        {
            break;
        }
        if (id > jmlMenu)
        {
            printf("ID menu tidak ada!\n");
            continue;
        }
        if (adaMenu[id - 1] == 0)
        {
            printf("Maaf, menu itu sedang habis.\n");
            continue;
        }

        printf("Jumlah: ");
        qty = inputAngka(1, 99);

        for (i = 0; i < jmlCart; i++)
        {
            if (cartMenu[i] == id - 1)
            {
                break;
            }
        }
        if (i < jmlCart)
        {
            cartQty[i] = cartQty[i] + qty;
        }
        else
        {
            cartMenu[jmlCart] = id - 1;
            cartQty[jmlCart] = qty;
            jmlCart++;
        }
        printf("Masuk ke pesanan.\n");
    }
}

void pilihJenis()
{
    garis();
    printf("                  JENIS PESANAN\n");
    garis();
    printf("1. Take in (makan di tempat)\n");
    printf("2. Take away (dibawa pulang)\n");
    printf("Pilih: ");
    jenis = inputAngka(1, 2);
}

void halamanDiskon()
{
    char input[20];
    int i;

    garis();
    printf("                      KODE DISKON\n");
    garis();
    printf("Kode yang tersedia:\n");
    for (i = 0; i < jmlDiskon; i++)
    {
        if (aktifDiskon[i] == 1)
        {
            printf("- %s (%d%%)\n", kodeDiskon[i], persenDiskon[i]);
        }
    }
    printf("Ketik 0 kalau tidak pakai diskon.\n");

    while (1)
    {
        printf("Kode diskon: ");
        scanf("%19s", input);
        if (strcmp(input, "0") == 0)
        {
            persen = 0;
            strcpy(kode, "");
            return;
        }
        for (i = 0; i < jmlDiskon; i++)
        {
            if (strcmp(input, kodeDiskon[i]) == 0 && aktifDiskon[i] == 1)
            {
                persen = persenDiskon[i];
                strcpy(kode, kodeDiskon[i]);
                printf("Diskon %d%% berhasil dipakai.\n", persen);
                return;
            }
        }
        printf("Kode salah atau tidak aktif.\n");
    }
}

long long hitungSubtotal()
{
    long long sub = 0;
    int i;
    for (i = 0; i < jmlCart; i++)
    {
        sub = sub + (long long)hargaMenu[cartMenu[i]] * cartQty[i];
    }
    return sub;
}

void batalkanMenu()
{
    int no, qty, i;

    garis();
    printf("                    PEMBATALAN MENU\n");
    garis();
    for (i = 0; i < jmlCart; i++)
    {
        printf("%d. %s (%d)\n", i + 1, namaMenu[cartMenu[i]], cartQty[i]);
    }
    printf("0. Kembali\n");
    printf("Pilih menu yang dibatalkan: ");
    no = inputAngka(0, jmlCart);
    if (no == 0)
    {
        return;
    }

    printf("Jumlah yang dibatalkan: ");
    qty = inputAngka(1, cartQty[no - 1]);
    cartQty[no - 1] = cartQty[no - 1] - qty;

    if (cartQty[no - 1] == 0)
    {
        for (i = no - 1; i < jmlCart - 1; i++)
        {
            cartMenu[i] = cartMenu[i + 1];
            cartQty[i] = cartQty[i + 1];
        }
        jmlCart--;
    }
}

int konfirmasi()
{
    int i, pilih;
    long long sub, diskon, total;

    while (1)
    {
        sub = hitungSubtotal();
        diskon = sub * persen / 100;
        total = sub - diskon;

        garis();
        printf("                    KONFIRMASI PESANAN\n");
        garis();
        if (jenis == 1)
        {
            printf("Jenis pesanan: Take in\n");
        }
        else
        {
            printf("Jenis pesanan: Take away\n");
        }
        for (i = 0; i < jmlCart; i++)
        {
            printf("%d. %-22s %d x Rp%d = Rp%lld\n", i + 1, namaMenu[cartMenu[i]], cartQty[i],
                   hargaMenu[cartMenu[i]], (long long)hargaMenu[cartMenu[i]] * cartQty[i]);
        }
        garis();
        printf("Subtotal : Rp%lld\n", sub);
        printf("Diskon   : %d%% (Rp%lld)\n", persen, diskon);
        printf("Total    : Rp%lld\n", total);
        garis();
        printf("1. Lanjut pembayaran\n");
        printf("2. Batalkan sebagian menu\n");
        printf("3. Tambah menu\n");
        printf("0. Batalkan semua pesanan\n");
        printf("Pilih: ");
        pilih = inputAngka(0, 3);

        if (pilih == 1)
        {
            return 1;
        }
        else if (pilih == 2)
        {
            batalkanMenu();
        }
        else if (pilih == 3)
        {
            pilihMenu();
        }
        else
        {
            return 0;
        }

        if (jmlCart == 0)
        {
            return 0;
        }
    }
}

void pembayaran()
{
    int i, metode;
    long long sub, diskon, total;

    sub = hitungSubtotal();
    diskon = sub * persen / 100;
    total = sub - diskon;

    garis();
    printf("                 PEMBAYARAN / STRUK\n");
    garis();
    printf("Pelanggan : %s\n", username[userLogin]);
    if (jenis == 1)
    {
        printf("Jenis     : Take in\n");
    }
    else
    {
        printf("Jenis     : Take away\n");
    }
    garis();
    for (i = 0; i < jmlCart; i++)
    {
        printf("%-22s %d x Rp%d = Rp%lld\n", namaMenu[cartMenu[i]], cartQty[i],
               hargaMenu[cartMenu[i]], (long long)hargaMenu[cartMenu[i]] * cartQty[i]);
    }
    garis();
    printf("Subtotal : Rp%lld\n", sub);
    printf("Diskon   : Rp%lld", diskon);
    if (persen > 0)
    {
        printf(" (%s)", kode);
    }
    printf("\nTOTAL    : Rp%lld\n", total);
    garis();
    printf("Metode bayar:\n1. Tunai\n2. QRIS\n3. Kartu debit\n");
    printf("Pilih: ");
    metode = inputAngka(1, 3);

    strcpy(trNama[jmlTransaksi], username[userLogin]);
    trJenis[jmlTransaksi] = jenis;
    trSubtotal[jmlTransaksi] = sub;
    trDiskon[jmlTransaksi] = diskon;
    trTotal[jmlTransaksi] = total;
    trMetode[jmlTransaksi] = metode;
    jmlTransaksi++;

    garis();
    printf("Pembayaran berhasil! Simpan struk ini.\n");
    garis();
}

void beriRating()
{
    garis();
    printf("                    RATING RESTORAN\n");
    garis();
    printf("Beri rating 1-5: ");
    rating[jmlRating] = inputAngka(1, 5);
    jmlRating++;
    printf("Terima kasih atas ratingnya!\n");
}

int penutup()
{
    garis();
    printf("     TERIMA KASIH TELAH MEMESAN DI RESTORAN NUSANTARA\n");
    garis();
    printf("1. Pesan lagi\n");
    printf("0. Kembali ke dashboard\n");
    printf("Pilih: ");
    return inputAngka(0, 1);
}

void halamanUser()
{
    int lagi = 1;

    while (lagi == 1)
    {
        jmlCart = 0;
        persen = 0;
        strcpy(kode, "");

        printf("\nHalo %s, silakan pesan.\n", username[userLogin]);
        pilihJenis();
        pilihMenu();
        if (jmlCart == 0)
        {
            printf("Tidak ada menu yang dipilih.\n");
            return;
        }
        halamanDiskon();
        if (konfirmasi() == 0)
        {
            printf("Pesanan dibatalkan.\n");
            return;
        }
        pembayaran();
        beriRating();
        lagi = penutup();
    }
}

void ubahMenu()
{
    int id, pilih;

    tampilMenu();
    printf("ID menu yang diubah (0 kembali): ");
    id = inputAngka(0, jmlMenu);
    if (id == 0)
    {
        return;
    }

    printf("1. Ubah nama\n2. Ubah harga\n3. Ubah status tersedia/habis\n");
    printf("Pilih: ");
    pilih = inputAngka(1, 3);
    if (pilih == 1)
    {
        printf("Nama baru: ");
        scanf(" %29[^\n]", namaMenu[id - 1]);
    }
    else if (pilih == 2)
    {
        printf("Harga baru: Rp");
        hargaMenu[id - 1] = inputAngka(1, 10000000);
    }
    else
    {
        if (adaMenu[id - 1] == 1)
        {
            adaMenu[id - 1] = 0;
        }
        else
        {
            adaMenu[id - 1] = 1;
        }
    }
    printf("Menu berhasil diubah.\n");
}

void banUser()
{
    int i, no = 0, pilih;

    garis();
    printf("                      BAN USER\n");
    garis();
    for (i = 0; i < jmlUser; i++)
    {
        if (isAdmin[i] == 0 && diban[i] == 0)
        {
            no++;
            printf("%d. %s\n", no, username[i]);
        }
    }
    if (no == 0)
    {
        printf("Tidak ada user yang bisa di-ban.\n");
        return;
    }
    printf("Pilih user (0 kembali): ");
    pilih = inputAngka(0, no);
    if (pilih == 0)
    {
        return;
    }

    no = 0;
    for (i = 0; i < jmlUser; i++)
    {
        if (isAdmin[i] == 0 && diban[i] == 0)
        {
            no++;
            if (no == pilih)
            {
                diban[i] = 1;
                printf("%s berhasil di-ban.\n", username[i]);
            }
        }
    }
}

void unbanUser()
{
    int i, no = 0, pilih;

    garis();
    printf("                    USER YANG DIBAN\n");
    garis();
    for (i = 0; i < jmlUser; i++)
    {
        if (diban[i] == 1)
        {
            no++;
            printf("%d. %s\n", no, username[i]);
        }
    }
    if (no == 0)
    {
        printf("Tidak ada user yang diban.\n");
        return;
    }
    printf("Pilih user (0 kembali): ");
    pilih = inputAngka(0, no);
    if (pilih == 0)
    {
        return;
    }

    no = 0;
    for (i = 0; i < jmlUser; i++)
    {
        if (diban[i] == 1)
        {
            no++;
            if (no == pilih)
            {
                diban[i] = 0;
                salah[i] = 0;
                printf("%s berhasil di-unban.\n", username[i]);
            }
        }
    }
}

void kelolaDiskon()
{
    char baru[20];
    int i, p, aktif;

    garis();
    printf("                  KELOLA KODE DISKON\n");
    garis();
    for (i = 0; i < jmlDiskon; i++)
    {
        printf("- %-10s %d%% ", kodeDiskon[i], persenDiskon[i]);
        if (aktifDiskon[i] == 1)
        {
            printf("(aktif)\n");
        }
        else
        {
            printf("(nonaktif)\n");
        }
    }
    printf("Kode baru / kode yang diubah (huruf besar, 0 batal): ");
    scanf("%19s", baru);
    if (strcmp(baru, "0") == 0)
    {
        return;
    }

    for (i = 0; i < jmlDiskon; i++)
    {
        if (strcmp(baru, kodeDiskon[i]) == 0)
        {
            break;
        }
    }
    if (i == jmlDiskon && jmlDiskon == 10)
    {
        printf("Kode diskon sudah penuh.\n");
        return;
    }

    printf("Persen diskon (1-90): ");
    p = inputAngka(1, 90);
    printf("Aktif? (1 = ya, 0 = tidak): ");
    aktif = inputAngka(0, 1);

    if (i == jmlDiskon)
    {
        strcpy(kodeDiskon[i], baru);
        jmlDiskon++;
    }
    persenDiskon[i] = p;
    aktifDiskon[i] = aktif;
    printf("Kode diskon disimpan.\n");
}

void laporan()
{
    int i;
    long long pendapatan = 0, totalDiskon = 0;

    garis();
    printf("                    LAPORAN TRANSAKSI\n");
    garis();
    if (jmlTransaksi == 0)
    {
        printf("Belum ada transaksi.\n");
        return;
    }
    printf("%-3s %-12s %-9s %-10s %-9s %-10s %s\n", "No", "Pelanggan", "Jenis", "Subtotal",
           "Diskon", "Total", "Bayar");
    garis();
    for (i = 0; i < jmlTransaksi; i++)
    {
        printf("%-3d %-12s ", i + 1, trNama[i]);
        if (trJenis[i] == 1)
        {
            printf("%-9s ", "Take in");
        }
        else
        {
            printf("%-9s ", "Take away");
        }
        printf("%-10lld %-9lld %-10lld ", trSubtotal[i], trDiskon[i], trTotal[i]);
        if (trMetode[i] == 1)
        {
            printf("Tunai\n");
        }
        else if (trMetode[i] == 2)
        {
            printf("QRIS\n");
        }
        else
        {
            printf("Debit\n");
        }
        pendapatan = pendapatan + trTotal[i];
        totalDiskon = totalDiskon + trDiskon[i];
    }
    garis();
    printf("Jumlah transaksi : %d\n", jmlTransaksi);
    printf("Total diskon     : Rp%lld\n", totalDiskon);
    printf("Total pendapatan : Rp%lld\n", pendapatan);
}

void halamanAdmin()
{
    int pilih = -1;

    while (pilih != 0)
    {
        garis();
        printf("                 HALAMAN ADMIN\n");
        garis();
        printf("1. Update menu dan harga\n");
        printf("2. Ban user\n");
        printf("3. Unban user\n");
        printf("4. Kelola kode diskon\n");
        printf("5. Laporan transaksi\n");
        printf("0. Logout\n");
        printf("Pilih: ");
        pilih = inputAngka(0, 5);

        if (pilih == 1)
        {
            ubahMenu();
        }
        else if (pilih == 2)
        {
            banUser();
        }
        else if (pilih == 3)
        {
            unbanUser();
        }
        else if (pilih == 4)
        {
            kelolaDiskon();
        }
        else if (pilih == 5)
        {
            laporan();
        }
    }
}

int main()
{
    int pilih = -1;

    dataAwal();

    while (pilih != 0)
    {
        pilih = dashboard();
        if (pilih == 1)
        {
            if (login() == 1)
            {
                if (isAdmin[userLogin] == 1)
                {
                    halamanAdmin();
                }
                else
                {
                    halamanUser();
                }
                logout();
            }
        }
        else if (pilih == 2)
        {
            registerUser();
        }
    }
    printf("Program selesai. Terima kasih!\n");
    return 0;
}
