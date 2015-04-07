#include "CRTC.h"

// ##############################
// # CONSTRUCTEUR - DESTRUCTEUR #
// ##############################

CRTC::CRTC() {}

CRTC::~CRTC() {}

// ######################################################
// # METHODES DE MODIFICATION DES VALEURS DES REGISTRES #
// # DE L'HORLOGE RTC 									#
// ######################################################

void CRTC::setRTCValReg(__u8 val, __u8 reg)
{
	__u8 valEnvoye = val;

	if( val > 9)
 	{
 		valEnvoye = (val/10) << 4;
		valEnvoye += val % 10;
 	}

	writeByte(reg, valEnvoye);
}

void CRTC::setRTCSecondes(int secondes)
{
	setRTCValReg(
		static_cast<__u8>(ADDR_REG::SECONDES),
		static_cast<__u8>(secondes)
		);
}

void CRTC::setRTCMinutes(int minutes)
{
	setRTCValReg(
		static_cast<__u8>(minutes),
		static_cast<__u8>(ADDR_REG::MINUTES)
		);
}

void CRTC::setRTCHeures(int heures)
{
	if( getRTCModeHeure() != MODE_HEURE::MODE_VINGT_QUATRE )
		throw CRTC::ErreurModeHeure(MODE_HEURE::MODE_DOUZE);

	setRTCValReg(
		static_cast<__u8>(ADDR_REG::HEURES),
		static_cast<__u8>(heures)
		);
}

void CRTC::setRTCHeures(int heures, PERIODE_HORAIRE pHoraire)
{
	if( getRTCModeHeure() != MODE_HEURE::MODE_DOUZE )
		throw ErreurModeHeure(MODE_HEURE::MODE_VINGT_QUATRE);

	const int masque_mode = 0x40;
	const int masque_pm = 0x20;
	int valEnvoye = 0;

	valEnvoye = (heures/10) << 4;
	valEnvoye += heures % 10;

	valEnvoye |= masque_mode;

	if( pHoraire == PERIODE_HORAIRE::PM )
		valEnvoye |= masque_pm;

	writeByte(
		static_cast<__u8>(ADDR_REG::HEURES),
		static_cast<__u8>(valEnvoye)
		);
}

void CRTC::setRTCJourSemaine(int jour_semaine)
{
	setRTCValReg(
		static_cast<__u8>(ADDR_REG::JOUR_SEMAINE),
		static_cast<__u8>(jour_semaine)
		);
}

void CRTC::setRTCJourMois(int jour_mois)
{
	setRTCValReg(
		static_cast<__u8>(ADDR_REG::JOUR_MOIS),
		static_cast<__u8>(jour_mois)
		);
}

void CRTC::setRTCMois(int mois)
{
	setRTCValReg(
		static_cast<__u8>(ADDR_REG::MOIS),
		static_cast<__u8>(mois)
		);
}

void CRTC::setRTCAnnee(int annee)
{
	setRTCValReg(
		static_cast<__u8>(ADDR_REG::ANNEE),
		static_cast<__u8>(annee)
		);
}

void CRTC::setRTCDate(str_date date)
{
	setRTCJourSemaine(date.jour_semaine);
	setRTCJourMois(date.jour_mois);
	setRTCMois(date.mois);
	setRTCAnnee(date.annee);
}

void CRTC::setRTCTime(str_heure heure)
{
	setRTCSecondes(heure.secondes);
	setRTCMinutes(heure.minutes);

	if( heure.mode == MODE_HEURE::MODE_DOUZE )
		setRTCHeures(heure.heures, heure.pHoraire);
	else
		setRTCHeures(heure.heures);
}
void CRTC::setRTCDateTime(str_dateHeure dateHeure)
{
	setRTCDate(dateHeure.date);
	setRTCTime(dateHeure.heure);
}

// ######################################################
// # METHODES DE RECUPERATION DES VALEURS DES REGISTRES #
// # DE L'HORLOGE RTC 									#
// ######################################################

int CRTC::getRTCValReg(__u8 reg)
{
	const int masque_premier_octet = 0x0F;
	const int masque_deuxieme_octet = 0xF0;
	int data = readByte(reg);
	int res = 0;

	res = data & masque_premier_octet;
	res += 10 * ((data & masque_deuxieme_octet) >> 4);

	return res;
}

int CRTC::getRTCSecondes()
{
	return getRTCValReg(static_cast<__u8>(ADDR_REG::SECONDES));
}

int CRTC::getRTCMinutes()
{
	return getRTCValReg(static_cast<__u8>(ADDR_REG::MINUTES));
}

int CRTC::getRTCHeures()
{
	if( getRTCModeHeure() != MODE_HEURE::MODE_VINGT_QUATRE)
		throw ErreurModeHeure(MODE_HEURE::MODE_DOUZE);

	return getRTCValReg(static_cast<__u8>(ADDR_REG::HEURES));
}

int CRTC::getRTCHeures(PERIODE_HORAIRE &pHoraire)
{
	const int masque_premier_octet = 0x0F;
	const int masque_deuxieme_octet = 0xF0;
	const int masque_pm = 0x20;
	const int masque_delete_mode = 0xBF;
	const int masque_delete_pm = 0xDF;
	int data = readByte(static_cast<__u8>(ADDR_REG::HEURES));
	int res = 0;

	if( getRTCModeHeure() != MODE_HEURE::MODE_DOUZE )
		throw ErreurModeHeure(MODE_HEURE::MODE_VINGT_QUATRE);

	if( ((data & masque_pm) >> 5) == 1)
		pHoraire = PERIODE_HORAIRE::PM;
	else
		pHoraire = PERIODE_HORAIRE::AM;

	data &= masque_delete_pm;
	data &= masque_delete_mode;

	res = data & masque_premier_octet;
	res += 10 * ((data & masque_deuxieme_octet) >> 4);

	return res;
}

int CRTC::getRTCJourSemaine()
{
	return getRTCValReg(static_cast<__u8>(ADDR_REG::JOUR_SEMAINE));
}

int CRTC::getRTCJourMois()
{
	return getRTCValReg(static_cast<__u8>(ADDR_REG::JOUR_MOIS));
}

int CRTC::getRTCMois()
{
	return getRTCValReg(static_cast<__u8>(ADDR_REG::MOIS));
}

int CRTC::getRTCAnnee()
{
	return getRTCValReg(static_cast<__u8>(ADDR_REG::ANNEE));
}

CRTC::str_date CRTC::getRTCDate()
{
	str_date temp;

	temp.jour_semaine = getRTCJourSemaine();
	temp.jour_mois = getRTCJourMois();
	temp.mois = getRTCMois();
	temp.annee = getRTCAnnee();

	return temp;
}

CRTC::str_heure CRTC::getRTCTime()
{
	str_heure temp;

	temp.secondes = getRTCSecondes();
	temp.minutes = getRTCMinutes();
	temp.mode = getRTCModeHeure();

	if( temp.mode == MODE_HEURE::MODE_DOUZE )
		temp.heures = getRTCHeures(temp.pHoraire);
	else
		temp.heures = getRTCHeures();

	return temp;
}

CRTC::str_dateHeure CRTC::getRTCDateHeure()
{
	str_dateHeure temp;
	temp.date = getRTCDate();
	temp.heure = getRTCTime();

	return temp;
}

CRTC::MODE_HEURE CRTC::getRTCModeHeure()
{
	const int masque_mode = 0x40;
	int data = readByte(static_cast<__u8>(ADDR_REG::HEURES));

	if( ((data & masque_mode) >> 6) == 1)
		return MODE_HEURE::MODE_DOUZE;
	else
		return MODE_HEURE::MODE_VINGT_QUATRE;
}