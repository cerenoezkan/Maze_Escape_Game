#include "Labirent.hpp"

// Labirent sınıfının yapıcısı
	Labirent::Labirent(Konum baslangic, Konum bitis){
	FILE* fp = fopen("Harita.txt", "r"); //Harita.txt dosyasını okuma modunda açtık
	unsigned char karakter = 0;
	int satir=0,sutun=0; //Başlangıç x ve y kordinatı 
	//Başlangıç konumunu (baslangic.x ve baslangic.y) ayarlar.
	x = baslangic.x; // Başlangıç konumunun x koordinatını alıyoruz
	y = baslangic.y; // Başlangıç konumunun y koordinatını alıyoruz
	this->bitis = bitis; // Bitiş konumunu atıyoruz
	yon = ASAGI; // Başlangıç yönünü "aşağı" olarak ayarlıyoruz.

	// Yığın (stack) oluşturuluyor
	yigit = new Stack<Konum>(); // dinamik Stack nesnesi oluşturuluyor
	yigit->push(Konum(-1,-1,yon)); // İlk konum olarak (-1, -1, ASAGI) değeri yığına ekleniyor.
	//-1,-1 denmesinin sebebi ilk konum değeri olduğu anlaşılması için çünkü yığıt içine gittiğimiz yönleri kaydedicez.

	// Harita dosyasını okuma ve harita dizisine aktarma
	while (!feof(fp)) {
	   karakter = getc(fp); // Dosyadan bir karakter okur
	   if(karakter == 255)
	  	 break; //255 değeri, dosya sonu belirlemek için bir özel işaretçi olarak kullanılmış. Dosya sonu ifadesi.

	   if(karakter == 10){ //10, ASCII karakter tablosunda bir satır sonu (newline) karakterini ifade eder ve genellikle metin dosyalarında satır sonlarını ayırt etmek için kullanılır.
		 satir++;
		 sutun=0;
	   }
	   else{
			harita[satir][sutun] = karakter; // Okunan karakteri harita dizisine kaydediyoruz
			sutun++; // Sutun değerini arttırıyoruz
	   }
	}
}
// Mevcut konumu döndüren fonksiyon
Konum Labirent::mevcutKonum(){
	return Konum(x,y,yon); // Mevcut konum (x, y) ve yönü döndürüyoruz.
}

// Adım atma fonksiyonu
bool Labirent::adimAt(Konum mevcut, Konum ileri){ // Eğer ileri konumda engel yoksa, adım atılır
	if(!EngelVarmi(ileri)){ //ileri zaten konum ve yön bilgilerini içerisinde içeriyordu, sonrasında kontroller başlıyor 
		yigit->push(mevcut); // Mevcut konumu yığına ekler
		ayarla(ileri,ileri.yon); // İleri konum ve yön ile ayar yapılır
		return true; // Adım atma başarılı
	}
	return false; // Engel varsa adım atma başarısız
}

// Yeni konum ve yönle güncelleme yapan fonksiyon
void Labirent::ayarla(Konum konum,Yon yon){
	system("cls"); //Ekranı temizler (Windows için).

	//Yeni konum ve yön değerleriyle güncellenir.
	this->x = konum.x; // Yeni konumu x'e atar
	this->y = konum.y; // Yeni konumu y'ye atar
	this->yon = yon; // Yeni yönü yon'a atar

	harita[konum.x][konum.y] = '-';  // Geçilen yer '-' ile işaretlenir.
    
	cout<<yaz(); //Labirentin güncel halini ekrana yazdırır.
	Sleep(100); //100 milisaniye (0.1 saniye) bekler, böylece her hareketi görselleştirir.
}

// Çıkışa ulaşıp ulaşmadığını kontrol eden fonksiyon
bool Labirent::CikisaGeldimi(){
	return x == bitis.x && y == bitis.y; // Eğer x ve y koordinatları bitiş noktasına eşitse, çıkışa ulaşılmış demektir.
}

// Engel kontrol fonksiyonu, adım atma için önemli !
bool Labirent::EngelVarmi(Konum konum){		
	// Harita dışı bir konum olup olmadığını kontrol ederiz.	
	if(konum.x >= YUKSEKLIK || konum.x < 0 || konum.y >= GENISLIK || konum.y < 0) 
		return false;

	// Eğer harita'da belirtilen konumda engel varsa, (engel = '#' veya boş alan = '-')
	return harita[konum.x][konum.y] == '#' || harita[konum.x][konum.y] == '-'; //geçtiğimiz yerlere '-' koyuyoruz 
}

// Harita yazdırma fonksiyonu
string Labirent::yaz(){
    char YonChr[] = {'v', '<', '^', '>'}; // Yönleri karakter olarak tanımladık: v (aşağı), < (sol), ^ (yukarı), > (sağ)
    stringstream ss; // stringstream kullanarak string oluşturuyoruz.

    // Harita üzerinde gezinip her bir hücreyi yazdırıyoruz
    for(int satir=0; satir<YUKSEKLIK; satir++){
        ss << setw(10); // Satır başına boşluk ekler, düzenli bir çıktı elde edilir
        for(int sutun=0; sutun<GENISLIK; sutun++){
            if(satir == x && sutun == y){
                ss << YonChr[yon]; // Eğer bu konum, oyuncunun bulunduğu konumsa, yön karakterini yazdırırız
            }
            else{
                // Eğer harita hücresinde '-' varsa, onu yazdır
                if(harita[satir][sutun] == '-') {
                    ss << '-'; // Geçilen yerin üzerinde '-' işareti yazdırılır
                }
                else {
                    ss << harita[satir][sutun]; // Engel varsa engel karakterini yazdırır
                }
            }
        }   
        ss << endl; // Satır sonunda yeni satıra geçilir
    }
    return ss.str(); // Ekranda gösterilecek labirentin tam halini döndürüyoruz
}