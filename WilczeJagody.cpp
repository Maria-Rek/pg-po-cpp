//#include "WilczeJagody.h"
//#include "Swiat.h"
//
//WilczeJagody::WilczeJagody(Swiat* swiat, Punkt polozenie)
//    : Roslina(swiat, polozenie, 99) {  // 99 si³y tylko po to, ¿eby nikt ich nie zjada³ "zwyczajnie"
//}
//
//char WilczeJagody::rysowanie() const {
//    return 'J';
//}
//
//std::string WilczeJagody::nazwa() const {
//    return "WilczeJagody";
//}
//
//void WilczeJagody::kolizja(Organizm* inny) {
//    std::string atakujacy = inny->nazwa();
//    std::string ja = nazwa();
//
//    swiat->usunOrganizm(inny);  // zjadaj¹cy ginie
//    swiat->usunOrganizm(this);  // jagody te¿ zostaj¹ zniszczone
//
//    swiat->dodajLog(atakujacy + " zjad³ " + ja + " i zgin¹³");
//}
