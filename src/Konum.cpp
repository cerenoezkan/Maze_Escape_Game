#include "Konum.hpp"
//Konum yapısının nesnelerini oluşturmak için kullanılır.
Konum::Konum(int x,int y, Yon yon){
	this->x = x;
	this->y = y;
	this->yon = yon;
}
Konum::Konum(int x,int y){
	this->x = x;
	this->y = y;
	this->yon = ASAGI;
}
Konum::Konum(){
	x=0;
	y=0;
	yon=ASAGI;
}
Konum Konum::AyniYon(){ //
	switch(yon){
		case YUKARI:
			return Yukari();
		case SAG:
			return Sag();
			case ASAGI:
			return Asagi();
		default:
			return Sol();
	}
}
Konum Konum::SaatYonu(Yon yn){ //yn yönüne göre saat yönünde dönüş yapan bir hareketi gerçekleştirir.
	switch(yn){
		case YUKARI:
			return Sag(); // Saat yönünde ilk hareket: sağa
		case SAG:
			return Asagi(); // Saat yönünde ikinci hareket: aşağıya
		case ASAGI:
			return Sol();  // Saat yönünde üçüncü hareket: sola
		default:
			return Yukari(); // Saat yönünde dördüncü hareket: yukarıya
	}
}
//mevcut Konum nesnesinin yönüne göre yeni bir Konum döndürür.
Konum Konum::Asagi(){
	return Konum(x+1,y,ASAGI); //konumun yönünü belirtmek (saklamak) için tekrar yön değerini de göndermemiz gerekir
}
Konum Konum::Yukari(){
	return Konum(x-1,y,YUKARI);
}
Konum Konum::Sol(){
	return Konum(x,y-1,SOL);
}
Konum Konum::Sag(){
	return Konum(x,y+1,SAG);
}	
Yon Konum::TersYon(){ //konumun yönünü kontrol eder ve ona karşılık gelen ters yönü döndürür.
	if(yon == ASAGI) return YUKARI;
	if(yon == YUKARI) return ASAGI;
	if(yon == SOL) return SAG;
	if(yon == SAG) return SOL;
	return YUKARI; // Eğer yukarıdaki şartların hiçbiri sağlanmazsa, varsayılan olarak YUKARI döndür.
	//Bu satır, genellikle bir güvenlik önlemi olarak kullanılır. Eğer yon değeri beklenmeyen bir şeyse, varsayılan olarak YUKARI döndürülür.
}