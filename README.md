# SoalShift_Modul3_B02

## 1. soal1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
##### Contoh
##### ./faktorial 5 3 4
##### 3!=6
##### 4!=24
##### 5!=120
### Jawaban:
> Check : [Full SourceCode](https://github.com/sherlyrosa/SoalShift_Modul3_B02/blob/master/SoalNo1/no1.c)
### Penjelasan :
1. Karena input-an pada file yang diminta ialah dalam bentuk argumen maka menggunakan `argc` dan `argv`.
2. Untuk menghitung `factorial` nya 
```sh
void *factorial(void *args) {
  int fac=1;
  for(int a=1; a<=num[j];a++){
    fac=fac*a;
  }
  printf("%d! = %d \n",num[j],fac);
  j++;
  status=1;

```
3. Untuk merubah dari `string` menjadi `integer` dengan menggunakan fungsi `atoi`
```sh
while(argv[i] != NULL){
  num[i]=atoi(argv[i]);
  i++;}
```
4. Karena yang diminta sorting 
```sh
for(k=1;k<argc;k++){
  for(j=k+1;j<argc;j++){
    int angka1=atoi(argv[k]);
    int angka2=atoi(argv[j]);
    if(angka2<angka1){
      char *temp = argv[j];
      int temp2 = num[j];
      num[j] = num[k];
      num[k] = temp2;
      argv[j] = argv[k];
      argv[k] = temp;
    }
  }
```
## 2. soal2
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi  sebagai berikut:  

a. Terdapat 2 server: server penjual dan server pembeli

b. 1 server hanya bisa terkoneksi dengan 1 client

c. Server penjual dan server pembeli memiliki stok barang yang selalu sama

d. Client yang terkoneksi ke server penjual hanya bisa menambah stok
 	
        Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1

e. Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
	
        Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1

f. Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
	
        Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
	
        Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”

g. Server penjual akan mencetak stok saat ini setiap 5 detik sekali

h. Menggunakan thread, socket, shared memory
### Jawaban :
> Check : [Full SourceCode](https://github.com/sherlyrosa/SoalShift_Modul3_B02/tree/master/SoalNo2)
### Penjelasan :
#### Client Pembeli
1. Membuat deskriptor file socket

```sh
if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	printf("\n Socket creation error \n");
        return -1;
    }
    
 ```
 
 2. Tetapkan alamat IP di `servaddr` ke `127.0.0.1` karena server juga berada di mesin yang sama. Alamat dalam `servaddr` harus dalam format integer, karenanya menggunakan fungsi `inet_pton`

```sh
 if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
```

3. Hubungkan ke perangkat yang `address` dan nomor `port`nya ditentukan di `servaddr`.

```sh
if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
```

4. Client pembeli melakukan apa yang diperintahkan

```sh
while(1) {
        char perintah[10];
        scanf("%s", perintah);
        send(sock , perintah , strlen(perintah) , 0 );
        valread = read(sock, temp, 1024);
        printf("%s\n", temp);
        memset(temp, 0, sizeof(temp));
    }
```

#### Client Penjual
1. Untuk proses socketnya sama dengan `Client Pembeli`

2. Client penjual melakukan apa yang diperintahkan

```sh
while(1) {
        char perintah[10];
        scanf("%s", perintah);
        send(sock, perintah, strlen(perintah), 0);
    }
```
#### Server Pembeli

1. Memaksa melampirkan socket ke `port`

```sh
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
   
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
```

2. Melaksanakan yang diperintahkan, `sizeof()` untuk mengembalikan jumlah memori.

```sh
 while((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))>0) {
        memset(buffer, 0, sizeof(buffer));
        while(valread = read( new_socket , buffer, 1024) > 0) {
            if(strcmp(buffer, "beli") == 0) {
                if(*value == 0)
                    send(new_socket, "Transaksi Gagal", strlen("Transaksi Gagal"), 0);
                else {
                    *value -= 1;
                    send(new_socket, "Transaksi Berhasil", strlen("Transaksi Berhasil"), 0);
                }
            }
            memset(buffer, 0, sizeof(buffer));
        }
    }
 ```
 
#### Server Penjual
1. Socket memiliki perintah yang sama dengan server pembeli

2. Melaksanakan yang diperintahkan, `sizeof()` untuk mengembalikan jumlah memori.

```sh
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))>0) {
        memset(buffer, 0, sizeof(buffer));
        while(valread = read( new_socket , buffer, 1024) > 0) {
            if(strcmp(buffer, "tambah") == 0) {
                *value += 1;
            }
            memset(buffer, 0, sizeof(buffer));
        }
    }
```

3. Untuk mengeluarkan jumlah stok yang tersedia di penjual

```sh
void *print_value(void *ptr) {
    while(1) {
        printf("Stok saat ini : %d\n", *value);
        sleep(5);
    }
```
## 3. soal3
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:

a. Terdapat 2 karakter Agmal dan Iraj
b. Kedua karakter memiliki status yang unik
	-Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
	
	-Iraj memiliki Spirit_Status, di awal program memiliki status 100
	
	-Terdapat 3 Fitur utama
		
		All Status, yaitu menampilkan status kedua sahabat
		
		Ex: Agmal WakeUp_Status = 75 
      		    
		    Iraj Spirit_Status = 30
		
		“Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
		
		“Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
	
	-Terdapat Kasus yang unik dimana:
		
		Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
		
		Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
	
	-Program akan berhenti jika Salah Satu :
		
		WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
		
		Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)

#### Syarat Menggunakan Lebih dari 1 Thread
### Jawaban:
> Check : [Full SourceCode](https://github.com/sherlyrosa/SoalShift_Modul3_B02/blob/master/SoalNo3/no3.c)
### Penjelasan :
1. pertama-tama buat karakter agmal dan iraj dalam bentuk fungsi, dan langsung dalam bentuk thread, karena akan dijalankan secara pararel.
```c
void *agmal(void *argv);
void *iraj(void *argv);
```
2. Buat variable untuk menampung WakeUp status Agmal dan Spirit Status Iraj sebagai variable global.
```c
int WakeUp_Status = 0;
int Spirit_Status = 100;
```
3. Buat fungsi agmal dan iraj bekerja sebagai thread.
```c
... 
    pthread_t tid_a, tid_i, tid_s;
    pthread_create(&tid_a, NULL, agmal, NULL);
    pthread_create(&tid_i, NULL, iraj, NULL);
...
    pthread_join(tid_a, NULL);
    pthread_join(tid_i, NULL);
...
```
4. Buat menu main aplikasi menggunakan command.
```c
    char *cmd = malloc(100);
    char *s1 = "All Status";
    char *s2 = "Agmal Ayo Bangun";
    char *s3 = "Iraj Ayo Tidur";
...
    while(1){
        gets(cmd);
        if(strcasecmp(cmd, s1) == 0){
            printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }else if(strcasecmp(cmd, s2) == 0){
            printf("agmal ayo bangun\n");
        }else if(strcasecmp(cmd, s3) == 0){
            printf("iraj ayo tidur\n");
        }
    }
...
```
5. Karena antara command dan fungsi yang menjalankan perubahan status agmal dan iraj diberbeda tempat namun berjalan seirama, dapat digunakan variable untuk memanipulasi keadan mereka. Pertama buat varible untuk menunjuk keadaan dimana user memberikan command ke fungsi agmal dan iraj.
```c
int i_ptr = 0;
int a_ptr = 0;
```
6. dan karena di kondisi dimana kita tidak dapat memberikan command sebabanyak tiga kali maka dapat ditambahkan variable global:
```c
int i_stat = 0;
int a_stat = 0;
```
7. Sekarang proses utama di fungsi main() dapat dilengkapi menjadi :
```c
    while(1){
        gets(cmd);
        if(strcasecmp(cmd, s1) == 0){
            printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }else if(strcasecmp(cmd, s2) == 0){
            // printf("agmal ayo bangun\n");
            if(a_stat != 3)
                a_ptr = 1;
        }else if(strcasecmp(cmd, s3) == 0){
            // printf("iraj ayo tidur\n");
            if(i_stat != 3)
                i_ptr = 1;
        }
    }
```
8. Setelah itu, lengkapi fungsi agmal, dimana setelah variable a_stat berisikan 3 makan fungsi ini akan di-disable selama 10 detik, dan jika tidak maka value WakeUp_Status ditambah 15 dan i_stat bertambah 1.
```c
void *agmal(void *argv){
    while (1) {
        if(a_stat == 3){            
            printf("Agmal Ayo Bangun disabled 10 s\n");
            sleep(10);
            // printf("\tagmal sleep selesai\n");
            a_stat = 0;
        }else if(a_ptr == 1 && a_stat != 3){
            a_ptr = 0;
            WakeUp_Status += 15;
            i_stat++;
            // printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            // printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }
    }
    
}
```
9. Begitu juga dengan fungsi iraj, namun sebaliknya.
```c
void *iraj(void *argv){
    while (1) {
        if(i_stat == 3){
            printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
            sleep(10);
            // printf("\tiraj sleep selesai\n");
            i_stat = 0;
        }else if(i_ptr == 1 && i_stat != 3){
            i_ptr = 0;
            Spirit_Status -= 20;
            a_stat++;
            // printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            // printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }
    }
}
```
10. Terakhir tambahkan thread untuk memeriksa dimana WakeUp_Status agmal >= 100 dan juga Spirit_Status iraj <= 0 maka hentikan program.
```c
...
    pthread_t tid_a, tid_i, tid_s;
...
    pthread_create(&tid_s, NULL, checker, NULL);
...
    pthread_join(tid_s, NULL);
...
```
Untuk fungsinya:
```c
void *checker(void *argv){
    while(1){
        if(WakeUp_Status >= 100){
            printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
            exit(0);
        }
        if(Spirit_Status <= 0){
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            exit(0);
        }
    }
}
```