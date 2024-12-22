#include "Labirent.hpp"


int main(){
	Labirent *labirent = new Labirent(Konum(0,20),Konum(19,11)); //labirent dinamik olarak oluşturuluyor.
	//Bu nesneye başlangıç (Konum(0, 20)) ve bitiş (Konum(19, 11)) noktaları atanıyor.
	//Labirent sınıfının yapıcısı çağrılacak ve harita verisi yüklenecek.

	labirent->yigit->push(Konum(labirent->x,labirent->y,ASAGI)); // Bu satırda, labirent->yigit (yığın) üzerine ilk konum ekleniyor.
	// Başlangıç konumu (0, 20) ve yön (ASAGI) Konum objesi olarak yığına itiliyor.
	labirent->ayarla(Konum(labirent->x,labirent->y,ASAGI).Asagi(),ASAGI); //Yığın ile eklenen başlangıç konumunun bir adım aşağıya (Asagi()) hareket etmesi sağlanıyor
	// ve bu yeni konumla birlikte yön (ASAGI) güncelleniyor.
	
	while(!labirent->CikisaGeldimi()){ // Bu döngü, oyuncunun labirentteki bitiş noktasına (19, 11) ulaşana kadar devam eder. Eğer oyuncu bu noktaya ulaşırsa döngü sonlanır.
		int denemeYonSayisi=1; //her bir adımda yön değiştirmeye çalışırken kullanılan sayaçtır. 
		Konum oncekiKonum = labirent->yigit->top();
		Konum mevcutKonum = labirent->mevcutKonum();

		Konum ileri = mevcutKonum.AyniYon(); //mevcutKonum nesnesinin yönüne bağlı olarak, oyuncunun hareket edeceği yeni konum (ileri) belirleniyor. Bu fonksiyon yönüne göre bir sonraki konumu döndürür.

		if(!labirent->adimAt(mevcutKonum,ileri)){
			/*Eğer bir adım atılabilirse, adimAt fonksiyonu mevcutKonumdan ileri konumuna geçişi gerçekleştirir. 
			Eğer bu adım engel içeriyorsa (EngelVarmi fonksiyonu aracılığıyla kontrol edilir), yeni yönler denenmeye başlanır.*/
			int i = 0; // Deneme yön sayacını başlatıyoruz. i, saat yönünde dönecek yönlerin sayısını takip eder.
			bool sonuc = false; // Sonuç değişkeni, yön denemeleri başarılı olursa true, aksi takdirde false olur.
			Konum yeni = mevcutKonum; // Yeni bir Konum nesnesi oluşturuyoruz ve başlangıç olarak mevcut konumu atıyoruz.
			while(!sonuc && denemeYonSayisi < 5) { // Sonuç bulunana kadar ve 5 denemeyi aşmadığımız sürece döngüye gireriz. Zaten 4 tane yönümüz var 
    		// Saat yönünde yeni bir yön hesaplanır. (mevcutKonum.yon + i) % 4 ile, yönler arasında dönme sağlanır.
    		yeni = mevcutKonum.SaatYonu((Yon)((mevcutKonum.yon + i) % 4)); 
    		i++; // i'yi artırıyoruz, böylece bir sonraki adımda saat yönünde daha fazla dönüş yapılır.
    		denemeYonSayisi++; // Deneme sayısını bir artırıyoruz.
    
    		if(yeni.yon == mevcutKonum.TersYon()) { // Eğer yeni yön, mevcut yönün tam tersiyse (geri dönme durumu),
        		sonuc = false; // Bu durumda, yön değiştirmek yerine geri dönülmesini engelliyoruz, deneme başarısız oluyor.
    		} else { 
        	// Eğer yön ters değilse, yeni yönle adım atılmaya çalışılır.
        	sonuc = labirent->adimAt(mevcutKonum, yeni); 
        	// adimAt fonksiyonu, yeni konuma geçip geçilemeyeceğini kontrol eder.
    }
}

			}
			if(denemeYonSayisi == 5){ 
    		// Eğer deneme sayısı 5'e ulaşmışsa, bu demektir ki 5 farklı yön denendikten sonra hala geçerli bir yön bulunamamış.
    		// Bu durumda, geri gitmek ve önceki konuma dönmek gerekiyor.
    
    		labirent->yigit->pop(); 
    		// Yığın (stack) üzerinde en son eklenen öğe çıkarılır. Bu, mevcut konumdan geri adım atılmasını sağlar.
    		// Yığın, önceki konumu tutuyordu ve `pop` işlemi ile bu konum yığından çıkarılacak.
    
    		labirent->ayarla(oncekiKonum, oncekiKonum.TersYon());
    		// `oncekiKonum`'a geri dönülmesi sağlanır. Ayrıca, `TersYon()` fonksiyonu kullanılarak, bu konuma ters yönde bir adım yapılır.
    		// Bu, geri gitmek anlamına gelir, yani bir önceki hareketin tersine dönülür. Böylece, labirentin geri yolunda ilerlenebilir.
			}

		}
	cout<<"CIKISA GELDI"<<endl;

	getchar();

	delete labirent;
	return 0;
	}

	
