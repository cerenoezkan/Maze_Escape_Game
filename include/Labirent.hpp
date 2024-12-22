#ifndef LABIRENT_HPP
#define LABIRENT_HPP

#include <fstream>
#include <iomanip>
#include "Windows.h"
#include <sstream>

#include "Konum.hpp"
#include "Stack.hpp"
#define YUKSEKLIK 20
#define GENISLIK 50

class Labirent{
	public:
		char harita[YUKSEKLIK][GENISLIK]; //Labirentin haritasını tutan 2D karakter dizisi.
		int x,y; // '>'  mevcut konumu.
		Yon yon; //hangi yönde hareket ettiğini tutar
		Konum bitis; //Labirentin bitiş noktasının koordinatları.
		Stack<Konum> *yigit; //Hareketlerin geri alınıp alınamayacağına karar vermek için kullanılan bir stack.
		
		Labirent(Konum, Konum); //labirent haritasını okur ve başlangıç ile bitiş konumlarını ayarlar.
		Konum mevcutKonum(); //Mevcut konumu döndürür.
		bool adimAt(Konum, Konum); //yeni bir konuma hareket ettiğinde) çağrılır
		void ayarla(Konum,Yon); //'>' konumunu ve yönünü günceller.
		bool CikisaGeldimi(); //bitiş noktasına ulaşıp ulaşmadığını kontrol eder.
		bool EngelVarmi(Konum);	//Belirli bir konumda engel olup olmadığını kontrol eder.
		string yaz(); //mevcut durumunu (konum, engeller vs.) yazdırır.
};

#endif
