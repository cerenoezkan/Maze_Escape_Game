#ifndef KONUM_HPP
#define KONUM_HPP

typedef enum{ ASAGI, SOL, YUKARI, SAG}Yon;
/*Bu enum, yönleri temsil etmek için kullanılıyor.enum yapısında tanımlanan her bir sabit, sırasıyla 0, 1, 2, 3 gibi tamsayı değerlerine sahiptir*/
/*typedef kullanımı = Enum türünü Yon adıyla tanımlar. Bu sayede, bu enum türünü daha kolay bir şekilde kodda kullandık*/

struct Konum{ 
	int x,y; //x satır , y sütun değeri 
	Yon yon;
	Konum(int,int,Yon);
	Konum(int,int);
	Konum();
	Konum AyniYon();
	Konum SaatYonu(Yon);
	Konum Asagi();
	Konum Yukari();
	Konum Sol();
	Konum Sag();
	Yon TersYon();
};

#endif