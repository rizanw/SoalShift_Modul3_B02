# SoalShift_Modul3_B02

## 1. soal1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
##### Contoh
##### ./faktorial 5 3 4
##### 3!=6
##### 4!=24
##### 5!=120
### Jawaban:
> Check : [Full SourceCode]
### Penjelasan :
1. Karena input-an pada file yang diminta ialah dalam bentuk argumen maka menggunakan `argc` dan `argv`.
2. Untuk menghitung `factorial` nya 
```sh
void *factorial(void *args) {
	int fac=1;
	char* temp = (char*)args;
	int argc = temp[0] - '0';
	for(int a=1; a<=argc;a++){
		fac=fac*a;
	}
	printf("Factorial of Given Number is = %d\n",fac);
}
```
