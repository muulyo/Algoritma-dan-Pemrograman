#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
//Kelompok buat kategori
enum KategoriArea {
    KARBOHIDRAT = 1,
    PROTEIN = 2,
    MAKANAN_INSTAN = 3
};
struct Produk {
    string kodeProduk;
    string namaProduk;
    int jumlahWadah;
    int ukuranKardus; // ukuran : 1=kecil, 2=sedang, 3=besar
};

struct AreaGudang {
    int idArea;
    KategoriArea kategori;
    string namaArea;
    int kapasitasMaksWadah;
    Produk daftarProduk[50]; // Kapasitas maksimal 50 
    int jumlahJenisProduk;
};
//Fungsi awal
void GuDaNg(AreaGudang gudang[], int jumlahArea);
// TUGAS ANDI 
void statusGudangTerpusat(const AreaGudang gudang[], int jumlahArea);
void cekDetailStokPerArea(const AreaGudang gudang[], int jumlahArea);
// TUGAS NAUFAL
void barangmasuk(AreaGudang gudang[], int jumlahArea);
void barangkeluar(AreaGudang gudang[], int jumlahArea);
// TUGAS DAMAR
void cari(const AreaGudang gudang[], int jumlahArea);
//Buat manggil void atas
int main() {
    const int JUMLAH_AREA = 3;
    AreaGudang gudang[JUMLAH_AREA];
 //buat ngisi data
    GuDaNg(gudang, JUMLAH_AREA);
    int pilihan;
    do {
        cout << " \n SISTEM MANAJEMEN GUDANG GROSIR TERPUSAT\n";
        cout << "1. Status Gudang Terpusat & Daftar Area\n";
        cout << "2. Cek Detail Stok Kardus per Area\n";
        cout << "3. Input Barang Masuk (Sesuai Ukuran Kardus)\n";
        cout << "4. Output Barang Keluar\n";
        cout << "5. Cari Produk\n";
        cout << "6. Selesai \n";
        cout << "\n";
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;
        // kalo semisal inputnya diluar pilihan
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            pilihan = -1;
        }
        switch (pilihan) {
            case 1:
                statusGudangTerpusat(gudang, JUMLAH_AREA);
                break;
            case 2:
                cekDetailStokPerArea(gudang, JUMLAH_AREA);
                break;
            case 3:
                 barangmasuk(gudang, JUMLAH_AREA);
                break;
            case 4:
                 barangkeluar(gudang, JUMLAH_AREA);
                break;
            case 5:
                cari(gudang, JUMLAH_AREA);
                break;
            case 6:
                cout << "\n Selesai \n";
                break;
            default:
                cout << "\n Pilihan menu tidak tersedia silahkan pilih yang lain \n";
        }
    } while (pilihan != 6);
    return 0;
}
void GuDaNg(AreaGudang gudang[], int jumlahArea) {
    //buat area 1
    gudang[0].idArea = 1;
    gudang[0].kategori = KARBOHIDRAT;
    gudang[0].namaArea = "Area 1 (Karbohidrat)";
    gudang[0].kapasitasMaksWadah = 200;
    gudang[0].jumlahJenisProduk = 2;
    gudang[0].daftarProduk[0] = {"Karbo1", "Beras damara ", 120, 3};     
    gudang[0].daftarProduk[1] = {"Karbo2", "Tepung Terigu Segitiga", 80, 2}; 
//area 2
    gudang[1].idArea = 2;
    gudang[1].kategori = PROTEIN;
    gudang[1].namaArea = "Area 2 (Protein)";
    gudang[1].kapasitasMaksWadah = 150;
    gudang[1].jumlahJenisProduk = 2;
    gudang[1].daftarProduk[0] = {"Prot1", "Telur Ayam ", 90, 2}; 
    gudang[1].daftarProduk[1] = {"Prot2", "Sosis & Nugget premium ", 60, 1};  
//area 3
    gudang[2].idArea = 3;
    gudang[2].kategori = MAKANAN_INSTAN;
    gudang[2].namaArea = "Area 3 (Makanan Instan)";
    gudang[2].kapasitasMaksWadah = 600;
    gudang[2].jumlahJenisProduk = 2;

    gudang[2].daftarProduk[0] = {"INS-01", "Mie Indomie", 250, 2};
    gudang[2].daftarProduk[1] = {"INS-02", "Sarden Kaleng", 75, 1};    
}
//Lanjutan Pilihan yg pertama (Tugas Andi)
void statusGudangTerpusat(const AreaGudang gudang[], int jumlahArea) {
    int totalKapasitasSemua = 0;
    int totalTerisiSemua = 0;
    cout << " Status Gudang Terpusat \n";
    cout << "\n";
    cout << left << setw(26) << "Nama Area"
         << setw(14) << "Jumlah Jenis"
         << setw(15) << "Banyak"
         << setw(15) << "Sisa"
         << "Status" << endl;

    for (int i = 0; i < jumlahArea; i++) {
        int totalWadahArea = 0;
        for (int j = 0; j < gudang[i].jumlahJenisProduk; j++) {
            totalWadahArea += gudang[i].daftarProduk[j].jumlahWadah;
        }
        
        int sisaKapasitas = gudang[i].kapasitasMaksWadah - totalWadahArea;
        totalKapasitasSemua += gudang[i].kapasitasMaksWadah;
        totalTerisiSemua += totalWadahArea;

        // status longgar
        string statusArea;
        double persentase = (double)totalWadahArea / gudang[i].kapasitasMaksWadah * 100.0;
        if (persentase >= 90.0) {
            statusArea = "Sudah penuh";
        } else if (persentase >= 50.0) {
            statusArea = "Cukup penuh";
        } else {
            statusArea = "Belum penuh";
        }

        cout << left << setw(26) << gudang[i].namaArea
             << setw(14) << gudang[i].jumlahJenisProduk
             << setw(15) << totalWadahArea
             << setw(15) << sisaKapasitas
             << statusArea << endl;
    }
    cout << "Kapasitas Gudang : " << totalKapasitasSemua << " Wadah \n";
    cout << "Stok yang Ada    : " << totalTerisiSemua << " Wadah \n";
    cout << "Sisa Tempat    : " << (totalKapasitasSemua - totalTerisiSemua) << " Kardus\n";
}

// Buat pilihan yang kedua (Cek Stok)(TugasAndi)
void cekDetailStokPerArea(const AreaGudang gudang[], int jumlahArea) {
    int pilihArea;
    cout << "\n Pilih area yang mau dicek stoknya \n";
    for (int i = 0; i < jumlahArea; i++) {
        cout << gudang[i].idArea << ". " << gudang[i].namaArea << endl;
    }
    cout << "4. Semua semua yang aku mau \n";
    cout << "Masukkan pilihan area (1-4): ";
    cin >> pilihArea;

    if (cin.fail() || pilihArea < 1 || pilihArea > 4) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\n Area Tidak Ada silahkan piloh yang lain \n";
        return;
    }
    //buat ngasi keterangannya
    cout << " Detail wadah per area \n";

    for (int i = 0; i < jumlahArea; i++) {
        if (pilihArea != 4 && gudang[i].idArea != pilihArea) {
            continue;
        }
        cout << "\n>>> " << gudang[i].namaArea
             << " (Kapasitas Maks: " << gudang[i].kapasitasMaksWadah << " Wadah) <<<\n";
        cout << left << setw(12) << "Kode"
             << setw(30) << "Nama Produk"
             << setw(18) << "Kode Ukuran"
             << "Jumlah Stok" << endl;
            
        if (gudang[i].jumlahJenisProduk == 0) {
            cout << "Kosong \n";
        } else {
            int subtotalKardus = 0;
            for (int j = 0; j < gudang[i].jumlahJenisProduk; j++) {
                cout << left << setw(12) << gudang[i].daftarProduk[j].kodeProduk
                     << setw(30) << gudang[i].daftarProduk[j].namaProduk
                     << setw(18) << gudang[i].daftarProduk[j].ukuranKardus
                     << gudang[i].daftarProduk[j].jumlahWadah << " Kardus" << endl;
                subtotalKardus += gudang[i].daftarProduk[j].jumlahWadah;
            }
            cout << "Subtotal Stok " << gudang[i].namaArea << ": " << subtotalKardus << " Kardus\n";
        }
    }
}

// barang masuk

void barangmasuk(AreaGudang gudang[], int jumlahArea) {
    int pilihArea, jumlahMasuk;
    string kode;
    bool ditemukan = false;

    cout << "\n=== INPUT BARANG MASUK ===\n";
    for (int i = 0; i < jumlahArea; i++) {
        cout << gudang[i].idArea << ". " << gudang[i].namaArea << endl;

    }

    cout << "Pilih area: ";
    cin >> pilihArea;

    if (cin.fail() || pilihArea < 1 || pilihArea > jumlahArea) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Area tidak ditemukan!\n";
        return;

    }

    int i = pilihArea - 1;
    cout << "Masukkan kode produk: ";
    cin >> kode;

    for (int j = 0; j < gudang[i].jumlahJenisProduk; j++) {
        if (gudang[i].daftarProduk[j].kodeProduk == kode) {
            ditemukan = true;

            cout << "Nama produk: "
                 <<gudang[i].daftarProduk[j].namaProduk << endl;
            cout << "stok saat ini: "
                 << gudang[i].daftarProduk[j].jumlahWadah << " kardus\n";
            cout << "jumlah barang masuk: ";
            cin >> jumlahMasuk;

            if (cin.fail()|| jumlahMasuk <= 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "jumlah barang tidak valid!\n";
                return;

            }

            int totalstok = 0;
            for (int k = 0; k < gudang[i].jumlahJenisProduk; k++) {
                totalstok += gudang[i].daftarProduk[k].jumlahWadah;

            }

            if (totalstok + jumlahMasuk > gudang[i].kapasitasMaksWadah) {
                cout << "kapasitas gudang tidak mencukupi\n";
                return;

            }

            gudang[i].daftarProduk[j].jumlahWadah += jumlahMasuk;
            cout << "\nBarang berhasil ditambahkan!\n";
            cout << "Total stok sekarang: "
                 << gudang[i].daftarProduk[j].jumlahWadah << " kardus\n";
                 break;

            
            
            
        }
    }

    if (!ditemukan) {
        cout << "produk tidak ditemukan!\n";

    }
}

//Barang keluar

void barangkeluar(AreaGudang gudang[], int jumlahArea) {
    int piliharea, jumlahkeluar;
    string kode;
    bool ditemukan = false;

    cout << "\n=== OUTPUT BARANG KELUAR ===\n";
    for (int i = 0; i < jumlahArea; i++) {
        cout << gudang[i].idArea << ". " << gudang[i].namaArea << endl;

    }

    cout << "Pilih Area: ";
    cin >> piliharea;

    if (cin.fail() || piliharea < 1 || piliharea > jumlahArea) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Area tidak di temukan!\n";
        return;

    }

    int i = piliharea - 1;
    cout << "Masukkan kode produk: ";
    cin >> kode;

    for (int j = 0; j < gudang[i].jumlahJenisProduk; j++) {
        if (gudang[i].daftarProduk[j].kodeProduk == kode) {
            ditemukan = true;

            cout << "Nama Produk: "
                 << gudang[i].daftarProduk[j].namaProduk << endl;
            cout << "Stok tersedia: "
                 << gudang[i].daftarProduk[j].jumlahWadah << " kardus\n";
            cout << "Jumlah barang keluar: ";
            cin >> jumlahkeluar;

            if (cin.fail() || jumlahkeluar <= 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Jumlah barang tidak valid!\n";
                return;

            }

            gudang[i].daftarProduk[j].jumlahWadah -= jumlahkeluar;
            cout << "\nBarang berhasil dikeluarkan!\n";
            cout << "Sisa stok sekarang: "
                 << gudang[i].daftarProduk[j].jumlahWadah << " kardus\n";
            break; 
        }
    }

    if (!ditemukan) {
        cout << "Produk tidak di temukan!\n";
    }

}

//Cari produk

void cari(const AreaGudang gudang[], int jumlahArea) {
    string key;
    bool headerMuncul = false;

    cout << "Produk apa yang mau dicari?\n Masukkan nama produk: ";
    cin.ignore(1000, '\n');
    getline(cin, key);

    if (key.empty()) {
        cout << "Nama produk tidak boleh kosong.\n";
        return;
    }
    int jumlahDitemukan = 0;

    cout << "Hasil pencarian untuk \"" << key << "\": \n";
    
    for (int i = 0; i < jumlahArea; i++) {
        for (int j = 0; j < gudang[i].jumlahJenisProduk; j++) {
            const Produk& p = gudang[i].daftarProduk[j];

            if (p.namaProduk.find(key) != string::npos) {
                 if (!headerMuncul) {
                  cout << left << setw(26) << "Area"
                         << setw(30) << "Nama Produk"
                         << setw(14) << "Ukuran"
                         << "Stok" << endl;
                         headerMuncul = true;
                  }
                string ukuran;
                if (p.ukuranKardus == 1)      ukuran = "Kecil";
                else if (p.ukuranKardus == 2) ukuran = "Sedang";
                else                          ukuran = "Besar";

                cout << left << setw(26) << gudang[i].namaArea
                     << setw(30) << p.namaProduk
                     << setw(14) << ukuran
                     << p.jumlahWadah << " Kardus" << endl;

                jumlahDitemukan++;
            }
        }
    }

    if (jumlahDitemukan == 0) {
        cout << "Produk tidak ditemukan.\n";
    } else {
        cout << "\n Ditemukan " << jumlahDitemukan << " produk\n";
    }
}