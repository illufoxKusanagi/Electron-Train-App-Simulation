# Rencana Kerja & Workflow: TrainAppModern

Dokumen ini adalah panduan dan rencana kerja langkah demi langkah untuk mengembangkan `TrainAppModern`. Tujuannya adalah untuk memodernisasi aplikasi C++/Qt yang sudah ada dengan memisahkannya menjadi backend API dan frontend web modern yang dibungkus dengan Electron.

**Arsitektur Proyek:**

Proyek ini menggunakan struktur *monorepo* dengan *workspaces* untuk memisahkan setiap bagian aplikasi secara bersih.

```
TrainAppModern/
├── packages/
│   ├── backend-cpp/          <-- Kode C++/Qt (API Server)
│   ├── main/                 <-- Kode Electron Main Process (TypeScript)
│   ├── preload/              <-- Kode Electron Preload Script (TypeScript)
│   └── renderer/             <-- Aplikasi Next.js (UI)
│
└── package.json              <-- Konfigurasi utama & skrip
```

---

## Fase 1: Scaffolding & Backend API (Hari 1 - 3)

**Tujuan:** Menyiapkan kerangka proyek dan membuat backend C++ siap untuk dihubungi sebagai API service.

### Hari ke-1: Setup Lingkungan & Monorepo

1.  **Instalasi Toolchain Frontend (Nobara Linux):**
    Pastikan `nvm` dan `node` versi LTS sudah terinstal.
    ```bash
    # 1. Install nvm (Node Version Manager)
    curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash

    # 2. Muat nvm ke terminal (atau buka ulang terminal)
    source ~/.bashrc

    # 3. Install dan gunakan versi Node.js LTS
    nvm install --lts
    nvm use --lts
    ```

2.  **Buat Struktur Monorepo:**
    - Di folder root `TrainAppModern`, buat folder `packages`.
    - Buat file `package.json` di root `TrainAppModern` dengan konten yang sudah Anda miliki (pastikan `workspaces` sudah terdefinisi).
    - Jalankan `npm install` di folder root untuk menginstal `devDependencies` utama.

3.  **Migrasi Backend C++:**
    - Pindahkan seluruh proyek C++ Anda ke dalam folder `packages/backend-cpp`.
    - **PENTING:** Hapus semua folder `build`, `Desktop_Qt_...`, dan file `CMakeCache.txt` yang ada. Ini adalah sisa-sisa build dari Windows dan tidak relevan.

### Hari ke-2: Inisialisasi Frontend & Electron

1.  **Inisialisasi `renderer` (Next.js):**
    Buka terminal, masuk ke folder `packages/`, dan jalankan perintah berikut untuk membuat aplikasi Next.js di dalam folder `renderer`.
    ```bash
    cd packages
    npx create-next-app@latest renderer --typescript --tailwind --eslint --app --src-dir --import-alias "@/*"
    ```

2.  **Inisialisasi `main` (Electron Main Process):**
    - Buat folder `packages/main`.
    - Di dalamnya, buat file `package.json` sederhana:
      ```json
      {
        "name": "main",
        "version": "1.0.0",
        "main": "dist/index.js"
      }
      ```

3.  **Inisialisasi `preload` (Electron Preload Script):**
    - Buat folder `packages/preload`.
    - Di dalamnya, buat file `package.json` sederhana:
      ```json
      {
        "name": "preload",
        "version": "1.0.0",
        "main": "dist/index.js"
      }
      ```

### Hari ke-3: Refactor & Launch Backend API

Fokus hari ini hanya di folder `packages/backend-cpp`.

1.  **Refactor menjadi Aplikasi Konsol:**
    - Buka proyek di VS Code.
    - Hapus semua kode yang berhubungan dengan UI Qt (`QWidget`, `QDialog`, `QMessageBox`, `QPushButton`, dll.).
    - Ubah `main.cpp` untuk menggunakan `QCoreApplication` bukan `QApplication`.
    - Hapus semua file UI (`.ui`) dan referensinya dari `CMakeLists.txt`.

2.  **Implementasi Server HTTP Sederhana:**
    - Modifikasi `CMakeLists.txt` untuk hanya menyertakan modul `Core` dan `Network`.
    - Ubah `main.cpp` untuk menjalankan `QHttpServer` di port `9000` dengan satu endpoint `/status`.

3.  **Build & Test Backend:**
    - Di VS Code, gunakan ekstensi **CMake Tools**:
      - Pilih Kit **GCC** yang terdeteksi.
      - Klik tombol **Build** di status bar.
    - Jalankan executable yang dihasilkan dari terminal VS Code (misal: `./packages/backend-cpp/build/TrainSimulationApp`).
    - Buka terminal lain dan tes dengan `curl http://localhost:9000/status`. Jika berhasil, backend Anda siap.

---

## Fase 2: Integrasi & Development (Hari 4 - 6)

**Tujuan:** Menghubungkan semua bagian agar bisa berjalan bersamaan dalam mode development.

### Hari ke-4: Konfigurasi Electron & Vite

1.  **Buat Kode Awal Electron:**
    - Buat file `packages/main/src/index.ts`. Ini akan menjadi titik masuk utama aplikasi Electron.
    - Buat file `packages/preload/src/index.ts`.

2.  **Konfigurasi Vite:**
    - Buat file `vite.config.mjs` di root `TrainAppModern` untuk mengatur proses build `main` dan `preload`.

3.  **Konfigurasi Skrip `package.json`:**
    - Buka `package.json` di folder root dan tambahkan skrip untuk `dev`, `build`, dan `dist` yang akan mengoordinasikan semua *workspaces*.
    - Tambahkan skrip `dev` dan `build` di `packages/main/package.json` dan `packages/preload/package.json` yang memanggil Vite.

### Hari ke-5: Menghubungkan Frontend dan Backend

1.  **Definisikan Tipe Data (Kontrak API):**
    - Di dalam `packages/renderer/src`, buat folder `types`.
    - Buat file `simulation.ts` di dalamnya. Definisikan `interface` untuk parameter dan hasil simulasi. Ini akan menjadi "kamus" antara C++ dan TypeScript.

2.  **Buat UI dan Panggil API:**
    - Edit file `packages/renderer/src/app/page.tsx`.
    - Buat form input sederhana untuk parameter simulasi.
    - Buat fungsi `async` yang menggunakan `fetch` untuk memanggil endpoint `http://localhost:9000/status` saat tombol ditekan.

### Hari ke-6: Sesi Development Terintegrasi

1.  **Jalankan Backend:** Buka satu terminal, navigasi ke root proyek, dan jalankan executable C++ Anda secara manual.
    ```bash
    ./packages/backend-cpp/build/TrainSimulationApp
    ```

2.  **Jalankan Frontend & Electron:** Buka terminal **kedua**, navigasi ke root proyek, dan jalankan:
    ```bash
    npm run dev
    ```

3.  **Verifikasi:**
    - Sebuah window Electron akan muncul, menampilkan aplikasi Next.js.
    - Buka DevTools Electron (`Ctrl+Shift+I`).
    - Klik tombol pada UI Anda dan periksa tab "Network" atau "Console" untuk melihat apakah panggilan `fetch` ke backend berhasil.

---

## Fase 3: Otomatisasi & Packaging (Hari 7 - 9)

**Tujuan:** Membuat aplikasi menjadi satu kesatuan yang utuh dan siap didistribusikan.

### Hari ke-7: Otomatisasi Backend C++

1.  **Gunakan `child_process`:**
    - Modifikasi `packages/main/src/index.ts`.
    - Gunakan `spawn` dari modul `child_process` Node.js untuk menjalankan executable C++ secara otomatis saat aplikasi Electron dimulai.
    - Pastikan untuk mematikan proses backend (`backendProcess.kill()`) saat aplikasi Electron ditutup (event `will-quit`).
    - Buat logic untuk membedakan path executable antara mode development dan mode produksi (setelah di-package).

### Hari ke-8: Konfigurasi Build Produksi

1.  **Konfigurasi Next.js untuk Static Export:**
    - Buka `packages/renderer/next.config.mjs` dan tambahkan `output: 'export'`. Ini penting agar Next.js menghasilkan file HTML/CSS/JS statis yang bisa dibaca Electron.

2.  **Konfigurasi Electron Builder:**
    - Buka `package.json` di root dan tambahkan konfigurasi `build`.
    - Di dalam `build`, definisikan `appId`, `productName`, dan `directories`.
    - Atur `files` untuk menyertakan folder output dari `main`, `preload`, dan `renderer`.
    - **Paling Penting:** Gunakan `extraResources` untuk memberitahu `electron-builder` agar menyalin executable C++ Anda ke dalam paket aplikasi.
      ```json
      "extraResources": [
        {
          "from": "packages/backend-cpp/build/TrainSimulationApp",
          "to": "bin/TrainSimulationApp"
        }
      ]
      ```

### Hari ke-9: Build, Package, & Finalisasi

1.  **Build Backend C++:** Pastikan Anda sudah meng-compile backend C++ dalam mode `Release` untuk performa terbaik.
    ```bash
    # Di dalam folder backend-cpp
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ```

2.  **Build Frontend & Electron:** Dari folder root, jalankan:
    ```bash
    npm run build
    ```
    Perintah ini akan mem-build `main`, `preload`, dan `renderer` secara berurutan.

3.  **Package Aplikasi:** Dari folder root, jalankan:
    ```bash
    npm run dist
    ```
    `electron-builder` akan mengambil semua hasil build dan membungkusnya menjadi satu file installer (`.AppImage`, `.deb`, dll.) di dalam folder `dist`.

4.  **Test & Dokumentasi:**
    - Jalankan file `.AppImage` yang dihasilkan untuk memastikan aplikasi berjalan mandiri.
    - Perbarui file `README.md` utama dengan arsitektur baru dan instruksi build untuk Linux.
